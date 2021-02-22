#ifndef VELO_GENERIC_LITTLE_ENDIAN_HPP
#define VELO_GENERIC_LITTLE_ENDIAN_HPP

#include <cstdint>

namespace generic
{
	template<typename T>
	struct big_endian;

	template<typename T>
	struct little_endian
	{
		union
		{
			uint8_t bytes[sizeof(T)];
			T raw_value;
		};

		little_endian(T t = T()) { operator=(t); }

		little_endian(const little_endian<T> &t) { raw_value = t.raw_value; }

		little_endian(const big_endian<T> &t)
		{
			for(unsigned i = 0; i < sizeof(T); ++i)
				bytes[i] = t.bytes[sizeof(T) - 1 - i];
		}

		operator const T() const
		{
			T t = T();
			for(unsigned i = 0; i < sizeof(T); ++i)
				t |= T(bytes[i]) << (i << 3);
			return t;
		}

		const T operator=(const T t)
		{
			for(unsigned i = 0; i < sizeof(T); i++)
				bytes[i] = t >> (i << 3);
			return t;
		}

		const T operator+=(const T t) { return (*this = *this + t); }

		const T operator-=(const T t) { return (*this = *this - t); }

		const T operator*=(const T t) { return (*this = *this * t); }

		const T operator/=(const T t) { return (*this = *this / t); }

		const T operator%=(const T t) { return (*this = *this % t); }

		little_endian<T> operator++(int)
		{
			little_endian <T> tmp(*this);
			operator++();
			return tmp;
		}

		little_endian<T> &operator++()
		{
			for(unsigned i = 0; i < sizeof(T); i++)
			{
				++bytes[i];
				if(bytes[i] != 0)
					break;
			}
			return (*this);
		}

		little_endian<T> operator--(int)
		{
			little_endian<T> tmp(*this);
			operator--();
			return tmp;
		}

		little_endian<T> &operator--()
		{
			for(unsigned i = 0; i < sizeof(T); i++)
			{
				--bytes[i];
				if(bytes[i] != (T)(-1))
					break;
			}
			return (*this);
		}
	};
}

#endif //GENERIC_LITTLE_ENDIAN_H
