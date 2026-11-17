#include "Reflection/Property/FieldPathProperty/FFieldPathPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FFieldPathPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FMember) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetFieldPathObject(Src);

	if (!IManagedHandleIsValid(Object))
	{
		if (Class != nullptr)
		{
			Object = Class->NewObject(true);

			FCSharpEnvironment::GetEnvironment().AddFieldPathReference<false, true>(
				Class, Object, static_cast<FFieldPath*>(Src));
		}
	}

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FFieldPathPropertyDescriptor::Get(void* Src, void** Dest, FPropertyArgument::FReturn) const
{
	auto Object = InvalidManagedHandle;

	if (Class != nullptr)
	{
		Object = Class->NewObject(true);

		FCSharpEnvironment::GetEnvironment().AddFieldPathReference<true, false>(
			Class, Object, static_cast<FFieldPath*>(Src));
	}

	*reinterpret_cast<IManagedHandle*>(Dest) = Object;
}

void FFieldPathPropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcManagedHandle = *static_cast<IManagedHandle*>(Src);

	if (const auto SrcValue = FCSharpEnvironment::GetEnvironment().GetFieldPath(SrcManagedHandle))
	{
		Property->InitializeValue(Dest);

		Property->SetPropertyValue(Dest, *SrcValue);
	}
}

bool FFieldPathPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (const auto FieldPath = FCSharpEnvironment::GetEnvironment().GetFieldPath(
		*static_cast<IManagedHandle*>(const_cast<void*>(B))))
	{
		return Property->Identical(A, FieldPath, PortFlags);
	}

	return false;
}
