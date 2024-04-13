﻿#include "Reflection/Property/ContainerProperty/FMapPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Container/FMapHelper.h"

void FMapPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (MapProperty != nullptr)
	{
		*Dest = NewWeakRef(Src);
	}
}

void FMapPropertyDescriptor::Get(void* Src, void* Dest) const
{
	if (MapProperty != nullptr)
	{
		*static_cast<void**>(Dest) = NewRef(Src);
	}
}

void FMapPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (MapProperty != nullptr)
	{
		const auto SrcGarbageCollectionHandle = static_cast<FGarbageCollectionHandle>(Src);

		const auto SrcContainer = FCSharpEnvironment::GetEnvironment().GetContainer<FMapHelper>(
			SrcGarbageCollectionHandle);

		MapProperty->InitializeValue(Dest);

		MapProperty->CopyCompleteValue(Dest, SrcContainer->GetScriptMap());
	}
}

MonoObject* FMapPropertyDescriptor::NewRef(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetContainerObject<FMapHelper>(InAddress);

	if (Object == nullptr)
	{
		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		const auto MapHelper = new FMapHelper(MapProperty->KeyProp, MapProperty->ValueProp, InAddress);

		const auto OwnerGarbageCollectionHandle = FCSharpEnvironment::GetEnvironment().GetGarbageCollectionHandle(
			InAddress, MapProperty);

		FCSharpEnvironment::GetEnvironment().AddContainerReference(OwnerGarbageCollectionHandle, InAddress, MapHelper,
		                                                           Object);
	}

	return Object;
}

MonoObject* FMapPropertyDescriptor::NewWeakRef(void* InAddress) const
{
	const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

	const auto MapHelper = new FMapHelper(MapProperty->KeyProp, MapProperty->ValueProp, InAddress);

	FCSharpEnvironment::GetEnvironment().AddContainerReference(MapHelper, Object);

	return Object;
}
