#include "Reflection/Property/StringProperty/FTextPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"

void FTextPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (TextProperty != nullptr)
	{
		const auto FoundMonoClass = FTypeBridge::GetMonoClass(TextProperty);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*TextProperty->GetPropertyValue(Src).ToString())));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*Dest = NewMonoObject;
	}
}

void FTextPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (TextProperty != nullptr)
	{
		const auto SrcObject = static_cast<MonoObject*>(Src);

		const auto SrcValue = FString(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(SrcObject, nullptr))));

		TextProperty->InitializeValue(Dest);

		TextProperty->SetPropertyValue(Dest, FText::FromString(SrcValue));
	}
}

bool FTextPropertyDescriptor::Identical(const void* A, const void* B, uint32 PortFlags) const
{
	if (TextProperty != nullptr)
	{
		const auto StringA = TextProperty->GetPropertyValue(A).ToString();

		const auto StringB = FString(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(static_cast<MonoObject*>(const_cast<void*>(B)), nullptr))));

		return StringA == StringB;
	}

	return false;
}
