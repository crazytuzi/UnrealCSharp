#include "Reflection/Property/StringProperty/FStrPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Domain/Script/IManagedHandle.h"

void FStrPropertyDescriptor::Get(void* Src, void** Dest, std::true_type) const
{
	const auto Object = Class->NewObject();

	FCSharpEnvironment::GetEnvironment().AddStringReference<FString, true, false>(
		Class, MANAGED_HANDLE_FROM_OBJECT(Object), Src);

	*Dest = MANAGED_HANDLE_TO_OBJECT(Object);
}

void FStrPropertyDescriptor::Get(void* Src, void** Dest, std::false_type) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetStringObject<FString>(Src);

	if (!IManagedHandleIsValid(Object))
	{
		Object = Class->NewObject();

		FCSharpEnvironment::GetEnvironment().AddStringReference<FString, false, true>(
			Class, MANAGED_HANDLE_FROM_OBJECT(Object), Src);
	}

	*Dest = MANAGED_HANDLE_TO_OBJECT(Object);
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
