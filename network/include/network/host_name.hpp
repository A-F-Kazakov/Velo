#ifndef NETWORK_HOST_NAME_HPP
#define NETWORK_HOST_NAME_HPP

#include "error.hpp"
#include "native.hpp"

#include <string>

namespace network
{
	std::string host_name()
	{
		char name[1024];
		if(int out = native::host_name(name, sizeof(name)); out != 0)
			throw network_error(out);

		return std::string(name);
	}
} // namespace network

#endif // NETWORK_HOST_NAME_HPP
