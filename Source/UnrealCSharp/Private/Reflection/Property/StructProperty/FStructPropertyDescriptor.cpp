#include "Reflection/Property/StructProperty/FStructPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

FStructPropertyDescriptor::FStructPropertyDescriptor(FStructProperty* InProperty):
	TCompoundPropertyDescriptor(InProperty)
{
	FCSharpEnvironment::GetEnvironment().Bind<false>(InProperty->Struct);
}

void FStructPropertyDescriptor::Get(void* Src, void** Dest, std::true_type) const
{
	const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

	FCSharpEnvironment::GetEnvironment().AddStructReference<true>(Property->Struct, Src, Object);

	*Dest = Object;
}

void FStructPropertyDescriptor::Get(void* Src, void** Dest, std::false_type) const
{
	const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

	FCSharpEnvironment::GetEnvironment().AddStructReference<false>(Property->Struct, Src, Object);

	*Dest = Object;
}

void FStructPropertyDescriptor::Get(void* Src, void* Dest) const
{
	*static_cast<void**>(Dest) = NewRef(Src);
}

void FStructPropertyDescriptor::Set(void* Src, void* Dest) const
{
	const auto SrcGarbageCollectionHandle = *static_cast<FGarbageCollectionHandle*>(Src);

	if (const auto SrcStruct = FCSharpEnvironment::GetEnvironment().GetStruct(
		SrcGarbageCollectionHandle))
	{
		Property->InitializeValue(Dest);

		Property->CopySingleValue(Dest, SrcStruct);
	}
}

bool FStructPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	const auto StructA = Property->ContainerPtrToValuePtr<void>(A);

	const auto StructB = FCSharpEnvironment::GetEnvironment().GetStruct(
		*static_cast<FGarbageCollectionHandle*>(const_cast<void*>(B)));

	return Property->Identical(StructA, StructB, PortFlags);
}

MonoObject* FStructPropertyDescriptor::NewRef(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetObject(Property->Struct, InAddress);

	if (Object == nullptr)
	{
		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(Class);

		const auto OwnerGarbageCollectionHandle = FCSharpEnvironment::GetEnvironment().GetGarbageCollectionHandle(
			InAddress, Property);

		FCSharpEnvironment::GetEnvironment().AddStructReference(OwnerGarbageCollectionHandle, Property->Struct,
		                                                        InAddress, Object);
	}

	return Object;
}
