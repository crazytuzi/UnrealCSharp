#include "Domain/InternalCall/FMulticastDelegateImplementation.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FMulticastDelegateHelper.h"
#include "Macro/NamespaceMacro.h"
#include "Async/Async.h"
#include "Registry/FCSharpBind.h"

struct FRegisterMulticastDelegate
{
	FRegisterMulticastDelegate()
	{
		FClassBuilder(TEXT("MulticastDelegate"), NAMESPACE_LIBRARY)
			.Function("Register", FMulticastDelegateImplementation::MulticastDelegate_UnRegisterImplementation)
			.Function("UnRegister", FMulticastDelegateImplementation::MulticastDelegate_RegisterImplementation)
			.Function("Contains", FMulticastDelegateImplementation::MulticastDelegate_ContainsImplementation)
			.Function("IsBound", FMulticastDelegateImplementation::MulticastDelegate_IsBoundImplementation)
			.Function("Contains", FMulticastDelegateImplementation::MulticastDelegate_ContainsImplementation)
			.Function("Add", FMulticastDelegateImplementation::MulticastDelegate_AddImplementation)
			.Function("AddUnique", FMulticastDelegateImplementation::MulticastDelegate_AddUniqueImplementation)
			.Function("Remove", FMulticastDelegateImplementation::MulticastDelegate_RemoveImplementation)
			.Function("RemoveAll", FMulticastDelegateImplementation::MulticastDelegate_RemoveAllImplementation)
			.Function("Clear", FMulticastDelegateImplementation::MulticastDelegate_ClearImplementation)
			.Function("Broadcast", FMulticastDelegateImplementation::MulticastDelegate_BroadcastImplementation)
			.Register();
	}
};

static FRegisterMulticastDelegate RegisterMulticastDelegate;

void FMulticastDelegateImplementation::MulticastDelegate_RegisterImplementation(MonoObject* InMonoObject)
{
	FCSharpBind::Bind<FMulticastDelegateHelper>(InMonoObject);
}

void FMulticastDelegateImplementation::MulticastDelegate_UnRegisterImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	AsyncTask(ENamedThreads::GameThread, [InGarbageCollectionHandle]
	{
		(void)FCSharpEnvironment::GetEnvironment().RemoveDelegateReference(InGarbageCollectionHandle);
	});
}

bool FMulticastDelegateImplementation::MulticastDelegate_IsBoundImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
		FMulticastDelegateHelper>(InGarbageCollectionHandle))
	{
		return MulticastDelegateHelper->IsBound();
	}

	return false;
}

bool FMulticastDelegateImplementation::MulticastDelegate_ContainsImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InDelegate)
{
	if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
		FMulticastDelegateHelper>(InGarbageCollectionHandle))
	{
		return MulticastDelegateHelper->Contains(InDelegate);
	}

	return false;
}

void FMulticastDelegateImplementation::MulticastDelegate_AddImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InDelegate)
{
	if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
		FMulticastDelegateHelper>(InGarbageCollectionHandle))
	{
		return MulticastDelegateHelper->Add(InDelegate);
	}
}

void FMulticastDelegateImplementation::MulticastDelegate_AddUniqueImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InDelegate)
{
	if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
		FMulticastDelegateHelper>(InGarbageCollectionHandle))
	{
		return MulticastDelegateHelper->AddUnique(InDelegate);
	}
}

void FMulticastDelegateImplementation::MulticastDelegate_RemoveImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InDelegate)
{
	if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
		FMulticastDelegateHelper>(InGarbageCollectionHandle))
	{
		return MulticastDelegateHelper->Remove(InDelegate);
	}
}

void FMulticastDelegateImplementation::MulticastDelegate_RemoveAllImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InObject)
{
	if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
		FMulticastDelegateHelper>(InGarbageCollectionHandle))
	{
		return MulticastDelegateHelper->RemoveAll(InObject);
	}
}

void FMulticastDelegateImplementation::MulticastDelegate_ClearImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
		FMulticastDelegateHelper>(InGarbageCollectionHandle))
	{
		return MulticastDelegateHelper->Clear();
	}
}

void FMulticastDelegateImplementation::MulticastDelegate_BroadcastImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue, MonoArray* InValue)
{
	if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
		FMulticastDelegateHelper>(InGarbageCollectionHandle))
	{
		return MulticastDelegateHelper->Broadcast(OutValue, InValue);
	}
}
