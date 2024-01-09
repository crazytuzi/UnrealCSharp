#include "Reflection/Property/StringProperty/FTextPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"

FTextPropertyDescriptor::FTextPropertyDescriptor(FProperty* InProperty):
	FPropertyDescriptor(InProperty),
	Class(nullptr)
{
	Class = FTypeBridge::GetMonoClass(TextProperty);
}

void FTextPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (TextProperty != nullptr)
	{
		*Dest = Object_New(Src);
	}
}

void FTextPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (TextProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcValue = FCSharpEnvironment::GetEnvironment().GetString<FText>(SrcMonoObject);

		TextProperty->InitializeValue(Dest);

		TextProperty->SetPropertyValue(Dest, *SrcValue);
	}
}

bool FTextPropertyDescriptor::Identical(const void* A, const void* B, uint32 PortFlags) const
{
	if (TextProperty != nullptr)
	{
		const auto TextA = TextProperty->GetPropertyValue(A);

		const auto TextB = FCSharpEnvironment::GetEnvironment().GetString<FText>(
			static_cast<MonoObject*>(const_cast<void*>(B)));

		return TextA.EqualTo(*TextB);
	}

	return false;
}

MonoObject* FTextPropertyDescriptor::Object_New(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetStringObject<FText>(InAddress);

	if (Object == nullptr)
	{
		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Init(Class);

		FCSharpEnvironment::GetEnvironment().AddStringReference<FText>(Object, InAddress, false);
	}

	return Object;
}
