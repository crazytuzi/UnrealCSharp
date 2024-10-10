#include "Reflection/Property/ContainerProperty/FSetPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Container/FSetHelper.h"

void FSetPropertyDescriptor::Get(void* Src, void** Dest, std::true_type) const
{
	*Dest = NewWeakRef(Src, true);
}

void FSetPropertyDescriptor::Get(void* Src, void** Dest, std::false_type) const
{
	*Dest = NewWeakRef(Src, false);
}

void FSetPropertyDescriptor::Get(void* Src, void* Dest) const
{
	*static_cast<void**>(Dest) = NewRef(Src);
}

void FSetPropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcGarbageCollectionHandle = *static_cast<FGarbageCollectionHandle*>(Src);

	const auto SrcContainer = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(
		SrcGarbageCollectionHandle);

	Property->InitializeValue(Dest);

	Property->CopyCompleteValue(Dest, SrcContainer->GetScriptSet());
}

MonoObject* FSetPropertyDescriptor::NewRef(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetContainerObject<FSetHelper>(InAddress);

	if (Object == nullptr)
	{
		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		const auto SetHelper = new FSetHelper(Property->ElementProp, InAddress,
		                                      false, false);

		const auto OwnerGarbageCollectionHandle = FCSharpEnvironment::GetEnvironment().GetGarbageCollectionHandle(
			InAddress, Property);

		FCSharpEnvironment::GetEnvironment().AddContainerReference(
			OwnerGarbageCollectionHandle, InAddress, SetHelper, Object);
	}

	return Object;
}

MonoObject* FSetPropertyDescriptor::NewWeakRef(void* InAddress, const bool bIsCopy) const
{
	const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

	const auto SetHelper = new FSetHelper(Property->ElementProp, InAddress,
	                                      bIsCopy, false);

	FCSharpEnvironment::GetEnvironment().AddContainerReference(SetHelper, Object);

	return Object;
}
