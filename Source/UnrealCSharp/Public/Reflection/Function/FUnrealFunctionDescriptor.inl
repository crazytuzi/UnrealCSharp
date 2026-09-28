#pragma once

#include "CoreMacro/BufferMacro.h"
#include "Macro/FunctionMacro.h"

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call0(UObject* InObject) const
{
	if (const auto FoundFunction = Function.Get())
	{
		InObject->UObject::ProcessEvent(FoundFunction, nullptr);
	}
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call1(UObject* InObject, RETURN_BUFFER_SIGNATURE) const
{
	if (const auto FoundFunction = Function.Get())
	{
		const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

		InObject->UObject::ProcessEvent(FoundFunction, Params);

		PROCESS_RETURN()
	}
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call2(UObject* InObject, IN_BUFFER_SIGNATURE) const
{
	if (const auto FoundFunction = Function.Get())
	{
		const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

		PROCESS_SCRIPT_IN()

		InObject->UObject::ProcessEvent(FoundFunction, Params);
	}
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call3(UObject* InObject, IN_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE) const
{
	if (const auto FoundFunction = Function.Get())
	{
		const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

		PROCESS_SCRIPT_IN()

		InObject->UObject::ProcessEvent(FoundFunction, Params);

		PROCESS_RETURN()
	}
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call4(UObject* InObject, OUT_BUFFER_SIGNATURE) const
{
	if (const auto FoundFunction = Function.Get())
	{
		const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

		InObject->UObject::ProcessEvent(FoundFunction, Params);

		PROCESS_OUT()
	}
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call5(UObject* InObject, OUT_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE) const
{
	if (const auto FoundFunction = Function.Get())
	{
		const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

		InObject->UObject::ProcessEvent(FoundFunction, Params);

		PROCESS_OUT()

		PROCESS_RETURN()
	}
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call6(UObject* InObject, IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE) const
{
	if (const auto FoundFunction = Function.Get())
	{
		const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

		PROCESS_SCRIPT_REFERENCE_IN()

		InObject->UObject::ProcessEvent(FoundFunction, Params);

		PROCESS_OUT()
	}
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call7(UObject* InObject, IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE,
                                      RETURN_BUFFER_SIGNATURE) const
{
	if (const auto FoundFunction = Function.Get())
	{
		const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

		PROCESS_SCRIPT_REFERENCE_IN()

		InObject->UObject::ProcessEvent(FoundFunction, Params);

		PROCESS_OUT()

		PROCESS_RETURN()
	}
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call8(UObject* InObject) const
{
	if (const auto FoundFunction = Function.Get())
	{
		FFrame Stack(InObject, FoundFunction, nullptr, nullptr, FoundFunction->ChildProperties);

		FoundFunction->Invoke(InObject, Stack, nullptr);
	}
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call9(UObject* InObject, RETURN_BUFFER_SIGNATURE) const
{
	if (const auto FoundFunction = Function.Get())
	{
		const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

		FFrame Stack(InObject, FoundFunction, Params, nullptr, FoundFunction->ChildProperties);

		FoundFunction->Invoke(InObject, Stack, ReturnPropertyDescriptor->ContainerPtrToValuePtr<void>(Params));

		PROCESS_RETURN()
	}
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call10(UObject* InObject, IN_BUFFER_SIGNATURE) const
{
	if (const auto FoundFunction = Function.Get())
	{
		const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

		FFrame Stack(InObject, FoundFunction, Params, nullptr, FoundFunction->ChildProperties);

		PROCESS_NATIVE_REFERENCE_IN()

		FoundFunction->Invoke(InObject, Stack, nullptr);
	}
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call11(UObject* InObject, IN_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE) const
{
	if (const auto FoundFunction = Function.Get())
	{
		const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

		FFrame Stack(InObject, FoundFunction, Params, nullptr, FoundFunction->ChildProperties);

		PROCESS_NATIVE_REFERENCE_IN()

		FoundFunction->Invoke(InObject, Stack, ReturnPropertyDescriptor->ContainerPtrToValuePtr<void>(Params));

		PROCESS_RETURN()
	}
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call14(UObject* InObject, IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE) const
{
	if (const auto FoundFunction = Function.Get())
	{
		const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

		FFrame Stack(InObject, FoundFunction, Params, nullptr, FoundFunction->ChildProperties);

		PROCESS_NATIVE_REFERENCE_IN()

		FoundFunction->Invoke(InObject, Stack, nullptr);

		PROCESS_OUT()
	}
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call15(UObject* InObject, IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE,
                                       RETURN_BUFFER_SIGNATURE) const
{
	if (const auto FoundFunction = Function.Get())
	{
		const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

		FFrame Stack(InObject, FoundFunction, Params, nullptr, FoundFunction->ChildProperties);

		PROCESS_NATIVE_REFERENCE_IN()

		FoundFunction->Invoke(InObject, Stack, ReturnPropertyDescriptor->ContainerPtrToValuePtr<void>(Params));

		PROCESS_OUT()

		PROCESS_RETURN()
	}
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call16(UObject* InObject) const
{
	if (const auto FoundFunction = Function.Get())
	{
		const auto FunctionCallspace = InObject->GetFunctionCallspace(FoundFunction, nullptr);

		const bool bIsRemote = FunctionCallspace & FunctionCallspace::Remote;

		const bool bIsLocal = FunctionCallspace & FunctionCallspace::Local;

		if (bIsLocal)
		{
			InObject->UObject::ProcessEvent(FoundFunction, nullptr);
		}
		else if (bIsRemote)
		{
			InObject->CallRemoteFunction(FoundFunction, nullptr, nullptr, nullptr);
		}
	}
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call18(UObject* InObject, IN_BUFFER_SIGNATURE) const
{
	if (const auto FoundFunction = Function.Get())
	{
		const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

		PROCESS_SCRIPT_IN()

		const auto FunctionCallspace = InObject->GetFunctionCallspace(FoundFunction, nullptr);

		const bool bIsRemote = FunctionCallspace & FunctionCallspace::Remote;

		const bool bIsLocal = FunctionCallspace & FunctionCallspace::Local;

		if (bIsLocal)
		{
			InObject->UObject::ProcessEvent(FoundFunction, Params);
		}
		else if (bIsRemote)
		{
			InObject->CallRemoteFunction(FoundFunction, Params, nullptr, nullptr);
		}

		if (Params != nullptr)
		{
			BufferAllocator->Free(Params);
		}
	}
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call24(UObject* InObject) const
{
	if (const auto FoundFunction = Function.Get())
	{
		const auto FunctionCallspace = InObject->GetFunctionCallspace(FoundFunction, nullptr);

		const bool bIsRemote = FunctionCallspace & FunctionCallspace::Remote;

		const bool bIsLocal = FunctionCallspace & FunctionCallspace::Local;

		if (bIsLocal)
		{
			InObject->UObject::ProcessEvent(FoundFunction, nullptr);
		}
		else if (bIsRemote)
		{
			InObject->CallRemoteFunction(FoundFunction, nullptr, nullptr, nullptr);
		}
	}
}

template <auto ReturnType>
void FUnrealFunctionDescriptor::Call26(UObject* InObject, IN_BUFFER_SIGNATURE) const
{
	if (const auto FoundFunction = Function.Get())
	{
		const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

		PROCESS_SCRIPT_IN()

		const auto FunctionCallspace = InObject->GetFunctionCallspace(FoundFunction, nullptr);

		const bool bIsRemote = FunctionCallspace & FunctionCallspace::Remote;

		const bool bIsLocal = FunctionCallspace & FunctionCallspace::Local;

		if (bIsLocal)
		{
			InObject->UObject::ProcessEvent(FoundFunction, Params);
		}
		else if (bIsRemote)
		{
			InObject->CallRemoteFunction(FoundFunction, Params, nullptr, nullptr);
		}

		if (Params != nullptr)
		{
			BufferAllocator->Free(Params);
		}
	}
}
