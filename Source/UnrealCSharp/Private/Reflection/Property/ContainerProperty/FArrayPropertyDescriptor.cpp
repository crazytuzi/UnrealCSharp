﻿#include "Reflection/Property/ContainerProperty/FArrayPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Container/FArrayHelper.h"
#include "Template/TGetArrayLength.inl"
#include "Bridge/FTypeBridge.h"

FArrayPropertyDescriptor::FArrayPropertyDescriptor(FProperty* InProperty):
	FContainerPropertyDescriptor(InProperty),
	Class(nullptr),
	Type(nullptr)
{
	Class = FTypeBridge::GetMonoClass(ArrayProperty);

	const auto FoundMonoClass = FTypeBridge::GetMonoClass(ArrayProperty->Inner);

	const auto FoundMonoType = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_Get_Type(FoundMonoClass);

	Type = FCSharpEnvironment::GetEnvironment().GetDomain()->Type_Get_Object(FoundMonoType);
}

void FArrayPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (ArrayProperty != nullptr)
	{
		*Dest = Object_New(Src);
	}
}

void FArrayPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (ArrayProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcContainer = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(SrcMonoObject);

		ArrayProperty->InitializeValue(Dest);

		ArrayProperty->CopyCompleteValue(Dest, SrcContainer->GetScriptArray());
	}
}

MonoObject* FArrayPropertyDescriptor::Object_New(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetContainerObject(InAddress);

	if (Object == nullptr)
	{
		auto InParams = static_cast<void*>(Type);

		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			Class, TGetArrayLength(InParams), &InParams);

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
			FCSharpEnvironment::GetEnvironment().AddContainerReference(InAddress, ArrayHelper, Object);
		}
	}

	return Object;
}
