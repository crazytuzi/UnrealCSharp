#include "Reflection/Property/DelegateProperty/FMulticastDelegatePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FMulticastDelegateHelper.h"

void FMulticastDelegatePropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FMember) const
{
	*reinterpret_cast<IManagedHandle*>(Dest) = NewWeakRef(Src, Src);
}

void FMulticastDelegatePropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FReturn) const
{
	*reinterpret_cast<IManagedHandle*>(Dest) = NewWeakRef(Src, nullptr);
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

	if (SrcMulticastDelegateHelper != nullptr)
	{
		FScriptDelegate ScriptDelegate;

		ScriptDelegate.BindUFunction(SrcMulticastDelegateHelper->GetUObject(),
		                             SrcMulticastDelegateHelper->GetFunctionName());

		if (const auto MulticastScriptDelegate = const_cast<FMulticastScriptDelegate*>(GetMulticastDelegate(Dest)))
		{
			MulticastScriptDelegate->Add(ScriptDelegate);
		}
		else if (ScriptDelegate.IsBound())
		{
			FMulticastScriptDelegate MulticastDelegate;

			MulticastDelegate.Add(ScriptDelegate);

			Property->SetMulticastDelegate(Dest, MulticastDelegate);
		}
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
				Property->SignatureFunction, Property, InAddress);

			Object = Class->NewObject(true);

			const auto OwnerManagedHandle = FCSharpEnvironment::GetEnvironment().GeManagedHandle(
				InAddress, Property);

			FCSharpEnvironment::GetEnvironment().AddDelegateReference(OwnerManagedHandle, InAddress,
			                                                          MulticastDelegateHelper, Class, Object);
		}
	}

	return Object;
}

IManagedHandle FMulticastDelegatePropertyDescriptor::NewWeakRef(void* InAddress, void* InPropertyAddress) const
{
	auto Object = InvalidManagedHandle;

	if (Class != nullptr)
	{
		const auto MulticastDelegateHelper = new FMulticastDelegateHelper(
			const_cast<FMulticastScriptDelegate*>(GetMulticastDelegate(InAddress)),
			Property->SignatureFunction, Property, InPropertyAddress);

		Object = Class->NewObject(true);

		FCSharpEnvironment::GetEnvironment().AddDelegateReference(MulticastDelegateHelper, Class, Object);
	}

	return Object;
}
