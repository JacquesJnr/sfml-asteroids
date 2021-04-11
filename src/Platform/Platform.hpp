#ifndef UTIL_PLATFORM_HPP
#define UTIL_PLATFORM_HPP

#if defined(_WIN32)
	#include "Platform/Win32/WindowsPlatform.hpp"
#endif

namespace util
{
#if defined(_WIN32)
using Platform = WindowsPlatform;
#endif
}
#endif // UTIL_PLATFORM_HPP
