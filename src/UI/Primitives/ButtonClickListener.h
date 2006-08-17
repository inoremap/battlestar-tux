/* ButtonClickListener.h
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


#ifndef BUTTONCLICKLISTENER_H_
#define BUTTONCLICKLISTENER_H_

#include <iostream>

#include "Event.h"
#include "EventListener.h"

/* Listens for button clicks. */
class ButtonClickListener : public EventListener {
	public:
				ButtonClickListener() {}

				virtual ~ButtonClickListener() {}

				virtual void EventGenerated( ButtonClickEvent* e ) {
					cout << "Unhandled button click event generated...\n";
				}

	private:
				ButtonClickListener( const ButtonClickListener &l );
				const ButtonClickListener & operator= ( const ButtonClickListener &l );
};

#endif /*BUTTONCLICKLISTENER_H_*/
