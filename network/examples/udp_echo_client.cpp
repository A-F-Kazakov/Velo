#include "network/ip/udp.hpp"

#include <cstring>
#include <iostream>

using network::buffer;
using network::ip::address;
using network::ip::udp;

constexpr int max_length = 1024;

int main(int argc, char** argv)
{
	try
	{
		if(argc != 3)
		{
			std::cerr << "Usage: blocking_udp_echo_client <host> <port>\n";
			return 1;
		}

		udp::socket s({udp::v4(), 0});

		udp::endpoint endpoint(address::from_str<address::v4>(argv[1]), static_cast<uint16_t>(std::stoi(argv[2])));

		char request[max_length];

		std::cout << "Enter message: ";
		std::cin.getline(request, max_length);

		auto request_length = std::strlen(request);

		s.write(buffer(request, request_length), endpoint);

		char reply[max_length];

		udp::endpoint sender_endpoint;
		size_t reply_length = s.read(buffer(reply), sender_endpoint);
		std::cout << "Reply is: ";
		std::cout.write(reply, reply_length);
		std::cout << "\n";
	}
	catch(std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}
