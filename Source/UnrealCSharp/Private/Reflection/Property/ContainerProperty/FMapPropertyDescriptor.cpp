#include "Reflection/Property/ContainerProperty/FMapPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Container/FMapHelper.h"
#include "Template/TGetArrayLength.inl"
#include "Bridge/FTypeBridge.h"

void FMapPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (MapProperty != nullptr)
	{
		*Dest = Object_New(Src);
	}
}

void FMapPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (MapProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcContainer = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(SrcMonoObject);

		MapProperty->InitializeValue(Dest);

		MapProperty->CopyCompleteValue(Dest, SrcContainer->GetScriptMap());
	}
}

MonoObject* FMapPropertyDescriptor::Object_New(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetContainerObject(InAddress);

	if (Object == nullptr)
	{
		const auto GenericClassMonoClass = FTypeBridge::GetMonoClass(MapProperty);

		const auto FoundKeyMonoClass = FTypeBridge::GetMonoClass(MapProperty->KeyProp);

		const auto FoundKeyMonoType = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_Get_Type(
			FoundKeyMonoClass);

		const auto FoundKeyReflectionType = FCSharpEnvironment::GetEnvironment().GetDomain()->Type_Get_Object(
			FoundKeyMonoType);

		const auto FoundValueMonoClass = FTypeBridge::GetMonoClass(MapProperty->ValueProp);

		const auto FoundValueMonoType = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_Get_Type(
			FoundValueMonoClass);

		const auto FoundValueReflectionType = FCSharpEnvironment::GetEnvironment().GetDomain()->Type_Get_Object(
			FoundValueMonoType);

		void* InParams[2] = {FoundKeyReflectionType, FoundValueReflectionType};

		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			GenericClassMonoClass, TGetArrayLength(InParams), InParams);

		const auto MapHelper = new FMapHelper(MapProperty->KeyProp, MapProperty->ValueProp, InAddress);

		const auto OwnerGarbageCollectionHandle = FCSharpEnvironment::GetEnvironment().GetGarbageCollectionHandle(
			InAddress, MapProperty->GetOffset_ForInternal());

		if (OwnerGarbageCollectionHandle.IsValid())
		{
			FCSharpEnvironment::GetEnvironment().AddContainerReference(OwnerGarbageCollectionHandle, InAddress,
			                                                           MapHelper,
			                                                           Object);
		}
		else
		{
			FCSharpEnvironment::GetEnvironment().AddContainerReference(InAddress, MapHelper, Object);
		}
	}

	return Object;
}
