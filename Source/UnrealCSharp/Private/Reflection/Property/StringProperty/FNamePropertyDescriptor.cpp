#include "Reflection/Property/StringProperty/FNamePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FNamePropertyDescriptor::Get(void* Src, void** Dest, std::true_type) const
{
	const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

	FCSharpEnvironment::GetEnvironment().AddStringReference<FName, true>(Object, Src);

	*Dest = Object;
}

void FNamePropertyDescriptor::Get(void* Src, void** Dest, std::false_type) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetStringObject<FName>(Src);

	if (Object == nullptr)
	{
		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		FCSharpEnvironment::GetEnvironment().AddStringReference<FName, false>(Object, Src);
	}

	*Dest = Object;
}

void FNamePropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcGarbageCollectionHandle = *static_cast<FGarbageCollectionHandle*>(Src);

	if (const auto SrcValue = FCSharpEnvironment::GetEnvironment().GetString<FName>(
		SrcGarbageCollectionHandle))
	{
		Property->InitializeValue(Dest);

		Property->SetPropertyValue(Dest, *SrcValue);
	}
}

bool FNamePropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	const auto NameA = Property->GetPropertyValue(A);

	const auto NameB = FCSharpEnvironment::GetEnvironment().GetString<FName>(
		*static_cast<FGarbageCollectionHandle*>(const_cast<void*>(B)));

	return NameA == *NameB;
}
