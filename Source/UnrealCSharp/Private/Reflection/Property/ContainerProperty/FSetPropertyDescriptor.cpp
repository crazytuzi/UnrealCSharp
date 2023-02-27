#include "Reflection/Property/ContainerProperty/FSetPropertyDescriptor.h"
#include "Bridge/FTypeBridge.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/FunctionMacro.h"
#include "Macro/MonoMacro.h"
#include "Macro/NamespaceMacro.h"
#include "Reflection/Container/FSetHelper.h"

void FSetPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (SetProperty != nullptr)
	{
		auto SrcMonoObject = FCSharpEnvironment::GetEnvironment()->GetContainerObject(Src);

		if (SrcMonoObject == nullptr)
		{
			SrcMonoObject = Object_New(Src);
		}

		*Dest = SrcMonoObject;
	}
}

void FSetPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (SetProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcContainer = FCSharpEnvironment::GetEnvironment()->GetContainer<FSetHelper>(SrcMonoObject);

		FCSharpEnvironment::GetEnvironment()->RemoveContainerReference(Dest);

		MapProperty->CopyCompleteValue(Dest, SrcContainer->GetScriptSet());

		Object_New(Dest);
	}
}

MonoObject* FSetPropertyDescriptor::Object_New(void* InAddress) const
{
	const auto FoundSetMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_T_SET);

	const auto FoundSetMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(
		FoundSetMonoClass);

	const auto FoundSetReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Type_Get_Object(
		FoundSetMonoType);

	const auto FoundGenericMonoClass = FTypeBridge::GetMonoClass(SetProperty->ElementProp);

	const auto FoundGenericMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(
		FoundGenericMonoClass);

	const auto FoundGenericReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Type_Get_Object(
		FoundGenericMonoType);

	void* InParams[3];

	InParams[0] = FoundSetReflectionType;

	const auto GenericReflectionTypeMonoArray = FCSharpEnvironment::GetEnvironment()->GetDomain()->Array_New(
		FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Object_Class(), 1);

	ARRAY_SET(GenericReflectionTypeMonoArray, MonoReflectionType*, 0, FoundGenericReflectionType);

	InParams[1] = GenericReflectionTypeMonoArray;

	InParams[2] = GenericReflectionTypeMonoArray;

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

	auto FoundSetReflectionTypeParam = static_cast<void*>(FoundSetReflectionType);

	const auto SetHelper = new FSetHelper(SetProperty->ElementProp, InAddress);

	const auto Object = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
		GenericClassMonoClass, 1, &FoundSetReflectionTypeParam);

	const auto OwnerGarbageCollectionHandle = FCSharpEnvironment::GetEnvironment()->GetGarbageCollectionHandle(
		InAddress, SetProperty->GetOffset_ForInternal());

	FCSharpEnvironment::GetEnvironment()->AddContainerReference(OwnerGarbageCollectionHandle, InAddress, SetHelper,
	                                                            Object);

	return Object;
}
