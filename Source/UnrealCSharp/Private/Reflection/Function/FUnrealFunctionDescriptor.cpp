#include "Reflection/Function/FUnrealFunctionDescriptor.h"
#include "CoreMacro/MonoMacro.h"
#include "Domain/FMonoDomain.h"
#include "Environment/FCSharpEnvironment.h"
#include "GarbageCollection/FGarbageCollectionHandle.h"

#define PROCESS_IN_BEGIN(InValue, Params) \
	auto ParamIndex = 0; \
	for (auto Index = 0; Index < PropertyDescriptors.Num(); ++Index) \
	{ \
		const auto& PropertyDescriptor = PropertyDescriptors[Index]; \
		PropertyDescriptor->InitializeValue_InContainer(Params); \
		if (ReferencePropertyIndexes.Contains(Index) || !OutPropertyIndexes.Contains(Index)) \
		{ \
			if (PropertyDescriptor->IsPrimitiveProperty()) \
			{ \
				if (const auto UnBoxValue = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox( \
					ARRAY_GET(InValue, MonoObject*, ParamIndex++))) \
				{ \
					PropertyDescriptor->Set(UnBoxValue, PropertyDescriptor->ContainerPtrToValuePtr<void>(Params)); \
				} \
			} \
			else \
			{ \
				PropertyDescriptor->Set( \
					*static_cast<FGarbageCollectionHandle*>( \
						FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox( \
							ARRAY_GET(InValue, MonoObject*, ParamIndex++))), \
					PropertyDescriptor->ContainerPtrToValuePtr<void>(Params)); \
			}

#define PROCESS_IN_END() \
		} \
	}

#define SLOW_PROCESS_IN(InValue, Params) \
	PROCESS_IN_BEGIN(InValue, Params) \
	PROCESS_IN_END()

#define FAST_PROCESS_IN(InValue, OutParams, Params) \
	auto LastOut = OutParams; \
	PROCESS_IN_BEGIN(InValue, Params) \
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
			} \
	PROCESS_IN_END()

#define PROCESS_OUT(OutValue, Params) \
	if (!OutPropertyIndexes.IsEmpty()) \
	{ \
		const auto MonoObjectArray = FMonoDomain::Array_New(FMonoDomain::Get_Object_Class(), \
		                                                    OutPropertyIndexes.Num()); \
		for (auto Index = 0; Index < OutPropertyIndexes.Num(); ++Index) \
		{ \
			if (const auto OutPropertyDescriptor = PropertyDescriptors[OutPropertyIndexes[Index]]) \
			{ \
				MonoObject* Value = nullptr; \
				OutPropertyDescriptor->Get(OutPropertyDescriptor->ContainerPtrToValuePtr<void>(Params), \
				                           reinterpret_cast<void**>(&Value), true); \
				ARRAY_SET(MonoObjectArray, MonoObject*, Index, Value); \
			} \
		} \
		*OutValue = (MonoObject*)MonoObjectArray; \
	}

#define PROCESS_RETURN(Params) \
	MonoObject* ReturnValue{}; \
	if (ReturnPropertyDescriptor != nullptr) \
	{ \
		ReturnPropertyDescriptor->Get(ReturnPropertyDescriptor->ContainerPtrToValuePtr<void>(Params), \
		                              reinterpret_cast<void**>(&ReturnValue), true); \
	} \
	if (Params != nullptr) \
	{ \
		BufferAllocator->Free(Params); \
	} \
	return ReturnValue;

FUnrealFunctionDescriptor::FUnrealFunctionDescriptor(UFunction* InFunction):
	Super(InFunction,
	      FFunctionParamBufferAllocatorFactory::Factory<FFunctionParamPoolBufferAllocator>(InFunction))
{
}

MonoObject* FUnrealFunctionDescriptor::ProcessEvent(UObject* InObject, MonoObject** OutValue, MonoArray* InValue) const
{
	const auto FunctionCallspace = InObject->GetFunctionCallspace(Function.Get(), nullptr);

	const bool bIsRemote = FunctionCallspace & FunctionCallspace::Remote;

	const bool bIsLocal = FunctionCallspace & FunctionCallspace::Local;

	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	SLOW_PROCESS_IN(InValue, Params);

	if (bIsLocal)
	{
		InObject->UObject::ProcessEvent(Function.Get(), Params);

		PROCESS_OUT(OutValue, Params);

		PROCESS_RETURN(Params);
	}
	else if (bIsRemote)
	{
		InObject->CallRemoteFunction(Function.Get(), Params, nullptr, nullptr);
	}

	if (Params != nullptr)
	{
		BufferAllocator->Free(Params);
	}

	return nullptr;
}

MonoObject* FUnrealFunctionDescriptor::Invoke(UObject* InObject, MonoObject** OutValue, MonoArray* InValue) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	FFrame Stack(InObject, Function.Get(), Params, nullptr, Function->ChildProperties);

	FAST_PROCESS_IN(InValue, &Stack.OutParms, Params);

	const auto ReturnValueAddress = ReturnPropertyDescriptor != nullptr
		                                ? (uint8*)Params + Function->ReturnValueOffset
		                                : nullptr;

	Function->Invoke(InObject, Stack, ReturnValueAddress);

	PROCESS_OUT(OutValue, Params);

	PROCESS_RETURN(Params);
}
