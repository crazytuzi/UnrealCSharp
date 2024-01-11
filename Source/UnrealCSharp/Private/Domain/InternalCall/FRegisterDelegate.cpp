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

	static MonoObject* ExecuteImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                         MonoObject** OutValue, MonoArray* InValue)
	{
		if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
			InGarbageCollectionHandle))
		{
			return DelegateHelper->Execute(OutValue, InValue);
		}

		return nullptr;
	}

	static void Execute0Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
	{
		ExecuteImplementation(InGarbageCollectionHandle, nullptr, nullptr);
	}

	static MonoObject* Execute1Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
	{
		return ExecuteImplementation(InGarbageCollectionHandle, nullptr, nullptr);
	}

	static void Execute2Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoArray* InValue)
	{
		ExecuteImplementation(InGarbageCollectionHandle, nullptr, InValue);
	}

	static MonoObject* Execute3Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                          MonoArray* InValue)
	{
		return ExecuteImplementation(InGarbageCollectionHandle, nullptr, InValue);
	}

	static void Execute4Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
	{
		ExecuteImplementation(InGarbageCollectionHandle, OutValue, nullptr);
	}

	static MonoObject* Execute5Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                          MonoObject** OutValue)
	{
		return ExecuteImplementation(InGarbageCollectionHandle, OutValue, nullptr);
	}

	static void Execute6Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue,
	                                   MonoArray* InValue)
	{
		ExecuteImplementation(InGarbageCollectionHandle, OutValue, InValue);
	}

	static MonoObject* Execute7Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                          MonoObject** OutValue, MonoArray* InValue)
	{
		return ExecuteImplementation(InGarbageCollectionHandle, OutValue, InValue);;
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
			.Function("Execute0", Execute0Implementation)
			.Function("Execute1", Execute1Implementation)
			.Function("Execute2", Execute2Implementation)
			.Function("Execute3", Execute3Implementation)
			.Function("Execute4", Execute4Implementation)
			.Function("Execute5", Execute5Implementation)
			.Function("Execute6", Execute6Implementation)
			.Function("Execute7", Execute7Implementation)
			.Register();
	}
};

static FRegisterDelegate RegisterDelegate;
