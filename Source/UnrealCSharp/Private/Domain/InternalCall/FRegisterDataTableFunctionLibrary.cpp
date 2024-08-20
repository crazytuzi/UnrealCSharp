#include "Binding/Class/FClassBuilder.h"
#include "Binding/Class/TBindingClassBuilder.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Kismet/DataTableFunctionLibrary.h"
#include "CoreMacro/NamespaceMacro.h"

namespace
{
	struct FRegisterDataTableFunctionLibrary
	{
		static bool GetDataTableRowFromNameImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                                  const FGarbageCollectionHandle RowName, MonoObject** OutRow)
		{
			if (const auto InRowName = FCSharpEnvironment::GetEnvironment().GetString<FName>(RowName))
			{
				if (InRowName->IsNone())
				{
					return false;
				}

				if (const auto DataTable = FCSharpEnvironment::GetEnvironment().GetObject<
					UDataTable>(InGarbageCollectionHandle))
				{
					FCSharpEnvironment::GetEnvironment().Bind<false>(DataTable->RowStruct.Get());

					if (const auto ClassDescriptor = FCSharpEnvironment::GetEnvironment().GetClassDescriptor(
						DataTable->RowStruct.Get()))
					{
						*OutRow = FCSharpEnvironment::GetEnvironment().GetDomain()->
						                                               Object_Init(ClassDescriptor->GetMonoClass());

						const auto FindRowData = *DataTable->GetRowMap().Find(*InRowName);

						const auto OutRowData = FCSharpEnvironment::GetEnvironment().GetStruct(
							*FGarbageCollectionHandle::MonoObject2GarbageCollectionHandle(*OutRow));

						DataTable->RowStruct->CopyScriptStruct(OutRowData, FindRowData);

						return true;
					}
				}
			}

			return false;
		}

		FRegisterDataTableFunctionLibrary()
		{
			TBindingClassBuilder<UDataTableFunctionLibrary>(NAMESPACE_LIBRARY)
				.Function("GetDataTableRowFromName", GetDataTableRowFromNameImplementation);
		}
	};

	FRegisterDataTableFunctionLibrary RegisterDataTableFunctionLibrary;
}
