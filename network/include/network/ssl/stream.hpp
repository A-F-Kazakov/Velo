#ifndef NETWORK_SSL_HPP
#define NETWORK_SSL_HPP

#include "context.hpp"
#include "network/ip/tcp.hpp"

namespace network::ssl
{
	template<typename Protocol>
	class stream : protected basic_stream_socket<Protocol>
	{
	  public:
		using native_handle_type = SSL;
		using protocol_type		 = Protocol;
		using endpoint_type		 = typename protocol_type::endpoint;

		using basic_stream_socket<protocol_type>::basic_socket;
		using basic_stream_socket<protocol_type>::operator=;

		using basic_stream_socket<protocol_type>::connect;
		using basic_stream_socket<protocol_type>::shutdown;
		using basic_stream_socket<protocol_type>::remote_endpoint;

		explicit stream(const context& ctx) : stream(ctx, basic_stream_socket<protocol_type>(protocol_type::v4())) {}

		stream(const context& ctx, typename protocol_type::socket&& sock) :
			basic_stream_socket<protocol_type>(std::move(sock)), ssl(::SSL_new(ctx.native_handler()))
		{
			if(!::SSL_set_fd(ssl, basic_stream_socket<Protocol>::get_descriptor()))
				throw std::runtime_error(native::get_last_error());
		}

		stream(const stream&)	  = delete;
		stream(stream&&) noexcept = default;

		~stream() noexcept
		{
			::SSL_shutdown(ssl);
			::SSL_free(ssl);
		}

		stream& operator=(const stream&) = delete;
		stream& operator=(stream&& mv) noexcept = default;

		void handshake(context::handshake_type type)
		{
			int out = -1;
			if(type == context::server)
				out = ::SSL_accept(ssl);
			else if(type == context::client)
				out = ::SSL_connect(ssl);

			if(out <= 0)
				throw std::runtime_error(native::get_last_error());
		}

		size_t read(mutable_buffer buf) const
		{
			int out = ::SSL_read(ssl, buf.data(), static_cast<int>(buf.size()));

			if(out <= 0)
				throw std::runtime_error(native::get_last_error());

			return static_cast<size_t>(out);
		}

		size_t write(mutable_buffer buf) const { return write(immutable_buffer(buf.data(), buf.size())); }

		size_t write(immutable_buffer buf) const
		{
			int out = ::SSL_write(ssl, buf.data(), static_cast<int>(buf.size()));

			if(out <= 0)
				throw std::runtime_error(native::get_last_error());

			return static_cast<size_t>(out);
		}

	  private:
		native_handle_type* ssl;
	};
} // namespace network::ssl

#endif // NETWORK_SSL_HPP
