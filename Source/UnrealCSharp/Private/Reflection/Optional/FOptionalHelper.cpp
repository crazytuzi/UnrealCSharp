#include "Reflection/Optional/FOptionalHelper.h"
#if UE_F_OPTIONAL_PROPERTY
#include "UObject/PropertyOptional.h"

FOptionalHelper::FOptionalHelper(FOptionalProperty* InOptionalProperty, void* InData,
                                 const bool InbNeedFreeData, const bool InbNeedFreeProperty):
	OptionalProperty(InOptionalProperty),
	ValuePropertyDescriptor(nullptr),
	Data(nullptr),
	bNeedFreeData(InbNeedFreeData),
	bNeedFreeProperty(InbNeedFreeProperty)
{
	ValuePropertyDescriptor = FPropertyDescriptor::Factory(InOptionalProperty->GetValueProperty());

	if (InData != nullptr)
	{
		Data = InData;
	}
	else
	{
		Data = FMemory::Malloc(ValuePropertyDescriptor->GetSize(), ValuePropertyDescriptor->GetMinAlignment());

		InOptionalProperty->InitializeValueInternal(Data);
	}
}

FOptionalHelper::~FOptionalHelper()
{
	Deinitialize();
}

void FOptionalHelper::Initialize()
{
}

void FOptionalHelper::Deinitialize()
{
	if (bNeedFreeData && Data != nullptr)
	{
		FMemory::Free(Data);

		Data = nullptr;
	}

	if (bNeedFreeProperty && ValuePropertyDescriptor != nullptr && OptionalProperty != nullptr)
	{
		delete ValuePropertyDescriptor;

		ValuePropertyDescriptor = nullptr;

		delete OptionalProperty;

		OptionalProperty = nullptr;
	}
}

bool FOptionalHelper::Identical(const FOptionalHelper* InA, const FOptionalHelper* InB)
{
	if (InA == nullptr || InB == nullptr)
	{
		return false;
	}

	if (!InA->GetValuePropertyDescriptor()->SameType(InB->GetValuePropertyDescriptor()))
	{
		return false;
	}

	return InA->OptionalProperty->Identical(InA->Data, InB->Data, 0);
}

void FOptionalHelper::Reset() const
{
	OptionalProperty->MarkUnset(Data);
}

bool FOptionalHelper::IsSet() const
{
	return OptionalProperty->IsSet(Data);
}

void* FOptionalHelper::Get() const
{
	return OptionalProperty->GetValuePointerForReadOrReplace(Data);
}

void FOptionalHelper::Set(void* InValue) const
{
	OptionalProperty->MarkSetAndGetInitializedValuePointerToReplace(Data);

	ValuePropertyDescriptor->Set(InValue, Data);
}

FPropertyDescriptor* FOptionalHelper::GetValuePropertyDescriptor() const
{
	return ValuePropertyDescriptor;
}

void* FOptionalHelper::GetData() const
{
	return Data;
}
#endif
