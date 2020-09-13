#include <iostream>
#include <network/buffer.hpp>
#include <network/ip/tcp.hpp>
#include <network/ssl/context.hpp>
#include <network/ssl/stream.hpp>
#include <thread>

using network::ip::address;
using network::ip::tcp;
using network::ssl::context;

constexpr int max_length = 1024;

void session(const context& ctx, tcp::socket sock)
{
	try
	{
		char data[max_length];

		network::ssl::stream<tcp> io(ctx, std::move(sock));

		io.handshake(context::server);

		while(true)
		{
			size_t length = io.read(network::buffer(data));
			io.write(network::buffer(data, length));
		}
	}
	catch(const std::exception& e)
	{
		std::cerr << "Session exception: " << e.what() << "\n";
	}
}

class server
{
  public:
	server(const context& ctx, uint16_t port) : ctx(std::move(ctx)), acceptor(tcp::endpoint(address::v4::any(), port), true) {}

	void run()
	{
		tcp::socket sock;
		tcp::endpoint session_address{};
		while(true)
		{
			acceptor.accept(sock, session_address);

			std::clog << "Connection from host " << session_address << " established\n";

			std::thread(session, std::ref(ctx), std::move(sock)).detach();
		}
	}

  private:
	tcp::acceptor acceptor;
	const context& ctx;
};

int main(int argc, char** argv)
{
	try
	{
		if(argc != 5)
		{
			std::cerr << "Usage: " << argv[0] << " <port> <cert> <key> <ca>\n";
			return 1;
		}

		context ctx(context::tls_server);

		ctx.use_certificate_file(argv[2], context::pem);
		ctx.use_private_key_file(argv[3], context::pem);
		ctx.verify_private_key();

		ctx.set_verify_path(argv[4]);
		ctx.set_verify_depth(2);

		server s(ctx, static_cast<uint16_t>(std::stoi(argv[1])));
		s.run();
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}
