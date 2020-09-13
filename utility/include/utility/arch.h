#ifndef UTILITY_ARCH_H
#define UTILITY_ARCH_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__WIN32__) || \
	 defined(WIN64) || defined(_WIN64) || defined(__WIN64) || defined(__WIN64__) || \
	 defined(__CYGWIN__) || defined(__CYGWIN32__) || defined(__MINGW32__) || defined(__MINGW64__)

	#define OS_WIN
	#define OS "Windows"

	#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) || defined(__WIN32__) || \
	 	 defined(__CYGWIN__) || defined(__CYGWIN32__) || defined(__MINGW32__)

		#define X32
		#define ARCH "x32"

	#elif defined(WIN64) || defined(_WIN64) || defined(__WIN64) || defined(__WIN64__) || defined(__MINGW64__)

		#define X64
		#define ARCH "x64"

	#endif

#elif defined(__linux__) || defined(__linux) || defined(__gnu_linux)

	#define OS_LINUX
	#define OS "Linux"

	#if defined(__i386__)

		#define X32
		#define ARCH "x32"

	#elif defined(__x86_64__)

		#define X64
		#define ARCH "x64"

	#endif

#elif defined(__unix) || defined(__unix__) || defined(__APPLE__) && defined(__MACH__)

#include <sys/param.h>
	#if defined(BSD)
		#define OS "BSD"
		#if defined(__DragonFly__)
			#define OS "DragonFly"
		#elif defined(__FreeBSD__)
			#define OS "FreeBSD"
		#elif defined(__NetBSD__)
			#define OS "NetBSD"
		#elif defined(__OpenBSD__)
			#define OS "OpenBSD"
		#endif
	#endif
	#define OS_UNIX

	#if defined(__i386__)
		#define X32
		#define ARCH "x32"
	#elif defined(__x86_64__)
		#define X64
		#define ARCH "x64"
	#endif

#elif defined(__hpux)
	#define OS_UNIX
	#define OS "HP-UX"
#elif defined(_AIX)
	#define OS_UNIX
	#define OS "AIX"
#elif defined(__APPLE__) && defined(__MACH__)

#include <TargetConditionals.h>
	#if TARGET_IPHONE_SIMULATOR == 1
		#define OS "ios"
	#elif TARGET_OS_IPHONE == 1
		#define OS "ios"
	#elif TARGET_OS_MAC == 1
		#define OS "osx"
	#endif
	#define OS_UNIX

#elif defined(__sun) && defined(__SVR4)
	#define OS_UNIX
	#define OS "solaris"
#else
	#define OS "Undefined"
#endif

#define CURRENT_BYTE_ORDER       (*(int*)"\x01\x02\x03\x04")
#define LITTLE_ENDIAN_BYTE_ORDER 0x04030201
#define BIG_ENDIAN_BYTE_ORDER    0x01020304
#define PDP_ENDIAN_BYTE_ORDER    0x02010403

#define IS_LITTLE_ENDIAN (CURRENT_BYTE_ORDER == LITTLE_ENDIAN_BYTE_ORDER)
#define IS_BIG_ENDIAN    (CURRENT_BYTE_ORDER == BIG_ENDIAN_BYTE_ORDER)
#define IS_PDP_ENDIAN    (CURRENT_BYTE_ORDER == PDP_ENDIAN_BYTE_ORDER)

namespace utility::os
{
	constexpr inline auto name = OS;
	constexpr inline auto arch = ARCH;

	enum class endianness { little, big };

	constexpr inline auto get_endianness() { return IS_LITTLE_ENDIAN ? endianness::little : endianness::big; }

	constexpr inline auto endian = get_endianness();
}

#endif //UTILITY_ARCH_H
