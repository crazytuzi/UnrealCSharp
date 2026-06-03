#include "Reflection/Property/DelegateProperty/FDelegatePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FDelegateHelper.h"
#include "Domain/Script/IManagedTypes.h"

void FDelegatePropertyDescriptor::Get(void* Src, void** Dest, std::true_type) const
{
	*reinterpret_cast<IManagedObject*>(Dest) = NewWeakRef(Src);
}

void FDelegatePropertyDescriptor::Get(void* Src, void** Dest, std::false_type) const
{
	*reinterpret_cast<IManagedObject*>(Dest) = NewWeakRef(Src);
}

void FDelegatePropertyDescriptor::Get(void* Src, void* Dest) const
{
	*static_cast<IManagedObject*>(Dest) = NewRef(Src);
}

void FDelegatePropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcManagedHandle = *static_cast<IManagedHandle*>(Src);

	const auto SrcDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(SrcManagedHandle);

	Property->InitializeValue(Dest);

	const auto DestScriptDelegate = Property->GetPropertyValuePtr(Dest);

	DestScriptDelegate->BindUFunction(SrcDelegateHelper->GetUObject(), SrcDelegateHelper->GetFunctionName());
}

IManagedObject FDelegatePropertyDescriptor::NewRef(void* InAddress) const
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
		                                                          DelegateHelper, Class,
		                                                          MANAGED_HANDLE_FROM_OBJECT(Object));
	}

	return IManagedHandleToIManagedObject(Object);
}

IManagedObject FDelegatePropertyDescriptor::NewWeakRef(void* InAddress) const
{
	const auto DelegateHelper = new FDelegateHelper(Property->GetPropertyValuePtr(InAddress),
	                                                Property->SignatureFunction);

	const auto Object = Class->NewObject();

	FCSharpEnvironment::GetEnvironment().AddDelegateReference(DelegateHelper, Class,
	                                                          MANAGED_HANDLE_FROM_OBJECT(Object));

	return IManagedHandleToIManagedObject(Object);
}
