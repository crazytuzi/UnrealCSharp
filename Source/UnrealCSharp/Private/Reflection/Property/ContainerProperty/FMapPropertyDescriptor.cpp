#include "Reflection/Property/ContainerProperty/FMapPropertyDescriptor.h"
#include "Bridge/FTypeBridge.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/FunctionMacro.h"
#include "Macro/MonoMacro.h"
#include "Macro/NamespaceMacro.h"
#include "Reflection/Container/FMapHelper.h"

void FMapPropertyDescriptor::Get(void* Src, void** Dest) const
{
	if (MapProperty != nullptr)
	{
		const auto SrcMapProperty = FCSharpEnvironment::GetEnvironment()->GetContainer<FMapHelper>(Src);

		if (SrcMapProperty == nullptr)
		{
			const auto FoundMapMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
				COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_T_MAP);

			const auto FoundMapMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(
				FoundMapMonoClass);

			const auto FoundMapReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Type_Get_Object(
				FoundMapMonoType);

			const auto FoundKeyGenericMonoClass = FTypeBridge::GetMonoClass(MapProperty->KeyProp);

			const auto FoundKeyGenericMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(
				FoundKeyGenericMonoClass);

			const auto FoundKeyGenericReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->
				Type_Get_Object(
					FoundKeyGenericMonoType);

			const auto FoundValueGenericMonoClass = FTypeBridge::GetMonoClass(MapProperty->ValueProp);

			const auto FoundValueGenericMonoType = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Type(
				FoundValueGenericMonoClass);

			const auto FoundValueGenericReflectionType = FCSharpEnvironment::GetEnvironment()->GetDomain()->
				Type_Get_Object(
					FoundValueGenericMonoType);

			void* InParams[2];

			InParams[0] = FoundMapReflectionType;

			const auto GenericReflectionTypeMonoArray = FCSharpEnvironment::GetEnvironment()->GetDomain()->Array_New(
				FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Object_Class(), 2);

			ARRAY_SET(GenericReflectionTypeMonoArray, MonoReflectionType*, 0, FoundKeyGenericReflectionType);

			ARRAY_SET(GenericReflectionTypeMonoArray, MonoReflectionType*, 1, FoundValueGenericReflectionType);

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

			auto FoundArrayReflectionTypeParam = static_cast<void*>(FoundMapReflectionType);

			const auto MapHelper = new FMapHelper(MapProperty->KeyProp, MapProperty->ValueProp, Src);

			*Dest = static_cast<void*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(
				GenericClassMonoClass, 2, &FoundArrayReflectionTypeParam));

			FCSharpEnvironment::GetEnvironment()->AddContainerReference(
				Src, MapHelper, static_cast<MonoObject*>(*Dest));
		}
		else
		{
			*Dest = FCSharpEnvironment::GetEnvironment()->GetContainerObject(SrcMapProperty);
		}
	}
}

void FMapPropertyDescriptor::Set(void* Src, void* Dest) const
{
	if (MapProperty != nullptr)
	{
		const auto SrcMonoObject = static_cast<MonoObject*>(Src);

		const auto SrcContainer = FCSharpEnvironment::GetEnvironment()->GetContainer<FMapHelper>(SrcMonoObject);

		const auto DestContainer = FCSharpEnvironment::GetEnvironment()->GetContainer<FMapHelper>(Dest);

		if (SrcContainer != nullptr)
		{
			if (DestContainer == nullptr || SrcContainer->GetScriptMap() != DestContainer->GetScriptMap())
			{
				FCSharpEnvironment::GetEnvironment()->RemoveContainerReference<FMapHelper>(Dest);

				MapProperty->CopyCompleteValue(Dest, SrcContainer->GetScriptMap());

				FCSharpEnvironment::GetEnvironment()->AddContainerReference(Dest, SrcContainer, SrcMonoObject);
			}
		}
	}
}
