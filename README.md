It works 100% on Windows computers, I don't know about linux, but you can check

examples:
```C++
// server.cpp
#include <stdio.h>
#include <winsock2.h>

#include "net/core.h"

#define PORT 8392

void print_client(struct sockaddr_in* client) {
	printf("TCP USER CONNECTED\n");
	printf("----------------USER INFO----------------\n");
	printf("IP: %d.%d.%d.%d\n", client->sin_addr.S_un.S_un_b.s_b1, client->sin_addr.S_un.S_un_b.s_b2, client->sin_addr.S_un.S_un_b.s_b3, client->sin_addr.S_un.S_un_b.s_b4);
	printf("PORT: %d\n", ntohs(client->sin_port));
	printf("----------------USER INFO----------------\n\n");
}

int main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2), &wsa);
	
	net::socket sock_conn{AF_INET, "127.0.0.1", PORT};
	printf("server started!\n");
	sock_conn.listen(SOMAXCONN);
	
	net::sockinfo client_sock;
	net::socksize client_sock_size = client_sock.get_size();

	net::socket client_conn = sock_conn.accept(client_sock, client_sock_size);	
	print_client(client_sock.as_sockaddrin());
	
	char msg[100];
	client_conn.recv(msg, 100);
	printf("Recieved msg: %s\n", msg);
	
	WSACleanup();
	return 0;
}
```
and
```C++
// client.cpp
#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#include "net.hpp"

int main() {
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	
	net::sockinfo server_addr{AF_INET, "127.0.0.1", 8392};
	
	net::socket conn_sock{AF_INET, SOCK_STREAM, IPPROTO_TCP};
	conn_sock.make_client();
	conn_sock.connect(server_addr);
	
	
	char msg[100];
	printf("send msg to server: ");
	scanf("%[^\n]", msg);
	conn_sock.send(msg, strlen(msg) + 1);
	
	WSACleanup();
	return 0;
}
```
