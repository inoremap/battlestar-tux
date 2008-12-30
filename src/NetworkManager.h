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