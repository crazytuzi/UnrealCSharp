#include "Reflection/Property/ContainerProperty/FSetPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Container/FSetHelper.h"

void FSetPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FMember) const
{
	*reinterpret_cast<IManagedHandle*>(Dest) = NewWeakRef(Src, false);
}

void FSetPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FReturn) const
{
	*reinterpret_cast<IManagedHandle*>(Dest) = NewWeakRef(Src, true);
}

void FSetPropertyDescriptor::Get(void* Src, void* Dest) const
{
	*reinterpret_cast<IManagedHandle*>(Dest) = NewRef(Src);
}

void FSetPropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcManagedHandle = *static_cast<IManagedHandle*>(Src);

	const auto SrcContainer = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(SrcManagedHandle);

	Property->InitializeValue(Dest);

	Property->CopyCompleteValue(Dest, SrcContainer->GetScriptSet());
}

IManagedHandle FSetPropertyDescriptor::NewRef(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetContainerObject<FSetHelper>(InAddress);

	if (!IManagedHandleIsValid(Object))
	{
		Object = Class->NewObject();

		const auto SetHelper = new FSetHelper(Property->ElementProp, InAddress,
		                                      false, false);

		const auto OwnerManagedHandle = FCSharpEnvironment::GetEnvironment().GeManagedHandle(
			InAddress, Property);

		FCSharpEnvironment::GetEnvironment().AddContainerReference(
			OwnerManagedHandle, InAddress, SetHelper, Class, Object);
	}

	return Object;
}

IManagedHandle FSetPropertyDescriptor::NewWeakRef(void* InAddress, const bool bIsCopy) const
{
	const auto Object = Class->NewObject();

	const auto SetHelper = new FSetHelper(Property->ElementProp, InAddress,
	                                      bIsCopy, false);

	FCSharpEnvironment::GetEnvironment().AddContainerReference(SetHelper, Class, Object);

	return Object;
}
