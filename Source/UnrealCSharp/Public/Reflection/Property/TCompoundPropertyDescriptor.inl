#pragma once

#include "TPropertyDescriptor.inl"

template <typename T>
class TCompoundPropertyDescriptor : public TPropertyDescriptor<T, false>
{
public:
	using TPropertyDescriptor<T, false>::TPropertyDescriptor;

	using Super = TPropertyDescriptor<T, false>;

public:
	virtual auto Get(void* Src, void** Dest, bool bIsCopy) const -> void override
	{
	}

	virtual auto Get(void* Src, void* Dest) const -> void override
	{
		Get(Src, static_cast<void**>(Dest), false);
	}

	virtual auto CopyValue(const void* InAddress) const -> void* override
	{
		const auto Value = static_cast<void*>(static_cast<uint8*>(FMemory::Malloc(Super::Property->ElementSize)));

		Super::Property->InitializeValue(Value);

		Super::Property->CopySingleValue(Value, InAddress);

		return Value;
	}
};
