using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FPolyglotTextData
    {
        public Boolean IsValid(out FText OutFailureReason) =>
            PolyglotTextDataImplementation.PolyglotTextData_IsValidImplementation(this, out OutFailureReason);

        // @TODO
        // SetCategory
        // GetCategory

        public void SetNativeCulture(FString InNativeCulture) =>
            PolyglotTextDataImplementation.PolyglotTextData_SetNativeCultureImplementation(this, InNativeCulture);

        public FString GetNativeCulture()
        {
            PolyglotTextDataImplementation.PolyglotTextData_GetNativeCultureImplementation(this, out var OutValue);

            return OutValue;
        }

        public FString ResolveNativeCulture()
        {
            PolyglotTextDataImplementation.PolyglotTextData_ResolveNativeCultureImplementation(this, out var OutValue);

            return OutValue;
        }

        // @TODO
        // GetLocalizedCultures

        public void SetIdentity(FString InNamespace, FString InKey) =>
            PolyglotTextDataImplementation.PolyglotTextData_SetIdentityImplementation(this, InNamespace, InKey);

        public void GetIdentity(out FString OutNamespace, out FString OutKey) =>
            PolyglotTextDataImplementation.PolyglotTextData_GetIdentityImplementation(this, out OutNamespace,
                out OutKey);

        public FString GetNamespace()
        {
            PolyglotTextDataImplementation.PolyglotTextData_GetNamespaceImplementation(this, out var OutValue);

            return OutValue;
        }

        public FString GetKey()
        {
            PolyglotTextDataImplementation.PolyglotTextData_GetKeyImplementation(this, out var OutValue);

            return OutValue;
        }

        public void SetNativeString(FString InNativeString) =>
            PolyglotTextDataImplementation.PolyglotTextData_SetNativeStringImplementation(this, InNativeString);

        public FString GetNativeString()
        {
            PolyglotTextDataImplementation.PolyglotTextData_GetNativeStringImplementation(this, out var OutValue);

            return OutValue;
        }

        public void AddLocalizedString(FString InCulture, FString InLocalizedString) =>
            PolyglotTextDataImplementation.PolyglotTextData_AddLocalizedStringImplementation(this, InCulture,
                InLocalizedString);

        public void RemoveLocalizedString(FString InCulture) =>
            PolyglotTextDataImplementation.PolyglotTextData_RemoveLocalizedStringImplementation(this, InCulture);

        public Boolean GetLocalizedString(FString InCulture, out FString OutLocalizedString) =>
            PolyglotTextDataImplementation.PolyglotTextData_GetLocalizedStringImplementation(this, InCulture,
                out OutLocalizedString);

        public void ClearLocalizedStrings() =>
            PolyglotTextDataImplementation.PolyglotTextData_ClearLocalizedStringsImplementation(this);

        public void IsMinimalPatch(Boolean InIsMinimalPatch) =>
            PolyglotTextDataImplementation.PolyglotTextData_SetIsMinimalPatchImplementation(this, InIsMinimalPatch);

        public Boolean IsMinimalPatch() =>
            PolyglotTextDataImplementation.PolyglotTextData_GetIsMinimalPatchImplementation(this);

        public FText GetText()
        {
            PolyglotTextDataImplementation.PolyglotTextData_GetTextImplementation(this, out var OutValue);

            return OutValue;
        }
    }
}