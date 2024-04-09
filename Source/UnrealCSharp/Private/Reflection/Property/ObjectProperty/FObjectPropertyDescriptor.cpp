﻿#include "Reflection/Property/ObjectProperty/FObjectPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

void FObjectPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (ObjectProperty != nullptr)
	{
		const auto SrcObject = ObjectProperty->GetObjectPropertyValue(Src);

		*Dest = FCSharpEnvironment::GetEnvironment().Bind(SrcObject);
	}
}

void FObjectPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (ObjectProperty != nullptr)
	{
		const auto SrcGarbageCollectionHandle = static_cast<FGarbageCollectionHandle>(Src);

		const auto SrcObject = FCSharpEnvironment::GetEnvironment().GetObject(
			SrcGarbageCollectionHandle);

		ObjectProperty->InitializeValue(Dest);

		ObjectProperty->SetObjectPropertyValue(Dest, SrcObject);
	}
}

bool FObjectPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (ObjectProperty != nullptr)
	{
		const auto ObjectA = ObjectProperty->GetObjectPropertyValue(A);

		const auto ObjectB = FCSharpEnvironment::GetEnvironment().GetObject(
			static_cast<FGarbageCollectionHandle>(const_cast<void*>(B)));

		return ObjectProperty->StaticIdentical(ObjectA, ObjectB, PortFlags);
	}

	return false;
}
