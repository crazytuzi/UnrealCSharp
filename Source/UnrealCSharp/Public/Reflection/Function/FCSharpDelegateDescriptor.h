#pragma once

#include "FFunctionDescriptor.h"
#include "mono/metadata/object.h"

class FCSharpDelegateDescriptor final : public FFunctionDescriptor
{
public:
	typedef FFunctionDescriptor Super;

public:
	explicit FCSharpDelegateDescriptor(UFunction* InFunction);

public:
	bool CallDelegate(const UObject* InObject, MonoMethod* InMethod, void* InParams);

	template <typename T>
	void Execute0(const FScriptDelegate* InScriptDelegate) const;

	template <typename T>
	auto Execute1(const FScriptDelegate* InScriptDelegate) const;

	template <typename T>
	void Execute2(const FScriptDelegate* InScriptDelegate, uint8* InBuffer) const;

	template <typename T>
	auto Execute3(const FScriptDelegate* InScriptDelegate, uint8* InBuffer) const;

	template <typename T>
	void Execute4(const FScriptDelegate* InScriptDelegate, MonoObject** OutValue) const;

	template <typename T>
	void Execute6(const FScriptDelegate* InScriptDelegate, MonoObject** OutValue, uint8* InBuffer) const;

	template <typename T>
	auto Execute7(const FScriptDelegate* InScriptDelegate, MonoObject** OutValue, uint8* InBuffer) const;

	template <typename T>
	void Broadcast0(const FMulticastScriptDelegate* InMulticastScriptDelegate) const;

	template <typename T>
	void Broadcast2(const FMulticastScriptDelegate* InMulticastScriptDelegate, uint8* InBuffer) const;

	template <typename T>
	void Broadcast4(const FMulticastScriptDelegate* InMulticastScriptDelegate, MonoObject** OutValue) const;

	template <typename T>
	void Broadcast6(const FMulticastScriptDelegate* InMulticastScriptDelegate, MonoObject** OutValue,
	                uint8* InBuffer) const;
};

#include "FCSharpDelegateDescriptor.inl"
