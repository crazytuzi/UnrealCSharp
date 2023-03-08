#include "Reflection/Property/ObjectProperty/FClassPropertyDescriptor.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/FunctionMacro.h"
#include "Macro/MonoMacro.h"
#include "Macro/NamespaceMacro.h"
#include "FUnrealCSharpFunctionLibrary.h"

void FClassPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (ClassProperty != nullptr)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetMultiObject(Src);

		if (SrcMonoObject == nullptr)
		{
			SrcMonoObject = Object_New(Src);
		}

		*Dest = SrcMonoObject;
	}
}

void FClassPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (ClassProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcMulti = FCSharpEnvironment::GetEnvironment()->GetMulti(SrcMonoObject);

		FCSharpEnvironment::GetEnvironment()->RemoveMultiReference(Dest);

		ClassProperty->SetObjectPropertyValue(Dest, SrcMulti);

		Object_New(Dest);
	}
}

MonoObject* FClassPropertyDescriptor::Object_New(void* InAddress) const
{
	const auto SrcClass = Cast<UClass>(ClassProperty->GetObjectPropertyValue(InAddress));

	const auto FoundSubClassOfMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_T_SUB_CLASS_OF);

	const auto FoundSubClassOfMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(
		FoundSubClassOfMonoClass);

	const auto FoundSubClassOfReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->
		Type_Get_Object(FoundSubClassOfMonoType);

	const auto FoundGenericMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(ClassProperty->MetaClass),
		FUnrealCSharpFunctionLibrary::GetFullClass(ClassProperty->MetaClass));

	const auto FoundGenericMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(
		FoundGenericMonoClass);

	const auto FoundGenericReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Type_Get_Object(
		FoundGenericMonoType);

	void* InParams[3];

	InParams[0] = FoundSubClassOfReflectionType;

	const auto GenericReflectionTypeMonoArray = FCSharpEnvironment::GetEnvironment()->GetDomain()->Array_New(
		FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Object_Class(), 1);

	ARRAY_SET(GenericReflectionTypeMonoArray, MonoReflectionType*, 0, FoundGenericReflectionType);

	InParams[1] = GenericReflectionTypeMonoArray;

	InParams[2] = FoundSubClassOfReflectionType;

	const auto UtilsMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_UTILS);

	const auto CreateGenericTypeMethod = FCSharpEnvironment::GetEnvironment()->GetDomain()->
	                                                                           Class_Get_Method_From_Name(
		                                                                           UtilsMonoClass,
		                                                                           FUNCTION_UTILS_MAKE_GENERIC_TYPE_INSTANCE,
		                                                                           3);

	const auto GenericClassMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Runtime_Invoke(
		CreateGenericTypeMethod, nullptr, InParams, nullptr);

	const auto GenericClassMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_Get_Class(
		GenericClassMonoObject);

	const auto SrcMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(SrcClass),
		FUnrealCSharpFunctionLibrary::GetFullClass(SrcClass));

	const auto StaticClassMonoMethod = FCSharpEnvironment::GetEnvironment()->GetDomain()->
	                                                                         Class_Get_Method_From_Name(
		                                                                         SrcMonoClass, FUNCTION_STATIC_CLASS,
		                                                                         0);

	const auto ReturnValue = FCSharpEnvironment::GetEnvironment()->GetDomain()->Runtime_Invoke(
		StaticClassMonoMethod, nullptr, nullptr, nullptr);

	auto GenericClassMonoClassParam = static_cast<void*>(ReturnValue);

	const auto Object = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
		GenericClassMonoClass, 1, &GenericClassMonoClassParam);

	FCSharpEnvironment::GetEnvironment()->AddMultiReference(InAddress, Object, SrcClass);

	return Object;
}
