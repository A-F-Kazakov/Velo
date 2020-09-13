#ifndef NETWORK_ERROR_HPP
#define NETWORK_ERROR_HPP

#include <cstring>
#include <system_error>

namespace network::error
{
	class address_category_impl : public std::error_category
	{
	  public:
		const char* name() const noexcept override { return "Network/address"; }
		std::string message(int) const override { return std::strerror(errno); }
	};

	const std::error_category& address_category()
	{
		static address_category_impl instance;
		return instance;
	}

	class address : public std::system_error
	{
	  public:
		explicit address(int error, const char* what) : std::system_error(error, address_category(), what) {}
	};

	class socket_category_impl : public std::error_category
	{
	  public:
		const char* name() const noexcept override { return "Network/socket"; }
		std::string message(int) const override { return std::strerror(errno); }
	};

	const std::error_category& socket_category()
	{
		static socket_category_impl instance;
		return instance;
	}

	class socket : public std::system_error
	{
	  public:
		using system_error::system_error;
		explicit socket(int error, const char* what) : std::system_error(error, socket_category(), what) {}
	};
} // namespace network::error

#endif // NETWORK_ERROR_HPP
