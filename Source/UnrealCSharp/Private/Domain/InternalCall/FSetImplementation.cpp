#include "Domain/InternalCall/FSetImplementation.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Container/FSetHelper.h"

void FSetImplementation::RegisterSetImplementation(MonoObject InMonoObject, MonoReflectionType* InReflectionType)
{
	FCSharpEnvironment::GetEnvironment()->Bind<FSetHelper>(&InMonoObject, InReflectionType);
}

void FSetImplementation::UnRegisterSetImplementation(MonoObject InMonoObject)
{
	FCSharpEnvironment::GetEnvironment()->RemoveContainerReference<FSetHelper>(&InMonoObject);
}

void FSetImplementation::Set_EmptyImplementation(MonoObject InMonoObject, const int32 InExpectedNumElements)
{
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FSetHelper>(&InMonoObject))
	{
		SetHelper->Empty(InExpectedNumElements);
	}
}

int32 FSetImplementation::Set_NumImplementation(MonoObject InMonoObject)
{
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FSetHelper>(&InMonoObject))
	{
		return SetHelper->Num();
	}

	return 0;
}

void FSetImplementation::Set_AddImplementation(MonoObject InMonoObject, void* InElement)
{
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FSetHelper>(&InMonoObject))
	{
		return SetHelper->Add(&InElement);
	}
}

int32 FSetImplementation::Set_RemoveImplementation(MonoObject InMonoObject, void* InKey)
{
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FSetHelper>(&InMonoObject))
	{
		return SetHelper->Remove(&InKey);
	}

	return 0;
}

bool FSetImplementation::Set_ContainsImplementation(MonoObject InMonoObject, const void* InKey)
{
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FSetHelper>(&InMonoObject))
	{
		return SetHelper->Contains(&InKey);
	}

	return false;
}
