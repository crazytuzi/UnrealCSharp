#include "Reflection/Property/StringProperty/FNamePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/NamespaceMacro.h"

void FNamePropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (NameProperty != nullptr)
	{
		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_ENGINE), CLASS_F_NAME);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_New(
			TCHAR_TO_UTF8(*NameProperty->GetPropertyValue(Src).ToString())));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*Dest = NewMonoObject;
	}
}

void FNamePropertyDescriptor::Get(void* Src, void* Dest) const
{
	if (NameProperty != nullptr)
	{
		Get(Src, static_cast<void**>(Dest));
	}
}

void FNamePropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (NameProperty != nullptr)
	{
		const auto SrcObject = static_cast<MonoObject*>(Src);

		const auto SrcValue = FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(
			FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_To_String(SrcObject, nullptr));

		NameProperty->SetPropertyValue(Dest, SrcValue);
	}
}
