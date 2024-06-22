#pragma once

namespace net {
    using ushort   = unsigned short; // псевдоним
    using ulong    = unsigned long;
	using uchar    = unsigned char;
	using socksize = int;
	using byte     = char;
    class sockinfo {
    private:
        sockaddr_in addr_in;
    public:
		sockinfo() {
			memset(&addr_in, 0, sizeof(addr_in));
		}
		sockinfo(const char* ip_addr, ushort port) {
			memset(&addr_in, 0, sizeof(addr_in));
			addr_in.sin_family = AF_INET;
			addr_in.sin_addr.S_un.S_addr = inet_addr(ip_addr);
			addr_in.sin_port = htons(port);
		}
		sockinfo(int ip_ver, const char* ip_addr, ushort port) {
			memset(&addr_in, 0, sizeof(addr_in));
			if (ip_ver != AF_INET && ip_ver != AF_INET6) {
				printf("Error: ip_ver != AF_INET or AF_INET6");
				exit(1);
			}
			addr_in.sin_family = ip_ver; // AF_INET или AF_INET6
			addr_in.sin_addr.S_un.S_addr = inet_addr(ip_addr);
			addr_in.sin_port = htons(port);
		}

		sockinfo& operator=(sockinfo& addr) {
			this->addr_in.sin_family             = addr.addr_in.sin_family;
			this->addr_in.sin_addr.S_un.S_addr   = addr.addr_in.sin_addr.S_un.S_addr;
			this->addr_in.sin_port               = addr.addr_in.sin_port;

			return *this;
		}	
		sockinfo& operator=(sockaddr_in& addr) {
			addr_in.sin_family 			   = addr.sin_family;
			addr_in.sin_addr.S_un.S_addr   = addr.sin_addr.S_un.S_addr;
			addr_in.sin_port		       = addr.sin_port;

			return *this;
		}
		sockinfo& operator=(sockaddr& saddr) {
			sockaddr_in* addr = (sockaddr_in*)&saddr;

			addr_in.sin_family			   = addr->sin_family;
			addr_in.sin_addr.S_un.S_addr   = addr->sin_addr.S_un.S_addr;
			addr_in.sin_port  			   = addr->sin_port;

			return *this;
		}
	
		bool operator==(sockinfo& addr) {
			bool family_equal = this->addr_in.sin_family  			 == addr.addr_in.sin_family;
			bool addr_equal   = this->addr_in.sin_addr.S_un.S_addr   == addr.addr_in.sin_addr.S_un.S_addr;
			bool port_equal   = this->addr_in.sin_port 			     == addr.addr_in.sin_port;

			return family_equal && addr_equal && port_equal;
		}	
		bool operator==(sockaddr_in& addr) {
			bool family_equal = this->addr_in.sin_family  			 == addr.sin_family;
			bool addr_equal   = this->addr_in.sin_addr.S_un.S_addr   == addr.sin_addr.S_un.S_addr;
			bool port_equal   = this->addr_in.sin_port			     == addr.sin_port;

			return family_equal && addr_equal && port_equal;
		}
		bool operator==(sockaddr& saddr) {
			sockaddr_in* addr = (sockaddr_in*)&saddr;
		
			bool family_equal = this->addr_in.sin_family   			 == addr->sin_family;
			bool addr_equal   = this->addr_in.sin_addr.S_un.S_addr   == addr->sin_addr.S_un.S_addr;
			bool port_equal   = this->addr_in.sin_port 			     == addr->sin_port;

			return family_equal && addr_equal && port_equal;
		}
	
		int get_version() {
			return this->addr_in.sin_family;
		}
		void set_version(int ip_version) { // Зачем нужен этот метод? Не знаю
			this->addr_in.sin_family = ip_version;
		}

		ulong get_ip() {
			return this->addr_in.sin_addr.S_un.S_addr;
		}
		void set_ip(const char* ip) {
			this->addr_in.sin_addr.S_un.S_addr = inet_addr(ip);
		}
		void set_ip(sockaddr_in ip) {
			this->addr_in.sin_addr.S_un.S_addr = ip.sin_addr.S_un.S_addr;
		}
        
		ulong get_port() {
			return this->addr_in.sin_port;
		}
		void set_port(const ushort port) {
			this->addr_in.sin_port = port;
		}
        
		void set(const char* ip_addr, ushort port) {
			memset(&addr_in, 0, sizeof(addr_in));
			addr_in.sin_family = AF_INET;
			addr_in.sin_addr.S_un.S_addr = inet_addr(ip_addr);
			addr_in.sin_port = htons(port);
		}
		void set(int ip_ver, const char* ip_addr, ushort port) {
			memset(&addr_in, 0, sizeof(addr_in));
			if (ip_ver != AF_INET && ip_ver != AF_INET6) {
				printf("Error: ip_ver != AF_INET or AF_INET6");
				exit(1);
			}
			addr_in.sin_family = ip_ver; // AF_INET или AF_INET6
			addr_in.sin_addr.S_un.S_addr = inet_addr(ip_addr);
			addr_in.sin_port = htons(port);
		}

		sockaddr copy_sockaddr() {
			sockaddr* saddr = (sockaddr*)&addr_in;
			return *saddr;
		}
		sockaddr_in copy_sockaddrin() {
			return addr_in;
		}
    
		sockaddr* as_sockaddr() {
			return (sockaddr*)&addr_in;
		}    
		sockaddr_in* as_sockaddrin() {
			return &addr_in;
		}
        
		size_t get_size() {
			return sizeof(addr_in);
		}
	};
	
	class socket {
	private:
	enum sock_type {SOCK_LSTN, SOCK_CLNT};
		SOCKET sock      = INVALID_SOCKET;
		sock_type sock_tp = SOCK_LSTN;
	public:
		socket() { sock = INVALID_SOCKET; }
		
		socket(SOCKET sock) : sock{sock} {}
		
		socket(int ip_ver, int sock_type, int protocol) {
			if (sock != INVALID_SOCKET) closesocket(sock);
			sock = ::socket(ip_ver, sock_type, protocol);
		}
		socket(int sock_type, int protocol) {
			if (sock != INVALID_SOCKET) closesocket(sock);
			sock = ::socket(AF_INET, sock_type, protocol);
		}
		
		socket(const char* ip, ushort port, int sock_type = SOCK_STREAM, int protocol = IPPROTO_TCP) {
			sockinfo addr_in{ip, port};
			
			sock = ::socket(AF_INET, sock_type, protocol);
			bind(addr_in);
		}
		socket(int family, const char* ip, ushort port, int sock_type = SOCK_STREAM, int protocol = IPPROTO_TCP) {
			sockinfo addr_in{family, ip, port};
			
			sock = ::socket(family, sock_type, protocol);
			bind(addr_in);
		}
		
		~socket() { closesocket(sock); }
		
		void make_server() {
			if (sock_tp == SOCK_LSTN) return;
			sock_tp = SOCK_LSTN;
		}
		void make_client() {
			if (sock_tp == SOCK_CLNT) return; 
			sock_tp = SOCK_CLNT;
		}
		SOCKET get_socket() {
			return sock;
		}
		
		void bind(sockinfo& sock_in, int size = sizeof(sockaddr)) {
			if (sock_tp != SOCK_LSTN) return;
			::bind(sock, sock_in.as_sockaddr(), size);
		}
		void bind(sockaddr_in& sock_in, int size = sizeof(sockaddr)) {
			if (sock_tp != SOCK_LSTN) return;
			::bind(sock, (sockaddr*)&sock_in, size);
		}
		void bind(sockaddr& sock_in, int size = sizeof(sockaddr)) {
			if (sock_tp != SOCK_LSTN) return;
			::bind(sock, &sock_in, size);
		}
		
		void listen(int count_conns) {
			if (sock_tp != SOCK_LSTN) return;
			::listen(sock, count_conns);
		}
		
		SOCKET accept(sockinfo& sock_in, int& size) {
			if (sock_tp != SOCK_LSTN) return INVALID_SOCKET;
			SOCKET conn = ::accept(sock, sock_in.as_sockaddr(), &size);
			
			return conn;
		}
		
		void connect(sockinfo& sock_in, int size = sizeof(sockaddr)) {
			if (sock_tp != SOCK_CLNT) return;
			
			::connect(sock, sock_in.as_sockaddr(), size);
		}
		void connect(sockaddr_in& sock_in, int size = sizeof(sockaddr)) {
			if (sock_tp != SOCK_CLNT) return;
			
			::connect(sock, (sockaddr*)&sock_in, size);
		}
		void connect(sockaddr& sock_in, int size = sizeof(sockaddr)) {
			if (sock_tp != SOCK_CLNT) return;
			
			::connect(sock, &sock_in, size);
		}
		
		void recv(byte* buf, size_t len, int params = 0) {
			::recv(sock, buf, len, params);
		}
		void send(byte* buf, size_t len, int params = 0) {
			::send(sock, buf, len, params);
		}
		
		void close() {
			closesocket(sock);
		}
	};
}
