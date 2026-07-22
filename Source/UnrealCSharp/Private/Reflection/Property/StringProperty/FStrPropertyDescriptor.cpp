#include "Reflection/Property/StringProperty/FStrPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FStrPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FMember) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetStringObject<FString>(Src);

	if (!IManagedHandleIsValid(Object))
	{
		Object = Class->NewObject();

		FCSharpEnvironment::GetEnvironment().AddStringReference<FString, false, true>(
			Class, Object, Src);
	}

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FStrPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FReturn) const
{
	const auto Object = Class->NewObject();

	FCSharpEnvironment::GetEnvironment().AddStringReference<FString, true, false>(
		Class, Object, Src);

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FStrPropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcManagedHandle = *static_cast<IManagedHandle*>(Src);

	if (const auto SrcValue = FCSharpEnvironment::GetEnvironment().GetString<FString>(SrcManagedHandle))
	{
		Property->InitializeValue(Dest);

		Property->SetPropertyValue(Dest, *SrcValue);
	}
}

bool FStrPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	const auto StringA = Property->GetPropertyValue(A);

	const auto StringB = FCSharpEnvironment::GetEnvironment().GetString<FString>(
		*static_cast<IManagedHandle*>(const_cast<void*>(B)));

	return StringA == *StringB;
}
