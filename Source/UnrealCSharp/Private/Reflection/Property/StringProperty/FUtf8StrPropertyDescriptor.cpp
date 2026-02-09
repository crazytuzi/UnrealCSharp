#include "Reflection/Property/StringProperty/FUtf8StrPropertyDescriptor.h"
#if UE_F_UTF8_STR_PROPERTY
#include "Environment/FCSharpEnvironment.h"

void FUtf8StrPropertyDescriptor::Get(void* Src, void** Dest, std::true_type) const
{
	const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

	FCSharpEnvironment::GetEnvironment().AddStringReference<FUtf8String, true, false>(Class, Object, Src);

	*Dest = Object;
}

void FUtf8StrPropertyDescriptor::Get(void* Src, void** Dest, std::false_type) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetStringObject<FUtf8String>(Src);

	if (Object == nullptr)
	{
		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		FCSharpEnvironment::GetEnvironment().AddStringReference<FUtf8String, false, true>(Class, Object, Src);
	}

	*Dest = Object;
}

void FUtf8StrPropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcGarbageCollectionHandle = *static_cast<FGarbageCollectionHandle*>(Src);

	if (const auto SrcValue = FCSharpEnvironment::GetEnvironment().GetString<FUtf8String>(
		SrcGarbageCollectionHandle))
	{
		Property->InitializeValue(Dest);

		Property->SetPropertyValue(Dest, *SrcValue);
	}
}

bool FUtf8StrPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	const auto Utf8StringA = Property->GetPropertyValue(A);

	const auto Utf8StringB = FCSharpEnvironment::GetEnvironment().GetString<FUtf8String>(
		*static_cast<FGarbageCollectionHandle*>(const_cast<void*>(B)));

	return Utf8StringA == *Utf8StringB;
}
#endif
