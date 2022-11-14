#include "Domain/InternalCall/FFunctionImplementation.h"
#include "Environment/FCSharpEnvironment.h"

void FFunctionImplementation::CallReflectionMemberFunctionImplementation(
	const MonoObject* InMonoObject, const UTF16CHAR* InFunctionName, MonoObject** ReturnValue, MonoObject** OutValue,
	MonoArray* InValue)
{
	if (const auto FoundObject = FCSharpEnvironment::GetEnvironment()->GetObject(InMonoObject))
	{
		const auto FunctionName = StringCast<TCHAR>(InFunctionName + 10).Get();

		if (const auto FunctionDescriptor = FCSharpEnvironment::GetEnvironment()->GetFunctionDescriptor(
			FoundObject->GetClass(), FunctionName))
		{
			FunctionDescriptor->CallUnreal(FoundObject, ReturnValue, OutValue, InValue);
		}
	}
}

void FFunctionImplementation::CallReflectionStaticFunctionImplementation(
	const UTF16CHAR* InClassName, const UTF16CHAR* InFunctionName, MonoObject** ReturnValue, MonoObject** OutValue,
	MonoArray* InValue)
{
	const auto ClassName = StringCast<TCHAR>(InClassName + 10).Get();

	const auto FunctionName = StringCast<TCHAR>(InFunctionName + 10).Get();

	if (const auto FunctionDescriptor = FCSharpEnvironment::GetEnvironment()->GetFunctionDescriptor(
		ClassName, FunctionName))
	{
		FunctionDescriptor->CallUnreal(ReturnValue, OutValue, InValue);
	}
}
