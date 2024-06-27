#include "Reflection/Function/CSharpFunction.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Function/FCSharpFunctionDescriptor.h"

DEFINE_FUNCTION(UCSharpFunction::execCallCSharp)
{
	if (const auto FunctionDescriptor = static_cast<FCSharpFunctionDescriptor*>(
		FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(
			Stack.CurrentNativeFunction->GetOwnerClass(), Stack.CurrentNativeFunction->GetName())))
	{
		FunctionDescriptor->CallCSharp(Context, Stack, RESULT_PARAM);
	}
}
