#ifndef __XNET_ORDERING__
#define __XNET_ORDERING__

#include "XNet.h"
#include <inttypes.h>
#include <map>

namespace XNet
{

namespace Plugins
{

class Ordering : public Plugin
{
private:
	std::map<ConnectionID, uint32_t> maxReceivedID;
	std::map<ConnectionID, uint32_t> nextSendID;
public:
	Ordering() {}

	virtual void DidDisconnect(ConnectionID);
	virtual void DidReceiveMessage(ConnectionID, const Message& message);
	virtual bool AuditOutgoingMessage(ConnectionID, const Message& message);
};

}

}

#endif
