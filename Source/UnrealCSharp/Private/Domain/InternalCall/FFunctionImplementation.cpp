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
	const FGarbageCollectionHandle InGarbageCollectionHandle, const uint32 InFunctionHash, MonoObject** ReturnValue,
	MonoObject** OutValue, MonoArray* InValue)
{
	if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
	{
		if (const auto FunctionDescriptor = FCSharpEnvironment::GetEnvironment().GetFunctionDescriptor(InFunctionHash))
		{
			FunctionDescriptor->CallUnreal(FoundObject, ReturnValue, OutValue, InValue);
		}
	}
}
