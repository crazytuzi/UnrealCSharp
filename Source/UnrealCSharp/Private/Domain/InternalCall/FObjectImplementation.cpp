#include "Domain/InternalCall/FObjectImplementation.h"
#include "Binding/Class/TClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/NamespaceMacro.h"
#include "FUnrealCSharpFunctionLibrary.h"

struct FRegisterUObject
{
	FRegisterUObject()
	{
		TClassBuilder<UObject>(NAMESPACE_LIBRARY)
			.Function("StaticClass", static_cast<void*>(FObjectImplementation::Object_StaticClassImplementation))
			.Function("GetClass", static_cast<void*>(FObjectImplementation::Object_GetClassImplementation))
			.Function("GetName", static_cast<void*>(FObjectImplementation::Object_GetNameImplementation))
			.Register();
	}
};

static FRegisterUObject RegisterUObject;

void FObjectImplementation::Object_StaticClassImplementation(MonoString* InClassName, MonoObject** OutValue)
{
	const auto ClassName =
		UTF8_TO_TCHAR(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(InClassName));

	const auto InClass = LoadObject<UClass>(nullptr, ClassName);

	if (const auto FoundMonoObject = FCSharpEnvironment::GetEnvironment()->GetObject(InClass))
	{
		*OutValue = FoundMonoObject;
	}
	else
	{
		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(UClass::StaticClass()),
			FUnrealCSharpFunctionLibrary::GetFullClass(UClass::StaticClass()));

		*OutValue = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass);

		FCSharpEnvironment::GetEnvironment()->AddObjectReference(InClass, *OutValue);
	}
}

void FObjectImplementation::Object_GetClassImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	if (const auto FoundObject = FCSharpEnvironment::GetEnvironment()->GetObject(InMonoObject))
	{
		const auto Class = FoundObject->GetClass();

		if (const auto FoundMonoObject = FCSharpEnvironment::GetEnvironment()->GetObject(Class))
		{
			*OutValue = FoundMonoObject;
		}
		else
		{
			const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
				FUnrealCSharpFunctionLibrary::GetClassNameSpace(UClass::StaticClass()),
				FUnrealCSharpFunctionLibrary::GetFullClass(UClass::StaticClass()));

			*OutValue = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass);

			FCSharpEnvironment::GetEnvironment()->AddObjectReference(Class, *OutValue);
		}
	}
}

void FObjectImplementation::Object_GetNameImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	if (const auto FoundObject = FCSharpEnvironment::GetEnvironment()->GetObject(InMonoObject))
	{
		const auto Name = FoundObject->GetName();

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_New(
			TCHAR_TO_UTF8(*Name)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}
