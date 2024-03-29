#include "Reflection/Property/StructProperty/FStructPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

FStructPropertyDescriptor::FStructPropertyDescriptor(FProperty* InProperty):
	FCompoundPropertyDescriptor(InProperty)
{
	FCSharpEnvironment::GetEnvironment().Bind(StructProperty->Struct, false);
}

void FStructPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (StructProperty != nullptr)
	{
		*Dest = NewWeakRef(Src);
	}
}

void FStructPropertyDescriptor::Get(void* Src, void* Dest) const
{
	*static_cast<void**>(Dest) = NewRef(Src);
}

void FStructPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (StructProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<FGarbageCollectionHandle>(Src);
		
		if (const auto SrcStruct = FCSharpEnvironment::GetEnvironment().GetStruct(
			SrcMonoObject))
		{
			StructProperty->InitializeValue(Dest);

			StructProperty->CopySingleValue(Dest, SrcStruct);
		}
	}
}

bool FStructPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (StructProperty != nullptr)
	{
		const auto StructA = StructProperty->ContainerPtrToValuePtr<void>(A);

		const auto StructB = FCSharpEnvironment::GetEnvironment().GetStruct(
			static_cast<FGarbageCollectionHandle>(const_cast<void*>(B)));

		return StructProperty->Identical(StructA, StructB, PortFlags);
	}

	return false;
}

MonoObject* FStructPropertyDescriptor::NewRef(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetObject(StructProperty->Struct, InAddress);

	if (Object == nullptr)
	{
		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		const auto OwnerGarbageCollectionHandle = FCSharpEnvironment::GetEnvironment().GetGarbageCollectionHandle(
			InAddress, StructProperty);

		FCSharpEnvironment::GetEnvironment().AddStructReference(OwnerGarbageCollectionHandle, StructProperty->Struct,
		                                                        InAddress, Object);
	}

	return Object;
}

MonoObject* FStructPropertyDescriptor::NewWeakRef(const void* InAddress) const
{
	const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

	FCSharpEnvironment::GetEnvironment().AddStructReference(StructProperty->Struct, InAddress, Object, false);

	return Object;
}
