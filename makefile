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

tcpserver.exe: $(INET) examples/tcpserver.c 
	$(CC) $(CFLAG) $+ -o $@

tcpclient.exe: $(INET) examples/tcpclient.c
	$(CC) $(CFLAG) $+ -o $@

udpserver.exe: $(INET) examples/udpserver.c
	$(CC) $(CFLAG) $+ -o $@

udpclient.exe: $(INET) examples/udpclient.c
	$(CC) $(CFLAG) $+ -o $@

unix_dgram_server.exe: $(UNIX) examples/unix_dgram_server.c
	$(CC) $(CFLAG) $+ -o $@

unix_dgram_client.exe: $(UNIX) examples/unix_dgram_client.c
	$(CC) $(CFLAG) $+ -o $@

unix_stream_server.exe: $(UNIX) examples/unix_stream_server.c
	$(CC) $(CFLAG) $+ -o $@

unix_stream_client.exe: $(UNIX) examples/unix_stream_client.c
	$(CC) $(CFLAG) $+ -o $@


clean:
	@rm -vrf *.o *.exe
