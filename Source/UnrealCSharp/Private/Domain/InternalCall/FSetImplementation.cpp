#include "Domain/InternalCall/FSetImplementation.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Container/FSetHelper.h"

void FSetImplementation::Set_RegisterImplementation(MonoObject* InMonoObject, MonoReflectionType* InReflectionType)
{
	FCSharpEnvironment::GetEnvironment()->Bind<FSetHelper>(InMonoObject, InReflectionType);
}

void FSetImplementation::Set_UnRegisterImplementation(const MonoObject* InMonoObject)
{
	FCSharpEnvironment::GetEnvironment()->RemoveContainerReference<FSetHelper>(InMonoObject);
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
