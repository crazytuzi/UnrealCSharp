using System;
using Script.CoreUObject;
using Script.Library;

namespace Script.EnhancedInput
{
    public partial class UEnhancedInputComponent
    {
        public FEnhancedInputActionEventBinding BindAction<T>(ETriggerEvent InTriggerEvent,
            UObject InObject, Action<FInputActionValue, float, float, UInputAction> InAction)
            where T : UInputAction, IStaticClass
        {
            return BindAction(Unreal.LoadObject<T>(this), InTriggerEvent, InObject, InAction);
        }

        public FEnhancedInputActionEventBinding BindAction(UInputAction InInputAction, ETriggerEvent InTriggerEvent,
            UObject InObject, Action<FInputActionValue, float, float, UInputAction> InAction)
        {
            var EnhancedInputActionDelegateBinding = UEnhancedInputComponentImplementation
                .UEnhancedInputComponent_GetDynamicBindingObjectImplementation<UEnhancedInputActionDelegateBinding>(
                    InObject.GetClass().GarbageCollectionHandle,
                    UEnhancedInputActionDelegateBinding.StaticClass().GarbageCollectionHandle);

            if (EnhancedInputActionDelegateBinding != null)
            {
                foreach (var InputActionDelegate in EnhancedInputActionDelegateBinding.InputActionDelegateBindings)
                {
                    if (InputActionDelegate.InputAction == InInputAction &&
                        InputActionDelegate.TriggerEvent == InTriggerEvent &&
                        InputActionDelegate.FunctionNameToBind.ToString() == InAction.Method.Name)
                    {
                        return null;
                    }
                }

                var Binding = new FBlueprintEnhancedInputActionBinding
                {
                    InputAction = InInputAction,
                    TriggerEvent = InTriggerEvent,
                    FunctionNameToBind = InAction.Method.Name
                };

                EnhancedInputActionDelegateBinding.InputActionDelegateBindings.Add(Binding);

                return UEnhancedInputComponentImplementation.UEnhancedInputComponent_BindActionImplementation(
                    GarbageCollectionHandle, Binding.GarbageCollectionHandle, InObject.GarbageCollectionHandle,
                    Binding.FunctionNameToBind.GarbageCollectionHandle);
            }

            return null;
        }

        public void RemoveAction(UObject InObject, FEnhancedInputActionEventBinding InEnhancedInputActionEventBinding,
            Action<FInputActionValue, float, float, UInputAction> InAction)
        {
            var EnhancedInputActionDelegateBinding = UEnhancedInputComponentImplementation
                .UEnhancedInputComponent_GetDynamicBindingObjectImplementation<UEnhancedInputActionDelegateBinding>(
                    InObject.GetClass().GarbageCollectionHandle,
                    UEnhancedInputActionDelegateBinding.StaticClass().GarbageCollectionHandle);

            if (EnhancedInputActionDelegateBinding != null)
            {
                foreach (var InputActionDelegate in EnhancedInputActionDelegateBinding.InputActionDelegateBindings)
                {
                    if (InputActionDelegate.InputAction == InEnhancedInputActionEventBinding.GetAction() &&
                        InputActionDelegate.TriggerEvent == InEnhancedInputActionEventBinding.GetTriggerEvent() &&
                        InputActionDelegate.FunctionNameToBind.ToString() == InAction.Method.Name)
                    {
                        EnhancedInputActionDelegateBinding.InputActionDelegateBindings.Remove(InputActionDelegate);

                        break;
                    }
                }
            }

            UEnhancedInputComponentImplementation.UEnhancedInputComponent_RemoveBindingImplementation(
                GarbageCollectionHandle,
                InEnhancedInputActionEventBinding.GarbageCollectionHandle);

            InObject.GetClass().RemoveFunction(InAction.Method.Name);
        }
    }
}