#include "Domain/InternalCall/UDataTableFunctionLibrary.h"
#include "Binding/Class/FBindingClassBuilder.h"
#include "Bridge/FTypeBridge.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct UDataTableRegistry
{
	UDataTableRegistry()
	{
		FBindingClassBuilder(TEXT("UDataTableFunctionLibrary"), NAMESPACE_LIBRARY)
			.Function("GetDataTableRowFromName",
					  static_cast<void*>(
						  UDataTableFunctionLibraryImplementation::UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation))
			.Register();
	}
};

static UDataTableRegistry UDataTableRegistry;


bool UDataTableFunctionLibraryImplementation::UDataTableFunctionLibrary_GetDataTableRowFromNameImplementation(
	MonoObject* InTable,
	MonoString* InRowName,
	MonoObject** OutRow)
{
	const FName RowName = UTF8_TO_TCHAR(FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(InRowName));

	const UDataTable* DataTable = FCSharpEnvironment::GetEnvironment()->GetObject<UDataTable>(InTable);

	const bool IsBind = FCSharpEnvironment::GetEnvironment()->Bind(DataTable->RowStruct.Get(), false);

	const auto StructDescriptor = FCSharpEnvironment::GetEnvironment()->GetClassDescriptor(DataTable->RowStruct.Get());
	
	if (!IsBind || StructDescriptor == nullptr)
	{
		return false;
	}
	
	*OutRow = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(StructDescriptor->GetMonoClass());

	const auto FindRowData = *DataTable->GetRowMap().Find(RowName);

	const auto OutRowData = FCSharpEnvironment::GetEnvironment()->GetStruct(*OutRow);

	DataTable->RowStruct->CopyScriptStruct(OutRowData, FindRowData);

	return true;
}
