#include "Components/InputComponent.h"
#include "Engine/DynamicBlueprintBinding.h"
#include "Engine/InputActionDelegateBinding.h"
#include "Engine/InputAxisDelegateBinding.h"
#include "Engine/InputAxisKeyDelegateBinding.h"
#include "Engine/InputKeyDelegateBinding.h"
#include "Engine/InputTouchDelegateBinding.h"
#include "Engine/InputVectorAxisDelegateBinding.h"
#include "Binding/Class/TBindingClassBuilder.inl"
#include "Environment/FCSharpEnvironment.h"
#include "UEVersion.h"

namespace
{
	struct FRegisterInputComponent
	{
		static IManagedHandle GetDynamicBindingObjectImplementation(const IManagedHandle InThisClass,
		                                                            const IManagedHandle InBindingClass)
		{
			const auto ThisClass = FCSharpEnvironment::GetEnvironment().GetObject<
				UBlueprintGeneratedClass>(InThisClass);

			const auto BindingClass = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(InBindingClass);

			if (ThisClass != nullptr && BindingClass != nullptr)
			{
				auto DynamicBindingObject = UBlueprintGeneratedClass::GetDynamicBindingObject(ThisClass, BindingClass);

				if (DynamicBindingObject == nullptr)
				{
					DynamicBindingObject = NewObject<UDynamicBlueprintBinding>(GetTransientPackage(), BindingClass);

					ThisClass->DynamicBindingObjects.Add(DynamicBindingObject);
				}

				return FCSharpEnvironment::GetEnvironment().Bind(DynamicBindingObject);
			}

			return InvalidManagedHandle;
		}

		template <typename T>
		static void BindImplementation(const IManagedHandle InManagedHandle,
		                               const IManagedHandle InInputDelegateBinding,
		                               const IManagedHandle InObjectToBindTo,
		                               const IManagedHandle InFunctionNameToBind,
		                               const TFunction<void(UClass*, const FName*)>& InFunction
		)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<UInputComponent>(
				InManagedHandle))
			{
				const auto InputDelegateBinding = FCSharpEnvironment::GetEnvironment().GetObject<T>(
					InInputDelegateBinding);

				const auto ObjectToBindTo = FCSharpEnvironment::GetEnvironment().GetObject<UObject>(InObjectToBindTo);

				InputDelegateBinding->BindToInputComponent(FoundObject, ObjectToBindTo);

				InFunction(ObjectToBindTo->GetClass(),
				           FCSharpEnvironment::GetEnvironment().GetString<FName>(InFunctionNameToBind));
			}
		}

		static void BindActionImplementation(const IManagedHandle InManagedHandle,
		                                     const IManagedHandle InInputActionDelegateBinding,
		                                     const IManagedHandle InObjectToBindTo,
		                                     const IManagedHandle InFunctionNameToBind)
		{
			BindImplementation<UInputActionDelegateBinding>(
				InManagedHandle,
				InInputActionDelegateBinding,
				InObjectToBindTo,
				InFunctionNameToBind,
				[](UClass* InClass, const FName* InFunctionName)
				{
					BindFunction(InClass, InFunctionName, [](UFunction* InFunction)
					{
						const auto Property = new FStructProperty(InFunction, TEXT("Key"), RF_Public | RF_Transient);

#if UE_F_PROPERTY_SET_ELEMENT_SIZE
						Property->SetElementSize(FKey::StaticStruct()->GetStructureSize());
#else
						Property->ElementSize = FKey::StaticStruct()->GetStructureSize();
#endif

						Property->Struct = FKey::StaticStruct();

						Property->SetPropertyFlags(CPF_Parm);

						InFunction->AddCppProperty(Property);
					});
				}
			);
		}

		static void BindAxisImplementation(const IManagedHandle InManagedHandle,
		                                   const IManagedHandle InInputAxisDelegateBinding,
		                                   const IManagedHandle InObjectToBindTo,
		                                   const IManagedHandle InFunctionNameToBind)
		{
			BindImplementation<UInputAxisDelegateBinding>(
				InManagedHandle,
				InInputAxisDelegateBinding,
				InObjectToBindTo,
				InFunctionNameToBind,
				[](UClass* InClass, const FName* InFunctionName)
				{
					BindFunction(InClass, InFunctionName, [](UFunction* InFunction)
					{
						const auto Property = new FFloatProperty(InFunction, TEXT("AxisValue"),
						                                         RF_Public | RF_Transient);

						Property->SetPropertyFlags(CPF_Parm);

						InFunction->AddCppProperty(Property);
					});
				});
		}

		static void BindAxisKeyImplementation(const IManagedHandle InManagedHandle,
		                                      const IManagedHandle InInputAxisKeyDelegateBinding,
		                                      const IManagedHandle InObjectToBindTo,
		                                      const IManagedHandle InFunctionNameToBind)
		{
			BindImplementation<UInputAxisKeyDelegateBinding>(
				InManagedHandle,
				InInputAxisKeyDelegateBinding,
				InObjectToBindTo,
				InFunctionNameToBind,
				[](UClass* InClass, const FName* InFunctionName)
				{
					BindFunction(InClass, InFunctionName, [](UFunction* InFunction)
					{
						const auto Property = new FFloatProperty(InFunction, TEXT("AxisValue"),
						                                         RF_Public | RF_Transient);

						Property->SetPropertyFlags(CPF_Parm);

						InFunction->AddCppProperty(Property);
					});
				});
		}

		static void BindKeyImplementation(const IManagedHandle InManagedHandle,
		                                  const IManagedHandle InInputKeyDelegateBinding,
		                                  const IManagedHandle InObjectToBindTo,
		                                  const IManagedHandle InFunctionNameToBind)
		{
			BindImplementation<UInputKeyDelegateBinding>(
				InManagedHandle,
				InInputKeyDelegateBinding,
				InObjectToBindTo,
				InFunctionNameToBind,
				[](UClass* InClass, const FName* InFunctionName)
				{
					BindFunction(InClass, InFunctionName, [](UFunction* InFunction)
					{
						const auto Property = new FStructProperty(InFunction, TEXT("Key"), RF_Public | RF_Transient);

#if UE_F_PROPERTY_SET_ELEMENT_SIZE
						Property->SetElementSize(FKey::StaticStruct()->GetStructureSize());
#else
						Property->ElementSize = FKey::StaticStruct()->GetStructureSize();
#endif

						Property->Struct = FKey::StaticStruct();

						Property->SetPropertyFlags(CPF_Parm);

						InFunction->AddCppProperty(Property);
					});
				});
		}

		static void BindTouchImplementation(const IManagedHandle InManagedHandle,
		                                    const IManagedHandle InInputTouchDelegateBinding,
		                                    const IManagedHandle InObjectToBindTo,
		                                    const IManagedHandle InFunctionNameToBind)
		{
			BindImplementation<UInputTouchDelegateBinding>(
				InManagedHandle,
				InInputTouchDelegateBinding,
				InObjectToBindTo,
				InFunctionNameToBind,
				[](UClass* InClass, const FName* InFunctionName)
				{
					BindFunction(InClass, InFunctionName, [](UFunction* InFunction)
					{
						const auto LocationProperty = new FStructProperty(InFunction, TEXT("Location"),
						                                                  RF_Public | RF_Transient);

#if UE_F_PROPERTY_SET_ELEMENT_SIZE
						LocationProperty->SetElementSize(TBaseStructure<FVector2D>().Get()->GetStructureSize());
#else
						LocationProperty->ElementSize = TBaseStructure<FVector2D>().Get()->GetStructureSize();
#endif

						LocationProperty->Struct = TBaseStructure<FVector2D>().Get();

						LocationProperty->SetPropertyFlags(CPF_Parm);

						InFunction->AddCppProperty(LocationProperty);

						const auto FingerIndexProperty = new FEnumProperty(InFunction, TEXT("FingerIndex"),
						                                                   RF_Public | RF_Transient);

#if UE_F_PROPERTY_SET_ELEMENT_SIZE
						FingerIndexProperty->SetElementSize(sizeof(uint8));
#else
						FingerIndexProperty->ElementSize = sizeof(uint8);
#endif

						FingerIndexProperty->SetEnum(StaticEnum<ETouchIndex::Type>());

						FingerIndexProperty->SetPropertyFlags(CPF_Parm);

						InFunction->AddCppProperty(FingerIndexProperty);
					});
				});
		}

		static void BindVectorAxisImplementation(const IManagedHandle InManagedHandle,
		                                         const IManagedHandle InInputVectorAxisDelegateBinding,
		                                         const IManagedHandle InObjectToBindTo,
		                                         const IManagedHandle InFunctionNameToBind)
		{
			BindImplementation<UInputVectorAxisDelegateBinding>(
				InManagedHandle,
				InInputVectorAxisDelegateBinding,
				InObjectToBindTo,
				InFunctionNameToBind,
				[](UClass* InClass, const FName* InFunctionName)
				{
					BindFunction(InClass, InFunctionName, [](UFunction* InFunction)
					{
						const auto Property = new FStructProperty(InFunction, TEXT("AxisValue"),
						                                          RF_Public | RF_Transient);

#if UE_F_PROPERTY_SET_ELEMENT_SIZE
						Property->SetElementSize(TBaseStructure<FVector2D>().Get()->GetStructureSize());
#else
						Property->ElementSize = TBaseStructure<FVector2D>().Get()->GetStructureSize();
#endif

						Property->Struct = TBaseStructure<FVector2D>().Get();

						Property->SetPropertyFlags(CPF_Parm);

						InFunction->AddCppProperty(Property);
					});
				});
		}

		static void BindFunction(UClass* InClass, const FName* InFunctionName,
		                         const TFunction<void(UFunction* InFunction)>& InProperty)
		{
			if (InClass == nullptr || InFunctionName == nullptr)
			{
				return;
			}

			if (InClass->FindFunctionByName(*InFunctionName))
			{
				return;
			}

			const auto Function = NewObject<UFunction>(InClass, *InFunctionName, EObjectFlags::RF_Transient);

			Function->FunctionFlags = FUNC_BlueprintEvent;

			InProperty(Function);

			Function->Bind();

			Function->StaticLink(true);

			InClass->AddFunctionToFunctionMap(Function, *InFunctionName);

			Function->Next = InClass->Children;

			InClass->Children = Function;

			Function->AddToRoot();

			FCSharpEnvironment::GetEnvironment().GetBind()->Bind(FCSharpEnvironment::GetEnvironment().GetRegistry<
				                                                     FClassRegistry>()->GetClassDescriptor(InClass),
			                                                     InClass,
			                                                     Function
			);
		}

		static void ClearBindingValuesImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<UInputComponent>(
				InManagedHandle))
			{
				FoundObject->ClearBindingValues();
			}
		}

		FRegisterInputComponent()
		{
			TBindingClassBuilder<UInputComponent>(NAMESPACE_LIBRARY)
				.Function("GetDynamicBindingObject", GetDynamicBindingObjectImplementation)
				.Function("BindAction", BindActionImplementation)
				.Function("BindAxis", BindAxisImplementation)
				.Function("BindAxisKey", BindAxisKeyImplementation)
				.Function("BindKey", BindKeyImplementation)
				.Function("BindTouch", BindTouchImplementation)
				.Function("BindVectorAxis", BindVectorAxisImplementation)
				.Function("ClearBindingValues", ClearBindingValuesImplementation);
		}
	};

	[[maybe_unused]] FRegisterInputComponent RegisterInputComponent;
}
