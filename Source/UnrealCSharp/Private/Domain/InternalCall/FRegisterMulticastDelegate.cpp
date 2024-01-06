#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FMulticastDelegateHelper.h"
#include "Macro/NamespaceMacro.h"
#include "Async/Async.h"
#include "Registry/FCSharpBind.h"

struct FRegisterMulticastDelegate
{
	static void RegisterImplementation(MonoObject* InMonoObject)
	{
		FCSharpBind::Bind<FMulticastDelegateHelper>(InMonoObject);
	}

	static void UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
	{
		AsyncTask(ENamedThreads::GameThread, [InGarbageCollectionHandle]
		{
			(void)FCSharpEnvironment::GetEnvironment().RemoveDelegateReference<FMulticastDelegateHelper>(
				InGarbageCollectionHandle);
		});
	}

	static bool IsBoundImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
	{
		if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
			FMulticastDelegateHelper>(InGarbageCollectionHandle))
		{
			return MulticastDelegateHelper->IsBound();
		}

		return false;
	}

	static bool ContainsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InDelegate)
	{
		if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
			FMulticastDelegateHelper>(InGarbageCollectionHandle))
		{
			return MulticastDelegateHelper->Contains(InDelegate);
		}

		return false;
	}

	static void AddImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InDelegate)
	{
		if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
			FMulticastDelegateHelper>(InGarbageCollectionHandle))
		{
			return MulticastDelegateHelper->Add(InDelegate);
		}
	}

	static void AddUniqueImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                    MonoObject* InDelegate)
	{
		if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
			FMulticastDelegateHelper>(InGarbageCollectionHandle))
		{
			return MulticastDelegateHelper->AddUnique(InDelegate);
		}
	}

	static void RemoveImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InDelegate)
	{
		if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
			FMulticastDelegateHelper>(InGarbageCollectionHandle))
		{
			return MulticastDelegateHelper->Remove(InDelegate);
		}
	}

	static void RemoveAllImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InObject)
	{
		if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
			FMulticastDelegateHelper>(InGarbageCollectionHandle))
		{
			return MulticastDelegateHelper->RemoveAll(InObject);
		}
	}

	static void ClearImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
	{
		if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
			FMulticastDelegateHelper>(InGarbageCollectionHandle))
		{
			return MulticastDelegateHelper->Clear();
		}
	}

	static void BroadcastImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue,
	                                    MonoArray* InValue)
	{
		if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
			FMulticastDelegateHelper>(InGarbageCollectionHandle))
		{
			return MulticastDelegateHelper->Broadcast(OutValue, InValue);
		}
	}

	FRegisterMulticastDelegate()
	{
		FClassBuilder(TEXT("MulticastDelegate"), NAMESPACE_LIBRARY)
			.Function("Register", RegisterImplementation)
			.Function("UnRegister", UnRegisterImplementation)
			.Function("Contains", ContainsImplementation)
			.Function("IsBound", IsBoundImplementation)
			.Function("Contains", ContainsImplementation)
			.Function("Add", AddImplementation)
			.Function("AddUnique", AddUniqueImplementation)
			.Function("Remove", RemoveImplementation)
			.Function("RemoveAll", RemoveAllImplementation)
			.Function("Clear", ClearImplementation)
			.Function("Broadcast", BroadcastImplementation)
			.Register();
	}
};

static FRegisterMulticastDelegate RegisterMulticastDelegate;
