#include "Reflection/Property/StringProperty/FNamePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FNamePropertyDescriptor::Get(void* Src, void** Dest, const bool bIsCopy) const
{
	if (Property != nullptr)
	{
		*Dest = NewWeakRef(Src, bIsCopy);
	}
}

void FNamePropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (Property != nullptr)
	{
		const auto SrcGarbageCollectionHandle = *static_cast<FGarbageCollectionHandle*>(Src);

		if (const auto SrcValue = FCSharpEnvironment::GetEnvironment().GetString<FName>(
			SrcGarbageCollectionHandle))
		{
			Property->InitializeValue(Dest);

			Property->SetPropertyValue(Dest, *SrcValue);
		}
	}
}

bool FNamePropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (Property != nullptr)
	{
		const auto NameA = Property->GetPropertyValue(A);

		const auto NameB = FCSharpEnvironment::GetEnvironment().GetString<FName>(
			*static_cast<FGarbageCollectionHandle*>(const_cast<void*>(B)));

		return NameA == *NameB;
	}

	return false;
}

MonoObject* FNamePropertyDescriptor::NewWeakRef(void* InAddress, const bool bIsCopy) const
{
	if (bIsCopy)
	{
		const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		FCSharpEnvironment::GetEnvironment().AddStringReference<FName, true>(Object, InAddress);

		return Object;
	}
	else
	{
		auto Object = FCSharpEnvironment::GetEnvironment().GetStringObject<FName>(InAddress);

		if (Object == nullptr)
		{
			Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

			FCSharpEnvironment::GetEnvironment().AddStringReference<FName, false>(Object, InAddress);
		}

		return Object;
	}
}
