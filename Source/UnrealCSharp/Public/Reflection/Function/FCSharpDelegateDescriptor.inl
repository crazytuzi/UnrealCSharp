#pragma once

#include "CoreMacro/BufferMacro.h"
#include "Macro/FunctionMacro.h"

template <auto ReturnType>
void FCSharpDelegateDescriptor::Execute0(const FScriptDelegate* InScriptDelegate) const
{
	InScriptDelegate->ProcessDelegate<UObject>(nullptr);
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Execute1(const FScriptDelegate* InScriptDelegate, RETURN_BUFFER_SIGNATURE) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	InScriptDelegate->ProcessDelegate<UObject>(Params);

	PROCESS_RETURN()
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Execute2(const FScriptDelegate* InScriptDelegate, IN_BUFFER_SIGNATURE) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_IN()

	InScriptDelegate->ProcessDelegate<UObject>(Params);
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Execute3(const FScriptDelegate* InScriptDelegate, IN_BUFFER_SIGNATURE,
                                         RETURN_BUFFER_SIGNATURE) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_IN()

	InScriptDelegate->ProcessDelegate<UObject>(Params);

	PROCESS_RETURN()
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Execute4(const FScriptDelegate* InScriptDelegate, OUT_BUFFER_SIGNATURE) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	InScriptDelegate->ProcessDelegate<UObject>(Params);

	PROCESS_OUT()
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Execute6(const FScriptDelegate* InScriptDelegate, IN_BUFFER_SIGNATURE,
                                         OUT_BUFFER_SIGNATURE) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_REFERENCE_IN()

	InScriptDelegate->ProcessDelegate<UObject>(Params);

	PROCESS_OUT()
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Execute7(const FScriptDelegate* InScriptDelegate, IN_BUFFER_SIGNATURE,
                                         OUT_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE) const
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
                                           IN_BUFFER_SIGNATURE) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_IN()

	InMulticastScriptDelegate->ProcessMulticastDelegate<UObject>(Params);
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Broadcast4(const FMulticastScriptDelegate* InMulticastScriptDelegate,
                                           OUT_BUFFER_SIGNATURE) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	InMulticastScriptDelegate->ProcessMulticastDelegate<UObject>(Params);

	PROCESS_OUT()
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Broadcast6(const FMulticastScriptDelegate* InMulticastScriptDelegate,
                                           IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_REFERENCE_IN()

	InMulticastScriptDelegate->ProcessMulticastDelegate<UObject>(Params);

	PROCESS_OUT()
}
