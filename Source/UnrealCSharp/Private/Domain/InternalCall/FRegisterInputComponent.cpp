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
		static MonoObject* GetDynamicBindingObjectImplementation(const FGarbageCollectionHandle InThisClass,
		                                                         const FGarbageCollectionHandle InBindingClass)
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

			return nullptr;
		}

		template <typename T>
		static void BindImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                               const FGarbageCollectionHandle InInputDelegateBinding,
		                               const FGarbageCollectionHandle InObjectToBindTo,
		                               const FGarbageCollectionHandle InFunctionNameToBind,
		                               const TFunction<void(UClass*, const FName*)>& InFunction
		)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<UInputComponent>(
				InGarbageCollectionHandle))
			{
				const auto InputDelegateBinding = FCSharpEnvironment::GetEnvironment().GetObject<T>(
					InInputDelegateBinding);

				const auto ObjectToBindTo = FCSharpEnvironment::GetEnvironment().GetObject<UObject>(InObjectToBindTo);

				InputDelegateBinding->BindToInputComponent(FoundObject, ObjectToBindTo);

				InFunction(ObjectToBindTo->GetClass(),
				           FCSharpEnvironment::GetEnvironment().GetString<FName>(InFunctionNameToBind));
			}
		}

		static void BindActionImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                     const FGarbageCollectionHandle InInputActionDelegateBinding,
		                                     const FGarbageCollectionHandle InObjectToBindTo,
		                                     const FGarbageCollectionHandle InFunctionNameToBind)
		{
			BindImplementation<UInputActionDelegateBinding>(
				InGarbageCollectionHandle,
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

		static void BindAxisImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                   const FGarbageCollectionHandle InInputAxisDelegateBinding,
		                                   const FGarbageCollectionHandle InObjectToBindTo,
		                                   const FGarbageCollectionHandle InFunctionNameToBind)
		{
			BindImplementation<UInputAxisDelegateBinding>(
				InGarbageCollectionHandle,
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

		static void BindAxisKeyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                      const FGarbageCollectionHandle InInputAxisKeyDelegateBinding,
		                                      const FGarbageCollectionHandle InObjectToBindTo,
		                                      const FGarbageCollectionHandle InFunctionNameToBind)
		{
			BindImplementation<UInputAxisKeyDelegateBinding>(
				InGarbageCollectionHandle,
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

		static void BindKeyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                  const FGarbageCollectionHandle InInputKeyDelegateBinding,
		                                  const FGarbageCollectionHandle InObjectToBindTo,
		                                  const FGarbageCollectionHandle InFunctionNameToBind)
		{
			BindImplementation<UInputKeyDelegateBinding>(
				InGarbageCollectionHandle,
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

		static void BindTouchImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                    const FGarbageCollectionHandle InInputTouchDelegateBinding,
		                                    const FGarbageCollectionHandle InObjectToBindTo,
		                                    const FGarbageCollectionHandle InFunctionNameToBind)
		{
			BindImplementation<UInputTouchDelegateBinding>(
				InGarbageCollectionHandle,
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

		static void BindVectorAxisImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                         const FGarbageCollectionHandle InInputVectorAxisDelegateBinding,
		                                         const FGarbageCollectionHandle InObjectToBindTo,
		                                         const FGarbageCollectionHandle InFunctionNameToBind)
		{
			BindImplementation<UInputVectorAxisDelegateBinding>(
				InGarbageCollectionHandle,
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

			FCSharpEnvironment::GetEnvironment().GetBind()->Bind(FCSharpEnvironment::GetEnvironment().GetDomain(),
			                                                     FCSharpEnvironment::GetEnvironment().GetRegistry<
				                                                     FClassRegistry>()->GetClassDescriptor(InClass),
			                                                     InClass,
			                                                     Function
			);
		}

		static void ClearBindingValuesImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<UInputComponent>(
				InGarbageCollectionHandle))
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
