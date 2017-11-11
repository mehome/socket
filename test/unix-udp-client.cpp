#include <stdio.h>
#include <unistd.h>
#include "unix-udp.h"

int main(int argc, char **argv)
{
	UnixUdp unixudp;
	string client_path = "unixudp.udp.clien.socket";
	string server_path = "unixudp.udp.server.socket";

	unixudp.Open();
	if( unixudp.Connect(client_path) )
	{
		return 0;
	}
	else
	{
		unixudp.Unlink(client_path);
	}
	if( unixudp.Bind(client_path) )
	{
		printf("bind(%s) ok\n", client_path.data());
	}
	else
	{
		printf("bind(%s) failed\n", client_path.data());
	}
	unixudp.Unblock();
	while(1)
	{
		usleep(1);
		char buf[32] = {0};
		static int i = 0;
		snprintf(buf, sizeof(buf), "data from client[ %d ]", i++);
		client_path = buf;
		if( unixudp.SendTo(server_path, client_path.data(), client_path.length()) > 0 )
		{
			printf("sendto(%s, %s, %d)\n", 
						server_path.data(), 
						client_path.data(), 
						client_path.length());
		}
	}
	return 0;
}
