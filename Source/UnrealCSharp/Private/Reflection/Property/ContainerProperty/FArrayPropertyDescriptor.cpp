#include "Reflection/Property/ContainerProperty/FArrayPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Container/FArrayHelper.h"

void FArrayPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (ArrayProperty != nullptr)
	{
		*Dest = NewWeakRef(Src);
	}
}

void FArrayPropertyDescriptor::Get(void* Src, void* Dest) const
{
	if (ArrayProperty != nullptr)
	{
		*static_cast<void**>(Dest) = NewRef(Src);
	}
}

void FArrayPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (ArrayProperty != nullptr)
	{
		const auto SrcGarbageCollectionHandle = static_cast<FGarbageCollectionHandle>(Src);

		const auto SrcContainer = FCSharpEnvironment::GetEnvironment().GetContainer<FArrayHelper>(
			SrcGarbageCollectionHandle);

		ArrayProperty->InitializeValue(Dest);

		ArrayProperty->CopyCompleteValue(Dest, SrcContainer->GetScriptArray());
	}
}

MonoObject* FArrayPropertyDescriptor::NewRef(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetContainerObject<FArrayHelper>(InAddress);

	if (Object == nullptr)
	{
		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		const auto ArrayHelper = new FArrayHelper(ArrayProperty->Inner, InAddress);

		const auto OwnerGarbageCollectionHandle = FCSharpEnvironment::GetEnvironment().GetGarbageCollectionHandle(
			InAddress, ArrayProperty);

		FCSharpEnvironment::GetEnvironment().AddContainerReference(OwnerGarbageCollectionHandle, InAddress, ArrayHelper,
		                                                           Object);
	}

	return Object;
}

MonoObject* FArrayPropertyDescriptor::NewWeakRef(void* InAddress) const
{
	const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

	const auto ArrayHelper = new FArrayHelper(ArrayProperty->Inner, InAddress);

	FCSharpEnvironment::GetEnvironment().AddContainerReference(ArrayHelper, Object);

	return Object;
}
