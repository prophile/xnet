#include "Logging.h"
#include <stdio.h>

namespace XNet
{

namespace Plugins
{

Logging::Logging()
{
	fprintf(stderr, "Logging plugin constructed\n");
}

Logging::~Logging()
{
	fprintf(stderr, "Logging plugin destroyed\n");
}

void Logging::DidAttach()
{
	fprintf(stderr, "Logging plugin attached\n");
}

void Logging::DidDetach()
{
	fprintf(stderr, "Logging plugin detached\n");
}

void Logging::DidConnect(ConnectionID connectionID, const std::string& hostname, uint16_t port)
{
	fprintf(stderr, "Connection %d established to %s port %d\n", connectionID, hostname.c_str(), port);
	Plugin::DidConnect(connectionID, hostname, port);
}

void Logging::DidDisconnect(ConnectionID connectionID)
{
	fprintf(stderr, "Connection %d broken\n", connectionID);
	Plugin::DidDisconnect(connectionID);
}

void Logging::DidReceiveMessage(ConnectionID connectionID, const Message& message)
{
	fprintf(stderr, "Got message %d from connection %d, content: %s\n", message.id, connectionID, message.data.c_str());
	Plugin::DidReceiveMessage(connectionID, message);
}

bool Logging::AuditConnection(const std::string& hostname, uint16_t port)
{
	fprintf(stderr, "Auditing incoming connection from %s port %d\n", hostname.c_str(), port);
	return Plugin::AuditConnection(hostname, port);
}

bool Logging::AuditOutgoingMessage(ConnectionID connectionID, const Message& message)
{
	fprintf(stderr, "Auditing message %d to connection %d, content: %s\n", message.id, connectionID, message.data.c_str());
	return Plugin::AuditOutgoingMessage(connectionID, message);
}

}

}
