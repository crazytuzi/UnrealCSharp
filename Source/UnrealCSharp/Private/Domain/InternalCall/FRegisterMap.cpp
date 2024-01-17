﻿#include "Registry/FCSharpBind.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"
#include "Reflection/Container/FMapHelper.h"
#include "Macro/NamespaceMacro.h"
#include "Async/Async.h"

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
			(void)FCSharpEnvironment::GetEnvironment().RemoveContainerReference<FMapHelper>(InGarbageCollectionHandle);
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
	                              MonoObject* InKey, MonoObject* InValue)
	{
		if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
			InGarbageCollectionHandle))
		{
			auto Key = static_cast<void*>(InKey);

			auto Value = static_cast<void*>(InValue);

			if (MapHelper->GetKeyPropertyDescriptor()->IsPrimitiveProperty())
			{
				Key = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InKey);
			}

			if (MapHelper->GetValuePropertyDescriptor()->IsPrimitiveProperty())
			{
				Value = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InValue);
			}

			MapHelper->Add(Key, Value);
		}
	}

	static int32 RemoveImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                  MonoObject* InKey)
	{
		if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
			InGarbageCollectionHandle))
		{
			if (MapHelper->GetKeyPropertyDescriptor()->IsPrimitiveProperty())
			{
				return MapHelper->Remove(FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InKey));
			}
			else
			{
				return MapHelper->Remove(InKey);
			}
		}

		return 0;
	}

	static MonoObject* FindKeyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                         MonoObject* InValue)
	{
		MonoObject* ReturnValue{};

		if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
			InGarbageCollectionHandle))
		{
			auto Value = static_cast<void*>(InValue);

			if (MapHelper->GetValuePropertyDescriptor()->IsPrimitiveProperty())
			{
				Value = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InValue);
			}

			const auto Key = MapHelper->FindKey(Value);

			MapHelper->GetKeyPropertyDescriptor()->Get(Key, reinterpret_cast<void**>(&ReturnValue));
		}

		return ReturnValue;
	}

	static MonoObject* FindImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InKey)
	{
		MonoObject* ReturnValue{};

		if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
			InGarbageCollectionHandle))
		{
			auto Key = static_cast<void*>(InKey);

			if (MapHelper->GetKeyPropertyDescriptor()->IsPrimitiveProperty())
			{
				Key = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InKey);
			}

			const auto Value = MapHelper->Find(Key);

			MapHelper->GetValuePropertyDescriptor()->Get(Value, reinterpret_cast<void**>(&ReturnValue));
		}

		return ReturnValue;
	}

	static bool ContainsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                   MonoObject* InKey)
	{
		if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
			InGarbageCollectionHandle))
		{
			if (MapHelper->GetKeyPropertyDescriptor()->IsPrimitiveProperty())
			{
				return MapHelper->Contains(FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InKey));
			}
			else
			{
				return MapHelper->Contains(InKey);
			}
		}

		return false;
	}

	static MonoObject* GetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InKey)
	{
		MonoObject* ReturnValue{};

		if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
			InGarbageCollectionHandle))
		{
			auto Key = static_cast<void*>(InKey);

			if (MapHelper->GetKeyPropertyDescriptor()->IsPrimitiveProperty())
			{
				Key = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InKey);
			}

			const auto Value = MapHelper->Get(Key);

			MapHelper->GetValuePropertyDescriptor()->Get(Value, reinterpret_cast<void**>(&ReturnValue));
		}

		return ReturnValue;
	}

	static void SetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InKey,
	                              MonoObject* InValue)
	{
		if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
			InGarbageCollectionHandle))
		{
			auto Key = static_cast<void*>(InKey);

			auto Value = static_cast<void*>(InValue);

			if (MapHelper->GetKeyPropertyDescriptor()->IsPrimitiveProperty())
			{
				Key = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InKey);
			}

			if (MapHelper->GetValuePropertyDescriptor()->IsPrimitiveProperty())
			{
				Value = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InValue);
			}

			MapHelper->Set(Key, Value);
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

	static MonoObject* GetEnumeratorKeyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                  const int32 InIndex)
	{
		MonoObject* ReturnValue{};

		if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
			InGarbageCollectionHandle))
		{
			const auto Key = MapHelper->GetEnumeratorKey(InIndex);

			MapHelper->GetKeyPropertyDescriptor()->Get(Key, reinterpret_cast<void**>(&ReturnValue));
		}

		return ReturnValue;
	}

	static MonoObject* GetEnumeratorValueImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                    const int32 InIndex)
	{
		MonoObject* ReturnValue{};

		if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
			InGarbageCollectionHandle))
		{
			const auto Value = MapHelper->GetEnumeratorValue(InIndex);

			MapHelper->GetValuePropertyDescriptor()->Get(Value, reinterpret_cast<void**>(&ReturnValue));
		}

		return ReturnValue;
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
			.Register();
	}
};

static FRegisterMap RegisterMap;
