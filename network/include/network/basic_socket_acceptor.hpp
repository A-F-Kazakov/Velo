#ifndef NETWORK_ACCEPTOR_HPP
#define NETWORK_ACCEPTOR_HPP

#include "socket_options.hpp"

namespace network
{
	template<typename Protocol>
	class basic_socket_acceptor
	{
	  public:
		using protocol_type = Protocol;
		using endpoint_type = typename protocol_type::endpoint;

		explicit basic_socket_acceptor(const protocol_type& protocol) : listener(protocol) {}
		explicit basic_socket_acceptor(const endpoint_type& endpoint, bool reuse_address = true) : listener(endpoint)
		{
			if(reuse_address)
				listener.reuse_address(enable);

			listen();
		}

		basic_socket_acceptor(const basic_socket_acceptor&)	  = delete;
		basic_socket_acceptor(basic_socket_acceptor&&) noexcept = default;

		~basic_socket_acceptor() noexcept = default;

		basic_socket_acceptor& operator=(const basic_socket_acceptor&) = delete;
		basic_socket_acceptor& operator=(basic_socket_acceptor&&) noexcept = default;

		void open(const protocol_type& protocol = protocol_type()) { listener.open(protocol); }

		bool is_open() const { return listener.is_open(); }

		void bind(const endpoint_type& endpoint) { listener.bind(endpoint); }

		void listen(int backlog = native::max_listen_connections) { listener.listen(backlog); }

		void close() { listener.close(); }

		template<typename SocketOption, typename SocketOptionValue>
		void option(const SocketOption& option, SocketOptionValue value)
		{
			listener.option(option, value);
		}

		endpoint_type local_endpoint() const { return listener.local_endpoint(); }

		void accept(typename protocol_type::socket& peer) { listener.accept(peer); }

		void accept(typename protocol_type::socket& peer, endpoint_type& peer_endpoint) { listener.accept(peer, peer_endpoint); }

		typename Protocol::socket accept() { return listener.accept(); }

	  private:
		typename protocol_type::socket listener;
	};
} // namespace network

#endif // NETWORK_ACCEPTOR_HPP
