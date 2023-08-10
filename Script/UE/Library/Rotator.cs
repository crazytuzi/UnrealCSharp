using System;
using Script.Library;
using Script.Common;
#if UE_5_0_OR_LATER
using LwcType = System.Double;
#else
using LwcType = System.Single;
#endif

namespace Script.CoreUObject
{
    public partial class FRotator
    {
        public static FRotator operator +(FRotator A, FRotator B)
        {
            RotatorImplementation.Rotator_AddImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FRotator operator -(FRotator A, FRotator B)
        {
            RotatorImplementation.Rotator_SubtractImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FRotator operator *(FRotator A, LwcType Scale)
        {
            RotatorImplementation.Rotator_MultiplyImplementation(A.GetHandle(), Scale, out var OutValue);

            return OutValue;
        }

        public static Boolean operator ==(FRotator A, FRotator B) =>
            RotatorImplementation.Rotator_EqualityImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator !=(FRotator A, FRotator B) =>
            RotatorImplementation.Rotator_InequalityImplementation(A.GetHandle(), B.GetHandle());

        // @TODO KINDA_SMALL_NUMBER
        public Boolean IsNearlyZero(LwcType Tolerance) =>
            RotatorImplementation.Rotator_IsNearlyZeroImplementation(GetHandle(), Tolerance);

        public Boolean IsZero() =>
            RotatorImplementation.Rotator_IsZeroImplementation(GetHandle());

        // @TODO KINDA_SMALL_NUMBER
        public Boolean Equals(FRotator R, LwcType Tolerance) =>
            RotatorImplementation.Rotator_EqualsImplementation(GetHandle(), R.GetHandle(), Tolerance);

        public FRotator Add(LwcType DeltaPitch, LwcType DeltaYaw, LwcType DeltaRoll)
        {
            RotatorImplementation.Rotator_AddDeltaImplementation(GetHandle(), DeltaPitch, DeltaYaw, DeltaRoll,
                out var OutValue);

            return OutValue;
        }

        public FRotator GetInverse()
        {
            RotatorImplementation.Rotator_GetInverseImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FRotator GridSnap(FRotator RotGrid)
        {
            RotatorImplementation.Rotator_GridSnapImplementation(GetHandle(), RotGrid, out var OutValue);

            return OutValue;
        }

        public FVector Vector()
        {
            RotatorImplementation.Rotator_VectorImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FQuat Quaternion()
        {
            RotatorImplementation.Rotator_QuaternionImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FVector Euler()
        {
            RotatorImplementation.Rotator_EulerImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FVector RotateVector(FVector V)
        {
            RotatorImplementation.Rotator_RotateVectorImplementation(GetHandle(), V, out var OutValue);

            return OutValue;
        }

        public FVector UnrotateVector(FVector V)
        {
            RotatorImplementation.Rotator_UnrotateVectorImplementation(GetHandle(), V, out var OutValue);

            return OutValue;
        }

        public FRotator Clamp()
        {
            RotatorImplementation.Rotator_ClampImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FRotator GetNormalized()
        {
            RotatorImplementation.Rotator_GetNormalizedImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FRotator GetDenormalized()
        {
            RotatorImplementation.Rotator_GetDenormalizedImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        // @TODO
        // GetComponentForAxis
        // SetComponentForAxis

        public void Normalize() =>
            RotatorImplementation.Rotator_NormalizeImplementation(GetHandle());

        public void GetWindingAndRemainder(out FRotator Winding, out FRotator Remainder) =>
            RotatorImplementation.Rotator_GetWindingAndRemainderImplementation(GetHandle(), out Winding, out Remainder);

        public LwcType GetManhattanDistance(FRotator Rotator) =>
            RotatorImplementation.Rotator_GetManhattanDistanceImplementation(GetHandle(), Rotator);

        public FRotator GetEquivalentRotator()
        {
            RotatorImplementation.Rotator_GetEquivalentRotatorImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FRotator SetClosestToMe()
        {
            RotatorImplementation.Rotator_SetClosestToMeImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public override string ToString()
        {
            RotatorImplementation.Rotator_ToStringImplementation(GetHandle(), out var OutValue);

            return OutValue.ToString();
        }

        public FString ToCompactString()
        {
            RotatorImplementation.Rotator_ToCompactStringImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public Boolean InitFromString(FString InSourceString) =>
            RotatorImplementation.Rotator_InitFromStringImplementation(GetHandle(), InSourceString);

        public Boolean ContainsNaN() =>
            RotatorImplementation.Rotator_ContainsNaNImplementation(GetHandle());

        public static LwcType ClampAxis(LwcType Angle) =>
            RotatorImplementation.Rotator_ClampAxisImplementation(Angle);

        public static LwcType NormalizeAxis(LwcType Angle) =>
            RotatorImplementation.Rotator_NormalizeAxisImplementation(Angle);

        public static Byte CompressAxisToByte(LwcType Angle) =>
            RotatorImplementation.Rotator_CompressAxisToByteImplementation(Angle);

        public static LwcType DecompressAxisFromByte(Byte Angle) =>
            RotatorImplementation.Rotator_DecompressAxisFromByteImplementation(Angle);

        public static UInt16 CompressAxisToByte(Byte Angle) =>
            RotatorImplementation.Rotator_CompressAxisToShortImplementation(Angle);

        public static LwcType DecompressAxisFromShort(UInt16 Angle) =>
            RotatorImplementation.Rotator_DecompressAxisFromShortImplementation(Angle);

        public static FRotator MakeFromEuler(FVector Euler)
        {
            RotatorImplementation.Rotator_MakeFromEulerImplementation(Euler, out var OutValue);

            return OutValue;
        }
    }
}