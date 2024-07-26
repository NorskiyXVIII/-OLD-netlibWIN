#pragma once
#include <WinSock2.h>

namespace net {
	namespace win {
		struct nt_tuple {
			int v1 = 2, v2 = 2;
		};
		constexpr nt_tuple last_version{2, 2};


		class Wsa {
		private:
			::WSADATA wsa;
		public:
			Wsa(int v1 = 2, int v2 = 2) {
				WSAStartup(MAKEWORD(v1, v2), &wsa);
			}
			Wsa(const nt_tuple& ver) {
				WSAStartup(MAKEWORD(ver.v1, ver.v2), &wsa);
			}
			~Wsa() {
				WSACleanup();
			}
		};

		using data = Wsa;
	}

	namespace NT = net::win;
}


using NTDATA = net::NT::Wsa;
