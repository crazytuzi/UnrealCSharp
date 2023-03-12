#include "Reflection/Property/ObjectProperty/FSoftObjectPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/FunctionMacro.h"
#include "Macro/MonoMacro.h"
#include "Macro/NamespaceMacro.h"
#include "FUnrealCSharpFunctionLibrary.h"
#include "Template/TGetArrayLength.h"

void FSoftObjectPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (SoftObjectProperty != nullptr)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetMultiObject<TSoftObjectPtr<UObject>>(Src);

		if (SrcMonoObject == nullptr)
		{
			SrcMonoObject = Object_New(Src);
		}

		*Dest = SrcMonoObject;
	}
}

void FSoftObjectPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (SoftObjectProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcMulti = FCSharpEnvironment::GetEnvironment()->GetMulti<TSoftObjectPtr<UObject>>(SrcMonoObject);

		FCSharpEnvironment::GetEnvironment()->RemoveMultiReference<TSoftObjectPtr<UObject>>(Dest);

		SoftObjectProperty->SetObjectPropertyValue(Dest, SrcMulti.Get());

		Object_New(Dest);
	}
}

MonoObject* FSoftObjectPropertyDescriptor::Object_New(void* InAddress) const
{
	const auto SrcObject = SoftObjectProperty->GetObjectPropertyValue(InAddress);

	const auto FoundSoftObjectPtrMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_T_SOFT_OBJECT_PTR);

	const auto FoundSoftObjectPtrMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(
		FoundSoftObjectPtrMonoClass);

	const auto FoundSoftObjectPtrReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->
		Type_Get_Object(FoundSoftObjectPtrMonoType);

	const auto FoundGenericMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(SoftObjectProperty->PropertyClass),
		FUnrealCSharpFunctionLibrary::GetFullClass(SoftObjectProperty->PropertyClass));

	const auto FoundGenericMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(
		FoundGenericMonoClass);

	const auto FoundGenericReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Type_Get_Object(
		FoundGenericMonoType);

	void* InParams[3];

	InParams[0] = FoundSoftObjectPtrReflectionType;

	const auto GenericReflectionTypeMonoArray = FCSharpEnvironment::GetEnvironment()->GetDomain()->Array_New(
		FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Object_Class(), 1);

	ARRAY_SET(GenericReflectionTypeMonoArray, MonoReflectionType*, 0, FoundGenericReflectionType);

	InParams[1] = GenericReflectionTypeMonoArray;

	InParams[2] = FoundSoftObjectPtrReflectionType;

	const auto UtilsMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_UTILS);

	const auto CreateGenericTypeMethod = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Method_From_Name(
		UtilsMonoClass, FUNCTION_UTILS_MAKE_GENERIC_TYPE_INSTANCE, TGetArrayLength(InParams));

	const auto GenericClassMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Runtime_Invoke(
		CreateGenericTypeMethod, nullptr, InParams, nullptr);

	const auto GenericClassMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_Get_Class(
		GenericClassMonoObject);

	const auto Object = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(GenericClassMonoClass);

	FCSharpEnvironment::GetEnvironment()->AddMultiReference<TSoftObjectPtr<UObject>>(InAddress, Object, SrcObject);

	return Object;
}
