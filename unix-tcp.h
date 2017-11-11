#ifndef __UNIX_TCP_H__
#define __UNIX_TCP_H__
#include <string>
using namespace std;

class UnixTcp
{
protected:
	int sock;
	string m_path;
public:
	UnixTcp(void);
	UnixTcp(const string& path);
	~UnixTcp(void);
public:
	bool Open(void);
	bool Bind(const string& path);
	bool Unlink(const string& path);
	bool Connect(const string& path);
	int Recv(char *buf, int len);
	int SendTo(const string& path, const char *buf, int len);
	int RecvFrom(string& path, char *buf, int len);
	bool Block(void);
	bool Unblock(void);
	bool Close(void);
public:
	const string& GetPath(void)const{return m_path;}
};


#endif//__UNIX_TCP_H__
