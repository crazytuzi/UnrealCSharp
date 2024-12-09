#pragma once

#include "CoreMacro/BufferMacro.h"
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
	void Call1(UObject* InObject, RETURN_BUFFER_SIGNATURE) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call2(UObject* InObject, IN_BUFFER_SIGNATURE) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call3(UObject* InObject, IN_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call4(UObject* InObject, OUT_BUFFER_SIGNATURE) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call6(UObject* InObject, IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call7(UObject* InObject, IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call8(UObject* InObject) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call9(UObject* InObject, RETURN_BUFFER_SIGNATURE) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call10(UObject* InObject, IN_BUFFER_SIGNATURE) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call11(UObject* InObject, IN_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call14(UObject* InObject, IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call15(UObject* InObject, IN_BUFFER_SIGNATURE, OUT_BUFFER_SIGNATURE, RETURN_BUFFER_SIGNATURE) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call16(UObject* InObject) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call18(UObject* InObject, IN_BUFFER_SIGNATURE) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call24(UObject* InObject) const;

	template <auto ReturnType = EFunctionReturnType::Void>
	void Call26(UObject* InObject, IN_BUFFER_SIGNATURE) const;
};

#include "FUnrealFunctionDescriptor.inl"
