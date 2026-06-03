#include "Reflection/Property/StringProperty/FAnsiStrPropertyDescriptor.h"
#if UE_F_ANSI_STR_PROPERTY
#include "Environment/FCSharpEnvironment.h"
#include "Domain/Script/IManagedHandle.h"

void FAnsiStrPropertyDescriptor::Get(void* Src, void** Dest, std::true_type) const
{
	const auto Object = Class->NewObject();

	FCSharpEnvironment::GetEnvironment().AddStringReference<FAnsiString, true, false>(
		Class, MANAGED_HANDLE_FROM_OBJECT(Object), Src);

	*Dest = MANAGED_HANDLE_TO_OBJECT(Object);
}

void FAnsiStrPropertyDescriptor::Get(void* Src, void** Dest, std::false_type) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetStringObject<FAnsiString>(Src);

	if (!IManagedHandleIsValid(Object))
	{
		Object = Class->NewObject();

		FCSharpEnvironment::GetEnvironment().AddStringReference<FAnsiString, false, true>(
			Class, MANAGED_HANDLE_FROM_OBJECT(Object), Src);
	}

	*Dest = MANAGED_HANDLE_TO_OBJECT(Object);
}

void FAnsiStrPropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcManagedHandle = *static_cast<IManagedHandle*>(Src);

	if (const auto SrcValue = FCSharpEnvironment::GetEnvironment().GetString<FAnsiString>(SrcManagedHandle))
	{
		Property->InitializeValue(Dest);

		Property->SetPropertyValue(Dest, *SrcValue);
	}
}

bool FAnsiStrPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	const auto AnsiStringA = Property->GetPropertyValue(A);

	const auto AnsiStringB = FCSharpEnvironment::GetEnvironment().GetString<FAnsiString>(
		*static_cast<IManagedHandle*>(const_cast<void*>(B)));

	return AnsiStringA == *AnsiStringB;
}
#endif
