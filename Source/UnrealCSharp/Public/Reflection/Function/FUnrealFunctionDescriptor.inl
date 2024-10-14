#pragma once

#include "Macro/FunctionMacro.h"

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call0(UObject* InObject) const
{
	InObject->UObject::ProcessEvent(Function.Get(), nullptr);
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call1(UObject* InObject, uint8* ReturnBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	InObject->UObject::ProcessEvent(Function.Get(), Params);

	PROCESS_RETURN()
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call2(UObject* InObject, uint8* InBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_IN()

	InObject->UObject::ProcessEvent(Function.Get(), Params);
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call3(UObject* InObject, uint8* InBuffer, uint8* ReturnBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_IN()

	InObject->UObject::ProcessEvent(Function.Get(), Params);

	PROCESS_RETURN()
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call4(UObject* InObject, uint8* OutBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	InObject->UObject::ProcessEvent(Function.Get(), Params);

	PROCESS_OUT()
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call6(UObject* InObject, uint8* InBuffer, uint8* OutBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_REFERENCE_IN()

	InObject->UObject::ProcessEvent(Function.Get(), Params);

	PROCESS_OUT()
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call7(UObject* InObject, uint8* InBuffer, uint8* OutBuffer,
                                      uint8* ReturnBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_REFERENCE_IN()

	InObject->UObject::ProcessEvent(Function.Get(), Params);

	PROCESS_OUT()

	PROCESS_RETURN()
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call8(UObject* InObject) const
{
	FFrame Stack(InObject, Function.Get(), nullptr, nullptr, Function->ChildProperties);

	Function->Invoke(InObject, Stack, nullptr);
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call9(UObject* InObject, uint8* ReturnBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	FFrame Stack(InObject, Function.Get(), Params, nullptr, Function->ChildProperties);

	Function->Invoke(InObject, Stack, ReturnPropertyDescriptor->ContainerPtrToValuePtr<void>(Params));

	PROCESS_RETURN()
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call10(UObject* InObject, uint8* InBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	FFrame Stack(InObject, Function.Get(), Params, nullptr, Function->ChildProperties);

	PROCESS_NATIVE_REFERENCE_IN()

	Function->Invoke(InObject, Stack, nullptr);
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call11(UObject* InObject, uint8* InBuffer, uint8* ReturnBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	FFrame Stack(InObject, Function.Get(), Params, nullptr, Function->ChildProperties);

	PROCESS_NATIVE_REFERENCE_IN()

	Function->Invoke(InObject, Stack, ReturnPropertyDescriptor->ContainerPtrToValuePtr<void>(Params));

	PROCESS_RETURN()
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call14(UObject* InObject, uint8* InBuffer, uint8* OutBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	FFrame Stack(InObject, Function.Get(), Params, nullptr, Function->ChildProperties);

	PROCESS_NATIVE_REFERENCE_IN()

	Function->Invoke(InObject, Stack, nullptr);

	PROCESS_OUT()
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call15(UObject* InObject, uint8* InBuffer, uint8* OutBuffer,
                                       uint8* ReturnBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	FFrame Stack(InObject, Function.Get(), Params, nullptr, Function->ChildProperties);

	PROCESS_NATIVE_REFERENCE_IN()

	Function->Invoke(InObject, Stack, ReturnPropertyDescriptor->ContainerPtrToValuePtr<void>(Params));

	PROCESS_OUT()

	PROCESS_RETURN()
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call16(UObject* InObject) const
{
	const auto FunctionCallspace = InObject->GetFunctionCallspace(Function.Get(), nullptr);

	const bool bIsRemote = FunctionCallspace & FunctionCallspace::Remote;

	const bool bIsLocal = FunctionCallspace & FunctionCallspace::Local;

	if (bIsLocal)
	{
		InObject->UObject::ProcessEvent(Function.Get(), nullptr);
	}
	else if (bIsRemote)
	{
		InObject->CallRemoteFunction(Function.Get(), nullptr, nullptr, nullptr);
	}
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call18(UObject* InObject, uint8* InBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_IN()

	const auto FunctionCallspace = InObject->GetFunctionCallspace(Function.Get(), nullptr);

	const bool bIsRemote = FunctionCallspace & FunctionCallspace::Remote;

	const bool bIsLocal = FunctionCallspace & FunctionCallspace::Local;

	if (bIsLocal)
	{
		InObject->UObject::ProcessEvent(Function.Get(), Params);
	}
	else if (bIsRemote)
	{
		InObject->CallRemoteFunction(Function.Get(), Params, nullptr, nullptr);
	}

	if (Params != nullptr)
	{
		BufferAllocator->Free(Params);
	}
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call24(UObject* InObject) const
{
	const auto FunctionCallspace = InObject->GetFunctionCallspace(Function.Get(), nullptr);

	const bool bIsRemote = FunctionCallspace & FunctionCallspace::Remote;

	const bool bIsLocal = FunctionCallspace & FunctionCallspace::Local;

	if (bIsLocal)
	{
		InObject->UObject::ProcessEvent(Function.Get(), nullptr);
	}
	else if (bIsRemote)
	{
		InObject->CallRemoteFunction(Function.Get(), nullptr, nullptr, nullptr);
	}
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call26(UObject* InObject, uint8* InBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_IN()

	const auto FunctionCallspace = InObject->GetFunctionCallspace(Function.Get(), nullptr);

	const bool bIsRemote = FunctionCallspace & FunctionCallspace::Remote;

	const bool bIsLocal = FunctionCallspace & FunctionCallspace::Local;

	if (bIsLocal)
	{
		InObject->UObject::ProcessEvent(Function.Get(), Params);
	}
	else if (bIsRemote)
	{
		InObject->CallRemoteFunction(Function.Get(), Params, nullptr, nullptr);
	}

	if (Params != nullptr)
	{
		BufferAllocator->Free(Params);
	}
}
