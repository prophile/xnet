#include "XNet.h"

namespace XNet
{

Plugin::Plugin()
: lower(0),
  higher(0),
  peer(0)
{
}

void Plugin::Update(unsigned long dt)
{
}

void Plugin::DidAttach()
{
}

void Plugin::DidDetach()
{
}

void Plugin::DidConnect(ConnectionID connectionID, const std::string& hostname, uint16_t port)
{
	if (higher)
		higher->DidConnect(connectionID, hostname, port);
}

void Plugin::DidDisconnect(ConnectionID connectionID, bool initiated)
{
	if (higher)
		higher->DidDisconnect(connectionID, initiated);
}

void Plugin::DidReceiveMessage(ConnectionID connectionID, const Message& message)
{
	if (higher)
		higher->DidReceiveMessage(connectionID, message);
}

bool Plugin::AuditConnection(const std::string& hostname, uint16_t port)
{
	return true;
}

bool Plugin::AuditOutgoingMessage(ConnectionID connectionID, const Message& message)
{
	if (lower)
		return lower->AuditOutgoingMessage(connectionID, message);
	return true;
}

}
