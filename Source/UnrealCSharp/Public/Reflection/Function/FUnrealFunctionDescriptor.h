#pragma once

#include "FFunctionDescriptor.h"
#include "Common/EFunctionReturnType.h"

class FUnrealFunctionDescriptor final : public FFunctionDescriptor
{
public:
	typedef FFunctionDescriptor Super;

public:
	explicit FUnrealFunctionDescriptor(UFunction* InFunction);

public:
	template <auto ReturnType = EFunctionReturnType::Void>
	void Call0(UObject* InObject) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call1(UObject* InObject, uint8* ReturnBuffer) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call2(UObject* InObject, uint8* InBuffer) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call3(UObject* InObject, uint8* InBuffer, uint8* ReturnBuffer) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call4(UObject* InObject, uint8* OutBuffer) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call6(UObject* InObject, uint8* InBuffer, uint8* OutBuffer) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call7(UObject* InObject, uint8* InBuffer, uint8* OutBuffer, uint8* ReturnBuffer) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call8(UObject* InObject) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call9(UObject* InObject, uint8* ReturnBuffer) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call10(UObject* InObject, uint8* InBuffer) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call11(UObject* InObject, uint8* InBuffer, uint8* ReturnBuffer) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call14(UObject* InObject, uint8* InBuffer, uint8* OutBuffer) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call15(UObject* InObject, uint8* InBuffer, uint8* OutBuffer, uint8* ReturnBuffer) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call16(UObject* InObject) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call18(UObject* InObject, uint8* InBuffer) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call24(UObject* InObject) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call26(UObject* InObject, uint8* InBuffer) const;
};

#include "FUnrealFunctionDescriptor.inl"
