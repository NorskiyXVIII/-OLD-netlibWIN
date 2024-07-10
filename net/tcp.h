#pragma once

#include "core.h"

namespace net {
	namespace tcp {
		class listener {
		private:
			net::socket   conn_sock;
			net::socket   listen_sock;
			net::sockinfo info;
		public:
			listener(char* ip, char* port);
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