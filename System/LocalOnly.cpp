#include "LocalOnly.h"
#include <map>

namespace XNet
{

#ifdef __LITTLE_ENDIAN__
const uint32_t LOCALHOST_IP = 0x0100007F;
#else
const uint32_t LOCALHOST_IP = 0x7F000001;
#endif

std::map<uint16_t, LocalOnlySocket*> portMappings;

LocalOnlySocket::LocalOnlySocket(uint16_t portno)
{
	localPort = portno;
	portMappings[portno] = this;
}

LocalOnlySocket::~LocalOnlySocket()
{
	std::map<uint16_t, LocalOnlySocket*>::iterator iter = portMappings.find(localPort);
	if (iter == portMappings.end() || iter->second != this)
		return;
	portMappings.erase(iter);
}

void LocalOnlySocket::Send(uint32_t host, uint16_t port, const void* data, size_t length)
{
	if (host != LOCALHOST_IP)
		return;
	std::map<uint16_t, LocalOnlySocket*>::iterator iter = portMappings.find(port);
	if (iter == portMappings.end())
		return;
	iter->second->queuedMessages.push(std::make_pair(port, std::string((const char*)data, length)));
}

void* LocalOnlySocket::Receive(uint32_t& host, uint16_t& port, size_t& length)
{
	if (queuedMessages.empty())
	{
		host = 0;
		port = 0;
		length = 0;
		return NULL;
	}
	else
	{
		std::pair<uint16_t, std::string> message = queuedMessages.front();
		queuedMessages.pop();
		host = LOCALHOST_IP;
		port = message.first;
		length = message.second.length();
		void* buffer = malloc(length);
		memcpy(buffer, message.second.data(), length);
		return buffer;
	}
}

}
