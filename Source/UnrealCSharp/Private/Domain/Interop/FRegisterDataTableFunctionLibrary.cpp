#include "Binding/Class/FClassBuilder.h"
#include "Binding/Class/TBindingClassBuilder.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Domain/Script/IManagedTypes.h"
#include "Domain/Script/IUnmanagedBool.h"
#include "Kismet/DataTableFunctionLibrary.h"
#include "CoreMacro/NamespaceMacro.h"

namespace
{
	struct FRegisterDataTableFunctionLibrary
	{
		static IUnmanagedBool GetDataTableRowFromNameImplementation(const IManagedHandle InManagedHandle,
		                                                            const IManagedHandle RowName,
		                                                            IManagedObject* OutRow)
		{
			if (const auto InRowName = FCSharpEnvironment::GetEnvironment().GetString<FName>(RowName))
			{
				if (InRowName->IsNone())
				{
					return IUnmanagedFalse;
				}

				if (const auto DataTable = FCSharpEnvironment::GetEnvironment().GetObject<
					UDataTable>(InManagedHandle))
				{
					FCSharpEnvironment::GetEnvironment().Bind<false>(DataTable->RowStruct.Get());

					const auto Class = FReflectionRegistry::Get().GetClass(DataTable->RowStruct);

					*OutRow = IManagedHandleToIManagedObject(Class->InitObject());

					const auto FindRowData = *DataTable->GetRowMap().Find(*InRowName);

					const auto OutRowData = FCSharpEnvironment::GetEnvironment().GetStruct<>(
						Class->GetGCHandle(*OutRow));

					DataTable->RowStruct->CopyScriptStruct(OutRowData, FindRowData);

					return IUnmanagedTrue;
				}
			}

			return IUnmanagedFalse;
		}

		FRegisterDataTableFunctionLibrary()
		{
			TBindingClassBuilder<UDataTableFunctionLibrary>(NAMESPACE_LIBRARY)
				.Function("GetDataTableRowFromName", GetDataTableRowFromNameImplementation);
		}
	};

	[[maybe_unused]] FRegisterDataTableFunctionLibrary RegisterDataTableFunctionLibrary;
}
