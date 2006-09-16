/* ButtonClickEvent.h
 *
 * Copyright 2006 Eliot Eshelman
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


#ifndef BUTTONCLICKEVENT_H_
#define BUTTONCLICKEVENT_H_

#include <string>

#include "Event.h"

class ButtonClickEvent : public Event {
	public:
				ButtonClickEvent( std::string value ) : Event( BUTTONCLICK_EVENT ) {
					buttonText = value;
				}

				~ButtonClickEvent() {}

				std::string getButtonText() { return buttonText; }

	private:
				std::string buttonText;
};

#endif /*BUTTONCLICKEVENT_H_*/
