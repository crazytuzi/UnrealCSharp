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
	virtual void Get(void* Src, void** Dest) const override
	{
		*Dest = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->Value_Box(Super::Class, Src));
	}

	virtual void DestroyProperty() override
	{
		if (Super::Property != nullptr)
		{
			delete Super::Property;

			Super::Property = nullptr;
		}
	}

	virtual void Get(void* Src, void* Dest) const override
	{
		if (Super::Property != nullptr)
		{
			Super::Property->CopySingleValue(Dest, Src);
		}
	}

	virtual void Set(void* Src, void* Dest) const override
	{
		if (Super::Property != nullptr)
		{
			Super::Property->InitializeValue(Dest);

			Super::Property->CopySingleValue(Dest, Src);
		}
	}
};
