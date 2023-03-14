#include "Reflection/Property/DelegateProperty/FDelegatePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FDelegateHelper.h"
#include "Bridge/FTypeBridge.h"

void FDelegatePropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (DelegateProperty != nullptr)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetDelegateObject(Src);

		if (SrcMonoObject == nullptr)
		{
			const auto FoundMonoClass = FTypeBridge::GetMonoClass(DelegateProperty);

			const auto DelegateHelper = new FDelegateHelper(static_cast<FScriptDelegate*>(Src),
			                                                DelegateProperty->SignatureFunction);

			SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass);

			const auto OwnerGarbageCollectionHandle = FCSharpEnvironment::GetEnvironment()->GetGarbageCollectionHandle(
				Src, DelegateProperty->GetOffset_ForInternal());

			FCSharpEnvironment::GetEnvironment()->AddDelegateReference(OwnerGarbageCollectionHandle, Src,
			                                                           DelegateHelper, SrcMonoObject);
		}

		*Dest = SrcMonoObject;
	}
}
