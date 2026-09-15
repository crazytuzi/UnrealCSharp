#include "Reflection/Property/DelegateProperty/FMulticastDelegatePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FMulticastDelegateHelper.h"

void FMulticastDelegatePropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FMember) const
{
	*reinterpret_cast<IManagedHandle*>(Dest) = NewWeakRef(Src);
}

void FMulticastDelegatePropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FReturn) const
{
	*reinterpret_cast<IManagedHandle*>(Dest) = NewWeakRef(Src);
}

void FMulticastDelegatePropertyDescriptor::Get(void* Src, void* Dest) const
{
	*reinterpret_cast<IManagedHandle*>(Dest) = NewRef(Src);
}

void FMulticastDelegatePropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcManagedHandle = *static_cast<IManagedHandle*>(Src);

	const auto SrcMulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
		FMulticastDelegateHelper>(SrcManagedHandle);

	Property->InitializeValue(Dest);

	const auto MulticastScriptDelegate = const_cast<FMulticastScriptDelegate*>(GetMulticastDelegate(Dest));

	if (SrcMulticastDelegateHelper != nullptr)
	{
		FScriptDelegate ScriptDelegate;

		ScriptDelegate.BindUFunction(SrcMulticastDelegateHelper->GetUObject(),
		                             SrcMulticastDelegateHelper->GetFunctionName());

		MulticastScriptDelegate->Add(ScriptDelegate);
	}
}

bool FMulticastDelegatePropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (const auto MulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
		FMulticastDelegateHelper>(*static_cast<IManagedHandle*>(const_cast<void*>(B))))
	{
		return Property->Identical(A, MulticastDelegateHelper->GetAddress(), PortFlags);
	}

	return false;
}

const FMulticastScriptDelegate* FMulticastDelegatePropertyDescriptor::GetMulticastDelegate(void* InAddress) const
{
	return Property->GetMulticastDelegate(InAddress);
}

IManagedHandle FMulticastDelegatePropertyDescriptor::NewRef(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetDelegateObject<FMulticastDelegateHelper>(InAddress);

	if (!IManagedHandleIsValid(Object))
	{
		if (Class != nullptr)
		{
			const auto MulticastDelegateHelper = new FMulticastDelegateHelper(
				const_cast<FMulticastScriptDelegate*>(GetMulticastDelegate(InAddress)),
				Property->SignatureFunction);

			Object = Class->NewObject();

			const auto OwnerManagedHandle = FCSharpEnvironment::GetEnvironment().GeManagedHandle(
				InAddress, Property);

			FCSharpEnvironment::GetEnvironment().AddDelegateReference(OwnerManagedHandle, InAddress,
			                                                          MulticastDelegateHelper, Class, Object);
		}
	}

	return Object;
}

IManagedHandle FMulticastDelegatePropertyDescriptor::NewWeakRef(void* InAddress) const
{
	auto Object = InvalidManagedHandle;

	if (Class != nullptr)
	{
		const auto MulticastDelegateHelper = new FMulticastDelegateHelper(
			const_cast<FMulticastScriptDelegate*>(GetMulticastDelegate(InAddress)),
			Property->SignatureFunction);

		Object = Class->NewObject();

		FCSharpEnvironment::GetEnvironment().AddDelegateReference(MulticastDelegateHelper, Class, Object);
	}

	return Object;
}
