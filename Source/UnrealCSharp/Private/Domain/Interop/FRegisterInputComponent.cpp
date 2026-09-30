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

		template <typename TUnifiedDelegate>
		static bool IsBoundTo(const TUnifiedDelegate& InUnifiedDelegate, const UObject* InObject,
		                      const FName& InFunctionName)
		{
			const auto& DynamicDelegate = InUnifiedDelegate.GetDynamicDelegate();

			return DynamicDelegate.GetUObject() == InObject && DynamicDelegate.GetFunctionName() == InFunctionName;
		}

		static bool IsBoundTo(const FInputActionBinding& InActionBinding, const UObject* InObject,
		                      const FName& InActionName, const EInputEvent InKeyEvent)
		{
			return InActionBinding.ActionDelegate.GetUObject() == InObject &&
				InActionBinding.GetActionName() == InActionName && InActionBinding.KeyEvent.GetValue() == InKeyEvent;
		}

		static bool IsBoundTo(const FInputKeyBinding& InKeyBinding, const UObject* InObject,
		                      const FInputChord& InInputChord, const EInputEvent InKeyEvent)
		{
			return InKeyBinding.KeyDelegate.GetUObject() == InObject && InKeyBinding.Chord == InInputChord &&
				InKeyBinding.KeyEvent.GetValue() == InKeyEvent;
		}

		template <auto TUnifiedDelegate, typename TBinding>
		static bool HasBinding(const TArray<TBinding>& InBindings, const UObject* InObject,
		                       const FName& InFunctionName)
		{
			for (const auto& Binding : InBindings)
			{
				if (IsBoundTo(Binding.*TUnifiedDelegate, InObject, InFunctionName))
				{
					return true;
				}
			}

			return false;
		}

		static bool HasActionBinding(const UInputComponent* InInputComponent, const UObject* InObject,
		                             const FName& InActionName, const EInputEvent InKeyEvent)
		{
			for (auto Index = 0; Index < InInputComponent->GetNumActionBindings(); ++Index)
			{
				if (IsBoundTo(InInputComponent->GetActionBinding(Index), InObject, InActionName, InKeyEvent))
				{
					return true;
				}
			}

			return false;
		}

		static bool HasKeyBinding(const UInputComponent* InInputComponent, const UObject* InObject,
		                          const FInputChord& InInputChord, const EInputEvent InKeyEvent)
		{
			for (const auto& KeyBinding : InInputComponent->KeyBindings)
			{
				if (IsBoundTo(KeyBinding, InObject, InInputChord, InKeyEvent))
				{
					return true;
				}
			}

			return false;
		}

		template <auto TUnifiedDelegate, typename TBinding>
		static void Unbind(TArray<TBinding>& InBindings, const UObject* InObject, const FName& InFunctionName)
		{
			for (auto Index = InBindings.Num() - 1; Index >= 0; --Index)
			{
				if (IsBoundTo(InBindings[Index].*TUnifiedDelegate, InObject, InFunctionName))
				{
					InBindings.RemoveAt(Index, EAllowShrinking::No);
				}
			}
		}

		template <typename TEntry, typename TProcess>
		static void BindImplementation(const IManagedHandle InManagedHandle,
		                               const IManagedHandle InBlueprintInputDelegateBinding,
		                               const IManagedHandle InObjectToBindTo,
		                               const TProcess& InProcess)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<UInputComponent>(
				InManagedHandle))
			{
				const auto FoundInputBinding = FCSharpEnvironment::GetEnvironment().GetStruct<TEntry>(
					InBlueprintInputDelegateBinding);

				const auto ObjectToBindTo = FCSharpEnvironment::GetEnvironment().GetObject<UObject>(InObjectToBindTo);

				if (FoundInputBinding != nullptr && ObjectToBindTo != nullptr)
				{
					InProcess(FoundObject, ObjectToBindTo, *FoundInputBinding);
				}
			}
		}

		template <typename TKey, typename TProcess>
		static void UnbindImplementation(const IManagedHandle InManagedHandle,
		                                 const IManagedHandle InObjectToBindTo,
		                                 const TKey* InKey,
		                                 const TProcess& InProcess)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<UInputComponent>(
				InManagedHandle))
			{
				const auto ObjectToBindTo = FCSharpEnvironment::GetEnvironment().GetObject<UObject>(InObjectToBindTo);

				if (ObjectToBindTo != nullptr && InKey != nullptr)
				{
					InProcess(FoundObject, ObjectToBindTo, InKey);
				}
			}
		}

		static void BindActionImplementation(const IManagedHandle InManagedHandle,
		                                     const IManagedHandle InBlueprintInputActionDelegateBinding,
		                                     const IManagedHandle InObjectToBindTo)
		{
			BindImplementation<FBlueprintInputActionDelegateBinding>(
				InManagedHandle,
				InBlueprintInputActionDelegateBinding,
				InObjectToBindTo,
				[](UInputComponent* InFoundObject, UObject* InObjectToBindTo,
				   const FBlueprintInputActionDelegateBinding& InBinding)
				{
					if (!HasActionBinding(InFoundObject, InObjectToBindTo, InBinding.InputActionName,
					                      InBinding.InputKeyEvent))
					{
						BindFunction(InObjectToBindTo->GetClass(), &InBinding.FunctionNameToBind,
						             [](UFunction* InFunction)
						             {
#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
							             const auto Property = new FStructProperty(
								             InFunction, TEXT("Key"), RF_Public | RF_Transient);
#else
							             const auto Property = new FStructProperty(InFunction, TEXT("Key"));
#endif

#if UE_F_PROPERTY_SET_ELEMENT_SIZE
							             Property->SetElementSize(FKey::StaticStruct()->GetStructureSize());
#else
							             Property->ElementSize = FKey::StaticStruct()->GetStructureSize();
#endif

							             Property->Struct = FKey::StaticStruct();

							             Property->SetPropertyFlags(CPF_Parm);

							             InFunction->AddCppProperty(Property);
						             });

						FInputActionBinding ActionBinding(InBinding.InputActionName, InBinding.InputKeyEvent);

						ActionBinding.bConsumeInput = InBinding.bConsumeInput;

						ActionBinding.bExecuteWhenPaused = InBinding.bExecuteWhenPaused;

						ActionBinding.ActionDelegate.BindDelegate(InObjectToBindTo, InBinding.FunctionNameToBind);

						InFoundObject->AddActionBinding(ActionBinding);
					}
				});
		}

		static void BindAxisImplementation(const IManagedHandle InManagedHandle,
		                                   const IManagedHandle InBlueprintInputAxisDelegateBinding,
		                                   const IManagedHandle InObjectToBindTo)
		{
			BindImplementation<FBlueprintInputAxisDelegateBinding>(
				InManagedHandle,
				InBlueprintInputAxisDelegateBinding,
				InObjectToBindTo,
				[](UInputComponent* InFoundObject, UObject* InObjectToBindTo,
				   const FBlueprintInputAxisDelegateBinding& InBinding)
				{
					if (!HasBinding<&FInputAxisBinding::AxisDelegate>(InFoundObject->AxisBindings, InObjectToBindTo,
					                                                  InBinding.FunctionNameToBind))
					{
						BindFunction(InObjectToBindTo->GetClass(), &InBinding.FunctionNameToBind,
						             [](UFunction* InFunction)
						             {
#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
							             const auto Property = new FFloatProperty(
								             InFunction, TEXT("AxisValue"), RF_Public | RF_Transient);
#else
							             const auto Property = new FFloatProperty(InFunction, TEXT("AxisValue"));
#endif

							             Property->SetPropertyFlags(CPF_Parm);

							             InFunction->AddCppProperty(Property);
						             });

						FInputAxisBinding AxisBinding(InBinding.InputAxisName);

						AxisBinding.bConsumeInput = InBinding.bConsumeInput;

						AxisBinding.bExecuteWhenPaused = InBinding.bExecuteWhenPaused;

						AxisBinding.AxisDelegate.BindDelegate(InObjectToBindTo, InBinding.FunctionNameToBind);

						InFoundObject->AxisBindings.Add(AxisBinding);
					}
				});
		}

		static void BindAxisKeyImplementation(const IManagedHandle InManagedHandle,
		                                      const IManagedHandle InBlueprintInputAxisKeyDelegateBinding,
		                                      const IManagedHandle InObjectToBindTo)
		{
			BindImplementation<FBlueprintInputAxisKeyDelegateBinding>(
				InManagedHandle,
				InBlueprintInputAxisKeyDelegateBinding,
				InObjectToBindTo,
				[](UInputComponent* InFoundObject, UObject* InObjectToBindTo,
				   const FBlueprintInputAxisKeyDelegateBinding& InBinding)
				{
					if (!HasBinding<&FInputAxisKeyBinding::AxisDelegate>(InFoundObject->AxisKeyBindings,
					                                                     InObjectToBindTo,
					                                                     InBinding.FunctionNameToBind))
					{
						BindFunction(InObjectToBindTo->GetClass(), &InBinding.FunctionNameToBind,
						             [](UFunction* InFunction)
						             {
#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
							             const auto Property = new FFloatProperty(
								             InFunction, TEXT("AxisValue"), RF_Public | RF_Transient);
#else
							             const auto Property = new FFloatProperty(InFunction, TEXT("AxisValue"));
#endif

							             Property->SetPropertyFlags(CPF_Parm);

							             InFunction->AddCppProperty(Property);
						             });

						FInputAxisKeyBinding AxisKeyBinding(InBinding.AxisKey);

						AxisKeyBinding.bConsumeInput = InBinding.bConsumeInput;

						AxisKeyBinding.bExecuteWhenPaused = InBinding.bExecuteWhenPaused;

						AxisKeyBinding.AxisDelegate.BindDelegate(InObjectToBindTo, InBinding.FunctionNameToBind);

						InFoundObject->AxisKeyBindings.Add(AxisKeyBinding);
					}
				});
		}

		static void BindKeyImplementation(const IManagedHandle InManagedHandle,
		                                  const IManagedHandle InBlueprintInputKeyDelegateBinding,
		                                  const IManagedHandle InObjectToBindTo)
		{
			BindImplementation<FBlueprintInputKeyDelegateBinding>(
				InManagedHandle,
				InBlueprintInputKeyDelegateBinding,
				InObjectToBindTo,
				[](UInputComponent* InFoundObject, UObject* InObjectToBindTo,
				   const FBlueprintInputKeyDelegateBinding& InBinding)
				{
					if (!HasKeyBinding(InFoundObject, InObjectToBindTo, InBinding.InputChord, InBinding.InputKeyEvent))
					{
						BindFunction(InObjectToBindTo->GetClass(), &InBinding.FunctionNameToBind,
						             [](UFunction* InFunction)
						             {
#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
							             const auto Property = new FStructProperty(
								             InFunction, TEXT("Key"), RF_Public | RF_Transient);
#else
							             const auto Property = new FStructProperty(InFunction, TEXT("Key"));
#endif

#if UE_F_PROPERTY_SET_ELEMENT_SIZE
							             Property->SetElementSize(FKey::StaticStruct()->GetStructureSize());
#else
							             Property->ElementSize = FKey::StaticStruct()->GetStructureSize();
#endif

							             Property->Struct = FKey::StaticStruct();

							             Property->SetPropertyFlags(CPF_Parm);

							             InFunction->AddCppProperty(Property);
						             });

						FInputKeyBinding KeyBinding(InBinding.InputChord, InBinding.InputKeyEvent);

						KeyBinding.bConsumeInput = InBinding.bConsumeInput;

						KeyBinding.bExecuteWhenPaused = InBinding.bExecuteWhenPaused;

						KeyBinding.KeyDelegate.BindDelegate(InObjectToBindTo, InBinding.FunctionNameToBind);

						InFoundObject->KeyBindings.Add(KeyBinding);
					}
				});
		}

		static void BindTouchImplementation(const IManagedHandle InManagedHandle,
		                                    const IManagedHandle InBlueprintInputTouchDelegateBinding,
		                                    const IManagedHandle InObjectToBindTo)
		{
			BindImplementation<FBlueprintInputTouchDelegateBinding>(
				InManagedHandle,
				InBlueprintInputTouchDelegateBinding,
				InObjectToBindTo,
				[](UInputComponent* InFoundObject, UObject* InObjectToBindTo,
				   const FBlueprintInputTouchDelegateBinding& InBinding)
				{
					if (!HasBinding<&FInputTouchBinding::TouchDelegate>(InFoundObject->TouchBindings, InObjectToBindTo,
					                                                    InBinding.FunctionNameToBind))
					{
						BindFunction(InObjectToBindTo->GetClass(), &InBinding.FunctionNameToBind,
						             [](UFunction* InFunction)
						             {
#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
							             const auto LocationProperty = new FStructProperty(
								             InFunction, TEXT("Location"), RF_Public | RF_Transient);
#else
							             const auto LocationProperty = new FStructProperty(
								             InFunction, TEXT("Location"));
#endif

#if UE_F_PROPERTY_SET_ELEMENT_SIZE
							             LocationProperty->SetElementSize(
								             TBaseStructure<FVector2D>().Get()->GetStructureSize());
#else
							             LocationProperty->ElementSize = TBaseStructure<FVector2D>().Get()->
								             GetStructureSize();
#endif

							             LocationProperty->Struct = TBaseStructure<FVector2D>().Get();

							             LocationProperty->SetPropertyFlags(CPF_Parm);

							             InFunction->AddCppProperty(LocationProperty);

#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
							             const auto FingerIndexProperty = new FEnumProperty(
								             InFunction, TEXT("FingerIndex"), RF_Public | RF_Transient);
#else
							             const auto FingerIndexProperty = new FEnumProperty(
								             InFunction, TEXT("FingerIndex"));
#endif

#if UE_F_PROPERTY_SET_ELEMENT_SIZE
							             FingerIndexProperty->SetElementSize(sizeof(uint8));
#else
							             FingerIndexProperty->ElementSize = sizeof(uint8);
#endif

							             FingerIndexProperty->SetEnum(StaticEnum<ETouchIndex::Type>());

							             FingerIndexProperty->SetPropertyFlags(CPF_Parm);

							             InFunction->AddCppProperty(FingerIndexProperty);
						             });

						FInputTouchBinding TouchBinding(InBinding.InputKeyEvent);

						TouchBinding.bConsumeInput = InBinding.bConsumeInput;

						TouchBinding.bExecuteWhenPaused = InBinding.bExecuteWhenPaused;

						TouchBinding.TouchDelegate.BindDelegate(InObjectToBindTo, InBinding.FunctionNameToBind);

						InFoundObject->TouchBindings.Add(TouchBinding);
					}
				});
		}

		static void BindVectorAxisImplementation(const IManagedHandle InManagedHandle,
		                                         const IManagedHandle InBlueprintInputAxisKeyDelegateBinding,
		                                         const IManagedHandle InObjectToBindTo)
		{
			BindImplementation<FBlueprintInputAxisKeyDelegateBinding>(
				InManagedHandle,
				InBlueprintInputAxisKeyDelegateBinding,
				InObjectToBindTo,
				[](UInputComponent* InFoundObject, UObject* InObjectToBindTo,
				   const FBlueprintInputAxisKeyDelegateBinding& InBinding)
				{
					if (!HasBinding<&FInputVectorAxisBinding::AxisDelegate>(InFoundObject->VectorAxisBindings,
					                                                        InObjectToBindTo,
					                                                        InBinding.FunctionNameToBind))
					{
						BindFunction(InObjectToBindTo->GetClass(), &InBinding.FunctionNameToBind,
						             [](UFunction* InFunction)
						             {
#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
							             const auto Property = new FStructProperty(
								             InFunction, TEXT("AxisValue"), RF_Public | RF_Transient);
#else
							             const auto Property = new FStructProperty(
								             InFunction, TEXT("AxisValue"));
#endif

#if UE_F_PROPERTY_SET_ELEMENT_SIZE
							             Property->SetElementSize(
								             TBaseStructure<FVector2D>().Get()->GetStructureSize());
#else
							             Property->ElementSize = TBaseStructure<FVector2D>().Get()->
								             GetStructureSize();
#endif

							             Property->Struct = TBaseStructure<FVector2D>().Get();

							             Property->SetPropertyFlags(CPF_Parm);

							             InFunction->AddCppProperty(Property);
						             });

						FInputVectorAxisBinding VectorAxisBinding(InBinding.AxisKey);

						VectorAxisBinding.bConsumeInput = InBinding.bConsumeInput;

						VectorAxisBinding.bExecuteWhenPaused = InBinding.bExecuteWhenPaused;

						VectorAxisBinding.AxisDelegate.BindDelegate(InObjectToBindTo, InBinding.FunctionNameToBind);

						InFoundObject->VectorAxisBindings.Add(VectorAxisBinding);
					}
				});
		}

		static void UnbindActionImplementation(const IManagedHandle InManagedHandle,
		                                       const IManagedHandle InObjectToBindTo,
		                                       const IManagedHandle InActionName,
		                                       const int32 InKeyEvent)
		{
			UnbindImplementation(
				InManagedHandle,
				InObjectToBindTo,
				FCSharpEnvironment::GetEnvironment().GetString<FName>(InActionName),
				[InKeyEvent](UInputComponent* InFoundObject, UObject* InObjectToBindTo, const FName* InActionName)
				{
					for (auto Index = InFoundObject->GetNumActionBindings() - 1; Index >= 0; --Index)
					{
						if (IsBoundTo(InFoundObject->GetActionBinding(Index), InObjectToBindTo, *InActionName,
						              static_cast<EInputEvent>(InKeyEvent)))
						{
							InFoundObject->RemoveActionBinding(Index);
						}
					}
				});
		}

		static void UnbindAxisImplementation(const IManagedHandle InManagedHandle,
		                                     const IManagedHandle InObjectToBindTo,
		                                     const IManagedHandle InFunctionNameToBind)
		{
			UnbindImplementation(
				InManagedHandle,
				InObjectToBindTo,
				FCSharpEnvironment::GetEnvironment().GetString<FName>(InFunctionNameToBind),
				[](UInputComponent* InFoundObject, UObject* InObjectToBindTo, const FName* InFunctionName)
				{
					Unbind<&FInputAxisBinding::AxisDelegate>(InFoundObject->AxisBindings, InObjectToBindTo,
					                                         *InFunctionName);
				});
		}

		static void UnbindAxisKeyImplementation(const IManagedHandle InManagedHandle,
		                                        const IManagedHandle InObjectToBindTo,
		                                        const IManagedHandle InFunctionNameToBind)
		{
			UnbindImplementation(
				InManagedHandle,
				InObjectToBindTo,
				FCSharpEnvironment::GetEnvironment().GetString<FName>(InFunctionNameToBind),
				[](UInputComponent* InFoundObject, UObject* InObjectToBindTo, const FName* InFunctionName)
				{
					Unbind<&FInputAxisKeyBinding::AxisDelegate>(InFoundObject->AxisKeyBindings, InObjectToBindTo,
					                                            *InFunctionName);
				});
		}

		static void UnbindKeyImplementation(const IManagedHandle InManagedHandle,
		                                    const IManagedHandle InObjectToBindTo,
		                                    const IManagedHandle InInputChord,
		                                    const int32 InKeyEvent)
		{
			UnbindImplementation(
				InManagedHandle,
				InObjectToBindTo,
				FCSharpEnvironment::GetEnvironment().GetStruct<FInputChord>(InInputChord),
				[InKeyEvent](UInputComponent* InFoundObject, UObject* InObjectToBindTo, const FInputChord* InInputChord)
				{
					for (auto Index = InFoundObject->KeyBindings.Num() - 1; Index >= 0; --Index)
					{
						if (IsBoundTo(InFoundObject->KeyBindings[Index], InObjectToBindTo, *InInputChord,
						              static_cast<EInputEvent>(InKeyEvent)))
						{
							InFoundObject->KeyBindings.RemoveAt(Index, EAllowShrinking::No);
						}
					}
				});
		}

		static void UnbindTouchImplementation(const IManagedHandle InManagedHandle,
		                                      const IManagedHandle InObjectToBindTo,
		                                      const IManagedHandle InFunctionNameToBind)
		{
			UnbindImplementation(
				InManagedHandle,
				InObjectToBindTo,
				FCSharpEnvironment::GetEnvironment().GetString<FName>(InFunctionNameToBind),
				[](UInputComponent* InFoundObject, UObject* InObjectToBindTo, const FName* InFunctionName)
				{
					Unbind<&FInputTouchBinding::TouchDelegate>(InFoundObject->TouchBindings, InObjectToBindTo,
					                                           *InFunctionName);
				});
		}

		static void UnbindVectorAxisImplementation(const IManagedHandle InManagedHandle,
		                                           const IManagedHandle InObjectToBindTo,
		                                           const IManagedHandle InFunctionNameToBind)
		{
			UnbindImplementation(
				InManagedHandle,
				InObjectToBindTo,
				FCSharpEnvironment::GetEnvironment().GetString<FName>(InFunctionNameToBind),
				[](UInputComponent* InFoundObject, UObject* InObjectToBindTo, const FName* InFunctionName)
				{
					Unbind<&FInputVectorAxisBinding::AxisDelegate>(InFoundObject->VectorAxisBindings, InObjectToBindTo,
					                                               *InFunctionName);
				});
		}

		static void BindFunction(UClass* InClass, const FName* InFunctionName,
		                         const TFunction<void(UFunction* InFunction)>& InProperty)
		{
			if (InClass == nullptr || InFunctionName == nullptr)
			{
				return;
			}

			if (const auto FoundFunction = InClass->FindFunctionByName(*InFunctionName))
			{
				FoundFunction->RemoveFromRoot();

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

		static int32 GetNumActionBindingsImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<UInputComponent>(
				InManagedHandle))
			{
				return FoundObject->GetNumActionBindings();
			}

			return 0;
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
				.Function("UnbindAction", UnbindActionImplementation)
				.Function("UnbindAxis", UnbindAxisImplementation)
				.Function("UnbindAxisKey", UnbindAxisKeyImplementation)
				.Function("UnbindKey", UnbindKeyImplementation)
				.Function("UnbindTouch", UnbindTouchImplementation)
				.Function("UnbindVectorAxis", UnbindVectorAxisImplementation)
				.Function("GetNumActionBindings", GetNumActionBindingsImplementation)
				.Function("ClearBindingValues", ClearBindingValuesImplementation);
		}
	};

	[[maybe_unused]] FRegisterInputComponent RegisterInputComponent;
}
