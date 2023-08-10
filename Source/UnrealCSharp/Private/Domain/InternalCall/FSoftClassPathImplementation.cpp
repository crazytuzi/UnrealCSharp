#include "Domain/InternalCall/FSoftClassPathImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterSoftClassPath
{
	FRegisterSoftClassPath()
	{
		TReflectionClassBuilder<FSoftClassPath>(NAMESPACE_LIBRARY)
			.Function("GetOrCreateIDForClass",
			          FSoftClassPathImplementation::SoftClassPath_GetOrCreateIDForClassImplementation)
			.Register();
	}
};

static FRegisterSoftClassPath RegisterSoftClassPath;

void FSoftClassPathImplementation::SoftClassPath_GetOrCreateIDForClassImplementation(
	const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto FoundClass = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FSoftClassPath, FSoftClassPath>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutSoftClassPath = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FSoftClassPath>(NewMonoObject);

	if (FoundClass != nullptr && OutSoftClassPath != nullptr)
	{
		*OutSoftClassPath = FSoftClassPath::GetOrCreateIDForClass(FoundClass);
	}
}
