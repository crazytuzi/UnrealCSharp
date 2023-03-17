#include "Reflection/Property/StringProperty/FNamePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"

void FNamePropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (NameProperty != nullptr)
	{
		const auto FoundMonoClass = FTypeBridge::GetMonoClass(NameProperty);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_New(
			TCHAR_TO_UTF8(*NameProperty->GetPropertyValue(Src).ToString())));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*Dest = NewMonoObject;
	}
}

void FNamePropertyDescriptor::Set(void** Src, void* Dest) const
{
	Set(*reinterpret_cast<MonoObject**>(Src), Dest);
}

void FNamePropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (NameProperty != nullptr)
	{
		const auto SrcObject = static_cast<MonoObject*>(Src);

		const auto SrcValue = FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(
			FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_To_String(SrcObject, nullptr));

		NameProperty->InitializeValue(Dest);
		
		NameProperty->SetPropertyValue(Dest, SrcValue);
	}
}
