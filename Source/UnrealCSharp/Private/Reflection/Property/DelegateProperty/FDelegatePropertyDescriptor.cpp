#include "Reflection/Property/DelegateProperty/FDelegatePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FDelegateHelper.h"

void FDelegatePropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FMember) const
{
	*reinterpret_cast<IManagedHandle*>(Dest) = NewWeakRef(Src);
}

void FDelegatePropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FReturn) const
{
	*reinterpret_cast<IManagedHandle*>(Dest) = NewWeakRef(Src);
}

void FDelegatePropertyDescriptor::Get(void* Src, void* Dest) const
{
	*reinterpret_cast<IManagedHandle*>(Dest) = NewRef(Src);
}

void FDelegatePropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcManagedHandle = *static_cast<IManagedHandle*>(Src);

	const auto SrcDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(SrcManagedHandle);

	Property->InitializeValue(Dest);

	const auto DestScriptDelegate = Property->GetPropertyValuePtr(Dest);

	DestScriptDelegate->BindUFunction(SrcDelegateHelper->GetUObject(), SrcDelegateHelper->GetFunctionName());
}

IManagedHandle FDelegatePropertyDescriptor::NewRef(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetDelegateObject<FDelegateHelper>(InAddress);

	if (!IManagedHandleIsValid(Object))
	{
		const auto DelegateHelper = new FDelegateHelper(Property->GetPropertyValuePtr(InAddress),
		                                                Property->SignatureFunction);

		Object = Class->NewObject();

		const auto OwnerManagedHandle = FCSharpEnvironment::GetEnvironment().GeManagedHandle(
			InAddress, Property);

		FCSharpEnvironment::GetEnvironment().AddDelegateReference(OwnerManagedHandle, InAddress,
		                                                          DelegateHelper, Class, Object);
	}

	return Object;
}

IManagedHandle FDelegatePropertyDescriptor::NewWeakRef(void* InAddress) const
{
	const auto DelegateHelper = new FDelegateHelper(Property->GetPropertyValuePtr(InAddress),
	                                                Property->SignatureFunction);

	const auto Object = Class->NewObject();

	FCSharpEnvironment::GetEnvironment().AddDelegateReference(DelegateHelper, Class, Object);

	return Object;
}
