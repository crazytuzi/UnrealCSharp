#pragma once

#include "CoreMacro/MonoMacro.h"
#include "Domain/FMonoDomain.h"
#include "Macro/FunctionMacro.h"

template <typename T>
void FUnrealFunctionDescriptor::Call0(UObject* InObject) const
{
	InObject->UObject::ProcessEvent(Function.Get(), nullptr);
}

template <typename T>
auto FUnrealFunctionDescriptor::Call1(UObject* InObject) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	InObject->UObject::ProcessEvent(Function.Get(), Params);

	if constexpr (std::is_same_v<T, MonoObject*>)
	{
		PROCESS_COMPOUND_RETURN(Params);
	}
	else
	{
		PROCESS_PRIMITIVE_RETURN(Params, T)
	}
}

template <typename T>
void FUnrealFunctionDescriptor::Call2(UObject* InObject, uint8* InBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_IN(InBuffer, Params);

	InObject->UObject::ProcessEvent(Function.Get(), Params);
}

template <typename T>
auto FUnrealFunctionDescriptor::Call3(UObject* InObject, uint8* InBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_IN(InBuffer, Params);

	InObject->UObject::ProcessEvent(Function.Get(), Params);

	if constexpr (std::is_same_v<T, MonoObject*>)
	{
		PROCESS_COMPOUND_RETURN(Params);
	}
	else
	{
		PROCESS_PRIMITIVE_RETURN(Params, T)
	}
}

template <typename T>
void FUnrealFunctionDescriptor::Call4(UObject* InObject, MonoObject** OutValue) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	InObject->UObject::ProcessEvent(Function.Get(), Params);

	PROCESS_OUT(OutValue, Params);
}

template <typename T>
void FUnrealFunctionDescriptor::Call6(UObject* InObject, MonoObject** OutValue, uint8* InBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_REFERENCE_IN(InBuffer, Params);

	InObject->UObject::ProcessEvent(Function.Get(), Params);

	PROCESS_OUT(OutValue, Params);
}

template <typename T>
auto FUnrealFunctionDescriptor::Call7(UObject* InObject, MonoObject** OutValue, uint8* InBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_REFERENCE_IN(InBuffer, Params);

	InObject->UObject::ProcessEvent(Function.Get(), Params);

	PROCESS_OUT(OutValue, Params);

	if constexpr (std::is_same_v<T, MonoObject*>)
	{
		PROCESS_COMPOUND_RETURN(Params);
	}
	else
	{
		PROCESS_PRIMITIVE_RETURN(Params, T)
	}
}

template <typename T>
void FUnrealFunctionDescriptor::Call8(UObject* InObject) const
{
	FFrame Stack(InObject, Function.Get(), nullptr, nullptr, Function->ChildProperties);

	Function->Invoke(InObject, Stack, nullptr);
}

template <typename T>
auto FUnrealFunctionDescriptor::Call9(UObject* InObject) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	FFrame Stack(InObject, Function.Get(), Params, nullptr, Function->ChildProperties);

	Function->Invoke(InObject, Stack, ReturnPropertyDescriptor->ContainerPtrToValuePtr<void>(Params));

	if constexpr (std::is_same_v<T, MonoObject*>)
	{
		PROCESS_COMPOUND_RETURN(Params);
	}
	else
	{
		PROCESS_PRIMITIVE_RETURN(Params, T)
	}
}

template <typename T>
void FUnrealFunctionDescriptor::Call10(UObject* InObject, uint8* InBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	FFrame Stack(InObject, Function.Get(), Params, nullptr, Function->ChildProperties);

	PROCESS_NATIVE_REFERENCE_IN(InBuffer, &Stack.OutParms, Params);

	Function->Invoke(InObject, Stack, nullptr);
}

template <typename T>
auto FUnrealFunctionDescriptor::Call11(UObject* InObject, uint8* InBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	FFrame Stack(InObject, Function.Get(), Params, nullptr, Function->ChildProperties);

	PROCESS_NATIVE_REFERENCE_IN(InBuffer, &Stack.OutParms, Params);

	Function->Invoke(InObject, Stack, ReturnPropertyDescriptor->ContainerPtrToValuePtr<void>(Params));

	if constexpr (std::is_same_v<T, MonoObject*>)
	{
		PROCESS_COMPOUND_RETURN(Params);
	}
	else
	{
		PROCESS_PRIMITIVE_RETURN(Params, T)
	}
}

template <typename T>
void FUnrealFunctionDescriptor::Call14(UObject* InObject, MonoObject** OutValue, uint8* InBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	FFrame Stack(InObject, Function.Get(), Params, nullptr, Function->ChildProperties);

	PROCESS_NATIVE_REFERENCE_IN(InBuffer, &Stack.OutParms, Params);

	Function->Invoke(InObject, Stack, nullptr);

	PROCESS_OUT(OutValue, Params);
}

template <typename T>
auto FUnrealFunctionDescriptor::Call15(UObject* InObject, MonoObject** OutValue, uint8* InBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	FFrame Stack(InObject, Function.Get(), Params, nullptr, Function->ChildProperties);

	PROCESS_NATIVE_REFERENCE_IN(InBuffer, &Stack.OutParms, Params);

	Function->Invoke(InObject, Stack, ReturnPropertyDescriptor->ContainerPtrToValuePtr<void>(Params));

	PROCESS_OUT(OutValue, Params);

	if constexpr (std::is_same_v<T, MonoObject*>)
	{
		PROCESS_COMPOUND_RETURN(Params);
	}
	else
	{
		PROCESS_PRIMITIVE_RETURN(Params, T)
	}
}

template <typename T>
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

template <typename T>
void FUnrealFunctionDescriptor::Call26(UObject* InObject, uint8* InBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_IN(InBuffer, Params);

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
