using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FGuid
    {
        public static Boolean operator ==(FGuid A, FGuid B) =>
            GuidImplementation.Guid_EqualityImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator !=(FGuid A, FGuid B) =>
            GuidImplementation.Guid_InequalityImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator <(FGuid A, FGuid B) =>
            GuidImplementation.Guid_LessThanImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator >(FGuid A, FGuid B) =>
            GuidImplementation.Guid_GreaterThanImplementation(A.GetHandle(), B.GetHandle());

        public UInt32 this[Int32 Index]
        {
            get => GuidImplementation.Guid_GetComponentImplementation(GetHandle(), Index);

            set => GuidImplementation.Guid_SetComponentImplementation(GetHandle(), Index, value);
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
            GuidImplementation.Guid_InvalidateImplementation(GetHandle());

        public Boolean IsValid() =>
            GuidImplementation.Guid_IsValidImplementation(GetHandle());

        public override string ToString()
        {
            GuidImplementation.Guid_ToStringImplementation(GetHandle(), out var OutValue);

            return OutValue.ToString();
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