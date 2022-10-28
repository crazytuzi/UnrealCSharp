#include "Reflection/Function/FCSharpFunctionDescriptor.h"

FCSharpFunctionDescriptor::FCSharpFunctionDescriptor(UFunction* InFunction):
	Super(InFunction),
	OriginalFunctionFlags(EFunctionFlags::FUNC_None),
	OriginalNativeFuncPtr(nullptr)
{
}

FCSharpFunctionDescriptor::~FCSharpFunctionDescriptor()
{
	FCSharpFunctionDescriptor::Deinitialize();
}

void FCSharpFunctionDescriptor::Deinitialize()
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

			if (OriginalScript.Num() > 0)
			{
				InCallCSharpFunction->Script.Empty();

				InCallCSharpFunction->Script = OriginalScript;
			}
			else
			{
				InCallCSharpFunction->Script.Empty();
			}

			FunctionRemove = InOriginalFunction;
		}
		else
		{
			FunctionRemove = InCallCSharpFunction;
		}

		if (FunctionRemove != nullptr)
		{
			if (const auto Class = Cast<UClass>(FunctionRemove->GetOuter()))
			{
				Class->RemoveFunctionFromFunctionMap(FunctionRemove);
			}

			FunctionRemove->MarkPendingKill();
		}
	}

	OriginalFunction = nullptr;

	Function = nullptr;
}
