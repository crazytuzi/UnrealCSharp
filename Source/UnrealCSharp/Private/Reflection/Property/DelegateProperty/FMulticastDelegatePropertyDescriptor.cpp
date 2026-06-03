#include "Reflection/Property/DelegateProperty/FMulticastDelegatePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FMulticastDelegateHelper.h"
#include "Domain/Script/IManagedTypes.h"

void FMulticastDelegatePropertyDescriptor::Get(void* Src, void** Dest, std::true_type) const
{
	*reinterpret_cast<IManagedObject*>(Dest) = NewWeakRef(Src);
}

void FMulticastDelegatePropertyDescriptor::Get(void* Src, void** Dest, std::false_type) const
{
	*reinterpret_cast<IManagedObject*>(Dest) = NewWeakRef(Src);
}

void FMulticastDelegatePropertyDescriptor::Get(void* Src, void* Dest) const
{
	*static_cast<IManagedObject*>(Dest) = NewRef(Src);
}

void FMulticastDelegatePropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcManagedHandle = *static_cast<IManagedHandle*>(Src);

	const auto SrcMulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
		FMulticastDelegateHelper>(SrcManagedHandle);

	Property->InitializeValue(Dest);

	const auto MulticastScriptDelegate = const_cast<FMulticastScriptDelegate*>(GetMulticastDelegate(Dest));

	FScriptDelegate ScriptDelegate;

	ScriptDelegate.BindUFunction(SrcMulticastDelegateHelper->GetUObject(),
	                             SrcMulticastDelegateHelper->GetFunctionName());

	MulticastScriptDelegate->Add(ScriptDelegate);
}

const FMulticastScriptDelegate* FMulticastDelegatePropertyDescriptor::GetMulticastDelegate(void* InAddress) const
{
	return Property->GetMulticastDelegate(InAddress);
}

IManagedObject FMulticastDelegatePropertyDescriptor::NewRef(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetDelegateObject<FMulticastDelegateHelper>(InAddress);

	if (!IManagedHandleIsValid(Object))
	{
		const auto MulticastDelegateHelper = new FMulticastDelegateHelper(
			const_cast<FMulticastScriptDelegate*>(GetMulticastDelegate(InAddress)),
			Property->SignatureFunction);

		Object = Class->NewObject();

		const auto OwnerManagedHandle = FCSharpEnvironment::GetEnvironment().GeManagedHandle(
			InAddress, Property);

		FCSharpEnvironment::GetEnvironment().AddDelegateReference(OwnerManagedHandle, InAddress,
		                                                          MulticastDelegateHelper, Class,
		                                                          MANAGED_HANDLE_FROM_OBJECT(Object));
	}

	return IManagedHandleToIManagedObject(Object);
}

IManagedObject FMulticastDelegatePropertyDescriptor::NewWeakRef(void* InAddress) const
{
	const auto MulticastDelegateHelper = new FMulticastDelegateHelper(
		const_cast<FMulticastScriptDelegate*>(GetMulticastDelegate(InAddress)),
		Property->SignatureFunction);

	const auto Object = Class->NewObject();

	FCSharpEnvironment::GetEnvironment().AddDelegateReference(MulticastDelegateHelper, Class,
	                                                          MANAGED_HANDLE_FROM_OBJECT(Object));

	return IManagedHandleToIManagedObject(Object);
}
