#pragma once

#define FUNCTION_CSHARP_CALLBACK FString(TEXT("CSharpCallBack"))

#define FUNCTION_UTILS_IS_OVERRIDE_TYPE FString(TEXT("IsOverrideType"))

#define FUNCTION_UTILS_IS_OVERRIDE_METHOD FString(TEXT("IsOverrideMethod"))

#define FUNCTION_UTILS_GET_TRACEBACK FString(TEXT("GetTraceback"))

#define FUNCTION_SYNCHRONIZATION_CONTEXT_INITIALIZE FString(TEXT("Initialize"))

#define FUNCTION_SYNCHRONIZATION_CONTEXT_DEINITIALIZE FString(TEXT("Deinitialize"))

#define FUNCTION_SYNCHRONIZATION_CONTEXT_TICK FString(TEXT("Tick"))

#define FUNCTION_DESTRUCTOR FString(TEXT("Destructor"))

#define FUNCTION_GET_SUBSCRIPT FString(TEXT("GetSubscript"))

#define FUNCTION_SET_SUBSCRIPT FString(TEXT("SetSubscript"))

#define FUNCTION_LOGICAL_NOT FString(TEXT("LogicalNot"))

#define FUNCTION_UNARY_PLUS FString(TEXT("UnaryPlus"))

#define FUNCTION_UNARY_MINUS FString(TEXT("UnaryMinus"))

#define FUNCTION_COMPLEMENT FString(TEXT("Complement"))

#define FUNCTION_PRE_INCREMENT FString(TEXT("PreIncrement"))

#define FUNCTION_PRE_DECREMENT FString(TEXT("PreDecrement"))

#define FUNCTION_PLUS FString(TEXT("Plus"))

#define FUNCTION_MINUS FString(TEXT("Minus"))

#define FUNCTION_MULTIPLIES FString(TEXT("Multiplies"))

#define FUNCTION_DIVIDES FString(TEXT("Divides"))

#define FUNCTION_MODULUS FString(TEXT("Modulus"))

#define FUNCTION_BIT_AND FString(TEXT("BitAnd"))

#define FUNCTION_BIT_OR FString(TEXT("BitOr"))

#define FUNCTION_BIT_XOR FString(TEXT("BitXor"))

#define FUNCTION_LEFT_SHIFT FString(TEXT("LeftShift"))

#define FUNCTION_RIGHT_SHIFT FString(TEXT("RightShift"))

#define FUNCTION_EQUAL_TO FString(TEXT("EqualTo"))

#define FUNCTION_NOT_EQUAL_TO FString(TEXT("NotEqualTo"))

#define FUNCTION_LESS FString(TEXT("Less"))

#define FUNCTION_LESS_EQUAL FString(TEXT("LessEqual"))

#define FUNCTION_GREATER FString(TEXT("Greater"))

#define FUNCTION_GREATER_EQUAL FString(TEXT("GreaterEqual"))

#define INITIALIZE_VALUE() \
	for (auto Index = 0; Index < PropertyDescriptors.Num(); ++Index) \
	{ \
		const auto& PropertyDescriptor = PropertyDescriptors[Index]; \
		PropertyDescriptor->InitializeValue_InContainer(Params);

#define IN_VALUE() \
		PropertyDescriptor->Set(InBuffer + InBufferOffsets[Index], PropertyDescriptor->ContainerPtrToValuePtr<void>(Params));

#define REFERENCE_IN_VALUE() \
		if (ReferencePropertyIndexes.Contains(Index) || !OutPropertyIndexes.Contains(Index)) \
		{ \
			IN_VALUE() \
		}

#define IN_END() \
	}

#define PROCESS_SCRIPT_IN() \
	INITIALIZE_VALUE() \
	IN_VALUE() \
	IN_END()

#define PROCESS_SCRIPT_REFERENCE_IN() \
	INITIALIZE_VALUE() \
	REFERENCE_IN_VALUE() \
	IN_END()

#define NATIVE_OUT_VALUE() \
		CA_SUPPRESS(6263) \
		const auto Out = (FOutParmRec*)FMemory_Alloca(sizeof(FOutParmRec)); \
		Out->Property = PropertyDescriptor->GetProperty(); \
		Out->PropAddr = (uint8*)PropertyDescriptor->ContainerPtrToValuePtr<void>(Params); \
		if (*LastOut) \
		{ \
			(*LastOut)->NextOutParm = Out; \
			LastOut = &(*LastOut)->NextOutParm; \
		} \
		else \
		{ \
			*LastOut = Out; \
		}

#define PROCESS_NATIVE_REFERENCE_IN() \
	auto LastOut = &Stack.OutParms; \
	INITIALIZE_VALUE() \
	IN_VALUE() \
	NATIVE_OUT_VALUE() \
	IN_END()

#define PROCESS_OUT() \
	for (auto Index = 0; Index < OutPropertyIndexes.Num(); ++Index) \
	{ \
		if (const auto OutPropertyDescriptor = PropertyDescriptors[OutPropertyIndexes[Index]]) \
		{ \
			if (OutPropertyDescriptor->IsPrimitiveProperty()) \
			{ \
				OutPropertyDescriptor->Get(OutPropertyDescriptor->ContainerPtrToValuePtr<void>(Params), \
										   OutBuffer + OutBufferOffsets[Index]); \
			} \
			else \
			{ \
				OutPropertyDescriptor->Get<std::true_type>( \
					OutPropertyDescriptor->CopyValue(OutPropertyDescriptor->ContainerPtrToValuePtr<void>(Params)), \
					reinterpret_cast<void**>(OutBuffer + OutBufferOffsets[Index])); \
			} \
		} \
	}

#define PROCESS_RETURN() \
	if constexpr (ReturnType == EFunctionReturnType::Primitive) \
	{ \
		ReturnPropertyDescriptor->Get(ReturnPropertyDescriptor->ContainerPtrToValuePtr<void>(Params), ReturnBuffer); \
	} \
	else if constexpr (ReturnType == EFunctionReturnType::Compound) \
	{ \
		ReturnPropertyDescriptor->Get<std::true_type>( \
			ReturnPropertyDescriptor->CopyValue(ReturnPropertyDescriptor->ContainerPtrToValuePtr<void>(Params)), \
			reinterpret_cast<void**>(ReturnBuffer)); \
	} \
	BufferAllocator->Free(Params);
