#ifndef NETWORK_BASIC_DATAGRAM_SOCKET_HPP
#define NETWORK_BASIC_DATAGRAM_SOCKET_HPP

#include "basic_socket.hpp"
#include "buffer.hpp"

namespace network
{
	template<class Protocol>
	class basic_datagram_socket : public basic_socket<Protocol>
	{
	  public:
		using protocol_type = Protocol;
		using endpoint_type = typename protocol_type::endpoint;

		using basic_socket<protocol_type>::basic_socket;
		using basic_socket<protocol_type>::operator=;

		using basic_socket<protocol_type>::bind;

		size_t read(mutable_buffer buf, endpoint_type& addr) const
		{
			return basic_socket<protocol_type>::read(addr, buf.data(), buf.size(), 0);
		}

		size_t read(immutable_buffer buf, endpoint_type& addr) const
		{
			return basic_socket<protocol_type>::read(addr, buf.data(), buf.size(), 0);
		}

		void write(mutable_buffer buf, endpoint_type& addr) const
		{
			basic_socket<protocol_type>::write(addr, buf.data(), buf.size(), 0);
		}

		void write(immutable_buffer buf, endpoint_type& addr) const
		{
			basic_socket<protocol_type>::write(addr, buf.data(), buf.size(), 0);
		}
	};
} // namespace network

#endif // NETWORK_BASIC_DATAGRAM_SOCKET_HPP
