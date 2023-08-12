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
    public partial class FVector4
    {
        public LwcType this[Int32 ComponentIndex]
        {
            get => Vector4Implementation.Vector4_GetComponentImplementation(GetHandle(), ComponentIndex);

            set => Vector4Implementation.Vector4_SetComponentImplementation(GetHandle(), ComponentIndex, value);
        }

        public static FVector4 operator -(FVector4 A)
        {
            Vector4Implementation.Vector4_NegatedImplementation(A.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FVector4 operator +(FVector4 A, FVector4 B)
        {
            Vector4Implementation.Vector4_AddImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FVector4 operator -(FVector4 A, FVector4 B)
        {
            Vector4Implementation.Vector4_SubtractImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FVector4 operator *(FVector4 A, LwcType Scale)
        {
            Vector4Implementation.Vector4_MultiplyScaleImplementation(A.GetHandle(), Scale, out var OutValue);

            return OutValue;
        }

        public static FVector4 operator /(FVector4 A, LwcType Scale)
        {
            Vector4Implementation.Vector4_DivideScaleImplementation(A.GetHandle(), Scale, out var OutValue);

            return OutValue;
        }

        public static FVector4 operator /(FVector4 A, FVector4 B)
        {
            Vector4Implementation.Vector4_DivideImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FVector4 operator *(FVector4 A, FVector4 B)
        {
            Vector4Implementation.Vector4_MultiplyImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static LwcType Dot3(FVector4 V1, FVector4 V2) =>
            Vector4Implementation.Vector4_Dot3Implementation(V1.GetHandle(), V2.GetHandle());

        public static LwcType Dot4(FVector4 V1, FVector4 V2) =>
            Vector4Implementation.Vector4_Dot4Implementation(V1.GetHandle(), V2.GetHandle());

        public static Boolean operator ==(FVector4 A, FVector4 B) =>
            Vector4Implementation.Vector4_EqualityImplementation(A.GetHandle(), B.GetHandle());

        public static Boolean operator !=(FVector4 A, FVector4 B) =>
            Vector4Implementation.Vector4_InequalityImplementation(A.GetHandle(), B.GetHandle());

        public static FVector4 operator ^(FVector4 A, FVector4 B)
        {
            Vector4Implementation.Vector4_CrossProductImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public LwcType Component(Int32 Index) =>
            Vector4Implementation.Vector4_ComponentImplementation(GetHandle(), Index);

        // @TODO KINDA_SMALL_NUMBER
        public Boolean Equals(FVector4 V, LwcType Tolerance) =>
            Vector4Implementation.Vector4_EqualsImplementation(GetHandle(), V.GetHandle(), Tolerance);

        // @TODO KINDA_SMALL_NUMBER
        public Boolean IsUnit3(LwcType LengthSquaredTolerance) =>
            Vector4Implementation.Vector4_IsUnit3Implementation(GetHandle(), LengthSquaredTolerance);

        public override string ToString()
        {
            Vector4Implementation.Vector4_ToStringImplementation(GetHandle(), out var OutValue);

            return OutValue.ToString();
        }

        public Boolean InitFromString(FString InSourceString) =>
            Vector4Implementation.Vector4_InitFromStringImplementation(GetHandle(), InSourceString);

        // @TODO SMALL_NUMBER
        public FVector4 GetSafeNormal(LwcType Tolerance)
        {
            Vector4Implementation.Vector4_GetSafeNormalImplementation(GetHandle(), Tolerance, out var OutValue);

            return OutValue;
        }

        public FVector4 GetUnsafeNormal3()
        {
            Vector4Implementation.Vector4_GetUnsafeNormal3Implementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FRotator ToOrientationRotator()
        {
            Vector4Implementation.Vector4_ToOrientationRotatorImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FQuat ToOrientationQuat()
        {
            Vector4Implementation.Vector4_ToOrientationQuatImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FRotator Rotation()
        {
            Vector4Implementation.Vector4_RotationImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public void Set(LwcType InX, LwcType InY, LwcType InZ, LwcType InW) =>
            Vector4Implementation.Vector4_SetImplementation(GetHandle(), InX, InY, InZ, InW);

        public LwcType Size3() =>
            Vector4Implementation.Vector4_Size3Implementation(GetHandle());

        public LwcType SizeSquared3() =>
            Vector4Implementation.Vector4_SizeSquared3Implementation(GetHandle());

        public LwcType Size() =>
            Vector4Implementation.Vector4_SizeImplementation(GetHandle());

        public LwcType SizeSquared() =>
            Vector4Implementation.Vector4_SizeSquaredImplementation(GetHandle());

        public Boolean ContainsNaN() =>
            Vector4Implementation.Vector4_ContainsNaNImplementation(GetHandle());

        // @TODO KINDA_SMALL_NUMBER
        public Boolean IsNearlyZero3(LwcType Tolerance) =>
            Vector4Implementation.Vector4_IsNearlyZero3Implementation(GetHandle(), Tolerance);

        public FVector4 Reflect3(FVector4 Normal)
        {
            Vector4Implementation.Vector4_Reflect3Implementation(GetHandle(), Normal, out var OutValue);

            return OutValue;
        }

        public void FindBestAxisVectors3(out FVector4 Axis1, out FVector4 Axis2) =>
            Vector4Implementation.Vector4_FindBestAxisVectors3Implementation(GetHandle(), out Axis1, out Axis2);
    }
}