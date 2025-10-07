using System.Runtime.CompilerServices;
using Script.CoreUObject;
using Script.Engine;

namespace Script.Library
{
    public static partial class UEnhancedInputComponentImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern T UEnhancedInputComponent_GetDynamicBindingObjectImplementation<T>(
            nint InThisClass,
            nint InBindingClass)
            where T : UDynamicBlueprintBinding;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern FEnhancedInputActionEventBinding UEnhancedInputComponent_BindActionImplementation(
            nint InObject,
            nint InBlueprintEnhancedInputActionBinding,
            nint InObjectToBindTo,
            nint InFunctionNameToBind);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void UEnhancedInputComponent_RemoveBindingImplementation(
            nint InObject,
            nint InEnhancedInputActionEventBinding);
    }
}