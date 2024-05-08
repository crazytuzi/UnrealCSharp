#include "Reflection/Function/FUnrealFunctionDescriptor.h"

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

	SlowProcessIn(InValue, Params);

	if (bIsLocal)
	{
		InObject->UObject::ProcessEvent(Function.Get(), Params);

		ProcessOut(OutValue, Params);

		return ProcessReturn(Params);
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

	FastProcessIn(InValue, &Stack.OutParms, Params);

	const auto ReturnValueAddress = ReturnPropertyDescriptor != nullptr
		                                ? (uint8*)Params + Function->ReturnValueOffset
		                                : nullptr;

	Function->Invoke(InObject, Stack, ReturnValueAddress);

	ProcessOut(OutValue, Params);

	return ProcessReturn(Params);
}
