#include "core.h"
#include "tcp.h"
#include <string>

net::tcp::listener::listener(net::family fm_type, const char* ip, const char* port, int listens_count) : addr_info{ ip, port } {
	conn_sock = addr_info;
	sock_info = addr_info.get_sockinfo();
	
	conn_sock.bind(sock_info);
	conn_sock.listen(listens_count);
}
