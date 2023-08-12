#include "Domain/InternalCall/FSetImplementation.h"
#include "Registry/FCSharpBind.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Container/FSetHelper.h"
#include "Macro/NamespaceMacro.h"
#include "Bridge/FTypeBridge.h"
#include "Async/Async.h"

struct FRegisterSet
{
	FRegisterSet()
	{
		FClassBuilder(TEXT("Set"), NAMESPACE_LIBRARY)
			.Function("Register", FSetImplementation::Set_RegisterImplementation)
			.Function("UnRegister", FSetImplementation::Set_UnRegisterImplementation)
			.Function("Empty", FSetImplementation::Set_EmptyImplementation)
			.Function("Num", FSetImplementation::Set_NumImplementation)
			.Function("GetMaxIndex", FSetImplementation::Set_GetMaxIndexImplementation)
			.Function("Add", FSetImplementation::Set_AddImplementation)
			.Function("Remove", FSetImplementation::Set_RemoveImplementation)
			.Function("Contains", FSetImplementation::Set_ContainsImplementation)
			.Function("IsValidIndex", FSetImplementation::Set_IsValidIndexImplementation)
			.Function("GetEnumerator", FSetImplementation::Set_GetEnumeratorImplementation)
			.Register();
	}
};

static FRegisterSet RegisterSet;

void FSetImplementation::Set_RegisterImplementation(MonoObject* InMonoObject)
{
	FCSharpBind::Bind<FSetHelper>(InMonoObject, FTypeBridge::GetGenericArgument(InMonoObject));
}

void FSetImplementation::Set_UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	AsyncTask(ENamedThreads::GameThread, [InGarbageCollectionHandle]
	{
		(void)FCSharpEnvironment::GetEnvironment().RemoveContainerReference(InGarbageCollectionHandle);
	});
}

void FSetImplementation::Set_EmptyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                 const int32 InExpectedNumElements)
{
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(InGarbageCollectionHandle))
	{
		SetHelper->Empty(InExpectedNumElements);
	}
}

int32 FSetImplementation::Set_NumImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(InGarbageCollectionHandle))
	{
		return SetHelper->Num();
	}

	return 0;
}

int32 FSetImplementation::Set_GetMaxIndexImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(InGarbageCollectionHandle))
	{
		return SetHelper->GetMaxIndex();
	}

	return 0;
}

void FSetImplementation::Set_AddImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                               MonoObject* InValue)
{
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(InGarbageCollectionHandle))
	{
		if (SetHelper->GetElementPropertyDescriptor()->IsPrimitiveProperty())
		{
			SetHelper->Add(FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InValue));
		}
		else
		{
			SetHelper->Add(InValue);
		}
	}
}

int32 FSetImplementation::Set_RemoveImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                   MonoObject* InValue)
{
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(InGarbageCollectionHandle))
	{
		if (SetHelper->GetElementPropertyDescriptor()->IsPrimitiveProperty())
		{
			return SetHelper->Remove(FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InValue));
		}
		else
		{
			return SetHelper->Remove(InValue);
		}
	}

	return 0;
}

bool FSetImplementation::Set_ContainsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                    MonoObject* InValue)
{
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(InGarbageCollectionHandle))
	{
		if (SetHelper->GetElementPropertyDescriptor()->IsPrimitiveProperty())
		{
			return SetHelper->Contains(FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InValue));
		}
		else
		{
			return SetHelper->Contains(InValue);
		}
	}

	return false;
}

bool FSetImplementation::Set_IsValidIndexImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                        const int32 InIndex)
{
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(InGarbageCollectionHandle))
	{
		return SetHelper->IsValidIndex(InIndex);
	}

	return false;
}

void FSetImplementation::Set_GetEnumeratorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                         const int32 InIndex,
                                                         MonoObject** OutValue)
{
	if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(InGarbageCollectionHandle))
	{
		const auto Value = SetHelper->GetEnumerator(InIndex);

		if (SetHelper->GetElementPropertyDescriptor()->IsPrimitiveProperty())
		{
			*OutValue = FCSharpEnvironment::GetEnvironment().GetDomain()->Value_Box(
				FTypeBridge::GetMonoClass(SetHelper->GetElementPropertyDescriptor()->GetProperty()), Value);
		}
		else
		{
			SetHelper->GetElementPropertyDescriptor()->Get(Value, reinterpret_cast<void**>(OutValue));
		}
	}
}
