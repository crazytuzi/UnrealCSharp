#include "Registry/FCSharpBind.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"
#include "Reflection/Container/FArrayHelper.h"
#include "CoreMacro/BufferMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterArray
	{
		static void RegisterImplementation(MonoObject* InMonoObject)
		{
			FCSharpBind::Bind<FArrayHelper>(InMonoObject, FTypeBridge::GetGenericArgument(InMonoObject));
		}

		static bool IdenticalImplementation(const FGarbageCollectionHandle InA, const FGarbageCollectionHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InB))
				{
					return FArrayHelper::Identical(FoundA, FoundB);
				}
			}

			return false;
		}

		static void UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			AsyncTask(ENamedThreads::GameThread, [InGarbageCollectionHandle]
			{
				(void)FCSharpEnvironment::GetEnvironment().RemoveContainerReference<
					FArrayHelper>(InGarbageCollectionHandle);
			});
		}

		static int32 GetTypeSizeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InGarbageCollectionHandle))
			{
				return ArrayHelper->GetTypeSize();
			}

			return 0;
		}

		static int32 GetSlackImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InGarbageCollectionHandle))
			{
				return ArrayHelper->GetSlack();
			}

			return 0;
		}

		static bool IsValidIndexImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                       const int32 InIndex)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InGarbageCollectionHandle))
			{
				return ArrayHelper->IsValidIndex(InIndex);
			}

			return false;
		}

		static int32 NumImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InGarbageCollectionHandle))
			{
				return ArrayHelper->Num();
			}

			return 0;
		}

		static bool IsEmptyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InGarbageCollectionHandle))
			{
				return ArrayHelper->IsEmpty();
			}

			return false;
		}

		static int32 MaxImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InGarbageCollectionHandle))
			{
				return ArrayHelper->Max();
			}

			return 0;
		}

		static void GetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                              const int32 InIndex, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InGarbageCollectionHandle))
			{
				const auto Value = ArrayHelper->Get(InIndex);

				ArrayHelper->GetInnerPropertyDescriptor()->Get(Value, reinterpret_cast<void**>(RETURN_BUFFER));
			}
		}

		static void SetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                              const int32 InIndex, IN_VALUE_BUFFER_SIGNATURE)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InGarbageCollectionHandle))
			{
				ArrayHelper->Set(InIndex, IN_VALUE_BUFFER);
			}
		}

		static int32 FindImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                const IN_VALUE_BUFFER_SIGNATURE)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InGarbageCollectionHandle))
			{
				return ArrayHelper->Find(IN_VALUE_BUFFER);
			}

			return INDEX_NONE;
		}

		static int32 FindLastImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                    const IN_VALUE_BUFFER_SIGNATURE)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InGarbageCollectionHandle))
			{
				return ArrayHelper->FindLast(IN_VALUE_BUFFER);
			}

			return INDEX_NONE;
		}

		static bool ContainsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                   const IN_VALUE_BUFFER_SIGNATURE)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InGarbageCollectionHandle))
			{
				return ArrayHelper->Contains(IN_VALUE_BUFFER);
			}

			return false;
		}

		static int32 AddUninitializedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                            const int32 InCount)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InGarbageCollectionHandle))
			{
				return ArrayHelper->AddUninitialized(InCount);
			}

			return 0;
		}

		static void InsertZeroedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                       const int32 InIndex, const int32 InCount)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InGarbageCollectionHandle))
			{
				ArrayHelper->InsertZeroed(InIndex, InCount);
			}
		}

		static void InsertDefaultedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                          const int32 InIndex, const int32 InCount)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InGarbageCollectionHandle))
			{
				ArrayHelper->InsertDefaulted(InIndex, InCount);
			}
		}

		static void RemoveAtImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                   const int32 InIndex, const int32 InCount, const bool bAllowShrinking)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InGarbageCollectionHandle))
			{
				ArrayHelper->RemoveAt(InIndex, InCount, bAllowShrinking);
			}
		}

		static void ResetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                const int32 InNewSize)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InGarbageCollectionHandle))
			{
				return ArrayHelper->Reset(InNewSize);
			}
		}

		static void EmptyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                const int32 InSlack)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InGarbageCollectionHandle))
			{
				return ArrayHelper->Empty(InSlack);
			}
		}

		static void SetNumImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                 const int32 InNewNum, const bool bAllowShrinking)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InGarbageCollectionHandle))
			{
				return ArrayHelper->SetNum(InNewNum, bAllowShrinking);
			}
		}

		static int32 AddImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                               IN_VALUE_BUFFER_SIGNATURE)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InGarbageCollectionHandle))
			{
				return ArrayHelper->Add(IN_VALUE_BUFFER);
			}

			return 0;
		}

		static int32 AddZeroedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                     const int32 InCount)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InGarbageCollectionHandle))
			{
				return ArrayHelper->AddZeroed(InCount);
			}

			return 0;
		}

		static int32 AddUniqueImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                     IN_VALUE_BUFFER_SIGNATURE)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InGarbageCollectionHandle))
			{
				return ArrayHelper->AddUnique(IN_VALUE_BUFFER);
			}

			return 0;
		}

		static int32 RemoveSingleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                        const IN_VALUE_BUFFER_SIGNATURE)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InGarbageCollectionHandle))
			{
				return ArrayHelper->RemoveSingle(IN_VALUE_BUFFER);
			}

			return 0;
		}

		static int32 RemoveImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                  const IN_VALUE_BUFFER_SIGNATURE)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InGarbageCollectionHandle))
			{
				return ArrayHelper->Remove(IN_VALUE_BUFFER);
			}

			return 0;
		}

		static void SwapMemoryImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                     const int32 InFirstIndexToSwap, const int32 InSecondIndexToSwap)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InGarbageCollectionHandle))
			{
				ArrayHelper->SwapMemory(InFirstIndexToSwap, InSecondIndexToSwap);
			}
		}

		static void SwapImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                               const int32 InFirstIndexToSwap, const int32 InSecondIndexToSwap)
		{
			if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
				InGarbageCollectionHandle))
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
