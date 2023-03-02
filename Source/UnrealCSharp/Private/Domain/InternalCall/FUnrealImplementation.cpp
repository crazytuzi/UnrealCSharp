#include "Domain/InternalCall/FUnrealImplementation.h"
#include "Binding/Class/FBindingClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterUnreal
{
	FRegisterUnreal()
	{
		FBindingClassBuilder(TEXT("Unreal"), NAMESPACE_LIBRARY)
			.Function("NewObject",
			          static_cast<void*>(FUnrealImplementation::Unreal_NewObjectImplementation))
			.Function("NewObjectWithClassName",
			          static_cast<void*>(FUnrealImplementation::Unreal_NewObjectWithClassNameImplementation))

			.Register();
	}
};

static FRegisterUnreal RegisterUnreal;

void FUnrealImplementation::Unreal_NewObjectImplementation(const MonoObject* Outer, const MonoObject* Class,
                                                           MonoObject* Name, MonoObject** OutValue)
{
	const auto ObjectOuter = FCSharpEnvironment::GetEnvironment()->GetObject(Outer);

	const auto ObjectClass = Cast<UClass>(FCSharpEnvironment::GetEnvironment()->GetObject(Class));

	const auto ObjectName = FName(UTF8_TO_TCHAR(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(
		FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_To_String(Name,nullptr))));

	const auto Object = NewObject<UObject>(ObjectOuter, ObjectClass, ObjectName);

	*OutValue = FCSharpEnvironment::GetEnvironment()->GetObject(Object);
}

void FUnrealImplementation::Unreal_NewObjectWithClassNameImplementation(const MonoObject* Outer, MonoString* Class,
                                                                        MonoObject* Name, MonoObject** OutValue)
{
	const auto ObjectOuter = FCSharpEnvironment::GetEnvironment()->GetObject(Outer);

	const auto ClassName = UTF8_TO_TCHAR(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(Class));

	const auto ObjectClass = LoadClass<UObject>(nullptr, ClassName);

	const auto ObjectName = FName(UTF8_TO_TCHAR(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(
		FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_To_String(Name,nullptr))));

	const auto Object = NewObject<UObject>(ObjectOuter, ObjectClass, ObjectName);

	*OutValue = FCSharpEnvironment::GetEnvironment()->GetObject(Object);
}
