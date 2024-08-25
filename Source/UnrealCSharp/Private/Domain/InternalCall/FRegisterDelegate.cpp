#include "Registry/FCSharpBind.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FDelegateHelper.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
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
		                               const FGarbageCollectionHandle InObject, MonoObject* InDelegate)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject))
				{
					DelegateHelper->Bind(FoundObject, FCSharpEnvironment::GetEnvironment().GetDomain()->
					                     Delegate_Get_Method(InDelegate));
				}
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

		static void GenericExecute0Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				DelegateHelper->Execute0<>();
			}
		}

		static void PrimitiveExecute1Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                            uint8* ReturnBuffer)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				DelegateHelper->Execute1<EFunctionReturnType::Primitive>(ReturnBuffer);
			}
		}

		static void CompoundExecute1Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                           uint8* ReturnBuffer)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				DelegateHelper->Execute1<EFunctionReturnType::Compound>(ReturnBuffer);
			}
		}

		static void GenericExecute2Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                          uint8* InBuffer)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				DelegateHelper->Execute2<>(InBuffer);
			}
		}

		static void PrimitiveExecute3Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                            uint8* InBuffer, uint8* ReturnBuffer)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				DelegateHelper->Execute3<EFunctionReturnType::Primitive>(InBuffer, ReturnBuffer);
			}
		}

		static void CompoundExecute3Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                           uint8* InBuffer, uint8* ReturnBuffer)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				DelegateHelper->Execute3<EFunctionReturnType::Compound>(InBuffer, ReturnBuffer);
			}
		}

		static void GenericExecute4Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                          MonoObject** OutValue)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				DelegateHelper->Execute4<>(OutValue);
			}
		}

		static void GenericExecute6Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                          MonoObject** OutValue, uint8* InBuffer)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				DelegateHelper->Execute6<>(OutValue, InBuffer);
			}
		}

		static void PrimitiveExecute7Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                            MonoObject** OutValue, uint8* InBuffer, uint8* ReturnBuffer)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				DelegateHelper->Execute7<EFunctionReturnType::Primitive>(OutValue, InBuffer, ReturnBuffer);
			}
		}

		static void CompoundExecute7Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                           MonoObject** OutValue, uint8* InBuffer, uint8* ReturnBuffer)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				DelegateHelper->Execute7<EFunctionReturnType::Compound>(OutValue, InBuffer, ReturnBuffer);
			}
		}

		FRegisterDelegate()
		{
			FClassBuilder(TEXT("FDelegate"), NAMESPACE_LIBRARY, true)
				.Function("Register", RegisterImplementation)
				.Function("UnRegister", UnRegisterImplementation)
				.Function("Bind", BindImplementation)
				.Function("IsBound", IsBoundImplementation)
				.Function("UnBind", UnBindImplementation)
				.Function("Clear", ClearImplementation)
				.Function("GenericExecute0", GenericExecute0Implementation)
				.Function("PrimitiveExecute1", PrimitiveExecute1Implementation)
				.Function("CompoundExecute1", CompoundExecute1Implementation)
				.Function("GenericExecute2", GenericExecute2Implementation)
				.Function("PrimitiveExecute3", PrimitiveExecute3Implementation)
				.Function("CompoundExecute3", CompoundExecute3Implementation)
				.Function("GenericExecute4", GenericExecute4Implementation)
				.Function("GenericExecute6", GenericExecute6Implementation)
				.Function("PrimitiveExecute7", PrimitiveExecute7Implementation)
				.Function("CompoundExecute7", CompoundExecute7Implementation);
		}
	};

	FRegisterDelegate RegisterDelegate;
}
