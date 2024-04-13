#include "Reflection/Property/DelegateProperty/FDelegatePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FDelegateHelper.h"

void FDelegatePropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (DelegateProperty != nullptr)
	{
		*Dest = NewWeakRef(Src);
	}
}

void FDelegatePropertyDescriptor::Get(void* Src, void* Dest) const
{
	if (DelegateProperty != nullptr)
	{
		*static_cast<void**>(Dest) = NewRef(Src);
	}
}

void FDelegatePropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (DelegateProperty != nullptr)
	{
		const auto SrcGarbageCollectionHandle = static_cast<FGarbageCollectionHandle>(Src);

		const auto SrcDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
			SrcGarbageCollectionHandle);

		DelegateProperty->InitializeValue(Dest);

		const auto DestScriptDelegate = DelegateProperty->GetPropertyValuePtr(Dest);

		DestScriptDelegate->BindUFunction(SrcDelegateHelper->GetUObject(), SrcDelegateHelper->GetFunctionName());
	}
}

MonoObject* FDelegatePropertyDescriptor::NewRef(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetDelegateObject<FDelegateHelper>(InAddress);

	if (Object == nullptr)
	{
		const auto DelegateHelper = new FDelegateHelper(DelegateProperty->GetPropertyValuePtr(InAddress),
		                                                DelegateProperty->SignatureFunction);

		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		const auto OwnerGarbageCollectionHandle = FCSharpEnvironment::GetEnvironment().GetGarbageCollectionHandle(
			InAddress, DelegateProperty);

		FCSharpEnvironment::GetEnvironment().AddDelegateReference(OwnerGarbageCollectionHandle, InAddress,
		                                                          DelegateHelper, Object);
	}

	return Object;
}

MonoObject* FDelegatePropertyDescriptor::NewWeakRef(void* InAddress) const
{
	const auto DelegateHelper = new FDelegateHelper(DelegateProperty->GetPropertyValuePtr(InAddress),
	                                                DelegateProperty->SignatureFunction);

	const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

	FCSharpEnvironment::GetEnvironment().AddDelegateReference(DelegateHelper, Object);

	return Object;
}
