/* ButtonClickGenerator.h
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


#ifndef BUTTONCLICKGENERATOR_H_
#define BUTTONCLICKGENERATOR_H_

#include "ButtonClickEvent.h"
#include "ButtonClickListener.h"
#include "EventGenerator.h"

/* Generates button click events. */
class ButtonClickGenerator : public EventGenerator {
	public:
				ButtonClickGenerator() {}
				~ButtonClickGenerator() {}

				void AddListener( ButtonClickListener* l ) { addObject( l ); }
				void RemListener( ButtonClickListener* l ) { remObject( l ); }

	protected:
				virtual void GenerateEvent( ButtonClickEvent* e ) {
					ButtonClickListener* cur = (ButtonClickListener*) rootObj;

					while( cur ) {
						cur->EventGenerated( e );
						cur = (ButtonClickListener*) cur->getNext();
					}	
				}

	private:
				ButtonClickGenerator( const ButtonClickGenerator &gen );
				const ButtonClickGenerator & operator= ( const ButtonClickGenerator &gen );
};


#endif /*BUTTONCLICKGENERATOR_H_*/
