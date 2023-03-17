#include "Reflection/Property/ObjectProperty/FObjectPropertyDescriptor.h"
#include "Bridge/FTypeBridge.h"
#include "Environment/FCSharpEnvironment.h"

void FObjectPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (ObjectProperty != nullptr)
	{
		const auto SrcObject = ObjectProperty->GetObjectPropertyValue(Src);

		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetObject(SrcObject);

		if (SrcMonoObject == nullptr)
		{
			const auto FoundMonoClass = FTypeBridge::GetMonoClass(ObjectProperty);

			SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass);

			FCSharpEnvironment::GetEnvironment()->Bind(ObjectProperty->PropertyClass, false);
		}

		*Dest = SrcMonoObject;
	}
}

void FObjectPropertyDescriptor::Set(void** Src, void* Dest) const
{
	Set(*reinterpret_cast<MonoObject**>(Src), Dest);
}

void FObjectPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (ObjectProperty != nullptr)
	{
		const auto SrcObject = FCSharpEnvironment::GetEnvironment()->GetObject(static_cast<MonoObject*>(Src));

		ObjectProperty->SetObjectPropertyValue(Dest, SrcObject);
	}
}
