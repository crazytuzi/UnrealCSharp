#include "Reflection/Property/DelegateProperty/FDelegatePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FDelegateHelper.h"
#include "FUnrealCSharpFunctionLibrary.h"

void FDelegatePropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (DelegateProperty != nullptr)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetDelegateObject(Src);

		if (SrcMonoObject == nullptr)
		{
			auto MonoClassName = DelegateProperty->SignatureFunction->GetName();

			MonoClassName.LeftChopInline(FString(HEADER_GENERATED_DELEGATE_SIGNATURE_SUFFIX).Len(), false);

			const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
				FUnrealCSharpFunctionLibrary::GetClassNameSpace(DelegateProperty),
				FUnrealCSharpFunctionLibrary::GetFullClass(DelegateProperty));

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
