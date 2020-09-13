#include "network/ip/udp.hpp"

#include <iostream>

using network::buffer;
using network::ip::address;
using network::ip::udp;

constexpr int max_length = 1024;

void server(uint16_t port)
{
	udp::socket sock({udp::v4(), port});
	char data[max_length];

	while(true)
	{
		udp::endpoint sender_endpoint;
		size_t length = sock.read(buffer(data, max_length), sender_endpoint);

		std::clog << "Message from " << sender_endpoint << '\n';

		sock.write(buffer(data, length), sender_endpoint);
	}
}

int main(int argc, char** argv)
{
	try
	{
		if(argc != 2)
		{
			std::cerr << "Usage: blocking_udp_echo_server <port>\n";
			return 1;
		}

		server(static_cast<uint16_t>(std::stoi(argv[1])));
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}
