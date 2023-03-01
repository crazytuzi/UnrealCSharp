#include "Reflection/Property/ObjectProperty/FObjectPropertyDescriptor.h"
#include "FUnrealCSharpFunctionLibrary.h"
#include "Environment/FCSharpEnvironment.h"

void FObjectPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (ObjectProperty != nullptr)
	{
		const auto SrcObject = ObjectProperty->GetObjectPropertyValue(Src);

		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetObject(SrcObject);

		if (SrcMonoObject == nullptr)
		{
			const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
				FUnrealCSharpFunctionLibrary::GetClassNameSpace(SrcObject->GetClass()),
				FUnrealCSharpFunctionLibrary::GetFullClass(SrcObject->GetClass()));

			SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass);

			FCSharpEnvironment::GetEnvironment()->Bind(SrcObject->GetClass(), false);
		}

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
