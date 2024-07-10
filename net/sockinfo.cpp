#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "core.h"

net::sockinfo::sockinfo() {
	memset(&addr_in, 0, sizeof(addr_in));
}
net::sockinfo::sockinfo(sockaddr& sck_addr) {
	sockaddr_in* sck_in = (sockaddr_in*)&sck_addr;

	memset(&addr_in, 0, sizeof addr_in);
	addr_in.sin_addr.S_un.S_addr = sck_in->sin_addr.S_un.S_addr;
	addr_in.sin_family			 = sck_in->sin_family;
	addr_in.sin_port			 = sck_in->sin_port;
}
net::sockinfo::sockinfo(sockaddr_in& sck_in) {
	memset(&addr_in, 0, sizeof addr_in);
	addr_in.sin_addr.S_un.S_addr = sck_in.sin_addr.S_un.S_addr;
	addr_in.sin_family = sck_in.sin_family;
	addr_in.sin_port = sck_in.sin_port;
}
net::sockinfo::sockinfo(sockinfo* addr) {
	memset(&addr_in, 0, sizeof addr_in);
	addr_in.sin_family = addr->addr_in.sin_family;
	addr_in.sin_addr.S_un.S_addr = addr->addr_in.sin_addr.S_un.S_addr;
	addr_in.sin_port = addr->addr_in.sin_port;
}
net::sockinfo::sockinfo(sockaddr_in* addr) {
	memset(&addr_in, 0, sizeof addr_in);
	addr_in.sin_family = addr->sin_family;
	addr_in.sin_addr.S_un.S_addr = addr->sin_addr.S_un.S_addr;
	addr_in.sin_port = addr->sin_port;
}
net::sockinfo::sockinfo(sockaddr* saddr) {
	memset(&addr_in, 0, sizeof addr_in);
	sockaddr_in* addr = (sockaddr_in*)&saddr;

	addr_in.sin_family = addr->sin_family;
	addr_in.sin_addr.S_un.S_addr = addr->sin_addr.S_un.S_addr;
	addr_in.sin_port = addr->sin_port;
}
net::sockinfo::sockinfo(const char* ip_addr, ushort port) {
	memset(&addr_in, 0, sizeof(addr_in));
	addr_in.sin_family = AF_INET;
	addr_in.sin_addr.S_un.S_addr = inet_addr(ip_addr);
	addr_in.sin_port = htons(port);
}
net::sockinfo::sockinfo(int ip_ver, const char* ip_addr, ushort port) {
	memset(&addr_in, 0, sizeof(addr_in));
	if (ip_ver != AF_INET && ip_ver != AF_INET6) {
		printf("Error: ip_ver != AF_INET or AF_INET6");
		exit(1);
	}
	addr_in.sin_family = ip_ver; // AF_INET или AF_INET6
	addr_in.sin_addr.S_un.S_addr = inet_addr(ip_addr);
	addr_in.sin_port = htons(port);
}

net::sockinfo& net::sockinfo::operator=(sockinfo& addr) {
	this->addr_in.sin_family = addr.addr_in.sin_family;
	this->addr_in.sin_addr.S_un.S_addr = addr.addr_in.sin_addr.S_un.S_addr;
	this->addr_in.sin_port = addr.addr_in.sin_port;

	return *this;
}
net::sockinfo& net::sockinfo::operator=(sockaddr_in& addr) {
	addr_in.sin_family = addr.sin_family;
	addr_in.sin_addr.S_un.S_addr = addr.sin_addr.S_un.S_addr;
	addr_in.sin_port = addr.sin_port;

	return *this;
}
net::sockinfo& net::sockinfo::operator=(sockaddr& saddr) {
	sockaddr_in* addr = (sockaddr_in*)&saddr;

	addr_in.sin_family = addr->sin_family;
	addr_in.sin_addr.S_un.S_addr = addr->sin_addr.S_un.S_addr;
	addr_in.sin_port = addr->sin_port;

	return *this;
}

net::sockinfo& net::sockinfo::operator=(sockinfo* addr) {
	addr_in.sin_family = addr->addr_in.sin_family;
	addr_in.sin_addr.S_un.S_addr = addr->addr_in.sin_addr.S_un.S_addr;
	addr_in.sin_port = addr->addr_in.sin_port;

	return *this;
}
net::sockinfo& net::sockinfo::operator=(sockaddr_in* addr) {
	addr_in.sin_family = addr->sin_family;
	addr_in.sin_addr.S_un.S_addr = addr->sin_addr.S_un.S_addr;
	addr_in.sin_port = addr->sin_port;

	return *this;
}
net::sockinfo& net::sockinfo::operator=(sockaddr* saddr) {
	sockaddr_in* addr = (sockaddr_in*)&saddr;

	addr_in.sin_family = addr->sin_family;
	addr_in.sin_addr.S_un.S_addr = addr->sin_addr.S_un.S_addr;
	addr_in.sin_port = addr->sin_port;

	return *this;
}

bool net::sockinfo::operator==(sockinfo& addr) {
	bool family_equal = this->addr_in.sin_family == addr.addr_in.sin_family;
	bool addr_equal = this->addr_in.sin_addr.S_un.S_addr == addr.addr_in.sin_addr.S_un.S_addr;
	bool port_equal = this->addr_in.sin_port == addr.addr_in.sin_port;

	return family_equal && addr_equal && port_equal;
}
bool net::sockinfo::operator==(sockaddr_in& addr) {
	bool family_equal = this->addr_in.sin_family == addr.sin_family;
	bool addr_equal = this->addr_in.sin_addr.S_un.S_addr == addr.sin_addr.S_un.S_addr;
	bool port_equal = this->addr_in.sin_port == addr.sin_port;

	return family_equal && addr_equal && port_equal;
}
bool net::sockinfo::operator==(sockaddr& saddr) {
	sockaddr_in* addr = (sockaddr_in*)&saddr;

	bool family_equal = this->addr_in.sin_family == addr->sin_family;
	bool addr_equal = this->addr_in.sin_addr.S_un.S_addr == addr->sin_addr.S_un.S_addr;
	bool port_equal = this->addr_in.sin_port == addr->sin_port;

	return family_equal && addr_equal && port_equal;
}

int net::sockinfo::get_version() {
	return this->addr_in.sin_family;
}

net::ulong net::sockinfo::get_ip() {
	return this->addr_in.sin_addr.S_un.S_addr;
}
void net::sockinfo::set_ip(const char* ip) {
	this->addr_in.sin_addr.S_un.S_addr = inet_addr(ip);
}
void net::sockinfo::set_ip(sockaddr_in ip) {
	this->addr_in.sin_addr.S_un.S_addr = ip.sin_addr.S_un.S_addr;
}

net::ulong net::sockinfo::get_port() {
	return this->addr_in.sin_port;
}
void net::sockinfo::set_port(const ushort port) {
	this->addr_in.sin_port = port;
}

void net::sockinfo::set(const char* ip_addr, ushort port) {
	memset(&addr_in, 0, sizeof(addr_in));
	addr_in.sin_family = AF_INET;
	addr_in.sin_addr.S_un.S_addr = inet_addr(ip_addr);
	addr_in.sin_port = htons(port);
}
void net::sockinfo::set(int ip_ver, const char* ip_addr, ushort port) {
	memset(&addr_in, 0, sizeof(addr_in));
	if (ip_ver != AF_INET && ip_ver != AF_INET6) {
		printf("Error: ip_ver != AF_INET or AF_INET6");
		exit(1);
	}
	addr_in.sin_family = ip_ver; // AF_INET или AF_INET6
	addr_in.sin_addr.S_un.S_addr = inet_addr(ip_addr);
	addr_in.sin_port = htons(port);
}

sockaddr net::sockinfo::copy_sockaddr() {
	sockaddr* saddr = (sockaddr*)&addr_in;
	return *saddr;
}
sockaddr_in net::sockinfo::copy_sockaddrin() {
	return addr_in;
}

sockaddr* net::sockinfo::as_sockaddr() {
	return (sockaddr*)&addr_in;
}
sockaddr_in* net::sockinfo::as_sockaddrin() {
	return &addr_in;
}

size_t net::sockinfo::get_size() {
	return sizeof(addr_in);
}