#include "Registry/FCSharpBind.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FDelegateHelper.h"
#include "Macro/NamespaceMacro.h"
#include "Async/Async.h"

struct FRegisterDelegate
{
	static void RegisterImplementation(MonoObject* InMonoObject)
	{
		FCSharpBind::Bind<FDelegateHelper>(InMonoObject);
	}

	static void UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
	{
		AsyncTask(ENamedThreads::GameThread, [InGarbageCollectionHandle]
		{
			(void)FCSharpEnvironment::GetEnvironment().RemoveDelegateReference<FDelegateHelper>(
				InGarbageCollectionHandle);
		});
	}

	static void BindImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                               MonoObject* InDelegate)
	{
		if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
			InGarbageCollectionHandle))
		{
			DelegateHelper->Bind(InDelegate);
		}
	}

	static bool IsBoundImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
	{
		if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
			InGarbageCollectionHandle))
		{
			return DelegateHelper->IsBound();
		}

		return false;
	}

	static void UnBindImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
	{
		if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
			InGarbageCollectionHandle))
		{
			DelegateHelper->UnBind();
		}
	}

	static void ClearImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
	{
		if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
			InGarbageCollectionHandle))
		{
			DelegateHelper->Clear();
		}
	}

	static void ExecuteImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                  MonoObject** ReturnValue, MonoObject** OutValue, MonoArray* InValue)
	{
		if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
			InGarbageCollectionHandle))
		{
			DelegateHelper->Execute(ReturnValue, OutValue, InValue);
		}
	}

	FRegisterDelegate()
	{
		FClassBuilder(TEXT("Delegate"), NAMESPACE_LIBRARY)
			.Function("Register", RegisterImplementation)
			.Function("UnRegister", UnRegisterImplementation)
			.Function("Bind", BindImplementation)
			.Function("IsBound", IsBoundImplementation)
			.Function("UnBind", UnBindImplementation)
			.Function("Clear", ClearImplementation)
			.Function("Execute", ExecuteImplementation)
			.Register();
	}
};

static FRegisterDelegate RegisterDelegate;
