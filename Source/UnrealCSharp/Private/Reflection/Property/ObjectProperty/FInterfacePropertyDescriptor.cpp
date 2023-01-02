#include "Reflection/Property/ObjectProperty/FInterfacePropertyDescriptor.h"
#include "Bridge/FTypeBridge.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/FunctionMacro.h"
#include "Macro/MonoMacro.h"
#include "Macro/NamespaceMacro.h"

void FInterfacePropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (InterfaceProperty != nullptr)
	{
		const auto SrcClass = Cast<UClass>(InterfaceProperty->GetPropertyValuePtr(Src)->GetObject());

		const auto FoundScriptInterfaceMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_T_SCRIPT_INTERFACE);

		const auto FoundScriptInterfaceMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(
			FoundScriptInterfaceMonoClass);

		const auto FoundScriptInterfaceReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->
			Type_Get_Object(FoundScriptInterfaceMonoType);

		const auto FoundGenericMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			FTypeBridge::GetClassNameSpace(InterfaceProperty->InterfaceClass),
			FTypeBridge::GetFullInterface(InterfaceProperty->InterfaceClass));

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

		const auto CreateGenericTypeMethod = FCSharpEnvironment::GetEnvironment()->GetDomain()->
			Class_Get_Method_From_Name(UtilsMonoClass, FUNCTION_UTILS_MAKE_GENERIC_TYPE_INSTANCE,
			                           2);

		const auto GenericClassMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Runtime_Invoke(
			CreateGenericTypeMethod, nullptr, InParams, nullptr);

		const auto GenericClassMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_Get_Class(
			GenericClassMonoObject);

		const auto SrcMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			FTypeBridge::GetClassNameSpace(SrcClass),
			FTypeBridge::GetFullClass(SrcClass));

		const auto StaticClassMonoMethod = FCSharpEnvironment::GetEnvironment()->GetDomain()->
			Class_Get_Method_From_Name(SrcMonoClass, FUNCTION_STATIC_CLASS, 0);

		const auto ReturnValue = FCSharpEnvironment::GetEnvironment()->GetDomain()->Runtime_Invoke(
			StaticClassMonoMethod, nullptr, nullptr, nullptr);

		auto GenericClassMonoClassParam = static_cast<void*>(ReturnValue);

		*Dest = static_cast<void*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
			GenericClassMonoClass, 1, &GenericClassMonoClassParam));
	}
}

void FInterfacePropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (InterfaceProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_Get_Class(SrcMonoObject);

		const auto FoundMonoMethod = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Method_From_Name(
			SrcMonoClass, FUNCTION_SCRIPT_INTERFACE_GET, 0);

		const auto ReturnValue = FCSharpEnvironment::GetEnvironment()->GetDomain()->Runtime_Invoke(
			FoundMonoMethod, SrcMonoObject, nullptr, nullptr);

		const auto SrcClass = Cast<UClass>(FCSharpEnvironment::GetEnvironment()->GetObject(ReturnValue));

		InterfaceProperty->SetPropertyValue(Dest, SrcClass);
	}
}
