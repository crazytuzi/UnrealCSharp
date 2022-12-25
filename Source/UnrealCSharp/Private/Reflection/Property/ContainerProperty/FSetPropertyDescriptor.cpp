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
		const auto SrcSetHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FSetHelper>(Src);

		if (SrcSetHelper == nullptr)
		{
			const auto FoundSetMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
				COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON),CLASS_T_SET);

			const auto FoundSetMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(
				FoundSetMonoClass);

			const auto FoundSetReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Type_Get_Object(
				FoundSetMonoType);

			const auto FoundGenericMonoClass = FTypeBridge::GetMonoClass(SetProperty->ElementProp);

			const auto FoundGenericMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(
				FoundGenericMonoClass);

			const auto FoundGenericReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Type_Get_Object(
				FoundGenericMonoType);

			void* InParams[2];

			InParams[0] = FoundSetReflectionType;

			const auto GenericReflectionTypeMonoSet = FCSharpEnvironment::GetEnvironment()->GetDomain()->Array_New(
				FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Object_Class(), 1);

			ARRAY_SET(GenericReflectionTypeMonoSet, MonoReflectionType*, 0, FoundGenericReflectionType);

			InParams[1] = GenericReflectionTypeMonoSet;

			const auto ContainerUtilsMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
				COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_CONTAINER_UTILS);

			const auto CreateGenericTypeMethod = FCSharpEnvironment::GetEnvironment()->GetDomain()->
				Class_Get_Method_From_Name(ContainerUtilsMonoClass,FUNCTION_CONTAINER_UTILS_MAKE_GENERIC_TYPE_INSTANCE,
				                           2);

			const auto GenericClassMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Runtime_Invoke(
				CreateGenericTypeMethod, nullptr, InParams, nullptr);

			const auto GenericClassMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_Get_Class(
				GenericClassMonoObject);

			auto FoundSetReflectionTypeParam = static_cast<void*>(FoundSetReflectionType);

			const auto SetHelper = new FSetHelper(SetProperty->ElementProp, Src);

			*Dest = static_cast<void*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
				GenericClassMonoClass, 1, &FoundSetReflectionTypeParam));

			FCSharpEnvironment::GetEnvironment()->AddContainerReference(
				Src, SetHelper, static_cast<MonoObject*>(*Dest));
		}
		else
		{
			*Dest = FCSharpEnvironment::GetEnvironment()->GetContainerObject(SrcSetHelper);
		}
	}
}

void FSetPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (SetProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcContainer = FCSharpEnvironment::GetEnvironment()->GetContainer<FSetHelper>(SrcMonoObject);

		const auto DestContainer = FCSharpEnvironment::GetEnvironment()->GetContainer<FSetHelper>(Dest);

		if (SrcContainer != nullptr)
		{
			if (DestContainer == nullptr || SrcContainer->GetScriptSet() != DestContainer->GetScriptSet())
			{
				FCSharpEnvironment::GetEnvironment()->RemoveContainerReference<FSetHelper>(Dest);

				SetProperty->CopyCompleteValue(Dest, SrcContainer->GetScriptSet());

				FCSharpEnvironment::GetEnvironment()->AddContainerReference(Dest, SrcContainer, SrcMonoObject);
			}
		}
	}
}
