#include "XNet.h"
#include <assert.h>

namespace XNet
{

#ifdef __LITTLE_ENDIAN__
#define BE16(x) ((x)<<8 | (x)>>8)
#ifdef __clang__
#define BE32(x) __builtin_bswap32(x)
#else
#define BE32(x) ntohl(x)
#endif
#else
#define BE16(x) (x)
#define BE32(x) (x)
#endif

Peer::Peer(SocketProvider* provider, uint16_t port)
: highestPlugin(0),
  lowestPlugin(0),
  socketProvider(provider),
  primarySocket(0),
  acceptNewConnections(false)
{
	primarySocket = socketProvider->NewSocket(BE16(port));
}

Peer::~Peer()
{
	delete primarySocket;
}

void Peer::Update(unsigned long dt)
{
	// update plugins
	Plugin* current = highestPlugin;
	while (current)
	{
		current->Update(dt);
		current = current->lower;
	}
	// TODO: check connections
}

void Peer::Connect(const std::string& remote, uint16_t port)
{
	// TODO
}

void Peer::Disconnect(ConnectionID connection)
{
	// TODO
}

void Peer::SendMessage(const Message& message, ConnectionID target, Plugin* source)
{
	// TODO
}

void Peer::AttachPlugin(Plugin* plugin, Plugin* lowerThan)
{
	if (!highestPlugin)
	{
		highestPlugin = lowestPlugin = plugin;
		plugin->lower = plugin->higher = NULL;
	}
	if (lowerThan)
	{
		Plugin* p = highestPlugin;
		while (p && p != lowerThan)
		{
			 p = p->lower;
		}
		assert(p);
		if (p->lower)
		{
			p->lower->higher = plugin;
		}
		else
		{
			lowestPlugin = plugin;
		}
		p->lower = plugin;
		plugin->lower = NULL;
		plugin->higher = p;
	}
	else
	{
		highestPlugin->higher = plugin;
		plugin->lower = highestPlugin;
		plugin->higher = NULL;
		highestPlugin = plugin;
	}
}

void Peer::DetachPlugin(Plugin* plugin)
{
	// TODO
}

void Peer::ReceiveMessage(ConnectionID source, const Message& message, Plugin* plugin)
{
	// TODO
}

}
