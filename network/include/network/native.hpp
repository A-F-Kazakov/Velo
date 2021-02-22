#ifndef NETWORK_CONFIG_HPP
#define NETWORK_CONFIG_HPP

#include <system_error>

#if __has_include("arch.hpp")
#include "arch.hpp"
#endif

#if __has_include("endian.hpp")

#include "endian.hpp"

#define CONSTEXPR			constexpr
#define TO_BIG_16(X)		big_endian{X}.raw_value
#define TO_LITTLE_16(X) little_endian{X}.raw_value

#define TO_BIG_32(X)		big_endian{X}.raw_value
#define TO_LITTLE_32(X) little_endian{X}.raw_value
#else
#define CONSTEXPR
#define TO_BIG_16(X)		htons(X)
#define TO_LITTLE_16(X) ntohs(X)

#define TO_BIG_32(X)		htonl(X)
#define TO_LITTLE_32(X) ntohl(X)
#endif

#if defined(OS_UNIX)

#include <arpa/inet.h>
#include <cerrno>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#ifdef __APPLE__
// Don't know is it a good approach
#define MSG_NOSIGNAL SO_NOSIGPIPE
#define MSG_CONFIRM	0x400
#define MSG_MORE 0x800
#define IN6_ADDR in6_addr
#else
#define IN6_ADDR		  void
#endif

#define IOCTL_ARG_TYPE int

#define NETWORK_LAST_ERROR		 errno
#define NETWORK_SOCKET_TYPE	 int
#define NETWORK_INVALID_SOCKET (-1)
#define NETWORK_CLOSE(X)		 close(X)
#define NETWORK_SOCKET_IOCTL	 ioctl

#define HOST_RESOLVER(X, Y) gethostbyname2(X, Y)

#define NETWORK_OPTION_SHUTDOWN_READ  SHUT_RD
#define NETWORK_OPTION_SHUTDOWN_WRITE SHUT_WR
#define NETWORK_OPTION_SHUTDOWN_BOTH  SHUT_RDWR

#define NETWORK_OPTION_FLAG_BROADCAST		SO_BROADCAST
#define NETWORK_OPTION_FLAG_REUSE_ADDRESS SO_BROADCAST
#define NETWORK_OPTION_FLAG_REUSE_PORT		SO_REUSEPORT
#define NETWORK_OPTION_FLAG_DEBUG			SO_DEBUG
#define NETWORK_OPTION_FLAG_OOB_INLINE		SO_OOBINLINE
#define NETWORK_OPTION_FLAG_DO_NOT_ROUTE	SO_DONTROUTE
#define NETWORK_OPTION_FLAG_NON_BLOCK		O_NONBLOCK
#define NETWORK_OPTION_FLAG_KEEP_ALIVE		SO_KEEPALIVE

#define NETWORK_OPTION_FLAG_LINGER		  SO_LINGER
#define NETWORK_OPTION_FLAG_WRITE_BUFFER SO_SNDBUF
#define NETWORK_OPTION_FLAG_READ_BUFFER  SO_RCVBUF

#define NETWORK_OPTION_FLAG_READ_TIMEOUT	SO_RCVTIMEO
#define NETWORK_OPTION_FLAG_WRITE_TIMEOUT SO_SNDTIMEO

#define NETWORK_READ_FLAG_NON_BLOCK MSG_DONTWAIT
#define NETWORK_READ_FLAG_PEEK		MSG_PEEK
#define NETWORK_READ_FLAG_WAIT_ALL	MSG_WAITALL
#define NETWORK_READ_FLAG_NO_SIGNAL MSG_NOSIGNAL

#define NETWORK_WRITE_FLAG_CONFIRM		 MSG_CONFIRM
#define NETWORK_WRITE_FLAG_DO_NOT_ROUTE MSG_DONTROUTE
#define NETWORK_WRITE_FLAG_DO_NOT_WAIT	 MSG_DONTWAIT
#define NETWORK_WRITE_FLAG_EOR			 MSG_EOR
#define NETWORK_WRITE_FLAG_MORE			 MSG_MORE
#define NETWORK_WRITE_FLAG_NO_SIGNAL	 MSG_NOSIGNAL
#define NETWORK_WRITE_FLAG_OOB			 MSG_OOB

#define NETWORK_MAX_CONNECTIONS SOMAXCONN

#elif defined(OS_WIN)

#include <WS2tcpip.h>
#include <WinSock2.h>
#include <ws2ipdef.h>

#define IOCTL_ARG_TYPE u_long

#define NETWORK_LAST_ERROR		 WSAGetLastError()
#define NETWORK_SOCKET_TYPE	 SOCKET
#define NETWORK_INVALID_SOCKET INVALID_SOCKET
#define NETWORK_CLOSE(X)		 closesocket(X)
#define NETWORK_SOCKET_IOCTL	 ioctlsocket

#define HOST_RESOLVER(X, Y) gethostbyname(X)

#define NETWORK_OPTION_SHUTDOWN_READ  SO_KEEPALIVE
#define NETWORK_OPTION_SHUTDOWN_WRITE SO_KEEPALIVE
#define NETWORK_OPTION_SHUTDOWN_BOTH  SO_KEEPALIVE

#define NETWORK_OPTION_FLAG_BROADCAST		SO_BROADCAST
#define NETWORK_OPTION_FLAG_REUSE_ADDRESS SO_REUSEADDR
#define NETWORK_OPTION_FLAG_REUSE_PORT		SO_REUSEADDR
#define NETWORK_OPTION_FLAG_DEBUG			SO_DEBUG
#define NETWORK_OPTION_FLAG_OOB_INLINE		SO_OOBINLINE
#define NETWORK_OPTION_FLAG_DO_NOT_ROUTE	SO_DONTROUTE
#define NETWORK_OPTION_FLAG_NON_BLOCK		FIONBIO
#define NETWORK_OPTION_FLAG_KEEP_ALIVE		SO_KEEPALIVE

#define NETWORK_OPTION_FLAG_LINGER		  SO_LINGER
#define NETWORK_OPTION_FLAG_WRITE_BUFFER SO_SNDBUF
#define NETWORK_OPTION_FLAG_READ_BUFFER  SO_RCVBUF

#define NETWORK_OPTION_FLAG_READ_TIMEOUT	SO_RCVTIMEO
#define NETWORK_OPTION_FLAG_WRITE_TIMEOUT SO_SNDTIMEO

#define NETWORK_READ_FLAG_NON_BLOCK FIONBIO
#define NETWORK_READ_FLAG_PEEK		MSG_PEEK
#define NETWORK_READ_FLAG_WAIT_ALL	MSG_WAITALL
#define NETWORK_READ_FLAG_NO_SIGNAL 0

#define NETWORK_WRITE_FLAG_CONFIRM		 0
#define NETWORK_WRITE_FLAG_DO_NOT_ROUTE MSG_DONTROUTE
#define NETWORK_WRITE_FLAG_DO_NOT_WAIT	 0
#define NETWORK_WRITE_FLAG_EOR			 0
#define NETWORK_WRITE_FLAG_MORE			 0
#define NETWORK_WRITE_FLAG_NO_SIGNAL	 0
#define NETWORK_WRITE_FLAG_OOB			 MSG_OOB

#define NETWORK_MAX_CONNECTIONS SOMAXCONN

#ifdef _WIN64
using ssize_t = __int64;
#else
using ssize_t = int;
#endif

namespace
{
	[[maybe_unused]] struct win_api_initializer
	{
		win_api_initializer()
		{
			int out = ::WSAStartup(MAKEWORD(2, 2), &d);
			if(out != 0)
				throw std::system_error(out, std::system_category());
		}
		~win_api_initializer() { ::WSACleanup(); }

		WSAData d{};
	} wsa;
} // namespace

#endif

namespace network::native
{
	using socket_type = NETWORK_SOCKET_TYPE;

	enum address_family { none = AF_UNSPEC, v4 = AF_INET, v6 = AF_INET6 };
	enum socket_type_e { stream = SOCK_STREAM, datagram = SOCK_DGRAM };
	enum socket_proto { tcp = IPPROTO_TCP, udp = IPPROTO_UDP };

	constexpr socket_type invalid_socket = NETWORK_INVALID_SOCKET;
	constexpr int max_listen_connections = NETWORK_MAX_CONNECTIONS;

	inline int error_code() noexcept { return NETWORK_LAST_ERROR; }

	inline CONSTEXPR uint16_t to_network_format(uint16_t value) { return TO_BIG_16(value); }
	inline CONSTEXPR uint16_t from_network_format(uint16_t value) { return TO_LITTLE_16(value); }

	inline CONSTEXPR uint32_t to_network_format(uint32_t value) { return TO_BIG_32(value); }
	inline CONSTEXPR uint32_t from_network_format(uint32_t value) { return TO_LITTLE_32(value); }

	inline int close(socket_type fd) { return ::NETWORK_CLOSE(fd); }
	inline int io_control(socket_type fd, uint64_t flag, IOCTL_ARG_TYPE* value) { return ::NETWORK_SOCKET_IOCTL(fd, flag, value); }
	inline int host_name(char* buffer, size_t size) { return ::gethostname(buffer, size); }
	inline hostent* resolve_host(const char* str, int address_family) { return ::HOST_RESOLVER(str, address_family); }

	constexpr inline int shutdown_flag_read() { return NETWORK_OPTION_SHUTDOWN_READ; }
	constexpr inline int shutdown_flag_write() { return NETWORK_OPTION_SHUTDOWN_WRITE; }
	constexpr inline int shutdown_flag_both() { return NETWORK_OPTION_SHUTDOWN_BOTH; }

	constexpr inline int option_boolean_flag_broadcast() { return NETWORK_OPTION_FLAG_BROADCAST; }
	constexpr inline int option_boolean_flag_reuse_address() { return NETWORK_OPTION_FLAG_REUSE_ADDRESS; }
	constexpr inline int option_boolean_flag_reuse_port() { return NETWORK_OPTION_FLAG_REUSE_PORT; }
	constexpr inline int option_boolean_flag_debug() { return NETWORK_OPTION_FLAG_DEBUG; }
	constexpr inline int option_boolean_flag_oob_inline() { return NETWORK_OPTION_FLAG_OOB_INLINE; }
	constexpr inline int option_boolean_flag_do_not_route() { return NETWORK_OPTION_FLAG_DO_NOT_ROUTE; }
	constexpr inline int option_boolean_flag_non_block() { return NETWORK_OPTION_FLAG_NON_BLOCK; }
	constexpr inline int option_boolean_flag_keep_alive() { return NETWORK_OPTION_FLAG_KEEP_ALIVE; }

	constexpr inline int option_value_flag_linger() { return NETWORK_OPTION_FLAG_LINGER; }
	constexpr inline int option_value_flag_write_buffer() { return NETWORK_OPTION_FLAG_WRITE_BUFFER; }
	constexpr inline int option_value_flag_read_buffer() { return NETWORK_OPTION_FLAG_READ_BUFFER; }

	constexpr inline int option_timeout_flag_read() { return NETWORK_OPTION_FLAG_READ_TIMEOUT; }
	constexpr inline int option_timeout_flag_write() { return NETWORK_OPTION_FLAG_WRITE_TIMEOUT; }

	constexpr inline int option_read_flag_non_block() { return NETWORK_READ_FLAG_NON_BLOCK; }
	constexpr inline int option_read_flag_peek() { return NETWORK_READ_FLAG_PEEK; }
	constexpr inline int option_read_flag_wait_all() { return NETWORK_READ_FLAG_WAIT_ALL; }
	constexpr inline int option_read_flag_no_signal() { return NETWORK_READ_FLAG_NO_SIGNAL; }

	constexpr inline int option_write_flag_confirm() { return NETWORK_WRITE_FLAG_CONFIRM; }
	constexpr inline int option_write_flag_do_not_route() { return NETWORK_WRITE_FLAG_DO_NOT_ROUTE; }
	constexpr inline int option_write_flag_do_not_wait() { return NETWORK_WRITE_FLAG_DO_NOT_WAIT; }
	constexpr inline int option_write_flag_eor() { return NETWORK_WRITE_FLAG_EOR; }
	constexpr inline int option_write_flag_mor() { return NETWORK_WRITE_FLAG_MORE; }
	constexpr inline int option_write_flag_no_signal() { return NETWORK_WRITE_FLAG_NO_SIGNAL; }
	constexpr inline int option_write_flag_oob() { return NETWORK_WRITE_FLAG_OOB; }

	inline bool is_address_loopback(const unsigned char* data) { return IN6_IS_ADDR_LOOPBACK((IN6_ADDR*)data); }
	inline bool is_address_unspecified(const unsigned char* data) { return IN6_IS_ADDR_UNSPECIFIED((IN6_ADDR*)data); }
	inline bool is_address_link_local(const unsigned char* data) { return IN6_IS_ADDR_LINKLOCAL((IN6_ADDR*)data); }
	inline bool is_address_site_local(const unsigned char* data) { return IN6_IS_ADDR_SITELOCAL((IN6_ADDR*)data); }
	inline bool is_address_v4_mapped(const unsigned char* data) { return IN6_IS_ADDR_V4MAPPED((IN6_ADDR*)data); }
	inline bool is_address_multi_cast(const unsigned char* data) { return IN6_IS_ADDR_MULTICAST((IN6_ADDR*)data); }
	inline bool is_address_mc_global(const unsigned char* data) { return IN6_IS_ADDR_MC_GLOBAL((IN6_ADDR*)data); }
	inline bool is_address_mc_local(const unsigned char* data) { return IN6_IS_ADDR_MC_LINKLOCAL((IN6_ADDR*)data); }
	inline bool is_address_mc_node_local(const unsigned char* data) { return IN6_IS_ADDR_MC_NODELOCAL((IN6_ADDR*)data); }
	inline bool is_address_mc_org_local(const unsigned char* data) { return IN6_IS_ADDR_MC_ORGLOCAL((IN6_ADDR*)data); }
	inline bool is_address_mc_site_local(const unsigned char* data) { return IN6_IS_ADDR_MC_SITELOCAL((IN6_ADDR*)data); }

	inline bool is_address_equal(const unsigned char* l, const unsigned char* r)
	{
		return IN6_ARE_ADDR_EQUAL(reinterpret_cast<const IN6_ADDR*>(l), reinterpret_cast<const IN6_ADDR*>(r));
	}

	inline int set_socket_option(socket_type descriptor, int option, int value)
	{
		int out = 0;
		if(option == NETWORK_OPTION_FLAG_NON_BLOCK)
		{
#if defined(OS_Windows)
			int iSize, iValOld, iValNew = 1;
			iSize = sizeof(iValOld);
			out	= getsockopt(descriptor, SOL_SOCKET, SO_RCVTIMEO, (char*)&iValOld, &iSize);

			if(out == -1)
				return out;

			out = setsockopt(descriptor, SOL_SOCKET, SO_RCVTIMEO, (char*)&iValNew, iSize);
#elif defined(OS_Linux)
			out = fcntl(descriptor, F_GETFL, 0);

			if(out == -1)
				return out;

			if(value)
				out |= O_NONBLOCK;
			else
				out &= ~O_NONBLOCK;

			out = fcntl(descriptor, F_SETFL, out);
#endif
			if(out == -1)
				return out;
		}
		else
			return ::setsockopt(descriptor, SOL_SOCKET, option, (char*)&value, sizeof(int));
		return 0;
	}
} // namespace network::native

#undef NETWORK_LAST_ERROR
#undef NETWORK_SOCKET_TYPE
#undef NETWORK_INVALID_SOCKET
#undef NETWORK_CLOSE
#undef NETWORK_SOCKET_IOCTL

#undef NETWORK_OPTION_SHUTDOWN_READ
#undef NETWORK_OPTION_SHUTDOWN_WRITE
#undef NETWORK_OPTION_SHUTDOWN_BOTH

#undef NETWORK_OPTION_FLAG_BROADCAST
#undef NETWORK_OPTION_FLAG_REUSE_ADDRESS
#undef NETWORK_OPTION_FLAG_REUSE_PORT
#undef NETWORK_OPTION_FLAG_DEBUG
#undef NETWORK_OPTION_FLAG_OOB_INLINE
#undef NETWORK_OPTION_FLAG_DO_NOT_ROUTE
#undef NETWORK_OPTION_FLAG_NON_BLOCK
#undef NETWORK_OPTION_FLAG_KEEP_ALIVE

#undef NETWORK_OPTION_FLAG_LINGER
#undef NETWORK_OPTION_FLAG_WRITE_BUFFER
#undef NETWORK_OPTION_FLAG_READ_BUFFER

#undef NETWORK_OPTION_FLAG_READ_TIMEOUT
#undef NETWORK_OPTION_FLAG_WRITE_TIMEOUT

#undef NETWORK_READ_FLAG_NON_BLOCK
#undef NETWORK_READ_FLAG_PEEK
#undef NETWORK_READ_FLAG_WAIT_ALL
#undef NETWORK_READ_FLAG_NO_SIGNAL

#undef NETWORK_WRITE_FLAG_CONFIRM
#undef NETWORK_WRITE_FLAG_DO_NOT_ROUTE
#undef NETWORK_WRITE_FLAG_DO_NOT_WAIT
#undef NETWORK_WRITE_FLAG_EOR
#undef NETWORK_WRITE_FLAG_MORE
#undef NETWORK_WRITE_FLAG_NO_SIGNAL
#undef NETWORK_WRITE_FLAG_OOB

#undef NETWORK_MAX_CONNECTIONS

#endif // NETWORK_CONFIG_HPP
