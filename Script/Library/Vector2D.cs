using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FVector2D
    {
        public static FVector2D operator +(FVector2D A, FVector2D B)
        {
            Vector2DImplementation.Vector2D_AddImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FVector2D operator -(FVector2D A, FVector2D B)
        {
            Vector2DImplementation.Vector2D_SubtractImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FVector2D operator *(FVector2D A, Single Scale)
        {
            Vector2DImplementation.Vector2D_MultiplyScaleImplementation(A, Scale, out var OutValue);

            return OutValue;
        }

        public static FVector2D operator /(FVector2D A, Single Scale)
        {
            Vector2DImplementation.Vector2D_DivideScaleImplementation(A, Scale, out var OutValue);

            return OutValue;
        }

        public static FVector2D operator +(FVector2D A, Single Scale)
        {
            Vector2DImplementation.Vector2D_AddAImplementation(A, Scale, out var OutValue);

            return OutValue;
        }

        public static FVector2D operator -(FVector2D A, Single Scale)
        {
            Vector2DImplementation.Vector2D_SubtractAImplementation(A, Scale, out var OutValue);

            return OutValue;
        }

        public static FVector2D operator *(FVector2D A, FVector2D B)
        {
            Vector2DImplementation.Vector2D_MultiplyImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FVector2D operator /(FVector2D A, FVector2D B)
        {
            Vector2DImplementation.Vector2D_DivideImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static Single operator |(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_DotProductImplementation(A, B);

        public static Single operator ^(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_CrossProductImplementation(A, B);

        public static Boolean operator ==(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_EqualityImplementation(A, B);

        public static Boolean operator !=(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_InequalityImplementation(A, B);

        public static Boolean operator <(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_LessThanImplementation(A, B);

        public static Boolean operator >(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_GreaterThanImplementation(A, B);

        public static Boolean operator <=(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_LessThanOrEqualImplementation(A, B);

        public static Boolean operator >=(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_GreaterThanOrEqualImplementation(A, B);

        public static FVector2D operator -(FVector2D A)
        {
            Vector2DImplementation.Vector2D_NegatedImplementation(A, out var OutValue);

            return OutValue;
        }

        public Single this[Int32 Index]
        {
            get => Vector2DImplementation.Vector2D_GetComponentImplementation(this, Index);

            set => Vector2DImplementation.Vector2D_SetComponentImplementation(this, Index, value);
        }

        public Single Component(Int32 Index) =>
            Vector2DImplementation.Vector2D_ComponentImplementation(this, Index);

        public static Single DotProduct(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_DotProductImplementation(A, B);

        public static Single DistSquared(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_DistSquaredImplementation(A, B);

        public static Single Distance(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_DistanceImplementation(A, B);

        public static Single CrossProduct(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_CrossProductImplementation(A, B);

        public static FVector2D Max(FVector2D A, FVector2D B)
        {
            Vector2DImplementation.Vector2D_MaxImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FVector2D Min(FVector2D A, FVector2D B)
        {
            Vector2DImplementation.Vector2D_MinImplementation(A, B, out var OutValue);

            return OutValue;
        }

        // @TODO KINDA_SMALL_NUMBER
        public Boolean Equals(FVector2D V, Single Tolerance) =>
            Vector2DImplementation.Vector2D_EqualsImplementation(this, V, Tolerance);

        public void Set(Single InX, Single InY) =>
            Vector2DImplementation.Vector2D_SetImplementation(this, InX, InY);

        public Single GetMax() =>
            Vector2DImplementation.Vector2D_GetMaxImplementation(this);

        public Single GetAbsMax() =>
            Vector2DImplementation.Vector2D_GetAbsMaxImplementation(this);

        public Single GetMin() =>
            Vector2DImplementation.Vector2D_GetMinImplementation(this);

        public Single Size() =>
            Vector2DImplementation.Vector2D_SizeImplementation(this);

        public Single SizeSquared() =>
            Vector2DImplementation.Vector2D_SizeSquaredImplementation(this);

        public FVector2D GetRotated(Single AngleDeg)
        {
            Vector2DImplementation.Vector2D_GetRotatedImplementation(this, AngleDeg, out var OutValue);

            return OutValue;
        }

        // @TODO SMALL_NUMBER
        public FVector2D GetSafeNormal(Single Tolerance)
        {
            Vector2DImplementation.Vector2D_GetSafeNormalImplementation(this, Tolerance, out var OutValue);

            return OutValue;
        }

        // @TODO SMALL_NUMBER
        public void Normalize(Single Tolerance) =>
            Vector2DImplementation.Vector2D_NormalizeImplementation(this, Tolerance);

        // @TODO KINDA_SMALL_NUMBER
        public Boolean IsNearlyZero(Single Tolerance) =>
            Vector2DImplementation.Vector2D_IsNearlyZeroImplementation(this, Tolerance);

        public void ToDirectionAndLength(out FVector2D OutDir, out Single OutLength) =>
            Vector2DImplementation.Vector2D_ToDirectionAndLengthImplementation(this, out OutDir, out OutLength);

        public Boolean IsZero() =>
            Vector2DImplementation.Vector2D_IsZeroImplementation(this);

        public FIntPoint IntPoint()
        {
            Vector2DImplementation.Vector2D_IntPointImplementation(this, out var OutValue);

            return OutValue;
        }

        public FVector2D RoundToVector()
        {
            Vector2DImplementation.Vector2D_RoundToVectorImplementation(this, out var OutValue);

            return OutValue;
        }

        public FVector2D ClampAxes(Single MinAxisVal, Single MaxAxisVal)
        {
            Vector2DImplementation.Vector2D_ClampAxesImplementation(this, MinAxisVal, MaxAxisVal, out var OutValue);

            return OutValue;
        }

        public FVector2D GetSignVector()
        {
            Vector2DImplementation.Vector2D_GetSignVectorImplementation(this, out var OutValue);

            return OutValue;
        }

        public FVector2D GetAbs()
        {
            Vector2DImplementation.Vector2D_GetAbsImplementation(this, out var OutValue);

            return OutValue;
        }

        public override string ToString()
        {
            Vector2DImplementation.Vector2D_ToStringImplementation(this, out var OutValue);

            return OutValue.ToString();
        }

        public Boolean InitFromString(FString InSourceString) =>
            Vector2DImplementation.Vector2D_InitFromStringImplementation(this, InSourceString);

        public Boolean ContainsNaN() =>
            Vector2DImplementation.Vector2D_ContainsNaNImplementation(this);

        public FVector SphericalToUnitCartesian()
        {
            Vector2DImplementation.Vector2D_SphericalToUnitCartesianImplementation(this, out var OutValue);

            return OutValue;
        }
    }
}