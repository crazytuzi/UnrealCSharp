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

	if (SrcDelegateHelper != nullptr)
	{
		DestScriptDelegate->BindUFunction(SrcDelegateHelper->GetUObject(), SrcDelegateHelper->GetFunctionName());
	}
}

bool FDelegatePropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
		*static_cast<IManagedHandle*>(const_cast<void*>(B))))
	{
		return Property->Identical(A, DelegateHelper->GetAddress(), PortFlags);
	}

	return false;
}

IManagedHandle FDelegatePropertyDescriptor::NewRef(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetDelegateObject<FDelegateHelper>(InAddress);

	if (!IManagedHandleIsValid(Object))
	{
		if (Class != nullptr)
		{
			const auto DelegateHelper = new FDelegateHelper(Property->GetPropertyValuePtr(InAddress),
			                                                Property->SignatureFunction);

			Object = Class->NewObject();

			const auto OwnerManagedHandle = FCSharpEnvironment::GetEnvironment().GeManagedHandle(
				InAddress, Property);

			FCSharpEnvironment::GetEnvironment().AddDelegateReference(OwnerManagedHandle, InAddress,
			                                                          DelegateHelper, Class, Object);
		}
	}

	return Object;
}

IManagedHandle FDelegatePropertyDescriptor::NewWeakRef(void* InAddress) const
{
	auto Object = InvalidManagedHandle;

	if (Class != nullptr)
	{
		const auto DelegateHelper = new FDelegateHelper(Property->GetPropertyValuePtr(InAddress),
		                                                Property->SignatureFunction);

		Object = Class->NewObject(true);

		FCSharpEnvironment::GetEnvironment().AddDelegateReference(DelegateHelper, Class, Object);
	}

	return Object;
}
