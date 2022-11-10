#include "Reflection/Property/ContainerProperty/FArrayPropertyDescriptor.h"
#include "Bridge/FTypeBridge.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/FunctionMacro.h"
#include "Macro/MonoMacro.h"
#include "Macro/NamespaceMacro.h"
#include "Reflection/Container/FArrayHelper.h"

void FArrayPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (ArrayProperty != nullptr)
	{
		const auto SrcArrayHelper = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(Src);

		if (SrcArrayHelper == nullptr)
		{
			const auto FoundArrayMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
				COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_ENGINE),CLASS_T_ARRAY);

			const auto FoundArrayMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(
				FoundArrayMonoClass);

			const auto FoundArrayReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Type_Get_Object(
				FoundArrayMonoType);

			const auto FoundGenericMonoClass = FTypeBridge::GetMonoClass(ArrayProperty->Inner);

			const auto FoundGenericMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(
				FoundGenericMonoClass);

			const auto FoundGenericReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Type_Get_Object(
				FoundGenericMonoType);

			void* InParams[2];

			InParams[0] = FoundArrayReflectionType;

			const auto GenericReflectionTypeMonoArray = FCSharpEnvironment::GetEnvironment()->GetDomain()->Array_New(
				FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Object_Class(), 1);

			ARRAY_SET(GenericReflectionTypeMonoArray, MonoReflectionType*, 0, FoundGenericReflectionType);

			InParams[1] = GenericReflectionTypeMonoArray;

			const auto ContainerUtilsMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
				COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_CONTAINER_UTILS);

			const auto CreateGenericTypeMethod = FCSharpEnvironment::GetEnvironment()->GetDomain()->
				Class_Get_Method_From_Name(ContainerUtilsMonoClass,FUNCTION_MAKE_GENERIC_TYPE_INSTANCE, 2);

			const auto GenericClassMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Runtime_Invoke(
				CreateGenericTypeMethod, nullptr, InParams, nullptr);

			const auto GenericClassMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_Get_Class(
				GenericClassMonoObject);

			auto FoundArrayReflectionTypeParam = static_cast<void*>(FoundArrayReflectionType);

			FArrayHelper* ArrayHelper = new FArrayHelper(ArrayProperty->Inner, Src);

			*Dest = static_cast<void*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
				GenericClassMonoClass, 1, &FoundArrayReflectionTypeParam));

			FCSharpEnvironment::GetEnvironment()->AddContainerReference(
				Src, ArrayHelper, static_cast<MonoObject*>(*Dest));
		}
		else
		{
			*Dest = FCSharpEnvironment::GetEnvironment()->GetContainerObject(SrcArrayHelper);
		}
	}
}

void FArrayPropertyDescriptor::Get(void* Src, void* Dest) const
{
	if (ArrayProperty != nullptr)
	{
		Get(Src, static_cast<void**>(Dest));
	}
}

void FArrayPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (ArrayProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcContainer = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(SrcMonoObject);

		const auto DestContainer = FCSharpEnvironment::GetEnvironment()->GetContainer<FArrayHelper>(Dest);

		if (SrcContainer != nullptr)
		{
			if (DestContainer == nullptr || SrcContainer->GetScriptArray() != DestContainer->GetScriptArray())
			{
				FCSharpEnvironment::GetEnvironment()->RemoveContainerReference<FArrayHelper>(Dest);

				ArrayProperty->CopyCompleteValue(Dest, SrcContainer->GetScriptArray());

				FCSharpEnvironment::GetEnvironment()->AddContainerReference(Dest, SrcContainer, SrcMonoObject);
			}
		}
	}
}
