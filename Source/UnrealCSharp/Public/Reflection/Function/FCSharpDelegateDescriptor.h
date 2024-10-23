﻿#pragma once

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
	bool CallDelegate(const UObject* InObject, MonoObject* InDelegate, void* InParams);

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute0(const FScriptDelegate* InScriptDelegate) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute1(const FScriptDelegate* InScriptDelegate, uint8* ReturnBuffer) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute2(const FScriptDelegate* InScriptDelegate, uint8* InBuffer) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute3(const FScriptDelegate* InScriptDelegate, uint8* InBuffer, uint8* ReturnBuffer) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute4(const FScriptDelegate* InScriptDelegate, uint8* OutBuffer) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute6(const FScriptDelegate* InScriptDelegate, uint8* InBuffer, uint8* OutBuffer) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Execute7(const FScriptDelegate* InScriptDelegate, uint8* InBuffer, uint8* OutBuffer,
	              uint8* ReturnBuffer) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Broadcast0(const FMulticastScriptDelegate* InMulticastScriptDelegate) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Broadcast2(const FMulticastScriptDelegate* InMulticastScriptDelegate, uint8* InBuffer) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Broadcast4(const FMulticastScriptDelegate* InMulticastScriptDelegate, uint8* OutBuffer) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Broadcast6(const FMulticastScriptDelegate* InMulticastScriptDelegate, uint8* InBuffer,
	                uint8* OutBuffer) const;
};

#include "FCSharpDelegateDescriptor.inl"
