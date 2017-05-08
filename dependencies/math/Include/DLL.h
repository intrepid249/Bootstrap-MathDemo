#pragma once

#ifdef MATHLIB_EXPORTS
	#define LIB_API __declspec(dllexport)
#else
	#define LIB_API
#endif // MATHLIB_EXPORTS