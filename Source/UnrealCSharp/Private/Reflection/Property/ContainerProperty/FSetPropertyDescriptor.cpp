#include "Reflection/Property/ContainerProperty/FSetPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Container/FSetHelper.h"
#include "Template/TGetArrayLength.inl"
#include "Bridge/FTypeBridge.h"

FSetPropertyDescriptor::FSetPropertyDescriptor(FProperty* InProperty):
	FContainerPropertyDescriptor(InProperty),
	Class(nullptr),
	Type(nullptr)
{
	Class = FTypeBridge::GetMonoClass(SetProperty);

	const auto FoundMonoClass = FTypeBridge::GetMonoClass(SetProperty->ElementProp);

	const auto FoundMonoType = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_Get_Type(FoundMonoClass);

	Type = FCSharpEnvironment::GetEnvironment().GetDomain()->Type_Get_Object(FoundMonoType);
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
	auto Object = FCSharpEnvironment::GetEnvironment().GetContainerObject(InAddress);

	if (Object == nullptr)
	{
		auto InParams = static_cast<void*>(Type);

		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			Class, TGetArrayLength(InParams), &InParams);

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
	auto InParams = static_cast<void*>(Type);

	const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
		Class, TGetArrayLength(InParams), &InParams);

	const auto SetHelper = new FSetHelper(SetProperty->ElementProp, InAddress);

	FCSharpEnvironment::GetEnvironment().AddContainerReference(InAddress, SetHelper, Object);

	return Object;
}
