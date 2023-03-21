#include "Domain/InternalCall/FStructImplementation.h"
#include "Binding/Class/FBindingClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"
#include "FUnrealCSharpFunctionLibrary.h"

struct FRegisterStruct
{
	FRegisterStruct()
	{
		FBindingClassBuilder(TEXT("Struct"), NAMESPACE_LIBRARY)
			.Function("StaticStruct", static_cast<void*>(FStructImplementation::Struct_StaticStructImplementation))
			.Function("Register", static_cast<void*>(FStructImplementation::Struct_RegisterImplementation))
			.Function("UnRegister", static_cast<void*>(FStructImplementation::Struct_UnRegisterImplementation))
			.Register();
	}
};

static FRegisterStruct RegisterStruct;

void FStructImplementation::Struct_StaticStructImplementation(MonoString* InStructName, MonoObject** OutValue)
{
	const auto StructName =
		UTF8_TO_TCHAR(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(InStructName));

	const auto InStruct = LoadObject<UScriptStruct>(nullptr, StructName);

	auto FoundMonoObject = FCSharpEnvironment::GetEnvironment()->GetObject(InStruct);

	if (FoundMonoObject == nullptr)
	{
		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(UScriptStruct::StaticClass()),
			FUnrealCSharpFunctionLibrary::GetFullClass(UScriptStruct::StaticClass()));

		FoundMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass);

		// @TODO	
		FCSharpEnvironment::GetEnvironment()->Bind(UScriptStruct::StaticClass(), false);

		FCSharpEnvironment::GetEnvironment()->AddObjectReference(InStruct, FoundMonoObject);
	}

	*OutValue = FoundMonoObject;
}

void FStructImplementation::Struct_RegisterImplementation(MonoObject* InMonoObject, MonoString* InStructName)
{
	const auto StructName = UTF8_TO_TCHAR(
		FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(InStructName));

	FCSharpEnvironment::GetEnvironment()->Bind(InMonoObject, StructName);
}

void FStructImplementation::Struct_UnRegisterImplementation(const MonoObject* InMonoObject)
{
	FCSharpEnvironment::GetEnvironment()->RemoveStructReference(InMonoObject);
}
