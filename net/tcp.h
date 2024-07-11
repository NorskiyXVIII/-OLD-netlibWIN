#pragma once

#include "core.h"

namespace net {
	namespace tcp {
		class listener {
		private:
			net::socket   conn_sock;
			net::socket   listen_sock;

			net::addrinfo addr_info;
			net::sockinfo sock_info;
		public:
			listener(net::family fm_type, const char* ip, const char* port, int listens_count);
		};

		class sender {
		private:
			net::socket   conn_sock;
			net::sockinfo info;
		public:
			sender(const char* ip, const char* port);
		};
	}
}