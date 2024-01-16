﻿#include "Domain/InternalCall/FScriptInterfaceImplementation.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"
#include "Async/Async.h"

struct FRegisterScriptInterface
{
	FRegisterScriptInterface()
	{
		FClassBuilder(TEXT("ScriptInterface"), NAMESPACE_LIBRARY)
			.Function("Register", FScriptInterfaceImplementation::ScriptInterface_RegisterImplementation)
			.Function("Identical", FScriptInterfaceImplementation::ScriptInterface_IdenticalImplementation)
			.Function("UnRegister", FScriptInterfaceImplementation::ScriptInterface_UnRegisterImplementation)
			.Function("GetObject", FScriptInterfaceImplementation::ScriptInterface_GetObjectImplementation)
			.Register();
	}
};

static FRegisterScriptInterface RegisterScriptInterface;

void FScriptInterfaceImplementation::ScriptInterface_RegisterImplementation(
	MonoObject* InMonoObject, const MonoObject* InObject, MonoString* InInterfaceName)
{
	const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject);

	const auto ScriptInterface = new TScriptInterface<IInterface>(FoundObject);

	FCSharpEnvironment::GetEnvironment().AddMultiReference<TScriptInterface<IInterface>>(InMonoObject, ScriptInterface);
}

bool FScriptInterfaceImplementation::ScriptInterface_IdenticalImplementation(const FGarbageCollectionHandle InA,
                                                                             const FGarbageCollectionHandle InB)
{
	if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetMulti<TScriptInterface<IInterface>>(InA))
	{
		if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetMulti<TScriptInterface<IInterface>>(InB))
		{
			return *FoundA == *FoundB;
		}
	}

	return false;
}

void FScriptInterfaceImplementation::ScriptInterface_UnRegisterImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	AsyncTask(ENamedThreads::GameThread, [InGarbageCollectionHandle]
	{
		(void)FCSharpEnvironment::GetEnvironment().RemoveMultiReference<TScriptInterface<IInterface>>(
			InGarbageCollectionHandle);
	});
}

void FScriptInterfaceImplementation::ScriptInterface_GetObjectImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Multi = FCSharpEnvironment::GetEnvironment().GetMulti<TScriptInterface<IInterface>>(
		InGarbageCollectionHandle);

	*OutValue = FCSharpEnvironment::GetEnvironment().Bind(Multi->GetObject());
}
