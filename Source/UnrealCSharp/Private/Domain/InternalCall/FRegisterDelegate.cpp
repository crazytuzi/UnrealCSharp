#include "Registry/FCSharpBind.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FDelegateHelper.h"
#include "CoreMacro/BufferMacro.h"
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
		                                            RETURN_BUFFER_SIGNATURE)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				DelegateHelper->Execute1<EFunctionReturnType::Primitive>(RETURN_BUFFER);
			}
		}

		static void CompoundExecute1Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                           RETURN_BUFFER_SIGNATURE)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				DelegateHelper->Execute1<EFunctionReturnType::Compound>(RETURN_BUFFER);
			}
		}

		static void GenericExecute2Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                          IN_BUFFER_SIGNATURE)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				DelegateHelper->Execute2<>(IN_BUFFER);
			}
		}

		static void PrimitiveExecute3Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                            IN_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				DelegateHelper->Execute3<EFunctionReturnType::Primitive>(IN_BUFFER, RETURN_BUFFER);
			}
		}

		static void CompoundExecute3Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                           IN_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				DelegateHelper->Execute3<EFunctionReturnType::Compound>(IN_BUFFER, RETURN_BUFFER);
			}
		}

		static void GenericExecute4Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                          OUT_BUFFER_SIGNATURE)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				DelegateHelper->Execute4<>(OUT_BUFFER);
			}
		}

		static void GenericExecute6Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                          IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				DelegateHelper->Execute6<>(IN_BUFFER, OUT_BUFFER);
			}
		}

		static void PrimitiveExecute7Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                            IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				DelegateHelper->Execute7<EFunctionReturnType::Primitive>(IN_BUFFER, OUT_BUFFER, RETURN_BUFFER);
			}
		}

		static void CompoundExecute7Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                           IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				DelegateHelper->Execute7<EFunctionReturnType::Compound>(IN_BUFFER, OUT_BUFFER, RETURN_BUFFER);
			}
		}

		FRegisterDelegate()
		{
			FClassBuilder(TEXT("FDelegate"), NAMESPACE_LIBRARY)
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

	[[maybe_unused]] FRegisterDelegate RegisterDelegate;
}
