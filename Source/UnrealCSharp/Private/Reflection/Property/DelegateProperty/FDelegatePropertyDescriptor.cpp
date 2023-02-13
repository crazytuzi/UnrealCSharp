#include "Reflection/Property/DelegateProperty/FDelegatePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FDelegateHelper.h"
#include "FUnrealCSharpFunctionLibrary.h"

void FDelegatePropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (DelegateProperty != nullptr)
	{
		const auto SrcDelegateHelper = FCSharpEnvironment::GetEnvironment()->GetDelegate<FDelegateHelper>(Src);

		if (SrcDelegateHelper == nullptr)
		{
			auto MonoClassName = DelegateProperty->SignatureFunction->GetName();

			MonoClassName.LeftChopInline(FString(HEADER_GENERATED_DELEGATE_SIGNATURE_SUFFIX).Len(), false);

			const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
				FUnrealCSharpFunctionLibrary::GetClassNameSpace(DelegateProperty),
				FUnrealCSharpFunctionLibrary::GetFullClass(DelegateProperty));

			const auto DelegateHelper = new FDelegateHelper(static_cast<FScriptDelegate*>(Src),
			                                                DelegateProperty->SignatureFunction);

			void* Param[1] = {Src};

			*Dest = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass, 1, Param);

			FCSharpEnvironment::GetEnvironment()->AddDelegateReference(Src, DelegateHelper,
			                                                           static_cast<MonoObject*>(*Dest));
		}
		else
		{
			*Dest = FCSharpEnvironment::GetEnvironment()->GetDelegateObject(SrcDelegateHelper);
		}
	}
}
