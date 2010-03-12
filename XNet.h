#ifndef __XNET__
#define __XNET__

#include <string>
#include <map>
#include <inttypes.h>

namespace XNet
{

typedef uint32_t MessageID;
typedef unsigned long ConnectionID;

class Peer;

struct Message
{
private:
	std::map<std::string, std::string>* metadata;
public:
	MessageID id;
	std::string data;
	bool reliable, ordered;

	Message(MessageID mid, const std::string& payload = "", bool isReliable = true, bool isOrdered = true)
	: id(mid),
	  data(payload),
	  reliable(isReliable),
	  ordered(isOrdered),
	  metadata(0)
	{
	}

	Message(const Message& om)
	: id(om.id),
	  data(om.data),
	  reliable(om.reliable),
	  ordered(om.ordered)
	{
		if (om.metadata)
		{
			metadata = new std::map<std::string, std::string>(*om.metadata);
		}
		else
		{
			metadata = 0;
		}
	}
	
	~Message()
	{
		if (metadata) delete metadata;
	}

	std::string GetMetadata(const std::string& key) const
	{
		if (!metadata) return "";
		std::map<std::string, std::string>::const_iterator iter;
		if ((iter = metadata->find(key)) == metadata->end())
		{
			return "";
		}
		else
		{
			return iter->second;
		}
	}

	void SetMetadata(const std::string& key, const std::string& value)
	{
		if (!metadata)
			metadata = new std::map<std::string, std::string>();
		metadata->insert(std::make_pair(key, value));
	}
};

class Plugin
{
private:
	friend class Peer;
	Plugin* next;
public:
	Plugin();
	virtual ~Plugin() = 0;

	virtual void DidConnect(Peer* peer, ConnectionID connectionID, const std::string& hostname, uint16_t port) {}
	virtual void DidDisconnect(Peer* peer, ConnectionID connectionID, bool started) {}
	virtual bool DidReceiveMessage(Peer* peer, ConnectionID connectionID, const Message& message) {return false;}
	virtual bool AuditConnection(Peer* peer, const std::string& hostname, uint16_t port) {return true;}
	virtual bool AuditIncomingMessage(Peer* peer, ConnectionID connectionID, const Message& message) {return true;}
	virtual bool AuditOutgoingMessage(Peer* peer, ConnectionID connectionID, const Message& message) {return true;}

	Plugin* NextPlugin() { return next; }
};

class Peer
{
private:
public:
	typedef unsigned long ConnectionID;
	typedef uint32_t MessageID;
	const static ConnectionID NOBODY = 0;
	const static ConnectionID EVERYBODY = -1;

	Peer();
	~Peer();

	void BeginListening(uint16_t port);
	void EndListening();
	std::string GetPassword() const;
	void SetPassword(const std::string& pw);
	void Connect(const std::string& remote, uint16_t port, const std::string& password);
	void Disconnect(ConnectionID connection = EVERYBODY);
	void KillConnection(ConnectionID connection = EVERYBODY);
	void SendMessage(const Message& message,
	                 ConnectionID target = EVERYBODY);
	Plugin* FirstPlugin();
	void AttachPlugin(Plugin* plugin);
	void DetachPlugin(Plugin* plugin);
	void ReceiveMessage(ConnectionID source, const Message& message);
};

}

#endif
