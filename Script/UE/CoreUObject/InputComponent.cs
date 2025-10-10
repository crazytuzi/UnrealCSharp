using System;
using Script.CoreUObject;
using Script.InputCore;
using Script.Library;
using Script.Slate;

namespace Script.Engine
{
    public partial class UInputComponent
    {
        public void BindAction(FName InActionName, EInputEvent InKeyEvent, UObject InObject, Action<FKey> InAction)
        {
            var InputActionDelegateBinding = UInputComponentImplementation
                .UInputComponent_GetDynamicBindingObjectImplementation<UInputActionDelegateBinding>(
                    InObject.GetClass().GarbageCollectionHandle,
                    UInputActionDelegateBinding.StaticClass().GarbageCollectionHandle);

            if (InputActionDelegateBinding != null)
            {
                foreach (var InputActionDelegate in InputActionDelegateBinding.InputActionDelegateBindings)
                {
                    if (InputActionDelegate.InputActionName == InActionName &&
                        InputActionDelegate.InputKeyEvent == InKeyEvent &&
                        InputActionDelegate.FunctionNameToBind.ToString() == InAction.Method.Name)
                    {
                        return;
                    }
                }

                var Binding = new FBlueprintInputActionDelegateBinding
                {
                    InputActionName = InActionName,
                    InputKeyEvent = InKeyEvent,
                    FunctionNameToBind = InAction.Method.Name
                };

                InputActionDelegateBinding.InputActionDelegateBindings.Add(Binding);

                UInputComponentImplementation.UInputComponent_BindActionImplementation(
                    GarbageCollectionHandle,
                    InputActionDelegateBinding.GarbageCollectionHandle,
                    InObject.GarbageCollectionHandle,
                    Binding.FunctionNameToBind.GarbageCollectionHandle);
            }
        }

        public void BindAxis(FName InAxisName, UObject InObject, Action<float> InAction)
        {
            var InputAxisDelegateBinding = UInputComponentImplementation
                .UInputComponent_GetDynamicBindingObjectImplementation<UInputAxisDelegateBinding>(
                    InObject.GetClass().GarbageCollectionHandle,
                    UInputAxisDelegateBinding.StaticClass().GarbageCollectionHandle);

            if (InputAxisDelegateBinding != null)
            {
                foreach (var InputAxisDelegate in InputAxisDelegateBinding.InputAxisDelegateBindings)
                {
                    if (InputAxisDelegate.InputAxisName == InAxisName &&
                        InputAxisDelegate.FunctionNameToBind.ToString() == InAction.Method.Name)
                    {
                        return;
                    }
                }

                var Binding = new FBlueprintInputAxisDelegateBinding
                {
                    InputAxisName = InAxisName,
                    FunctionNameToBind = InAction.Method.Name
                };

                InputAxisDelegateBinding.InputAxisDelegateBindings.Add(Binding);

                UInputComponentImplementation.UInputComponent_BindAxisImplementation(
                    GarbageCollectionHandle,
                    InputAxisDelegateBinding.GarbageCollectionHandle,
                    InObject.GarbageCollectionHandle,
                    Binding.FunctionNameToBind.GarbageCollectionHandle);
            }
        }

        public void BindAxisKey(FKey InKey, UObject InObject, Action<float> InAction)
        {
            var InputAxisKeyDelegateBinding = UInputComponentImplementation
                .UInputComponent_GetDynamicBindingObjectImplementation<UInputAxisKeyDelegateBinding>(
                    InObject.GetClass().GarbageCollectionHandle,
                    UInputAxisKeyDelegateBinding.StaticClass().GarbageCollectionHandle);

            if (InputAxisKeyDelegateBinding != null)
            {
                foreach (var InputAxisKeyDelegate in InputAxisKeyDelegateBinding.InputAxisKeyDelegateBindings)
                {
                    if (InputAxisKeyDelegate.AxisKey == InKey &&
                        InputAxisKeyDelegate.FunctionNameToBind.ToString() == InAction.Method.Name)
                    {
                        return;
                    }
                }

                var Binding = new FBlueprintInputAxisKeyDelegateBinding
                {
                    AxisKey = InKey,
                    FunctionNameToBind = InAction.Method.Name
                };

                InputAxisKeyDelegateBinding.InputAxisKeyDelegateBindings.Add(Binding);

                UInputComponentImplementation.UInputComponent_BindAxisKeyImplementation(
                    GarbageCollectionHandle,
                    InputAxisKeyDelegateBinding.GarbageCollectionHandle,
                    InObject.GarbageCollectionHandle,
                    Binding.FunctionNameToBind.GarbageCollectionHandle);
            }
        }

        public void BindKey(FInputChord InInputChord, EInputEvent InKeyEvent, UObject InObject, Action<FKey> InAction)
        {
            var InputKeyDelegateBinding = UInputComponentImplementation
                .UInputComponent_GetDynamicBindingObjectImplementation<UInputKeyDelegateBinding>(
                    InObject.GetClass().GarbageCollectionHandle,
                    UInputKeyDelegateBinding.StaticClass().GarbageCollectionHandle);

            if (InputKeyDelegateBinding != null)
            {
                foreach (var InputKeyDelegate in InputKeyDelegateBinding.InputKeyDelegateBindings)
                {
                    if (InputKeyDelegate.InputChord == InInputChord &&
                        InputKeyDelegate.InputKeyEvent == InKeyEvent &&
                        InputKeyDelegate.FunctionNameToBind.ToString() == InAction.Method.Name)
                    {
                        return;
                    }
                }

                var Binding = new FBlueprintInputKeyDelegateBinding
                {
                    InputChord = InInputChord,
                    InputKeyEvent = InKeyEvent,
                    FunctionNameToBind = InAction.Method.Name
                };

                InputKeyDelegateBinding.InputKeyDelegateBindings.Add(Binding);

                UInputComponentImplementation.UInputComponent_BindKeyImplementation(
                    GarbageCollectionHandle,
                    InputKeyDelegateBinding.GarbageCollectionHandle,
                    InObject.GarbageCollectionHandle,
                    Binding.FunctionNameToBind.GarbageCollectionHandle);
            }
        }

        public void BindKey(FKey InKey, EInputEvent InKeyEvent, UObject InObject, Action<FKey> InAction)
        {
            BindKey(new FInputChord
                {
                    Key = InKey,
                    bShift = false,
                    bCtrl = false,
                    bAlt = false,
                    bCmd = false
                },
                InKeyEvent,
                InObject,
                InAction);
        }

        public void BindTouch(EInputEvent InKeyEvent, UObject InObject, Action<ETouchIndex, FVector> InAction)
        {
            var InputTouchDelegateBinding = UInputComponentImplementation
                .UInputComponent_GetDynamicBindingObjectImplementation<UInputTouchDelegateBinding>(
                    InObject.GetClass().GarbageCollectionHandle,
                    UInputTouchDelegateBinding.StaticClass().GarbageCollectionHandle);

            if (InputTouchDelegateBinding != null)
            {
                foreach (var InputTouchDelegate in InputTouchDelegateBinding.InputTouchDelegateBindings)
                {
                    if (InputTouchDelegate.InputKeyEvent == InKeyEvent &&
                        InputTouchDelegate.FunctionNameToBind.ToString() == InAction.Method.Name)
                    {
                        return;
                    }
                }

                var Binding = new FBlueprintInputTouchDelegateBinding
                {
                    InputKeyEvent = InKeyEvent,
                    FunctionNameToBind = InAction.Method.Name
                };

                InputTouchDelegateBinding.InputTouchDelegateBindings.Add(Binding);

                UInputComponentImplementation.UInputComponent_BindTouchImplementation(
                    GarbageCollectionHandle,
                    InputTouchDelegateBinding.GarbageCollectionHandle,
                    InObject.GarbageCollectionHandle,
                    Binding.FunctionNameToBind.GarbageCollectionHandle);
            }
        }

        public void BindVectorAxis(FKey InKey, UObject InObject, Action<FVector> InAction)
        {
            var InputVectorAxisDelegateBinding = UInputComponentImplementation
                .UInputComponent_GetDynamicBindingObjectImplementation<UInputVectorAxisDelegateBinding>(
                    InObject.GetClass().GarbageCollectionHandle,
                    UInputVectorAxisDelegateBinding.StaticClass().GarbageCollectionHandle);

            if (InputVectorAxisDelegateBinding != null)
            {
                foreach (var InputAxisKeyDelegate in InputVectorAxisDelegateBinding.InputAxisKeyDelegateBindings)
                {
                    if (InputAxisKeyDelegate.AxisKey == InKey &&
                        InputAxisKeyDelegate.FunctionNameToBind.ToString() == InAction.Method.Name)
                    {
                        return;
                    }
                }

                var Binding = new FBlueprintInputAxisKeyDelegateBinding
                {
                    AxisKey = InKey,
                    FunctionNameToBind = InAction.Method.Name
                };

                InputVectorAxisDelegateBinding.InputAxisKeyDelegateBindings.Add(Binding);

                UInputComponentImplementation.UInputComponent_BindVectorAxisImplementation(
                    GarbageCollectionHandle,
                    InputVectorAxisDelegateBinding.GarbageCollectionHandle,
                    InObject.GarbageCollectionHandle,
                    Binding.FunctionNameToBind.GarbageCollectionHandle);
            }
        }

        public void RemoveAction(FName InActionName, EInputEvent InKeyEvent, UObject InObject, Action<FKey> InAction)
        {
            var InputActionDelegateBinding = UInputComponentImplementation
                .UInputComponent_GetDynamicBindingObjectImplementation<UInputActionDelegateBinding>(
                    InObject.GetClass().GarbageCollectionHandle,
                    UInputActionDelegateBinding.StaticClass().GarbageCollectionHandle);

            if (InputActionDelegateBinding != null)
            {
                foreach (var InputActionDelegate in InputActionDelegateBinding.InputActionDelegateBindings)
                {
                    if (InputActionDelegate.InputActionName == InActionName &&
                        InputActionDelegate.InputKeyEvent == InKeyEvent &&
                        InputActionDelegate.FunctionNameToBind.ToString() == InAction.Method.Name)
                    {
                        InputActionDelegateBinding.InputActionDelegateBindings.Remove(InputActionDelegate);

                        break;
                    }
                }
            }

            InObject.GetClass().RemoveFunction(InAction.Method.Name);
        }

        public void RemoveAxis(FName InAxisName, UObject InObject, Action<float> InAction)
        {
            var InputAxisDelegateBinding = UInputComponentImplementation
                .UInputComponent_GetDynamicBindingObjectImplementation<UInputAxisDelegateBinding>(
                    InObject.GetClass().GarbageCollectionHandle,
                    UInputAxisDelegateBinding.StaticClass().GarbageCollectionHandle);

            if (InputAxisDelegateBinding != null)
            {
                foreach (var InputAxisDelegate in InputAxisDelegateBinding.InputAxisDelegateBindings)
                {
                    if (InputAxisDelegate.InputAxisName == InAxisName &&
                        InputAxisDelegate.FunctionNameToBind.ToString() == InAction.Method.Name)
                    {
                        InputAxisDelegateBinding.InputAxisDelegateBindings.Remove(InputAxisDelegate);

                        break;
                    }
                }
            }

            InObject.GetClass().RemoveFunction(InAction.Method.Name);
        }

        public void RemoveAxisKey(FKey InKey, UObject InObject, Action<float> InAction)
        {
            var InputAxisKeyDelegateBinding = UInputComponentImplementation
                .UInputComponent_GetDynamicBindingObjectImplementation<UInputAxisKeyDelegateBinding>(
                    InObject.GetClass().GarbageCollectionHandle,
                    UInputAxisKeyDelegateBinding.StaticClass().GarbageCollectionHandle);

            if (InputAxisKeyDelegateBinding != null)
            {
                foreach (var InputAxisKeyDelegate in InputAxisKeyDelegateBinding.InputAxisKeyDelegateBindings)
                {
                    if (InputAxisKeyDelegate.AxisKey == InKey &&
                        InputAxisKeyDelegate.FunctionNameToBind.ToString() == InAction.Method.Name)
                    {
                        InputAxisKeyDelegateBinding.InputAxisKeyDelegateBindings.Remove(InputAxisKeyDelegate);

                        break;
                    }
                }
            }

            InObject.GetClass().RemoveFunction(InAction.Method.Name);
        }

        public void RemoveKey(FInputChord InInputChord, EInputEvent InKeyEvent, UObject InObject, Action<FKey> InAction)
        {
            var InputKeyDelegateBinding = UInputComponentImplementation
                .UInputComponent_GetDynamicBindingObjectImplementation<UInputKeyDelegateBinding>(
                    InObject.GetClass().GarbageCollectionHandle,
                    UInputKeyDelegateBinding.StaticClass().GarbageCollectionHandle);

            if (InputKeyDelegateBinding != null)
            {
                foreach (var InputKeyDelegate in InputKeyDelegateBinding.InputKeyDelegateBindings)
                {
                    if (InputKeyDelegate.InputChord == InInputChord &&
                        InputKeyDelegate.InputKeyEvent == InKeyEvent &&
                        InputKeyDelegate.FunctionNameToBind.ToString() == InAction.Method.Name)
                    {
                        InputKeyDelegateBinding.InputKeyDelegateBindings.Remove(InputKeyDelegate);

                        break;
                    }
                }
            }

            InObject.GetClass().RemoveFunction(InAction.Method.Name);
        }

        public void RemoveKey(FKey InKey, EInputEvent InKeyEvent, UObject InObject, Action<FKey> InAction)
        {
            RemoveKey(new FInputChord
                {
                    Key = InKey,
                    bShift = false,
                    bCtrl = false,
                    bAlt = false,
                    bCmd = false
                },
                InKeyEvent,
                InObject,
                InAction);
        }

        public void RemoveTouch(EInputEvent InKeyEvent, UObject InObject, Action<ETouchIndex, FVector> InAction)
        {
            var InputTouchDelegateBinding = UInputComponentImplementation
                .UInputComponent_GetDynamicBindingObjectImplementation<UInputTouchDelegateBinding>(
                    InObject.GetClass().GarbageCollectionHandle,
                    UInputTouchDelegateBinding.StaticClass().GarbageCollectionHandle);

            if (InputTouchDelegateBinding != null)
            {
                foreach (var InputTouchDelegate in InputTouchDelegateBinding.InputTouchDelegateBindings)
                {
                    if (InputTouchDelegate.InputKeyEvent == InKeyEvent &&
                        InputTouchDelegate.FunctionNameToBind.ToString() == InAction.Method.Name)
                    {
                        InputTouchDelegateBinding.InputTouchDelegateBindings.Remove(InputTouchDelegate);

                        break;
                    }
                }
            }

            InObject.GetClass().RemoveFunction(InAction.Method.Name);
        }

        public void RemoveVectorAxis(FKey InKey, UObject InObject, Action<FVector> InAction)
        {
            var InputVectorAxisDelegateBinding = UInputComponentImplementation
                .UInputComponent_GetDynamicBindingObjectImplementation<UInputVectorAxisDelegateBinding>(
                    InObject.GetClass().GarbageCollectionHandle,
                    UInputVectorAxisDelegateBinding.StaticClass().GarbageCollectionHandle);

            if (InputVectorAxisDelegateBinding != null)
            {
                foreach (var InputAxisKeyDelegate in InputVectorAxisDelegateBinding.InputAxisKeyDelegateBindings)
                {
                    if (InputAxisKeyDelegate.AxisKey == InKey &&
                        InputAxisKeyDelegate.FunctionNameToBind.ToString() == InAction.Method.Name)
                    {
                        InputVectorAxisDelegateBinding.InputAxisKeyDelegateBindings.Remove(InputAxisKeyDelegate);

                        break;
                    }
                }
            }

            InObject.GetClass().RemoveFunction(InAction.Method.Name);
        }

        public void ClearBindingValues(UObject InObject)
        {
            UInputComponentImplementation.UInputComponent_ClearBindingValuesImplementation(GarbageCollectionHandle);
        }
    }
}