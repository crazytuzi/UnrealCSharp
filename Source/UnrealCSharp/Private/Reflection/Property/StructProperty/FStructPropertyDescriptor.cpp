#include "Reflection/Property/StructProperty/FStructPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/NamespaceMacro.h"

void FStructPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (StructProperty != nullptr)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetObject(Src);

		if (SrcMonoObject == nullptr)
		{
			auto FoundClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
				COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_GAME),
				StructProperty->Struct->GetPrefixCPP() + StructProperty->Struct->GetName());

			if (FoundClass == nullptr)
			{
				FoundClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
					COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_ENGINE),
					StructProperty->Struct->GetPrefixCPP() + StructProperty->Struct->GetName());
			}

			const auto FoundIntPtrClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
				COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_FUNCTION), CLASS_INT_PTR);

			auto NewIntPtr = static_cast<void*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
				FoundIntPtrClass, 1, &Src));

			SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundClass, 1, &NewIntPtr);

			FCSharpEnvironment::GetEnvironment()->AddStructReference(StructProperty->Struct, Src, SrcMonoObject, false);
		}

		*Dest = SrcMonoObject;
	}
}

void FStructPropertyDescriptor::Get(void* Src, void* Dest) const
{
	if (StructProperty != nullptr)
	{
		Get(Src, static_cast<void**>(Dest));
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
