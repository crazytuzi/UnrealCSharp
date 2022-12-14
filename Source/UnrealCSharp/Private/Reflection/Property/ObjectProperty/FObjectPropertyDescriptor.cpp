#include "Reflection/Property/ObjectProperty/FObjectPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FObjectPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (ObjectProperty != nullptr)
	{
		const auto SrcObject = ObjectProperty->GetObjectPropertyValue(Src);

		const auto SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetObject(SrcObject);

		*Dest = SrcMonoObject;
	}
}

void FObjectPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (ObjectProperty != nullptr)
	{
		const auto SrcObject = FCSharpEnvironment::GetEnvironment()->GetObject(static_cast<MonoObject*>(Src));

		ObjectProperty->SetObjectPropertyValue(Dest, SrcObject);
	}
}
