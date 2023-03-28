#include "Domain/InternalCall/FStructImplementation.h"
#include "Binding/Class/FBindingClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

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
	const auto StructName = UTF8_TO_TCHAR(
		FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(InStructName));

	const auto InStruct = LoadObject<UScriptStruct>(nullptr, StructName);

	*OutValue = FCSharpEnvironment::GetEnvironment()->Bind(InStruct);
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
