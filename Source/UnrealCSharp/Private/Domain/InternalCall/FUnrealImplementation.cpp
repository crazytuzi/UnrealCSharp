#include "Domain/InternalCall/FUnrealImplementation.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterUnreal
{
	FRegisterUnreal()
	{
		FClassBuilder(TEXT("Unreal"), NAMESPACE_LIBRARY)
			.Function("NewObject", FUnrealImplementation::Unreal_NewObjectImplementation)
			.Function("DuplicateObject", FUnrealImplementation::Unreal_DuplicateObjectImplementation)
			.Function("LoadObject", FUnrealImplementation::Unreal_LoadObjectImplementation)
			.Function("LoadClass", FUnrealImplementation::Unreal_LoadClassImplementation)
			.Register();
	}
};

static FRegisterUnreal RegisterUnreal;

void FUnrealImplementation::Unreal_NewObjectImplementation(const MonoObject* Outer, const MonoObject* Class,
                                                           MonoObject* Name, MonoObject** OutValue)
{
	const auto ObjectOuter = FCSharpEnvironment::GetEnvironment().GetObject(Outer);

	const auto ObjectClass = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(Class);

	const auto ObjectName = FName(UTF8_TO_TCHAR(
		FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
			GetDomain()->Object_To_String(Name, nullptr))));

	const auto Object = NewObject<UObject>(ObjectOuter, ObjectClass, ObjectName);

	*OutValue = FCSharpEnvironment::GetEnvironment().Bind(Object);
}

void FUnrealImplementation::Unreal_DuplicateObjectImplementation(const MonoObject* SourceObject,
                                                                 const MonoObject* Outer, MonoObject* Name,
                                                                 MonoObject** OutValue)
{
	const auto ObjectSourceObject = FCSharpEnvironment::GetEnvironment().GetObject(SourceObject);

	const auto ObjectOuter = FCSharpEnvironment::GetEnvironment().GetObject(Outer);

	const auto ObjectName = FName(UTF8_TO_TCHAR(
		FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
			GetDomain()->Object_To_String(Name, nullptr))));

	const auto Object = DuplicateObject<UObject>(ObjectSourceObject, ObjectOuter, ObjectName);

	*OutValue = FCSharpEnvironment::GetEnvironment().Bind(Object);
}

void FUnrealImplementation::Unreal_LoadObjectImplementation(const MonoObject* Outer, MonoString* Name,
                                                            MonoObject** OutValue)
{
	const auto ObjectOuter = FCSharpEnvironment::GetEnvironment().GetObject(Outer);

	const auto ObjectName = UTF8_TO_TCHAR(FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(Name));

	const auto Object = LoadObject<UObject>(ObjectOuter, ObjectName);

	*OutValue = FCSharpEnvironment::GetEnvironment().Bind(Object);
}

void FUnrealImplementation::Unreal_LoadClassImplementation(const MonoObject* Outer, MonoString* Name,
                                                           MonoObject** OutValue)
{
	const auto ObjectOuter = FCSharpEnvironment::GetEnvironment().GetObject(Outer);

	const auto ObjectName = UTF8_TO_TCHAR(FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(Name));

	const auto Class = LoadClass<UObject>(ObjectOuter, ObjectName);

	*OutValue = FCSharpEnvironment::GetEnvironment().Bind(Class);
}
