#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FMulticastDelegateHelper.h"
#include "CoreMacro/BufferMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"
#include "Registry/FCSharpBind.h"

namespace
{
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

		static bool ContainsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                   const FGarbageCollectionHandle InObject, MonoObject* InDelegate)
		{
			if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
				FMulticastDelegateHelper>(InGarbageCollectionHandle))
			{
				if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject))
				{
					return MulticastDelegateHelper->Contains(FoundObject,
					                                         FCSharpEnvironment::GetEnvironment().GetDomain()->
					                                         Delegate_Get_Method(InDelegate));
				}
			}

			return false;
		}

		static void AddImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                              const FGarbageCollectionHandle InObject, MonoObject* InDelegate)
		{
			if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
				FMulticastDelegateHelper>(InGarbageCollectionHandle))
			{
				if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject))
				{
					MulticastDelegateHelper->Add(FoundObject,
					                             FCSharpEnvironment::GetEnvironment().GetDomain()->
					                             Delegate_Get_Method(InDelegate));
				}
			}
		}

		static void AddUniqueImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                    const FGarbageCollectionHandle InObject, MonoObject* InDelegate)
		{
			if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
				FMulticastDelegateHelper>(InGarbageCollectionHandle))
			{
				if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject))
				{
					MulticastDelegateHelper->AddUnique(FoundObject,
					                                   FCSharpEnvironment::GetEnvironment().GetDomain()->
					                                   Delegate_Get_Method(InDelegate));
				}
			}
		}

		static void RemoveImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                 const FGarbageCollectionHandle InObject, MonoObject* InDelegate)
		{
			if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
				FMulticastDelegateHelper>(InGarbageCollectionHandle))
			{
				if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject))
				{
					MulticastDelegateHelper->Remove(FoundObject,
					                                FCSharpEnvironment::GetEnvironment().GetDomain()->
					                                Delegate_Get_Method(InDelegate));
				}
			}
		}

		static void RemoveAllImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                    const FGarbageCollectionHandle InObject)
		{
			if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
				FMulticastDelegateHelper>(InGarbageCollectionHandle))
			{
				if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject))
				{
					MulticastDelegateHelper->RemoveAll(FoundObject);
				}
			}
		}

		static void ClearImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
				FMulticastDelegateHelper>(InGarbageCollectionHandle))
			{
				MulticastDelegateHelper->Clear();
			}
		}

		static void GenericBroadcast0Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
				FMulticastDelegateHelper>(InGarbageCollectionHandle))
			{
				return MulticastDelegateHelper->Broadcast0<>();
			}
		}

		static void GenericBroadcast2Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                            IN_BUFFER_SIGNATURE)
		{
			if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
				FMulticastDelegateHelper>(InGarbageCollectionHandle))
			{
				MulticastDelegateHelper->Broadcast2<>(IN_BUFFER);
			}
		}

		static void GenericBroadcast4Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                            OUT_BUFFER_SIGNATURE)
		{
			if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
				FMulticastDelegateHelper>(InGarbageCollectionHandle))
			{
				MulticastDelegateHelper->Broadcast4<>(OUT_BUFFER);
			}
		}

		static void GenericBroadcast6Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                            IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE)
		{
			if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
				FMulticastDelegateHelper>(InGarbageCollectionHandle))
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
