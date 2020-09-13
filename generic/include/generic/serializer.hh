/**
 * @author   Казаков Андрей 
 * @date     18.09.19.
 */

#ifndef GENERIC_SERIALIZER_HH
#define GENERIC_SERIALIZER_HH

#include <iostream>
#include <array>
#include <vector>

namespace std
{
	inline std::string to_string(std::string v) { return v; }

	template<typename T>
	inline std::string to_string(const T *const p, size_t n) noexcept
	{
		std::string tmp(std::to_string(*(p + 1)));
		for(int i = 1; i < n; ++i)
			tmp += "," + std::to_string(*((int *)(p + i)));
		return tmp;
		return "";
	}

	template<class T, size_t N>
	inline std::string to_string(T (&data)[N]) noexcept
	{
		return to_string(data, N);
	}

	template<class T, size_t N>
	inline std::string to_string(const std::array<T, N> &data) noexcept
	{
		return to_string(data, N);;
	}

	template<class T, class Allocator>
	inline std::string to_string(std::vector<T, Allocator> &data) noexcept
	{
		return to_string(data, data.size());
	}
}

namespace generic
{
	namespace type_traits
	{
		template<typename T>
		struct field_count { enum { value = 0 }; };

		template<typename T, int Index>
		struct access
		{
			static inline std::string get_name();
			template<typename U>
			static inline U get(T v);
		};
	}

	struct json
	{
		static inline const char *opener = "{";
		static inline const char *closer = "}";
		static inline const char *separator = ",";

		template<typename T, int Index>
		static inline std::string process(T v)
		{
			auto g = type_traits::access<T, Index>::get(v);

			return std::string("\"").append(type_traits::access<T, Index>::get_name())
					.append("\":\"")
					.append(std::to_string(type_traits::access<T, Index>::get(v)))
					.append("\"");
		}
	};

	struct xml
	{
		static inline const char *opener = "";
		static inline const char *closer = "";
		static inline const char *separator = "";

		template<typename T, int Index>
		static inline std::string process(T v)
		{
			return std::string("<").append(type_traits::access<T, Index>::get_name()).append(">")
					.append(std::to_string(type_traits::access<T, Index>::get(v)))
					.append("</").append(type_traits::access<T, Index>::get_name()).append(">");
		}
	};

	template<typename Engine, typename T, int Index = type_traits::field_count<T>::value - 1>
	std::string serialize(T t)
	{
		std::string str;
		if constexpr (Index == type_traits::field_count<T>::value - 1)
			str += Engine::opener;

		str += Engine::template process<T, Index>(t);
		if constexpr (Index > 0)
			str += Engine::separator + serialize<Engine, T, Index - 1>(t);

		if constexpr (Index == 0)
			str += Engine::closer;
		return str;
	}
}

#endif //GENERIC_SERIALIZER_HH
