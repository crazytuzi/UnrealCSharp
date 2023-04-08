#include "Reflection/Property/StructProperty/FStructPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Bridge/FTypeBridge.h"
#include "Template/TGetArrayLength.h"

void FStructPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (StructProperty != nullptr)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetObject(Src);

		if (SrcMonoObject == nullptr)
		{
			SrcMonoObject = Object_New(Src);
		}

		*Dest = SrcMonoObject;
	}
}

void FStructPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (StructProperty != nullptr)
	{
		const auto SrcStruct = FCSharpEnvironment::GetEnvironment()->GetStruct(static_cast<MonoObject*>(Src));

		FCSharpEnvironment::GetEnvironment()->RemoveStructReference(Dest);

		StructProperty->InitializeValue(Dest);

		StructProperty->CopySingleValue(Dest, SrcStruct);

		Object_New(Dest);
	}
}

bool FStructPropertyDescriptor::Identical(const void* A, const void* B, const uint32 PortFlags) const
{
	if (StructProperty != nullptr)
	{
		const auto StructA = StructProperty->ContainerPtrToValuePtr<void>(A);

		const auto StructB = FCSharpEnvironment::GetEnvironment()->GetStruct(
			static_cast<MonoObject*>(const_cast<void*>(B)));

		return StructProperty->Identical(StructA, StructB, PortFlags);
	}

	return false;
}

MonoObject* FStructPropertyDescriptor::Object_New(void* InAddress) const
{
	const auto FoundMonoClass = FTypeBridge::GetMonoClass(StructProperty);

	auto InParams = static_cast<void*>(FoundMonoClass);

	const auto Object = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
		FoundMonoClass, TGetArrayLength(InParams), &InParams);

	FCSharpEnvironment::GetEnvironment()->Bind(StructProperty->Struct, false);

	FCSharpEnvironment::GetEnvironment()->AddStructReference(StructProperty->Struct, InAddress, Object, false);

	return Object;
}
