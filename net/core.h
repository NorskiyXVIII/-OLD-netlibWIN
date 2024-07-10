#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <string>

namespace net {
	using ushort = unsigned short; // псевдоним
	using ulong = unsigned long;
	using uchar = unsigned char;
	using socksize = int;
	using byte = char;
	using status = int;

	constexpr status sock_is_not_server = 101;
	constexpr status sock_is_not_client = 100;


	constexpr status success = 1;
	constexpr status cannot_connect = 0;

	class sockinfo {
	private:
		sockaddr_in addr_in;
	public:
		sockinfo();
		sockinfo(sockaddr& sck_addr);
		sockinfo(sockaddr_in& sck_in);
		sockinfo(sockinfo* addr);
		sockinfo(sockaddr_in* addr);
		sockinfo(sockaddr* saddr);
		sockinfo(const char* ip_addr, ushort port);
		sockinfo(int ip_ver, const char* ip_addr, ushort port);

		sockinfo& operator=(sockinfo& addr);
		sockinfo& operator=(sockaddr_in& addr);
		sockinfo& operator=(sockaddr& saddr);

		sockinfo& operator=(sockinfo* addr);
		sockinfo& operator=(sockaddr_in* addr);
		sockinfo& operator=(sockaddr* saddr);


		bool operator==(sockinfo& addr);
		bool operator==(sockaddr_in& addr);
		bool operator==(sockaddr& saddr);

		int get_version();

		ulong get_ip();
		void set_ip(const char* ip);
		void set_ip(sockaddr_in ip);

		ulong get_port();
		void set_port(const ushort port);

		void set(const char* ip_addr, ushort port);
		void set(int ip_ver, const char* ip_addr, ushort port);

		sockaddr copy_sockaddr();
		sockaddr_in copy_sockaddrin();

		sockaddr* as_sockaddr();
		sockaddr_in* as_sockaddrin();

		size_t get_size();
	};
	class addrinfo {
	private:
		::addrinfo  adr;
		::addrinfo* res;
	public:
		addrinfo(const char* ip, const char* port);
		addrinfo(const std::string& ip, const std::string& port);

		::addrinfo* as_addrinfo();
		sockaddr* get_sockaddr();
		sockinfo* get_sockinfo();
		
		sockaddr* get_next();
		
		void set(const char* ip, const char* port);

		~addrinfo();
	};
	class socket {
	private:
		enum sock_type { SOCK_LSTN, SOCK_CLNT };
		SOCKET sock = INVALID_SOCKET;
		sock_type sock_tp = SOCK_LSTN;
	public:
		socket();

		socket(SOCKET sock);

		socket(int ip_ver, int sock_type, int protocol);
		socket(int sock_type, int protocol);

		socket(const char* ip, ushort port, int sock_type = SOCK_STREAM, int protocol = IPPROTO_TCP);
		socket(int family, const char* ip, ushort port, int sock_type = SOCK_STREAM, int protocol = IPPROTO_TCP);

		~socket();

		void make_server();
		void make_client();
		SOCKET get_socket();

		void bind(sockinfo& sock_in, int size = sizeof(sockaddr));
		void bind(sockaddr_in& sock_in, int size = sizeof(sockaddr));
		void bind(sockaddr& sock_in, int size = sizeof(sockaddr));

		void listen(int count_conns);

		SOCKET accept(sockinfo& sock_in, int& size);

		status connect(sockinfo& sock_in, int size = sizeof(sockaddr));
		status connect(sockaddr_in& sock_in, int size = sizeof(sockaddr));
		status connect(sockaddr& sock_in, int size = sizeof(sockaddr));
		status connect(addrinfo& addrinf);
		status connect(::addrinfo* addrinf);

		void recv(byte* buf, size_t len, int params = 0);
		void send(byte* buf, size_t len, int params = 0);

		void close();
	};
}