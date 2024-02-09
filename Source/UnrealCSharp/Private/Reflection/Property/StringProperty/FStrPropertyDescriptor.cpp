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
		*Dest = Object_New(Src);
	}
}

void FStrPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (StrProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		if (const auto SrcValue = FCSharpEnvironment::GetEnvironment().GetString<FString>(SrcMonoObject))
		{
			StrProperty->InitializeValue(Dest);

			StrProperty->SetPropertyValue(Dest, *SrcValue);
		}
	}
}

bool FStrPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (StrProperty != nullptr)
	{
		const auto StringA = StrProperty->GetPropertyValue(A);

		const auto StringB = FCSharpEnvironment::GetEnvironment().GetString<FString>(
			static_cast<MonoObject*>(const_cast<void*>(B)));

		return StringA == *StringB;
	}

	return false;
}

MonoObject* FStrPropertyDescriptor::Object_New(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetStringObject<FString>(InAddress);

	if (Object == nullptr)
	{
		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		FCSharpEnvironment::GetEnvironment().AddStringReference<FString>(Object, InAddress, false);
	}

	return Object;
}
