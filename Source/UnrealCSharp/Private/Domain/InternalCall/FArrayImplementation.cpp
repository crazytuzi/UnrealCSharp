#include "Domain/InternalCall/FArrayImplementation.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"
#include "Reflection/Container/FArrayHelper.h"

void FArrayImplementation::Array_RegisterImplementation(MonoObject* InMonoObject, MonoReflectionType* InReflectionType)
{
	FCSharpEnvironment::GetEnvironment()->Bind<FArrayHelper>(InMonoObject, InReflectionType);
}

void FArrayImplementation::Array_UnRegisterImplementation(const MonoObject* InMonoObject)
{
	FCSharpEnvironment::GetEnvironment()->RemoveContainerReference<FArrayHelper>(InMonoObject);
}

int32 FArrayImplementation::Array_GetTypeSizeImplementation(const MonoObject* InMonoObject)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->GetTypeSize();
	}

	return 0;
}

int32 FArrayImplementation::Array_GetSlackImplementation(const MonoObject* InMonoObject)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->GetSlack();
	}

	return 0;
}

bool FArrayImplementation::Array_IsValidIndexImplementation(const MonoObject* InMonoObject, const int32 InIndex)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->IsValidIndex(InIndex);
	}

	return false;
}

int32 FArrayImplementation::Array_NumImplementation(const MonoObject* InMonoObject)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->Num();
	}

	return 0;
}

int32 FArrayImplementation::Array_MaxImplementation(const MonoObject* InMonoObject)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->Max();
	}

	return 0;
}

void FArrayImplementation::Array_GetImplementation(const MonoObject* InMonoObject, const int32 InIndex,
                                                   MonoObject** OutValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(InMonoObject))
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

void FArrayImplementation::Array_SetImplementation(const MonoObject* InMonoObject, const int32 InIndex, void* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(InMonoObject))
	{
		ArrayHelper->Set(InIndex, &InValue);
	}
}

int32 FArrayImplementation::Array_FindImplementation(const MonoObject* InMonoObject, void* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->Find(&InValue);
	}

	return 0;
}

int32 FArrayImplementation::Array_FindLastImplementation(const MonoObject* InMonoObject, void* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->FindLast(&InValue);
	}

	return 0;
}

bool FArrayImplementation::Array_ContainsImplementation(const MonoObject* InMonoObject, void* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->Contains(&InValue);
	}

	return false;
}

int32 FArrayImplementation::Array_AddUninitializedImplementation(const MonoObject* InMonoObject, const int32 InCount)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->AddUninitialized(InCount);
	}

	return 0;
}

void FArrayImplementation::Array_InsertZeroedImplementation(const MonoObject* InMonoObject, const int32 InIndex,
                                                            const int32 InCount)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(InMonoObject))
	{
		ArrayHelper->InsertZeroed(InIndex, InCount);
	}
}

void FArrayImplementation::Array_InsertDefaultedImplementation(const MonoObject* InMonoObject, const int32 InIndex,
                                                               const int32 InCount)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(InMonoObject))
	{
		ArrayHelper->InsertDefaulted(InIndex, InCount);
	}
}

void FArrayImplementation::Array_RemoveAtImplementation(const MonoObject* InMonoObject, const int32 InIndex,
                                                        const int32 InCount, const bool bAllowShrinking)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(InMonoObject))
	{
		ArrayHelper->RemoveAt(InIndex, InCount, bAllowShrinking);
	}
}

void FArrayImplementation::Array_ResetImplementation(const MonoObject* InMonoObject, const int32 InNewSize)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->Reset(InNewSize);
	}
}

void FArrayImplementation::Array_EmptyImplementation(const MonoObject* InMonoObject, const int32 InSlack)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->Empty(InSlack);
	}
}

void FArrayImplementation::Array_SetNumImplementation(const MonoObject* InMonoObject, const int32 InNewNum,
                                                      const bool bAllowShrinking)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->SetNum(InNewNum, bAllowShrinking);
	}
}

int32 FArrayImplementation::Array_AddImplementation(const MonoObject* InMonoObject, void* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->Add(&InValue);
	}

	return 0;
}

int32 FArrayImplementation::Array_AddZeroedImplementation(const MonoObject* InMonoObject, const int32 InCount)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->AddZeroed(InCount);
	}

	return 0;
}

int32 FArrayImplementation::Array_AddUniqueImplementation(const MonoObject* InMonoObject, void* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->AddUnique(&InValue);
	}

	return 0;
}

int32 FArrayImplementation::Array_RemoveSingleImplementation(const MonoObject* InMonoObject, const void* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->RemoveSingle(&InValue);
	}

	return 0;
}

int32 FArrayImplementation::Array_RemoveImplementation(const MonoObject* InMonoObject, const void* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->Remove(&InValue);
	}

	return 0;
}

void FArrayImplementation::Array_SwapMemoryImplementation(const MonoObject* InMonoObject,
                                                          const int32 InFirstIndexToSwap,
                                                          const int32 InSecondIndexToSwap)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->SwapMemory(InFirstIndexToSwap, InSecondIndexToSwap);
	}
}

void FArrayImplementation::Array_SwapImplementation(const MonoObject* InMonoObject, const int32 InFirstIndexToSwap,
                                                    const int32 InSecondIndexToSwap)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->Swap(InFirstIndexToSwap, InSecondIndexToSwap);
	}
}
