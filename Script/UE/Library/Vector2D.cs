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
            Vector2DImplementation.Vector2D_AddImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FVector2D operator -(FVector2D A, FVector2D B)
        {
            Vector2DImplementation.Vector2D_SubtractImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FVector2D operator *(FVector2D A, LwcType Scale)
        {
            Vector2DImplementation.Vector2D_MultiplyScaleImplementation(A.GetHandle(), Scale, out var OutValue);

            return OutValue;
        }

        public static FVector2D operator /(FVector2D A, LwcType Scale)
        {
            Vector2DImplementation.Vector2D_DivideScaleImplementation(A.GetHandle(), Scale, out var OutValue);

            return OutValue;
        }

        public static FVector2D operator +(FVector2D A, LwcType Scale)
        {
            Vector2DImplementation.Vector2D_AddAImplementation(A.GetHandle(), Scale, out var OutValue);

            return OutValue;
        }

        public static FVector2D operator -(FVector2D A, LwcType Scale)
        {
            Vector2DImplementation.Vector2D_SubtractAImplementation(A.GetHandle(), Scale, out var OutValue);

            return OutValue;
        }

        public static FVector2D operator *(FVector2D A, FVector2D B)
        {
            Vector2DImplementation.Vector2D_MultiplyImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FVector2D operator /(FVector2D A, FVector2D B)
        {
            Vector2DImplementation.Vector2D_DivideImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static LwcType operator |(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_DotProductImplementation(A.GetHandle(), B.GetHandle());

        public static LwcType operator ^(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_CrossProductImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator ==(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_EqualityImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator !=(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_InequalityImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator <(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_LessThanImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator >(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_GreaterThanImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator <=(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_LessThanOrEqualImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator >=(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_GreaterThanOrEqualImplementation(A.GetHandle(), B.GetHandle());

        public static FVector2D operator -(FVector2D A)
        {
            Vector2DImplementation.Vector2D_NegatedImplementation(A.GetHandle(), out var OutValue);

            return OutValue;
        }

        public LwcType this[Int32 Index]
        {
            get => Vector2DImplementation.Vector2D_GetComponentImplementation(GetHandle(), Index);

            set => Vector2DImplementation.Vector2D_SetComponentImplementation(GetHandle(), Index, value);
        }

        public LwcType Component(Int32 Index) =>
            Vector2DImplementation.Vector2D_ComponentImplementation(GetHandle(), Index);

        public static LwcType DotProduct(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_DotProductImplementation(A.GetHandle(), B.GetHandle());

        public static LwcType DistSquared(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_DistSquaredImplementation(A.GetHandle(), B.GetHandle());

        public static LwcType Distance(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_DistanceImplementation(A.GetHandle(), B.GetHandle());

        public static LwcType CrossProduct(FVector2D A, FVector2D B) =>
            Vector2DImplementation.Vector2D_CrossProductImplementation(A.GetHandle(), B.GetHandle());

        public static FVector2D Max(FVector2D A, FVector2D B)
        {
            Vector2DImplementation.Vector2D_MaxImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FVector2D Min(FVector2D A, FVector2D B)
        {
            Vector2DImplementation.Vector2D_MinImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        // @TODO KINDA_SMALL_NUMBER
        public Boolean Equals(FVector2D V, LwcType Tolerance) =>
            Vector2DImplementation.Vector2D_EqualsImplementation(GetHandle(), V.GetHandle(), Tolerance);

        public void Set(LwcType InX, LwcType InY) =>
            Vector2DImplementation.Vector2D_SetImplementation(GetHandle(), InX, InY);

        public LwcType GetMax() =>
            Vector2DImplementation.Vector2D_GetMaxImplementation(GetHandle());

        public LwcType GetAbsMax() =>
            Vector2DImplementation.Vector2D_GetAbsMaxImplementation(GetHandle());

        public LwcType GetMin() =>
            Vector2DImplementation.Vector2D_GetMinImplementation(GetHandle());

        public LwcType Size() =>
            Vector2DImplementation.Vector2D_SizeImplementation(GetHandle());

        public LwcType SizeSquared() =>
            Vector2DImplementation.Vector2D_SizeSquaredImplementation(GetHandle());

        public FVector2D GetRotated(LwcType AngleDeg)
        {
            Vector2DImplementation.Vector2D_GetRotatedImplementation(GetHandle(), AngleDeg, out var OutValue);

            return OutValue;
        }

        // @TODO SMALL_NUMBER
        public FVector2D GetSafeNormal(LwcType Tolerance)
        {
            Vector2DImplementation.Vector2D_GetSafeNormalImplementation(GetHandle(), Tolerance, out var OutValue);

            return OutValue;
        }

        // @TODO SMALL_NUMBER
        public void Normalize(LwcType Tolerance) =>
            Vector2DImplementation.Vector2D_NormalizeImplementation(GetHandle(), Tolerance);

        // @TODO KINDA_SMALL_NUMBER
        public Boolean IsNearlyZero(LwcType Tolerance) =>
            Vector2DImplementation.Vector2D_IsNearlyZeroImplementation(GetHandle(), Tolerance);

        public void ToDirectionAndLength(out FVector2D OutDir, out LwcType OutLength) =>
            Vector2DImplementation.Vector2D_ToDirectionAndLengthImplementation(GetHandle(), out OutDir, out OutLength);

        public Boolean IsZero() =>
            Vector2DImplementation.Vector2D_IsZeroImplementation(GetHandle());

        public FIntPoint IntPoint()
        {
            Vector2DImplementation.Vector2D_IntPointImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FVector2D RoundToVector()
        {
            Vector2DImplementation.Vector2D_RoundToVectorImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FVector2D ClampAxes(LwcType MinAxisVal, LwcType MaxAxisVal)
        {
            Vector2DImplementation.Vector2D_ClampAxesImplementation(GetHandle(), MinAxisVal, MaxAxisVal,
                out var OutValue);

            return OutValue;
        }

        public FVector2D GetSignVector()
        {
            Vector2DImplementation.Vector2D_GetSignVectorImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FVector2D GetAbs()
        {
            Vector2DImplementation.Vector2D_GetAbsImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public override string ToString()
        {
            Vector2DImplementation.Vector2D_ToStringImplementation(GetHandle(), out var OutValue);

            return OutValue.ToString();
        }

        public Boolean InitFromString(FString InSourceString) =>
            Vector2DImplementation.Vector2D_InitFromStringImplementation(GetHandle(), InSourceString);

        public Boolean ContainsNaN() =>
            Vector2DImplementation.Vector2D_ContainsNaNImplementation(GetHandle());

        public FVector SphericalToUnitCartesian()
        {
            Vector2DImplementation.Vector2D_SphericalToUnitCartesianImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }
    }
}