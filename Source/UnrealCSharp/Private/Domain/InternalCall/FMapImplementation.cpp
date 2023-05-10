#include "Domain/InternalCall/FMapImplementation.h"
#include "Binding/Class/FBindingClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"
#include "Reflection/Container/FMapHelper.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterMap
{
	FRegisterMap()
	{
		FBindingClassBuilder(TEXT("Map"), NAMESPACE_LIBRARY)
			.Function("Register", static_cast<void*>(FMapImplementation::Map_RegisterImplementation))
			.Function("UnRegister", static_cast<void*>(FMapImplementation::Map_UnRegisterImplementation))
			.Function("Empty", static_cast<void*>(FMapImplementation::Map_EmptyImplementation))
			.Function("Num", static_cast<void*>(FMapImplementation::Map_NumImplementation))
			.Function("Add", static_cast<void*>(FMapImplementation::Map_AddImplementation))
			.Function("Remove", static_cast<void*>(FMapImplementation::Map_RemoveImplementation))
			.Function("FindKey", static_cast<void*>(FMapImplementation::Map_FindKeyImplementation))
			.Function("Find", static_cast<void*>(FMapImplementation::Map_FindImplementation))
			.Function("Contains", static_cast<void*>(FMapImplementation::Map_ContainsImplementation))
			.Function("Get", static_cast<void*>(FMapImplementation::Map_GetImplementation))
			.Function("Set", static_cast<void*>(FMapImplementation::Map_SetImplementation))
			.Function("GetMaxIndex", static_cast<void*>(FMapImplementation::Map_GetMaxIndexImplementation))
			.Function("IsValidIndex", static_cast<void*>(FMapImplementation::Map_IsValidIndexImplementation))
			.Function("GetEnumeratorKey", static_cast<void*>(FMapImplementation::Map_GetEnumeratorKeyImplementation))
			.Function("GetEnumeratorValue",
			          static_cast<void*>(FMapImplementation::Map_GetEnumeratorValueImplementation))
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

void FMapImplementation::Map_UnRegisterImplementation(const MonoObject* InMonoObject)
{
	(void)FCSharpEnvironment::GetEnvironment().RemoveContainerReference(InMonoObject);
}

void FMapImplementation::Map_EmptyImplementation(const MonoObject* InMonoObject, const int32 InExpectedNumElements)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InMonoObject))
	{
		return MapHelper->Empty(InExpectedNumElements);
	}
}

int32 FMapImplementation::Map_NumImplementation(const MonoObject* InMonoObject)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InMonoObject))
	{
		return MapHelper->Num();
	}

	return 0;
}

void FMapImplementation::Map_AddImplementation(const MonoObject* InMonoObject, MonoObject* InKey, MonoObject* InValue)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InMonoObject))
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

int32 FMapImplementation::Map_RemoveImplementation(const MonoObject* InMonoObject, MonoObject* InKey)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InMonoObject))
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

void FMapImplementation::Map_FindKeyImplementation(const MonoObject* InMonoObject, MonoObject* InValue,
                                                   MonoObject** OutKey)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InMonoObject))
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

void FMapImplementation::Map_FindImplementation(const MonoObject* InMonoObject, MonoObject* InKey,
                                                MonoObject** OutValue)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InMonoObject))
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

bool FMapImplementation::Map_ContainsImplementation(const MonoObject* InMonoObject, MonoObject* InKey)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InMonoObject))
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

void FMapImplementation::Map_GetImplementation(const MonoObject* InMonoObject, MonoObject* InKey, MonoObject** OutValue)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InMonoObject))
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

void FMapImplementation::Map_SetImplementation(const MonoObject* InMonoObject, MonoObject* InKey, MonoObject* InValue)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InMonoObject))
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

int32 FMapImplementation::Map_GetMaxIndexImplementation(const MonoObject* InMonoObject)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InMonoObject))
	{
		return MapHelper->GetMaxIndex();
	}

	return 0;
}

bool FMapImplementation::Map_IsValidIndexImplementation(const MonoObject* InMonoObject, const int32 InIndex)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InMonoObject))
	{
		return MapHelper->IsValidIndex(InIndex);
	}

	return false;
}

void FMapImplementation::Map_GetEnumeratorKeyImplementation(const MonoObject* InMonoObject, const int32 InIndex,
                                                            MonoObject** OutKey)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InMonoObject))
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

void FMapImplementation::Map_GetEnumeratorValueImplementation(const MonoObject* InMonoObject, const int32 InIndex,
                                                              MonoObject** OutValue)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(InMonoObject))
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
