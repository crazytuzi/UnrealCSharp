using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FGuid
    {
        public static Boolean operator ==(FGuid A, FGuid B) =>
            GuidImplementation.Guid_EqualityImplementation(A, B);

        public static Boolean operator !=(FGuid A, FGuid B) =>
            GuidImplementation.Guid_InequalityImplementation(A, B);

        public static Boolean operator <(FGuid A, FGuid B) =>
            GuidImplementation.Guid_LessThanImplementation(A, B);

        public static Boolean operator >(FGuid A, FGuid B) =>
            GuidImplementation.Guid_GreaterThanImplementation(A, B);

        public UInt32 this[Int32 Index]
        {
            get => GuidImplementation.Guid_GetComponentImplementation(this, Index);

            set => GuidImplementation.Guid_SetComponentImplementation(this, Index, value);
        }

        public static FString LexToString(FGuid Value)
        {
            GuidImplementation.Guid_LexToStringImplementation(Value, out var OutValue);

            return OutValue;
        }

        // @TODO
        // LexFromString
        // ExportTextItem
        // ImportTextItem

        public void Invalidate() =>
            GuidImplementation.Guid_InvalidateImplementation(this);

        public Boolean IsValid() =>
            GuidImplementation.Guid_IsValidImplementation(this);

        public FString ToString()
        {
            GuidImplementation.Guid_ToStringImplementation(this, out var OutValue);

            return OutValue;
        }

        // @TODO
        // ToString

        public static FGuid NewGuid()
        {
            GuidImplementation.Guid_NewGuidImplementation(out var OutValue);

            return OutValue;
        }

        public static Boolean Parse(FString GuidString, out FGuid OutGuid) =>
            GuidImplementation.Guid_ParseImplementation(GuidString, out OutGuid);

        // @TODO
        // ParseExact
    }
}