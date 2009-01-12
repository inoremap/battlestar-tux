/* Battlestar TUX
 * Copyright (C) 2008-2009 Eliot Eshelman <battlestartux@6by9.net>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef NetworkManager_H
#define NetworkManager_H

class NetworkManager {
public:
    virtual ~NetworkManager();

    void initialise( NETWORK_TYPE eType );

    void connect();
    void disconnect();
    void updateNetworkSystem( unsigned long lTimeElapsed );

    void sendText();
    void sendObject();

    void receiveText();
    void reveiveObject();

    bool isConnected();
    NETWORK_TYPE getLocalType();

    static NetworkManager* getSingletonPtr();

    typedef enum {
        NETWORK_TYPE_HOST_LAN,
        NETWORK_TYPE_CLIENT_LAN,
        NETWORK_TYPE_DEDICATED_LAN,
        NETWORK_TYPE_HOST_INET,
        NETWORK_TYPE_CLIENT_INET,
        NETWORK_TYPE_DEDICATED_INET,
        NETWORK_TYPE_UNDEFINED
    } NETWORK_TYPE;

private:
    NetworkManager();
    NetworkManager( const NetworkManager& ) { }
    NetworkManager & operator = ( const NetworkManager& );

    void sendPacket();
    void receivePacket();

    NETWORK_TYPE eLocalType;

    static NetworkManaget *mNetworkManager;
};

#endif

