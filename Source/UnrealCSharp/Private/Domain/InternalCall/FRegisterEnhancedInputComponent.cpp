#include "EnhancedInputComponent.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Engine/DynamicBlueprintBinding.h"
#include "EnhancedInputActionDelegateBinding.h"
#include "Binding/Class/TBindingClassBuilder.inl"
#include "Environment/FCSharpEnvironment.h"
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

		static void BindActionFunction(UClass* InClass, const FName* InFunctionName)
		{
			BindFunction(InClass, InFunctionName, [](UFunction* InFunction)
			{
				const auto SourceActionProperty = new FObjectProperty(InFunction, TEXT("SourceAction"),
				                                                      RF_Public | RF_Transient);

				SourceActionProperty->PropertyClass = UInputAction::StaticClass();

				SourceActionProperty->SetPropertyFlags(CPF_Parm);

				InFunction->AddCppProperty(SourceActionProperty);

				const auto TriggeredTimeProperty = new FFloatProperty(InFunction, TEXT("TriggeredTime"),
				                                                      RF_Public | RF_Transient);

				TriggeredTimeProperty->SetPropertyFlags(CPF_Parm);

				InFunction->AddCppProperty(TriggeredTimeProperty);

				const auto ElapsedTimeProperty = new FFloatProperty(InFunction, TEXT("ElapsedTime"),
				                                                    RF_Public | RF_Transient);

				ElapsedTimeProperty->SetPropertyFlags(CPF_Parm);

				InFunction->AddCppProperty(ElapsedTimeProperty);

				const auto ActionValueProperty = new FStructProperty(InFunction, TEXT("ActionValue"),
				                                                     RF_Public | RF_Transient);

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

		static MonoObject* BindActionImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                            const FGarbageCollectionHandle
		                                            InBlueprintEnhancedInputActionBinding,
		                                            const FGarbageCollectionHandle InObjectToBindTo,
		                                            const FGarbageCollectionHandle InFunctionNameToBind)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<UEnhancedInputComponent>(
				InGarbageCollectionHandle))
			{
				const auto [InputAction, TriggerEvent, FunctionNameToBind] = *FCSharpEnvironment::GetEnvironment().
					GetStruct<FBlueprintEnhancedInputActionBinding>(InBlueprintEnhancedInputActionBinding);

				const auto ObjectToBindTo = FCSharpEnvironment::GetEnvironment().GetObject<UObject>(InObjectToBindTo);

				const auto& EnhancedInputActionEventBinding = FoundObject->BindAction(
					InputAction,
					TriggerEvent,
					ObjectToBindTo,
					FunctionNameToBind
				);

				BindActionFunction(ObjectToBindTo->GetClass(),
				                   FCSharpEnvironment::GetEnvironment().GetString<FName>(InFunctionNameToBind));

				const auto FoundMonoClass = TPropertyClass<
					FEnhancedInputActionEventBinding, FEnhancedInputActionEventBinding>::Get();

				const auto SrcMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

				FCSharpEnvironment::GetEnvironment().AddBindingReference<
					std::decay_t<FEnhancedInputActionEventBinding>, false>(
					SrcMonoObject, &EnhancedInputActionEventBinding);

				return SrcMonoObject;
			}

			return nullptr;
		}

		static void RemoveBindingImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                        const FGarbageCollectionHandle InEnhancedInputActionEventBinding)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<UEnhancedInputComponent>(
				InGarbageCollectionHandle))
			{
				const auto EnhancedInputActionEventBinding = FCSharpEnvironment::GetEnvironment().GetBinding<
					FEnhancedInputActionEventBinding>(InEnhancedInputActionEventBinding);

				FoundObject->RemoveBinding(*EnhancedInputActionEventBinding);
			}
		}

		FRegisterEnhancedInputComponent()
		{
			TBindingClassBuilder<UEnhancedInputComponent>(NAMESPACE_LIBRARY)
				.Function("GetDynamicBindingObject", GetDynamicBindingObjectImplementation)
				.Function("BindAction", BindActionImplementation)
				.Function("RemoveBinding", RemoveBindingImplementation);
		}
	};

	[[maybe_unused]] FRegisterEnhancedInputComponent RegisterEnhancedInputComponent;
}
