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
			.Function("StaticClass", static_cast<void*>(FObjectImplementation::Object_StaticClassImplementation))
			.Function("GetClass", static_cast<void*>(FObjectImplementation::Object_GetClassImplementation))
			.Function("GetName", static_cast<void*>(FObjectImplementation::Object_GetNameImplementation))
			.Function("GetWorld", static_cast<void*>(FObjectImplementation::Object_GetWorldImplementation))
			.Function("IsValid", static_cast<void*>(FObjectImplementation::Object_IsValidImplementation))
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

void FObjectImplementation::Object_GetClassImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InMonoObject))
	{
		const auto Class = FoundObject->GetClass();

		*OutValue = FCSharpEnvironment::GetEnvironment().Bind(Class);
	}
}

void FObjectImplementation::Object_GetNameImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InMonoObject))
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

void FObjectImplementation::Object_GetWorldImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InMonoObject))
	{
		const auto World = FoundObject->GetWorld();

		*OutValue = FCSharpEnvironment::GetEnvironment().Bind(World);
	}
}

bool FObjectImplementation::Object_IsValidImplementation(const MonoObject* InMonoObject)
{
	if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InMonoObject))
	{
		return IsValid(FoundObject);
	}

	return false;
}
