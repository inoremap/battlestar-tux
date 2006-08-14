/* Event.h
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


#ifndef EVENT_H_
#define EVENT_H_

// Possible event types.
enum EventType {
	NULL_EVENT,				// Event that does nothing.
	BUTTONHOVER_EVENT,		// Mouse is hovering over button.
	BUTTONCLICK_EVENT		// Button was clicked.
};

/* Every widget event generates an object inherited from this event. */
class Event {
	public:
				Event( EventType t ) { type = t; }
				virtual ~Event() {}

				EventType getType() { return type; }

	private:
				Event( const Event &e );
				const Event & operator= ( const Event &e );

				// Type of event.
				EventType type;
};

#endif /*EVENT_H_*/
