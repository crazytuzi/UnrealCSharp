#include "Reflection/Property/ObjectProperty/FWeakObjectPropertyDescriptor.h"
#include "Bridge/FTypeBridge.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/FunctionMacro.h"
#include "Macro/MonoMacro.h"
#include "Macro/NamespaceMacro.h"

void FWeakObjectPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (WeakObjectProperty != nullptr)
	{
		const auto FoundWeakObjectPtrMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_T_WEAK_OBJECT_PTR);

		const auto FoundWeakObjectPtrMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(
			FoundWeakObjectPtrMonoClass);

		const auto FoundWeakObjectPtrReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->
			Type_Get_Object(FoundWeakObjectPtrMonoType);

		const auto FoundGenericMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			FTypeBridge::GetClassNameSpace(WeakObjectProperty->PropertyClass),
			FTypeBridge::GetFullClass(WeakObjectProperty->PropertyClass));

		const auto FoundGenericMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(
			FoundGenericMonoClass);

		const auto FoundGenericReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Type_Get_Object(
			FoundGenericMonoType);

		void* InParams[2];

		InParams[0] = FoundWeakObjectPtrReflectionType;

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

		const auto SrcObject = WeakObjectProperty->GetObjectPropertyValue(Src);

		auto FoundMonoObject = FCSharpEnvironment::GetEnvironment()->GetObject(SrcObject);

		if (FoundMonoObject == nullptr)
		{
			const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
				FTypeBridge::GetClassNameSpace(SrcObject->GetClass()),
				FTypeBridge::GetFullClass(SrcObject->GetClass()));

			FoundMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass);

			FCSharpEnvironment::GetEnvironment()->AddObjectReference(SrcObject, FoundMonoObject);
		}

		auto GenericClassMonoClassParam = static_cast<void*>(FoundMonoObject);

		*Dest = static_cast<void*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
			GenericClassMonoClass, 1, &GenericClassMonoClassParam));
	}
}

void FWeakObjectPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (WeakObjectProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_Get_Class(SrcMonoObject);

		const auto FoundMonoMethod = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Method_From_Name(
			SrcMonoClass, FUNCTION_WEAK_OBJECT_PTR_GET, 0);

		const auto ReturnValue = FCSharpEnvironment::GetEnvironment()->GetDomain()->Runtime_Invoke(
			FoundMonoMethod, SrcMonoObject, nullptr, nullptr);

		const auto SrcObject = FCSharpEnvironment::GetEnvironment()->GetObject(ReturnValue);

		WeakObjectProperty->SetPropertyValue(Dest, SrcObject);
	}
}
