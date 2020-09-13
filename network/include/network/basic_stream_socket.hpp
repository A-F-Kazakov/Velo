#ifndef NETWORK_BASIC_STREAM_SOCKET_HPP
#define NETWORK_BASIC_STREAM_SOCKET_HPP

#include "basic_socket.hpp"
#include "buffer.hpp"

namespace network
{
	template<class Protocol>
	class basic_stream_socket : public basic_socket<Protocol>
	{
	  public:
		using protocol_type = Protocol;
		using endpoint_type = typename protocol_type::endpoint;

		using basic_socket<protocol_type>::basic_socket;
		using basic_socket<protocol_type>::operator=;

		using basic_socket<protocol_type>::connect;
		using basic_socket<protocol_type>::shutdown;
		using basic_socket<protocol_type>::remote_endpoint;

		using basic_socket<protocol_type>::listen;

		basic_stream_socket<protocol_type> accept() const
		{
			basic_stream_socket<protocol_type> sock;
			accept(sock);
			return sock;
		}

		void accept(basic_stream_socket<protocol_type>& socket) const
		{
			auto descriptor = basic_socket<protocol_type>::accept_fd(nullptr, nullptr);

			if(descriptor == -1)
				throw error::socket(native::error_code(), std::system_category(), __FUNCTION__);

			socket = descriptor;
		}

		void accept(basic_stream_socket<protocol_type>& socket, endpoint_type& peer_endpoint) const
		{
			socklen_t len	= peer_endpoint.size();
			int descriptor = basic_socket<protocol_type>::accept_fd(peer_endpoint.data(), &len);

			if(descriptor == -1)
				throw error::socket(native::error_code(), std::system_category(), __FUNCTION__);

			socket = std::move(basic_stream_socket<protocol_type>(descriptor));
		}

		size_t read(mutable_buffer buf) const { return basic_socket<protocol_type>::read(buf.data(), buf.size(), 0); }

		void write(mutable_buffer buf) const { return write(immutable_buffer(buf.data(), buf.size())); }

		void write(immutable_buffer buf) const
		{
			size_t out = 0;

			while(out < buf.size())
				out += basic_socket<protocol_type>::write((buf.data() + out), buf.size() - out, 0);
		}
	};
} // namespace network

#endif // NETWORK_BASIC_STREAM_SOCKET_HPP
