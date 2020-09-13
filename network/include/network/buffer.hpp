#ifndef NETWORK_BUFFER_HPP
#define NETWORK_BUFFER_HPP

#include <array>
#include <vector>

namespace network
{
	class mutable_buffer
	{
	  public:
		constexpr mutable_buffer() : data_m(nullptr), size_m(0) {}
		constexpr mutable_buffer(char* data, size_t size) : data_m(data), size_m(size) {}

		constexpr char* data() noexcept { return data_m; }
		constexpr size_t size() const noexcept { return size_m; }

	  private:
		char* data_m;
		size_t size_m;
	};

	class immutable_buffer
	{
	  public:
		constexpr immutable_buffer() : data_m(nullptr), size_m(0) {}
		constexpr immutable_buffer(const char* data, size_t size) : data_m(data), size_m(size) {}

		constexpr const char* data() const noexcept { return data_m; }
		constexpr size_t size() const noexcept { return size_m; }

	  private:
		const char* data_m;
		size_t size_m;
	};

	mutable_buffer buffer(void* p, size_t n) noexcept { return {reinterpret_cast<char*>(p), n}; }

	immutable_buffer buffer(const void* p, size_t n) noexcept { return {reinterpret_cast<const char*>(p), n}; }

	template<class T, size_t N>
	mutable_buffer buffer(T (&data)[N]) noexcept
	{
		return {data, N};
	}

	template<class T, size_t N>
	immutable_buffer buffer(const T (&data)[N]) noexcept
	{
		return {data, N};
	}

	template<class T, size_t N>
	mutable_buffer buffer(std::array<T, N>& data) noexcept
	{
		return {data, N};
	}

	template<class T, size_t N>
	immutable_buffer buffer(std::array<const T, N>& data) noexcept
	{
		return {data, N};
	}

	template<class T, size_t N>
	immutable_buffer buffer(const std::array<T, N>& data) noexcept
	{
		return {data, N};
	}

	template<class T, class Allocator>
	mutable_buffer buffer(std::vector<T, Allocator>& data) noexcept
	{
		return {data, data.capacity()};
	}

	template<class T, class Allocator>
	immutable_buffer buffer(const std::vector<T, Allocator>& data) noexcept
	{
		return {data, data.capacity()};
	}

	template<class CharT, class Traits, class Allocator>
	mutable_buffer buffer(std::basic_string<CharT, Traits, Allocator>& str) noexcept
	{
		return {str.data(), str.size()};
	}

	template<class CharT, class Traits, class Allocator>
	immutable_buffer buffer(const std::basic_string<CharT, Traits, Allocator>& data) noexcept
	{
		return {data, data.size()};
	}

	template<class CharT, class Traits>
	immutable_buffer buffer(std::basic_string_view<CharT, Traits> data) noexcept
	{
		return {data, data.size()};
	}

	template<class T, size_t N>
	mutable_buffer buffer(T (&data)[N], size_t n) noexcept
	{
		return {data, n};
	}

	template<class T, size_t N>
	immutable_buffer buffer(const T (&data)[N], size_t n) noexcept
	{
		return {data, n};
	}

	template<class T, size_t N>
	mutable_buffer buffer(std::array<T, N>& data, size_t n) noexcept
	{
		return {data, n};
	}

	template<class T, size_t N>
	immutable_buffer buffer(std::array<const T, N>& data, size_t n) noexcept
	{
		return {data, n};
	}

	template<class T, size_t N>
	immutable_buffer buffer(const std::array<T, N>& data, size_t n) noexcept
	{
		return {data, n};
	}

	template<class T, class Allocator>
	mutable_buffer buffer(std::vector<T, Allocator>& data, size_t n) noexcept
	{
		return {data, n};
	}

	template<class T, class Allocator>
	immutable_buffer buffer(const std::vector<T, Allocator>& data, size_t n) noexcept
	{
		return {data, n};
	}

	template<class CharT, class Traits, class Allocator>
	mutable_buffer buffer(std::basic_string<CharT, Traits, Allocator>& data, size_t n) noexcept
	{
		return {data, n};
	}

	template<class CharT, class Traits, class Allocator>
	immutable_buffer buffer(const std::basic_string<CharT, Traits, Allocator>& data, size_t n) noexcept
	{
		return {data, n};
	}

	template<class CharT, class Traits>
	immutable_buffer buffer(std::basic_string_view<CharT, Traits> data, size_t n) noexcept
	{
		return {data, n};
	}

	template<class T, class Allocator>
	class dynamic_vector_buffer
	{
	  public:
		using const_buffers_type	= immutable_buffer;
		using mutable_buffers_type = mutable_buffer;

		explicit dynamic_vector_buffer(std::vector<T, Allocator>& vec) noexcept : vec_(vec), max_size_(vec.capacity()) {}
		dynamic_vector_buffer(std::vector<T, Allocator>& vec, size_t maximum_size) noexcept : vec_(vec), max_size_(maximum_size) {}
		dynamic_vector_buffer(dynamic_vector_buffer&&) noexcept = default;

		size_t size() const noexcept { return vec_.size(); }
		size_t max_size() const noexcept { return max_size_; }
		size_t capacity() const noexcept { return vec_.capacity(); }
		const_buffers_type data() const noexcept { return {vec_, max_size_}; }
		mutable_buffers_type prepare(size_t n) { return {vec_, n}; }

	  private:
		std::vector<T, Allocator>& vec_;
		size_t size_ = 0;
		const size_t max_size_;
	};

	template<class CharT, class Traits, class Allocator>
	class dynamic_string_buffer
	{
	  public:
		using const_buffers_type	= immutable_buffer;
		using mutable_buffers_type = mutable_buffer;

		explicit dynamic_string_buffer(std::basic_string<CharT, Traits, Allocator>& str) noexcept : str_(str), max_size_(str.size())
		{}
		dynamic_string_buffer(std::basic_string<CharT, Traits, Allocator>& str, size_t maximum_size) noexcept :
			str_(str), max_size_(maximum_size)
		{}
		dynamic_string_buffer(dynamic_string_buffer&&) noexcept = default;

		size_t size() const noexcept { return size_; }
		size_t max_size() const noexcept { return max_size_; }
		size_t capacity() const noexcept { return str_.capacity(); }
		const_buffers_type data() const noexcept { return {str_.data(), max_size_}; }

	  private:
		std::basic_string<CharT, Traits, Allocator>& str_;
		size_t size_ = 0;
		const size_t max_size_;
	};
} // namespace network

#endif // NETWORK_BUFFER_HPP
