#include "Registry/FCSharpBind.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Container/FSetHelper.h"
#include "Domain/Script/IUnmanagedBool.h"
#include "Reflection/FReflectionRegistry.h"
#include "CoreMacro/BufferMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterSet
	{
		static void RegisterImplementation(const IManagedObject InManagedObject,
		                                   const IManagedReflectionType InManagedReflectionType)
		{
			const auto Class = FReflectionRegistry::Get().GetClass(InManagedReflectionType);

			FCSharpBind::Bind<FSetHelper>(Class, Class->GetGenericArgument(), InManagedObject);
		}

		static void UnRegisterImplementation(const IManagedHandle InManagedHandle)
		{
			AsyncTask(ENamedThreads::GameThread, [InManagedHandle]
			{
				(void)FCSharpEnvironment::GetEnvironment().RemoveContainerReference<FSetHelper>(
					InManagedHandle);
			});
		}

		static void EmptyImplementation(const IManagedHandle InManagedHandle,
		                                const int32 InExpectedNumElements)
		{
			if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(
				InManagedHandle))
			{
				SetHelper->Empty(InExpectedNumElements);
			}
		}

		static int32 NumImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(
				InManagedHandle))
			{
				return SetHelper->Num();
			}

			return 0;
		}

		static IUnmanagedBool IsEmptyImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(
				InManagedHandle))
			{
				return BoolToIUnmanagedBool(SetHelper->IsEmpty());
			}

			return IUnmanagedFalse;
		}

		static int32 GetMaxIndexImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(
				InManagedHandle))
			{
				return SetHelper->GetMaxIndex();
			}

			return 0;
		}

		static void AddImplementation(const IManagedHandle InManagedHandle,
		                              IN_VALUE_BUFFER_SIGNATURE)
		{
			if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(
				InManagedHandle))
			{
				SetHelper->Add(IN_VALUE_BUFFER);
			}
		}

		static int32 RemoveImplementation(const IManagedHandle InManagedHandle,
		                                  const IN_VALUE_BUFFER_SIGNATURE)
		{
			if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(
				InManagedHandle))
			{
				return SetHelper->Remove(IN_VALUE_BUFFER);
			}

			return 0;
		}

		static IUnmanagedBool ContainsImplementation(const IManagedHandle InManagedHandle,
		                                             const IN_VALUE_BUFFER_SIGNATURE)
		{
			if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(
				InManagedHandle))
			{
				return BoolToIUnmanagedBool(SetHelper->Contains(IN_VALUE_BUFFER));
			}

			return IUnmanagedFalse;
		}

		static IUnmanagedBool IsValidIndexImplementation(const IManagedHandle InManagedHandle,
		                                                 const int32 InIndex)
		{
			if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(
				InManagedHandle))
			{
				return BoolToIUnmanagedBool(SetHelper->IsValidIndex(InIndex));
			}

			return IUnmanagedFalse;
		}

		static void GetEnumeratorImplementation(const IManagedHandle InManagedHandle,
		                                        const int32 InIndex, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(
				InManagedHandle))
			{
				const auto Value = SetHelper->GetEnumerator(InIndex);

				SetHelper->GetElementPropertyDescriptor()->Get(Value, reinterpret_cast<void**>(RETURN_BUFFER));
			}
		}

		FRegisterSet()
		{
			FClassBuilder(TEXT("TSet"), NAMESPACE_LIBRARY)
				.Function("Register", RegisterImplementation)
				.Function("UnRegister", UnRegisterImplementation)
				.Function("Empty", EmptyImplementation)
				.Function("Num", NumImplementation)
				.Function("IsEmpty", IsEmptyImplementation)
				.Function("GetMaxIndex", GetMaxIndexImplementation)
				.Function("Add", AddImplementation)
				.Function("Remove", RemoveImplementation)
				.Function("Contains", ContainsImplementation)
				.Function("IsValidIndex", IsValidIndexImplementation)
				.Function("GetEnumerator", GetEnumeratorImplementation);
		}
	};

	[[maybe_unused]] FRegisterSet RegisterSet;
}
