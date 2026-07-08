#include "Reflection/Property/ContainerProperty/FArrayPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Container/FArrayHelper.h"

void FArrayPropertyDescriptor::Get(void* Src, void** Dest, std::true_type) const
{
	*reinterpret_cast<IManagedHandle*>(Dest) = NewWeakRef(Src, true);
}

void FArrayPropertyDescriptor::Get(void* Src, void** Dest, std::false_type) const
{
	*reinterpret_cast<IManagedHandle*>(Dest) = NewWeakRef(Src, false);
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

	Property->CopyCompleteValue(Dest, SrcContainer->GetScriptArray());
}

IManagedHandle FArrayPropertyDescriptor::NewRef(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetContainerObject<FArrayHelper>(InAddress);

	if (!IManagedHandleIsValid(Object))
	{
		Object = Class->NewObject();

		const auto ArrayHelper = new FArrayHelper(Property->Inner, InAddress,
		                                          false, false);

		const auto OwnerManagedHandle = FCSharpEnvironment::GetEnvironment().GeManagedHandle(
			InAddress, Property);

		FCSharpEnvironment::GetEnvironment().AddContainerReference(
			OwnerManagedHandle, InAddress, ArrayHelper, Class, Object);
	}

	return Object;
}

IManagedHandle FArrayPropertyDescriptor::NewWeakRef(void* InAddress, const bool bIsCopy) const
{
	const auto Object = Class->NewObject();

	const auto ArrayHelper = new FArrayHelper(Property->Inner, InAddress,
	                                          bIsCopy, false);

	FCSharpEnvironment::GetEnvironment().AddContainerReference(ArrayHelper, Class, Object);

	return Object;
}
