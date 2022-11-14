#include "Domain/InternalCall/FStructImplementation.h"
#include "Environment/FCSharpEnvironment.h"

void FStructImplementation::Struct_RegisterImplementation(MonoObject* InMonoObject, const UTF16CHAR* InStructName)
{
	const auto StructName = StringCast<TCHAR>(InStructName + 10).Get();

	FCSharpEnvironment::GetEnvironment()->Bind(InMonoObject, StructName);
}

void FStructImplementation::Struct_UnRegisterImplementation(const MonoObject* InMonoObject)
{
	FCSharpEnvironment::GetEnvironment()->RemoveStructReference(InMonoObject);
}
