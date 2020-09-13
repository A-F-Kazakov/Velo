#ifndef NETWORK_SOCKET_OPTIONS_HPP
#define NETWORK_SOCKET_OPTIONS_HPP

#include "native.hpp"

enum on_off_options { disable, enable };

namespace network::socket::option
{
	enum shutdown_type {
		shutdown_read	= native::shutdown_flag_read(),
		shutdown_write = native::shutdown_flag_write(),
		shutdown_both	= native::shutdown_flag_both()
	};

	enum boolean_options {
		broadcast	  = native::option_boolean_flag_broadcast(),
		reuse_address = native::option_boolean_flag_reuse_address(),
		reuse_port	  = native::option_boolean_flag_reuse_port(),
		debug			  = native::option_boolean_flag_debug(),
		oobinline	  = native::option_boolean_flag_oob_inline(),
		dont_route	  = native::option_boolean_flag_do_not_route(),
		non_blocking  = native::option_boolean_flag_non_block(),
		keepalive	  = native::option_boolean_flag_keep_alive()
	};

	enum number_options {
		LINGER		 = native::option_value_flag_linger(),
		WRITE_BUFFER = native::option_value_flag_write_buffer(),
		READ_BUFFER	 = native::option_value_flag_read_buffer()
	};

	enum timeout_options {
		READ_TIMEOUT  = native::option_timeout_flag_read(),
		WRITE_TIMEOUT = native::option_timeout_flag_write()
	};
} // namespace network::socket::option

namespace network::socket_resolver::option
{
	enum flags {
		canonical_name		 = AI_CANONNAME,
		passive				 = AI_PASSIVE,
		numeric_host		 = AI_NUMERICHOST,
		numeric_service	 = AI_NUMERICSERV,
		v4_mapped			 = AI_V4MAPPED,
		all_matching		 = AI_ALL,
		address_configured = AI_ADDRCONFIG
	};

	flags operator&(flags x, flags y) { return static_cast<flags>(static_cast<unsigned int>(x) & static_cast<unsigned int>(y)); }

	flags operator|(flags x, flags y) { return static_cast<flags>(static_cast<unsigned int>(x) | static_cast<unsigned int>(y)); }

	flags operator^(flags x, flags y) { return static_cast<flags>(static_cast<unsigned int>(x) ^ static_cast<unsigned int>(y)); }

	flags operator~(flags x) { return static_cast<flags>(~static_cast<unsigned int>(x)); }

	flags& operator&=(flags& x, flags y)
	{
		x = x & y;
		return x;
	}

	flags& operator|=(flags& x, flags y)
	{
		x = x | y;
		return x;
	}

	flags& operator^=(flags& x, flags y)
	{
		x = x ^ y;
		return x;
	}
} // namespace network::socket_resolver::option

#endif // NETWORK_SOCKET_OPTIONS_HPP
