#ifndef NETWORK_BASIC_SOCKET_STREAMBUF_HPP
#define NETWORK_BASIC_SOCKET_STREAMBUF_HPP

#include "basic_stream_socket.hpp"

#include <streambuf>

namespace network
{
	template<typename Protocol>
	class basic_socket_streambuf : public std::basic_streambuf<char>
	{
	  public:
		using protocol_type = Protocol;
		using endpoint_type = typename protocol_type::endpoint;

		basic_socket_streambuf() = delete;

		explicit basic_socket_streambuf(basic_stream_socket<protocol_type> s) : socket_(std::move(s)) { init_buffers(); }

		basic_socket_streambuf(const basic_socket_streambuf&) = delete;
		basic_socket_streambuf(basic_socket_streambuf&& rhs) noexcept : socket_(std::move(rhs.socket_)) { init_buffers(); }

		~basic_socket_streambuf() noexcept override { flush_m(); }

		basic_socket_streambuf& operator=(const basic_socket_streambuf&) = delete;
		basic_socket_streambuf& operator											  =(basic_socket_streambuf&& rhs) noexcept
		{
			socket_ = std::move(rhs.socket_);
			return *this;
		}

		basic_socket_streambuf* connect(const endpoint_type& e)
		{
			init_buffers();
			socket_.connect(e);
			return this;
		}

		basic_socket_streambuf* close()
		{
			sync();
			socket_.close();
			return this;
		}

		basic_socket<protocol_type>& socket() { return socket_; }

	  protected:
		int_type underflow() override
		{
			if(gptr() < egptr())
				return *(unsigned char*)gptr();

			ssize_t nbRead = 0;

			std::error_code err = socket_.read(buffer(in_buffer, buffer_size));

			if(err)
				return EOF;

			setg(eback(), eback(), eback() + nbRead);

			return *(unsigned char*)gptr();
		}

		int_type overflow(int_type c = traits_type::eof()) override
		{
			if(c == EOF)
				return flush_m();

			*pptr() = c;
			pbump(1);

			if(c == '\n' || pptr() >= epptr())
				if(flush_m() == EOF)
					return EOF;

			return c;
		}

		int sync() override { return flush_m(); }

	  private:
		int flush_m()
		{
			// Return 0 if nothing to fflush or success
			// Return EOF if couldnt fflush

			if(pptr() < pbase())
				return 0;

			if(!socket_.write(std::string_view(pbase(), pptr() - pbase())))
				return EOF;

			setp(out_buffer, out_buffer + buffer_size);

			return 0;
		}

		void init_buffers()
		{
			char* in_buffer_end_ptr = in_buffer + buffer_size;

			setg(in_buffer, in_buffer_end_ptr, in_buffer_end_ptr);
			setp(out_buffer, out_buffer + buffer_size);
		}

		basic_stream_socket<protocol_type> socket_;
		enum { buffer_size = 512 };
		char in_buffer[buffer_size];
		char out_buffer[buffer_size];
	};
} // namespace network

#endif // NETWORK_BASIC_SOCKET_STREAMBUF_HPP
