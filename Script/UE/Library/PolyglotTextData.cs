using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FPolyglotTextData
    {
        public Boolean IsValid(out FText OutFailureReason) =>
            PolyglotTextDataImplementation.PolyglotTextData_IsValidImplementation(GetHandle(), out OutFailureReason);

        // @TODO
        // SetCategory
        // GetCategory

        public void SetNativeCulture(FString InNativeCulture) =>
            PolyglotTextDataImplementation.PolyglotTextData_SetNativeCultureImplementation(GetHandle(),
                InNativeCulture);

        public FString GetNativeCulture()
        {
            PolyglotTextDataImplementation.PolyglotTextData_GetNativeCultureImplementation(GetHandle(),
                out var OutValue);

            return OutValue;
        }

        public FString ResolveNativeCulture()
        {
            PolyglotTextDataImplementation.PolyglotTextData_ResolveNativeCultureImplementation(GetHandle(),
                out var OutValue);

            return OutValue;
        }

        // @TODO
        // GetLocalizedCultures

        public void SetIdentity(FString InNamespace, FString InKey) =>
            PolyglotTextDataImplementation.PolyglotTextData_SetIdentityImplementation(GetHandle(), InNamespace, InKey);

        public void GetIdentity(out FString OutNamespace, out FString OutKey) =>
            PolyglotTextDataImplementation.PolyglotTextData_GetIdentityImplementation(GetHandle(), out OutNamespace,
                out OutKey);

        public FString GetNamespace()
        {
            PolyglotTextDataImplementation.PolyglotTextData_GetNamespaceImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FString GetKey()
        {
            PolyglotTextDataImplementation.PolyglotTextData_GetKeyImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public void SetNativeString(FString InNativeString) =>
            PolyglotTextDataImplementation.PolyglotTextData_SetNativeStringImplementation(GetHandle(), InNativeString);

        public FString GetNativeString()
        {
            PolyglotTextDataImplementation.PolyglotTextData_GetNativeStringImplementation(GetHandle(),
                out var OutValue);

            return OutValue;
        }

        public void AddLocalizedString(FString InCulture, FString InLocalizedString) =>
            PolyglotTextDataImplementation.PolyglotTextData_AddLocalizedStringImplementation(GetHandle(), InCulture,
                InLocalizedString);

        public void RemoveLocalizedString(FString InCulture) =>
            PolyglotTextDataImplementation.PolyglotTextData_RemoveLocalizedStringImplementation(GetHandle(), InCulture);

        public Boolean GetLocalizedString(FString InCulture, out FString OutLocalizedString) =>
            PolyglotTextDataImplementation.PolyglotTextData_GetLocalizedStringImplementation(GetHandle(), InCulture,
                out OutLocalizedString);

        public void ClearLocalizedStrings() =>
            PolyglotTextDataImplementation.PolyglotTextData_ClearLocalizedStringsImplementation(GetHandle());

        public void IsMinimalPatch(Boolean InIsMinimalPatch) =>
            PolyglotTextDataImplementation.PolyglotTextData_SetIsMinimalPatchImplementation(GetHandle(),
                InIsMinimalPatch);

        public Boolean IsMinimalPatch() =>
            PolyglotTextDataImplementation.PolyglotTextData_GetIsMinimalPatchImplementation(GetHandle());

        public FText GetText()
        {
            PolyglotTextDataImplementation.PolyglotTextData_GetTextImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }
    }
}