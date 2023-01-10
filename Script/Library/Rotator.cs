using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FRotator
    {
        public static FRotator operator +(FRotator A, FRotator B)
        {
            RotatorImplementation.Rotator_AddImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FRotator operator -(FRotator A, FRotator B)
        {
            RotatorImplementation.Rotator_SubtractImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FRotator operator *(FRotator A, Single Scale)
        {
            RotatorImplementation.Rotator_MultiplyImplementation(A, Scale, out var OutValue);

            return OutValue;
        }

        public static Boolean operator ==(FRotator A, FRotator B) =>
            RotatorImplementation.Rotator_EqualityImplementation(A, B);

        public static Boolean operator !=(FRotator A, FRotator B) =>
            RotatorImplementation.Rotator_InequalityImplementation(A, B);

        // @TODO KINDA_SMALL_NUMBER
        public Boolean IsNearlyZero(Single Tolerance) =>
            RotatorImplementation.Rotator_IsNearlyZeroImplementation(this, Tolerance);

        public Boolean IsZero() =>
            RotatorImplementation.Rotator_IsZeroImplementation(this);

        // @TODO KINDA_SMALL_NUMBER
        public Boolean Equals(FRotator R, Single Tolerance) =>
            RotatorImplementation.Rotator_EqualsImplementation(this, R, Tolerance);

        public FRotator Add(Single DeltaPitch, Single DeltaYaw, Single DeltaRoll)
        {
            RotatorImplementation.Rotator_AddDeltaImplementation(this, DeltaPitch, DeltaYaw, DeltaRoll,
                out var OutValue);

            return OutValue;
        }

        public FRotator GetInverse()
        {
            RotatorImplementation.Rotator_GetInverseImplementation(this, out var OutValue);

            return OutValue;
        }

        public FRotator GridSnap(FRotator RotGrid)
        {
            RotatorImplementation.Rotator_GridSnapImplementation(this, RotGrid, out var OutValue);

            return OutValue;
        }

        public FVector Vector()
        {
            RotatorImplementation.Rotator_VectorImplementation(this, out var OutValue);

            return OutValue;
        }

        public FQuat Quaternion()
        {
            RotatorImplementation.Rotator_QuaternionImplementation(this, out var OutValue);

            return OutValue;
        }

        public FVector Euler()
        {
            RotatorImplementation.Rotator_EulerImplementation(this, out var OutValue);

            return OutValue;
        }

        public FVector RotateVector(FVector V)
        {
            RotatorImplementation.Rotator_RotateVectorImplementation(this, V, out var OutValue);

            return OutValue;
        }

        public FVector UnrotateVector(FVector V)
        {
            RotatorImplementation.Rotator_UnrotateVectorImplementation(this, V, out var OutValue);

            return OutValue;
        }

        public FRotator Clamp()
        {
            RotatorImplementation.Rotator_ClampImplementation(this, out var OutValue);

            return OutValue;
        }

        public FRotator GetNormalized()
        {
            RotatorImplementation.Rotator_GetNormalizedImplementation(this, out var OutValue);

            return OutValue;
        }

        public FRotator GetDenormalized()
        {
            RotatorImplementation.Rotator_GetDenormalizedImplementation(this, out var OutValue);

            return OutValue;
        }

        // @TODO
        // GetComponentForAxis
        // SetComponentForAxis

        public void Normalize() =>
            RotatorImplementation.Rotator_NormalizeImplementation(this);

        public void GetWindingAndRemainder(out FRotator Winding, out FRotator Remainder) =>
            RotatorImplementation.Rotator_GetWindingAndRemainderImplementation(this, out Winding, out Remainder);

        public Single GetManhattanDistance(FRotator Rotator) =>
            RotatorImplementation.Rotator_GetManhattanDistanceImplementation(this, Rotator);

        public FRotator GetEquivalentRotator()
        {
            RotatorImplementation.Rotator_GetEquivalentRotatorImplementation(this, out var OutValue);

            return OutValue;
        }

        public FRotator SetClosestToMe()
        {
            RotatorImplementation.Rotator_SetClosestToMeImplementation(this, out var OutValue);

            return OutValue;
        }

        public FString ToString()
        {
            RotatorImplementation.Rotator_ToStringImplementation(this, out var OutValue);

            return OutValue;
        }

        public FString ToCompactString()
        {
            RotatorImplementation.Rotator_ToCompactStringImplementation(this, out var OutValue);

            return OutValue;
        }

        public Boolean InitFromString(FString InSourceString) =>
            RotatorImplementation.Rotator_InitFromStringImplementation(this, InSourceString);

        public Boolean ContainsNaN() =>
            RotatorImplementation.Rotator_ContainsNaNImplementation(this);

        public static Single ClampAxis(Single Angle) =>
            RotatorImplementation.Rotator_ClampAxisImplementation(Angle);

        public static Single NormalizeAxis(Single Angle) =>
            RotatorImplementation.Rotator_NormalizeAxisImplementation(Angle);

        public static Byte CompressAxisToByte(Single Angle) =>
            RotatorImplementation.Rotator_CompressAxisToByteImplementation(Angle);

        public static Single DecompressAxisFromByte(Byte Angle) =>
            RotatorImplementation.Rotator_DecompressAxisFromByteImplementation(Angle);

        public static UInt16 CompressAxisToByte(Byte Angle) =>
            RotatorImplementation.Rotator_CompressAxisToShortImplementation(Angle);

        public static Single DecompressAxisFromShort(UInt16 Angle) =>
            RotatorImplementation.Rotator_DecompressAxisFromShortImplementation(Angle);

        public static FRotator MakeFromEuler(FVector Euler)
        {
            RotatorImplementation.Rotator_MakeFromEulerImplementation(Euler, out var OutValue);

            return OutValue;
        }
    }
}