#include "Reflection/Property/ContainerProperty/FSetPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Container/FSetHelper.h"
#include "Domain/Script/IManagedTypes.h"

void FSetPropertyDescriptor::Get(void* Src, void** Dest, std::true_type) const
{
	*reinterpret_cast<IManagedObject*>(Dest) = NewWeakRef(Src, true);
}

void FSetPropertyDescriptor::Get(void* Src, void** Dest, std::false_type) const
{
	*reinterpret_cast<IManagedObject*>(Dest) = NewWeakRef(Src, false);
}

void FSetPropertyDescriptor::Get(void* Src, void* Dest) const
{
	*static_cast<IManagedObject*>(Dest) = NewRef(Src);
}

void FSetPropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcManagedHandle = *static_cast<IManagedHandle*>(Src);

	const auto SrcContainer = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(SrcManagedHandle);

	Property->InitializeValue(Dest);

	Property->CopyCompleteValue(Dest, SrcContainer->GetScriptSet());
}

IManagedObject FSetPropertyDescriptor::NewRef(void* InAddress) const
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
			OwnerManagedHandle, InAddress, SetHelper, Class, MANAGED_HANDLE_FROM_OBJECT(Object));
	}

	return IManagedHandleToIManagedObject(Object);
}

IManagedObject FSetPropertyDescriptor::NewWeakRef(void* InAddress, const bool bIsCopy) const
{
	const auto Object = Class->NewObject();

	const auto SetHelper = new FSetHelper(Property->ElementProp, InAddress,
	                                      bIsCopy, false);

	FCSharpEnvironment::GetEnvironment().AddContainerReference(SetHelper, Class, Object);

	return IManagedHandleToIManagedObject(Object);
}
