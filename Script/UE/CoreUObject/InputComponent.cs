using System;
using Script.CoreUObject;
using Script.InputCore;
using Script.Library;
using Script.Slate;
using Interop;

namespace Script.Engine
{
    public partial class UInputComponent
    {
        public void BindAction(FName InActionName, EInputEvent InKeyEvent, UObject InObject, Action<FKey> InAction)
        {
            var InputActionDelegateBinding = UInputComponentImplementation
                .UInputComponent_GetDynamicBindingObjectImplementation<UInputActionDelegateBinding>(
                    HandleData.GetHandle(InObject.GetClass()),
                    HandleData.GetHandle(UInputActionDelegateBinding.StaticClass()));

            if (InputActionDelegateBinding != null)
            {
                var Bindings = InputActionDelegateBinding.InputActionDelegateBindings;

                var Index = -1;

                for (var BindingIndex = 0; BindingIndex < Bindings.Num(); ++BindingIndex)
                {
                    var InputActionDelegate = Bindings[BindingIndex];

                    if (InputActionDelegate.InputActionName == InActionName &&
                        InputActionDelegate.InputKeyEvent == InKeyEvent &&
                        InputActionDelegate.FunctionNameToBind.ToString() == InAction.Method.Name)
                    {
                        Index = BindingIndex;

                        break;
                    }
                }

                if (Index < 0)
                {
                    Bindings.Add(new FBlueprintInputActionDelegateBinding
                    {
                        InputActionName = InActionName,
                        InputKeyEvent = InKeyEvent,
                        FunctionNameToBind = InAction.Method.Name
                    });

                    Index = Bindings.Num() - 1;
                }

                UInputComponentImplementation.UInputComponent_BindActionImplementation(
                    HandleData.GetHandle(this),
                    HandleData.GetHandle(InputActionDelegateBinding),
                    HandleData.GetHandle(InObject),
                    Index);
            }
        }

        public void BindAxis(FName InAxisName, UObject InObject, Action<float> InAction)
        {
            var InputAxisDelegateBinding = UInputComponentImplementation
                .UInputComponent_GetDynamicBindingObjectImplementation<UInputAxisDelegateBinding>(
                    HandleData.GetHandle(InObject.GetClass()),
                    HandleData.GetHandle(UInputAxisDelegateBinding.StaticClass()));

            if (InputAxisDelegateBinding != null)
            {
                var Bindings = InputAxisDelegateBinding.InputAxisDelegateBindings;

                var Index = -1;

                for (var BindingIndex = 0; BindingIndex < Bindings.Num(); ++BindingIndex)
                {
                    var InputAxisDelegate = Bindings[BindingIndex];

                    if (InputAxisDelegate.InputAxisName == InAxisName &&
                        InputAxisDelegate.FunctionNameToBind.ToString() == InAction.Method.Name)
                    {
                        Index = BindingIndex;

                        break;
                    }
                }

                if (Index < 0)
                {
                    Bindings.Add(new FBlueprintInputAxisDelegateBinding
                    {
                        InputAxisName = InAxisName,
                        FunctionNameToBind = InAction.Method.Name
                    });

                    Index = Bindings.Num() - 1;
                }

                UInputComponentImplementation.UInputComponent_BindAxisImplementation(
                    HandleData.GetHandle(this),
                    HandleData.GetHandle(InputAxisDelegateBinding),
                    HandleData.GetHandle(InObject),
                    Index);
            }
        }

        public void BindAxisKey(FKey InKey, UObject InObject, Action<float> InAction)
        {
            var InputAxisKeyDelegateBinding = UInputComponentImplementation
                .UInputComponent_GetDynamicBindingObjectImplementation<UInputAxisKeyDelegateBinding>(
                    HandleData.GetHandle(InObject.GetClass()),
                    HandleData.GetHandle(UInputAxisKeyDelegateBinding.StaticClass()));

            if (InputAxisKeyDelegateBinding != null)
            {
                var Bindings = InputAxisKeyDelegateBinding.InputAxisKeyDelegateBindings;

                var Index = -1;

                for (var BindingIndex = 0; BindingIndex < Bindings.Num(); ++BindingIndex)
                {
                    var InputAxisKeyDelegate = Bindings[BindingIndex];

                    if (InputAxisKeyDelegate.AxisKey == InKey &&
                        InputAxisKeyDelegate.FunctionNameToBind.ToString() == InAction.Method.Name)
                    {
                        Index = BindingIndex;

                        break;
                    }
                }

                if (Index < 0)
                {
                    Bindings.Add(new FBlueprintInputAxisKeyDelegateBinding
                    {
                        AxisKey = InKey,
                        FunctionNameToBind = InAction.Method.Name
                    });

                    Index = Bindings.Num() - 1;
                }

                UInputComponentImplementation.UInputComponent_BindAxisKeyImplementation(
                    HandleData.GetHandle(this),
                    HandleData.GetHandle(InputAxisKeyDelegateBinding),
                    HandleData.GetHandle(InObject),
                    Index);
            }
        }

        public void BindKey(FInputChord InInputChord, EInputEvent InKeyEvent, UObject InObject, Action<FKey> InAction)
        {
            var InputKeyDelegateBinding = UInputComponentImplementation
                .UInputComponent_GetDynamicBindingObjectImplementation<UInputKeyDelegateBinding>(
                    HandleData.GetHandle(InObject.GetClass()),
                    HandleData.GetHandle(UInputKeyDelegateBinding.StaticClass()));

            if (InputKeyDelegateBinding != null)
            {
                var Bindings = InputKeyDelegateBinding.InputKeyDelegateBindings;

                var Index = -1;

                for (var BindingIndex = 0; BindingIndex < Bindings.Num(); ++BindingIndex)
                {
                    var InputKeyDelegate = Bindings[BindingIndex];

                    if (InputKeyDelegate.InputChord == InInputChord &&
                        InputKeyDelegate.InputKeyEvent == InKeyEvent &&
                        InputKeyDelegate.FunctionNameToBind.ToString() == InAction.Method.Name)
                    {
                        Index = BindingIndex;

                        break;
                    }
                }

                if (Index < 0)
                {
                    Bindings.Add(new FBlueprintInputKeyDelegateBinding
                    {
                        InputChord = InInputChord,
                        InputKeyEvent = InKeyEvent,
                        FunctionNameToBind = InAction.Method.Name
                    });

                    Index = Bindings.Num() - 1;
                }

                UInputComponentImplementation.UInputComponent_BindKeyImplementation(
                    HandleData.GetHandle(this),
                    HandleData.GetHandle(InputKeyDelegateBinding),
                    HandleData.GetHandle(InObject),
                    Index);
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
                    HandleData.GetHandle(InObject.GetClass()),
                    HandleData.GetHandle(UInputTouchDelegateBinding.StaticClass()));

            if (InputTouchDelegateBinding != null)
            {
                var Bindings = InputTouchDelegateBinding.InputTouchDelegateBindings;

                var Index = -1;

                for (var BindingIndex = 0; BindingIndex < Bindings.Num(); ++BindingIndex)
                {
                    var InputTouchDelegate = Bindings[BindingIndex];

                    if (InputTouchDelegate.InputKeyEvent == InKeyEvent &&
                        InputTouchDelegate.FunctionNameToBind.ToString() == InAction.Method.Name)
                    {
                        Index = BindingIndex;

                        break;
                    }
                }

                if (Index < 0)
                {
                    Bindings.Add(new FBlueprintInputTouchDelegateBinding
                    {
                        InputKeyEvent = InKeyEvent,
                        FunctionNameToBind = InAction.Method.Name
                    });

                    Index = Bindings.Num() - 1;
                }

                UInputComponentImplementation.UInputComponent_BindTouchImplementation(
                    HandleData.GetHandle(this),
                    HandleData.GetHandle(InputTouchDelegateBinding),
                    HandleData.GetHandle(InObject),
                    Index);
            }
        }

        public void BindVectorAxis(FKey InKey, UObject InObject, Action<FVector> InAction)
        {
            var InputVectorAxisDelegateBinding = UInputComponentImplementation
                .UInputComponent_GetDynamicBindingObjectImplementation<UInputVectorAxisDelegateBinding>(
                    HandleData.GetHandle(InObject.GetClass()),
                    HandleData.GetHandle(UInputVectorAxisDelegateBinding.StaticClass()));

            if (InputVectorAxisDelegateBinding != null)
            {
                var Bindings = InputVectorAxisDelegateBinding.InputAxisKeyDelegateBindings;

                var Index = -1;

                for (var BindingIndex = 0; BindingIndex < Bindings.Num(); ++BindingIndex)
                {
                    var InputAxisKeyDelegate = Bindings[BindingIndex];

                    if (InputAxisKeyDelegate.AxisKey == InKey &&
                        InputAxisKeyDelegate.FunctionNameToBind.ToString() == InAction.Method.Name)
                    {
                        Index = BindingIndex;

                        break;
                    }
                }

                if (Index < 0)
                {
                    Bindings.Add(new FBlueprintInputAxisKeyDelegateBinding
                    {
                        AxisKey = InKey,
                        FunctionNameToBind = InAction.Method.Name
                    });

                    Index = Bindings.Num() - 1;
                }

                UInputComponentImplementation.UInputComponent_BindVectorAxisImplementation(
                    HandleData.GetHandle(this),
                    HandleData.GetHandle(InputVectorAxisDelegateBinding),
                    HandleData.GetHandle(InObject),
                    Index);
            }
        }

        public void RemoveAction(FName InActionName, EInputEvent InKeyEvent, UObject InObject, Action<FKey> InAction)
        {
            var InputActionDelegateBinding = UInputComponentImplementation
                .UInputComponent_GetDynamicBindingObjectImplementation<UInputActionDelegateBinding>(
                    HandleData.GetHandle(InObject.GetClass()),
                    HandleData.GetHandle(UInputActionDelegateBinding.StaticClass()));

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

            UInputComponentImplementation.UInputComponent_UnbindActionImplementation(
                HandleData.GetHandle(this),
                HandleData.GetHandle(InObject),
                HandleData.GetHandle(InActionName),
                (int)InKeyEvent);
        }

        public void RemoveAxis(FName InAxisName, UObject InObject, Action<float> InAction)
        {
            var InputAxisDelegateBinding = UInputComponentImplementation
                .UInputComponent_GetDynamicBindingObjectImplementation<UInputAxisDelegateBinding>(
                    HandleData.GetHandle(InObject.GetClass()),
                    HandleData.GetHandle(UInputAxisDelegateBinding.StaticClass()));

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

            using var FunctionName = new FName(InAction.Method.Name);

            UInputComponentImplementation.UInputComponent_UnbindAxisImplementation(
                HandleData.GetHandle(this),
                HandleData.GetHandle(InObject),
                HandleData.GetHandle(FunctionName));
        }

        public void RemoveAxisKey(FKey InKey, UObject InObject, Action<float> InAction)
        {
            var InputAxisKeyDelegateBinding = UInputComponentImplementation
                .UInputComponent_GetDynamicBindingObjectImplementation<UInputAxisKeyDelegateBinding>(
                    HandleData.GetHandle(InObject.GetClass()),
                    HandleData.GetHandle(UInputAxisKeyDelegateBinding.StaticClass()));

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

            using var FunctionName = new FName(InAction.Method.Name);

            UInputComponentImplementation.UInputComponent_UnbindAxisKeyImplementation(
                HandleData.GetHandle(this),
                HandleData.GetHandle(InObject),
                HandleData.GetHandle(FunctionName));
        }

        public void RemoveKey(FInputChord InInputChord, EInputEvent InKeyEvent, UObject InObject, Action<FKey> InAction)
        {
            var InputKeyDelegateBinding = UInputComponentImplementation
                .UInputComponent_GetDynamicBindingObjectImplementation<UInputKeyDelegateBinding>(
                    HandleData.GetHandle(InObject.GetClass()),
                    HandleData.GetHandle(UInputKeyDelegateBinding.StaticClass()));

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

            UInputComponentImplementation.UInputComponent_UnbindKeyImplementation(
                HandleData.GetHandle(this),
                HandleData.GetHandle(InObject),
                HandleData.GetHandle(InInputChord),
                (int)InKeyEvent);
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
                    HandleData.GetHandle(InObject.GetClass()),
                    HandleData.GetHandle(UInputTouchDelegateBinding.StaticClass()));

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

            using var FunctionName = new FName(InAction.Method.Name);

            UInputComponentImplementation.UInputComponent_UnbindTouchImplementation(
                HandleData.GetHandle(this),
                HandleData.GetHandle(InObject),
                HandleData.GetHandle(FunctionName));
        }

        public void RemoveVectorAxis(FKey InKey, UObject InObject, Action<FVector> InAction)
        {
            var InputVectorAxisDelegateBinding = UInputComponentImplementation
                .UInputComponent_GetDynamicBindingObjectImplementation<UInputVectorAxisDelegateBinding>(
                    HandleData.GetHandle(InObject.GetClass()),
                    HandleData.GetHandle(UInputVectorAxisDelegateBinding.StaticClass()));

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

            using var FunctionName = new FName(InAction.Method.Name);

            UInputComponentImplementation.UInputComponent_UnbindVectorAxisImplementation(
                HandleData.GetHandle(this),
                HandleData.GetHandle(InObject),
                HandleData.GetHandle(FunctionName));
        }

        public void ClearBindingValues(UObject InObject)
        {
            UInputComponentImplementation.UInputComponent_ClearBindingValuesImplementation(HandleData.GetHandle(this));
        }
    }
}