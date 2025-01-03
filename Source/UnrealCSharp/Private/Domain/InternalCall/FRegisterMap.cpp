#include "Registry/FCSharpBind.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"
#include "Reflection/Container/FMapHelper.h"
#include "CoreMacro/BufferMacro.h"
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
		                              IN_KEY_BUFFER_SIGNATURE, IN_VALUE_BUFFER_SIGNATURE)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InGarbageCollectionHandle))
			{
				MapHelper->Add(IN_KEY_BUFFER, IN_VALUE_BUFFER);
			}
		}

		static int32 RemoveImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                  const IN_KEY_BUFFER_SIGNATURE)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InGarbageCollectionHandle))
			{
				return MapHelper->Remove(IN_KEY_BUFFER);
			}

			return 0;
		}

		static void FindKeyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                  const IN_VALUE_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InGarbageCollectionHandle))
			{
				MapHelper->GetKeyPropertyDescriptor()->Get(MapHelper->FindKey(IN_VALUE_BUFFER),
				                                           reinterpret_cast<void**>(RETURN_BUFFER));
			}
		}

		static void FindImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                               const IN_KEY_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InGarbageCollectionHandle))
			{
				MapHelper->GetValuePropertyDescriptor()->Get(MapHelper->Find(IN_KEY_BUFFER),
				                                             reinterpret_cast<void**>(RETURN_BUFFER));
			}
		}

		static bool ContainsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                   const IN_KEY_BUFFER_SIGNATURE)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InGarbageCollectionHandle))
			{
				return MapHelper->Contains(IN_KEY_BUFFER);
			}

			return false;
		}

		static void GetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                              const IN_KEY_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InGarbageCollectionHandle))
			{
				MapHelper->GetValuePropertyDescriptor()->Get(MapHelper->Get(IN_KEY_BUFFER),
				                                             reinterpret_cast<void**>(RETURN_BUFFER));
			}
		}

		static void SetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                              IN_KEY_BUFFER_SIGNATURE, IN_VALUE_BUFFER_SIGNATURE)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InGarbageCollectionHandle))
			{
				MapHelper->Set(IN_KEY_BUFFER, IN_VALUE_BUFFER);
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
		                                           const int32 InIndex, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InGarbageCollectionHandle))
			{
				const auto Key = MapHelper->GetEnumeratorKey(InIndex);

				MapHelper->GetKeyPropertyDescriptor()->Get(Key, reinterpret_cast<void**>(RETURN_BUFFER));
			}
		}

		static void GetEnumeratorValueImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                             const int32 InIndex, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InGarbageCollectionHandle))
			{
				const auto Value = MapHelper->GetEnumeratorValue(InIndex);

				MapHelper->GetValuePropertyDescriptor()->Get(Value, reinterpret_cast<void**>(RETURN_BUFFER));
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
