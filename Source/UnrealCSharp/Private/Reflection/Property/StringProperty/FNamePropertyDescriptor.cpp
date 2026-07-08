#include "Reflection/Property/StringProperty/FNamePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FNamePropertyDescriptor::Get(void* Src, void** Dest, std::true_type) const
{
	const auto Object = Class->NewObject();

	FCSharpEnvironment::GetEnvironment().AddStringReference<FName, true, false>(
		Class, Object, Src);

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FNamePropertyDescriptor::Get(void* Src, void** Dest, std::false_type) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetStringObject<FName>(Src);

	if (!IManagedHandleIsValid(Object))
	{
		Object = Class->NewObject();

		FCSharpEnvironment::GetEnvironment().AddStringReference<FName, false, true>(
			Class, Object, Src);
	}

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FNamePropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcManagedHandle = *static_cast<IManagedHandle*>(Src);

	if (const auto SrcValue = FCSharpEnvironment::GetEnvironment().GetString<FName>(SrcManagedHandle))
	{
		Property->InitializeValue(Dest);

		Property->SetPropertyValue(Dest, *SrcValue);
	}
}

bool FNamePropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	const auto NameA = Property->GetPropertyValue(A);

	const auto NameB = FCSharpEnvironment::GetEnvironment().GetString<FName>(
		*static_cast<IManagedHandle*>(const_cast<void*>(B)));

	return NameA == *NameB;
}
