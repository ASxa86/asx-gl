#pragma once

#include <source_location>
#include <string_view>

#ifdef NDEBUG
#define glCheck(Func) Func
#else
#define glCheck(Func)        \
	do                       \
	{                        \
		Func;                \
		GLCheckError(#Func); \
	} while(false)
#endif

namespace asx
{
	void GLCheckError(std::string_view expression, std::source_location x = std::source_location::current());
}
