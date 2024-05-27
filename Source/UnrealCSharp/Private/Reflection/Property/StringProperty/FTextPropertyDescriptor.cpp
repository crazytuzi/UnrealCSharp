#include "Reflection/Property/StringProperty/FTextPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FTextPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (Property != nullptr)
	{
		*Dest = NewWeakRef(Src);
	}
}

void FTextPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (Property != nullptr)
	{
		const auto SrcGarbageCollectionHandle = static_cast<FGarbageCollectionHandle>(Src);

		if (const auto SrcValue = FCSharpEnvironment::GetEnvironment().GetString<FText>(
			SrcGarbageCollectionHandle))
		{
			Property->InitializeValue(Dest);

			Property->SetPropertyValue(Dest, *SrcValue);
		}
	}
}

bool FTextPropertyDescriptor::Identical(const void* A, const void* B, uint32 PortFlags) const
{
	if (Property != nullptr)
	{
		const auto TextA = Property->GetPropertyValue(A);

		const auto TextB = FCSharpEnvironment::GetEnvironment().GetString<FText>(
			static_cast<FGarbageCollectionHandle>(const_cast<void*>(B)));

		return TextA.EqualTo(*TextB);
	}

	return false;
}

MonoObject* FTextPropertyDescriptor::NewWeakRef(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetStringObject<FText>(InAddress);

	if (Object == nullptr)
	{
		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		FCSharpEnvironment::GetEnvironment().AddStringReference<FText>(Object, InAddress, false);
	}

	return Object;
}
