#include "Reflection/Property/DelegateProperty/FMulticastDelegatePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"
#include "Reflection/Delegate/FMulticastDelegateHelper.h"

void FMulticastDelegatePropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (MulticastDelegateProperty != nullptr)
	{
		const auto SrcMulticastDelegateHelper = FCSharpEnvironment::GetEnvironment()->GetDelegate<
			FMulticastDelegateHelper>(Src);

		if (SrcMulticastDelegateHelper == nullptr)
		{
			auto MonoClassName = MulticastDelegateProperty->SignatureFunction->GetName();

			MonoClassName.LeftChopInline(FString(HEADER_GENERATED_DELEGATE_SIGNATURE_SUFFIX).Len(), false);

			auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
				COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_GAME), MonoClassName);

			if (FoundMonoClass == nullptr)
			{
				FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
					COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_ENGINE), MonoClassName);
			}

			const auto MulticastDelegateHelper = new FMulticastDelegateHelper(
				static_cast<FMulticastScriptDelegate*>(Src), MulticastDelegateProperty->SignatureFunction);

			void* Param[1] = {Src};

			*Dest = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass, 1, Param);

			FCSharpEnvironment::GetEnvironment()->AddDelegateReference(Src, MulticastDelegateHelper,
			                                                           static_cast<MonoObject*>(*Dest));
		}
		else
		{
			*Dest = FCSharpEnvironment::GetEnvironment()->GetDelegateObject(SrcMulticastDelegateHelper);
		}
	}
}
