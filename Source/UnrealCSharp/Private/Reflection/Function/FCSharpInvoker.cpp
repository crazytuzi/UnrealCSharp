#include "Reflection/Function/FCSharpInvoker.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Function/FFunctionDescriptor.h"

static FNativeFunctionRegistrar CallCSharpRegistrar(UObject::StaticClass(), "execCallCSharp",
                                                    (FNativeFuncPtr)&FCSharpInvoker::execCallCSharp);

extern uint8 GRegisterNative(int32 NativeBytecodeIndex, const FNativeFuncPtr& Func);

uint8 CallCSharpBytecode = GRegisterNative(EX_CallCSharp, (FNativeFuncPtr)&FCSharpInvoker::execCallCSharp);

DEFINE_FUNCTION(FCSharpInvoker::execCallCSharp)
{
	auto Function = Stack.Node;

	FFunctionDescriptor* FunctionDescriptor = nullptr;

	if (Stack.CurrentNativeFunction != nullptr)
	{
		if (Function != Stack.CurrentNativeFunction)
		{
			Function = Stack.CurrentNativeFunction;

			FunctionDescriptor = FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(
				Cast<UClass>(Function->GetOuter()), Function->GetFName());
		}
		else
		{
			if (Function->GetNativeFunc() == (FNativeFuncPtr)&FCSharpInvoker::execCallCSharp)
			{
				check(*Stack.Code == EX_CallCSharp);

				Stack.SkipCode(1);
			}
		}
	}

	if (FunctionDescriptor == nullptr)
	{
		FunctionDescriptor = FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(
			Cast<UClass>(Function->GetOuter()), Function->GetFName());
	}

	if (FunctionDescriptor != nullptr)
	{
		FunctionDescriptor->CallCSharp(Stack, RESULT_PARAM);
	}
}
