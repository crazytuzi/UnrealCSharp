#include "Domain/InternalCall/FSetImplementation.h"
#include "Binding/Class/FBindingClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Container/FSetHelper.h"
#include "Macro/NamespaceMacro.h"
#include "Bridge/FTypeBridge.h"

struct FRegisterSet
{
	FRegisterSet()
	{
		FBindingClassBuilder(TEXT("Set"), NAMESPACE_LIBRARY)
			.Function("Register", static_cast<void*>(FSetImplementation::Set_RegisterImplementation))
			.Function("UnRegister", static_cast<void*>(FSetImplementation::Set_UnRegisterImplementation))
			.Function("Empty", static_cast<void*>(FSetImplementation::Set_EmptyImplementation))
			.Function("Num", static_cast<void*>(FSetImplementation::Set_NumImplementation))
			.Function("Add", static_cast<void*>(FSetImplementation::Set_AddImplementation))
			.Function("Remove", static_cast<void*>(FSetImplementation::Set_RemoveImplementation))
			.Function("Contains", static_cast<void*>(FSetImplementation::Set_ContainsImplementation))
			.Function("ToArray",static_cast<void*>(FSetImplementation::Set_ToArrayImplementation))
			.Function("Find",static_cast<void*>(FSetImplementation::Set_FindImplementation))
			.Function("GetMaxIndex",static_cast<void*>(FSetImplementation::Set_GetMaxIndexImplementation))
			.Function("Union",static_cast<void*>(FSetImplementation::Set_UnionImplementation))
			.Function("Get",static_cast<void*>(FSetImplementation::Set_GetImplementation))
			.Function("Set",static_cast<void*>(FSetImplementation::Set_SetImplementation))
			.Register();
	}
};

static FRegisterSet RegisterSet;

void FSetImplementation::Set_RegisterImplementation(MonoObject* InMonoObject)
{
	FCSharpEnvironment::GetEnvironment()->Bind<FSetHelper>(InMonoObject,
	                                                       FTypeBridge::GetGenericArgument(InMonoObject));
}

void FSetImplementation::Set_UnRegisterImplementation(const MonoObject* InMonoObject)
{
	FCSharpEnvironment::GetEnvironment()->RemoveContainerReference(InMonoObject);
}

void FSetImplementation::Set_EmptyImplementation(const MonoObject* InMonoObject, const int32 InExpectedNumElements)
{
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FSetHelper>(InMonoObject))
	{
		SetHelper->Empty(InExpectedNumElements);
	}
}

int32 FSetImplementation::Set_NumImplementation(const MonoObject* InMonoObject)
{
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FSetHelper>(InMonoObject))
	{
		return SetHelper->Num();
	}

	return 0;
}

void FSetImplementation::Set_AddImplementation(const MonoObject* InMonoObject, void* InElement)
{
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FSetHelper>(InMonoObject))
	{
		return SetHelper->Add(&InElement);
	}
}

int32 FSetImplementation::Set_RemoveImplementation(const MonoObject* InMonoObject, void* InKey)
{
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FSetHelper>(InMonoObject))
	{
		return SetHelper->Remove(&InKey);
	}

	return 0;
}

bool FSetImplementation::Set_ContainsImplementation(const MonoObject* InMonoObject, const void* InKey)
{
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FSetHelper>(InMonoObject))
	{
		return SetHelper->Contains(&InKey);
	}

	return false;
}
TArray<FProperty*> FSetImplementation::Set_ToArrayImplementation(const MonoObject* InMonoObject)
{
	TArray<FProperty*> Array;
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FSetHelper>(InMonoObject))
	{
		Array=SetHelper->ToArray();
	}

	return Array;
}

int32 FSetImplementation::Set_FindImplementation(const MonoObject* InMonoObject,void* Value)
{
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FSetHelper>(InMonoObject))
	{
		return SetHelper->Find(&Value);
	}
	return 0;
}

int32 FSetImplementation::Set_GetMaxIndexImplementation(const MonoObject* InMonoObject)
{
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FSetHelper>(InMonoObject))
	{
		return SetHelper->GetMaxIndex();
	}
	else
	{
		return 0;
	}
}

TSet<void*> FSetImplementation::Set_UnionImplementation(const MonoObject* InMonoObject,TSet<void*> OtherSet)
{
	TSet<void*> NewSet;
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FSetHelper>(InMonoObject))
	{
		NewSet= SetHelper->Union(OtherSet);
	}
	return NewSet;
}

void FSetImplementation::Set_GetImplementation(const MonoObject* InMonoObject, int32 Index ,MonoObject** OutValue)
{
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FSetHelper>(InMonoObject))
	{
		const auto Value = SetHelper->Get(Index);

		if (SetHelper->GetElementPropertyDescriptor()->IsPrimitiveProperty())
		{
			*OutValue = FCSharpEnvironment::GetEnvironment()->GetDomain()->Value_Box(
				FTypeBridge::GetMonoClass(SetHelper->GetElementPropertyDescriptor()->GetProperty()), Value);
		}
		else
		{
			SetHelper->GetElementPropertyDescriptor()->Get(Value, reinterpret_cast<void**>(OutValue));
		}
	}
}

void FSetImplementation::Set_SetImplementation(const MonoObject* InMonoObject, int32 Index, MonoObject* InValue)
{
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FSetHelper>(InMonoObject))
	{
		SetHelper->Set(Index, &InValue);
	}
}
