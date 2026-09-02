using Script.CoreUObject;
using Script.Engine;
using Interop;

namespace Script.Library
{
    public static partial class UEnhancedInputComponentImplementation
    {
        private static unsafe partial nint __UEnhancedInputComponent_GetDynamicBindingObjectImplementation(nint InThisClass, nint InBindingClass);

        public static unsafe T UEnhancedInputComponent_GetDynamicBindingObjectImplementation<T>(
            nint InThisClass, nint InBindingClass) where T : UDynamicBlueprintBinding
        {
            var Handle = __UEnhancedInputComponent_GetDynamicBindingObjectImplementation(InThisClass, InBindingClass);

            return Handle != 0 ? (T)HandleData.GetObject(Handle) : null;
        }

        private static unsafe partial nint __UEnhancedInputComponent_BindActionImplementation(nint InObject, nint InBlueprintEnhancedInputActionBinding, nint InObjectToBindTo, nint InFunctionNameToBind);

        public static unsafe FEnhancedInputActionEventBinding UEnhancedInputComponent_BindActionImplementation(
            nint InObject, nint InBlueprintEnhancedInputActionBinding, nint InObjectToBindTo, nint InFunctionNameToBind)
        {
            var Handle = __UEnhancedInputComponent_BindActionImplementation(InObject,
                InBlueprintEnhancedInputActionBinding, InObjectToBindTo, InFunctionNameToBind);

            return Handle != 0 ? (FEnhancedInputActionEventBinding)HandleData.GetObject(Handle) : null;
        }

        private static unsafe partial void __UEnhancedInputComponent_RemoveBindingImplementation(nint InObject, nint InEnhancedInputActionEventBinding);

        public static unsafe void UEnhancedInputComponent_RemoveBindingImplementation(nint InObject,
            nint InEnhancedInputActionEventBinding)
        {
            __UEnhancedInputComponent_RemoveBindingImplementation(InObject, InEnhancedInputActionEventBinding);
        }
    }
}