#include "Reflection/Property/ObjectProperty/FObjectPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FObjectPropertyDescriptor::Get(void* Src, void* Dest) const
{
	const auto SrcMonoObject = static_cast<MonoObject*>(Src);

	const auto DestMonoObject = static_cast<MonoObject**>(Dest);

	*DestMonoObject = SrcMonoObject;
}

void FObjectPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (ObjectProperty != nullptr)
	{
		ObjectProperty->SetObjectPropertyValue(Dest, static_cast<UObject*>(Src));
	}
}

void FObjectPropertyDescriptor::Get(UObject* Src, void* Dest) const
{
	if (ObjectProperty != nullptr)
	{
		if (const auto Object = ObjectProperty->GetObjectPropertyValue(Property->ContainerPtrToValuePtr<void>(Src)))
		{
			if (const auto FoundMonoObject = FCSharpEnvironment::GetEnvironment()->GetObject(Object))
			{
				Get(FoundMonoObject, Dest);
			}
		}
	}
}

void FObjectPropertyDescriptor::Set(void* Src, UObject* Dest) const
{
	if (ObjectProperty != nullptr)
	{
		if (const auto FoundObject = FCSharpEnvironment::GetEnvironment()->GetObject(static_cast<MonoObject*>(Src)))
		{
			Set(FoundObject, ObjectProperty->ContainerPtrToValuePtr<void>(Dest));
		}
	}
}
