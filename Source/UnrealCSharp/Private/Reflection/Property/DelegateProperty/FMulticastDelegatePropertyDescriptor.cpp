#include "Reflection/Property/DelegateProperty/FMulticastDelegatePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FMulticastDelegateHelper.h"
#include "Bridge/FTypeBridge.h"

void FMulticastDelegatePropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (MulticastDelegateProperty != nullptr)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetDelegateObject(Src);

		if (SrcMonoObject == nullptr)
		{
			const auto FoundMonoClass = FTypeBridge::GetMonoClass(MulticastDelegateProperty);

			const auto MulticastDelegateHelper = new FMulticastDelegateHelper(
				static_cast<FMulticastScriptDelegate*>(Src), MulticastDelegateProperty->SignatureFunction);

			SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass);

			const auto OwnerGarbageCollectionHandle = FCSharpEnvironment::GetEnvironment()->GetGarbageCollectionHandle(
				Src, MulticastDelegateProperty->GetOffset_ForInternal());

			FCSharpEnvironment::GetEnvironment()->AddDelegateReference(OwnerGarbageCollectionHandle, Src,
			                                                           MulticastDelegateHelper, SrcMonoObject);
		}

		*Dest = SrcMonoObject;
	}
}
