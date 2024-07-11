#include "core.h"
#include <string>

net::addrinfo::addrinfo(const char* ip, const char* port) {
	getaddrinfo(ip, port, &adr, &res);
}

net::addrinfo::addrinfo(const std::string& ip, const std::string& port) {
	getaddrinfo(ip.c_str(), port.c_str(), &adr, &res);
}

::addrinfo* net::addrinfo::as_addrinfo() {
	return res;
}

sockaddr* net::addrinfo::get_sockaddr() {
	return res->ai_addr;
}

net::sockinfo* net::addrinfo::get_sockinfo() {
	net::sockinfo ret;

	ret = res->ai_addr;

	return &ret;
}

::sockaddr* net::addrinfo::get_next() {
	res = res->ai_next;

	return res->ai_addr;
}

net::addrinfo::~addrinfo() {
	freeaddrinfo(res);
}

void net::addrinfo::set(const char* ip, const char* port) {
	if (res != NULL) freeaddrinfo(res);
	getaddrinfo(ip, port, &adr, &res);
}