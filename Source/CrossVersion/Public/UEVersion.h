#pragma once

#include "Misc/EngineVersionComparison.h"

#define UE_VERSION_START(MajorVersion, MinorVersion, PatchVersion) \
	UE_GREATER_SORT(ENGINE_MAJOR_VERSION, MajorVersion, UE_GREATER_SORT(ENGINE_MINOR_VERSION, MinorVersion, UE_GREATER_SORT(ENGINE_PATCH_VERSION, PatchVersion, true)))

#define UE_T_IS_T_ENUM_AS_BYTE !UE_VERSION_START(5, 2, 0)

#define UE_T_BASE_STRUCTURE_F_INT_POINT !UE_VERSION_START(5, 1, 0)

#define UE_CLASS_ADD_REFERENCED_OBJECTS !UE_VERSION_START(5, 1, 0)

#define UE_FILTER_CLASS_PATHS UE_VERSION_START(5, 1, 0)

#define UE_BOX_2D_EXPAND_BY_VECTOR2 UE_VERSION_START(5, 1, 0)

#define UE_GUID_TO_STRING !UE_VERSION_START(5, 1, 0)

#define UE_DATETIME_PLUS !UE_VERSION_START(5, 1, 0)

#define STD_CPP_11 __cplusplus >= 201103L

#define STD_CPP_14 __cplusplus >= 201402L

#define STD_CPP_17 __cplusplus >= 201703L

#define STD_CPP_20 __cplusplus >= 202002L
