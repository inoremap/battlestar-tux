/* TextureManager.h
 *
 * Copyright 2005-2006 Eliot Eshelman
 * eliot@6by9.net
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


#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_

#include <SDL_image.h>
#include <SDL_opengl.h>
#include <iostream>
#include <string>

#include "Structures/StringArray.h"


/* Manages all image textures. */
class TextureManager {
	public:
				TextureManager();
				~TextureManager();

				// Get the texture ID for the specified image.
				GLuint loadTexture( std::string filename );
				GLuint loadTexture( std::string filename, int texture_quality );

				// Free the texture for the specified image.
				// If other instances of this texture are in use,
				// the texture won't be freed.
				void freeTexture( std::string filename );
				void freeTexture( GLuint id );
				void freeTextures( int num, GLuint* ids );

				// Remove all textures.
				void freeAllTextures();

	private:
				TextureManager( const TextureManager &t );
				const TextureManager & operator= ( const TextureManager &t );

				StringArray* textures;

				// Load texture into memory.
				GLuint loadTextureFile( std::string filename, int texture_quality );

};

#endif /*TEXTUREMANAGER_H_*/
