#include <stdio.h>
#include <unistd.h>
#include "unix-udp.h"

int main(int argc, char **argv)
{
	UnixUdp unixudp;
	char buf[32] = {0};
	string path = "unix-udp.connect";
	string server = "unixudp.udp.server.socket";

	unixudp.Open();
	if( unixudp.Connect(server) )
	{
		printf("connect ok\n");
	}
	while(1)
	{
		usleep(1);
		char buf[32] = {0};
		static int i = 0;
		snprintf(buf, sizeof(buf), "data from connect[%d]", i++);
		path = buf;
		if( unixudp.Send(path.data(), path.length()) > 0 )
		{
			printf("sendto(%s, %s, %d)\n", server.data(), path.data(), path.length());
		}
	}
	return 0;
}
