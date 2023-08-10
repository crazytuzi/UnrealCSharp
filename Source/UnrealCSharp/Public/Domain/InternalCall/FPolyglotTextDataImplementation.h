#pragma once

#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

class FPolyglotTextDataImplementation
{
public:
	static bool PolyglotTextData_IsValidImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                   MonoObject** OutFailureReason);

	static void PolyglotTextData_SetNativeCultureImplementation(
		const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InNativeCulture);

	static void PolyglotTextData_GetNativeCultureImplementation(
		const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue);

	static void PolyglotTextData_ResolveNativeCultureImplementation(
		const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue);

	static void PolyglotTextData_SetIdentityImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                       MonoObject* InNamespace, MonoObject* InKey);

	static void PolyglotTextData_GetIdentityImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                       MonoObject** OutNamespace, MonoObject** OutKey);

	static void PolyglotTextData_GetNamespaceImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                        MonoObject** OutValue);

	static void PolyglotTextData_GetKeyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                  MonoObject** OutValue);

	static void PolyglotTextData_SetNativeStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                           MonoObject* InNativeString);

	static void PolyglotTextData_GetNativeStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                           MonoObject** OutValue);

	static void PolyglotTextData_AddLocalizedStringImplementation(
		const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InCulture, MonoObject* InLocalizedString);

	static void PolyglotTextData_RemoveLocalizedStringImplementation(
		const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InCulture);

	static bool PolyglotTextData_GetLocalizedStringImplementation(
		const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InCulture,
		MonoObject** OutLocalizedString);

	static void PolyglotTextData_ClearLocalizedStringsImplementation(
		const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void PolyglotTextData_SetIsMinimalPatchImplementation(
		const FGarbageCollectionHandle InGarbageCollectionHandle, bool InIsMinimalPatch);

	static bool PolyglotTextData_GetIsMinimalPatchImplementation(
		const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void PolyglotTextData_GetTextImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                   MonoObject** OutValue);
};
