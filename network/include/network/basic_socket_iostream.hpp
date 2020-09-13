#ifndef NETWORK_BASIC_SOCKET_IOSTREAM_HPP
#define NETWORK_BASIC_SOCKET_IOSTREAM_HPP

#include "basic_socket_streambuf.hpp"
#include "basic_stream_socket.hpp"

#include <istream>

namespace network
{
	template<typename Protocol>
	class basic_socket_iostream : public std::basic_iostream<char>
	{
	  public:
		using protocol_type = Protocol;
		using endpoint_type = typename protocol_type::endpoint;

		basic_socket_iostream() = delete;
		explicit basic_socket_iostream(basic_stream_socket<protocol_type> s) : sb_(s) {}
		basic_socket_iostream(const basic_socket_iostream&) = delete;
		basic_socket_iostream(basic_socket_iostream&& other) noexcept : sb_(std::move(other.sb_)) {}
		basic_socket_iostream& operator=(const basic_socket_iostream&) = delete;
		basic_socket_iostream& operator											=(basic_socket_iostream&& other) noexcept
		{
			std::swap(sb_, other.sb_);
			return *this;
		}

		void close() { sb_.close(); }

		basic_socket_streambuf<protocol_type>* rdbuf() const { return &sb_; }
		basic_socket<protocol_type>& socket() { return sb_.socket(); }

	  private:
		basic_socket_streambuf<protocol_type> sb_;
	};
} // namespace network

#endif // NETWORK_BASIC_SOCKET_IOSTREAM_HPP
