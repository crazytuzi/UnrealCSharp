#include "Registry/FCSharpBind.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FDelegateHelper.h"
#include "Reflection/FReflectionRegistry.h"
#include "CoreMacro/BufferMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterDelegate
	{
		static void RegisterImplementation(const IManagedHandle InManagedObject, const IManagedHandle InManagedType)
		{
			const auto Class = FReflectionRegistry::Get().GetClass(InManagedType);

			FCSharpBind::Bind<FDelegateHelper>(Class, InManagedObject);
		}

		static void UnRegisterImplementation(const IManagedHandle InManagedHandle)
		{
			AsyncTask(ENamedThreads::GameThread, [InManagedHandle]
			{
				(void)FCSharpEnvironment::GetEnvironment().RemoveDelegateReference<FDelegateHelper>(
					InManagedHandle);
			});
		}

		static void BindImplementation(const IManagedHandle InManagedHandle,
		                               const IManagedHandle InObject,
		                               const IManagedHandle InManagedType,
		                               const IManagedHandle InManagedMethod)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InManagedHandle))
			{
				if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject))
				{
					if (const auto FoundClass = FReflectionRegistry::Get().GetClass(InManagedType))
					{
						if (const auto FoundMethod = FoundClass->GetMethod(InManagedMethod))
						{
							DelegateHelper->Bind(FoundObject, FoundMethod);
						}
					}
				}
			}
		}

		static uint8 IsBoundImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InManagedHandle))
			{
				return DelegateHelper->IsBound() ? 1 : 0;
			}

			return 0;
		}

		static void UnBindImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InManagedHandle))
			{
				DelegateHelper->UnBind();
			}
		}

		static void ClearImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InManagedHandle))
			{
				DelegateHelper->Clear();
			}
		}

		static void GenericExecute0Implementation(const IManagedHandle InManagedHandle)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InManagedHandle))
			{
				DelegateHelper->Execute0<>();
			}
		}

		static void PrimitiveExecute1Implementation(const IManagedHandle InManagedHandle, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InManagedHandle))
			{
				DelegateHelper->Execute1<EFunctionReturnType::Primitive>(RETURN_BUFFER);
			}
		}

		static void CompoundExecute1Implementation(const IManagedHandle InManagedHandle, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InManagedHandle))
			{
				DelegateHelper->Execute1<EFunctionReturnType::Compound>(RETURN_BUFFER);
			}
		}

		static void GenericExecute2Implementation(const IManagedHandle InManagedHandle, IN_BUFFER_SIGNATURE)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InManagedHandle))
			{
				DelegateHelper->Execute2<>(IN_BUFFER);
			}
		}

		static void PrimitiveExecute3Implementation(const IManagedHandle InManagedHandle,
		                                            IN_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InManagedHandle))
			{
				DelegateHelper->Execute3<EFunctionReturnType::Primitive>(IN_BUFFER, RETURN_BUFFER);
			}
		}

		static void CompoundExecute3Implementation(const IManagedHandle InManagedHandle,
		                                           IN_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InManagedHandle))
			{
				DelegateHelper->Execute3<EFunctionReturnType::Compound>(IN_BUFFER, RETURN_BUFFER);
			}
		}

		static void GenericExecute4Implementation(const IManagedHandle InManagedHandle, OUT_BUFFER_SIGNATURE)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InManagedHandle))
			{
				DelegateHelper->Execute4<>(OUT_BUFFER);
			}
		}

		static void GenericExecute6Implementation(const IManagedHandle InManagedHandle,
		                                          IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InManagedHandle))
			{
				DelegateHelper->Execute6<>(IN_BUFFER, OUT_BUFFER);
			}
		}

		static void PrimitiveExecute7Implementation(const IManagedHandle InManagedHandle,
		                                            IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InManagedHandle))
			{
				DelegateHelper->Execute7<EFunctionReturnType::Primitive>(IN_BUFFER, OUT_BUFFER, RETURN_BUFFER);
			}
		}

		static void CompoundExecute7Implementation(const IManagedHandle InManagedHandle,
		                                           IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InManagedHandle))
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
