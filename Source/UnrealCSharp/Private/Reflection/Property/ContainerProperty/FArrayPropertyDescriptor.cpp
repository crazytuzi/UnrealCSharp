#include "Reflection/Property/ContainerProperty/FArrayPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Container/FArrayHelper.h"
#include "Template/TGetArrayLength.inl"
#include "Bridge/FTypeBridge.h"

void FArrayPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (ArrayProperty != nullptr)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetContainerObject(Src);

		if (SrcMonoObject == nullptr)
		{
			SrcMonoObject = Object_New(Src);
		}

		*Dest = SrcMonoObject;
	}
}

void FArrayPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (ArrayProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcContainer = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(SrcMonoObject);

		(void)FCSharpEnvironment::GetEnvironment().RemoveContainerReference(Dest);

		ArrayProperty->InitializeValue(Dest);

		ArrayProperty->CopyCompleteValue(Dest, SrcContainer->GetScriptArray());

		Object_New(Dest);
	}
}

MonoObject* FArrayPropertyDescriptor::Object_New(void* InAddress) const
{
	const auto GenericClassMonoClass = FTypeBridge::GetMonoClass(ArrayProperty);

	const auto FoundMonoClass = FTypeBridge::GetMonoClass(ArrayProperty->Inner);

	const auto FoundMonoType = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_Get_Type(FoundMonoClass);

	const auto FoundReflectionType = FCSharpEnvironment::GetEnvironment().GetDomain()->Type_Get_Object(FoundMonoType);

	auto InParams = static_cast<void*>(FoundReflectionType);

	const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
		GenericClassMonoClass, TGetArrayLength(InParams), &InParams);

	const auto ArrayHelper = new FArrayHelper(ArrayProperty->Inner, InAddress);

	const auto OwnerGarbageCollectionHandle = FCSharpEnvironment::GetEnvironment().GetGarbageCollectionHandle(
		InAddress, ArrayProperty->GetOffset_ForInternal());

	if (OwnerGarbageCollectionHandle.IsValid())
	{
		FCSharpEnvironment::GetEnvironment().AddContainerReference(OwnerGarbageCollectionHandle, InAddress,
		                                                           ArrayHelper, Object);
	}
	else
	{
		FCSharpEnvironment::GetEnvironment().AddContainerReference(ArrayHelper, Object);
	}

	return Object;
}
