using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FSoftObjectPath
    {
        public override string ToString()
        {
            SoftObjectPathImplementation.SoftObjectPath_ToStringImplementation(GetHandle(), out var OutValue);

            return OutValue.ToString();
        }

        public FName GetAssetPathName()
        {
            SoftObjectPathImplementation.SoftObjectPath_GetAssetPathNameImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FString GetAssetPathString()
        {
            SoftObjectPathImplementation.SoftObjectPath_GetAssetPathStringImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FString GetSubPathString()
        {
            SoftObjectPathImplementation.SoftObjectPath_GetSubPathStringImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FString GetLongPackageName()
        {
            SoftObjectPathImplementation.SoftObjectPath_GetLongPackageNameImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FString GetAssetName()
        {
            SoftObjectPathImplementation.SoftObjectPath_GetAssetNameImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public void SetPath(FName Path) =>
            SoftObjectPathImplementation.SoftObjectPath_SetPathNameImplementation(GetHandle(), Path);

        public void SetPath(FString Path) =>
            SoftObjectPathImplementation.SoftObjectPath_SetPathStringImplementation(GetHandle(), Path);

        // @TODO
        // TryLoad
        // ResolveObject

        public void Reset() =>
            SoftObjectPathImplementation.SoftObjectPath_ResetImplementation(GetHandle());

        public Boolean IsValid() =>
            SoftObjectPathImplementation.SoftObjectPath_IsValidImplementation(GetHandle());

        public Boolean IsNull() =>
            SoftObjectPathImplementation.SoftObjectPath_IsNullImplementation(GetHandle());

        public Boolean IsAsset() =>
            SoftObjectPathImplementation.SoftObjectPath_IsAssetImplementation(GetHandle());

        public Boolean IsSubobject() =>
            SoftObjectPathImplementation.SoftObjectPath_IsSubobjectImplementation(GetHandle());

        // @TODO
        // ExportTextItem
        // ImportTextItem
        // SerializeFromMismatchedTag
        // PreSavePath

        public Boolean FixupForPIE() =>
            SoftObjectPathImplementation.SoftObjectPath_FixupForPIEImplementation(GetHandle());

        public Boolean FixupForPIE(Int32 PIEInstance) =>
            SoftObjectPathImplementation.SoftObjectPath_FixupForPIEInstanceImplementation(GetHandle(), PIEInstance);

        public Boolean FixupCoreRedirects() =>
            SoftObjectPathImplementation.SoftObjectPath_FixupCoreRedirectsImplementation(GetHandle());

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