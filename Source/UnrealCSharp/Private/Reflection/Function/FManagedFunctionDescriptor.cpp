#include "Reflection/Function/FManagedFunctionDescriptor.h"
#include "Reflection/FReflectionRegistry.h"
#include "Domain/FDomain.h"

bool FManagedFunctionDescriptor::Invoke(const FMethodReflection* InMethod,
                                        const IManagedHandle InManagedHandle,
                                        const TFunctionRef<void*(int32)>& InPropertyAddress,
                                        void* InReturnAddress,
                                        const TFunctionRef<void*(const FPropertyDescriptor*)>& InOutPropertyAddress)
{
	TArray<void*> CSharpParams;

	CSharpParams.Reserve(PropertyDescriptors.Num());

	TArray<IManagedHandle> CompoundManagedHandles;

	CompoundManagedHandles.Reserve(PropertyDescriptors.Num());

	TArray<int32> CompoundPropertyIndexes;

	CompoundPropertyIndexes.Init(INDEX_NONE, PropertyDescriptors.Num());

	for (auto Index = 0; Index < PropertyDescriptors.Num(); ++Index)
	{
		if (const auto PropertyDescriptor = PropertyDescriptors[Index])
		{
			auto PropertyAddress = InPropertyAddress(Index);

			if (PropertyDescriptor->IsPrimitiveProperty())
			{
				CSharpParams.Add(PropertyAddress);
			}
			else
			{
				IManagedHandle ManagedHandle{};

				PropertyDescriptor->Get<FPropertyArgument::FParameter>(PropertyAddress,
				                                                       reinterpret_cast<void**>(&ManagedHandle));

				CompoundManagedHandles.Add(ManagedHandle);

				CompoundPropertyIndexes[Index] = CompoundManagedHandles.Num() - 1;

				CSharpParams.Add(&CompoundManagedHandles.Last());
			}
		}
	}

	if (auto ReturnValue = InMethod->Runtime_Invoke(InManagedHandle, CSharpParams.GetData());
		IManagedHandleIsValid(ReturnValue) && ReturnPropertyDescriptor != nullptr)
	{
		if (ReturnPropertyDescriptor->IsPrimitiveProperty())
		{
			if (const auto UnBoxResultValue = FDomain::Object_Unbox(ReturnValue))
			{
				ReturnPropertyDescriptor->Set(UnBoxResultValue, InReturnAddress);
			}
		}
		else
		{
			ReturnPropertyDescriptor->Set(&ReturnValue, InReturnAddress);
		}

		FDomain::GCHandle_Free(ReturnValue);
	}

	for (const auto Index : OutPropertyIndexes)
	{
		if (const auto OutPropertyDescriptor = PropertyDescriptors[Index])
		{
			if (const auto OutAddress = InOutPropertyAddress(OutPropertyDescriptor))
			{
				if (!OutPropertyDescriptor->IsPrimitiveProperty())
				{
					if (const auto CompoundPropertyIndex = CompoundPropertyIndexes[Index];
						CompoundPropertyIndex != INDEX_NONE &&
						CompoundManagedHandles.IsValidIndex(CompoundPropertyIndex))
					{
						if (auto ManagedHandle = CompoundManagedHandles[CompoundPropertyIndex];
							IManagedHandleIsValid(ManagedHandle))
						{
							OutPropertyDescriptor->Set(&ManagedHandle, OutAddress);
						}
					}
				}
			}
		}
	}

	return true;
}
