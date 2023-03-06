#include "Domain/InternalCall/FSoftClassPathImplementation.h"
#include "Binding/Class/TScriptStructBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/NamespaceMacro.h"
#include "FUnrealCSharpFunctionLibrary.h"

struct FRegisterSoftClassPath
{
	FRegisterSoftClassPath()
	{
		TScriptStructBuilder<FSoftClassPath>(NAMESPACE_LIBRARY)
			.Function("GetOrCreateIDForObject",
			          static_cast<void*>(
				          FSoftClassPathImplementation::SoftClassPath_GetOrCreateIDForObjectImplementation))
			.Register();
	}
};

static FRegisterSoftClassPath RegisterSoftClassPath;

void FSoftClassPathImplementation::SoftClassPath_GetOrCreateIDForObjectImplementation(
	const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto FoundClass = FCSharpEnvironment::GetEnvironment()->GetObject<UClass>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FSoftClassPath)),
		CLASS_SCRIPT_STRUCT_NAME(FSoftClassPath));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutSoftClassPath = FCSharpEnvironment::GetEnvironment()->GetAddress<
		UScriptStruct, FSoftClassPath>(NewMonoObject);

	if (FoundClass != nullptr && OutSoftClassPath != nullptr)
	{
		*OutSoftClassPath = FSoftClassPath::GetOrCreateIDForClass(FoundClass);
	}
}
