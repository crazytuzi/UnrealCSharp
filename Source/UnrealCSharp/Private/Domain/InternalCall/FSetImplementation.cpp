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
			.Function("IsValidIndex", static_cast<void*>(FSetImplementation::Set_IsValidIndexImplementation))
			.Function("GetEnumerator", static_cast<void*>(FSetImplementation::Set_GetEnumeratorImplementation))
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

void FSetImplementation::Set_AddImplementation(const MonoObject* InMonoObject, MonoObject* InValue)
{
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FSetHelper>(InMonoObject))
	{
		if (SetHelper->GetElementPropertyDescriptor()->IsPrimitiveProperty())
		{
			SetHelper->Add(FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_Unbox(InValue));
		}
		else
		{
			SetHelper->Add(InValue);
		}
	}
}

int32 FSetImplementation::Set_RemoveImplementation(const MonoObject* InMonoObject, MonoObject* InValue)
{
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FSetHelper>(InMonoObject))
	{
		if (SetHelper->GetElementPropertyDescriptor()->IsPrimitiveProperty())
		{
			return SetHelper->Remove(FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_Unbox(InValue));
		}
		else
		{
			return SetHelper->Remove(InValue);
		}
	}

	return 0;
}

bool FSetImplementation::Set_ContainsImplementation(const MonoObject* InMonoObject, MonoObject* InValue)
{
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FSetHelper>(InMonoObject))
	{
		if (SetHelper->GetElementPropertyDescriptor()->IsPrimitiveProperty())
		{
			return SetHelper->Contains(FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_Unbox(InValue));
		}
		else
		{
			return SetHelper->Contains(InValue);
		}
	}

	return false;
}

bool FSetImplementation::Set_IsValidIndexImplementation(const MonoObject* InMonoObject, const int32 InIndex)
{
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FSetHelper>(InMonoObject))
	{
		return SetHelper->IsValidIndex(InIndex);
	}

	return false;
}

void FSetImplementation::Set_GetEnumeratorImplementation(const MonoObject* InMonoObject, const int32 InIndex,
                                                         MonoObject** OutValue)
{
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FSetHelper>(InMonoObject))
	{
		const auto Value = SetHelper->GetEnumerator(InIndex);

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
