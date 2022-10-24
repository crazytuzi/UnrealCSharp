#include "Reflection/Function/FFunctionDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

FFunctionDescriptor::FFunctionDescriptor():
	OriginalFunctionFlags(EFunctionFlags::FUNC_None),
	OriginalNativeFuncPtr(nullptr)
{
	Initialize();
}

FFunctionDescriptor::~FFunctionDescriptor()
{
	Deinitialize();
}

void FFunctionDescriptor::Initialize()
{
}

void FFunctionDescriptor::Deinitialize()
{
	const auto InOriginalFunction = OriginalFunction.Get(true);

	const auto InCallCSharpFunction = CallCSharpFunction.Get(true);

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

	CallCSharpFunction = nullptr;
}

bool FFunctionDescriptor::CallCSharp(FFrame& Stack, void* const Z_Param__Result)
{
	if (const auto FoundMonoObject = FCSharpEnvironment::GetEnvironment()->GetObject(Stack.Object))
	{
		if (const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetClassDescriptor(
			Stack.Object->GetClass())->GetMonoClass())
		{
			if (const auto FoundMonoMethod = FCSharpEnvironment::GetEnvironment()->GetDomain()->
				Class_Get_Method_From_Name(FoundMonoClass,TCHAR_TO_UTF8(*Stack.Node->GetName()), 0))
			{
				FCSharpEnvironment::GetEnvironment()->GetDomain()->Runtime_Invoke(
					FoundMonoMethod, FoundMonoObject, nullptr, nullptr);
			}
		}
	}

	return true;
}
