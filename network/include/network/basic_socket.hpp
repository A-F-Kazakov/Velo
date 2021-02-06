#ifndef NETWORK_BASIC_SOCKET_HPP
#define NETWORK_BASIC_SOCKET_HPP

#include "error.hpp"
#include "native.hpp"
#include "socket_options.hpp"

#include <chrono>

namespace network
{
	template<class Protocol>
	class basic_socket
	{
	  public:
		using descriptor_type = native::socket_type;
		using protocol_type	 = Protocol;
		using endpoint_type	 = typename protocol_type::endpoint;

		enum class shutdown_target {
			read	= native::shutdown_flag_read(),
			write = native::shutdown_flag_write(),
			both	= native::shutdown_flag_both()
		};

		basic_socket() noexcept = default;

		explicit basic_socket(const protocol_type& proto) noexcept { open(proto); };

		explicit basic_socket(endpoint_type endpoint)
		{
			if(endpoint.address().is_v4())
				open(protocol_type::v4());
			else
				open(protocol_type::v6());

			bind(endpoint);
		}

		basic_socket(const basic_socket&) = delete;
		basic_socket(basic_socket&& mv) noexcept : descriptor(mv.descriptor) { mv.descriptor = native::invalid_socket; }

		~basic_socket() noexcept { native::close(descriptor); }

		basic_socket& operator=(const basic_socket&) = delete;
		basic_socket& operator								=(basic_socket&& mv) noexcept
		{
			std::swap(descriptor, mv.descriptor);
			return *this;
		}

		void open(const protocol_type& protocol)
		{
			if(is_open())
				close();

			descriptor = ::socket(protocol.family(), protocol.type(), protocol.protocol());

			if(descriptor == native::invalid_socket)
				throw error::socket(native::error_code(), __FUNCTION__);
		}

		bool is_open() const noexcept { return (descriptor != native::invalid_socket); }

		void close()
		{
			if(descriptor != native::invalid_socket)
			{
				int out = native::close(descriptor);

				if(out == -1)
					throw error::socket(native::error_code(), __FUNCTION__);
				descriptor = native::invalid_socket;
			}
		}

		size_t available() const
		{
			if(descriptor == native::invalid_socket)
				return 0;

			int value;

			int out = native::io_control(descriptor, FIONREAD, &value);

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);

			return static_cast<size_t>(value);
		}

		void bind(const endpoint_type& endpoint)
		{
			int out = ::bind(descriptor, endpoint.data(), endpoint.size());

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);
		}

		endpoint_type local_endpoint() const
		{
			endpoint_type endp;

			socklen_t name_len = endp.size();
			int out				 = ::getsockname(descriptor, reinterpret_cast<sockaddr*>(&endp), &name_len);

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);

			return endp;
		}

		inline void debug(on_off_options o)
		{
			int out = setsockopt(descriptor, SOL_SOCKET, native::option_boolean_flag_debug(), &o, sizeof(int));

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);
		}

		inline void broadcast(on_off_options o)
		{
			int out = setsockopt(descriptor, SOL_SOCKET, native::option_boolean_flag_broadcast(), &o, sizeof(int));

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);
		}

		inline void reuse_address(on_off_options o)
		{
			int out = setsockopt(descriptor, SOL_SOCKET, native::option_boolean_flag_reuse_address(), &o, sizeof(int));

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);
		}

		inline void reuse_port(on_off_options o)
		{
			int out = setsockopt(descriptor, SOL_SOCKET, native::option_boolean_flag_reuse_port(), &o, sizeof(int));

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);
		}

		inline void oob_inline(on_off_options o)
		{
			int out = setsockopt(descriptor, SOL_SOCKET, native::option_boolean_flag_oob_inline(), &o, sizeof(int));

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);
		}

		inline void do_not_route(on_off_options o)
		{
			int out = setsockopt(descriptor, SOL_SOCKET, native::option_boolean_flag_do_not_route(), &o, sizeof(int));

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);
		}

		inline void non_blocking(on_off_options o)
		{
			int out = fcntl(descriptor, F_GETFL, 0);

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);

			if(o == on_off_options::enable)
				out |= native::option_boolean_flag_non_block();
			else
				out &= ~native::option_boolean_flag_non_block();

			out = fcntl(descriptor, F_SETFL, out);

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);
		}

		inline void keep_alive(on_off_options o)
		{
			int out = setsockopt(descriptor, SOL_SOCKET, native::option_boolean_flag_keep_alive(), &o, sizeof(int));

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);
		}

		inline void write_buffer(int size)
		{
			int out = setsockopt(descriptor, SOL_SOCKET, native::option_value_flag_write_buffer(), &size, sizeof(int));

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);
		}

		inline std::size_t write_buffer()
		{
			int size		= 0;
			socklen_t t = sizeof(size);
			int out		= getsockopt(descriptor, SOL_SOCKET, native::option_value_flag_write_buffer(), &size, &t);

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);

			return static_cast<size_t>(size);
		}

		inline void read_buffer(int size)
		{
			int out = setsockopt(descriptor, SOL_SOCKET, native::option_value_flag_read_buffer(), &size, sizeof(int));

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);
		}

		inline std::size_t read_buffer()
		{
			int size		= 0;
			socklen_t t = sizeof(size);
			int out		= getsockopt(descriptor, SOL_SOCKET, native::option_value_flag_write_buffer(), &size, &t);

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);

			return static_cast<size_t>(size);
		}

		template<typename Rep, typename Period>
		inline void linger(std::chrono::duration<Rep, Period> d)
		{
			struct linger lng
			{};
			lng.l_onoff	 = d.count();
			lng.l_linger = static_cast<int>(std::chrono::duration_cast<std::chrono::seconds>(d).count());

			int out =
			  setsockopt(descriptor, SOL_SOCKET, native::option_value_flag_linger(), (const char*)&lng, sizeof(struct linger));

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);
		}

		inline std::chrono::seconds linger()
		{
			struct linger lng
			{};
			socklen_t t = sizeof(lng);
			int out		= getsockopt(descriptor, SOL_SOCKET, native::option_value_flag_linger(), (void*)&lng, &t);

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);

			return std::chrono::seconds(lng.l_linger);
		}

		template<typename Rep, typename Period>
		inline void write_timeout(std::chrono::duration<Rep, Period> d)
		{
			option(native::option_timeout_flag_write(), d);
		}

		inline std::chrono::seconds write_timeout() { return option(native::option_timeout_flag_write()); }

		template<typename Rep, typename Period>
		inline void read_timeout(std::chrono::duration<Rep, Period> d)
		{
			option(native::option_timeout_flag_read(), d);
		}

		inline std::chrono::seconds read_timeout() { return option(native::option_timeout_flag_read()); }

	  protected:
		explicit constexpr inline basic_socket(int value) noexcept : descriptor(value) {}

		basic_socket& operator=(descriptor_type desc)
		{
			descriptor = desc;
			return *this;
		}

		inline endpoint_type remote_endpoint() const
		{
			endpoint_type endp;

			socklen_t len = endp.size();
			int out		  = ::getpeername(descriptor, endp.data(), &len);

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);

			return endp;
		}

		inline void connect(endpoint_type addr)
		{
			int out = ::connect(descriptor, addr.data(), addr.size());

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);
		}

		inline void shutdown(shutdown_target target)
		{
			int out = ::shutdown(descriptor, static_cast<int>(target));

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);
		}

		inline void listen(int num = native::max_listen_connections)
		{
			int out = ::listen(descriptor, num);

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);
		}

		inline int accept_fd(sockaddr* address, socklen_t* address_length) const
		{
			int out = ::accept(descriptor, address, address_length);

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);

			return out;
		}

		inline size_t read(char* buf, size_t size, int flags) const
		{
			ssize_t out = ::recv(descriptor, buf, size, flags);

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);
			else if(out == 0)
				throw error::socket(std::make_error_code(std::errc::connection_aborted));

			return static_cast<size_t>(out);
		}

		inline size_t write(const char* buf, size_t size, int flags) const
		{
			ssize_t out = ::send(descriptor, buf, size, flags);

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);
			else if(out == 0)
				throw error::socket(std::make_error_code(std::errc::connection_aborted));

			return static_cast<size_t>(out);
		}

		inline size_t read(endpoint_type& addr, char* buf, size_t size, int flags) const
		{
			auto len		= addr.size();
			ssize_t out = ::recvfrom(descriptor, buf, size, flags, addr.data(), reinterpret_cast<socklen_t*>(&len));

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);

			return static_cast<size_t>(out);
		}

		inline size_t write(endpoint_type& addr, const char* buf, size_t size, int flags) const
		{
			auto out = ::sendto(descriptor, buf, size, flags, addr.data(), addr.size());

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);

			return static_cast<size_t>(out);
		}

		inline descriptor_type get_descriptor() { return descriptor; }

		template<typename Rep, typename Period>
		inline void option(int opt, std::chrono::duration<Rep, Period> d)
		{
			struct timeval timeout
			{};
			timeout.tv_sec	 = std::chrono::duration_cast<std::chrono::seconds>(d).count();
			timeout.tv_usec = std::chrono::duration_cast<std::chrono::milliseconds>(d).count() - timeout.tv_sec;

			int out = setsockopt(descriptor, SOL_SOCKET, opt, (const char*)&timeout, sizeof(struct timeval));

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);
		}

		inline std::chrono::seconds option(int opt)
		{
			struct timeval timeout
			{};
			socklen_t sz = sizeof(struct timeval);

			int out = getsockopt(descriptor, SOL_SOCKET, opt, (void*)&timeout, &sz);

			if(out == -1)
				throw error::socket(native::error_code(), __FUNCTION__);

			auto ret = std::chrono::milliseconds(timeout.tv_sec * 1000);
			ret += std::chrono::milliseconds(timeout.tv_usec);

			return std::chrono::duration_cast<std::chrono::seconds>(ret);
		}

	  private:
		descriptor_type descriptor{native::invalid_socket};
	};
} // namespace network

#endif // NETWORK_BASIC_SOCKET_HPP
 
#include <optional>
#include <system_error>

namespace network
{
    struct endpoint{};

    enum three_way_latch{ read, write, both };

    template<typename Protocol>
    struct basic_socket
    {
        using native_type = int;
        using protocol_type = Protocol;

        basic_socket() = default;
        explicit basic_socket(const protocol_type& proto) noexcept { open(proto);}

        basic_socket(const basic_socket&) noexcept = delete;
        basic_socket(basic_socket&&) noexcept = default;

        ~basic_socket() noexcept { close(); }

        basic_socket& operator=(const basic_socket&) noexcept = delete;
        basic_socket& operator=(basic_socket&&) noexcept = default;

        std::error_code open(protocol_type endp) noexcept { return {}; }

        std::error_code close() noexcept { return {}; }

        std::error_code shutdown(three_way_latch type) noexcept { return {}; }

        [[nodiscard]]
        size_t read(endpoint endp, std::error_code&) noexcept { return 0; }

        [[nodiscard]]
        size_t read(std::error_code&) noexcept { return 0; }

        private:
            native_type descriptor{};
    };

    struct tcp{};
}
