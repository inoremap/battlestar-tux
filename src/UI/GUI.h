/* GUI.h
 *
 * Copyright 2006 Eliot Eshelman
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


#ifndef GUI_H_
#define GUI_H_

#include <FTGLTextureFont.h>

#include "../Structures/List.h"

/* Top level Graphic User Interface class.
 * 
 * All widgets are controlled from here. */
class GUI : public List {
	public:
				GUI( int w, int h );
				~GUI();

				// Draw all GUI widgets.
				void Draw();

				// Update all GUI widgets.
				void Update();

				FTFont* getFont();
				FTFont* getItalicFont();
				FTFont* getBoldFont();

	private:
				GUI( const GUI &gui );
				const GUI & operator= ( const GUI &gui );

				// Screen width
				int screenW;
				// Screen height
				int screenH;

				FTFont* normalFont;
				FTFont* italicFont;
				FTFont* boldFont;
};

#endif /*GUI_H_*/
