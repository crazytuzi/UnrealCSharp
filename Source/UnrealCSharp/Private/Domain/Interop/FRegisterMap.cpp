#include "Registry/FCSharpBind.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Domain/Script/IUnmanagedBool.h"
#include "Reflection/Container/FMapHelper.h"
#include "CoreMacro/BufferMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterMap
	{
		static void RegisterImplementation(const IManagedObject InManagedObject,
		                                   const IManagedReflectionType InManagedReflectionType)
		{
			const auto Class = FReflectionRegistry::Get().GetClass(InManagedReflectionType);

			FCSharpBind::Bind<FMapHelper>(Class,
			                              Class->GetGenericArgument(),
			                              Class->GetGenericArgument(1),
			                              InManagedObject);
		}

		static void UnRegisterImplementation(const IManagedHandle InManagedHandle)
		{
			AsyncTask(ENamedThreads::GameThread, [InManagedHandle]
			{
				(void)FCSharpEnvironment::GetEnvironment().RemoveContainerReference<FMapHelper>(
					InManagedHandle);
			});
		}

		static void EmptyImplementation(const IManagedHandle InManagedHandle,
		                                const int32 InExpectedNumElements)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InManagedHandle))
			{
				return MapHelper->Empty(InExpectedNumElements);
			}
		}

		static int32 NumImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InManagedHandle))
			{
				return MapHelper->Num();
			}

			return 0;
		}

		static IUnmanagedBool IsEmptyImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InManagedHandle))
			{
				return BoolToIUnmanagedBool(MapHelper->IsEmpty());
			}

			return IUnmanagedFalse;
		}

		static void AddImplementation(const IManagedHandle InManagedHandle,
		                              IN_KEY_BUFFER_SIGNATURE, IN_VALUE_BUFFER_SIGNATURE)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InManagedHandle))
			{
				MapHelper->Add(IN_KEY_BUFFER, IN_VALUE_BUFFER);
			}
		}

		static int32 RemoveImplementation(const IManagedHandle InManagedHandle,
		                                  const IN_KEY_BUFFER_SIGNATURE)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InManagedHandle))
			{
				return MapHelper->Remove(IN_KEY_BUFFER);
			}

			return 0;
		}

		static void FindKeyImplementation(const IManagedHandle InManagedHandle,
		                                  const IN_VALUE_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InManagedHandle))
			{
				MapHelper->GetKeyPropertyDescriptor()->Get(MapHelper->FindKey(IN_VALUE_BUFFER),
				                                           reinterpret_cast<void**>(RETURN_BUFFER));
			}
		}

		static void FindImplementation(const IManagedHandle InManagedHandle,
		                               const IN_KEY_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InManagedHandle))
			{
				MapHelper->GetValuePropertyDescriptor()->Get(MapHelper->Find(IN_KEY_BUFFER),
				                                             reinterpret_cast<void**>(RETURN_BUFFER));
			}
		}

		static IUnmanagedBool ContainsImplementation(const IManagedHandle InManagedHandle,
		                                             const IN_KEY_BUFFER_SIGNATURE)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InManagedHandle))
			{
				return BoolToIUnmanagedBool(MapHelper->Contains(IN_KEY_BUFFER));
			}

			return IUnmanagedFalse;
		}

		static void GetImplementation(const IManagedHandle InManagedHandle,
		                              const IN_KEY_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InManagedHandle))
			{
				MapHelper->GetValuePropertyDescriptor()->Get(MapHelper->Get(IN_KEY_BUFFER),
				                                             reinterpret_cast<void**>(RETURN_BUFFER));
			}
		}

		static void SetImplementation(const IManagedHandle InManagedHandle,
		                              IN_KEY_BUFFER_SIGNATURE, IN_VALUE_BUFFER_SIGNATURE)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InManagedHandle))
			{
				MapHelper->Set(IN_KEY_BUFFER, IN_VALUE_BUFFER);
			}
		}

		static int32 GetMaxIndexImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InManagedHandle))
			{
				return MapHelper->GetMaxIndex();
			}

			return 0;
		}

		static IUnmanagedBool IsValidIndexImplementation(const IManagedHandle InManagedHandle,
		                                                 const int32 InIndex)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InManagedHandle))
			{
				return BoolToIUnmanagedBool(MapHelper->IsValidIndex(InIndex));
			}

			return IUnmanagedFalse;
		}

		static void GetEnumeratorKeyImplementation(const IManagedHandle InManagedHandle,
		                                           const int32 InIndex, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InManagedHandle))
			{
				const auto Key = MapHelper->GetEnumeratorKey(InIndex);

				MapHelper->GetKeyPropertyDescriptor()->Get(Key, reinterpret_cast<void**>(RETURN_BUFFER));
			}
		}

		static void GetEnumeratorValueImplementation(const IManagedHandle InManagedHandle,
		                                             const int32 InIndex, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InManagedHandle))
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
