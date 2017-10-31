ARCH := /usr/bin/
CC := $(ARCH)gcc
CFLAG := -Iinclude
INET:= inet/libinetsocket.c
UNIX:= unix/libunixsocket.c
TARGETS:= tcpserver.exe tcpclient.exe
TARGETS+= udpserver.exe udpclient.exe
TARGETS+= unix_dgram_client.exe unix_dgram_server.exe
TARGETS+= unix_stream_client.exe unix_stream_server.exe


targets: $(TARGETS)
	@ls -lh $+

tcpserver.exe: $(INET)
	$(CC) $(CFLAG) $+ examples/tcpserver.c -o $@

tcpclient.exe: $(INET)
	$(CC) $(CFLAG) $+ examples/tcpclient.c -o $@

udpserver.exe: $(INET)
	$(CC) $(CFLAG) $+ examples/udpserver.c -o $@

udpclient.exe: $(INET)
	$(CC) $(CFLAG) $+ examples/udpclient.c -o $@

unix_dgram_server.exe: $(UNIX)
	$(CC) $(CFLAG) $+ examples/unix_dgram_server.c -o $@

unix_dgram_client.exe: $(UNIX)
	$(CC) $(CFLAG) $+ examples/unix_dgram_client.c -o $@

unix_stream_server.exe: $(UNIX)
	$(CC) $(CFLAG) $+ examples/unix_stream_server.c -o $@

unix_stream_client.exe: $(UNIX)
	$(CC) $(CFLAG) $+ examples/unix_stream_client.c -o $@


clean:
	@rm -vrf *.o *.exe
