#include "Domain/InternalCall/FFunctionImplementation.h"
#include "Binding/Class/FBindingClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterFunction
{
	FRegisterFunction()
	{
		FBindingClassBuilder(TEXT("Function"), NAMESPACE_FUNCTION)
			.Function("Reflection", static_cast<void*>(FFunctionImplementation::Function_ReflectionImplementation))
			.Register();
	}
};

static FRegisterFunction RegisterFunction;

void FFunctionImplementation::Function_ReflectionImplementation(
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
