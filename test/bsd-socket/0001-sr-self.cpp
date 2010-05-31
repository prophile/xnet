#include "Test.h"
#include <arpa/inet.h>

using namespace XNet;

#ifdef __LITTLE_ENDIAN__
#define LOCALHOST 0x0100007F
#else
#define LOCALHOST 0x7F000001
#endif

int main()
{
	BSDSocketProvider* provider = new BSDSocketProvider();
	Socket* socket = provider->NewSocket(htons(1025));
	uint32_t localhost = provider->ResolveHost("localhost");
	ASSERT_EQUAL(localhost, LOCALHOST, "failed to look up localhost");
	socket->Send(localhost, htons(1025), (const void*)"blah", 4);
	uint32_t receiveHost;
	uint16_t receivePort;
	size_t receiveLength;
	void* receiveData = NULL;
	for (int i = 0; i < 40 && !receiveData; ++i)
	{
		receiveData = socket->Receive(receiveHost, receivePort, receiveLength);
		usleep(10000);
	}
	char* rd = (char*)receiveData;
	ASSERT_NOT_NULL(receiveData, "failed to receive message");
	ASSERT_EQUAL(receiveHost, localhost, "got message from wrong host");
	ASSERT_EQUAL(receiveLength, 4, "got wrong number of bytes: expected 4, got " << receiveLength);
	ASSERT_EQUAL(receivePort, htons(1025), "got message on wrong port (expected 1025, got " << receivePort << ")");
	ASSERT_EQUAL(0, memcmp(receiveData, (const void*)"blah", 4), "got wrong data: expected 'blah', got '" <<
	             rd[0] << rd[1] << rd[2] << rd[3] << "'");
	free(receiveData);
	delete socket;
	delete provider;
	return 0;
}
