#include "Domain/InternalCall/FStructImplementation.h"
#include "Environment/FCSharpEnvironment.h"

void FStructImplementation::RegisterStructImplementation(MonoObject InMonoObject, const UTF16CHAR* InStructName)
{
	const auto StructName = StringCast<TCHAR>(InStructName + 10).Get();

	FCSharpEnvironment::GetEnvironment()->Bind(&InMonoObject, StructName);
}

void FStructImplementation::UnRegisterStructImplementation(MonoObject InMonoObject)
{
	FCSharpEnvironment::GetEnvironment()->RemoveStructReference(&InMonoObject);
}
