#include "Registry/FCSharpBind.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Container/FArrayHelper.h"
#include "Reflection/FReflectionRegistry.h"
#include "CoreMacro/BufferMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterArray
	{
		static void RegisterImplementation(const IManagedHandle InManagedObject, const IManagedHandle InManagedType)
		{
			const auto Class = FReflectionRegistry::Get().GetClass(InManagedType);

			FCSharpBind::Bind<FArrayHelper>(Class, Class->GetGenericArgument(), InManagedObject);
		}

		static uint8 IdenticalImplementation(const IManagedHandle InA, const IManagedHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InB))
				{
					return FArrayHelper::Identical(FoundA, FoundB) ? 1 : 0;
				}
			}

			return 0;
		}

		static void UnRegisterImplementation(const IManagedHandle InManagedHandle)
		{
			AsyncTask(ENamedThreads::GameThread, [InManagedHandle]
			{
				(void)FCSharpEnvironment::GetEnvironment().RemoveContainerReference<
					FArrayHelper>(InManagedHandle);
			});
		}

		static int32 GetTypeSizeImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InManagedHandle))
			{
				return ArrayHelper->GetTypeSize();
			}

			return 0;
		}

		static int32 GetSlackImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InManagedHandle))
			{
				return ArrayHelper->GetSlack();
			}

			return 0;
		}

		static uint8 IsValidIndexImplementation(const IManagedHandle InManagedHandle, const int32 InIndex)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InManagedHandle))
			{
				return ArrayHelper->IsValidIndex(InIndex) ? 1 : 0;
			}

			return 0;
		}

		static int32 NumImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InManagedHandle))
			{
				return ArrayHelper->Num();
			}

			return 0;
		}

		static uint8 IsEmptyImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InManagedHandle))
			{
				return ArrayHelper->IsEmpty() ? 1 : 0;
			}

			return 0;
		}

		static int32 MaxImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InManagedHandle))
			{
				return ArrayHelper->Max();
			}

			return 0;
		}

		static void GetImplementation(const IManagedHandle InManagedHandle,
		                              const int32 InIndex, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InManagedHandle))
			{
				const auto Value = ArrayHelper->Get(InIndex);

				ArrayHelper->GetInnerPropertyDescriptor()->Get(Value, reinterpret_cast<void**>(RETURN_BUFFER));
			}
		}

		static void SetImplementation(const IManagedHandle InManagedHandle,
		                              const int32 InIndex, IN_VALUE_BUFFER_SIGNATURE)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InManagedHandle))
			{
				ArrayHelper->Set(InIndex, IN_VALUE_BUFFER);
			}
		}

		static int32 FindImplementation(const IManagedHandle InManagedHandle, const IN_VALUE_BUFFER_SIGNATURE)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InManagedHandle))
			{
				return ArrayHelper->Find(IN_VALUE_BUFFER);
			}

			return INDEX_NONE;
		}

		static int32 FindLastImplementation(const IManagedHandle InManagedHandle, const IN_VALUE_BUFFER_SIGNATURE)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InManagedHandle))
			{
				return ArrayHelper->FindLast(IN_VALUE_BUFFER);
			}

			return INDEX_NONE;
		}

		static uint8 ContainsImplementation(const IManagedHandle InManagedHandle, const IN_VALUE_BUFFER_SIGNATURE)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InManagedHandle))
			{
				return ArrayHelper->Contains(IN_VALUE_BUFFER) ? 1 : 0;
			}

			return 0;
		}

		static int32 AddUninitializedImplementation(const IManagedHandle InManagedHandle, const int32 InCount)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InManagedHandle))
			{
				return ArrayHelper->AddUninitialized(InCount);
			}

			return 0;
		}

		static void InsertZeroedImplementation(const IManagedHandle InManagedHandle,
		                                       const int32 InIndex, const int32 InCount)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InManagedHandle))
			{
				ArrayHelper->InsertZeroed(InIndex, InCount);
			}
		}

		static void InsertDefaultedImplementation(const IManagedHandle InManagedHandle,
		                                          const int32 InIndex, const int32 InCount)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InManagedHandle))
			{
				ArrayHelper->InsertDefaulted(InIndex, InCount);
			}
		}

		static void RemoveAtImplementation(const IManagedHandle InManagedHandle,
		                                   const int32 InIndex, const int32 InCount, const uint8 bAllowShrinking)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InManagedHandle))
			{
				ArrayHelper->RemoveAt(InIndex, InCount, bAllowShrinking != 0);
			}
		}

		static void ResetImplementation(const IManagedHandle InManagedHandle, const int32 InNewSize)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InManagedHandle))
			{
				return ArrayHelper->Reset(InNewSize);
			}
		}

		static void EmptyImplementation(const IManagedHandle InManagedHandle, const int32 InSlack)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InManagedHandle))
			{
				return ArrayHelper->Empty(InSlack);
			}
		}

		static void SetNumImplementation(const IManagedHandle InManagedHandle,
		                                 const int32 InNewNum, const uint8 bAllowShrinking)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InManagedHandle))
			{
				return ArrayHelper->SetNum(InNewNum, bAllowShrinking != 0);
			}
		}

		static int32 AddImplementation(const IManagedHandle InManagedHandle, IN_VALUE_BUFFER_SIGNATURE)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InManagedHandle))
			{
				return ArrayHelper->Add(IN_VALUE_BUFFER);
			}

			return 0;
		}

		static int32 AddZeroedImplementation(const IManagedHandle InManagedHandle, const int32 InCount)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InManagedHandle))
			{
				return ArrayHelper->AddZeroed(InCount);
			}

			return 0;
		}

		static int32 AddUniqueImplementation(const IManagedHandle InManagedHandle, IN_VALUE_BUFFER_SIGNATURE)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InManagedHandle))
			{
				return ArrayHelper->AddUnique(IN_VALUE_BUFFER);
			}

			return 0;
		}

		static int32 RemoveSingleImplementation(const IManagedHandle InManagedHandle, const IN_VALUE_BUFFER_SIGNATURE)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InManagedHandle))
			{
				return ArrayHelper->RemoveSingle(IN_VALUE_BUFFER);
			}

			return 0;
		}

		static int32 RemoveImplementation(const IManagedHandle InManagedHandle, const IN_VALUE_BUFFER_SIGNATURE)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InManagedHandle))
			{
				return ArrayHelper->Remove(IN_VALUE_BUFFER);
			}

			return 0;
		}

		static void SwapMemoryImplementation(const IManagedHandle InManagedHandle,
		                                     const int32 InFirstIndexToSwap, const int32 InSecondIndexToSwap)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InManagedHandle))
			{
				ArrayHelper->SwapMemory(InFirstIndexToSwap, InSecondIndexToSwap);
			}
		}

		static void SwapImplementation(const IManagedHandle InManagedHandle,
		                               const int32 InFirstIndexToSwap, const int32 InSecondIndexToSwap)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InManagedHandle))
			{
				ArrayHelper->Swap(InFirstIndexToSwap, InSecondIndexToSwap);
			}
		}

		static int32 INDEX_NONEImplementation()
		{
			return INDEX_NONE;
		}

		FRegisterArray()
		{
			FClassBuilder(TEXT("TArray"), NAMESPACE_LIBRARY)
				.Function("Register", RegisterImplementation)
				.Function("Identical", IdenticalImplementation)
				.Function("UnRegister", UnRegisterImplementation)
				.Function("GetTypeSize", GetTypeSizeImplementation)
				.Function("GetSlack", GetSlackImplementation)
				.Function("IsValidIndex", IsValidIndexImplementation)
				.Function("Num", NumImplementation)
				.Function("IsEmpty", IsEmptyImplementation)
				.Function("Max", MaxImplementation)
				.Function("Get", GetImplementation)
				.Function("Set", SetImplementation)
				.Function("Find", FindImplementation)
				.Function("FindLast", FindLastImplementation)
				.Function("Contains", ContainsImplementation)
				.Function("AddUninitialized", AddUninitializedImplementation)
				.Function("InsertZeroed", InsertZeroedImplementation)
				.Function("InsertDefaulted", InsertDefaultedImplementation)
				.Function("RemoveAt", RemoveAtImplementation)
				.Function("Reset", ResetImplementation)
				.Function("Empty", EmptyImplementation)
				.Function("SetNum", SetNumImplementation)
				.Function("Add", AddImplementation)
				.Function("AddZeroed", AddZeroedImplementation)
				.Function("AddUnique", AddUniqueImplementation)
				.Function("RemoveSingle", RemoveSingleImplementation)
				.Function("Remove", RemoveImplementation)
				.Function("SwapMemory", SwapMemoryImplementation)
				.Function("Swap", SwapImplementation)
				.Function("INDEX_NONE", INDEX_NONEImplementation);
		}
	};

	[[maybe_unused]] FRegisterArray RegisterArray;
}
