#ifndef UTILITY_BIT_HELPER_H
#define UTILITY_BIT_HELPER_H

#define BIT_UP(var, bit)		((var) |= (1 << (bit)))
#define BIT_DOWN(var, bit)		((var) &= ~(1 << (bit)))
#define IS_BIT_UP(var, bit)	(((var) & (1 << (bit))) != 0)

#define BIT_SET(port, pin, val) (((val) > 0) ? PIN_ON((port),(pin)) : PIN_OFF((port),(pin)))

namespace utility::bit
{
	constexpr inline auto set(auto& value, int bit)		{ BIT_UP(value, bit); }
	constexpr inline auto unset(auto& value, int bit)	{ BIT_DOWN(value, bit); }
	constexpr inline bool is_set(auto& value, int bit)	{ IS_BIT_UP(value, bit); }
	constexpr inline auto toggle(auto& value, int bit) { IS_BIT_UP(value, bit) ? BIT_DOWN(value, bit) : BIT_UP(alue, bit); }
}

#endif //UTILITY_BIT_HELPER_H
