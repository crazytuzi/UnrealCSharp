#include "Reflection/Property/StringProperty/FStrPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/NamespaceMacro.h"

void FStrPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (StrProperty != nullptr)
	{
		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_ENGINE), CLASS_F_STRING);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_New(
			TCHAR_TO_UTF8(*StrProperty->GetPropertyValue(Src))));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*Dest = NewMonoObject;
	}
}

void FStrPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (StrProperty != nullptr)
	{
		const auto SrcObject = static_cast<MonoObject*>(Src);

		const auto SrcValue = FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(
			FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_To_String(SrcObject, nullptr));

		StrProperty->SetPropertyValue(Dest, SrcValue);
	}
}
