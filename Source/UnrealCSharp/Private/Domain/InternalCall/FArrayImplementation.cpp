#include "Domain/InternalCall/FArrayImplementation.h"
#include "Binding/Class/FBindingClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"
#include "Reflection/Container/FArrayHelper.h"
#include "Macro/NamespaceMacro.h"
#include "Async/Async.h"

struct FRegisterArray
{
	FRegisterArray()
	{
		FBindingClassBuilder(TEXT("Array"), NAMESPACE_LIBRARY)
			.Function("Register", static_cast<void*>(FArrayImplementation::Array_RegisterImplementation))
			.Function("UnRegister", static_cast<void*>(FArrayImplementation::Array_UnRegisterImplementation))
			.Function("GetTypeSize", static_cast<void*>(FArrayImplementation::Array_GetTypeSizeImplementation))
			.Function("GetSlack", static_cast<void*>(FArrayImplementation::Array_GetSlackImplementation))
			.Function("IsValidIndex", static_cast<void*>(FArrayImplementation::Array_IsValidIndexImplementation))
			.Function("Num", static_cast<void*>(FArrayImplementation::Array_NumImplementation))
			.Function("Max", static_cast<void*>(FArrayImplementation::Array_MaxImplementation))
			.Function("Get", static_cast<void*>(FArrayImplementation::Array_GetImplementation))
			.Function("Set", static_cast<void*>(FArrayImplementation::Array_SetImplementation))
			.Function("Find", static_cast<void*>(FArrayImplementation::Array_FindImplementation))
			.Function("FindLast", static_cast<void*>(FArrayImplementation::Array_FindLastImplementation))
			.Function("Contains", static_cast<void*>(FArrayImplementation::Array_ContainsImplementation))
			.Function("AddUninitialized",
			          static_cast<void*>(FArrayImplementation::Array_AddUninitializedImplementation))
			.Function("InsertZeroed", static_cast<void*>(FArrayImplementation::Array_InsertZeroedImplementation))
			.Function("InsertDefaulted", static_cast<void*>(FArrayImplementation::Array_InsertDefaultedImplementation))
			.Function("RemoveAt", static_cast<void*>(FArrayImplementation::Array_RemoveAtImplementation))
			.Function("Reset", static_cast<void*>(FArrayImplementation::Array_ResetImplementation))
			.Function("Empty", static_cast<void*>(FArrayImplementation::Array_EmptyImplementation))
			.Function("SetNum", static_cast<void*>(FArrayImplementation::Array_SetNumImplementation))
			.Function("Add", static_cast<void*>(FArrayImplementation::Array_AddImplementation))
			.Function("AddZeroed", static_cast<void*>(FArrayImplementation::Array_AddZeroedImplementation))
			.Function("AddUnique", static_cast<void*>(FArrayImplementation::Array_AddUniqueImplementation))
			.Function("RemoveSingle", static_cast<void*>(FArrayImplementation::Array_RemoveSingleImplementation))
			.Function("Remove", static_cast<void*>(FArrayImplementation::Array_RemoveImplementation))
			.Function("SwapMemory", static_cast<void*>(FArrayImplementation::Array_SwapMemoryImplementation))
			.Function("Swap", static_cast<void*>(FArrayImplementation::Array_SwapImplementation))
			.Register();
	}
};

static FRegisterArray RegisterArray;

void FArrayImplementation::Array_RegisterImplementation(MonoObject* InMonoObject)
{
	FCSharpEnvironment::GetEnvironment().Bind<FArrayHelper>(InMonoObject,
	                                                        FTypeBridge::GetGenericArgument(InMonoObject));
}

void FArrayImplementation::Array_UnRegisterImplementation(const MonoObject* InMonoObject)
{
	AsyncTask(ENamedThreads::GameThread, [InMonoObject]
	{
		(void)FCSharpEnvironment::GetEnvironment().RemoveContainerReference(InMonoObject);
	});
}

int32 FArrayImplementation::Array_GetTypeSizeImplementation(const MonoObject* InMonoObject)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->GetTypeSize();
	}

	return 0;
}

int32 FArrayImplementation::Array_GetSlackImplementation(const MonoObject* InMonoObject)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->GetSlack();
	}

	return 0;
}

bool FArrayImplementation::Array_IsValidIndexImplementation(const MonoObject* InMonoObject, const int32 InIndex)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->IsValidIndex(InIndex);
	}

	return false;
}

int32 FArrayImplementation::Array_NumImplementation(const MonoObject* InMonoObject)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->Num();
	}

	return 0;
}

int32 FArrayImplementation::Array_MaxImplementation(const MonoObject* InMonoObject)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->Max();
	}

	return 0;
}

void FArrayImplementation::Array_GetImplementation(const MonoObject* InMonoObject, const int32 InIndex,
                                                   MonoObject** OutValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InMonoObject))
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

void FArrayImplementation::Array_SetImplementation(const MonoObject* InMonoObject, const int32 InIndex,
                                                   MonoObject* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InMonoObject))
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

int32 FArrayImplementation::Array_FindImplementation(const MonoObject* InMonoObject, MonoObject* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InMonoObject))
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

int32 FArrayImplementation::Array_FindLastImplementation(const MonoObject* InMonoObject, MonoObject* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InMonoObject))
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

bool FArrayImplementation::Array_ContainsImplementation(const MonoObject* InMonoObject, MonoObject* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InMonoObject))
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

int32 FArrayImplementation::Array_AddUninitializedImplementation(const MonoObject* InMonoObject, const int32 InCount)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->AddUninitialized(InCount);
	}

	return 0;
}

void FArrayImplementation::Array_InsertZeroedImplementation(const MonoObject* InMonoObject, const int32 InIndex,
                                                            const int32 InCount)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InMonoObject))
	{
		ArrayHelper->InsertZeroed(InIndex, InCount);
	}
}

void FArrayImplementation::Array_InsertDefaultedImplementation(const MonoObject* InMonoObject, const int32 InIndex,
                                                               const int32 InCount)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InMonoObject))
	{
		ArrayHelper->InsertDefaulted(InIndex, InCount);
	}
}

void FArrayImplementation::Array_RemoveAtImplementation(const MonoObject* InMonoObject, const int32 InIndex,
                                                        const int32 InCount, const bool bAllowShrinking)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InMonoObject))
	{
		ArrayHelper->RemoveAt(InIndex, InCount, bAllowShrinking);
	}
}

void FArrayImplementation::Array_ResetImplementation(const MonoObject* InMonoObject, const int32 InNewSize)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->Reset(InNewSize);
	}
}

void FArrayImplementation::Array_EmptyImplementation(const MonoObject* InMonoObject, const int32 InSlack)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->Empty(InSlack);
	}
}

void FArrayImplementation::Array_SetNumImplementation(const MonoObject* InMonoObject, const int32 InNewNum,
                                                      const bool bAllowShrinking)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->SetNum(InNewNum, bAllowShrinking);
	}
}

int32 FArrayImplementation::Array_AddImplementation(const MonoObject* InMonoObject, MonoObject* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InMonoObject))
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

int32 FArrayImplementation::Array_AddZeroedImplementation(const MonoObject* InMonoObject, const int32 InCount)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->AddZeroed(InCount);
	}

	return 0;
}

int32 FArrayImplementation::Array_AddUniqueImplementation(const MonoObject* InMonoObject, MonoObject* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InMonoObject))
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

int32 FArrayImplementation::Array_RemoveSingleImplementation(const MonoObject* InMonoObject, MonoObject* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InMonoObject))
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

int32 FArrayImplementation::Array_RemoveImplementation(const MonoObject* InMonoObject, MonoObject* InValue)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InMonoObject))
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

void FArrayImplementation::Array_SwapMemoryImplementation(const MonoObject* InMonoObject,
                                                          const int32 InFirstIndexToSwap,
                                                          const int32 InSecondIndexToSwap)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->SwapMemory(InFirstIndexToSwap, InSecondIndexToSwap);
	}
}

void FArrayImplementation::Array_SwapImplementation(const MonoObject* InMonoObject, const int32 InFirstIndexToSwap,
                                                    const int32 InSecondIndexToSwap)
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(InMonoObject))
	{
		return ArrayHelper->Swap(InFirstIndexToSwap, InSecondIndexToSwap);
	}
}
