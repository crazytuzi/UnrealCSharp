using System;
using System.Runtime.CompilerServices;
using Script.Common;
using Script.CoreUObject;

namespace Script.Library
{
    public static class PolyglotTextDataImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean PolyglotTextData_IsValidImplementation(FPolyglotTextData InPolyglotTextData,
            out FText OutFailureReason);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_SetNativeCultureImplementation(FPolyglotTextData InPolyglotTextData,
            FString InNativeCulture);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_GetNativeCultureImplementation(FPolyglotTextData InPolyglotTextData,
            out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_ResolveNativeCultureImplementation(
            FPolyglotTextData InPolyglotTextData, out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_SetIdentityImplementation(FPolyglotTextData InPolyglotTextData,
            FString InNamespace, FString InKey);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_GetIdentityImplementation(FPolyglotTextData InPolyglotTextData,
            out FString OutNamespace, out FString OutKey);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_GetNamespaceImplementation(FPolyglotTextData InPolyglotTextData,
            out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_GetKeyImplementation(FPolyglotTextData InPolyglotTextData,
            out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_SetNativeStringImplementation(FPolyglotTextData InPolyglotTextData,
            FString InNativeString);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_GetNativeStringImplementation(FPolyglotTextData InPolyglotTextData,
            out FString OutValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_AddLocalizedStringImplementation(
            FPolyglotTextData InPolyglotTextData, FString InCulture, FString InLocalizedString);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_RemoveLocalizedStringImplementation(
            FPolyglotTextData InPolyglotTextData, FString InCulture);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean PolyglotTextData_GetLocalizedStringImplementation(
            FPolyglotTextData InPolyglotTextData, FString InCulture, out FString OutLocalizedString);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_ClearLocalizedStringsImplementation(
            FPolyglotTextData InPolyglotTextData);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_SetIsMinimalPatchImplementation(FPolyglotTextData InPolyglotTextData,
            Boolean InIsMinimalPatch);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern Boolean PolyglotTextData_GetIsMinimalPatchImplementation(
            FPolyglotTextData InPolyglotTextData);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void PolyglotTextData_GetTextImplementation(FPolyglotTextData InPolyglotTextData,
            out FText OutValue);
    }
}