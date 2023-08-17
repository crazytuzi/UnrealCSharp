using System;
using System.Runtime.CompilerServices;
using Script.Common;

namespace Script.Library
{
    public static class PolyglotTextDataImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean PolyglotTextData_IsValidImplementation(IntPtr InPolyglotTextData,
            out FText OutFailureReason);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_SetNativeCultureImplementation(IntPtr InPolyglotTextData,
            FString InNativeCulture);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_GetNativeCultureImplementation(IntPtr InPolyglotTextData,
            out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_ResolveNativeCultureImplementation(
            IntPtr InPolyglotTextData, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_SetIdentityImplementation(IntPtr InPolyglotTextData,
            FString InNamespace, FString InKey);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_GetIdentityImplementation(IntPtr InPolyglotTextData,
            out FString OutNamespace, out FString OutKey);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_GetNamespaceImplementation(IntPtr InPolyglotTextData,
            out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_GetKeyImplementation(IntPtr InPolyglotTextData,
            out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_SetNativeStringImplementation(IntPtr InPolyglotTextData,
            FString InNativeString);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_GetNativeStringImplementation(IntPtr InPolyglotTextData,
            out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_AddLocalizedStringImplementation(
            IntPtr InPolyglotTextData, FString InCulture, FString InLocalizedString);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_RemoveLocalizedStringImplementation(
            IntPtr InPolyglotTextData, FString InCulture);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean PolyglotTextData_GetLocalizedStringImplementation(
            IntPtr InPolyglotTextData, FString InCulture, out FString OutLocalizedString);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_ClearLocalizedStringsImplementation(
            IntPtr InPolyglotTextData);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_SetIsMinimalPatchImplementation(IntPtr InPolyglotTextData,
            Boolean InIsMinimalPatch);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean PolyglotTextData_GetIsMinimalPatchImplementation(
            IntPtr InPolyglotTextData);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_GetTextImplementation(IntPtr InPolyglotTextData,
            out FText OutValue);
    }
}