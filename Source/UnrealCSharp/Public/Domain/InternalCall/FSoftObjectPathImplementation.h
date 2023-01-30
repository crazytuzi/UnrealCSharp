#pragma once

#include "mono/metadata/object-forward.h"

class FSoftObjectPathImplementation
{
public:
	static void SoftObjectPath_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void SoftObjectPath_GetAssetPathNameImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void SoftObjectPath_GetAssetPathStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void SoftObjectPath_GetSubPathStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void SoftObjectPath_GetLongPackageNameImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void SoftObjectPath_GetAssetNameImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void SoftObjectPath_SetPathNameImplementation(const MonoObject* InMonoObject, MonoObject* Path);

	static void SoftObjectPath_SetPathStringImplementation(const MonoObject* InMonoObject, MonoObject* Path);

	static void SoftObjectPath_ResetImplementation(const MonoObject* InMonoObject);

	static bool SoftObjectPath_IsValidImplementation(const MonoObject* InMonoObject);

	static bool SoftObjectPath_IsNullImplementation(const MonoObject* InMonoObject);

	static bool SoftObjectPath_IsAssetImplementation(const MonoObject* InMonoObject);

	static bool SoftObjectPath_IsSubobjectImplementation(const MonoObject* InMonoObject);

	static bool SoftObjectPath_EqualityImplementation(const MonoObject* A, const MonoObject* B);

	static bool SoftObjectPath_InequalityImplementation(const MonoObject* A, const MonoObject* B);

	static bool SoftObjectPath_FixupForPIEImplementation(const MonoObject* InMonoObject);

	static bool SoftObjectPath_FixupForPIEInstanceImplementation(const MonoObject* InMonoObject, int32 PIEInstance);

	static bool SoftObjectPath_FixupCoreRedirectsImplementation(const MonoObject* InMonoObject);

	static int32 SoftObjectPath_GetCurrentTagImplementation();

	static int32 SoftObjectPath_InvalidateTagImplementation();

	static void SoftObjectPath_GetOrCreateIDForObjectImplementation(const MonoObject* InMonoObject,
	                                                                MonoObject** OutValue);

	static void SoftObjectPath_AddPIEPackageNameImplementation(MonoObject* NewPIEPackageName);

	static void SoftObjectPath_ClearPIEPackageNamesImplementation();
};
