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

template <typename ValueType>
auto FPropertyDescriptor::ContainerPtrToValuePtr(void* ContainerPtr, const int32 ArrayIndex) const
{
	return Property->ContainerPtrToValuePtr<ValueType>(ContainerPtr, ArrayIndex);
}

void FPropertyDescriptor::DestroyValue(void* Dest) const
{
	Property->DestroyValue(Dest);
}

void FPropertyDescriptor::InitializeValue_InContainer(void* Dest) const
{
	Property->InitializeValue_InContainer(Dest);
}

int32 FPropertyDescriptor::GetSize() const
{
	return Property->GetSize();
}

uint32 FPropertyDescriptor::GetValueTypeHash(const void* Src) const
{
	return Property->GetValueTypeHash(Src);
}
