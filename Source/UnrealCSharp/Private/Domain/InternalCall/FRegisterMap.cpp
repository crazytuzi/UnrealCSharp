#include "Registry/FCSharpBind.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"
#include "Reflection/Container/FMapHelper.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterMap
	{
		static void RegisterImplementation(MonoObject* InMonoObject)
		{
			FCSharpBind::Bind<FMapHelper>(InMonoObject,
			                              FTypeBridge::GetGenericArgument(InMonoObject),
			                              FTypeBridge::GetGenericArgument(InMonoObject, 1));
		}

		static void UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			AsyncTask(ENamedThreads::GameThread, [InGarbageCollectionHandle]
			{
				(void)FCSharpEnvironment::GetEnvironment().RemoveContainerReference<FMapHelper>(
					InGarbageCollectionHandle);
			});
		}

		static void EmptyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                const int32 InExpectedNumElements)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InGarbageCollectionHandle))
			{
				return MapHelper->Empty(InExpectedNumElements);
			}
		}

		static int32 NumImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InGarbageCollectionHandle))
			{
				return MapHelper->Num();
			}

			return 0;
		}

		static bool IsEmptyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InGarbageCollectionHandle))
			{
				return MapHelper->IsEmpty();
			}

			return false;
		}

		static void AddImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                              uint8* InKeyBuffer, uint8* InValueBuffer)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InGarbageCollectionHandle))
			{
				MapHelper->Add(InKeyBuffer, InValueBuffer);
			}
		}

		static int32 RemoveImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                  const uint8* InKeyBuffer)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InGarbageCollectionHandle))
			{
				return MapHelper->Remove(InKeyBuffer);
			}

			return 0;
		}

		static void FindKeyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                  const uint8* InValueBuffer, uint8* ReturnBuffer)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InGarbageCollectionHandle))
			{
				MapHelper->GetKeyPropertyDescriptor()->Get(MapHelper->FindKey(InValueBuffer),
				                                           reinterpret_cast<void**>(ReturnBuffer));
			}
		}

		static void FindImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                               const uint8* InKeyBuffer, uint8* ReturnBuffer)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InGarbageCollectionHandle))
			{
				MapHelper->GetValuePropertyDescriptor()->Get(MapHelper->Find(InKeyBuffer),
				                                             reinterpret_cast<void**>(ReturnBuffer));
			}
		}

		static bool ContainsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                   const uint8* InKeyBuffer)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InGarbageCollectionHandle))
			{
				return MapHelper->Contains(InKeyBuffer);
			}

			return false;
		}

		static void GetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                              const uint8* InKeyBuffer, uint8* ReturnBuffer)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InGarbageCollectionHandle))
			{
				MapHelper->GetValuePropertyDescriptor()->Get(MapHelper->Get(InKeyBuffer),
				                                             reinterpret_cast<void**>(ReturnBuffer));
			}
		}

		static void SetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                              uint8* InKeyBuffer, uint8* InValueBuffer)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InGarbageCollectionHandle))
			{
				MapHelper->Set(InKeyBuffer, InValueBuffer);
			}
		}

		static int32 GetMaxIndexImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InGarbageCollectionHandle))
			{
				return MapHelper->GetMaxIndex();
			}

			return 0;
		}

		static bool IsValidIndexImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                       const int32 InIndex)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InGarbageCollectionHandle))
			{
				return MapHelper->IsValidIndex(InIndex);
			}

			return false;
		}

		static void GetEnumeratorKeyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                           const int32 InIndex, uint8* ReturnBuffer)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InGarbageCollectionHandle))
			{
				const auto Key = MapHelper->GetEnumeratorKey(InIndex);

				MapHelper->GetKeyPropertyDescriptor()->Get(Key, reinterpret_cast<void**>(ReturnBuffer));
			}
		}

		static void GetEnumeratorValueImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                             const int32 InIndex, uint8* ReturnBuffer)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InGarbageCollectionHandle))
			{
				const auto Value = MapHelper->GetEnumeratorValue(InIndex);

				MapHelper->GetValuePropertyDescriptor()->Get(Value, reinterpret_cast<void**>(ReturnBuffer));
			}
		}

		FRegisterMap()
		{
			FClassBuilder(TEXT("TMap"), NAMESPACE_LIBRARY)
				.Function("Register", RegisterImplementation)
				.Function("UnRegister", UnRegisterImplementation)
				.Function("Empty", EmptyImplementation)
				.Function("Num", NumImplementation)
				.Function("IsEmpty", IsEmptyImplementation)
				.Function("Add", AddImplementation)
				.Function("Remove", RemoveImplementation)
				.Function("FindKey", FindKeyImplementation)
				.Function("Find", FindImplementation)
				.Function("Contains", ContainsImplementation)
				.Function("Get", GetImplementation)
				.Function("Set", SetImplementation)
				.Function("GetMaxIndex", GetMaxIndexImplementation)
				.Function("IsValidIndex", IsValidIndexImplementation)
				.Function("GetEnumeratorKey", GetEnumeratorKeyImplementation)
				.Function("GetEnumeratorValue", GetEnumeratorValueImplementation);
		}
	};

	[[maybe_unused]] FRegisterMap RegisterMap;
}
