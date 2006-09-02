/* Button.h
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


#ifndef BUTTON_H_
#define BUTTON_H_

#include <string>

#include "ButtonClickGenerator.h"
#include "Widget.h"

/* Clickable widget that displays a text string. */
class Button : public Widget, public ButtonClickGenerator {
	public:
				Button( GUI* gui, std::string s, W_HAlignment h, W_VAlignment v );
				~Button();

				void Draw();

				// Button was clicked.
				void ClickEvent();

	private:
				Button( const Button &button );
				const Button & operator= ( const Button &button );

				std::string buttonText;

				// Width of the text in the button.
				int textWidth;
};


#endif /*BUTTON_H_*/
