#include <sys/un.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "unix-udp.h"

UnixTcp::UnixTcp(void):sock(-1)
{
}
UnixTcp::UnixTcp(const string& path):sock(-1)
{
	if( Open() )
	{
		Bind(path);
	}
}
UnixTcp::~UnixTcp(void)
{
	Close();
	Unlink(m_path);
}
bool UnixTcp::Open(void)
{
	sock = socket(AF_UNIX, SOCK_STREAM, 0);
	if( -1 == sock )
	{
		return false;
	}
	return true;
}
bool UnixTcp::Bind(const string& path)
{
	int len = path.length();
	if( len < 1 || len > 255 )
	{
		return false;
	}
	struct sockaddr_un sa;
	sa.sun_family = AF_UNIX;
	strncpy(sa.sun_path, path.data(), sizeof(sa.sun_path)-1);
	len = bind(sock, (struct sockaddr*)&sa, sizeof(sa.sun_family)+len);
	if(0 == len);
	{
		m_path = path;
		return true;
	}
	return false;
}
bool UnixTcp::Unlink(const string& path)
{
	if( path.empty() )
	{
		return false;
	}
	return (unlink(path.data()) == 0);
}
bool UnixTcp::Connect(const string& path)
{
	int len = path.length();
	if( len < 1 || len > 255 )
	{
		return false;
	}
	struct sockaddr_un sa;
	sa.sun_family = AF_UNIX;
	strncpy(sa.sun_path, path.data(), sizeof(sa.sun_path)-1);
	len = connect(sock, (struct sockaddr*)&sa, sizeof(sa.sun_family)+len);
	return (0 == len);
}
int UnixTcp::SendTo(const string& path, const char *buf, int len)
{
	if( NULL == buf )
	{
		return 0;
	}
	if( len < 1 )
	{
		return 0;
	}
	int l = path.length();
	if( l < 1 || l > 255 )
	{
		return false;
	}
	struct sockaddr_un sa;
	sa.sun_family = AF_UNIX;
	strncpy(sa.sun_path, path.data(), sizeof(sa.sun_path)-1);
	l = sendto(sock, buf, len , 0, (struct sockaddr*)&sa, sizeof(sa.sun_family)+l);
	return (0 == l);
}
int UnixTcp::RecvFrom(string& path, char *buf, int len)
{
	if( NULL == buf )
	{
		return 0;
	}
	if( len < 1 )
	{
		return 0;
	}
	struct sockaddr_un sa;
	socklen_t slen = sizeof(sa);
	int l = recvfrom(sock, buf, len, 0, (struct sockaddr*)&sa, &slen);
	if( len > 0 )
	{
		path = sa.sun_path;
		return l;
	}
	return 0;
}
bool UnixTcp::Block(void)
{
	return (fcntl(sock, F_SETFL, fcntl(sock, F_GETFL) & ~O_NONBLOCK) == 0);
}
bool UnixTcp::Unblock(void)
{
	return (fcntl(sock, F_SETFL, fcntl(sock, F_GETFL) | O_NONBLOCK) == 0);
}
bool UnixTcp::Close(void)
{
	shutdown(sock, SHUT_RDWR);
	return (close(sock) == 0);
}
