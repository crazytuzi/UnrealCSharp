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

void FMulticastDelegateImplementation::MulticastDelegate_UnRegisterImplementation(const MonoObject* InMonoObject)
{
	AsyncTask(ENamedThreads::GameThread, [InMonoObject]
	{
		(void)FCSharpEnvironment::GetEnvironment().RemoveDelegateReference(InMonoObject);
	});
}

bool FMulticastDelegateImplementation::MulticastDelegate_IsBoundImplementation(const MonoObject* InMonoObject)
{
	if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
		FMulticastDelegateHelper>(InMonoObject))
	{
		return MulticastDelegateHelper->IsBound();
	}

	return false;
}

bool FMulticastDelegateImplementation::MulticastDelegate_ContainsImplementation(
	const MonoObject* InMonoObject, MonoObject* InDelegate)
{
	if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
		FMulticastDelegateHelper>(InMonoObject))
	{
		return MulticastDelegateHelper->Contains(InDelegate);
	}

	return false;
}

void FMulticastDelegateImplementation::MulticastDelegate_AddImplementation(
	const MonoObject* InMonoObject, MonoObject* InDelegate)
{
	if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
		FMulticastDelegateHelper>(InMonoObject))
	{
		return MulticastDelegateHelper->Add(InDelegate);
	}
}

void FMulticastDelegateImplementation::MulticastDelegate_AddUniqueImplementation(
	const MonoObject* InMonoObject, MonoObject* InDelegate)
{
	if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
		FMulticastDelegateHelper>(InMonoObject))
	{
		return MulticastDelegateHelper->AddUnique(InDelegate);
	}
}

void FMulticastDelegateImplementation::MulticastDelegate_RemoveImplementation(
	const MonoObject* InMonoObject, MonoObject* InDelegate)
{
	if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
		FMulticastDelegateHelper>(InMonoObject))
	{
		return MulticastDelegateHelper->Remove(InDelegate);
	}
}

void FMulticastDelegateImplementation::MulticastDelegate_RemoveAllImplementation(
	const MonoObject* InMonoObject, MonoObject* InObject)
{
	if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
		FMulticastDelegateHelper>(InMonoObject))
	{
		return MulticastDelegateHelper->RemoveAll(InObject);
	}
}

void FMulticastDelegateImplementation::MulticastDelegate_ClearImplementation(const MonoObject* InMonoObject)
{
	if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
		FMulticastDelegateHelper>(InMonoObject))
	{
		return MulticastDelegateHelper->Clear();
	}
}

void FMulticastDelegateImplementation::MulticastDelegate_BroadcastImplementation(
	const MonoObject* InMonoObject, MonoObject** OutValue, MonoArray* InValue)
{
	if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
		FMulticastDelegateHelper>(InMonoObject))
	{
		return MulticastDelegateHelper->Broadcast(OutValue, InValue);
	}
}
