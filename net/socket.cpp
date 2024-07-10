#include "core.h"


net::socket::socket() { this->sock = INVALID_SOCKET; }
net::socket::socket(SOCKET sock) : sock{ sock } {}
net::socket::socket(int ip_ver, int sock_type, int protocol) {
		if (sock != INVALID_SOCKET) closesocket(sock);
		sock = ::socket(ip_ver, sock_type, protocol);
}
net::socket::socket(int sock_type, int protocol) {
		if (sock != INVALID_SOCKET) closesocket(sock);
		sock = ::socket(AF_INET, sock_type, protocol);
}

net::socket::socket(const char* ip, ushort port, int sock_type, int protocol) {
		net::sockinfo addr_in{ ip, port };

		sock = ::socket(AF_INET, sock_type, protocol);
		bind(addr_in);
	}
net::socket::socket(int family, const char* ip, ushort port, int sock_type, int protocol) {
		sockinfo addr_in{ family, ip, port };

		sock = ::socket(family, sock_type, protocol);
		bind(addr_in);
}

net::socket::~socket() { closesocket(sock); }

void net::socket::make_server() {
		if (sock_tp == SOCK_LSTN) return;
		sock_tp = SOCK_LSTN;
	}
void net::socket::make_client() {
		if (sock_tp == SOCK_CLNT) return;
		sock_tp = SOCK_CLNT;
	}
SOCKET net::socket::get_socket() {
		return sock;
}

void net::socket::bind(sockinfo& sock_in, int size) {
		if (sock_tp != SOCK_LSTN) return;
		::bind(sock, sock_in.as_sockaddr(), size);
}
void net::socket::bind(sockaddr_in& sock_in, int size) {
		if (sock_tp != SOCK_LSTN) return;
		::bind(sock, (sockaddr*)&sock_in, size);
}
void net::socket::bind(sockaddr& sock_in, int size) {
		if (sock_tp != SOCK_LSTN) return;
		::bind(sock, &sock_in, size);
}

void net::socket::listen(int count_conns) {
		if (sock_tp != SOCK_LSTN) return;
		::listen(sock, count_conns);
}

SOCKET net::socket::accept(sockinfo& sock_in, int& size) {
		if (sock_tp != SOCK_LSTN) return INVALID_SOCKET;
		SOCKET conn = ::accept(sock, sock_in.as_sockaddr(), &size);

		return conn;
}

net::status net::socket::connect(sockinfo& sock_in, int size) {
		if (sock_tp != SOCK_CLNT) return sock_is_not_client;

		 net::status st = ::connect(sock, sock_in.as_sockaddr(), size);

		 return st;
}
net::status net::socket::connect(sockaddr_in& sock_in, int size) {
		if (sock_tp != SOCK_CLNT) return sock_is_not_client;

		net::status st = ::connect(sock, (sockaddr*)&sock_in, size);

		return st;
}
net::status net::socket::connect(sockaddr& sock_in, int size) {
		if (sock_tp != SOCK_CLNT) return sock_is_not_client;

		net::status st = ::connect(sock, &sock_in, size);

		return st;
}

net::status net::socket::connect(net::addrinfo& addrinf) {
	if (sock_tp != SOCK_CLNT) return sock_is_not_client;
	sockaddr* sock_addr = addrinf.get_sockaddr();

	while (1) {
		if (::connect(sock, sock_addr, sizeof(sockaddr)) != SOCKET_ERROR) break;
		else {
			printf("trying connect to server...\n");

			sock_addr = addrinf.get_next();
			if (addrinf.as_addrinfo() == NULL) {
				printf("Failed connect to server!\n");
			}
		}
	}

	return net::success;
}

net::status net::socket::connect(::addrinfo* addrinf) {
	if (sock_tp != SOCK_CLNT) return sock_is_not_client;

	sockaddr* sock_addr = addrinf->ai_addr;

	while (1) {
		if (!::connect(sock, sock_addr, sizeof(sockaddr))) break;
		addrinf = addrinf->ai_next;
		printf("Attempting connect to server...\n");
		if (addrinf == NULL) {
			return net::cannot_connect;
		}

		sock_addr = addrinf->ai_addr;
	}

	return net::success;
}

void net::socket::recv(byte* buf, size_t len, int params) {
		::recv(sock, buf, len, params);
}
void net::socket::send(byte* buf, size_t len, int params) {
		::send(sock, buf, len, params);
}

void net::socket::close() {
		closesocket(sock);
}

