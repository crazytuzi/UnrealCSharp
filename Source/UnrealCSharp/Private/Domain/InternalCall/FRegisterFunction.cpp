#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/BufferMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Reflection/Function/FUnrealFunctionDescriptor.h"

namespace
{
	struct FRegisterFunction
	{
		static void GenericCall0Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                       const uint32 InFunctionHash)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call0<>(FoundObject);
				}
			}
		}

		static void PrimitiveCall1Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                         const uint32 InFunctionHash, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call1<EFunctionReturnType::Primitive>(FoundObject, RETURN_BUFFER);
				}
			}
		}

		static void CompoundCall1Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                        const uint32 InFunctionHash, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call1<EFunctionReturnType::Compound>(FoundObject, RETURN_BUFFER);
				}
			}
		}

		static void GenericCall2Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                       const uint32 InFunctionHash, IN_BUFFER_SIGNATURE)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call2<>(FoundObject, IN_BUFFER);
				}
			}
		}

		static void PrimitiveCall3Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                         const uint32 InFunctionHash, IN_BUFFER_SIGNATURE,
		                                         RETURN_BUFFER_SIGNATURE)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call3<EFunctionReturnType::Primitive>(FoundObject, IN_BUFFER, RETURN_BUFFER);
				}
			}
		}

		static void CompoundCall3Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                        const uint32 InFunctionHash, IN_BUFFER_SIGNATURE,
		                                        RETURN_BUFFER_SIGNATURE)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call3<EFunctionReturnType::Compound>(FoundObject, IN_BUFFER, RETURN_BUFFER);
				}
			}
		}

		static void GenericCall4Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                       const uint32 InFunctionHash, OUT_BUFFER_SIGNATURE)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call4<>(FoundObject, OUT_BUFFER);
				}
			}
		}

		static void GenericCall6Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                       const uint32 InFunctionHash, IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call6<>(FoundObject, IN_BUFFER, OUT_BUFFER);
				}
			}
		}

		static void PrimitiveCall7Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                         const uint32 InFunctionHash, IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE,
		                                         RETURN_BUFFER_SIGNATURE)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call7<EFunctionReturnType::Primitive>(
						FoundObject, IN_BUFFER, OUT_BUFFER, RETURN_BUFFER);
				}
			}
		}

		static void CompoundCall7Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                        const uint32 InFunctionHash, IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE,
		                                        RETURN_BUFFER_SIGNATURE)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call7<EFunctionReturnType::Compound>(
						FoundObject, IN_BUFFER, OUT_BUFFER, RETURN_BUFFER);
				}
			}
		}

		static void GenericCall8Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                       const uint32 InFunctionHash)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call8<>(FoundObject);
				}
			}
		}

		static void PrimitiveCall9Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                         const uint32 InFunctionHash, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call9<EFunctionReturnType::Primitive>(FoundObject, RETURN_BUFFER);
				}
			}
		}

		static void CompoundCall9Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                        const uint32 InFunctionHash, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call9<EFunctionReturnType::Compound>(FoundObject, RETURN_BUFFER);
				}
			}
		}

		static void GenericCall10Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                        const uint32 InFunctionHash, IN_BUFFER_SIGNATURE)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call10<>(FoundObject, IN_BUFFER);
				}
			}
		}

		static void PrimitiveCall11Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                          const uint32 InFunctionHash, IN_BUFFER_SIGNATURE,
		                                          RETURN_BUFFER_SIGNATURE)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call11<EFunctionReturnType::Primitive>(FoundObject, IN_BUFFER, RETURN_BUFFER);
				}
			}
		}

		static void CompoundCall11Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                         const uint32 InFunctionHash, IN_BUFFER_SIGNATURE,
		                                         RETURN_BUFFER_SIGNATURE)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call11<EFunctionReturnType::Compound>(FoundObject, IN_BUFFER, RETURN_BUFFER);
				}
			}
		}

		static void GenericCall14Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                        const uint32 InFunctionHash, IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call14<>(FoundObject, IN_BUFFER, OUT_BUFFER);
				}
			}
		}

		static void PrimitiveCall15Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                          const uint32 InFunctionHash, IN_BUFFER_SIGNATURE,
		                                          OUT_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call15<EFunctionReturnType::Primitive>(
						FoundObject, IN_BUFFER, OUT_BUFFER, RETURN_BUFFER);
				}
			}
		}

		static void CompoundCall15Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                         const uint32 InFunctionHash, IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE,
		                                         RETURN_BUFFER_SIGNATURE)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call15<EFunctionReturnType::Compound>(
						FoundObject, IN_BUFFER, OUT_BUFFER, RETURN_BUFFER);
				}
			}
		}

		static void GenericCall16Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                        const uint32 InFunctionHash)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call16<>(FoundObject);
				}
			}
		}

		static void GenericCall18Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                        const uint32 InFunctionHash, IN_BUFFER_SIGNATURE)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call18<>(FoundObject, IN_BUFFER);
				}
			}
		}

		static void GenericCall24Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                        const uint32 InFunctionHash)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call24<>(FoundObject);
				}
			}
		}

		static void GenericCall26Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                        const uint32 InFunctionHash, IN_BUFFER_SIGNATURE)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call26<>(FoundObject, IN_BUFFER);
				}
			}
		}

		FRegisterFunction()
		{
			FClassBuilder(TEXT("FFunction"), NAMESPACE_LIBRARY)
				.Function("GenericCall0", GenericCall0Implementation)
				.Function("PrimitiveCall1", PrimitiveCall1Implementation)
				.Function("CompoundCall1", CompoundCall1Implementation)
				.Function("GenericCall2", GenericCall2Implementation)
				.Function("PrimitiveCall3", PrimitiveCall3Implementation)
				.Function("CompoundCall3", CompoundCall3Implementation)
				.Function("GenericCall4", GenericCall4Implementation)
				.Function("GenericCall6", GenericCall6Implementation)
				.Function("PrimitiveCall7", PrimitiveCall7Implementation)
				.Function("CompoundCall7", CompoundCall7Implementation)
				.Function("GenericCall8", GenericCall8Implementation)
				.Function("PrimitiveCall9", PrimitiveCall9Implementation)
				.Function("CompoundCall9", CompoundCall9Implementation)
				.Function("GenericCall10", GenericCall10Implementation)
				.Function("PrimitiveCall11", PrimitiveCall11Implementation)
				.Function("CompoundCall11", CompoundCall11Implementation)
				.Function("GenericCall14", GenericCall14Implementation)
				.Function("PrimitiveCall15", PrimitiveCall15Implementation)
				.Function("CompoundCall15", CompoundCall15Implementation)
				.Function("GenericCall16", GenericCall16Implementation)
				.Function("GenericCall18", GenericCall18Implementation)
				.Function("GenericCall24", GenericCall24Implementation)
				.Function("GenericCall26", GenericCall26Implementation);
		}
	};

	[[maybe_unused]] FRegisterFunction RegisterFunction;
}
