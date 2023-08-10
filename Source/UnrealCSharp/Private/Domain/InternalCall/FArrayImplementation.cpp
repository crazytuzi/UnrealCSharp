#include "Domain/InternalCall/FArrayImplementation.h"
#include "Registry/FCSharpBind.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"
#include "Reflection/Container/FArrayHelper.h"
#include "Macro/NamespaceMacro.h"
#include "Async/Async.h"

struct FRegisterArray
{
	FRegisterArray()
	{
		FClassBuilder(TEXT("Array"), NAMESPACE_LIBRARY)
			.Function("Register", FArrayImplementation::Array_RegisterImplementation)
			.Function("UnRegister", FArrayImplementation::Array_UnRegisterImplementation)
			.Function("GetTypeSize", FArrayImplementation::Array_GetTypeSizeImplementation)
			.Function("GetSlack", FArrayImplementation::Array_GetSlackImplementation)
			.Function("IsValidIndex", FArrayImplementation::Array_IsValidIndexImplementation)
			.Function("Num", FArrayImplementation::Array_NumImplementation)
			.Function("Max", FArrayImplementation::Array_MaxImplementation)
			.Function("Get", FArrayImplementation::Array_GetImplementation)
			.Function("Set", FArrayImplementation::Array_SetImplementation)
			.Function("Find", FArrayImplementation::Array_FindImplementation)
			.Function("FindLast", FArrayImplementation::Array_FindLastImplementation)
			.Function("Contains", FArrayImplementation::Array_ContainsImplementation)
			.Function("AddUninitialized", FArrayImplementation::Array_AddUninitializedImplementation)
			.Function("InsertZeroed", FArrayImplementation::Array_InsertZeroedImplementation)
			.Function("InsertDefaulted", FArrayImplementation::Array_InsertDefaultedImplementation)
			.Function("RemoveAt", FArrayImplementation::Array_RemoveAtImplementation)
			.Function("Reset", FArrayImplementation::Array_ResetImplementation)
			.Function("Empty", FArrayImplementation::Array_EmptyImplementation)
			.Function("SetNum", FArrayImplementation::Array_SetNumImplementation)
			.Function("Add", FArrayImplementation::Array_AddImplementation)
			.Function("AddZeroed", FArrayImplementation::Array_AddZeroedImplementation)
			.Function("AddUnique", FArrayImplementation::Array_AddUniqueImplementation)
			.Function("RemoveSingle", FArrayImplementation::Array_RemoveSingleImplementation)
			.Function("Remove", FArrayImplementation::Array_RemoveImplementation)
			.Function("SwapMemory", FArrayImplementation::Array_SwapMemoryImplementation)
			.Function("Swap", FArrayImplementation::Array_SwapImplementation)
			.Register();
	}
};

static FRegisterArray RegisterArray;

void FArrayImplementation::Array_RegisterImplementation(MonoObject* InMonoObject)
{
	FCSharpBind::Bind<FArrayHelper>(InMonoObject, FTypeBridge::GetGenericArgument(InMonoObject));
}

void FArrayImplementation::Array_UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	AsyncTask(ENamedThreads::GameThread, [InGarbageCollectionHandle]
	{
		(void)FCSharpEnvironment::GetEnvironment().RemoveContainerReference(InGarbageCollectionHandle);
	});
}

int32 FArrayImplementation::Array_GetTypeSizeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
		InGarbageCollectionHandle))
	{
		return ArrayHelper->GetTypeSize();
	}

	return 0;
}

int32 FArrayImplementation::Array_GetSlackImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
		InGarbageCollectionHandle))
	{
		return ArrayHelper->GetSlack();
	}

	return 0;
}

bool FArrayImplementation::Array_IsValidIndexImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                            const int32 InIndex)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
		InGarbageCollectionHandle))
	{
		return ArrayHelper->IsValidIndex(InIndex);
	}

	return false;
}

int32 FArrayImplementation::Array_NumImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
		InGarbageCollectionHandle))
	{
		return ArrayHelper->Num();
	}

	return 0;
}

int32 FArrayImplementation::Array_MaxImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
		InGarbageCollectionHandle))
	{
		return ArrayHelper->Max();
	}

	return 0;
}

void FArrayImplementation::Array_GetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                   const int32 InIndex, MonoObject** OutValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
		InGarbageCollectionHandle))
	{
		const auto Value = ArrayHelper->Get(InIndex);

		if (ArrayHelper->GetInnerPropertyDescriptor()->IsPrimitiveProperty())
		{
			*OutValue = FCSharpEnvironment::GetEnvironment().GetDomain()->Value_Box(
				FTypeBridge::GetMonoClass(ArrayHelper->GetInnerPropertyDescriptor()->GetProperty()), Value);
		}
		else
		{
			ArrayHelper->GetInnerPropertyDescriptor()->Get(Value, reinterpret_cast<void**>(OutValue));
		}
	}
}

void FArrayImplementation::Array_SetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                   const int32 InIndex, MonoObject* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
		InGarbageCollectionHandle))
	{
		if (ArrayHelper->GetInnerPropertyDescriptor()->IsPrimitiveProperty())
		{
			ArrayHelper->Set(InIndex, FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InValue));
		}
		else
		{
			ArrayHelper->Set(InIndex, InValue);
		}
	}
}

int32 FArrayImplementation::Array_FindImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                     MonoObject* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
		InGarbageCollectionHandle))
	{
		if (ArrayHelper->GetInnerPropertyDescriptor()->IsPrimitiveProperty())
		{
			return ArrayHelper->Find(FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InValue));
		}
		else
		{
			return ArrayHelper->Find(InValue);
		}
	}

	return 0;
}

int32 FArrayImplementation::Array_FindLastImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                         MonoObject* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
		InGarbageCollectionHandle))
	{
		if (ArrayHelper->GetInnerPropertyDescriptor()->IsPrimitiveProperty())
		{
			return ArrayHelper->FindLast(FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InValue));
		}
		else
		{
			return ArrayHelper->FindLast(InValue);
		}
	}

	return 0;
}

bool FArrayImplementation::Array_ContainsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                        MonoObject* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
		InGarbageCollectionHandle))
	{
		if (ArrayHelper->GetInnerPropertyDescriptor()->IsPrimitiveProperty())
		{
			return ArrayHelper->Contains(FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InValue));
		}
		else
		{
			return ArrayHelper->Contains(InValue);
		}
	}

	return false;
}

int32 FArrayImplementation::Array_AddUninitializedImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const int32 InCount)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
		InGarbageCollectionHandle))
	{
		return ArrayHelper->AddUninitialized(InCount);
	}

	return 0;
}

void FArrayImplementation::Array_InsertZeroedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                            const int32 InIndex, const int32 InCount)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
		InGarbageCollectionHandle))
	{
		ArrayHelper->InsertZeroed(InIndex, InCount);
	}
}

void FArrayImplementation::Array_InsertDefaultedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                               const int32 InIndex, const int32 InCount)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
		InGarbageCollectionHandle))
	{
		ArrayHelper->InsertDefaulted(InIndex, InCount);
	}
}

void FArrayImplementation::Array_RemoveAtImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                        const int32 InIndex, const int32 InCount,
                                                        const bool bAllowShrinking)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
		InGarbageCollectionHandle))
	{
		ArrayHelper->RemoveAt(InIndex, InCount, bAllowShrinking);
	}
}

void FArrayImplementation::Array_ResetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                     const int32 InNewSize)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
		InGarbageCollectionHandle))
	{
		return ArrayHelper->Reset(InNewSize);
	}
}

void FArrayImplementation::Array_EmptyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                     const int32 InSlack)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
		InGarbageCollectionHandle))
	{
		return ArrayHelper->Empty(InSlack);
	}
}

void FArrayImplementation::Array_SetNumImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                      const int32 InNewNum, const bool bAllowShrinking)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
		InGarbageCollectionHandle))
	{
		return ArrayHelper->SetNum(InNewNum, bAllowShrinking);
	}
}

int32 FArrayImplementation::Array_AddImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                    MonoObject* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
		InGarbageCollectionHandle))
	{
		if (ArrayHelper->GetInnerPropertyDescriptor()->IsPrimitiveProperty())
		{
			return ArrayHelper->Add(FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InValue));
		}
		else
		{
			return ArrayHelper->Add(InValue);
		}
	}

	return 0;
}

int32 FArrayImplementation::Array_AddZeroedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                          const int32 InCount)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
		InGarbageCollectionHandle))
	{
		return ArrayHelper->AddZeroed(InCount);
	}

	return 0;
}

int32 FArrayImplementation::Array_AddUniqueImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                          MonoObject* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
		InGarbageCollectionHandle))
	{
		if (ArrayHelper->GetInnerPropertyDescriptor()->IsPrimitiveProperty())
		{
			return ArrayHelper->AddUnique(FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InValue));
		}
		else
		{
			return ArrayHelper->AddUnique(InValue);
		}
	}

	return 0;
}

int32 FArrayImplementation::Array_RemoveSingleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                             MonoObject* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
		InGarbageCollectionHandle))
	{
		if (ArrayHelper->GetInnerPropertyDescriptor()->IsPrimitiveProperty())
		{
			return ArrayHelper->RemoveSingle(FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InValue));
		}
		else
		{
			return ArrayHelper->RemoveSingle(InValue);
		}
	}

	return 0;
}

int32 FArrayImplementation::Array_RemoveImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                       MonoObject* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
		InGarbageCollectionHandle))
	{
		if (ArrayHelper->GetInnerPropertyDescriptor()->IsPrimitiveProperty())
		{
			return ArrayHelper->Remove(FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InValue));
		}
		else
		{
			return ArrayHelper->Remove(InValue);
		}
	}

	return 0;
}

void FArrayImplementation::Array_SwapMemoryImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                          const int32 InFirstIndexToSwap,
                                                          const int32 InSecondIndexToSwap)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
		InGarbageCollectionHandle))
	{
		return ArrayHelper->SwapMemory(InFirstIndexToSwap, InSecondIndexToSwap);
	}
}

void FArrayImplementation::Array_SwapImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                    const int32 InFirstIndexToSwap, const int32 InSecondIndexToSwap)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
		InGarbageCollectionHandle))
	{
		return ArrayHelper->Swap(InFirstIndexToSwap, InSecondIndexToSwap);
	}
}
