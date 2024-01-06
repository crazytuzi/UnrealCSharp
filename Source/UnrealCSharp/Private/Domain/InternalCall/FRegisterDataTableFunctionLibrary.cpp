#include "Binding/Class/FClassBuilder.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Kismet/DataTableFunctionLibrary.h"
#include "Macro/BindingMacro.h"
#include "Macro/NamespaceMacro.h"

BINDING_REFLECTION_CLASS(UDataTableFunctionLibrary);

struct FRegisterDataTableFunctionLibrary
{
	static bool GetDataTableRowFromNameImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                  MonoString* RowName, MonoObject** OutRow)
	{
		const auto InRowName = UTF8_TO_TCHAR(FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(RowName));

		if (const auto DataTable = FCSharpEnvironment::GetEnvironment().GetObject<
			UDataTable>(InGarbageCollectionHandle))
		{
#if UE_OBJECT_PTR
			FCSharpEnvironment::GetEnvironment().Bind(DataTable->RowStruct.Get(), false);
#else
			FCSharpEnvironment::GetEnvironment().Bind(DataTable->RowStruct, false);
#endif

#if UE_OBJECT_PTR
			if (const auto ClassDescriptor = FCSharpEnvironment::GetEnvironment().GetClassDescriptor(
				DataTable->RowStruct.Get()))
#else
			if (const auto ClassDescriptor = FCSharpEnvironment::GetEnvironment().GetClassDescriptor(
				DataTable->RowStruct))
#endif
			{
				*OutRow = FCSharpEnvironment::GetEnvironment().GetDomain()->
				                                               Object_Init(ClassDescriptor->GetMonoClass());

				const auto FindRowData = *DataTable->GetRowMap().Find(InRowName);

				const auto OutRowData = FCSharpEnvironment::GetEnvironment().GetStruct(*OutRow);

				DataTable->RowStruct->CopyScriptStruct(OutRowData, FindRowData);

				return true;
			}
		}

		return false;
	}

	FRegisterDataTableFunctionLibrary()
	{
		TReflectionClassBuilder<UDataTableFunctionLibrary>(NAMESPACE_LIBRARY)
			.Function("GetDataTableRowFromName", GetDataTableRowFromNameImplementation)
			.Register();
	}
};

static FRegisterDataTableFunctionLibrary RegisterDataTableFunctionLibrary;
