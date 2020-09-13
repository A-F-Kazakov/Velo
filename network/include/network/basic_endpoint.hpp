#ifndef NETWORK_BASIC_ENDPOINT_HPP
#define NETWORK_BASIC_ENDPOINT_HPP

#include "ip/address.hpp"

namespace network::ip
{
	template<class Protocol>
	class basic_endpoint
	{
	  public:
		using protocol_type = Protocol;
		using port_type	  = uint16_t;
		using family_type	  = uint16_t;

		constexpr explicit basic_endpoint() noexcept : af(protocol_type::v4()) {}
		constexpr explicit basic_endpoint(protocol_type proto) noexcept : af(proto) {}

		constexpr basic_endpoint(protocol_type proto, port_type port) noexcept : af(proto), port_(native::to_network_format(port))
		{}
		constexpr basic_endpoint(const address_v4& address, port_type port) noexcept :
			af(protocol_type::v4()), port_(native::to_network_format(port)), ipv4(address)
		{}
		constexpr basic_endpoint(const address_v6& address, port_type port) noexcept :
			af(protocol_type::v6()), port_(native::to_network_format(port)), ipv6(address)
		{}

		constexpr void address(const address_v4& addr) noexcept { ipv4 = addr; }
		constexpr void address(const address_v6& addr) noexcept { ipv6 = addr; }

		network::ip::address address() const noexcept
		{
			if(is_v4())
				return network::ip::address(ipv4);
			else
				return network::ip::address(ipv6);
		}

		constexpr port_type port() const noexcept { return native::to_network_format(port_); }
		constexpr void port(port_type port_num) noexcept { port_ = native::from_network_format(port_num); }

		constexpr sockaddr* data() noexcept { return reinterpret_cast<sockaddr*>(this); }
		constexpr const sockaddr* data() const noexcept { return reinterpret_cast<const sockaddr*>(this); }

		constexpr size_t size() const noexcept
		{
			if(af.family() == AF_INET)
				return sizeof(sockaddr_in);
			else
				return sizeof(sockaddr_in6);
		}

		bool is_v4() const noexcept { return (af.family() == AF_INET); }
		bool is_v6() const noexcept { return (af.family() == AF_INET6); }

		protocol_type protocol() const { return af; }

	  private:
		protocol_type af;
		port_type port_{};
		union
		{
			address_v4 ipv4;
			address_v6 ipv6{};
		};
	};

	template<class Protocol>
	bool operator==(const basic_endpoint<Protocol>& a1, const basic_endpoint<Protocol>& a2) noexcept
	{
		return (a1.port() == a2.port()) && (a1.address() == a2.address());
	}

	template<class Protocol>
	bool operator!=(const basic_endpoint<Protocol>& a1, const basic_endpoint<Protocol>& a2) noexcept
	{
		return !operator==(a1, a2);
	}

	template<class Protocol>
	std::ostream& operator<<(std::ostream& os, const basic_endpoint<Protocol>& ep)
	{
		os << "{" << ep.address() << ":" << ep.port() << "}";
		return os;
	}
} // namespace network::ip

#endif // NETWORK_BASIC_ENDPOINT_HPP
