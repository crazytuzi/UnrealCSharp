#pragma once

#include "CoreMacro/BufferMacro.h"
#include "FFunctionDescriptor.h"
#include "Common/EFunctionReturnType.h"
#include "mono/metadata/object.h"

class FCSharpDelegateDescriptor final : public FFunctionDescriptor
{
public:
	typedef FFunctionDescriptor Super;

public:
	explicit FCSharpDelegateDescriptor(UFunction* InFunction);

public:
	bool CallDelegate(const UObject* InObject, MonoMethod* InMethod, void* InParams);

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute0(const FScriptDelegate* InScriptDelegate) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute1(const FScriptDelegate* InScriptDelegate, RETURN_BUFFER_SIGNATURE) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute2(const FScriptDelegate* InScriptDelegate, IN_BUFFER_SIGNATURE) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute3(const FScriptDelegate* InScriptDelegate, IN_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute4(const FScriptDelegate* InScriptDelegate, OUT_BUFFER_SIGNATURE) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute6(const FScriptDelegate* InScriptDelegate, IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute7(const FScriptDelegate* InScriptDelegate, IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE,
	              RETURN_BUFFER_SIGNATURE) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Broadcast0(const FMulticastScriptDelegate* InMulticastScriptDelegate) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Broadcast2(const FMulticastScriptDelegate* InMulticastScriptDelegate, IN_BUFFER_SIGNATURE) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Broadcast4(const FMulticastScriptDelegate* InMulticastScriptDelegate, OUT_BUFFER_SIGNATURE) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Broadcast6(const FMulticastScriptDelegate* InMulticastScriptDelegate, IN_BUFFER_SIGNATURE,
	                OUT_BUFFER_SIGNATURE) const;
};

#include "FCSharpDelegateDescriptor.inl"
