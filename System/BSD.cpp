#include "BSD.h"
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <assert.h>
#include <errno.h>

namespace XNet
{

#define MAX_PACKET_SIZE 1500

BSDSocket::BSDSocket(int sock)
: socket(sock)
{
}

BSDSocket::~BSDSocket()
{
	close(socket);
}

void BSDSocket::Send(uint32_t host, uint16_t port, const void* data, size_t length)
{
	struct sockaddr_in address;
	memset(&address, 0, sizeof(address));
	address.sin_len = sizeof(address);
	address.sin_family = AF_INET;
	address.sin_port = port;
	address.sin_addr.s_addr = host;
	int rc = sendto(socket, data, length, 0, (const struct sockaddr*)&address, sizeof(address));
	if (rc == -1 && (errno == EAGAIN || errno == EINTR)) // would block, drop the packet
	{
		return;
	}
	else
	{
		assert((size_t)rc == length);
	}
}

void* BSDSocket::Receive(uint32_t& host, uint16_t& port, size_t& length)
{
	char packet[MAX_PACKET_SIZE];
	struct sockaddr_in address;
	socklen_t address_length = sizeof(address);
	ssize_t rv = recvfrom(socket, packet, MAX_PACKET_SIZE, 0, (struct sockaddr*)&address, &address_length);
	if (rv < 0)
	{
		if (errno != EAGAIN && errno != EINTR) // EAGAIN and EINTR can happen
		{
			perror("failed to receive packet");
		}
		length = 0;
		return NULL;
	}
	else if (rv == 0)
	{
		length = 0;
		return NULL;
	}
	else
	{
		void* data = malloc(length);
		memcpy(data, packet, length);
		length = rv;
		host = address.sin_addr.s_addr;
		assert(host);
		port = address.sin_port;
		assert(port);
		return data;
	}
}

BSDSocketProvider::~BSDSocketProvider()
{
}

Socket* BSDSocketProvider::NewSocket(uint16_t port)
{
	int rc;
	int sock = socket(PF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in address;
	memset(&address, 0, sizeof(address));
	address.sin_port = port;
	address.sin_family = AF_INET;
	rc = bind(sock, (const struct sockaddr*)&address, sizeof(address));
	assert(rc != 0);
	int flags;
	flags = fcntl(sock, F_GETFL);
	flags |= O_NONBLOCK;
	rc = fcntl(sock, F_SETFL, flags);
	assert(rc != -1);
	return new BSDSocket(sock);
}

uint32_t BSDSocketProvider::ResolveHost(const std::string& hostname)
{
	struct hostent* hostent = gethostbyname2(hostname.c_str(), AF_INET);
	if (hostent && hostent->h_addr)
	{
		uint32_t value = *(uint32_t*)hostent->h_addr;
		//fprintf(stderr, "%s = 0x%08X\n", hostname.c_str(), value);
		return value;
	}
	else
	{
		return 0;
	}
}

std::string BSDSocketProvider::ReverseLookup(uint32_t host)
{
	char buf[16];
	union
	{
		char octets[4];
		uint32_t val;
	} bitcast;
	bitcast.val = host;
	sprintf(buf, "%d.%d.%d.%d", bitcast.octets[0], bitcast.octets[1], bitcast.octets[2], bitcast.octets[3]);
	return std::string(buf);
}

}
