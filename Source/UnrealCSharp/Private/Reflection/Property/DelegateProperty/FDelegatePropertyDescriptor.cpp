#include "Reflection/Property/DelegateProperty/FDelegatePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FDelegateHelper.h"

void FDelegatePropertyDescriptor::Get(void* Src, void** Dest, std::true_type) const
{
	*Dest = NewWeakRef(Src);
}

void FDelegatePropertyDescriptor::Get(void* Src, void** Dest, std::false_type) const
{
	*Dest = NewWeakRef(Src);
}

void FDelegatePropertyDescriptor::Get(void* Src, void* Dest) const
{
	*static_cast<void**>(Dest) = NewRef(Src);
}

void FDelegatePropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcGarbageCollectionHandle = *static_cast<FGarbageCollectionHandle*>(Src);

	const auto SrcDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
		SrcGarbageCollectionHandle);

	Property->InitializeValue(Dest);

	const auto DestScriptDelegate = Property->GetPropertyValuePtr(Dest);

	DestScriptDelegate->BindUFunction(SrcDelegateHelper->GetUObject(), SrcDelegateHelper->GetFunctionName());
}

MonoObject* FDelegatePropertyDescriptor::NewRef(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetDelegateObject<FDelegateHelper>(InAddress);

	if (Object == nullptr)
	{
		const auto DelegateHelper = new FDelegateHelper(Property->GetPropertyValuePtr(InAddress),
		                                                Property->SignatureFunction);

		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		const auto OwnerGarbageCollectionHandle = FCSharpEnvironment::GetEnvironment().GetGarbageCollectionHandle(
			InAddress, Property);

		FCSharpEnvironment::GetEnvironment().AddDelegateReference(OwnerGarbageCollectionHandle, InAddress,
		                                                          DelegateHelper, Object);
	}

	return Object;
}

MonoObject* FDelegatePropertyDescriptor::NewWeakRef(void* InAddress) const
{
	const auto DelegateHelper = new FDelegateHelper(Property->GetPropertyValuePtr(InAddress),
	                                                Property->SignatureFunction);

	const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

	FCSharpEnvironment::GetEnvironment().AddDelegateReference(DelegateHelper, Object);

	return Object;
}
