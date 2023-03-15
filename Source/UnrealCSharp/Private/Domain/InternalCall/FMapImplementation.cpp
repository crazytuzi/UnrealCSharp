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
		FBindingClassBuilder(TEXT("Map"), NAMESPACE_CONTAINER)
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
			.Register();
	}
};

static FRegisterMap RegisterMap;

void FMapImplementation::Map_RegisterImplementation(MonoObject* InMonoObject)
{
	FCSharpEnvironment::GetEnvironment()->Bind(InMonoObject,
	                                           FTypeBridge::GetGenericArgument(InMonoObject),
	                                           FTypeBridge::GetGenericArgument(InMonoObject, 1));
}

void FMapImplementation::Map_UnRegisterImplementation(const MonoObject* InMonoObject)
{
	FCSharpEnvironment::GetEnvironment()->RemoveContainerReference(InMonoObject);
}

void FMapImplementation::Map_EmptyImplementation(const MonoObject* InMonoObject, const int32 InExpectedNumElements)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FMapHelper>(InMonoObject))
	{
		return MapHelper->Empty(InExpectedNumElements);
	}
}

int32 FMapImplementation::Map_NumImplementation(const MonoObject* InMonoObject)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FMapHelper>(InMonoObject))
	{
		return MapHelper->Num();
	}

	return 0;
}

void FMapImplementation::Map_AddImplementation(const MonoObject* InMonoObject, void* InKey, void* InValue)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FMapHelper>(InMonoObject))
	{
		MapHelper->Add(&InKey, &InValue);
	}
}

int32 FMapImplementation::Map_RemoveImplementation(const MonoObject* InMonoObject, void* InKey)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FMapHelper>(InMonoObject))
	{
		return MapHelper->Remove(&InKey);
	}

	return 0;
}

void FMapImplementation::Map_FindKeyImplementation(const MonoObject* InMonoObject, void* InValue, MonoObject** OutKey)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FMapHelper>(InMonoObject))
	{
		const auto Key = MapHelper->FindKey(&InValue);

		if (MapHelper->GetKeyPropertyDescriptor()->IsPrimitiveProperty())
		{
			*OutKey = FCSharpEnvironment::GetEnvironment()->GetDomain()->Value_Box(
				FTypeBridge::GetMonoClass(MapHelper->GetKeyPropertyDescriptor()->GetProperty()), Key);
		}
		else
		{
			MapHelper->GetKeyPropertyDescriptor()->Get(Key, reinterpret_cast<void**>(OutKey));
		}
	}
}

void FMapImplementation::Map_FindImplementation(const MonoObject* InMonoObject, void* InKey, MonoObject** OutValue)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FMapHelper>(InMonoObject))
	{
		const auto Value = MapHelper->Find(&InKey);

		if (MapHelper->GetValuePropertyDescriptor()->IsPrimitiveProperty())
		{
			*OutValue = FCSharpEnvironment::GetEnvironment()->GetDomain()->Value_Box(
				FTypeBridge::GetMonoClass(MapHelper->GetValuePropertyDescriptor()->GetProperty()), Value);
		}
		else
		{
			MapHelper->GetValuePropertyDescriptor()->Get(Value, reinterpret_cast<void**>(OutValue));
		}
	}
}

bool FMapImplementation::Map_ContainsImplementation(const MonoObject* InMonoObject, const void* InKey)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FMapHelper>(InMonoObject))
	{
		return MapHelper->Contains(&InKey);
	}

	return false;
}

void FMapImplementation::Map_GetImplementation(const MonoObject* InMonoObject, void* InKey, MonoObject** OutValue)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FMapHelper>(InMonoObject))
	{
		const auto Value = MapHelper->Get(&InKey);

		if (MapHelper->GetValuePropertyDescriptor()->IsPrimitiveProperty())
		{
			*OutValue = FCSharpEnvironment::GetEnvironment()->GetDomain()->Value_Box(
				FTypeBridge::GetMonoClass(MapHelper->GetValuePropertyDescriptor()->GetProperty()), Value);
		}
		else
		{
			MapHelper->GetValuePropertyDescriptor()->Get(Value, reinterpret_cast<void**>(OutValue));
		}
	}
}

void FMapImplementation::Map_SetImplementation(const MonoObject* InMonoObject, void* InKey, void* InValue)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FMapHelper>(InMonoObject))
	{
		MapHelper->Set(&InKey, &InValue);
	}
}
