#include "Reflection/Property/StringProperty/FStrPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"

FStrPropertyDescriptor::FStrPropertyDescriptor(FProperty* InProperty):
	FPropertyDescriptor(InProperty),
	Class(nullptr)
{
	Class = FTypeBridge::GetMonoClass(StrProperty);
}

void FStrPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (StrProperty != nullptr)
	{
		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*StrProperty->GetPropertyValue(Src))));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			Class, 1, &NewMonoString);

		*Dest = NewMonoObject;
	}
}

void FStrPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (StrProperty != nullptr)
	{
		const auto SrcObject = static_cast<MonoObject*>(Src);

		const auto SrcValue = FString(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(SrcObject, nullptr))));

		StrProperty->InitializeValue(Dest);

		StrProperty->SetPropertyValue(Dest, SrcValue);
	}
}

bool FStrPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (StrProperty != nullptr)
	{
		const auto StringA = StrProperty->GetPropertyValue(A);

		const auto StringB = UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(static_cast<MonoObject*>(const_cast<void*>(B)), nullptr)));

		return StringA == StringB;
	}

	return false;
}
