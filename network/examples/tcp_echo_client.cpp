#include "network/ip/tcp.hpp"

#include <algorithm>
#include <cstring>
#include <iostream>
#include <memory>

using network::buffer;
using network::ip::address;
using network::ip::tcp;

constexpr int max_length = 1024;

int main(int argc, char** argv)
{
	try
	{
		if(argc != 3)
		{
			std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
			return 1;
		}

		tcp::socket sock;

		sock.open(tcp::v4());

		sock.connect({address::from_str<address::v4>(argv[1]), static_cast<uint16_t>(std::stoi(argv[2]))});

		char request[max_length];

		std::cout << "Enter message: ";
		std::cin.getline(request, max_length);

		size_t request_length = std::strlen(request);
		sock.write(buffer(request, request_length));

		char reply[max_length];
		size_t reply_length = sock.read(buffer(reply, request_length));
		std::cout << "Reply is: ";
		std::cout.write(reply, reply_length);
		std::cout << "\n";
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}
