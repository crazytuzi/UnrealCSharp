#pragma once

#include "Macro/FunctionMacro.h"

template <auto ReturnType>
void FCSharpDelegateDescriptor::Execute0(const FScriptDelegate* InScriptDelegate) const
{
	InScriptDelegate->ProcessDelegate<UObject>(nullptr);
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Execute1(const FScriptDelegate* InScriptDelegate, uint8* ReturnBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	InScriptDelegate->ProcessDelegate<UObject>(Params);

	PROCESS_RETURN()
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Execute2(const FScriptDelegate* InScriptDelegate, uint8* InBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_IN()

	InScriptDelegate->ProcessDelegate<UObject>(Params);
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Execute3(const FScriptDelegate* InScriptDelegate, uint8* InBuffer,
                                         uint8* ReturnBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_IN()

	InScriptDelegate->ProcessDelegate<UObject>(Params);

	PROCESS_RETURN()
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Execute4(const FScriptDelegate* InScriptDelegate, uint8* OutBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	InScriptDelegate->ProcessDelegate<UObject>(Params);

	PROCESS_OUT()
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Execute6(const FScriptDelegate* InScriptDelegate, uint8* InBuffer,
                                         uint8* OutBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_REFERENCE_IN()

	InScriptDelegate->ProcessDelegate<UObject>(Params);

	PROCESS_OUT()
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Execute7(const FScriptDelegate* InScriptDelegate, uint8* InBuffer,
                                         uint8* OutBuffer, uint8* ReturnBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_REFERENCE_IN()

	InScriptDelegate->ProcessDelegate<UObject>(Params);

	PROCESS_OUT()

	PROCESS_RETURN()
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Broadcast0(const FMulticastScriptDelegate* InMulticastScriptDelegate) const
{
	InMulticastScriptDelegate->ProcessMulticastDelegate<UObject>(nullptr);
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Broadcast2(const FMulticastScriptDelegate* InMulticastScriptDelegate,
                                           uint8* InBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_IN()

	InMulticastScriptDelegate->ProcessMulticastDelegate<UObject>(Params);
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Broadcast4(const FMulticastScriptDelegate* InMulticastScriptDelegate,
                                           uint8* OutBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	InMulticastScriptDelegate->ProcessMulticastDelegate<UObject>(Params);

	PROCESS_OUT()
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Broadcast6(const FMulticastScriptDelegate* InMulticastScriptDelegate,
                                           uint8* InBuffer, uint8* OutBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_REFERENCE_IN()

	InMulticastScriptDelegate->ProcessMulticastDelegate<UObject>(Params);

	PROCESS_OUT()
}
