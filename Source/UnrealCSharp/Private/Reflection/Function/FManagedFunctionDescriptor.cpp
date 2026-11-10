#include "Reflection/Function/FManagedFunctionDescriptor.h"
#include "Reflection/FReflectionRegistry.h"
#include "Domain/FDomain.h"
#include "UEVersion.h"
#include "UObject/FieldPathProperty.h"
#if UE_F_OPTIONAL_PROPERTY
#include "UObject/PropertyOptional.h"
#endif

bool FManagedFunctionDescriptor::Invoke(const FMethodReflection* InMethod,
                                        const IManagedHandle InManagedHandle,
                                        const TFunctionRef<void*(int32)>& InPropertyAddress,
                                        void* InReturnAddress,
                                        const TFunctionRef<void*(const FPropertyDescriptor*)>& InOutPropertyAddress)
{
	if (InMethod != nullptr)
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
					const auto Property = PropertyDescriptor->GetProperty();

					IManagedHandle ManagedHandle{};

					if (PropertyAddress != nullptr &&
						!ReferencePropertyIndexes.Contains(Index) &&
						Property != nullptr &&
						IsCopyValueProperty(Property))
					{
						PropertyDescriptor->Get<FPropertyArgument::FReturn>(
							PropertyDescriptor->CopyValue(PropertyAddress),
							reinterpret_cast<void**>(&ManagedHandle));
					}
					else
					{
						PropertyDescriptor->Get<FPropertyArgument::FParameter>(
							PropertyAddress, reinterpret_cast<void**>(&ManagedHandle));
					}

					CompoundManagedHandles.Add(ManagedHandle);

					CompoundPropertyIndexes[Index] = CompoundManagedHandles.Num() - 1;

					CSharpParams.Add(&CompoundManagedHandles.Last());
				}
			}
		}

		if (auto ReturnValue = InMethod->Runtime_Invoke(InManagedHandle, CSharpParams.GetData());
			ReturnValue != ExceptionManagedHandle && IManagedHandleIsValid(ReturnValue) &&
			ReturnPropertyDescriptor != nullptr)
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

		const auto ManagedHandles = CompoundManagedHandles;

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

								if (ManagedHandles[CompoundPropertyIndex] != ManagedHandle)
								{
									FDomain::GCHandle_Free(ManagedHandle);
								}
							}
						}
					}
				}
			}
		}

		return true;
	}

	return false;
}

bool FManagedFunctionDescriptor::IsCopyValueProperty(const FProperty* InProperty)
{
	return InProperty->IsA<FNameProperty>() ||
		InProperty->IsA<FStructProperty>() ||
		InProperty->IsA<FArrayProperty>() ||
		InProperty->IsA<FStrProperty>() ||
#if UE_F_UTF8_STR_PROPERTY
		InProperty->IsA<FUtf8StrProperty>() ||
#endif
#if UE_F_ANSI_STR_PROPERTY
		InProperty->IsA<FAnsiStrProperty>() ||
#endif
		InProperty->IsA<FTextProperty>() ||
		InProperty->IsA<FMapProperty>() ||
		InProperty->IsA<FSetProperty>() ||
		InProperty->IsA<FFieldPathProperty>()
#if UE_F_OPTIONAL_PROPERTY
		|| InProperty->IsA<FOptionalProperty>();
#else
		;
#endif
}
