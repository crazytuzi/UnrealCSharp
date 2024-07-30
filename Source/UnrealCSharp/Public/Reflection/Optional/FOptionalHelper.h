#pragma once

#include "Reflection/Property/FPropertyDescriptor.h"
#include "UEVersion.h"

#if UE_F_OPTIONAL_PROPERTY
class UNREALCSHARP_API FOptionalHelper
{
public:
	explicit FOptionalHelper(FOptionalProperty* InOptionalProperty, void* InData,
	                         bool InbNeedFreeData, bool InbNeedFreeProperty);

	~FOptionalHelper();

public:
	void Initialize();

	void Deinitialize();

public:
	static bool Identical(const FOptionalHelper* InA, const FOptionalHelper* InB);

	void Reset() const;

	bool IsSet() const;

	void* Get() const;

	void Set(void* InValue) const;

	FPropertyDescriptor* GetValuePropertyDescriptor() const;

	void* GetData() const;

private:
	FOptionalProperty* OptionalProperty;

	FPropertyDescriptor* ValuePropertyDescriptor;

	void* Data;

	bool bNeedFreeData;

	bool bNeedFreeProperty;
};
#endif
