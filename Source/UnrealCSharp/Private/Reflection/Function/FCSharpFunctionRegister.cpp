#include "Reflection/Function/FCSharpFunctionRegister.h"

FCSharpFunctionRegister::FCSharpFunctionRegister(UFunction* InFunction,
                                                 UFunction* InOriginalFunction,
                                                 const EFunctionFlags InOriginalFunctionFlags,
                                                 const FNativeFuncPtr InOriginalNativeFuncPtr) :
	Function(InFunction),
	OriginalFunction(InOriginalFunction),
	OriginalFunctionFlags(InOriginalFunctionFlags),
	OriginalNativeFuncPtr(InOriginalNativeFuncPtr)
{
}

FCSharpFunctionRegister::FCSharpFunctionRegister(FCSharpFunctionRegister&& InOther) :
	Function(InOther.Function),
	OriginalFunction(InOther.OriginalFunction),
	OriginalFunctionFlags(InOther.OriginalFunctionFlags),
	OriginalNativeFuncPtr(InOther.OriginalNativeFuncPtr)
{
	InOther.Function.Reset();

	InOther.OriginalFunction.Reset();

	InOther.OriginalFunctionFlags = FUNC_None;

	InOther.OriginalNativeFuncPtr = nullptr;
}

FCSharpFunctionRegister::~FCSharpFunctionRegister()
{
	const auto InOriginalFunction = OriginalFunction.Get(true);

	const auto InCallCSharpFunction = Function.Get(true);

	if (InOriginalFunction != nullptr && InCallCSharpFunction != nullptr)
	{
		UFunction* FunctionRemove;

		if (InOriginalFunction->GetOuter() == InCallCSharpFunction->GetOuter())
		{
			InCallCSharpFunction->FunctionFlags = OriginalFunctionFlags;

			InCallCSharpFunction->SetNativeFunc(OriginalNativeFuncPtr);

			FunctionRemove = InOriginalFunction;
		}
		else
		{
			FunctionRemove = InCallCSharpFunction;
		}

		if (const auto Class = Cast<UClass>(FunctionRemove->GetOuter()))
		{
			Class->RemoveFunctionFromFunctionMap(FunctionRemove);
		}

		FunctionRemove->Rename(
			*MakeUniqueObjectName(
				GetTransientPackage(),
				FunctionRemove->GetClass(),
				*FString::Printf(TEXT(
					"TRASH_%s"
				),
				                 *FunctionRemove->GetName()
				)).ToString(),
			GetTransientPackage(),
			REN_DontCreateRedirectors | REN_NonTransactional | REN_DoNotDirty);

		if (FunctionRemove->IsRooted())
		{
			FunctionRemove->RemoveFromRoot();
		}
		else
		{
			FunctionRemove->MarkAsGarbage();
		}
	}

	OriginalFunction = nullptr;
}

const TWeakObjectPtr<UFunction>& FCSharpFunctionRegister::GetOriginalFunction() const
{
	return OriginalFunction;
}

EFunctionFlags FCSharpFunctionRegister::GetOriginalFunctionFlags() const
{
	return OriginalFunctionFlags;
}
