#pragma once

#define ASSEMBLY_CORE_LIB_NAME FString(TEXT("System.Private.CoreLib"))

#define ASSEMBLY_RESOURCE_SUFFIX FString(TEXT(".resources"))

#define ASSEMBLY_CORE_LIB_RESOURCE_NAME FString::Printf(TEXT("%s%s"), *ASSEMBLY_CORE_LIB_NAME, *ASSEMBLY_RESOURCE_SUFFIX)
