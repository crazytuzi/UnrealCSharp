#include "Domain/InternalCall/FArrayImplementation.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"
#include "Reflection/Container/FArrayHelper.h"

void FArrayImplementation::RegisterArrayImplementation(MonoObject InMonoObject, MonoReflectionType* InReflectionType)
{
	FCSharpEnvironment::GetEnvironment()->Bind(&InMonoObject, InReflectionType);
}

void FArrayImplementation::UnRegisterArrayImplementation(MonoObject InMonoObject)
{
	FCSharpEnvironment::GetEnvironment()->RemoveContainerReference<FArrayHelper>(&InMonoObject);
}

int32 FArrayImplementation::Array_GetTypeSizeImplementation(MonoObject InMonoObject)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(&InMonoObject))
	{
		return ArrayHelper->GetTypeSize();
	}

	return 0;
}

int32 FArrayImplementation::Array_GetSlackImplementation(MonoObject InMonoObject)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(&InMonoObject))
	{
		return ArrayHelper->GetSlack();
	}

	return 0;
}

bool FArrayImplementation::Array_IsValidIndexImplementation(MonoObject InMonoObject, const int32 InIndex)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(&InMonoObject))
	{
		return ArrayHelper->IsValidIndex(InIndex);
	}

	return false;
}

int32 FArrayImplementation::Array_NumImplementation(MonoObject InMonoObject)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(&InMonoObject))
	{
		return ArrayHelper->Num();
	}

	return 0;
}

int32 FArrayImplementation::Array_MaxImplementation(MonoObject InMonoObject)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(&InMonoObject))
	{
		return ArrayHelper->Max();
	}

	return 0;
}

void FArrayImplementation::Array_GetImplementation(MonoObject InMonoObject, const int32 InIndex, MonoObject** OutValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(&InMonoObject))
	{
		const auto Value = ArrayHelper->Get(InIndex);

		if (ArrayHelper->IsPrimitiveProperty())
		{
			*OutValue = FCSharpEnvironment::GetEnvironment()->GetDomain()->Value_Box(
				FTypeBridge::GetMonoClass(ArrayHelper->GetInnerProperty()), Value);
		}
		else
		{
			*OutValue = static_cast<MonoObject*>(Value);
		}
	}
}

void FArrayImplementation::Array_SetImplementation(MonoObject InMonoObject, const int32 InIndex, void* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(&InMonoObject))
	{
		ArrayHelper->Set(InIndex, &InValue);
	}
}

int32 FArrayImplementation::Array_FindImplementation(MonoObject InMonoObject, void* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(&InMonoObject))
	{
		return ArrayHelper->Find(&InValue);
	}

	return 0;
}

int32 FArrayImplementation::Array_FindLastImplementation(MonoObject InMonoObject, void* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(&InMonoObject))
	{
		return ArrayHelper->FindLast(&InValue);
	}

	return 0;
}

bool FArrayImplementation::Array_ContainsImplementation(MonoObject InMonoObject, void* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(&InMonoObject))
	{
		return ArrayHelper->Contains(&InValue);
	}

	return false;
}

int32 FArrayImplementation::Array_AddUninitializedImplementation(MonoObject InMonoObject, const int32 InCount)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(&InMonoObject))
	{
		return ArrayHelper->AddUninitialized(InCount);
	}

	return 0;
}

void FArrayImplementation::Array_InsertZeroedImplementation(MonoObject InMonoObject, const int32 InIndex,
                                                            const int32 InCount)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(&InMonoObject))
	{
		ArrayHelper->InsertZeroed(InIndex, InCount);
	}
}

void FArrayImplementation::Array_InsertDefaultedImplementation(MonoObject InMonoObject, int32 InIndex, int32 InCount)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(&InMonoObject))
	{
		ArrayHelper->InsertDefaulted(InIndex, InCount);
	}
}

void FArrayImplementation::Array_RemoveAtImplementation(MonoObject InMonoObject, const int32 InIndex,
                                                        const int32 InCount, const bool bAllowShrinking)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(&InMonoObject))
	{
		ArrayHelper->RemoveAt(InIndex, InCount, bAllowShrinking);
	}
}

void FArrayImplementation::Array_ResetImplementation(MonoObject InMonoObject, const int32 InNewSize)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(&InMonoObject))
	{
		return ArrayHelper->Reset(InNewSize);
	}
}

void FArrayImplementation::Array_EmptyImplementation(MonoObject InMonoObject, const int32 InSlack)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(&InMonoObject))
	{
		return ArrayHelper->Empty(InSlack);
	}
}

void FArrayImplementation::Array_SetNumImplementation(MonoObject InMonoObject, const int32 InNewNum,
                                                      const bool bAllowShrinking)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(&InMonoObject))
	{
		return ArrayHelper->SetNum(InNewNum, bAllowShrinking);
	}
}

int32 FArrayImplementation::Array_AddImplementation(MonoObject InMonoObject, void* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(&InMonoObject))
	{
		return ArrayHelper->Add(&InValue);
	}

	return 0;
}

int32 FArrayImplementation::Array_AddZeroedImplementation(MonoObject InMonoObject, const int32 InCount)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(&InMonoObject))
	{
		return ArrayHelper->AddZeroed(InCount);
	}

	return 0;
}

int32 FArrayImplementation::Array_AddUniqueImplementation(MonoObject InMonoObject, void* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(&InMonoObject))
	{
		return ArrayHelper->AddUnique(&InValue);
	}

	return 0;
}

int32 FArrayImplementation::Array_RemoveSingleImplementation(MonoObject InMonoObject, const void* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(&InMonoObject))
	{
		return ArrayHelper->RemoveSingle(&InValue);
	}

	return 0;
}

int32 FArrayImplementation::Array_RemoveImplementation(MonoObject InMonoObject, const void* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(&InMonoObject))
	{
		return ArrayHelper->Remove(&InValue);
	}

	return 0;
}

void FArrayImplementation::Array_SwapMemoryImplementation(MonoObject InMonoObject, const int32 InFirstIndexToSwap,
                                                          const int32 InSecondIndexToSwap)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(&InMonoObject))
	{
		return ArrayHelper->SwapMemory(InFirstIndexToSwap, InSecondIndexToSwap);
	}
}

void FArrayImplementation::Array_SwapImplementation(MonoObject InMonoObject, const int32 InFirstIndexToSwap,
                                                    const int32 InSecondIndexToSwap)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(&InMonoObject))
	{
		return ArrayHelper->Swap(InFirstIndexToSwap, InSecondIndexToSwap);
	}
}
