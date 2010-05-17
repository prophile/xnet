#ifndef __XNET_SYSTEM_BSD__
#define __XNET_SYSTEM_BSD__

#include "SocketProvider.h"

namespace XNet
{

class BSDSocket : public Socket
{
private:
	int socket;
	friend class BSDSocketProvider;
	BSDSocket(int sock);
public:
	virtual ~BSDSocket();

	virtual void Send(uint32_t host, uint16_t port, const void* data, size_t length);
	virtual void* Receive(uint32_t& host, uint16_t& port, size_t& length);
};

class BSDSocketProvider : public SocketProvider
{
private:
public:
	BSDSocketProvider() {}
	virtual ~BSDSocketProvider();

	virtual Socket* NewSocket(uint16_t port);
	virtual uint32_t ResolveHost(const std::string& hostname);
	virtual std::string ReverseLookup(uint32_t host);
};

}

#endif
