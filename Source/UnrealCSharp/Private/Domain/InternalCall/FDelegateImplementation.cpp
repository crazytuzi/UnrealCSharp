﻿#include "Domain/InternalCall/FDelegateImplementation.h"
#include "Registry/FCSharpBind.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FDelegateHelper.h"
#include "Macro/NamespaceMacro.h"
#include "Async/Async.h"

struct FRegisterDelegate
{
	FRegisterDelegate()
	{
		FClassBuilder(TEXT("Delegate"), NAMESPACE_LIBRARY)
			.Function("Register", FDelegateImplementation::Delegate_RegisterImplementation)
			.Function("UnRegister", FDelegateImplementation::Delegate_UnRegisterImplementation)
			.Function("Bind", FDelegateImplementation::Delegate_BindImplementation)
			.Function("IsBound", FDelegateImplementation::Delegate_IsBoundImplementation)
			.Function("UnBind", FDelegateImplementation::Delegate_UnBindImplementation)
			.Function("Clear", FDelegateImplementation::Delegate_ClearImplementation)
			.Function("Execute", FDelegateImplementation::Delegate_ExecuteImplementation)
			.Register();
	}
};

static FRegisterDelegate RegisterDelegate;

void FDelegateImplementation::Delegate_RegisterImplementation(MonoObject* InMonoObject)
{
	FCSharpBind::Bind<FDelegateHelper>(InMonoObject);
}

void FDelegateImplementation::Delegate_UnRegisterImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	AsyncTask(ENamedThreads::GameThread, [InGarbageCollectionHandle]
	{
		(void)FCSharpEnvironment::GetEnvironment().RemoveDelegateReference<FDelegateHelper>(InGarbageCollectionHandle);
	});
}

void FDelegateImplementation::Delegate_BindImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                          MonoObject* InDelegate)
{
	if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
		InGarbageCollectionHandle))
	{
		DelegateHelper->Bind(InDelegate);
	}
}

bool FDelegateImplementation::Delegate_IsBoundImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
		InGarbageCollectionHandle))
	{
		return DelegateHelper->IsBound();
	}

	return false;
}

void FDelegateImplementation::Delegate_UnBindImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
		InGarbageCollectionHandle))
	{
		DelegateHelper->UnBind();
	}
}

void FDelegateImplementation::Delegate_ClearImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
		InGarbageCollectionHandle))
	{
		DelegateHelper->Clear();
	}
}

void FDelegateImplementation::Delegate_ExecuteImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                             MonoObject** ReturnValue, MonoObject** OutValue,
                                                             MonoArray* InValue)
{
	if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
		InGarbageCollectionHandle))
	{
		DelegateHelper->Execute(ReturnValue, OutValue, InValue);
	}
}
