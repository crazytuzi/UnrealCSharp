#include "EnhancedInputComponent.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Engine/DynamicBlueprintBinding.h"
#include "EnhancedInputActionDelegateBinding.h"
#include "Binding/Class/TBindingClassBuilder.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Domain/Interop/FRegisterInputComponentHelper.h"
#include "Domain/Script/IManagedHandle.h"
#include "Macro/NamespaceMacro.h"
#include "UEVersion.h"

BINDING_CLASS(FInputBindingHandle)

BINDING_CLASS(FEnhancedInputActionEventBinding)

namespace
{
	struct FRegisterInputBindingHandle
	{
		FRegisterInputBindingHandle()
		{
			TBindingClassBuilder<FInputBindingHandle, false>(NAMESPACE_BINDING)
				.Function("GetHandle", BINDING_FUNCTION(&FInputBindingHandle::GetHandle));
		}
	};

	[[maybe_unused]] FRegisterInputBindingHandle RegisterInputBindingHandle;

	struct FRegisterEnhancedInputActionEventBinding
	{
		FRegisterEnhancedInputActionEventBinding()
		{
			TBindingClassBuilder<FEnhancedInputActionEventBinding, false>(NAMESPACE_BINDING)
				.Inheritance<FInputBindingHandle, false>(NAMESPACE_BINDING)
				.Function("GetAction", BINDING_FUNCTION(&FEnhancedInputActionEventBinding::GetAction))
				.Function("GetTriggerEvent", BINDING_FUNCTION(&FEnhancedInputActionEventBinding::GetTriggerEvent));
		}
	};

	[[maybe_unused]] FRegisterEnhancedInputActionEventBinding RegisterEnhancedInputActionEventBinding;

	struct FRegisterEnhancedInputComponent
	{
		static void BindActionFunction(UClass* InClass, const FName* InFunctionName)
		{
			FRegisterInputComponentHelper::BindFunction(InClass, InFunctionName, [](UFunction* InFunction)
			{
#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
				const auto SourceActionProperty = new FObjectProperty(InFunction, TEXT("SourceAction"),
				                                                      RF_Public | RF_Transient);
#else
				const auto SourceActionProperty = new FObjectProperty(InFunction, TEXT("SourceAction"));
#endif

				SourceActionProperty->PropertyClass = UInputAction::StaticClass();

				SourceActionProperty->SetPropertyFlags(CPF_Parm);

				InFunction->AddCppProperty(SourceActionProperty);

#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
				const auto TriggeredTimeProperty = new FFloatProperty(InFunction, TEXT("TriggeredTime"),
				                                                      RF_Public | RF_Transient);
#else
				const auto TriggeredTimeProperty = new FFloatProperty(InFunction, TEXT("TriggeredTime"));
#endif

				TriggeredTimeProperty->SetPropertyFlags(CPF_Parm);

				InFunction->AddCppProperty(TriggeredTimeProperty);

#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
				const auto ElapsedTimeProperty = new FFloatProperty(InFunction, TEXT("ElapsedTime"),
				                                                    RF_Public | RF_Transient);
#else
				const auto ElapsedTimeProperty = new FFloatProperty(InFunction, TEXT("ElapsedTime"));
#endif

				ElapsedTimeProperty->SetPropertyFlags(CPF_Parm);

				InFunction->AddCppProperty(ElapsedTimeProperty);

#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
				const auto ActionValueProperty = new FStructProperty(InFunction, TEXT("ActionValue"),
				                                                     RF_Public | RF_Transient);
#else
				const auto ActionValueProperty = new FStructProperty(InFunction, TEXT("ActionValue"));
#endif

#if UE_F_PROPERTY_SET_ELEMENT_SIZE
				ActionValueProperty->SetElementSize(FInputActionValue::StaticStruct()->GetStructureSize());
#else
				ActionValueProperty->ElementSize = FInputActionValue::StaticStruct()->GetStructureSize();
#endif

				ActionValueProperty->Struct = FInputActionValue::StaticStruct();

				ActionValueProperty->SetPropertyFlags(CPF_Parm);

				InFunction->AddCppProperty(ActionValueProperty);
			});
		}

		static bool HasActionEventBinding(const UEnhancedInputComponent* InEnhancedInputComponent,
		                                  const UInputAction* InInputAction, const ETriggerEvent InTriggerEvent,
		                                  const UObject* InObject)
		{
			for (const auto& ActionEventBinding : InEnhancedInputComponent->GetActionEventBindings())
			{
#if UE_F_ENHANCED_INPUT_ACTION_EVENT_BINDING_IS_BOUND_TO_OBJECT
				if (ActionEventBinding->GetAction() == InInputAction &&
					ActionEventBinding->GetTriggerEvent() == InTriggerEvent &&
					ActionEventBinding->IsBoundToObject(InObject))
#else
				if (ActionEventBinding->GetAction() == InInputAction &&
					ActionEventBinding->GetTriggerEvent() == InTriggerEvent)
#endif
				{
					return true;
				}
			}

			return false;
		}

		static IManagedHandle BindActionImplementation(const IManagedHandle InManagedHandle,
		                                               const IManagedHandle InBlueprintEnhancedInputActionBinding,
		                                               const IManagedHandle InObjectToBindTo,
		                                               const IManagedHandle InFunctionNameToBind)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<UEnhancedInputComponent>(
				InManagedHandle))
			{
				const auto FoundInputBinding = FCSharpEnvironment::GetEnvironment().
					GetStruct<FBlueprintEnhancedInputActionBinding>(InBlueprintEnhancedInputActionBinding);

				const auto ObjectToBindTo = FCSharpEnvironment::GetEnvironment().GetObject<UObject>(InObjectToBindTo);

				const auto FoundFunctionName = FCSharpEnvironment::GetEnvironment().GetString<FName>(
					InFunctionNameToBind);

				const auto FoundClass = TPropertyClass<
					FEnhancedInputActionEventBinding, FEnhancedInputActionEventBinding>::Get();

				if (FoundInputBinding != nullptr && ObjectToBindTo != nullptr &&
					FoundFunctionName != nullptr && FoundClass != nullptr)
				{
					const auto [InputAction, TriggerEvent, FunctionNameToBind] = *FoundInputBinding;

					if (HasActionEventBinding(FoundObject, InputAction, TriggerEvent, ObjectToBindTo))
					{
						return InvalidManagedHandle;
					}

					const auto& EnhancedInputActionEventBinding = FoundObject->BindAction(
						InputAction,
						TriggerEvent,
						ObjectToBindTo,
						FunctionNameToBind
					);

					BindActionFunction(ObjectToBindTo->GetClass(), FoundFunctionName);

					const auto Object = FoundClass->NewObject();

					FCSharpEnvironment::GetEnvironment().AddBindingReference<
						std::decay_t<FEnhancedInputActionEventBinding>>(
						InManagedHandle, FoundClass, Object, &EnhancedInputActionEventBinding);

					return Object;
				}
			}

			return InvalidManagedHandle;
		}

		static int32 GetNumActionEventBindingsImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<UEnhancedInputComponent>(
				InManagedHandle))
			{
				return FoundObject->GetActionEventBindings().Num();
			}

			return 0;
		}

		static void RemoveBindingImplementation(const IManagedHandle InManagedHandle,
		                                        const IManagedHandle InEnhancedInputActionEventBinding)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<UEnhancedInputComponent>(
				InManagedHandle))
			{
				if (const auto EnhancedInputActionEventBinding = FCSharpEnvironment::GetEnvironment().GetBinding<
					FEnhancedInputActionEventBinding>(InEnhancedInputActionEventBinding))
				{
					FoundObject->RemoveBinding(*EnhancedInputActionEventBinding);
				}

				(void)FCSharpEnvironment::GetEnvironment().RemoveBindingReference(InEnhancedInputActionEventBinding);
			}
		}

		FRegisterEnhancedInputComponent()
		{
			TBindingClassBuilder<UEnhancedInputComponent>(NAMESPACE_LIBRARY)
				.Function("GetDynamicBindingObject", FRegisterInputComponentHelper::GetDynamicBindingObject)
				.Function("BindAction", BindActionImplementation)
				.Function("RemoveBinding", RemoveBindingImplementation)
				.Function("GetNumActionEventBindings", GetNumActionEventBindingsImplementation);
		}
	};

	[[maybe_unused]] FRegisterEnhancedInputComponent RegisterEnhancedInputComponent;
}
