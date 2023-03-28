#include "Reflection/Property/StringProperty/FStrPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"

void FStrPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (StrProperty != nullptr)
	{
		const auto FoundMonoClass = FTypeBridge::GetMonoClass(StrProperty);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_New(
			TCHAR_TO_UTF8(*StrProperty->GetPropertyValue(Src))));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*Dest = NewMonoObject;
	}
}

void FStrPropertyDescriptor::Set(void** Src, void* Dest) const
{
	Set(*reinterpret_cast<MonoObject**>(Src), Dest);
}

void FStrPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (StrProperty != nullptr)
	{
		const auto SrcObject = static_cast<MonoObject*>(Src);

		const auto SrcValue = UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment()->
				GetDomain()->Object_To_String(SrcObject, nullptr)));

		StrProperty->InitializeValue(Dest);

		StrProperty->SetPropertyValue(Dest, SrcValue);
	}
}
