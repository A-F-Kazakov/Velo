#ifndef VELO_GENERIC_BIG_ENDIAN_HPP
#define VELO_GENERIC_BIG_ENDIAN_HPP

#include <cstdint>

namespace generic
{
	template<typename T>
	struct little_endian;

	template<typename T>
	struct big_endian
	{
		union
		{
			uint8_t bytes[sizeof(T)];
			T raw_value;
		};

		big_endian(T t = T()) { operator=(t); }

		big_endian(const big_endian<T> &t) { raw_value = t.raw_value; }

		big_endian(const little_endian<T> &t)
		{
			for(unsigned i = 0; i < sizeof(T); ++i)
				bytes[i] = t.bytes[sizeof(T) - 1 - i];
		}

		operator const T() const
		{
			T t = T();
			for(unsigned i = 0; i < sizeof(T); i++)
				t |= T(bytes[sizeof(T) - 1 - i]) << (i << 3);
			return t;
		}

		const T operator=(const T t)
		{
			for(unsigned i = 0; i < sizeof(T); ++i)
				bytes[sizeof(T) - 1 - i] = t >> (i << 3);
			return t;
		}

		const T operator+=(const T t) { return (*this = *this + t); }

		const T operator-=(const T t) { return (*this = *this - t); }

		const T operator*=(const T t) { return (*this = *this * t); }

		const T operator/=(const T t) { return (*this = *this / t); }

		const T operator%=(const T t) { return (*this = *this % t); }

		big_endian<T> operator++(int)
		{
			big_endian<T> tmp(*this);
			operator++();
			return tmp;
		}

		big_endian<T> &operator++()
		{
			for(unsigned i = 0; i < sizeof(T); ++i)
			{
				++bytes[sizeof(T) - 1 - i];
				if(bytes[sizeof(T) - 1 - i] != 0)
					break;
			}
			return (*this);
		}

		big_endian<T> operator--(int)
		{
			big_endian<T> tmp(*this);
			operator--();
			return tmp;
		}

		big_endian<T> &operator--()
		{
			for(unsigned i = 0; i < sizeof(T); ++i)
			{
				--bytes[sizeof(T) - 1 - i];
				if(bytes[sizeof(T) - 1 - i] != (T)(-1))
					break;
			}
			return (*this);
		}
	};
}

#endif //GENERIC_BIG_ENDIAN_H
