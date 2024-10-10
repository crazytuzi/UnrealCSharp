#pragma once

template <typename BoolConstant>
auto FPropertyDescriptor::Get(void* Src, void** Dest) const
{
	Get(Src, Dest, BoolConstant());
}

int32 FPropertyDescriptor::GetElementSize() const
{
	if (const auto Property = GetProperty())
	{
		return Property->ElementSize;
	}

	return 0;
}

EPropertyFlags FPropertyDescriptor::GetPropertyFlags() const
{
	if (const auto Property = GetProperty())
	{
		return Property->PropertyFlags;
	}

	return EPropertyFlags::CPF_None;
}

template <typename ValueType>
auto FPropertyDescriptor::ContainerPtrToValuePtr(void* ContainerPtr, const int32 ArrayIndex) const
{
	if (const auto Property = GetProperty())
	{
		return Property->ContainerPtrToValuePtr<ValueType>(ContainerPtr, ArrayIndex);
	}

	return decltype(std::declval<FProperty*>()->ContainerPtrToValuePtr<ValueType>(ContainerPtr, ArrayIndex)){};
}

FString FPropertyDescriptor::GetName() const
{
	if (const auto Property = GetProperty())
	{
		return Property->GetName();
	}

	return {};
}

void FPropertyDescriptor::InitializeValue_InContainer(void* Dest) const
{
	if (const auto Property = GetProperty())
	{
		return Property->InitializeValue_InContainer(Dest);
	}
}

int32 FPropertyDescriptor::GetSize() const
{
	if (const auto Property = GetProperty())
	{
		return Property->GetSize();
	}

	return 0;
}

int32 FPropertyDescriptor::GetMinAlignment() const
{
	if (const auto Property = GetProperty())
	{
		return Property->GetMinAlignment();
	}

	return 0;
}

uint32 FPropertyDescriptor::GetValueTypeHash(const void* Src) const
{
	if (const auto Property = GetProperty())
	{
		return Property->GetValueTypeHash(Src);
	}

	return 0;
}

bool FPropertyDescriptor::SameType(const FPropertyDescriptor* Other) const
{
	if (const auto Property = GetProperty(); Property != nullptr && Other != nullptr)
	{
		return Property->SameType(Other->GetProperty());
	}

	return false;
}
