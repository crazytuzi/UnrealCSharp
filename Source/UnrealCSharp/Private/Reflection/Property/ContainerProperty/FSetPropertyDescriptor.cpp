#include "Reflection/Property/ContainerProperty/FSetPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Container/FSetHelper.h"
#include "Bridge/FTypeBridge.h"

FSetPropertyDescriptor::FSetPropertyDescriptor(FProperty* InProperty):
	FContainerPropertyDescriptor(InProperty),
	Class(nullptr)
{
	Class = FTypeBridge::GetMonoClass(SetProperty);
}

void FSetPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (SetProperty != nullptr)
	{
		*Dest = NewWeakRef(Src);
	}
}

void FSetPropertyDescriptor::Get(void* Src, void* Dest) const
{
	if (SetProperty != nullptr)
	{
		*static_cast<void**>(Dest) = NewRef(Src);
	}
}

void FSetPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (SetProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcContainer = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(SrcMonoObject);

		SetProperty->InitializeValue(Dest);

		SetProperty->CopyCompleteValue(Dest, SrcContainer->GetScriptSet());
	}
}

MonoObject* FSetPropertyDescriptor::NewRef(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetContainerObject<FSetHelper>(InAddress);

	if (Object == nullptr)
	{
		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		const auto SetHelper = new FSetHelper(SetProperty->ElementProp, InAddress);

		const auto OwnerGarbageCollectionHandle = FCSharpEnvironment::GetEnvironment().GetGarbageCollectionHandle(
			InAddress, SetProperty);

		FCSharpEnvironment::GetEnvironment().AddContainerReference(OwnerGarbageCollectionHandle, InAddress, SetHelper,
		                                                           Object);
	}

	return Object;
}

MonoObject* FSetPropertyDescriptor::NewWeakRef(void* InAddress) const
{
	const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

	const auto SetHelper = new FSetHelper(SetProperty->ElementProp, InAddress);

	FCSharpEnvironment::GetEnvironment().AddContainerReference(SetHelper, Object);

	return Object;
}
