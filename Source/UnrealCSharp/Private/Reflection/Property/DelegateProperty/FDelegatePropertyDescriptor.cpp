#include "Reflection/Property/DelegateProperty/FDelegatePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FDelegateHelper.h"
#include "Bridge/FTypeBridge.h"
#include "Template/TGetArrayLength.inl"

void FDelegatePropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (DelegateProperty != nullptr)
	{
		*Dest = Object_New(Src);
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

		Object_New(Dest);
	}
}

MonoObject* FDelegatePropertyDescriptor::Object_New(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetDelegateObject(InAddress);

	if (Object == nullptr)
	{
		const auto FoundMonoClass = FTypeBridge::GetMonoClass(DelegateProperty);

		const auto DelegateHelper = new FDelegateHelper(DelegateProperty->GetPropertyValuePtr(InAddress),
		                                                DelegateProperty->SignatureFunction);

		const auto FoundMonoType = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_Get_Type(FoundMonoClass);

		const auto FoundReflectionType = FCSharpEnvironment::GetEnvironment().GetDomain()->Type_Get_Object(
			FoundMonoType);

		auto InParams = static_cast<void*>(FoundReflectionType);

		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, TGetArrayLength(InParams), &InParams);

		const auto OwnerGarbageCollectionHandle = FCSharpEnvironment::GetEnvironment().GetGarbageCollectionHandle(
			InAddress, DelegateProperty->GetOffset_ForInternal());

		if (OwnerGarbageCollectionHandle.IsValid())
		{
			FCSharpEnvironment::GetEnvironment().AddDelegateReference(OwnerGarbageCollectionHandle, InAddress,
			                                                          DelegateHelper, Object);
		}
		else
		{
			FCSharpEnvironment::GetEnvironment().AddDelegateReference(InAddress, DelegateHelper, Object);
		}
	}

	return Object;
}
