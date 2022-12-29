#include "Domain/InternalCall/FObjectImplementation.h"
#include "Binding/Class/TClassBuilder.h"
#include "Bridge/FTypeBridge.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterUObject
{
	FRegisterUObject()
	{
		TClassBuilder<UObject>()
			.Function("GetClass", static_cast<void*>(FObjectImplementation::Object_GetClassImplementation))
			.Function("GetName", static_cast<void*>(FObjectImplementation::Object_GetNameImplementation))
			.Register();
	}
};

static FRegisterUObject RegisterUObject;

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
				FTypeBridge::GetClassNameSpace(UClass::StaticClass()),
				FTypeBridge::GetFullClass(UClass::StaticClass()));

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
