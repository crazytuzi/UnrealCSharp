#pragma once

#if defined(_MSC_VER)
#elif defined(__clang__)

#define PRAGMA_DISABLE_DANGLING_WARNINGS \
	_Pragma("clang diagnostic push") \
	_Pragma("clang diagnostic ignored \"-Wdangling\"")

#define PRAGMA_ENABLE_DANGLING_WARNINGS \
	_Pragma("clang diagnostic pop")

#endif

#ifndef PRAGMA_DISABLE_DANGLING_WARNINGS
#define PRAGMA_DISABLE_DANGLING_WARNINGS
#endif

#ifndef PRAGMA_ENABLE_DANGLING_WARNINGS
#define PRAGMA_ENABLE_DANGLING_WARNINGS
#endif
