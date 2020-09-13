#ifndef NETWORK_TCP_HPP
#define NETWORK_TCP_HPP

#include "../basic_socket_acceptor.hpp"
#include "../basic_stream_socket.hpp"
#include "../basic_endpoint.hpp"

namespace network::ip
{
	class tcp
	{
	  public:
		using endpoint = basic_endpoint<tcp>;
		using socket	= basic_stream_socket<tcp>;
		using acceptor = basic_socket_acceptor<tcp>;

		static constexpr tcp v4() noexcept { return tcp(native::v4); }
		static constexpr tcp v6() noexcept { return tcp(native::v6); }

		tcp() = delete;

		constexpr uint16_t family() const noexcept { return address_family; }
		constexpr uint16_t type() const noexcept { return native::stream; }
		constexpr uint16_t protocol() const noexcept { return native::tcp; }

	  protected:
		explicit constexpr tcp(uint16_t af) : address_family(af) {}

		uint16_t address_family;
	};

	bool operator==(const tcp& a, const tcp& b) noexcept { return (a.family() == b.family()); }
	bool operator!=(const tcp& a, const tcp& b) noexcept { return !operator==(a, b); }
} // namespace network::ip

#endif // NETWORK_TCP_HPP
