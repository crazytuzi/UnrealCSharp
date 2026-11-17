#include "Reflection/Property/ContainerProperty/FArrayPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Container/FArrayHelper.h"

void FArrayPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FMember) const
{
	*reinterpret_cast<IManagedHandle*>(Dest) = NewWeakRef(Src, false);
}

void FArrayPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FReturn) const
{
	*reinterpret_cast<IManagedHandle*>(Dest) = NewWeakRef(Src, true);
}

void FArrayPropertyDescriptor::Get(void* Src, void* Dest) const
{
	*reinterpret_cast<IManagedHandle*>(Dest) = NewRef(Src);
}

void FArrayPropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcManagedHandle = *static_cast<IManagedHandle*>(Src);

	const auto SrcContainer = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(SrcManagedHandle);

	Property->InitializeValue(Dest);

	if (SrcContainer != nullptr)
	{
		Property->CopyCompleteValue(Dest, SrcContainer->GetScriptArray());
	}
}

bool FArrayPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (const auto ArrayHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
		*static_cast<IManagedHandle*>(const_cast<void*>(B))))
	{
		return Property->Identical(A, ArrayHelper->GetScriptArray(), PortFlags);
	}

	return false;
}

IManagedHandle FArrayPropertyDescriptor::NewRef(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetContainerObject<FArrayHelper>(InAddress);

	if (!IManagedHandleIsValid(Object))
	{
		if (Class != nullptr)
		{
			Object = Class->NewObject(true);

			const auto ArrayHelper = new FArrayHelper(Property->Inner, InAddress,
			                                          false, false);

			const auto OwnerManagedHandle = FCSharpEnvironment::GetEnvironment().GeManagedHandle(
				InAddress, Property);

			FCSharpEnvironment::GetEnvironment().AddContainerReference(
				OwnerManagedHandle, InAddress, ArrayHelper, Class, Object);
		}
	}

	return Object;
}

IManagedHandle FArrayPropertyDescriptor::NewWeakRef(void* InAddress, const bool bIsCopy) const
{
	auto Object = InvalidManagedHandle;

	if (Class != nullptr)
	{
		Object = Class->NewObject(true);

		const auto ArrayHelper = new FArrayHelper(Property->Inner, InAddress,
		                                          bIsCopy, false);

		FCSharpEnvironment::GetEnvironment().AddContainerReference(ArrayHelper, Class, Object);
	}

	return Object;
}
