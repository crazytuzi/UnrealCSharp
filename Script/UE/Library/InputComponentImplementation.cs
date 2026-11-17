using Script.Engine;
using Interop;

namespace Script.Library
{
    public static partial class UInputComponentImplementation
    {
        private static unsafe partial nint __UInputComponent_GetDynamicBindingObjectImplementation(nint InThisClass, nint InBindingClass);

        public static unsafe T UInputComponent_GetDynamicBindingObjectImplementation<T>(
            nint InThisClass, nint InBindingClass) where T : UDynamicBlueprintBinding
        {
            var Handle = __UInputComponent_GetDynamicBindingObjectImplementation(InThisClass, InBindingClass);

            return Handle != 0 ? (T)HandleData.GetObject(Handle) : null;
        }

        private static unsafe partial void __UInputComponent_BindActionImplementation(nint InObject, nint InBlueprintInputActionDelegateBinding, nint InObjectToBindTo);

        public static unsafe void UInputComponent_BindActionImplementation(nint InObject,
            nint InBlueprintInputActionDelegateBinding, nint InObjectToBindTo)
        {
            __UInputComponent_BindActionImplementation(InObject, InBlueprintInputActionDelegateBinding,
                InObjectToBindTo);
        }

        private static unsafe partial void __UInputComponent_BindAxisImplementation(nint InObject, nint InBlueprintInputAxisDelegateBinding, nint InObjectToBindTo);

        public static unsafe void UInputComponent_BindAxisImplementation(nint InObject,
            nint InBlueprintInputAxisDelegateBinding, nint InObjectToBindTo)
        {
            __UInputComponent_BindAxisImplementation(InObject, InBlueprintInputAxisDelegateBinding,
                InObjectToBindTo);
        }

        private static unsafe partial void __UInputComponent_BindAxisKeyImplementation(nint InObject, nint InBlueprintInputAxisKeyDelegateBinding, nint InObjectToBindTo);

        public static unsafe void UInputComponent_BindAxisKeyImplementation(nint InObject,
            nint InBlueprintInputAxisKeyDelegateBinding, nint InObjectToBindTo)
        {
            __UInputComponent_BindAxisKeyImplementation(InObject, InBlueprintInputAxisKeyDelegateBinding,
                InObjectToBindTo);
        }

        private static unsafe partial void __UInputComponent_BindKeyImplementation(nint InObject, nint InBlueprintInputKeyDelegateBinding, nint InObjectToBindTo);

        public static unsafe void UInputComponent_BindKeyImplementation(nint InObject,
            nint InBlueprintInputKeyDelegateBinding, nint InObjectToBindTo)
        {
            __UInputComponent_BindKeyImplementation(InObject, InBlueprintInputKeyDelegateBinding, InObjectToBindTo);
        }

        private static unsafe partial void __UInputComponent_BindTouchImplementation(nint InObject, nint InBlueprintInputTouchDelegateBinding, nint InObjectToBindTo);

        public static unsafe void UInputComponent_BindTouchImplementation(nint InObject,
            nint InBlueprintInputTouchDelegateBinding, nint InObjectToBindTo)
        {
            __UInputComponent_BindTouchImplementation(InObject, InBlueprintInputTouchDelegateBinding,
                InObjectToBindTo);
        }

        private static unsafe partial void __UInputComponent_BindVectorAxisImplementation(nint InObject, nint InBlueprintInputAxisKeyDelegateBinding, nint InObjectToBindTo);

        public static unsafe void UInputComponent_BindVectorAxisImplementation(nint InObject,
            nint InBlueprintInputAxisKeyDelegateBinding, nint InObjectToBindTo)
        {
            __UInputComponent_BindVectorAxisImplementation(InObject, InBlueprintInputAxisKeyDelegateBinding,
                InObjectToBindTo);
        }

        private static unsafe partial void __UInputComponent_UnbindActionImplementation(nint InObject, nint InObjectToBindTo, nint InActionName, int InKeyEvent);

        public static unsafe void UInputComponent_UnbindActionImplementation(nint InObject, nint InObjectToBindTo,
            nint InActionName, int InKeyEvent)
        {
            __UInputComponent_UnbindActionImplementation(InObject, InObjectToBindTo, InActionName, InKeyEvent);
        }

        private static unsafe partial void __UInputComponent_UnbindAxisImplementation(nint InObject, nint InObjectToBindTo, nint InFunctionNameToBind);

        public static unsafe void UInputComponent_UnbindAxisImplementation(nint InObject, nint InObjectToBindTo,
            nint InFunctionNameToBind)
        {
            __UInputComponent_UnbindAxisImplementation(InObject, InObjectToBindTo, InFunctionNameToBind);
        }

        private static unsafe partial void __UInputComponent_UnbindAxisKeyImplementation(nint InObject, nint InObjectToBindTo, nint InFunctionNameToBind);

        public static unsafe void UInputComponent_UnbindAxisKeyImplementation(nint InObject, nint InObjectToBindTo,
            nint InFunctionNameToBind)
        {
            __UInputComponent_UnbindAxisKeyImplementation(InObject, InObjectToBindTo, InFunctionNameToBind);
        }

        private static unsafe partial void __UInputComponent_UnbindKeyImplementation(nint InObject, nint InObjectToBindTo, nint InInputChord, int InKeyEvent);

        public static unsafe void UInputComponent_UnbindKeyImplementation(nint InObject, nint InObjectToBindTo,
            nint InInputChord, int InKeyEvent)
        {
            __UInputComponent_UnbindKeyImplementation(InObject, InObjectToBindTo, InInputChord, InKeyEvent);
        }

        private static unsafe partial void __UInputComponent_UnbindTouchImplementation(nint InObject, nint InObjectToBindTo, nint InFunctionNameToBind);

        public static unsafe void UInputComponent_UnbindTouchImplementation(nint InObject, nint InObjectToBindTo,
            nint InFunctionNameToBind)
        {
            __UInputComponent_UnbindTouchImplementation(InObject, InObjectToBindTo, InFunctionNameToBind);
        }

        private static unsafe partial void __UInputComponent_UnbindVectorAxisImplementation(nint InObject, nint InObjectToBindTo, nint InFunctionNameToBind);

        public static unsafe void UInputComponent_UnbindVectorAxisImplementation(nint InObject, nint InObjectToBindTo,
            nint InFunctionNameToBind)
        {
            __UInputComponent_UnbindVectorAxisImplementation(InObject, InObjectToBindTo, InFunctionNameToBind);
        }

        private static unsafe partial int __UInputComponent_GetNumActionBindingsImplementation(nint InObject);

        public static unsafe int UInputComponent_GetNumActionBindingsImplementation(nint InObject)
        {
            return __UInputComponent_GetNumActionBindingsImplementation(InObject);
        }

        private static unsafe partial void __UInputComponent_ClearBindingValuesImplementation(nint InObject);

        public static unsafe void UInputComponent_ClearBindingValuesImplementation(nint InObject)
        {
            __UInputComponent_ClearBindingValuesImplementation(InObject);
        }
    }
}