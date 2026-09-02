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

        private static unsafe partial void __UInputComponent_BindActionImplementation(nint InObject, nint InInputActionDelegateBinding, nint InObjectToBindTo, nint InFunctionNameToBind);

        public static unsafe void UInputComponent_BindActionImplementation(nint InObject,
            nint InInputActionDelegateBinding, nint InObjectToBindTo, nint InFunctionNameToBind)
        {
            __UInputComponent_BindActionImplementation(InObject, InInputActionDelegateBinding, InObjectToBindTo,
                InFunctionNameToBind);
        }

        private static unsafe partial void __UInputComponent_BindAxisImplementation(nint InObject, nint InInputAxisDelegateBinding, nint InObjectToBindTo, nint InFunctionNameToBind);

        public static unsafe void UInputComponent_BindAxisImplementation(nint InObject, nint InInputAxisDelegateBinding,
            nint InObjectToBindTo, nint InFunctionNameToBind)
        {
            __UInputComponent_BindAxisImplementation(InObject, InInputAxisDelegateBinding, InObjectToBindTo,
                InFunctionNameToBind);
        }

        private static unsafe partial void __UInputComponent_BindAxisKeyImplementation(nint InObject, nint InInputAxisKeyDelegateBinding, nint InObjectToBindTo, nint InFunctionNameToBind);

        public static unsafe void UInputComponent_BindAxisKeyImplementation(nint InObject,
            nint InInputAxisKeyDelegateBinding, nint InObjectToBindTo, nint InFunctionNameToBind)
        {
            __UInputComponent_BindAxisKeyImplementation(InObject, InInputAxisKeyDelegateBinding, InObjectToBindTo,
                InFunctionNameToBind);
        }

        private static unsafe partial void __UInputComponent_BindKeyImplementation(nint InObject, nint InInputKeyDelegateBinding, nint InObjectToBindTo, nint InFunctionNameToBind);

        public static unsafe void UInputComponent_BindKeyImplementation(nint InObject, nint InInputKeyDelegateBinding,
            nint InObjectToBindTo, nint InFunctionNameToBind)
        {
            __UInputComponent_BindKeyImplementation(InObject, InInputKeyDelegateBinding, InObjectToBindTo,
                InFunctionNameToBind);
        }

        private static unsafe partial void __UInputComponent_BindTouchImplementation(nint InObject, nint InInputTouchDelegateBinding, nint InObjectToBindTo, nint InFunctionNameToBind);

        public static unsafe void UInputComponent_BindTouchImplementation(nint InObject,
            nint InInputTouchDelegateBinding, nint InObjectToBindTo, nint InFunctionNameToBind)
        {
            __UInputComponent_BindTouchImplementation(InObject, InInputTouchDelegateBinding, InObjectToBindTo,
                InFunctionNameToBind);
        }

        private static unsafe partial void __UInputComponent_BindVectorAxisImplementation(nint InObject, nint InInputVectorAxisDelegateBinding, nint InObjectToBindTo, nint InFunctionNameToBind);

        public static unsafe void UInputComponent_BindVectorAxisImplementation(nint InObject,
            nint InInputVectorAxisDelegateBinding, nint InObjectToBindTo, nint InFunctionNameToBind)
        {
            __UInputComponent_BindVectorAxisImplementation(InObject, InInputVectorAxisDelegateBinding, InObjectToBindTo,
                InFunctionNameToBind);
        }

        private static unsafe partial void __UInputComponent_ClearBindingValuesImplementation(nint InObject);

        public static unsafe void UInputComponent_ClearBindingValuesImplementation(nint InObject)
        {
            __UInputComponent_ClearBindingValuesImplementation(InObject);
        }
    }
}