using Script.Engine;
using Interop;

namespace Script.Library
{
    public static partial class UInputComponentImplementation
    {
        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, nint>
            __UInputComponent_GetDynamicBindingObjectImplementation;

        public static unsafe T UInputComponent_GetDynamicBindingObjectImplementation<T>(
            nint InThisClass, nint InBindingClass) where T : UDynamicBlueprintBinding
        {
            if (__UInputComponent_GetDynamicBindingObjectImplementation == null)
            {
                __UInputComponent_GetDynamicBindingObjectImplementation = (delegate* unmanaged[Cdecl]<nint, nint, nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.UInputComponentImplementation::UInputComponent_GetDynamicBindingObjectImplementation");
            }

            var Handle = __UInputComponent_GetDynamicBindingObjectImplementation(InThisClass, InBindingClass);

            return Handle != 0 ? (T)HandleData.GetObject(Handle) : null;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, nint, nint, void>
            __UInputComponent_BindActionImplementation;

        public static unsafe void UInputComponent_BindActionImplementation(nint InObject,
            nint InInputActionDelegateBinding, nint InObjectToBindTo, nint InFunctionNameToBind)
        {
            if (__UInputComponent_BindActionImplementation == null)
            {
                __UInputComponent_BindActionImplementation = (delegate* unmanaged[Cdecl]<nint, nint, nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.UInputComponentImplementation::UInputComponent_BindActionImplementation");
            }

            __UInputComponent_BindActionImplementation(InObject, InInputActionDelegateBinding, InObjectToBindTo,
                InFunctionNameToBind);
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, nint, nint, void>
            __UInputComponent_BindAxisImplementation;

        public static unsafe void UInputComponent_BindAxisImplementation(nint InObject, nint InInputAxisDelegateBinding,
            nint InObjectToBindTo, nint InFunctionNameToBind)
        {
            if (__UInputComponent_BindAxisImplementation == null)
            {
                __UInputComponent_BindAxisImplementation = (delegate* unmanaged[Cdecl]<nint, nint, nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.UInputComponentImplementation::UInputComponent_BindAxisImplementation");
            }

            __UInputComponent_BindAxisImplementation(InObject, InInputAxisDelegateBinding, InObjectToBindTo,
                InFunctionNameToBind);
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, nint, nint, void>
            __UInputComponent_BindAxisKeyImplementation;

        public static unsafe void UInputComponent_BindAxisKeyImplementation(nint InObject,
            nint InInputAxisKeyDelegateBinding, nint InObjectToBindTo, nint InFunctionNameToBind)
        {
            if (__UInputComponent_BindAxisKeyImplementation == null)
            {
                __UInputComponent_BindAxisKeyImplementation = (delegate* unmanaged[Cdecl]<nint, nint, nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.UInputComponentImplementation::UInputComponent_BindAxisKeyImplementation");
            }

            __UInputComponent_BindAxisKeyImplementation(InObject, InInputAxisKeyDelegateBinding, InObjectToBindTo,
                InFunctionNameToBind);
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, nint, nint, void>
            __UInputComponent_BindKeyImplementation;

        public static unsafe void UInputComponent_BindKeyImplementation(nint InObject, nint InInputKeyDelegateBinding,
            nint InObjectToBindTo, nint InFunctionNameToBind)
        {
            if (__UInputComponent_BindKeyImplementation == null)
            {
                __UInputComponent_BindKeyImplementation = (delegate* unmanaged[Cdecl]<nint, nint, nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.UInputComponentImplementation::UInputComponent_BindKeyImplementation");
            }

            __UInputComponent_BindKeyImplementation(InObject, InInputKeyDelegateBinding, InObjectToBindTo,
                InFunctionNameToBind);
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, nint, nint, void>
            __UInputComponent_BindTouchImplementation;

        public static unsafe void UInputComponent_BindTouchImplementation(nint InObject,
            nint InInputTouchDelegateBinding, nint InObjectToBindTo, nint InFunctionNameToBind)
        {
            if (__UInputComponent_BindTouchImplementation == null)
            {
                __UInputComponent_BindTouchImplementation = (delegate* unmanaged[Cdecl]<nint, nint, nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.UInputComponentImplementation::UInputComponent_BindTouchImplementation");
            }

            __UInputComponent_BindTouchImplementation(InObject, InInputTouchDelegateBinding, InObjectToBindTo,
                InFunctionNameToBind);
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, nint, nint, void>
            __UInputComponent_BindVectorAxisImplementation;

        public static unsafe void UInputComponent_BindVectorAxisImplementation(nint InObject,
            nint InInputVectorAxisDelegateBinding, nint InObjectToBindTo, nint InFunctionNameToBind)
        {
            if (__UInputComponent_BindVectorAxisImplementation == null)
            {
                __UInputComponent_BindVectorAxisImplementation =
                    (delegate* unmanaged[Cdecl]<nint, nint, nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.UInputComponentImplementation::UInputComponent_BindVectorAxisImplementation");
            }

            __UInputComponent_BindVectorAxisImplementation(InObject, InInputVectorAxisDelegateBinding, InObjectToBindTo,
                InFunctionNameToBind);
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, void> __UInputComponent_ClearBindingValuesImplementation;

        public static unsafe void UInputComponent_ClearBindingValuesImplementation(nint InObject)
        {
            if (__UInputComponent_ClearBindingValuesImplementation == null)
            {
                __UInputComponent_ClearBindingValuesImplementation = (delegate* unmanaged[Cdecl]<nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.UInputComponentImplementation::UInputComponent_ClearBindingValuesImplementation");
            }

            __UInputComponent_ClearBindingValuesImplementation(InObject);
        }
    }
}