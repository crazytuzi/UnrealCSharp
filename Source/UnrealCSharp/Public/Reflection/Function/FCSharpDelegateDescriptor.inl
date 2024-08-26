#pragma once

#include "CoreMacro/MonoMacro.h"
#include "Domain/FMonoDomain.h"
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

	PROCESS_RETURN(ReturnBuffer, Params)
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Execute2(const FScriptDelegate* InScriptDelegate, uint8* InBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_IN(InBuffer, Params)

	InScriptDelegate->ProcessDelegate<UObject>(Params);
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Execute3(const FScriptDelegate* InScriptDelegate, uint8* InBuffer,
                                         uint8* ReturnBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_IN(InBuffer, Params)

	InScriptDelegate->ProcessDelegate<UObject>(Params);

	PROCESS_RETURN(ReturnBuffer, Params)
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Execute4(const FScriptDelegate* InScriptDelegate, MonoObject** OutValue) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	InScriptDelegate->ProcessDelegate<UObject>(Params);

	PROCESS_OUT(OutValue, Params)
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Execute6(const FScriptDelegate* InScriptDelegate, MonoObject** OutValue,
                                         uint8* InBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_REFERENCE_IN(InBuffer, Params)

	InScriptDelegate->ProcessDelegate<UObject>(Params);

	PROCESS_OUT(OutValue, Params)
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Execute7(const FScriptDelegate* InScriptDelegate, MonoObject** OutValue,
                                         uint8* InBuffer, uint8* ReturnBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_REFERENCE_IN(InBuffer, Params)

	InScriptDelegate->ProcessDelegate<UObject>(Params);

	PROCESS_OUT(OutValue, Params);

	PROCESS_RETURN(ReturnBuffer, Params)
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

	PROCESS_SCRIPT_IN(InBuffer, Params)

	InMulticastScriptDelegate->ProcessMulticastDelegate<UObject>(Params);
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Broadcast4(const FMulticastScriptDelegate* InMulticastScriptDelegate,
                                           MonoObject** OutValue) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	InMulticastScriptDelegate->ProcessMulticastDelegate<UObject>(Params);

	PROCESS_OUT(OutValue, Params)
}

template <auto ReturnType>
void FCSharpDelegateDescriptor::Broadcast6(const FMulticastScriptDelegate* InMulticastScriptDelegate,
                                           MonoObject** OutValue, uint8* InBuffer) const
{
	const auto Params = BufferAllocator.IsValid() ? BufferAllocator->Malloc() : nullptr;

	PROCESS_SCRIPT_REFERENCE_IN(InBuffer, Params)

	InMulticastScriptDelegate->ProcessMulticastDelegate<UObject>(Params);

	PROCESS_OUT(OutValue, Params)
}
