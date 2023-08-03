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

        public static FVector2D operator *(FVector2D A, LwcType Scale)
        {
            Vector2DImplementation.Vector2D_MultiplyScaleImplementation(A, Scale, out var OutValue);

            return OutValue;
        }

        public static FVector2D operator /(FVector2D A, LwcType Scale)
        {
            Vector2DImplementation.Vector2D_DivideScaleImplementation(A, Scale, out var OutValue);

            return OutValue;
        }

        public static FVector2D operator +(FVector2D A, LwcType Scale)
        {
            Vector2DImplementation.Vector2D_AddAImplementation(A, Scale, out var OutValue);

            return OutValue;
        }

        public static FVector2D operator -(FVector2D A, LwcType Scale)
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

        public static LwcType operator |(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_DotProductImplementation(A, B);

        public static LwcType operator ^(FVector2D A, FVector2D B) =>
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

        public LwcType this[Int32 Index]
        {
            get => Vector2DImplementation.Vector2D_GetComponentImplementation(this, Index);

            set => Vector2DImplementation.Vector2D_SetComponentImplementation(this, Index, value);
        }

        public LwcType Component(Int32 Index) =>
            Vector2DImplementation.Vector2D_ComponentImplementation(this, Index);

        public static LwcType DotProduct(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_DotProductImplementation(A, B);

        public static LwcType DistSquared(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_DistSquaredImplementation(A, B);

        public static LwcType Distance(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_DistanceImplementation(A, B);

        public static LwcType CrossProduct(FVector2D A, FVector2D B) =>
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
        public Boolean Equals(FVector2D V, LwcType Tolerance) =>
            Vector2DImplementation.Vector2D_EqualsImplementation(this, V, Tolerance);

        public void Set(LwcType InX, LwcType InY) =>
            Vector2DImplementation.Vector2D_SetImplementation(this, InX, InY);

        public LwcType GetMax() =>
            Vector2DImplementation.Vector2D_GetMaxImplementation(this);

        public LwcType GetAbsMax() =>
            Vector2DImplementation.Vector2D_GetAbsMaxImplementation(this);

        public LwcType GetMin() =>
            Vector2DImplementation.Vector2D_GetMinImplementation(this);

        public LwcType Size() =>
            Vector2DImplementation.Vector2D_SizeImplementation(this);

        public LwcType SizeSquared() =>
            Vector2DImplementation.Vector2D_SizeSquaredImplementation(this);

        public FVector2D GetRotated(LwcType AngleDeg)
        {
            Vector2DImplementation.Vector2D_GetRotatedImplementation(this, AngleDeg, out var OutValue);

            return OutValue;
        }

        // @TODO SMALL_NUMBER
        public FVector2D GetSafeNormal(LwcType Tolerance)
        {
            Vector2DImplementation.Vector2D_GetSafeNormalImplementation(this, Tolerance, out var OutValue);

            return OutValue;
        }

        // @TODO SMALL_NUMBER
        public void Normalize(LwcType Tolerance) =>
            Vector2DImplementation.Vector2D_NormalizeImplementation(this, Tolerance);

        // @TODO KINDA_SMALL_NUMBER
        public Boolean IsNearlyZero(LwcType Tolerance) =>
            Vector2DImplementation.Vector2D_IsNearlyZeroImplementation(this, Tolerance);

        public void ToDirectionAndLength(out FVector2D OutDir, out LwcType OutLength) =>
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

        public FVector2D ClampAxes(LwcType MinAxisVal, LwcType MaxAxisVal)
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