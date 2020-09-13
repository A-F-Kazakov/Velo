#include <iostream>
#include <network/buffer.hpp>
#include <network/ip/tcp.hpp>
#include <network/ssl/context.hpp>
#include <network/ssl/stream.hpp>

using network::ip::address;
using network::ip::tcp;
using network::ssl::context;

constexpr int max_length = 1024;

int main(int argc, char** argv)
{
	try
	{
		if(argc != 3)
		{
			std::cerr << "Usage: " << argv[0] << " <host> <port> <cert> <key> <ca>\n";
			return 1;
		}

		context ctx(context::tls_client);

		ctx.use_certificate_file(argv[2], context::pem);
		ctx.use_private_key_file(argv[3], context::pem);
		ctx.verify_private_key();

		ctx.set_verify_path(argv[4]);
		ctx.set_verify_depth(2);

		auto addr = tcp::endpoint(address::v4::from_str(argv[1]), static_cast<uint16_t>(std::stoi(argv[2])));

		network::ssl::stream<tcp> io(ctx);

		io.connect(addr);

		io.handshake(context::client);

		char buf[1024];

		io.write(network::buffer("Hello"));

		io.read(network::buffer(buf));

		std::cout << "Received: " << buf << std::endl;
	}
	catch(std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}
