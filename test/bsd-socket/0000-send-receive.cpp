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
	Socket* sender = provider->NewSocket(1025);
	Socket* receiver = provider->NewSocket(1026);
	uint32_t localhost = provider->ResolveHost("localhost");
	ASSERT_EQUAL(localhost, LOCALHOST, "failed to look up localhost");
	sender->Send(localhost, 1026, (const void*)"blah", 4);
	uint32_t receiveHost;
	uint16_t receivePort;
	size_t receiveLength;
	void* receiveData = NULL;
	for (int i = 0; i < 40 && !receiveData; ++i)
	{
		receiveData = receiver->Receive(receiveHost, receivePort, receiveLength);
		usleep(10000);
	}
	ASSERT_NOT_NULL(receiveData, "failed to receive message");
	ASSERT_EQUAL(0, memcmp(receiveData, (const void*)"blah", 4), "got wrong data");
	ASSERT_EQUAL(receiveHost, localhost, "got message from wrong host");
	ASSERT_EQUAL(receivePort, 1025, "got message on wrong port (expected 1025, got " << receivePort << ")");
	free(receiveData);
	delete receiver;
	delete sender;
	delete provider;
	return 0;
}
