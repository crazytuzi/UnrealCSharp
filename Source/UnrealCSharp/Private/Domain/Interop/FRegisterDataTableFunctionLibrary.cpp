#include "Binding/Class/FClassBuilder.h"
#include "Binding/Class/TBindingClassBuilder.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Kismet/DataTableFunctionLibrary.h"
#include "CoreMacro/NamespaceMacro.h"

namespace
{
	struct FRegisterDataTableFunctionLibrary
	{
		static uint8 GetDataTableRowFromNameImplementation(const IManagedHandle InManagedHandle,
		                                                   const IManagedHandle RowName,
		                                                   IManagedHandle* OutRow)
		{
			if (const auto InRowName = FCSharpEnvironment::GetEnvironment().GetString<FName>(RowName))
			{
				if (InRowName->IsNone())
				{
					return 0;
				}

				if (const auto DataTable = FCSharpEnvironment::GetEnvironment().GetObject<
					UDataTable>(InManagedHandle))
				{
					FCSharpEnvironment::GetEnvironment().Bind<false>(DataTable->RowStruct.Get());

					const auto Class = FReflectionRegistry::Get().GetClass(DataTable->RowStruct);

					*OutRow = Class->InitObject();

					const auto FindRowData = *DataTable->GetRowMap().Find(*InRowName);

					const auto OutRowData = FCSharpEnvironment::GetEnvironment().GetStruct<>(*OutRow);

					DataTable->RowStruct->CopyScriptStruct(OutRowData, FindRowData);

					return 1;
				}
			}

			return 0;
		}

		FRegisterDataTableFunctionLibrary()
		{
			TBindingClassBuilder<UDataTableFunctionLibrary>(NAMESPACE_LIBRARY)
				.Function("GetDataTableRowFromName", GetDataTableRowFromNameImplementation);
		}
	};

	[[maybe_unused]] FRegisterDataTableFunctionLibrary RegisterDataTableFunctionLibrary;
}
