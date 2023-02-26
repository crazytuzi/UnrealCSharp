#include "Domain/InternalCall/FSetImplementation.h"
#include "Binding/Class/FBindingClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Container/FSetHelper.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterSet
{
	FRegisterSet()
	{
		FBindingClassBuilder(TEXT("Set"), NAMESPACE_CONTAINER)
			.Function("Register", static_cast<void*>(FSetImplementation::Set_RegisterImplementation))
			.Function("UnRegister", static_cast<void*>(FSetImplementation::Set_UnRegisterImplementation))
			.Function("Empty", static_cast<void*>(FSetImplementation::Set_EmptyImplementation))
			.Function("Num", static_cast<void*>(FSetImplementation::Set_NumImplementation))
			.Function("Add", static_cast<void*>(FSetImplementation::Set_AddImplementation))
			.Function("Remove", static_cast<void*>(FSetImplementation::Set_RemoveImplementation))
			.Function("Contains", static_cast<void*>(FSetImplementation::Set_ContainsImplementation))
			.Register();
	}
};

static FRegisterSet RegisterSet;

void FSetImplementation::Set_RegisterImplementation(MonoObject* InMonoObject, MonoReflectionType* InReflectionType)
{
	FCSharpEnvironment::GetEnvironment()->Bind<FSetHelper>(InMonoObject, InReflectionType);
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
