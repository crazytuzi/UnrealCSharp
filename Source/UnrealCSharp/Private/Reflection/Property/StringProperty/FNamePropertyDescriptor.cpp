#include "Reflection/Property/StringProperty/FNamePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"

FNamePropertyDescriptor::FNamePropertyDescriptor(FProperty* InProperty):
	FPropertyDescriptor(InProperty),
	Class(nullptr)
{
	Class = FTypeBridge::GetMonoClass(NameProperty);
}

void FNamePropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (NameProperty != nullptr)
	{
		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*NameProperty->GetPropertyValue(Src).ToString())));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Init(
			Class, 1, &NewMonoString);

		*Dest = NewMonoObject;
	}
}

void FNamePropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (NameProperty != nullptr)
	{
		const auto SrcObject = static_cast<MonoObject*>(Src);

		const auto SrcValue = FName(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(SrcObject, nullptr))));

		NameProperty->InitializeValue(Dest);

		NameProperty->SetPropertyValue(Dest, SrcValue);
	}
}

bool FNamePropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (NameProperty != nullptr)
	{
		const auto NameA = NameProperty->GetPropertyValue(A);

		const auto NameB = FName(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(static_cast<MonoObject*>(const_cast<void*>(B)), nullptr))));

		return NameA == NameB;
	}

	return false;
}
