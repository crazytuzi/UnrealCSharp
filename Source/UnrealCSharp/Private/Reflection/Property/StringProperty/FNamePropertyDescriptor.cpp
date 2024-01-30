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
		*Dest = Object_New(Src);
	}
}

void FNamePropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (NameProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		if (const auto SrcValue = FCSharpEnvironment::GetEnvironment().GetString<FName>(SrcMonoObject))
		{
			NameProperty->InitializeValue(Dest);

			NameProperty->SetPropertyValue(Dest, *SrcValue);
		}
	}
}

bool FNamePropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (NameProperty != nullptr)
	{
		const auto NameA = NameProperty->GetPropertyValue(A);

		const auto NameB = FCSharpEnvironment::GetEnvironment().GetString<FName>(
			static_cast<MonoObject*>(const_cast<void*>(B)));

		return NameA == *NameB;
	}

	return false;
}

MonoObject* FNamePropertyDescriptor::Object_New(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetStringObject<FName>(InAddress);

	if (Object == nullptr)
	{
		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		FCSharpEnvironment::GetEnvironment().AddStringReference<FName>(Object, InAddress, false);
	}

	return Object;
}
