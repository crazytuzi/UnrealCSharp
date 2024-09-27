#pragma once

#include "TPropertyDescriptor.inl"
#include "Environment/FCSharpEnvironment.h"

template <typename T>
class TPrimitivePropertyDescriptor : public TPropertyDescriptor<T, true>
{
public:
	using TPropertyDescriptor<T, true>::TPropertyDescriptor;

	using Super = TPropertyDescriptor<T, true>;

public:
	virtual auto Get(void* Src, void** Dest) const -> void override
	{
		Super::Property->CopySingleValue(Dest, Src);
	}

	virtual auto Get(void* Src, void** Dest, std::true_type) const -> void override
	{
		*Dest = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->Value_Box(Super::Class, Src));
	}

	virtual auto Get(void* Src, void** Dest, std::false_type) const -> void override
	{
		*Dest = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->Value_Box(Super::Class, Src));
	}

	virtual auto Get(void* Src, void* Dest) const -> void override
	{
		Super::Property->CopySingleValue(Dest, Src);
	}

	virtual auto Set(void* Src, void* Dest) const -> void override
	{
		Super::Property->InitializeValue(Dest);

		Super::Property->CopySingleValue(Dest, Src);
	}

	virtual auto CopyValue(const void* InAddress) const -> void* override
	{
		return const_cast<void*>(InAddress);
	}

	virtual auto DestroyProperty() -> void override
	{
		if (Super::Property != nullptr)
		{
			delete Super::Property;

			Super::Property = nullptr;
		}
	}
};
