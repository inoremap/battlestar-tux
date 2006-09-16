/* TextureManager.cpp
 *
 * Copyright 2005-2006 Eliot Eshelman
 * battlestartux@6by9.net
 *
 *
 *  This file is part of Battlestar Tux.
 *
 *  Battlestar Tux is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  Battlestar Tux is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Battlestar Tux; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */


#include "TextureManager.h"

TextureManager::TextureManager() {
	textures = new StringArray();
}


TextureManager::~TextureManager() {
	// Remove all textures.
	delete textures;
}


GLuint TextureManager::loadTexture( std::string filename ) { return loadTexture( filename, GL_LINEAR ); }
GLuint TextureManager::loadTexture( std::string filename, int texture_quality ) {
	// Check for existing texture.
	GLuint textureID = textures->getID( filename );

	// Load texture since it doesn't already exist.
	if( !textureID ) {
		textureID = loadTextureFile( filename, texture_quality );

		if( textureID ) {
			textures->insert( filename, textureID );
		}
	}

	return textureID;
}


void TextureManager::freeTexture( std::string filename ) {
	GLuint id = textures->getID( filename );

	if( id )
		freeTextures( 1, &id );
}

void TextureManager::freeTexture( GLuint id ) {	freeTextures( 1, &id ); }
void TextureManager::freeTextures( int num, GLuint* ids ) {
	for( int i = 0; i < num; i++ )
		textures->remove( ids[i] );

	glDeleteTextures( num, ids );
}


void TextureManager::freeAllTextures() {
	glDeleteTextures( textures->getSize(), (const GLuint*) textures->getAllIDs() );
	textures->removeAll();
}


// Adapted from example SDL code:
// http://www.libsdl.org/cgi/docwiki.cgi/OpenGL_20Texture_20Example
GLuint TextureManager::loadTextureFile( std::string filename, int texture_quality ) {
	SDL_Surface* surface = 0;
	GLuint textureid;
	int mode;

	surface = IMG_Load( filename.c_str() );

	if( !surface ) {
		std::cout << "TextureManager: Couldn't load texture: " << filename << "\n";
		return 0;
	}

	/* RGB 24bit */
	if( surface->format->BytesPerPixel == 3 ) {
		mode = GL_RGB;
	}
	/* RGBA 32bit */
	else if( surface->format->BytesPerPixel == 4 ) {
		mode = GL_RGBA;
	}
	/* Unable to find suitable mode. */
	else {
		std::cout << "TextureManager: Couldn't find 24/32-bit texture: " << filename << "\n";
		SDL_FreeSurface( surface );
		return 0;
	}

	glGenTextures( 1, &textureid );
	glBindTexture( GL_TEXTURE_2D, textureid );
	glTexImage2D( GL_TEXTURE_2D, 0, mode, surface->w, surface->h, 0, mode, GL_UNSIGNED_BYTE, surface->pixels );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture_quality );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture_quality );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

	SDL_FreeSurface(surface);

	// We need to know when textures are being loaded.
	std::cout << "TextureManager: Texture loaded: " << filename << "\n";

	return textureid;
}
