#include "Domain/InternalCall/FScriptInterfaceImplementation.h"
#include "Binding/Class/FBindingClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

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

void FScriptInterfaceImplementation::ScriptInterface_RegisterImplementation(
	MonoObject* InMonoObject, const MonoObject* InObject, MonoString* InInterfaceName)
{
	const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject);

	const auto InterfaceName = UTF8_TO_TCHAR(
		FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(InInterfaceName));

	const auto InterfaceClass = LoadClass<UInterface>(nullptr, InterfaceName);

	TScriptInterface<IInterface> ScriptInterface;

	ScriptInterface.SetObject(FoundObject);

	ScriptInterface.SetInterface(static_cast<IInterface*>(FoundObject->GetInterfaceAddress(InterfaceClass)));

	FCSharpEnvironment::GetEnvironment().AddMultiReference<TScriptInterface<
		IInterface>>(InMonoObject, ScriptInterface);
}

void FScriptInterfaceImplementation::ScriptInterface_UnRegisterImplementation(const MonoObject* InMonoObject)
{
	(void)FCSharpEnvironment::GetEnvironment().RemoveMultiReference<TScriptInterface<IInterface>>(InMonoObject);
}

void FScriptInterfaceImplementation::ScriptInterface_GetObjectImplementation(const MonoObject* InMonoObject,
                                                                             MonoObject** OutValue)
{
	const auto Multi = FCSharpEnvironment::GetEnvironment().GetMulti<TScriptInterface<IInterface>>(InMonoObject);

	*OutValue = FCSharpEnvironment::GetEnvironment().Bind(Multi.GetObject());
}
