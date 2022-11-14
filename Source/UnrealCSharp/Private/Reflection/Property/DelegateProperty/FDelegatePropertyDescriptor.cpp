#include "Reflection/Property/DelegateProperty/FDelegatePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"
#include "Reflection/Delegate/FDelegateHelper.h"

void FDelegatePropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (DelegateProperty != nullptr)
	{
		const auto SrcDelegateHelper = FCSharpEnvironment::GetEnvironment()->GetDelegate<FDelegateHelper>(Src);

		if (SrcDelegateHelper == nullptr)
		{
			auto MonoClassName = DelegateProperty->SignatureFunction->GetName();

			MonoClassName.LeftChopInline(FString(HEADER_GENERATED_DELEGATE_SIGNATURE_SUFFIX).Len(), false);

			auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
				COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_GAME), MonoClassName);

			if (FoundMonoClass == nullptr)
			{
				FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
					COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_ENGINE), MonoClassName);
			}

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
