#include "Domain/InternalCall/FDataTableFunctionLibrary.h"
#include "Binding/Class/FBindingClassBuilder.h"
#include "Binding/Class/TClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterDataTableFunctionLibrary
{
	FRegisterDataTableFunctionLibrary()
	{
		TClassBuilder<UDataTableFunctionLibrary>(NAMESPACE_LIBRARY)
			.Function("GetDataTableRowFromName",
			          static_cast<void*>(
				          FDataTableFunctionLibraryImplementation::DataTableFunctionLibrary_GetDataTableRowFromNameImplementation))
			.Register();
	}
};

static FRegisterDataTableFunctionLibrary RegisterDataTableFunctionLibrary;

bool FDataTableFunctionLibraryImplementation::DataTableFunctionLibrary_GetDataTableRowFromNameImplementation(
	const MonoObject* Table, MonoString* RowName, MonoObject** OutRow)
{
	const auto InRowName = UTF8_TO_TCHAR(FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(RowName));

	if (const auto DataTable = FCSharpEnvironment::GetEnvironment().GetObject<UDataTable>(Table))
	{
		FCSharpEnvironment::GetEnvironment().Bind(DataTable->RowStruct.Get(), false);

		if (const auto ClassDescriptor = FCSharpEnvironment::GetEnvironment().GetClassDescriptor(
			DataTable->RowStruct.Get()))
		{
			*OutRow = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(ClassDescriptor->GetMonoClass());

			const auto FindRowData = *DataTable->GetRowMap().Find(InRowName);

			const auto OutRowData = FCSharpEnvironment::GetEnvironment().GetStruct(*OutRow);

			DataTable->RowStruct->CopyScriptStruct(OutRowData, FindRowData);

			return true;
		}
	}

	return false;
}
