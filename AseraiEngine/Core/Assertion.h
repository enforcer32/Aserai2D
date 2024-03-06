#pragma once

#include "AseraiEngine/Core/Logger.h"

#if defined ASERAI_DEBUG || ASERAI_ENGINE_DEBUG
	#ifdef ASERAI_PLATFORM_WINDOWS
		#define ASERAI_DEBUGBREAK() __debugbreak()	
	#else
		#error "Platform doesnt support debugbreak"
	#endif

	#define ASERAI_ENABLE_ASSERTS
#else
	#define ASERAI_DEBUGBREAK()
#endif


#ifdef ASERAI_ENABLE_ASSERTS
	#define ASERAI_ASSERT(x, msg) { if(!(x)) { ASERAI_LOG_ERROR("Assertion Error: {}, File: {}, Line: {}", msg, __FILE__, __LINE__); ASERAI_DEBUGBREAK(); } }
#else
	#define ASERAI_ASSERT(...)
#endif
