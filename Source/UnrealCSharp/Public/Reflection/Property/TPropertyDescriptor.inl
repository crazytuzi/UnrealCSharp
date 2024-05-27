#pragma once

#include "Reflection/Property/FPropertyDescriptor.h"
#include "Bridge/FTypeBridge.h"
#include "mono/metadata/details/object-types.h"

template <typename T, bool bIsPrimitiveProperty>
class TPropertyDescriptor : public FPropertyDescriptor
{
public:
	explicit TPropertyDescriptor(T* InProperty):
		Property(InProperty),
		Class(FTypeBridge::GetMonoClass(InProperty))
	{
	}

public:
	virtual T* GetProperty() const override
	{
		return Property;
	}

	virtual void DestroyProperty() override
	{
		if (Property != nullptr)
		{
			delete Property;

			Property = nullptr;
		}
	}

public:
	virtual bool IsPrimitiveProperty() const override
	{
		return bIsPrimitiveProperty;
	}

protected:
	T* Property;

	MonoClass* Class;
};
