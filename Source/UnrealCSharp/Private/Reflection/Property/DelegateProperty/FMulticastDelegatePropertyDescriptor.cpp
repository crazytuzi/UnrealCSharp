#include "Reflection/Property/DelegateProperty/FMulticastDelegatePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FMulticastDelegateHelper.h"
#include "FUnrealCSharpFunctionLibrary.h"

void FMulticastDelegatePropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (MulticastDelegateProperty != nullptr)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetDelegateObject(Src);

		if (SrcMonoObject == nullptr)
		{
			auto MonoClassName = MulticastDelegateProperty->SignatureFunction->GetName();

			MonoClassName.LeftChopInline(FString(HEADER_GENERATED_DELEGATE_SIGNATURE_SUFFIX).Len(), false);

			const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
				FUnrealCSharpFunctionLibrary::GetClassNameSpace(MulticastDelegateProperty),
				FUnrealCSharpFunctionLibrary::GetFullClass(MulticastDelegateProperty));

			const auto MulticastDelegateHelper = new FMulticastDelegateHelper(
				static_cast<FMulticastScriptDelegate*>(Src), MulticastDelegateProperty->SignatureFunction);

			SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass);

			FCSharpEnvironment::GetEnvironment()->AddDelegateReference(Src, MulticastDelegateHelper, SrcMonoObject);
		}

		*Dest = SrcMonoObject;
	}
}
