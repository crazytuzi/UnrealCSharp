#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FMulticastDelegateHelper.h"
#include "Domain/Script/IUnmanagedBool.h"
#include "Reflection/FReflectionRegistry.h"
#include "CoreMacro/BufferMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"
#include "Registry/FCSharpBind.h"

namespace
{
	struct FRegisterMulticastDelegate
	{
		static void RegisterImplementation(const IManagedObject InManagedObject,
		                                   const IManagedReflectionType InManagedReflectionType)
		{
			const auto Class = FReflectionRegistry::Get().GetClass(InManagedReflectionType);

			FCSharpBind::Bind<FMulticastDelegateHelper>(Class, InManagedObject);
		}

		static void UnRegisterImplementation(const IManagedHandle InManagedHandle)
		{
			AsyncTask(ENamedThreads::GameThread, [InManagedHandle]
			{
				(void)FCSharpEnvironment::GetEnvironment().RemoveDelegateReference<FMulticastDelegateHelper>(
					InManagedHandle);
			});
		}

		static IUnmanagedBool IsBoundImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
				FMulticastDelegateHelper>(InManagedHandle))
			{
				return BoolToIUnmanagedBool(MulticastDelegateHelper->IsBound());
			}

			return IUnmanagedFalse;
		}

		static IUnmanagedBool ContainsImplementation(const IManagedHandle InManagedHandle,
		                                             const IManagedHandle InObject,
		                                             const IManagedReflectionType InManagedReflectionType,
		                                             const IManagedReflectionMethod InManagedReflectionMethod)
		{
			if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
				FMulticastDelegateHelper>(InManagedHandle))
			{
				if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject))
				{
					if (const auto FoundClass = FReflectionRegistry::Get().GetClass(InManagedReflectionType))
					{
						if (const auto FoundMethod = FoundClass->GetMethod(InManagedReflectionMethod))
						{
							return BoolToIUnmanagedBool(MulticastDelegateHelper->Contains(FoundObject, FoundMethod));
						}
					}
				}
			}

			return IUnmanagedFalse;
		}

		static void AddImplementation(const IManagedHandle InManagedHandle,
		                              const IManagedHandle InObject,
		                              const IManagedReflectionType InManagedReflectionType,
		                              const IManagedReflectionMethod InManagedReflectionMethod)
		{
			if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
				FMulticastDelegateHelper>(InManagedHandle))
			{
				if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject))
				{
					if (const auto FoundClass = FReflectionRegistry::Get().GetClass(InManagedReflectionType))
					{
						if (const auto FoundMethod = FoundClass->GetMethod(InManagedReflectionMethod))
						{
							MulticastDelegateHelper->Add(FoundObject, FoundMethod);
						}
					}
				}
			}
		}

		static void AddUniqueImplementation(const IManagedHandle InManagedHandle,
		                                    const IManagedHandle InObject,
		                                    const IManagedReflectionType InManagedReflectionType,
		                                    const IManagedReflectionMethod InManagedReflectionMethod)
		{
			if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
				FMulticastDelegateHelper>(InManagedHandle))
			{
				if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject))
				{
					if (const auto FoundClass = FReflectionRegistry::Get().GetClass(InManagedReflectionType))
					{
						if (const auto FoundMethod = FoundClass->GetMethod(InManagedReflectionMethod))
						{
							MulticastDelegateHelper->AddUnique(FoundObject, FoundMethod);
						}
					}
				}
			}
		}

		static void RemoveImplementation(const IManagedHandle InManagedHandle,
		                                 const IManagedHandle InObject,
		                                 const IManagedReflectionType InManagedReflectionType,
		                                 const IManagedReflectionMethod InManagedReflectionMethod)
		{
			if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
				FMulticastDelegateHelper>(InManagedHandle))
			{
				if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject))
				{
					if (const auto FoundClass = FReflectionRegistry::Get().GetClass(InManagedReflectionType))
					{
						if (const auto FoundMethod = FoundClass->GetMethod(InManagedReflectionMethod))
						{
							MulticastDelegateHelper->Remove(FoundObject, FoundMethod);
						}
					}
				}
			}
		}

		static void RemoveAllImplementation(const IManagedHandle InManagedHandle,
		                                    const IManagedHandle InObject)
		{
			if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
				FMulticastDelegateHelper>(InManagedHandle))
			{
				if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject))
				{
					MulticastDelegateHelper->RemoveAll(FoundObject);
				}
			}
		}

		static void ClearImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
				FMulticastDelegateHelper>(InManagedHandle))
			{
				MulticastDelegateHelper->Clear();
			}
		}

		static void GenericBroadcast0Implementation(const IManagedHandle InManagedHandle)
		{
			if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
				FMulticastDelegateHelper>(InManagedHandle))
			{
				return MulticastDelegateHelper->Broadcast0<>();
			}
		}

		static void GenericBroadcast2Implementation(const IManagedHandle InManagedHandle,
		                                            IN_BUFFER_SIGNATURE)
		{
			if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
				FMulticastDelegateHelper>(InManagedHandle))
			{
				MulticastDelegateHelper->Broadcast2<>(IN_BUFFER);
			}
		}

		static void GenericBroadcast4Implementation(const IManagedHandle InManagedHandle,
		                                            OUT_BUFFER_SIGNATURE)
		{
			if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
				FMulticastDelegateHelper>(InManagedHandle))
			{
				MulticastDelegateHelper->Broadcast4<>(OUT_BUFFER);
			}
		}

		static void GenericBroadcast6Implementation(const IManagedHandle InManagedHandle,
		                                            IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE)
		{
			if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
				FMulticastDelegateHelper>(InManagedHandle))
			{
				MulticastDelegateHelper->Broadcast6<>(IN_BUFFER, OUT_BUFFER);
			}
		}

		FRegisterMulticastDelegate()
		{
			FClassBuilder(TEXT("FMulticastDelegate"), NAMESPACE_LIBRARY)
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
				.Function("GenericBroadcast0", GenericBroadcast0Implementation)
				.Function("GenericBroadcast2", GenericBroadcast2Implementation)
				.Function("GenericBroadcast4", GenericBroadcast4Implementation)
				.Function("GenericBroadcast6", GenericBroadcast6Implementation);
		}
	};

	[[maybe_unused]] FRegisterMulticastDelegate RegisterMulticastDelegate;
}
