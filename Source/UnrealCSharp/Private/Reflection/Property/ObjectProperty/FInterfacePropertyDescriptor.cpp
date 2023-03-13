#include "Reflection/Property/ObjectProperty/FInterfacePropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/FunctionMacro.h"
#include "Macro/MonoMacro.h"
#include "Macro/NamespaceMacro.h"
#include "FUnrealCSharpFunctionLibrary.h"
#include "Template/TGetArrayLength.h"

void FInterfacePropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (InterfaceProperty != nullptr)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetMultiObject<TScriptInterface<IInterface>>(Src);

		if (SrcMonoObject == nullptr)
		{
			SrcMonoObject = Object_New(Src);
		}

		*Dest = SrcMonoObject;
	}
}

void FInterfacePropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (InterfaceProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcMulti = FCSharpEnvironment::GetEnvironment()->GetMulti<TScriptInterface<IInterface>>(
			SrcMonoObject);

		FCSharpEnvironment::GetEnvironment()->RemoveMultiReference<TScriptInterface<IInterface>>(Dest);

		InterfaceProperty->SetPropertyValue(Dest, SrcMulti.GetObject());

		Object_New(Dest);
	}
}

MonoObject* FInterfacePropertyDescriptor::Object_New(void* InAddress) const
{
	const auto SrcObject = InterfaceProperty->GetPropertyValuePtr(InAddress)->GetObject();

	const auto FoundScriptInterfaceMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_T_SCRIPT_INTERFACE);

	const auto FoundScriptInterfaceMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(
		FoundScriptInterfaceMonoClass);

	const auto FoundScriptInterfaceReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->
		Type_Get_Object(FoundScriptInterfaceMonoType);

	const auto FoundGenericMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(InterfaceProperty->InterfaceClass),
		FUnrealCSharpFunctionLibrary::GetFullInterface(InterfaceProperty->InterfaceClass));

	const auto FoundGenericMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(
		FoundGenericMonoClass);

	const auto FoundGenericReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Type_Get_Object(
		FoundGenericMonoType);

	void* InParams[2];

	InParams[0] = FoundScriptInterfaceReflectionType;

	const auto GenericReflectionTypeMonoArray = FCSharpEnvironment::GetEnvironment()->GetDomain()->Array_New(
		FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Object_Class(), 1);

	ARRAY_SET(GenericReflectionTypeMonoArray, MonoReflectionType*, 0, FoundGenericReflectionType);

	InParams[1] = GenericReflectionTypeMonoArray;

	const auto UtilsMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_UTILS);

	const auto CreateGenericTypeMethod = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Method_From_Name(
		UtilsMonoClass, FUNCTION_UTILS_MAKE_GENERIC_TYPE_INSTANCE, TGetArrayLength(InParams));

	const auto GenericClassMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Runtime_Invoke(
		CreateGenericTypeMethod, nullptr, InParams, nullptr);

	const auto GenericClassMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_Get_Class(
		GenericClassMonoObject);

	const auto Object = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(GenericClassMonoClass);

	FCSharpEnvironment::GetEnvironment()->AddMultiReference<TScriptInterface<IInterface>>(InAddress, Object, SrcObject);

	return Object;
}
