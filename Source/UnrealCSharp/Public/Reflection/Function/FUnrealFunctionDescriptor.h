#pragma once

#include "FFunctionDescriptor.h"
#include "mono/metadata/object.h"

class FUnrealFunctionDescriptor final : public FFunctionDescriptor
{
public:
	typedef FFunctionDescriptor Super;

public:
	explicit FUnrealFunctionDescriptor(UFunction* InFunction);

public:
	template <typename T>
	void Call0(UObject* InObject) const;

	template <typename T>
	auto Call1(UObject* InObject) const;

	template <typename T>
	void Call2(UObject* InObject, uint8* InBuffer) const;

	template <typename T>
	auto Call3(UObject* InObject, uint8* InBuffer) const;

	template <typename T>
	void Call4(UObject* InObject, MonoObject** OutValue) const;

	template <typename T>
	void Call6(UObject* InObject, MonoObject** OutValue, uint8* InBuffer) const;

	template <typename T>
	auto Call7(UObject* InObject, MonoObject** OutValue, uint8* InBuffer) const;

	template <typename T>
	void Call8(UObject* InObject) const;

	template <typename T>
	auto Call9(UObject* InObject) const;

	template <typename T>
	void Call10(UObject* InObject, uint8* InBuffer) const;

	template <typename T>
	auto Call11(UObject* InObject, uint8* InBuffer) const;

	template <typename T>
	void Call14(UObject* InObject, MonoObject** OutValue, uint8* InBuffer) const;

	template <typename T>
	auto Call15(UObject* InObject, MonoObject** OutValue, uint8* InBuffer) const;

	template <typename T>
	void Call24(UObject* InObject) const;

	template <typename T>
	void Call26(UObject* InObject, uint8* InBuffer) const;
};

#include "FUnrealFunctionDescriptor.inl"
