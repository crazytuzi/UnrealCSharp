#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

class FSoftObjectPathImplementation
{
public:
	static void SoftObjectPath_ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                  MonoObject** OutValue);

	static void SoftObjectPath_GetAssetPathNameImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                          MonoObject** OutValue);

	static void SoftObjectPath_GetAssetPathStringImplementation(
		const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue);

	static void SoftObjectPath_GetSubPathStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                          MonoObject** OutValue);

	static void SoftObjectPath_GetLongPackageNameImplementation(
		const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue);

	static void SoftObjectPath_GetAssetNameImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                      MonoObject** OutValue);

	static void SoftObjectPath_SetPathNameImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                     MonoObject* Path);

	static void SoftObjectPath_SetPathStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                       MonoObject* Path);

	static void SoftObjectPath_ResetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool SoftObjectPath_IsValidImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool SoftObjectPath_IsNullImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool SoftObjectPath_IsAssetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool SoftObjectPath_IsSubobjectImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool SoftObjectPath_EqualityImplementation(const FGarbageCollectionHandle A,
	                                                  const FGarbageCollectionHandle B);

	static bool SoftObjectPath_InequalityImplementation(const FGarbageCollectionHandle A,
	                                                    const FGarbageCollectionHandle B);

	static bool SoftObjectPath_FixupForPIEImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool SoftObjectPath_FixupForPIEInstanceImplementation(
		const FGarbageCollectionHandle InGarbageCollectionHandle, int32 PIEInstance);

	static bool SoftObjectPath_FixupCoreRedirectsImplementation(
		const FGarbageCollectionHandle InGarbageCollectionHandle);

	static int32 SoftObjectPath_GetCurrentTagImplementation();

	static int32 SoftObjectPath_InvalidateTagImplementation();

	static void SoftObjectPath_GetOrCreateIDForObjectImplementation(
		const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue);

	static void SoftObjectPath_AddPIEPackageNameImplementation(MonoObject* NewPIEPackageName);

	static void SoftObjectPath_ClearPIEPackageNamesImplementation();
};
