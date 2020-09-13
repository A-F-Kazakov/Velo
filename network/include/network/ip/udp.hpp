#ifndef NETWORK_UDP_HPP
#define NETWORK_UDP_HPP

#include "../basic_datagram_socket.hpp"
#include "../basic_endpoint.hpp"

namespace network::ip
{
	class udp
	{
	  public:
		using endpoint = basic_endpoint<udp>;
		using socket	= basic_datagram_socket<udp>;

		static constexpr udp v4() noexcept { return udp(native::v4); }
		static constexpr udp v6() noexcept { return udp(native::v6); }

		udp() = delete;

		constexpr uint16_t family() const noexcept { return address_family; }
		constexpr uint16_t type() const noexcept { return native::datagram; }
		constexpr uint16_t protocol() const noexcept { return native::udp; }

	  private:
		explicit constexpr udp(uint16_t af) : address_family(af) {}

		uint16_t address_family;
	};

	bool operator==(const udp& a, const udp& b) noexcept { return (a.family() == b.family()); }
	bool operator!=(const udp& a, const udp& b) noexcept { return !operator==(a, b); }
} // namespace network::ip

#endif // NETWORK_UDP_HPP
