#include "Reflection/Property/ObjectProperty/FObjectPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FObjectPropertyDescriptor::Get(void* Src, void* Dest) const
{
	if (ObjectProperty != nullptr)
	{
		const auto SrcObject = ObjectProperty->GetObjectPropertyValue(Src);

		const auto SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetObject(SrcObject);

		const auto DestMonoObject = static_cast<MonoObject**>(Dest);

		*DestMonoObject = SrcMonoObject;
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

bool FObjectPropertyDescriptor::IsPointerProperty() const
{
	return true;
}
