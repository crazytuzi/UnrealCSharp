using System.Runtime.CompilerServices;
using Script.Engine;

namespace Script.Library
{
    public static partial class UInputComponentImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern T UInputComponent_GetDynamicBindingObjectImplementation<T>(
            nint InThisClass,
            nint InBindingClass)
            where T : UDynamicBlueprintBinding;

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void UInputComponent_BindActionImplementation(
            nint InObject,
            nint InInputActionDelegateBinding,
            nint InObjectToBindTo,
            nint InFunctionNameToBind);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void UInputComponent_BindAxisImplementation(
            nint InObject,
            nint InInputAxisDelegateBinding,
            nint InObjectToBindTo,
            nint InFunctionNameToBind);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void UInputComponent_BindAxisKeyImplementation(
            nint InObject,
            nint InInputAxisKeyDelegateBinding,
            nint InObjectToBindTo,
            nint InFunctionNameToBind);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void UInputComponent_BindKeyImplementation(
            nint InObject,
            nint InInputKeyDelegateBinding,
            nint InObjectToBindTo,
            nint InFunctionNameToBind);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void UInputComponent_BindTouchImplementation(
            nint InObject,
            nint InInputTouchDelegateBinding,
            nint InObjectToBindTo,
            nint InFunctionNameToBind);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void UInputComponent_BindVectorAxisImplementation(
            nint InObject,
            nint InInputVectorAxisDelegateBinding,
            nint InObjectToBindTo,
            nint InFunctionNameToBind);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void UInputComponent_ClearBindingValuesImplementation(nint InObject);
    }
}