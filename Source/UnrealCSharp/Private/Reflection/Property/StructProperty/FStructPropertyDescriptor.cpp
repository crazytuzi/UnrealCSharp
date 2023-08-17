#include "Reflection/Property/StructProperty/FStructPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"
#include "Template/TGetArrayLength.inl"

void FStructPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (StructProperty != nullptr)
	{
		*Dest = Object_New(Src);
	}
}

void FStructPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (StructProperty != nullptr)
	{
		const auto SrcStruct = FCSharpEnvironment::GetEnvironment().GetStruct(static_cast<MonoObject*>(Src));

		StructProperty->InitializeValue(Dest);

		StructProperty->CopySingleValue(Dest, SrcStruct);
	}
}

bool FStructPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (StructProperty != nullptr)
	{
		const auto StructA = StructProperty->ContainerPtrToValuePtr<void>(A);

		const auto StructB = FCSharpEnvironment::GetEnvironment().GetStruct(
			static_cast<MonoObject*>(const_cast<void*>(B)));

		return StructProperty->Identical(StructA, StructB, PortFlags);
	}

	return false;
}

void* FStructPropertyDescriptor::GetOwner(void* InAddress) const
{
	if (StructProperty != nullptr)
	{
		return static_cast<uint8*>(InAddress) - StructProperty->GetOffset_ForInternal();
	}

	return nullptr;
}

MonoObject* FStructPropertyDescriptor::Object_New(void* InAddress) const
{
	auto Object = FCSharpEnvironment::GetEnvironment().GetObject(GetOwner(InAddress), InAddress);

	if (Object == nullptr)
	{
		const auto FoundMonoClass = FTypeBridge::GetMonoClass(StructProperty);

		auto InParams = static_cast<void*>(FoundMonoClass);

		Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, TGetArrayLength(InParams), &InParams);

		FCSharpEnvironment::GetEnvironment().Bind(StructProperty->Struct, false);

		FCSharpEnvironment::GetEnvironment().AddStructReference(StructProperty->Struct, GetOwner(InAddress), InAddress,
		                                                        Object, false);
	}

	return Object;
}
