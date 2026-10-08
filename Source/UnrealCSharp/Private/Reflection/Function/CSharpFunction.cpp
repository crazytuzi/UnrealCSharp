#include "Reflection/Function/CSharpFunction.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Function/FCSharpFunctionDescriptor.h"

DEFINE_FUNCTION(UCSharpFunction::execCallCSharp)
{
	if (const auto FunctionDescriptor = FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor<
		FCSharpFunctionDescriptor>(FUnrealCSharpFunctionLibrary::GetHash(Stack.CurrentNativeFunction)))
	{
		FunctionDescriptor->CallCSharp(Context, Stack, RESULT_PARAM);
	}
}
