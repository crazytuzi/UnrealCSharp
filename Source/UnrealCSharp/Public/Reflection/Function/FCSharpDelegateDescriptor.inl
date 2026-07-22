#pragma once

#include "CoreMacro/BufferMacro.h"
#include "Macro/FunctionMacro.h"
#include "UEVersion.h"

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
#if UE_T_MULTICAST_SCRIPT_DELEGATE_PROCESS_DELEGATE
	InMulticastScriptDelegate->ProcessDelegate<UObject>(nullptr);
#else
	InMulticastScriptDelegate->ProcessMulticastDelegate<UObject>(nullptr);
#endif
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Broadcast2(const FMulticastScriptDelegate* InMulticastScriptDelegate,
                                           IN_BUFFER_SIGNATURE) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_IN()

#if UE_T_MULTICAST_SCRIPT_DELEGATE_PROCESS_DELEGATE
	InMulticastScriptDelegate->ProcessDelegate<UObject>(Params);
#else
	InMulticastScriptDelegate->ProcessMulticastDelegate<UObject>(Params);
#endif
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Broadcast4(const FMulticastScriptDelegate* InMulticastScriptDelegate,
                                           OUT_BUFFER_SIGNATURE) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

#if UE_T_MULTICAST_SCRIPT_DELEGATE_PROCESS_DELEGATE
	InMulticastScriptDelegate->ProcessDelegate<UObject>(Params);
#else
	InMulticastScriptDelegate->ProcessMulticastDelegate<UObject>(Params);
#endif

	PROCESS_OUT()
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Broadcast6(const FMulticastScriptDelegate* InMulticastScriptDelegate,
                                           IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_REFERENCE_IN()

#if UE_T_MULTICAST_SCRIPT_DELEGATE_PROCESS_DELEGATE
	InMulticastScriptDelegate->ProcessDelegate<UObject>(Params);
#else
	InMulticastScriptDelegate->ProcessMulticastDelegate<UObject>(Params);
#endif

	PROCESS_OUT()
}
