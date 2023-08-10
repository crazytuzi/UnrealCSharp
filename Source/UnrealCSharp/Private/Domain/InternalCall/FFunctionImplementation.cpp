#include "Domain/InternalCall/FFunctionImplementation.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterFunction
{
	FRegisterFunction()
	{
		FClassBuilder(TEXT("Function"), NAMESPACE_LIBRARY)
			.Function("Reflection", FFunctionImplementation::Function_ReflectionImplementation)
			.Register();
	}
};

static FRegisterFunction RegisterFunction;

void FFunctionImplementation::Function_ReflectionImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoString* InFunctionName, MonoObject** ReturnValue,
	MonoObject** OutValue, MonoArray* InValue)
{
	if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
	{
		const auto FunctionName = FName(
			UTF8_TO_TCHAR(FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(InFunctionName)));

		if (const auto FunctionDescriptor = FCSharpEnvironment::GetEnvironment().GetFunctionDescriptor(
			FoundObject->GetClass(), FunctionName))
		{
			FunctionDescriptor->CallUnreal(FoundObject, ReturnValue, OutValue, InValue);
		}
	}
}
