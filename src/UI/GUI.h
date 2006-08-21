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

/* Set of widgets and containers to be drawn. */
class GUI : public List {
	public:
				GUI( int w, int h );
				virtual ~GUI();

				// Create all widgets and bind listeners.
				virtual void CreateWidgets();

				// Draw all GUI widgets.
				virtual void Draw();

				// Some GUI widgets need to be drawn twice - usually for lighting reasons.
				virtual void SecondDraw();

				// Update all GUI widgets.
				void Update();

				int getScreenWidth();
				int getScreenHeight();

				FTFont* getFont();
				FTFont* getItalicFont();
				FTFont* getBoldFont();

	protected:
				// Screen width
				int screenW;
				// Screen height
				int screenH;

				FTFont* normalFont;
				FTFont* italicFont;
				FTFont* boldFont;

	private:
				GUI( const GUI &gui );
				const GUI & operator= ( const GUI &gui );

				// Called right before drawing widgets.
				void beforeDraw();

				// Called right after drawing widgets.
				void afterDraw();
};

#endif /*GUI_H_*/
