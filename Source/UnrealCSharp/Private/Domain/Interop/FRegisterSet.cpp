#include "Registry/FCSharpBind.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Container/FSetHelper.h"
#include "Reflection/FReflectionRegistry.h"
#include "CoreMacro/BufferMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterSet
	{
		static void RegisterImplementation(const IManagedHandle InManagedObject, const IManagedHandle InManagedType)
		{
			if (const auto Class = FReflectionRegistry::Get().GetClass(InManagedType))
			{
				FCSharpBind::Bind<FSetHelper>(Class, Class->GetGenericArgument(), InManagedObject);
			}
		}

		static void UnRegisterImplementation(const IManagedHandle InManagedHandle)
		{
			if (IsInGameThread())
			{
				(void)FCSharpEnvironment::GetEnvironment().RemoveContainerReference<FSetHelper>(InManagedHandle);
			}
			else
			{
				AsyncTask(ENamedThreads::GameThread, [InManagedHandle]
				{
					(void)FCSharpEnvironment::GetEnvironment().RemoveContainerReference<FSetHelper>(InManagedHandle);
				});
			}
		}

		static void EmptyImplementation(const IManagedHandle InManagedHandle, const int32 InExpectedNumElements)
		{
			if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(InManagedHandle))
			{
				SetHelper->Empty(InExpectedNumElements);
			}
		}

		static int32 NumImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(InManagedHandle))
			{
				return SetHelper->Num();
			}

			return 0;
		}

		static uint8 IsEmptyImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(InManagedHandle))
			{
				return SetHelper->IsEmpty() ? 1 : 0;
			}

			return 0;
		}

		static int32 GetMaxIndexImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(InManagedHandle))
			{
				return SetHelper->GetMaxIndex();
			}

			return 0;
		}

		static void AddImplementation(const IManagedHandle InManagedHandle, IN_VALUE_BUFFER_SIGNATURE)
		{
			if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(InManagedHandle))
			{
				SetHelper->Add(IN_VALUE_BUFFER);
			}
		}

		static int32 RemoveImplementation(const IManagedHandle InManagedHandle, const IN_VALUE_BUFFER_SIGNATURE)
		{
			if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(InManagedHandle))
			{
				return SetHelper->Remove(IN_VALUE_BUFFER);
			}

			return 0;
		}

		static uint8 ContainsImplementation(const IManagedHandle InManagedHandle, const IN_VALUE_BUFFER_SIGNATURE)
		{
			if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(InManagedHandle))
			{
				return SetHelper->Contains(IN_VALUE_BUFFER) ? 1 : 0;
			}

			return 0;
		}

		static uint8 IsValidIndexImplementation(const IManagedHandle InManagedHandle, const int32 InIndex)
		{
			if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(InManagedHandle))
			{
				return SetHelper->IsValidIndex(InIndex) ? 1 : 0;
			}

			return 0;
		}

		static void GetEnumeratorImplementation(const IManagedHandle InManagedHandle,
		                                        const int32 InIndex, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(InManagedHandle))
			{
				if (const auto Value = SetHelper->GetEnumerator(InIndex))
				{
					SetHelper->GetElementPropertyDescriptor()->Get(Value, reinterpret_cast<void**>(RETURN_BUFFER));
				}
				else
				{
					FPropertyDescriptor::GetDefaultValue(SetHelper->GetElementPropertyDescriptor(), RETURN_BUFFER);
				}
			}
		}

		static int32 GetTypeSizeImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(InManagedHandle))
			{
				return SetHelper->GetElementPropertyDescriptor() != nullptr
					       ? SetHelper->GetElementPropertyDescriptor()->GetBufferSize()
					       : 0;
			}

			return 0;
		}

		static int32 GetElementsImplementation(const IManagedHandle InManagedHandle, const int32 InIndex,
		                                       const int32 InCount, uint8* OutBuffer, const int32 InBufferSize,
		                                       int32* OutNextIndex)
		{
			if (OutNextIndex != nullptr)
			{
				*OutNextIndex = InIndex;
			}

			if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(InManagedHandle))
			{
				const auto ElementSize = SetHelper->GetElementPropertyDescriptor() != nullptr
					                         ? SetHelper->GetElementPropertyDescriptor()->GetBufferSize()
					                         : 0;

				if (ElementSize > 0 && InIndex >= 0 && InCount > 0 && OutBuffer != nullptr &&
					static_cast<int64>(InCount) * ElementSize <= InBufferSize)
				{
					const auto MaxIndex = SetHelper->GetMaxIndex();

					auto Index = InIndex;

					auto Count = 0;

					for (; Index < MaxIndex && Count < InCount; ++Index)
					{
						if (SetHelper->IsValidIndex(Index))
						{
							FMemory::Memcpy(OutBuffer + static_cast<int64>(Count) * ElementSize,
							                SetHelper->GetEnumerator(Index), ElementSize);

							++Count;
						}
					}

					if (OutNextIndex != nullptr)
					{
						*OutNextIndex = Index;
					}

					return Count;
				}
			}

			return 0;
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
				.Function("GetEnumerator", GetEnumeratorImplementation)
				.Function("GetTypeSize", GetTypeSizeImplementation)
				.Function("GetElements", GetElementsImplementation);
		}
	};

	[[maybe_unused]] FRegisterSet RegisterSet;
}
