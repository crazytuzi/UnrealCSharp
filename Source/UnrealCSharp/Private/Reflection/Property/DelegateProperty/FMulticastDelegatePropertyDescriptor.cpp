#include "Reflection/Property/DelegateProperty/FMulticastDelegatePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FMulticastDelegateHelper.h"
#include "Bridge/FTypeBridge.h"
#include "Template/TGetArrayLength.inl"

void FMulticastDelegatePropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (MulticastDelegateProperty != nullptr)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetDelegateObject(Src);

		if (SrcMonoObject == nullptr)
		{
			SrcMonoObject = Object_New(Src);
		}

		*Dest = SrcMonoObject;
	}
}

void FMulticastDelegatePropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (MulticastDelegateProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcMulticastDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
			FMulticastDelegateHelper>(SrcMonoObject);

		(void)FCSharpEnvironment::GetEnvironment().RemoveDelegateReference(Dest);

		MulticastDelegateProperty->InitializeValue(Dest);

		const auto MulticastScriptDelegate = const_cast<FMulticastScriptDelegate*>(MulticastDelegateProperty->
			GetMulticastDelegate(Dest));

		FScriptDelegate ScriptDelegate;

		ScriptDelegate.BindUFunction(SrcMulticastDelegateHelper->GetUObject(),
		                             SrcMulticastDelegateHelper->GetFunctionName());

		MulticastScriptDelegate->Add(ScriptDelegate);

		Object_New(Dest);
	}
}

MonoObject* FMulticastDelegatePropertyDescriptor::Object_New(void* InAddress) const
{
	const auto FoundMonoClass = FTypeBridge::GetMonoClass(MulticastDelegateProperty);

	const auto MulticastDelegateHelper = new FMulticastDelegateHelper(
		static_cast<FMulticastScriptDelegate*>(InAddress), MulticastDelegateProperty->SignatureFunction);

	const auto FoundMonoType = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_Get_Type(FoundMonoClass);

	const auto FoundReflectionType = FCSharpEnvironment::GetEnvironment().GetDomain()->Type_Get_Object(FoundMonoType);

	auto InParams = static_cast<void*>(FoundReflectionType);

	const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
		FoundMonoClass, TGetArrayLength(InParams), &InParams);

	const auto OwnerGarbageCollectionHandle = FCSharpEnvironment::GetEnvironment().GetGarbageCollectionHandle(
		InAddress, DelegateProperty->GetOffset_ForInternal());

	if (OwnerGarbageCollectionHandle.IsValid())
	{
		FCSharpEnvironment::GetEnvironment().AddDelegateReference(OwnerGarbageCollectionHandle, InAddress,
		                                                          MulticastDelegateHelper, Object);
	}
	else
	{
		FCSharpEnvironment::GetEnvironment().AddDelegateReference(InAddress, MulticastDelegateHelper, Object);
	}

	return Object;
}
