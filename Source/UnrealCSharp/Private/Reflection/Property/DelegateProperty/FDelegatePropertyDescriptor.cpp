#include "Reflection/Property/DelegateProperty/FDelegatePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FDelegateHelper.h"
#include "Bridge/FTypeBridge.h"
#include "Template/TGetArrayLength.inl"

FDelegatePropertyDescriptor::FDelegatePropertyDescriptor(FProperty* InProperty):
	FPropertyDescriptor(InProperty),
	Class(nullptr),
	Type(nullptr)
{
	Class = FTypeBridge::GetMonoClass(DelegateProperty);

	const auto FoundMonoType = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_Get_Type(Class);

	Type = FCSharpEnvironment::GetEnvironment().GetDomain()->Type_Get_Object(FoundMonoType);
}

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
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcDelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<
			FDelegateHelper>(SrcMonoObject);

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

		auto InParams = static_cast<void*>(Type);

		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			Class, TGetArrayLength(InParams), &InParams);

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

	auto InParams = static_cast<void*>(Type);

	const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
		Class, TGetArrayLength(InParams), &InParams);

	FCSharpEnvironment::GetEnvironment().AddDelegateReference(InAddress, DelegateHelper, Object);

	return Object;
}
