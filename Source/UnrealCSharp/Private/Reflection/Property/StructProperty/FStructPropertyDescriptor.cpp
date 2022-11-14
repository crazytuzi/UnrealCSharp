#include "Reflection/Property/StructProperty/FStructPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

void FStructPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (StructProperty != nullptr)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetObject(Src);

		if (SrcMonoObject == nullptr)
		{
			auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
				COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_GAME),
				StructProperty->Struct->GetPrefixCPP() + StructProperty->Struct->GetName());

			if (FoundMonoClass == nullptr)
			{
				FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
					COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_ENGINE),
					StructProperty->Struct->GetPrefixCPP() + StructProperty->Struct->GetName());
			}

			auto InParams = static_cast<void*>(FoundMonoClass);

			SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass, 1, &InParams);

			FCSharpEnvironment::GetEnvironment()->AddStructReference(StructProperty->Struct, Src, SrcMonoObject, false);
		}

		*Dest = SrcMonoObject;
	}
}

void FStructPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (StructProperty != nullptr)
	{
		const auto SrcStruct = FCSharpEnvironment::GetEnvironment()->GetStruct(static_cast<MonoObject*>(Src));

		StructProperty->CopySingleValue(Dest, SrcStruct);
	}
}
