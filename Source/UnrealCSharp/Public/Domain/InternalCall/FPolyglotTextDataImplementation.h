#pragma once

#include "mono/metadata/object-forward.h"

class FPolyglotTextDataImplementation
{
public:
	static bool PolyglotTextData_IsValidImplementation(const MonoObject* InMonoObject, MonoObject** OutFailureReason);

	static void PolyglotTextData_SetNativeCultureImplementation(const MonoObject* InMonoObject,
	                                                            MonoObject* InNativeCulture);

	static void PolyglotTextData_GetNativeCultureImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void PolyglotTextData_ResolveNativeCultureImplementation(const MonoObject* InMonoObject,
	                                                                MonoObject** OutValue);

	static void PolyglotTextData_SetIdentityImplementation(const MonoObject* InMonoObject, MonoObject* InNamespace,
	                                                       MonoObject* InKey);

	static void PolyglotTextData_GetIdentityImplementation(const MonoObject* InMonoObject, MonoObject** OutNamespace,
	                                                       MonoObject** OutKey);

	static void PolyglotTextData_GetNamespaceImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void PolyglotTextData_GetKeyImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void PolyglotTextData_SetNativeStringImplementation(const MonoObject* InMonoObject,
	                                                           MonoObject* InNativeString);

	static void PolyglotTextData_GetNativeStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void PolyglotTextData_AddLocalizedStringImplementation(const MonoObject* InMonoObject, MonoObject* InCulture,
	                                                              MonoObject* InLocalizedString);

	static void PolyglotTextData_RemoveLocalizedStringImplementation(const MonoObject* InMonoObject,
	                                                                 MonoObject* InCulture);

	static bool PolyglotTextData_GetLocalizedStringImplementation(const MonoObject* InMonoObject, MonoObject* InCulture,
	                                                              MonoObject** OutLocalizedString);

	static void PolyglotTextData_ClearLocalizedStringsImplementation(const MonoObject* InMonoObject);

	static void PolyglotTextData_SetIsMinimalPatchImplementation(const MonoObject* InMonoObject, bool InIsMinimalPatch);

	static bool PolyglotTextData_GetIsMinimalPatchImplementation(const MonoObject* InMonoObject);

	static void PolyglotTextData_GetTextImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);
};
