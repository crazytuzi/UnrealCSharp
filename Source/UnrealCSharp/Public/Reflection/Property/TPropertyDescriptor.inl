#pragma once

#include "Reflection/Property/FPropertyDescriptor.h"
#include "Bridge/FTypeBridge.h"

template <typename T, auto IsPrimitive>
class TPropertyDescriptor : public FPropertyDescriptor
{
public:
	explicit TPropertyDescriptor(T* InProperty):
		Property(InProperty),
		Class(FTypeBridge::GetClass(InProperty))
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

	virtual auto GetClass() const -> FClassReflection* override
	{
		return Class;
	}

protected:
	T* Property{};

	FClassReflection* Class{};
};
