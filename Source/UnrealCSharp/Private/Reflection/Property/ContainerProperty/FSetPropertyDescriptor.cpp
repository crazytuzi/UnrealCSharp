#include "Reflection/Property/ContainerProperty/FSetPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Container/FSetHelper.h"
#include "Template/TGetArrayLength.inl"
#include "Bridge/FTypeBridge.h"

void FSetPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (SetProperty != nullptr)
	{
		*Dest = Object_New(Src);
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

		Object_New(Dest);
	}
}

MonoObject* FSetPropertyDescriptor::Object_New(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetContainerObject(InAddress);

	if (Object == nullptr)
	{
		const auto GenericClassMonoClass = FTypeBridge::GetMonoClass(SetProperty);

		const auto FoundMonoClass = FTypeBridge::GetMonoClass(SetProperty->ElementProp);

		const auto FoundMonoType = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_Get_Type(FoundMonoClass);

		const auto FoundReflectionType = FCSharpEnvironment::GetEnvironment().GetDomain()->Type_Get_Object(
			FoundMonoType);

		auto InParams = static_cast<void*>(FoundReflectionType);

		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			GenericClassMonoClass, TGetArrayLength(InParams), &InParams);

		const auto SetHelper = new FSetHelper(SetProperty->ElementProp, InAddress);

		const auto OwnerGarbageCollectionHandle = FCSharpEnvironment::GetEnvironment().GetGarbageCollectionHandle(
			InAddress, SetProperty->GetOffset_ForInternal());

		if (OwnerGarbageCollectionHandle.IsValid())
		{
			FCSharpEnvironment::GetEnvironment().AddContainerReference(OwnerGarbageCollectionHandle, InAddress,
			                                                           SetHelper,
			                                                           Object);
		}
		else
		{
			FCSharpEnvironment::GetEnvironment().AddContainerReference(InAddress, SetHelper, Object);
		}
	}

	return Object;
}
