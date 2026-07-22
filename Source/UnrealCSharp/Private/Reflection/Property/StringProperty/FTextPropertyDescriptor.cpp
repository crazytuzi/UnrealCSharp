#include "Reflection/Property/StringProperty/FTextPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FTextPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FMember) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetStringObject<FText>(Src);

	if (!IManagedHandleIsValid(Object))
	{
		Object = Class->NewObject();

		FCSharpEnvironment::GetEnvironment().AddStringReference<FText, false, true>(
			Class, Object, Src);
	}

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FTextPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FReturn) const
{
	const auto Object = Class->NewObject();

	FCSharpEnvironment::GetEnvironment().AddStringReference<FText, true, false>(
		Class, Object, Src);

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FTextPropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcManagedHandle = *static_cast<IManagedHandle*>(Src);

	if (const auto SrcValue = FCSharpEnvironment::GetEnvironment().GetString<FText>(SrcManagedHandle))
	{
		Property->InitializeValue(Dest);

		Property->SetPropertyValue(Dest, *SrcValue);
	}
}

bool FTextPropertyDescriptor::Identical(const void* A, const void* B, uint32 PortFlags) const
{
	const auto TextA = Property->GetPropertyValue(A);

	const auto TextB = FCSharpEnvironment::GetEnvironment().GetString<FText>(
		*static_cast<IManagedHandle*>(const_cast<void*>(B)));

	return TextA.EqualTo(*TextB);
}
