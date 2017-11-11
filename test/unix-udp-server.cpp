#include <stdio.h>
#include <unistd.h>
#include "unix-udp.h"

int main(void)
{
	string path;
	UnixUdp unixudp;
	string server_path = "unixudp.udp.server.socket";

	unixudp.Open();
	if( unixudp.Connect(server_path) )
	{
		return 0;
	}
	unixudp.Unlink(server_path);
	if( unixudp.Bind(server_path) )
	{
		printf("bind(%s) ok\n", server_path.data());
	}
	unixudp.Unblock();
	while(1)
	{
		char buf[32] = {0};
		static int i = 0;i++;
		int len = unixudp.RecvFrom(path, buf, sizeof(buf));
		if( len > 0 )
		{
			printf("[%d]buf.recvfrom(%s):%s\n", i, path.data(), buf);
		}
		path.clear();
		usleep(1);
	}
	return 0;
}
