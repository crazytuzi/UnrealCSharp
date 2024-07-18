#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Reflection/Function/FUnrealFunctionDescriptor.h"

namespace
{
	struct FRegisterFunction
	{
		static MonoObject* ProcessEvent(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                const uint32 InFunctionHash, MonoObject** OutValue,
		                                MonoArray* InValue)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					return FunctionDescriptor->ProcessEvent(FoundObject, OutValue, InValue);
				}
			}

			return nullptr;
		}

		static void Reflection0Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                      const uint32 InFunctionHash)
		{
			ProcessEvent(InGarbageCollectionHandle, InFunctionHash, nullptr, nullptr);
		}

		static MonoObject* Reflection1Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                             const uint32 InFunctionHash)
		{
			return ProcessEvent(InGarbageCollectionHandle, InFunctionHash, nullptr, nullptr);
		}

		static void Reflection2Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                      const uint32 InFunctionHash, MonoArray* InValue)
		{
			ProcessEvent(InGarbageCollectionHandle, InFunctionHash, nullptr, InValue);
		}

		static MonoObject* Reflection3Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                             const uint32 InFunctionHash, MonoArray* InValue)
		{
			return ProcessEvent(InGarbageCollectionHandle, InFunctionHash, nullptr, InValue);
		}

		static void Reflection4Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                      const uint32 InFunctionHash, MonoObject** OutValue)
		{
			ProcessEvent(InGarbageCollectionHandle, InFunctionHash, OutValue, nullptr);
		}

		static MonoObject* Reflection5Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                             const uint32 InFunctionHash, MonoObject** OutValue)
		{
			return ProcessEvent(InGarbageCollectionHandle, InFunctionHash, OutValue, nullptr);
		}

		static void Reflection6Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                      const uint32 InFunctionHash, MonoObject** OutValue,
		                                      MonoArray* InValue)
		{
			ProcessEvent(InGarbageCollectionHandle, InFunctionHash, OutValue, InValue);
		}

		static MonoObject* Reflection7Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                             const uint32 InFunctionHash, MonoObject** OutValue,
		                                             MonoArray* InValue)
		{
			return ProcessEvent(InGarbageCollectionHandle, InFunctionHash, OutValue, InValue);
		}

		static MonoObject* Invoke(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                          const uint32 InFunctionHash, MonoObject** OutValue,
		                          MonoArray* InValue)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					return FunctionDescriptor->Invoke(FoundObject, OutValue, InValue);
				}
			}

			return nullptr;
		}

		static void Reflection8Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                      const uint32 InFunctionHash)
		{
			Invoke(InGarbageCollectionHandle, InFunctionHash, nullptr, nullptr);
		}

		static MonoObject* Reflection9Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                             const uint32 InFunctionHash)
		{
			return Invoke(InGarbageCollectionHandle, InFunctionHash, nullptr, nullptr);
		}

		static void Reflection10Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                       const uint32 InFunctionHash, MonoArray* InValue)
		{
			Invoke(InGarbageCollectionHandle, InFunctionHash, nullptr, InValue);
		}

		static MonoObject* Reflection11Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                              const uint32 InFunctionHash, MonoArray* InValue)
		{
			return Invoke(InGarbageCollectionHandle, InFunctionHash, nullptr, InValue);
		}

		static void Reflection12Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                       const uint32 InFunctionHash, MonoObject** OutValue)
		{
			Invoke(InGarbageCollectionHandle, InFunctionHash, OutValue, nullptr);
		}

		static MonoObject* Reflection13Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                              const uint32 InFunctionHash, MonoObject** OutValue)
		{
			return Invoke(InGarbageCollectionHandle, InFunctionHash, OutValue, nullptr);
		}

		static void Reflection14Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                       const uint32 InFunctionHash, MonoObject** OutValue,
		                                       MonoArray* InValue)
		{
			Invoke(InGarbageCollectionHandle, InFunctionHash, OutValue, InValue);
		}

		static MonoObject* Reflection15Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                              const uint32 InFunctionHash, MonoObject** OutValue,
		                                              MonoArray* InValue)
		{
			return Invoke(InGarbageCollectionHandle, InFunctionHash, OutValue, InValue);
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
				.Function("Reflection7", Reflection7Implementation)
				.Function("Reflection8", Reflection8Implementation)
				.Function("Reflection9", Reflection9Implementation)
				.Function("Reflection10", Reflection10Implementation)
				.Function("Reflection11", Reflection11Implementation)
				.Function("Reflection12", Reflection12Implementation)
				.Function("Reflection13", Reflection13Implementation)
				.Function("Reflection14", Reflection14Implementation)
				.Function("Reflection15", Reflection15Implementation);
		}
	};

	FRegisterFunction RegisterFunction;
}
