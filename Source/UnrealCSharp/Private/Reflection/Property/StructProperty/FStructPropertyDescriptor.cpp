#include "Reflection/Property/StructProperty/FStructPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"

void FStructPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (StructProperty != nullptr)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetObject(Src);

		if (SrcMonoObject == nullptr)
		{
			const auto FoundMonoClass = FTypeBridge::GetMonoClass(StructProperty);

			auto InParams = static_cast<void*>(FoundMonoClass);

			SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass, 1, &InParams);

			FCSharpEnvironment::GetEnvironment()->Bind(StructProperty->Struct, false);

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
