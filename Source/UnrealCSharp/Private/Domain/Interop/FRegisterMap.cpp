#include "Registry/FCSharpBind.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Container/FMapHelper.h"
#include "CoreMacro/BufferMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterMap
	{
		static void RegisterImplementation(const IManagedHandle InManagedObject, const IManagedHandle InManagedType)
		{
			if (const auto Class = FReflectionRegistry::Get().GetClass(InManagedType))
			{
				FCSharpBind::Bind<FMapHelper>(Class,
				                              Class->GetGenericArgument(),
				                              Class->GetGenericArgument(1),
				                              InManagedObject);
			}
		}

		static void UnRegisterImplementation(const IManagedHandle InManagedHandle)
		{
			if (IsInGameThread())
			{
				(void)FCSharpEnvironment::GetEnvironment().RemoveContainerReference<FMapHelper>(
					InManagedHandle);
			}
			else
			{
				AsyncTask(ENamedThreads::GameThread, [InManagedHandle]
				{
					(void)FCSharpEnvironment::GetEnvironment().RemoveContainerReference<FMapHelper>(
						InManagedHandle);
				});
			}
		}

		static void EmptyImplementation(const IManagedHandle InManagedHandle, const int32 InExpectedNumElements)
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

		static uint8 IsEmptyImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InManagedHandle))
			{
				return MapHelper->IsEmpty() ? 1 : 0;
			}

			return 0;
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
				if (const auto Key = MapHelper->FindKey(IN_VALUE_BUFFER))
				{
					MapHelper->GetKeyPropertyDescriptor()->Get(Key, reinterpret_cast<void**>(RETURN_BUFFER));
				}
				else
				{
					FPropertyDescriptor::GetDefaultValue(MapHelper->GetKeyPropertyDescriptor(), RETURN_BUFFER);
				}
			}
		}

		static void FindImplementation(const IManagedHandle InManagedHandle,
		                               const IN_KEY_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InManagedHandle))
			{
				if (const auto Value = MapHelper->Find(IN_KEY_BUFFER))
				{
					MapHelper->GetValuePropertyDescriptor()->Get(Value, reinterpret_cast<void**>(RETURN_BUFFER));
				}
				else
				{
					FPropertyDescriptor::GetDefaultValue(MapHelper->GetValuePropertyDescriptor(), RETURN_BUFFER);
				}
			}
		}

		static uint8 ContainsImplementation(const IManagedHandle InManagedHandle, const IN_KEY_BUFFER_SIGNATURE)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InManagedHandle))
			{
				return MapHelper->Contains(IN_KEY_BUFFER) ? 1 : 0;
			}

			return 0;
		}

		static void GetImplementation(const IManagedHandle InManagedHandle,
		                              const IN_KEY_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InManagedHandle))
			{
				if (const auto Value = MapHelper->Get(IN_KEY_BUFFER))
				{
					MapHelper->GetValuePropertyDescriptor()->Get(Value, reinterpret_cast<void**>(RETURN_BUFFER));
				}
				else
				{
					FPropertyDescriptor::GetDefaultValue(MapHelper->GetValuePropertyDescriptor(), RETURN_BUFFER);
				}
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

		static uint8 IsValidIndexImplementation(const IManagedHandle InManagedHandle, const int32 InIndex)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InManagedHandle))
			{
				return MapHelper->IsValidIndex(InIndex) ? 1 : 0;
			}

			return 0;
		}

		static void GetEnumeratorKeyImplementation(const IManagedHandle InManagedHandle,
		                                           const int32 InIndex, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InManagedHandle))
			{
				if (const auto Key = MapHelper->GetEnumeratorKey(InIndex))
				{
					MapHelper->GetKeyPropertyDescriptor()->Get(Key, reinterpret_cast<void**>(RETURN_BUFFER));
				}
				else
				{
					FPropertyDescriptor::GetDefaultValue(MapHelper->GetKeyPropertyDescriptor(), RETURN_BUFFER);
				}
			}
		}

		static void GetEnumeratorValueImplementation(const IManagedHandle InManagedHandle,
		                                             const int32 InIndex, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InManagedHandle))
			{
				if (const auto Value = MapHelper->GetEnumeratorValue(InIndex))
				{
					MapHelper->GetValuePropertyDescriptor()->Get(Value, reinterpret_cast<void**>(RETURN_BUFFER));
				}
				else
				{
					FPropertyDescriptor::GetDefaultValue(MapHelper->GetValuePropertyDescriptor(), RETURN_BUFFER);
				}
			}
		}

		static int32 GetKeyTypeSizeImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InManagedHandle))
			{
				return MapHelper->GetKeyPropertyDescriptor() != nullptr
					       ? MapHelper->GetKeyPropertyDescriptor()->GetBufferSize()
					       : 0;
			}

			return 0;
		}

		static int32 GetValueTypeSizeImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InManagedHandle))
			{
				return MapHelper->GetValuePropertyDescriptor() != nullptr
					       ? MapHelper->GetValuePropertyDescriptor()->GetBufferSize()
					       : 0;
			}

			return 0;
		}

		static int32 GetPairsImplementation(const IManagedHandle InManagedHandle, const int32 InIndex,
		                                    const int32 InCount, uint8* OutBuffer, const int32 InBufferSize,
		                                    int32* OutNextIndex)
		{
			if (OutNextIndex != nullptr)
			{
				*OutNextIndex = InIndex;
			}

			if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
				InManagedHandle))
			{
				const auto KeySize = MapHelper->GetKeyPropertyDescriptor() != nullptr
					                     ? MapHelper->GetKeyPropertyDescriptor()->GetBufferSize()
					                     : 0;

				const auto ValueSize = MapHelper->GetValuePropertyDescriptor() != nullptr
					                       ? MapHelper->GetValuePropertyDescriptor()->GetBufferSize()
					                       : 0;

				if (const auto PairSize = KeySize + ValueSize;
					KeySize > 0 && ValueSize > 0 && InIndex >= 0 && InCount > 0 && OutBuffer != nullptr &&
					static_cast<int64>(InCount) * PairSize <= InBufferSize)
				{
					const auto MaxIndex = MapHelper->GetMaxIndex();

					auto Index = InIndex;

					auto Count = 0;

					for (; Index < MaxIndex && Count < InCount; ++Index)
					{
						if (MapHelper->IsValidIndex(Index))
						{
							FMemory::Memcpy(OutBuffer + static_cast<int64>(Count) * PairSize,
							                MapHelper->GetEnumeratorKey(Index), KeySize);

							FMemory::Memcpy(OutBuffer + static_cast<int64>(Count) * PairSize + KeySize,
							                MapHelper->GetEnumeratorValue(Index), ValueSize);

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
				.Function("GetEnumeratorValue", GetEnumeratorValueImplementation)
				.Function("GetKeyTypeSize", GetKeyTypeSizeImplementation)
				.Function("GetValueTypeSize", GetValueTypeSizeImplementation)
				.Function("GetPairs", GetPairsImplementation);
		}
	};

	[[maybe_unused]] FRegisterMap RegisterMap;
}
