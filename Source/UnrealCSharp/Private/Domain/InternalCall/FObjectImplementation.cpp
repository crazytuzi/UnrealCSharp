#include "Domain/InternalCall/FObjectImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/Core/TPropertyClass.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/BindingMacro.h"
#include "Macro/NamespaceMacro.h"

BINDING_REFLECTION_CLASS(UObject);

struct FRegisterObject
{
	FRegisterObject()
	{
		TReflectionClassBuilder<UObject>(NAMESPACE_LIBRARY)
			.Function("StaticClass", FObjectImplementation::Object_StaticClassImplementation)
			.Function("GetClass", FObjectImplementation::Object_GetClassImplementation)
			.Function("GetName", FObjectImplementation::Object_GetNameImplementation)
			.Function("GetWorld", FObjectImplementation::Object_GetWorldImplementation)
			.Function("IsValid", FObjectImplementation::Object_IsValidImplementation)
			.Register();
	}
};

static FRegisterObject RegisterObject;

void FObjectImplementation::Object_StaticClassImplementation(MonoString* InClassName, MonoObject** OutValue)
{
	const auto ClassName =
		UTF8_TO_TCHAR(FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(InClassName));

	const auto InClass = LoadObject<UClass>(nullptr, ClassName);

	*OutValue = FCSharpEnvironment::GetEnvironment().Bind(InClass);
}

void FObjectImplementation::Object_GetClassImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                          MonoObject** OutValue)
{
	if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
	{
		const auto Class = FoundObject->GetClass();

		*OutValue = FCSharpEnvironment::GetEnvironment().Bind(Class);
	}
}

void FObjectImplementation::Object_GetNameImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                         MonoObject** OutValue)
{
	if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
	{
		const auto Name = FoundObject->GetName();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*Name)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

void FObjectImplementation::Object_GetWorldImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                          MonoObject** OutValue)
{
	if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
	{
		const auto World = FoundObject->GetWorld();

		*OutValue = FCSharpEnvironment::GetEnvironment().Bind(World);
	}
}

bool FObjectImplementation::Object_IsValidImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
	{
		return IsValid(FoundObject);
	}

	return false;
}
