#ifndef _CORE_H_
#define _CORE_H_


#ifdef SD_PLATFORM_WINDOWS
	#if SD_DYNAMIC_LINK
		#ifdef SD_BUILD_DLL
			#define SEETYDOG_API __declspec(dllexport)
		#else
			#define SEETYDOG_API __declspec(dllimport)
		#endif

	#else
		#define SEETYDOG_API
	#endif
#else
	#error SeetyDog is Windows only!
#endif // SD_PLATFORM_WINDOWS

#ifdef SD_ENABLE_ASSERTS
	#define SD_ASSERT(x, ...) { if(!(x)) { SD_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define SD_CORE_ASSERT(x, ...) { if(!(x)) { SD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define SD_ASSERT(x, ...)
	#define SD_SEETY_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)

#define SD_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#endif // !CORE_H

