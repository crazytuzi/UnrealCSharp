#include "Domain/InternalCall/FMapImplementation.h"
#include "Bridge/FTypeBridge.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Container/FMapHelper.h"

void FMapImplementation::RegisterMapImplementation(MonoObject InMonoObject, MonoReflectionType* InKeyReflectionType,
                                                   MonoReflectionType* InValueReflectionType)
{
	FCSharpEnvironment::GetEnvironment()->Bind(&InMonoObject, InKeyReflectionType, InValueReflectionType);
}

void FMapImplementation::UnRegisterMapImplementation(MonoObject InMonoObject)
{
	FCSharpEnvironment::GetEnvironment()->RemoveContainerReference<FMapHelper>(&InMonoObject);
}

void FMapImplementation::Map_EmptyImplementation(MonoObject InMonoObject, const int32 InExpectedNumElements)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FMapHelper>(&InMonoObject))
	{
		return MapHelper->Empty(InExpectedNumElements);
	}
}

int32 FMapImplementation::Map_NumImplementation(MonoObject InMonoObject)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FMapHelper>(&InMonoObject))
	{
		return MapHelper->Num();
	}

	return 0;
}

void FMapImplementation::Map_AddImplementation(MonoObject InMonoObject, void* InKey, void* InValue)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FMapHelper>(&InMonoObject))
	{
		MapHelper->Add(&InKey, &InValue);
	}
}

int32 FMapImplementation::Map_RemoveImplementation(MonoObject InMonoObject, void* InKey)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FMapHelper>(&InMonoObject))
	{
		return MapHelper->Remove(&InKey);
	}

	return 0;
}

void FMapImplementation::Map_FindKeyImplementation(MonoObject InMonoObject, void* InValue, MonoObject** OutKey)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FMapHelper>(&InMonoObject))
	{
		const auto Key = MapHelper->FindKey(&InValue);

		if (MapHelper->IsKeyPrimitiveProperty())
		{
			*OutKey = FCSharpEnvironment::GetEnvironment()->GetDomain()->Value_Box(
				FTypeBridge::GetMonoClass(MapHelper->GetKeyProperty()), Key);
		}
		else
		{
			*OutKey = static_cast<MonoObject*>(Key);
		}
	}
}

void FMapImplementation::Map_FindImplementation(MonoObject InMonoObject, void* InKey, MonoObject** OutValue)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FMapHelper>(&InMonoObject))
	{
		const auto Value = MapHelper->Find(&InKey);

		if (MapHelper->IsValuePrimitiveProperty())
		{
			*OutValue = FCSharpEnvironment::GetEnvironment()->GetDomain()->Value_Box(
				FTypeBridge::GetMonoClass(MapHelper->GetValueProperty()), Value);
		}
		else
		{
			*OutValue = static_cast<MonoObject*>(Value);
		}
	}
}

bool FMapImplementation::Map_ContainsImplementation(MonoObject InMonoObject, const void* InKey)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FMapHelper>(&InMonoObject))
	{
		return MapHelper->Contains(&InKey);
	}

	return false;
}

void FMapImplementation::Map_GetImplementation(MonoObject InMonoObject, void* InKey, MonoObject** OutValue)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FMapHelper>(&InMonoObject))
	{
		const auto Value = MapHelper->Get(&InKey);

		if (MapHelper->IsValuePrimitiveProperty())
		{
			*OutValue = FCSharpEnvironment::GetEnvironment()->GetDomain()->Value_Box(
				FTypeBridge::GetMonoClass(MapHelper->GetValueProperty()), Value);
		}
		else
		{
			*OutValue = static_cast<MonoObject*>(Value);
		}
	}
}

void FMapImplementation::Map_SetImplementation(MonoObject InMonoObject, void* InKey, void* InValue)
{
	if (const auto MapHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FMapHelper>(&InMonoObject))
	{
		MapHelper->Set(&InKey, &InValue);
	}
}
