#include "Reflection/Property/StringProperty/FAnsiStrPropertyDescriptor.h"
#if UE_F_ANSI_STR_PROPERTY
#include "Environment/FCSharpEnvironment.h"

void FAnsiStrPropertyDescriptor::Get(void* Src, void** Dest, std::true_type) const
{
	const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

	FCSharpEnvironment::GetEnvironment().AddStringReference<FAnsiString, true, false>(Object, Src);

	*Dest = Object;
}

void FAnsiStrPropertyDescriptor::Get(void* Src, void** Dest, std::false_type) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetStringObject<FAnsiString>(Src);

	if (Object == nullptr)
	{
		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		FCSharpEnvironment::GetEnvironment().AddStringReference<FAnsiString, false, true>(Object, Src);
	}

	*Dest = Object;
}

void FAnsiStrPropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcGarbageCollectionHandle = *static_cast<FGarbageCollectionHandle*>(Src);

	if (const auto SrcValue = FCSharpEnvironment::GetEnvironment().GetString<FAnsiString>(
		SrcGarbageCollectionHandle))
	{
		Property->InitializeValue(Dest);

		Property->SetPropertyValue(Dest, *SrcValue);
	}
}

bool FAnsiStrPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	const auto AnsiStringA = Property->GetPropertyValue(A);

	const auto AnsiStringB = FCSharpEnvironment::GetEnvironment().GetString<FAnsiString>(
		*static_cast<FGarbageCollectionHandle*>(const_cast<void*>(B)));

	return AnsiStringA == *AnsiStringB;
}
#endif
