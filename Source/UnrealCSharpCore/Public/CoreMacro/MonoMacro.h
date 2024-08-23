#pragma once

#define ARRAY_GET(array, type, index) mono_array_get(array, type, index)

#define ARRAY_SET(array, type, index, value) mono_array_set(array, type, index, value)

#define ASSEMBLY_CORE_LIB_NAME FString(TEXT("System.Private.CoreLib"))

#define ASSEMBLY_RESOURCE_SUFFIX FString(TEXT(".resources"))

#define ASSEMBLY_CORE_LIB_RESOURCE_NAME FString::Printf(TEXT("%s%s"), *ASSEMBLY_CORE_LIB_NAME, *ASSEMBLY_RESOURCE_SUFFIX)
