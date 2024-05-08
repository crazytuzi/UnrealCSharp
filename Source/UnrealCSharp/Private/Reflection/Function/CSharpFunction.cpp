#include "Reflection/Function/CSharpFunction.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Function/FCSharpFunctionDescriptor.h"

DEFINE_FUNCTION(UCSharpFunction::execCallCSharp)
{
	if (const auto FunctionDescriptor = static_cast<FCSharpFunctionDescriptor*>(
		FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(
			Cast<UClass>(Stack.CurrentNativeFunction->GetOuter()), Stack.CurrentNativeFunction->GetName())))
	{
		FunctionDescriptor->CallCSharp(Stack, RESULT_PARAM);
	}
}
