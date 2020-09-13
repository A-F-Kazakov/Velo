#ifndef NETWORK_BASIC_RESOLVER_RESULTS_HPP
#define NETWORK_BASIC_RESOLVER_RESULTS_HPP

#include "native.hpp"

#include <string>
#include <vector>

namespace network::ip
{
	template<typename Version>
	class basic_resolver_results
	{
	  public:
		using value_type		= Version;
		using container_type = std::vector<value_type>;
		using const_iterator = typename container_type::const_iterator;
		using iterator			= const_iterator;
		using size_type		= std::size_t;

		basic_resolver_results() = default;

		explicit basic_resolver_results(hostent* dta) : hostname_(dta->h_name)
		{
			int i = 0;
			while(dta->h_addr_list[i] != nullptr)
				data.emplace_back(value_type((struct in_addr*)(dta->h_addr_list[i++])));
		};

		basic_resolver_results(const basic_resolver_results&) = delete;
		basic_resolver_results(basic_resolver_results&& other) noexcept : data(other.data) { other.data = nullptr; }

		~basic_resolver_results() noexcept = default;

		basic_resolver_results& operator=(const basic_resolver_results& other) = delete;
		basic_resolver_results& operator													  =(basic_resolver_results&& other) noexcept
		{
			data		  = other.data;
			other.data = nullptr;
			return *this;
		}

		std::string_view hostname() { return hostname_; }

		size_type size() const noexcept { return data.size(); }

		const_iterator begin() const { return data.begin(); }
		const_iterator end() const { return data.end(); }

		const_iterator cbegin() const { return data.cbegin(); }
		const_iterator cend() const { return data.cend(); }

		friend bool operator==(const basic_resolver_results& a, const basic_resolver_results& b) { return a.data == b.data; }

		friend bool operator!=(const basic_resolver_results& a, const basic_resolver_results& b) { return !operator==(a, b); }

	  private:
		container_type data;
		std::string hostname_;
	};
} // namespace network::ip

#endif // NETWORK_BASIC_RESOLVER_RESULTS_HPP
