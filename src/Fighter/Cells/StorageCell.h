/* StorageCell.h
 *
 * Copyright 2007 Eliot Eshelman
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


#ifndef STORAGECELL_H_
#define STORAGECELL_H_

#include "HexCell.h"


// Store energy for the fighter to use.
class StorageCell : public HexCell {
	public:
				StorageCell( Fighter*, const ivec2 & );
				~StorageCell();

				void Draw();

				float getCurrentEnergy();
				void setMaxEnergy( float );
				float getMaxEnergy();

				// Store power.
				// The amount of power being stored is returned,
				// in case this cell can't store everything.
				float putPower( float );

				// Transfer power to another component.
				// The amount of power being transferred is returned,
				// in case this cell can't supply the full amount.
				float getPower( float );

	private:
				// The current amount of energy in the cell.
				float currentEnergy;

				// The maximum amount of energy that can be stored in this cell.
				float maxEnergy;

				StorageCell( const StorageCell & );
				const StorageCell & operator= ( const StorageCell & );
};


#endif /*STORAGECELL_H_*/
