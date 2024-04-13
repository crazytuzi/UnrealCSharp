#include "Reflection/Property/DelegateProperty/FMulticastDelegatePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FMulticastDelegateHelper.h"

void FMulticastDelegatePropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (MulticastDelegateProperty != nullptr)
	{
		*Dest = NewWeakRef(Src);
	}
}

void FMulticastDelegatePropertyDescriptor::Get(void* Src, void* Dest) const
{
	if (MulticastDelegateProperty != nullptr)
	{
		*static_cast<void**>(Dest) = NewRef(Src);
	}
}

void FMulticastDelegatePropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (MulticastDelegateProperty != nullptr)
	{
		const auto SrcGarbageCollectionHandle = static_cast<FGarbageCollectionHandle>(Src);

		const auto SrcMulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
			FMulticastDelegateHelper>(SrcGarbageCollectionHandle);

		MulticastDelegateProperty->InitializeValue(Dest);

		const auto MulticastScriptDelegate = const_cast<FMulticastScriptDelegate*>(GetMulticastDelegate(Dest));

		FScriptDelegate ScriptDelegate;

		ScriptDelegate.BindUFunction(SrcMulticastDelegateHelper->GetUObject(),
		                             SrcMulticastDelegateHelper->GetFunctionName());

		MulticastScriptDelegate->Add(ScriptDelegate);
	}
}

const FMulticastScriptDelegate* FMulticastDelegatePropertyDescriptor::GetMulticastDelegate(void* InAddress) const
{
	return MulticastDelegateProperty->GetMulticastDelegate(InAddress);
}

MonoObject* FMulticastDelegatePropertyDescriptor::NewRef(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetDelegateObject<FMulticastDelegateHelper>(InAddress);

	if (Object == nullptr)
	{
		const auto MulticastDelegateHelper = new FMulticastDelegateHelper(
			const_cast<FMulticastScriptDelegate*>(GetMulticastDelegate(InAddress)),
			MulticastDelegateProperty->SignatureFunction);

		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		const auto OwnerGarbageCollectionHandle = FCSharpEnvironment::GetEnvironment().GetGarbageCollectionHandle(
			InAddress, DelegateProperty);

		FCSharpEnvironment::GetEnvironment().AddDelegateReference(OwnerGarbageCollectionHandle, InAddress,
		                                                          MulticastDelegateHelper, Object);
	}

	return Object;
}

MonoObject* FMulticastDelegatePropertyDescriptor::NewWeakRef(void* InAddress) const
{
	const auto MulticastDelegateHelper = new FMulticastDelegateHelper(
		const_cast<FMulticastScriptDelegate*>(GetMulticastDelegate(InAddress)),
		MulticastDelegateProperty->SignatureFunction);

	const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

	FCSharpEnvironment::GetEnvironment().AddDelegateReference(MulticastDelegateHelper, Object);

	return Object;
}
