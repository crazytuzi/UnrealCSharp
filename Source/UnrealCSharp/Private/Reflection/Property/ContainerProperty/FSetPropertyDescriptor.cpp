#include "Reflection/Property/ContainerProperty/FSetPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Container/FSetHelper.h"
#include "Template/TGetArrayLength.inl"
#include "Bridge/FTypeBridge.h"

void FSetPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (SetProperty != nullptr)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetContainerObject(Src);

		if (SrcMonoObject == nullptr)
		{
			SrcMonoObject = Object_New(Src);
		}

		*Dest = SrcMonoObject;
	}
}

void FSetPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (SetProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcContainer = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(SrcMonoObject);

		(void)FCSharpEnvironment::GetEnvironment().RemoveContainerReference(Dest);

		SetProperty->InitializeValue(Dest);

		SetProperty->CopyCompleteValue(Dest, SrcContainer->GetScriptSet());

		Object_New(Dest);
	}
}

MonoObject* FSetPropertyDescriptor::Object_New(void* InAddress) const
{
	const auto GenericClassMonoClass = FTypeBridge::GetMonoClass(SetProperty);

	const auto FoundMonoClass = FTypeBridge::GetMonoClass(SetProperty->ElementProp);

	const auto FoundMonoType = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_Get_Type(FoundMonoClass);

	const auto FoundReflectionType = FCSharpEnvironment::GetEnvironment().GetDomain()->Type_Get_Object(FoundMonoType);

	auto InParams = static_cast<void*>(FoundReflectionType);

	const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
		GenericClassMonoClass, TGetArrayLength(InParams), &InParams);

	const auto SetHelper = new FSetHelper(SetProperty->ElementProp, InAddress);

	const auto OwnerGarbageCollectionHandle = FCSharpEnvironment::GetEnvironment().GetGarbageCollectionHandle(
		InAddress, SetProperty->GetOffset_ForInternal());

	if (OwnerGarbageCollectionHandle.IsValid())
	{
		FCSharpEnvironment::GetEnvironment().AddContainerReference(OwnerGarbageCollectionHandle, InAddress, SetHelper,
		                                                           Object);
	}
	else
	{
		FCSharpEnvironment::GetEnvironment().AddContainerReference(SetHelper, Object);
	}

	return Object;
}
