#include "Reflection/Property/ContainerProperty/FMapPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Container/FMapHelper.h"

void FMapPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FMember) const
{
	*reinterpret_cast<IManagedHandle*>(Dest) = NewWeakRef(Src, false);
}

void FMapPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FReturn) const
{
	*reinterpret_cast<IManagedHandle*>(Dest) = NewWeakRef(Src, true);
}

void FMapPropertyDescriptor::Get(void* Src, void* Dest) const
{
	*reinterpret_cast<IManagedHandle*>(Dest) = NewRef(Src);
}

void FMapPropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcManagedHandle = *static_cast<IManagedHandle*>(Src);

	const auto SrcContainer = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(SrcManagedHandle);

	Property->InitializeValue(Dest);

	Property->CopyCompleteValue(Dest, SrcContainer->GetScriptMap());
}

IManagedHandle FMapPropertyDescriptor::NewRef(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetContainerObject<FMapHelper>(InAddress);

	if (!IManagedHandleIsValid(Object))
	{
		Object = Class->NewObject();

		const auto MapHelper = new FMapHelper(Property->KeyProp, Property->ValueProp, InAddress,
		                                      false, false);

		const auto OwnerManagedHandle = FCSharpEnvironment::GetEnvironment().GeManagedHandle(
			InAddress, Property);

		FCSharpEnvironment::GetEnvironment().AddContainerReference(
			OwnerManagedHandle, InAddress, MapHelper, Class, Object);
	}

	return Object;
}

IManagedHandle FMapPropertyDescriptor::NewWeakRef(void* InAddress, const bool bIsCopy) const
{
	const auto Object = Class->NewObject();

	const auto MapHelper = new FMapHelper(Property->KeyProp, Property->ValueProp, InAddress,
	                                      bIsCopy, false);

	FCSharpEnvironment::GetEnvironment().AddContainerReference(MapHelper, Class, Object);

	return Object;
}
