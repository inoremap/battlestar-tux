/* VerticalPane.h
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


#ifndef VERTICALPANE_H_
#define VERTICALPANE_H_

#include "Container.h"

/* A column of vertical widgets placed inside a bordered area. */
class VerticalPane : public Container {
	public:
				VerticalPane( GUI* g, bool resize, W_Alignment h );
				~VerticalPane();

				void Draw();

				// Update pane given the (x, y) position of the mouse cursor
				// and the state of the mouse buttons.
				void Update( int x, int y, int state );

	protected:
				// Re-Align elements in pane.
				void ReevaluateElements();

				// Resize widgets to fill pane.
				bool resizeWidgets;

				// Horizontal alignment of widgets (right, center, left).
				W_Alignment hAlign;

	private:
				VerticalPane( const VerticalPane &vc );
				const VerticalPane & operator= ( const VerticalPane &vc );
};

#endif /*VERTICALPANE_H_*/
