#include "Domain/InternalCall/FMapImplementation.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"
#include "Reflection/Container/FMapHelper.h"
#include "Macro/NamespaceMacro.h"
#include "Async/Async.h"

struct FRegisterMap
{
	FRegisterMap()
	{
		FClassBuilder(TEXT("Map"), NAMESPACE_LIBRARY)
			.Function("Register", FMapImplementation::Map_RegisterImplementation)
			.Function("UnRegister", FMapImplementation::Map_UnRegisterImplementation)
			.Function("Empty", FMapImplementation::Map_EmptyImplementation)
			.Function("Num", FMapImplementation::Map_NumImplementation)
			.Function("Add", FMapImplementation::Map_AddImplementation)
			.Function("Remove", FMapImplementation::Map_RemoveImplementation)
			.Function("FindKey", FMapImplementation::Map_FindKeyImplementation)
			.Function("Find", FMapImplementation::Map_FindImplementation)
			.Function("Contains", FMapImplementation::Map_ContainsImplementation)
			.Function("Get", FMapImplementation::Map_GetImplementation)
			.Function("Set", FMapImplementation::Map_SetImplementation)
			.Function("GetMaxIndex", FMapImplementation::Map_GetMaxIndexImplementation)
			.Function("IsValidIndex", FMapImplementation::Map_IsValidIndexImplementation)
			.Function("GetEnumeratorKey", FMapImplementation::Map_GetEnumeratorKeyImplementation)
			.Function("GetEnumeratorValue", FMapImplementation::Map_GetEnumeratorValueImplementation)
			.Register();
	}
};

static FRegisterMap RegisterMap;

void FMapImplementation::Map_RegisterImplementation(MonoObject* InMonoObject)
{
	FCSharpEnvironment::GetEnvironment().Bind(InMonoObject,
	                                          FTypeBridge::GetGenericArgument(InMonoObject),
	                                          FTypeBridge::GetGenericArgument(InMonoObject, 1));
}

void FMapImplementation::Map_UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	AsyncTask(ENamedThreads::GameThread, [InGarbageCollectionHandle]
	{
		(void)FCSharpEnvironment::GetEnvironment().RemoveContainerReference(InGarbageCollectionHandle);
	});
}

void FMapImplementation::Map_EmptyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                 const int32 InExpectedNumElements)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InGarbageCollectionHandle))
	{
		return MapHelper->Empty(InExpectedNumElements);
	}
}

int32 FMapImplementation::Map_NumImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InGarbageCollectionHandle))
	{
		return MapHelper->Num();
	}

	return 0;
}

void FMapImplementation::Map_AddImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                               MonoObject* InKey, MonoObject* InValue)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InGarbageCollectionHandle))
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

int32 FMapImplementation::Map_RemoveImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                   MonoObject* InKey)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InGarbageCollectionHandle))
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

void FMapImplementation::Map_FindKeyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                   MonoObject* InValue, MonoObject** OutKey)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InGarbageCollectionHandle))
	{
		auto Value = static_cast<void*>(InValue);

		if (MapHelper->GetValuePropertyDescriptor()->IsPrimitiveProperty())
		{
			Value = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InValue);
		}

		const auto Key = MapHelper->FindKey(Value);

		if (MapHelper->GetKeyPropertyDescriptor()->IsPrimitiveProperty())
		{
			*OutKey = FCSharpEnvironment::GetEnvironment().GetDomain()->Value_Box(
				FTypeBridge::GetMonoClass(MapHelper->GetKeyPropertyDescriptor()->GetProperty()), Key);
		}
		else
		{
			MapHelper->GetKeyPropertyDescriptor()->Get(Key, reinterpret_cast<void**>(OutKey));
		}
	}
}

void FMapImplementation::Map_FindImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                MonoObject* InKey, MonoObject** OutValue)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InGarbageCollectionHandle))
	{
		auto Key = static_cast<void*>(InKey);

		if (MapHelper->GetKeyPropertyDescriptor()->IsPrimitiveProperty())
		{
			Key = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InKey);
		}

		const auto Value = MapHelper->Find(Key);

		if (MapHelper->GetValuePropertyDescriptor()->IsPrimitiveProperty())
		{
			*OutValue = FCSharpEnvironment::GetEnvironment().GetDomain()->Value_Box(
				FTypeBridge::GetMonoClass(MapHelper->GetValuePropertyDescriptor()->GetProperty()), Value);
		}
		else
		{
			MapHelper->GetValuePropertyDescriptor()->Get(Value, reinterpret_cast<void**>(OutValue));
		}
	}
}

bool FMapImplementation::Map_ContainsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                    MonoObject* InKey)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InGarbageCollectionHandle))
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

void FMapImplementation::Map_GetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                               MonoObject* InKey, MonoObject** OutValue)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InGarbageCollectionHandle))
	{
		auto Key = static_cast<void*>(InKey);

		if (MapHelper->GetKeyPropertyDescriptor()->IsPrimitiveProperty())
		{
			Key = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InKey);
		}

		const auto Value = MapHelper->Get(Key);

		if (MapHelper->GetValuePropertyDescriptor()->IsPrimitiveProperty())
		{
			*OutValue = FCSharpEnvironment::GetEnvironment().GetDomain()->Value_Box(
				FTypeBridge::GetMonoClass(MapHelper->GetValuePropertyDescriptor()->GetProperty()), Value);
		}
		else
		{
			MapHelper->GetValuePropertyDescriptor()->Get(Value, reinterpret_cast<void**>(OutValue));
		}
	}
}

void FMapImplementation::Map_SetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                               MonoObject* InKey, MonoObject* InValue)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InGarbageCollectionHandle))
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

int32 FMapImplementation::Map_GetMaxIndexImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InGarbageCollectionHandle))
	{
		return MapHelper->GetMaxIndex();
	}

	return 0;
}

bool FMapImplementation::Map_IsValidIndexImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                        const int32 InIndex)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InGarbageCollectionHandle))
	{
		return MapHelper->IsValidIndex(InIndex);
	}

	return false;
}

void FMapImplementation::Map_GetEnumeratorKeyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                            const int32 InIndex, MonoObject** OutKey)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InGarbageCollectionHandle))
	{
		const auto Key = MapHelper->GetEnumeratorKey(InIndex);

		if (MapHelper->GetKeyPropertyDescriptor()->IsPrimitiveProperty())
		{
			*OutKey = FCSharpEnvironment::GetEnvironment().GetDomain()->Value_Box(
				FTypeBridge::GetMonoClass(MapHelper->GetKeyPropertyDescriptor()->GetProperty()), Key);
		}
		else
		{
			MapHelper->GetKeyPropertyDescriptor()->Get(Key, reinterpret_cast<void**>(OutKey));
		}
	}
}

void FMapImplementation::Map_GetEnumeratorValueImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                              const int32 InIndex, MonoObject** OutValue)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InGarbageCollectionHandle))
	{
		const auto Value = MapHelper->GetEnumeratorValue(InIndex);

		if (MapHelper->GetValuePropertyDescriptor()->IsPrimitiveProperty())
		{
			*OutValue = FCSharpEnvironment::GetEnvironment().GetDomain()->Value_Box(
				FTypeBridge::GetMonoClass(MapHelper->GetValuePropertyDescriptor()->GetProperty()), Value);
		}
		else
		{
			MapHelper->GetValuePropertyDescriptor()->Get(Value, reinterpret_cast<void**>(OutValue));
		}
	}
}
