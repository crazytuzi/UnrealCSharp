#pragma once

FProperty* FPropertyDescriptor::GetProperty() const
{
	return Property;
}

void FPropertyDescriptor::DestroyProperty()
{
	if (Property != nullptr)
	{
		delete Property;

		Property = nullptr;
	}
}

int32 FPropertyDescriptor::GetElementSize() const
{
	return Property != nullptr ? Property->ElementSize : 0;
}

EPropertyFlags FPropertyDescriptor::GetPropertyFlags() const
{
	return Property != nullptr ? Property->PropertyFlags : EPropertyFlags::CPF_None;
}

template <typename ValueType>
auto FPropertyDescriptor::ContainerPtrToValuePtr(void* ContainerPtr, const int32 ArrayIndex) const
{
	return Property != nullptr ? Property->ContainerPtrToValuePtr<ValueType>(ContainerPtr, ArrayIndex) : nullptr;
}

FString FPropertyDescriptor::GetName() const
{
	return Property != nullptr ? Property->GetName() : FString();
}

void FPropertyDescriptor::InitializeValue_InContainer(void* Dest) const
{
	if (Property != nullptr)
	{
		Property->InitializeValue_InContainer(Dest);
	}
}

int32 FPropertyDescriptor::GetSize() const
{
	return Property != nullptr ? Property->GetSize() : 0;
}

int32 FPropertyDescriptor::GetMinAlignment() const
{
	return Property != nullptr ? Property->GetMinAlignment() : 0;
}

uint32 FPropertyDescriptor::GetValueTypeHash(const void* Src) const
{
	return Property != nullptr ? Property->GetValueTypeHash(Src) : 0u;
}

bool FPropertyDescriptor::SameType(const FPropertyDescriptor* Other) const
{
	return Property != nullptr && Other != nullptr ? Property->SameType(Other->Property) : false;
}
