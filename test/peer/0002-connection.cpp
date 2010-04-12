#include "Test.h"

using namespace XNet;

Peer* SetupPeer(SocketProvider* provider, uint16_t port)
{
	Peer* peer = new Peer(provider, port);
	// allocate plugins
	Plugins::AllowingConnections* plugin0 = new Plugins::AllowingConnections();
	// attach plugins
	peer->AttachPlugin(plugin0);
	// return
	return peer;
}

int main()
{
	SocketProvider* provider = new LocalOnlySocketProvider();
	Peer* peer0 = SetupPeer(provider, 1025);
	Peer* peer1 = SetupPeer(provider, 1026);

	ASSERT_NOT_NULL(peer0, "allocation of peer0 failed");
	ASSERT_NOT_NULL(peer1, "allocation of peer1 failed");

	std::cerr << "instructing peer1 to listen" << std::endl;	
	peer1->BeginListening();
	std::cerr << "instructing peer0 to connect" << std::endl;
	ASSERT_TRUE(peer0->Connect("localhost", 1026), "connection denied");

	std::cerr << "going into update cycle" << std::endl;

	for (int i = 0; i < 200; ++i)
	{
		std::cerr << "peer0->Update" << std::endl;
		peer0->Update(10);
		std::cerr << "peer1->Update" << std::endl;
		peer1->Update(10);
	}

	std::cerr << "leaving update cycle" << std::endl;

	delete peer1;
	delete peer0;

	delete provider;
	return 0;
}
