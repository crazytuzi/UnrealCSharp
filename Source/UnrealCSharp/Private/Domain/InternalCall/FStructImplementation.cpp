#include "Domain/InternalCall/FStructImplementation.h"
#include "Binding/Class/FBindingClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"

struct FRegisterStruct
{
	FRegisterStruct()
	{
		FBindingClassBuilder(TEXT("Struct"), NAMESPACE_STRUCT)
			.Function("Register", static_cast<void*>(FStructImplementation::Struct_RegisterImplementation))
			.Function("UnRegister", static_cast<void*>(FStructImplementation::Struct_UnRegisterImplementation))
			.Register();
	}
};

static FRegisterStruct RegisterStruct;

void FStructImplementation::Struct_RegisterImplementation(MonoObject* InMonoObject, const UTF16CHAR* InStructName)
{
	const auto StructName = StringCast<TCHAR>(InStructName + 10).Get();

	FCSharpEnvironment::GetEnvironment()->Bind(InMonoObject, StructName);
}

void FStructImplementation::Struct_UnRegisterImplementation(const MonoObject* InMonoObject)
{
	FCSharpEnvironment::GetEnvironment()->RemoveStructReference(InMonoObject);
}
