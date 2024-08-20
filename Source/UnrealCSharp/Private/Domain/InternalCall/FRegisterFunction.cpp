#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Reflection/Function/FUnrealFunctionDescriptor.h"

#define CALL_IMPLEMENTATION(PropertyType, Type) \
		static Type PropertyType##Call1Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle, const uint32 InFunctionHash) \
		{ \
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle)) \
			{ \
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>( \
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash))) \
				{ \
					return FunctionDescriptor->Call1<Type>(FoundObject); \
				} \
			} \
			return {}; \
		} \
		static Type PropertyType##Call3Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle, const uint32 InFunctionHash, uint8* InBuffer) \
		{ \
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle)) \
			{ \
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>( \
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash))) \
				{ \
					return FunctionDescriptor->Call3<Type>(FoundObject, InBuffer); \
				} \
			} \
			return {}; \
		} \
		static Type PropertyType##Call7Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle, const uint32 InFunctionHash, MonoObject** OutValue, uint8* InBuffer) \
		{ \
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle)) \
			{ \
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>( \
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash))) \
				{ \
					return FunctionDescriptor->Call7<Type>(FoundObject, OutValue, InBuffer); \
				} \
			} \
			return {}; \
		} \
		static Type PropertyType##Call9Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle, const uint32 InFunctionHash) \
		{ \
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle)) \
			{ \
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>( \
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash))) \
				{ \
					return FunctionDescriptor->Call9<Type>(FoundObject); \
				} \
			} \
			return {}; \
		} \
		static Type PropertyType##Call11Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle, const uint32 InFunctionHash, uint8* InBuffer) \
		{ \
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle)) \
			{ \
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>( \
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash))) \
				{ \
					return FunctionDescriptor->Call11<Type>(FoundObject, InBuffer); \
				} \
			} \
			return {}; \
		} \
		static Type PropertyType##Call15Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle, const uint32 InFunctionHash, MonoObject** OutValue, uint8* InBuffer) \
		{ \
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle)) \
			{ \
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>( \
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash))) \
				{ \
					return FunctionDescriptor->Call15<Type>(FoundObject, OutValue, InBuffer); \
				} \
			} \
			return {}; \
		}

namespace
{
	struct FRegisterFunction
	{
		CALL_IMPLEMENTATION(Byte, uint8)

		CALL_IMPLEMENTATION(UInt16, uint16)

		CALL_IMPLEMENTATION(UInt32, uint32)

		CALL_IMPLEMENTATION(UInt64, uint64)

		CALL_IMPLEMENTATION(SByte, int8)

		CALL_IMPLEMENTATION(Int16, int16)

		CALL_IMPLEMENTATION(Int32, int)

		CALL_IMPLEMENTATION(Int64, int64)

		CALL_IMPLEMENTATION(Boolean, bool)

		CALL_IMPLEMENTATION(Single, float)

		static void GenericCall0Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                       const uint32 InFunctionHash)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call0<MonoObject*>(FoundObject);
				}
			}
		}

		static void GenericCall2Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                       const uint32 InFunctionHash, uint8* InBuffer)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call2<MonoObject*>(FoundObject, InBuffer);
				}
			}
		}

		static void GenericCall4Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                       const uint32 InFunctionHash, MonoObject** OutValue)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call4<MonoObject*>(FoundObject, OutValue);
				}
			}
		}

		static void GenericCall6Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                       const uint32 InFunctionHash, MonoObject** OutValue, uint8* InBuffer)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call6<MonoObject*>(FoundObject, OutValue, InBuffer);
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
					FunctionDescriptor->Call8<MonoObject*>(FoundObject);
				}
			}
		}

		static void GenericCall10Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                        const uint32 InFunctionHash, uint8* InBuffer)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call10<MonoObject*>(FoundObject, InBuffer);
				}
			}
		}

		static void GenericCall14Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                        const uint32 InFunctionHash, MonoObject** OutValue, uint8* InBuffer)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call14<MonoObject*>(FoundObject, OutValue, InBuffer);
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
					FunctionDescriptor->Call24<MonoObject*>(FoundObject);
				}
			}
		}

		static void GenericCall26Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                        const uint32 InFunctionHash, uint8* InBuffer)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FunctionDescriptor = static_cast<FUnrealFunctionDescriptor*>(
					FCSharpEnvironment::GetEnvironment().GetOrAddFunctionDescriptor(InFunctionHash)))
				{
					FunctionDescriptor->Call26<MonoObject*>(FoundObject, InBuffer);
				}
			}
		}

		CALL_IMPLEMENTATION(Generic, MonoObject*)

		CALL_IMPLEMENTATION(Double, double)

		FRegisterFunction()
		{
			FClassBuilder(TEXT("FFunction"), NAMESPACE_LIBRARY, true)
				.Function("ByteCall1", ByteCall1Implementation)
				.Function("ByteCall3", ByteCall3Implementation)
				.Function("ByteCall7", ByteCall7Implementation)
				.Function("ByteCall9", ByteCall9Implementation)
				.Function("ByteCall11", ByteCall11Implementation)
				.Function("ByteCall15", ByteCall15Implementation)
				.Function("UInt16Call1", UInt16Call1Implementation)
				.Function("UInt16Call3", UInt16Call3Implementation)
				.Function("UInt16Call7", UInt16Call7Implementation)
				.Function("UInt16Call9", UInt16Call9Implementation)
				.Function("UInt16Call11", UInt16Call11Implementation)
				.Function("UInt16Call15", UInt16Call15Implementation)
				.Function("UInt32Call1", UInt32Call1Implementation)
				.Function("UInt32Call3", UInt32Call3Implementation)
				.Function("UInt32Call7", UInt32Call7Implementation)
				.Function("UInt32Call9", UInt32Call9Implementation)
				.Function("UInt32Call11", UInt32Call11Implementation)
				.Function("UInt32Call15", UInt32Call15Implementation)
				.Function("UInt64Call1", UInt64Call1Implementation)
				.Function("UInt64Call3", UInt64Call3Implementation)
				.Function("UInt64Call7", UInt64Call7Implementation)
				.Function("UInt64Call9", UInt64Call9Implementation)
				.Function("UInt64Call11", UInt64Call11Implementation)
				.Function("UInt64Call15", UInt64Call15Implementation)
				.Function("SByteCall1", SByteCall1Implementation)
				.Function("SByteCall3", SByteCall3Implementation)
				.Function("SByteCall7", SByteCall7Implementation)
				.Function("SByteCall9", SByteCall9Implementation)
				.Function("SByteCall11", SByteCall11Implementation)
				.Function("SByteCall15", SByteCall15Implementation)
				.Function("Int16Call1", Int16Call1Implementation)
				.Function("Int16Call3", Int16Call3Implementation)
				.Function("Int16Call7", Int16Call7Implementation)
				.Function("Int16Call9", Int16Call9Implementation)
				.Function("Int16Call11", Int16Call11Implementation)
				.Function("Int16Call15", Int16Call15Implementation)
				.Function("Int32Call1", Int32Call1Implementation)
				.Function("Int32Call3", Int32Call3Implementation)
				.Function("Int32Call7", Int32Call7Implementation)
				.Function("Int32Call9", Int32Call9Implementation)
				.Function("Int32Call11", Int32Call11Implementation)
				.Function("Int32Call15", Int32Call15Implementation)
				.Function("Int64Call1", Int64Call1Implementation)
				.Function("Int64Call3", Int64Call3Implementation)
				.Function("Int64Call7", Int64Call7Implementation)
				.Function("Int64Call9", Int64Call9Implementation)
				.Function("Int64Call11", Int64Call11Implementation)
				.Function("Int64Call15", Int64Call15Implementation)
				.Function("BooleanCall1", BooleanCall1Implementation)
				.Function("BooleanCall3", BooleanCall3Implementation)
				.Function("BooleanCall7", BooleanCall7Implementation)
				.Function("BooleanCall9", BooleanCall9Implementation)
				.Function("BooleanCall11", BooleanCall11Implementation)
				.Function("BooleanCall15", BooleanCall15Implementation)
				.Function("SingleCall1", SingleCall1Implementation)
				.Function("SingleCall3", SingleCall3Implementation)
				.Function("SingleCall7", SingleCall7Implementation)
				.Function("SingleCall9", SingleCall9Implementation)
				.Function("SingleCall11", SingleCall11Implementation)
				.Function("SingleCall15", SingleCall15Implementation)
				.Function("GenericCall0", GenericCall0Implementation)
				.Function("GenericCall1", GenericCall1Implementation)
				.Function("GenericCall2", GenericCall2Implementation)
				.Function("GenericCall3", GenericCall3Implementation)
				.Function("GenericCall4", GenericCall4Implementation)
				.Function("GenericCall6", GenericCall6Implementation)
				.Function("GenericCall7", GenericCall7Implementation)
				.Function("GenericCall8", GenericCall8Implementation)
				.Function("GenericCall9", GenericCall9Implementation)
				.Function("GenericCall10", GenericCall10Implementation)
				.Function("GenericCall11", GenericCall11Implementation)
				.Function("GenericCall14", GenericCall14Implementation)
				.Function("GenericCall15", GenericCall15Implementation)
				.Function("GenericCall24", GenericCall24Implementation)
				.Function("GenericCall26", GenericCall26Implementation)
				.Function("DoubleCall1", DoubleCall1Implementation)
				.Function("DoubleCall3", DoubleCall3Implementation)
				.Function("DoubleCall7", DoubleCall7Implementation)
				.Function("DoubleCall9", DoubleCall9Implementation)
				.Function("DoubleCall11", DoubleCall11Implementation)
				.Function("DoubleCall15", DoubleCall15Implementation);
		}
	};

	FRegisterFunction RegisterFunction;
}
