#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterFunction
{
	static void ReflectionImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                     const uint32 InFunctionHash, MonoObject** ReturnValue,
	                                     MonoObject** OutValue, MonoArray* InValue)
	{
		if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
		{
			if (const auto FunctionDescriptor = FCSharpEnvironment::GetEnvironment().
				GetOrAddFunctionDescriptor(InFunctionHash))
			{
				FunctionDescriptor->CallUnreal(FoundObject, ReturnValue, OutValue, InValue);
			}
		}
	}

	FRegisterFunction()
	{
		FClassBuilder(TEXT("Function"), NAMESPACE_LIBRARY)
			.Function("Reflection", ReflectionImplementation)
			.Register();
	}
};

static FRegisterFunction RegisterFunction;
