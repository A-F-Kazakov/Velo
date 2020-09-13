#include "network/ip/tcp.hpp"

#include <iostream>
#include <thread>

using network::buffer;
using network::ip::tcp;

constexpr int max_length = 1024;

void session(tcp::socket sock, tcp::endpoint peer_address)
{
	try
	{
		char data[max_length];

		while(true)
		{
			size_t length = sock.read(buffer(data));
			sock.write(buffer(data, length));
		}
	}
	catch(const network::error::socket& e)
	{
		if(e.code() == std::errc::connection_aborted)
			std::clog << "Connection with host " << peer_address << " aborted\n";
		else
			std::cerr << "Session exception: " << e.what() << "\n";
	}
}

void server(tcp protocol, uint16_t port)
{
	tcp::acceptor a(tcp::endpoint(protocol, port), true);
	while(true)
	{
		tcp::socket sock;
		tcp::endpoint address(protocol);
		a.accept(sock, address);

		std::clog << "Connection from host " << address << " established\n";

		std::thread(session, std::move(sock), address).detach();
	}
}

int main(int argc, char** argv)
{
	try
	{
		if(argc != 2)
		{
			std::cerr << "Usage: blocking_tcp_echo_server <port>\n";
			return 1;
		}

		server(tcp::v4(), static_cast<uint16_t>(std::stoi(argv[1])));
	}
	catch(const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
}
