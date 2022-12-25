#include "Reflection/Property/StringProperty/FTextPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/NamespaceMacro.h"

void FTextPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (TextProperty != nullptr)
	{
		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_TEXT);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_New(
			TCHAR_TO_UTF8(*TextProperty->GetPropertyValue(Src).ToString())));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*Dest = NewMonoObject;
	}
}

void FTextPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (TextProperty != nullptr)
	{
		const auto SrcObject = static_cast<MonoObject*>(Src);

		const auto SrcValue = FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(
			FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_To_String(SrcObject, nullptr));

		TextProperty->SetPropertyValue(Dest, FText::FromString(SrcValue));
	}
}
