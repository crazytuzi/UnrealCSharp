#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Reflection/Function/FUnrealFunctionDescriptor.h"

struct FRegisterFunction
{
	static MonoObject* ReflectionImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                            const uint32 InFunctionHash, MonoObject** OutValue, MonoArray* InValue)
	{
		if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
		{
			if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
				FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
			{
				return FunctionDescriptor->CallUnreal(FoundObject, OutValue, InValue);
			}
		}

		return nullptr;
	}

	static void Reflection0Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                      const uint32 InFunctionHash)
	{
		ReflectionImplementation(InGarbageCollectionHandle, InFunctionHash, nullptr, nullptr);
	}

	static MonoObject* Reflection1Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                             const uint32 InFunctionHash)
	{
		return ReflectionImplementation(InGarbageCollectionHandle, InFunctionHash, nullptr, nullptr);
	}

	static void Reflection2Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                      const uint32 InFunctionHash, MonoArray* InValue)
	{
		ReflectionImplementation(InGarbageCollectionHandle, InFunctionHash, nullptr, InValue);
	}

	static MonoObject* Reflection3Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                             const uint32 InFunctionHash, MonoArray* InValue)
	{
		return ReflectionImplementation(InGarbageCollectionHandle, InFunctionHash, nullptr, InValue);
	}

	static void Reflection4Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                      const uint32 InFunctionHash, MonoObject** OutValue)
	{
		ReflectionImplementation(InGarbageCollectionHandle, InFunctionHash, OutValue, nullptr);
	}

	static MonoObject* Reflection5Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                             const uint32 InFunctionHash, MonoObject** OutValue)
	{
		return ReflectionImplementation(InGarbageCollectionHandle, InFunctionHash, OutValue, nullptr);
	}

	static void Reflection6Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                      const uint32 InFunctionHash, MonoObject** OutValue, MonoArray* InValue)
	{
		ReflectionImplementation(InGarbageCollectionHandle, InFunctionHash, OutValue, InValue);
	}

	static MonoObject* Reflection7Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                             const uint32 InFunctionHash, MonoObject** OutValue, MonoArray* InValue)
	{
		return ReflectionImplementation(InGarbageCollectionHandle, InFunctionHash, OutValue, InValue);
	}

	FRegisterFunction()
	{
		FClassBuilder(TEXT("FFunction"), NAMESPACE_LIBRARY, true)
			.Function("Reflection0", Reflection0Implementation)
			.Function("Reflection1", Reflection1Implementation)
			.Function("Reflection2", Reflection2Implementation)
			.Function("Reflection3", Reflection3Implementation)
			.Function("Reflection4", Reflection4Implementation)
			.Function("Reflection5", Reflection5Implementation)
			.Function("Reflection6", Reflection6Implementation)
			.Function("Reflection7", Reflection7Implementation);
	}
};

static FRegisterFunction RegisterFunction;
