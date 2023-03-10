#include "Domain/InternalCall/FScriptInterfaceImplementation.h"
#include "Binding/Class/FBindingClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"
#include "FUnrealCSharpFunctionLibrary.h"

struct FRegisterScriptInterface
{
	FRegisterScriptInterface()
	{
		FBindingClassBuilder(TEXT("ScriptInterface"), NAMESPACE_LIBRARY)
			.Function("Register",
			          static_cast<void*>(FScriptInterfaceImplementation::ScriptInterface_RegisterImplementation))
			.Function("UnRegister",
			          static_cast<void*>(FScriptInterfaceImplementation::ScriptInterface_UnRegisterImplementation))
			.Function("GetObject",
			          static_cast<void*>(FScriptInterfaceImplementation::ScriptInterface_GetObjectImplementation))
			.Register();
	}
};

static FRegisterScriptInterface RegisterScriptInterface;

void FScriptInterfaceImplementation::ScriptInterface_RegisterImplementation(MonoObject* InMonoObject,
                                                                            const MonoObject* InObject)
{
	const auto FoundObject = FCSharpEnvironment::GetEnvironment()->GetObject(InObject);

	FCSharpEnvironment::GetEnvironment()->AddMultiReference<TScriptInterface<IInterface>>(InMonoObject, FoundObject);
}

void FScriptInterfaceImplementation::ScriptInterface_UnRegisterImplementation(const MonoObject* InMonoObject)
{
	FCSharpEnvironment::GetEnvironment()->RemoveMultiReference<TScriptInterface<IInterface>>(InMonoObject);
}

void FScriptInterfaceImplementation::ScriptInterface_GetObjectImplementation(const MonoObject* InMonoObject,
                                                                             MonoObject** OutValue)
{
	const auto Multi = FCSharpEnvironment::GetEnvironment()->GetMulti<TScriptInterface<IInterface>>(InMonoObject);

	auto FoundMonoObject = FCSharpEnvironment::GetEnvironment()->GetObject(Multi.GetObject());

	if (FoundMonoObject == nullptr)
	{
		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(Multi.GetObject()->GetClass()),
			FUnrealCSharpFunctionLibrary::GetFullClass(Multi.GetObject()->GetClass()));

		FoundMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass);

		FCSharpEnvironment::GetEnvironment()->Bind(Multi.GetObject()->GetClass(), false);

		FCSharpEnvironment::GetEnvironment()->AddObjectReference(Multi.GetObject(), FoundMonoObject);
	}

	*OutValue = FoundMonoObject;
}
