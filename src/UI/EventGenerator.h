/* EventGenerator.h
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


#ifndef EVENTGENERATOR_H_
#define EVENTGENERATOR_H_

#include "../Structures/List.h"
#include "Event.h"
#include "EventListener.h"

/* All widgets which generate events inherit this generator. */
class EventGenerator : public List {
	public:
				EventGenerator::EventGenerator() {}
				EventGenerator::~EventGenerator() {}

	protected:
				void EventGenerator::AddListener( EventListener* l ) { addObject( l ); }
				void EventGenerator::RemListener( EventListener* l ) { remObject( l ); }

				void EventGenerator::GenerateEvent( Event* e ) {
					EventListener* cur = (EventListener*) rootObj;

					while( cur ) {
						cur->EventGenerated( e );
						cur = (EventListener*) cur->getNext();
					}	
				}

	private:
				EventGenerator( const EventGenerator &gen );
				const EventGenerator & operator= ( const EventGenerator &gen );
};


#endif /*EVENTGENERATOR_H_*/
