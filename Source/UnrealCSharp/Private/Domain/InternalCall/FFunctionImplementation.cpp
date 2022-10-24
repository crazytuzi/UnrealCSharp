#include "Domain/InternalCall/FFunctionImplementation.h"
#include "Environment/FCSharpEnvironment.h"

void FFunctionImplementation::CallReflectionFunctionImplementation(MonoObject InMonoObject,
                                                                   const UTF16CHAR* InFunctionName, MonoArray* InValue)
{
	if (const auto FoundObject = FCSharpEnvironment::GetEnvironment()->GetObject(&InMonoObject))
	{
		const auto FunctionName = StringCast<TCHAR>(InFunctionName + 10).Get();

		if (const auto FoundFunction = FoundObject->FindFunction(FunctionName))
		{
			FFrame Stack{FoundObject, FoundFunction, nullptr};

			FoundObject->CallFunction(Stack, nullptr, FoundFunction);
		}
	}
}
