using Script.CoreUObject;
using Script.Engine;
using Interop;

namespace Script.Library
{
    public static partial class UEnhancedInputComponentImplementation
    {
        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, nint>
            __UEnhancedInputComponent_GetDynamicBindingObjectImplementation;

        public static unsafe T UEnhancedInputComponent_GetDynamicBindingObjectImplementation<T>(
            nint InThisClass, nint InBindingClass) where T : UDynamicBlueprintBinding
        {
            if (__UEnhancedInputComponent_GetDynamicBindingObjectImplementation == null)
            {
                __UEnhancedInputComponent_GetDynamicBindingObjectImplementation =
                    (delegate* unmanaged[Cdecl]<nint, nint, nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.UEnhancedInputComponentImplementation::UEnhancedInputComponent_GetDynamicBindingObjectImplementation");
            }

            var Handle = __UEnhancedInputComponent_GetDynamicBindingObjectImplementation(InThisClass, InBindingClass);

            return Handle != 0 ? (T)HandleData.GetObject(Handle) : null;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, nint, nint, nint>
            __UEnhancedInputComponent_BindActionImplementation;

        public static unsafe FEnhancedInputActionEventBinding UEnhancedInputComponent_BindActionImplementation(
            nint InObject, nint InBlueprintEnhancedInputActionBinding, nint InObjectToBindTo, nint InFunctionNameToBind)
        {
            if (__UEnhancedInputComponent_BindActionImplementation == null)
            {
                __UEnhancedInputComponent_BindActionImplementation =
                    (delegate* unmanaged[Cdecl]<nint, nint, nint, nint, nint>)
                    MethodBridge.GetMethod(
                        "Script.Library.UEnhancedInputComponentImplementation::UEnhancedInputComponent_BindActionImplementation");
            }

            var Handle = __UEnhancedInputComponent_BindActionImplementation(InObject,
                InBlueprintEnhancedInputActionBinding, InObjectToBindTo, InFunctionNameToBind);

            return Handle != 0 ? (FEnhancedInputActionEventBinding)HandleData.GetObject(Handle) : null;
        }

        private static unsafe delegate* unmanaged[Cdecl]<nint, nint, void>
            __UEnhancedInputComponent_RemoveBindingImplementation;

        public static unsafe void UEnhancedInputComponent_RemoveBindingImplementation(nint InObject,
            nint InEnhancedInputActionEventBinding)
        {
            if (__UEnhancedInputComponent_RemoveBindingImplementation == null)
            {
                __UEnhancedInputComponent_RemoveBindingImplementation = (delegate* unmanaged[Cdecl]<nint, nint, void>)
                    MethodBridge.GetMethod(
                        "Script.Library.UEnhancedInputComponentImplementation::UEnhancedInputComponent_RemoveBindingImplementation");
            }

            __UEnhancedInputComponent_RemoveBindingImplementation(InObject, InEnhancedInputActionEventBinding);
        }
    }
}