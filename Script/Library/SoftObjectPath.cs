using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FSoftObjectPath
    {
        public FString ToString()
        {
            SoftObjectPathImplementation.SoftObjectPath_ToStringImplementation(this, out var OutValue);

            return OutValue;
        }

        public FName GetAssetPathName()
        {
            SoftObjectPathImplementation.SoftObjectPath_GetAssetPathNameImplementation(this, out var OutValue);

            return OutValue;
        }

        public FString GetAssetPathString()
        {
            SoftObjectPathImplementation.SoftObjectPath_GetAssetPathStringImplementation(this, out var OutValue);

            return OutValue;
        }

        public FString GetSubPathString()
        {
            SoftObjectPathImplementation.SoftObjectPath_GetSubPathStringImplementation(this, out var OutValue);

            return OutValue;
        }

        public FString GetLongPackageName()
        {
            SoftObjectPathImplementation.SoftObjectPath_GetLongPackageNameImplementation(this, out var OutValue);

            return OutValue;
        }

        public FString GetAssetName()
        {
            SoftObjectPathImplementation.SoftObjectPath_GetAssetNameImplementation(this, out var OutValue);

            return OutValue;
        }

        public void SetPath(FName Path) =>
            SoftObjectPathImplementation.SoftObjectPath_SetPathNameImplementation(this, Path);

        public void SetPath(FString Path) =>
            SoftObjectPathImplementation.SoftObjectPath_SetPathStringImplementation(this, Path);

        // @TODO
        // TryLoad
        // ResolveObject

        public void Reset() =>
            SoftObjectPathImplementation.SoftObjectPath_ResetImplementation(this);

        public Boolean IsValid() =>
            SoftObjectPathImplementation.SoftObjectPath_IsValidImplementation(this);

        public Boolean IsNull() =>
            SoftObjectPathImplementation.SoftObjectPath_IsNullImplementation(this);

        public Boolean IsAsset() =>
            SoftObjectPathImplementation.SoftObjectPath_IsAssetImplementation(this);

        public Boolean IsSubobject() =>
            SoftObjectPathImplementation.SoftObjectPath_IsSubobjectImplementation(this);

        public static Boolean operator ==(FSoftObjectPath A, FSoftObjectPath B) =>
            SoftObjectPathImplementation.SoftObjectPath_EqualityImplementation(A, B);

        public static Boolean operator !=(FSoftObjectPath A, FSoftObjectPath B) =>
            SoftObjectPathImplementation.SoftObjectPath_InequalityImplementation(A, B);

        // @TODO
        // ExportTextItem
        // ImportTextItem
        // SerializeFromMismatchedTag
        // PreSavePath

        public Boolean FixupForPIE() =>
            SoftObjectPathImplementation.SoftObjectPath_FixupForPIEImplementation(this);

        public Boolean FixupForPIE(Int32 PIEInstance) =>
            SoftObjectPathImplementation.SoftObjectPath_FixupForPIEInstanceImplementation(this, PIEInstance);

        public Boolean FixupCoreRedirects() =>
            SoftObjectPathImplementation.SoftObjectPath_FixupCoreRedirectsImplementation(this);

        public static Int32 GetCurrentTag() =>
            SoftObjectPathImplementation.SoftObjectPath_GetCurrentTagImplementation();

        public static Int32 InvalidateTag() =>
            SoftObjectPathImplementation.SoftObjectPath_InvalidateTagImplementation();

        public static FSoftObjectPath GetOrCreateIDForObject(UObject Object)
        {
            SoftObjectPathImplementation.SoftObjectPath_GetOrCreateIDForObjectImplementation(Object, out var OutValue);

            return OutValue;
        }

        public static void AddPIEPackageName(FName NewPIEPackageName) =>
            SoftObjectPathImplementation.SoftObjectPath_AddPIEPackageNameImplementation(NewPIEPackageName);

        public static void ClearPIEPackageNames() =>
            SoftObjectPathImplementation.SoftObjectPath_ClearPIEPackageNamesImplementation();
    }
}