#include "Reflection/Property/StringProperty/FStrPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FStrPropertyDescriptor::Get(void* Src, void** Dest, const bool bIsCopy) const
{
	if (Property != nullptr)
	{
		*Dest = NewWeakRef(Src, bIsCopy);
	}
}

void FStrPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (Property != nullptr)
	{
		const auto SrcGarbageCollectionHandle = *static_cast<FGarbageCollectionHandle*>(Src);

		if (const auto SrcValue = FCSharpEnvironment::GetEnvironment().GetString<FString>(
			SrcGarbageCollectionHandle))
		{
			Property->InitializeValue(Dest);

			Property->SetPropertyValue(Dest, *SrcValue);
		}
	}
}

bool FStrPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (Property != nullptr)
	{
		const auto StringA = Property->GetPropertyValue(A);

		const auto StringB = FCSharpEnvironment::GetEnvironment().GetString<FString>(
			*static_cast<FGarbageCollectionHandle*>(const_cast<void*>(B)));

		return StringA == *StringB;
	}

	return false;
}

MonoObject* FStrPropertyDescriptor::NewWeakRef(void* InAddress, const bool bIsCopy) const
{
	if (bIsCopy)
	{
		const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		FCSharpEnvironment::GetEnvironment().AddStringReference<FString, true>(Object, InAddress);

		return Object;
	}
	else
	{
		auto Object = FCSharpEnvironment::GetEnvironment().GetStringObject<FString>(InAddress);

		if (Object == nullptr)
		{
			Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

			FCSharpEnvironment::GetEnvironment().AddStringReference<FString, false>(Object, InAddress);
		}

		return Object;
	}
}
