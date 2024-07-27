#pragma once

#include "Reflection/Property/FPropertyDescriptor.h"
#include "Bridge/FTypeBridge.h"
#include "mono/metadata/details/object-types.h"

template <typename T, auto IsPrimitive>
class TPropertyDescriptor : public FPropertyDescriptor
{
public:
	explicit TPropertyDescriptor(T* InProperty):
		Property(InProperty),
		Class(FTypeBridge::GetMonoClass(InProperty))
	{
	}

public:
	virtual auto GetProperty() const -> T* override
	{
		return Property;
	}

	virtual auto DestroyProperty() -> void override
	{
		if (Property != nullptr)
		{
			delete Property;

			Property = nullptr;
		}
	}

public:
	virtual auto IsPrimitiveProperty() const -> bool override
	{
		return IsPrimitive;
	}

protected:
	T* Property;

	MonoClass* Class;
};
