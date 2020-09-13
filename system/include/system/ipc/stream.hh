/**
 * @author   Казаков Андрей 
 * @date     28.07.19.
 */

#ifndef SYSTEM_STREAM_HH
#define SYSTEM_STREAM_HH

#include "basic_endpoint.h"

namespace system::ipc
{
	class stream_protocol
	{
		public:
			using endpoint = basic_endpoint<stream_protocol>;
			using socket = basic_stream_socket<stream_protocol>;
			using acceptor = basic_socket_acceptor<stream_protocol>;
			using iostream = basic_socket_iostream<stream_protocol>;

			int type() const { return SOCK_STREAM; }
			int protocol() const { return 0; }
			int family() const { return AF_UNIX; }
	};
}

#endif //SYSTEM_STREAM_HH
