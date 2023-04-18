using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FVector4
    {
        public Single this[Int32 ComponentIndex]
        {
            get => Vector4Implementation.Vector4_GetComponentImplementation(this, ComponentIndex);

            set => Vector4Implementation.Vector4_SetComponentImplementation(this, ComponentIndex, value);
        }

        public static FVector4 operator -(FVector4 A)
        {
            Vector4Implementation.Vector4_NegatedImplementation(A, out var OutValue);

            return OutValue;
        }

        public static FVector4 operator +(FVector4 A, FVector4 B)
        {
            Vector4Implementation.Vector4_AddImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FVector4 operator -(FVector4 A, FVector4 B)
        {
            Vector4Implementation.Vector4_SubtractImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FVector4 operator *(FVector4 A, Single Scale)
        {
            Vector4Implementation.Vector4_MultiplyScaleImplementation(A, Scale, out var OutValue);

            return OutValue;
        }

        public static FVector4 operator /(FVector4 A, Single Scale)
        {
            Vector4Implementation.Vector4_DivideScaleImplementation(A, Scale, out var OutValue);

            return OutValue;
        }

        public static FVector4 operator /(FVector4 A, FVector4 B)
        {
            Vector4Implementation.Vector4_DivideImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FVector4 operator *(FVector4 A, FVector4 B)
        {
            Vector4Implementation.Vector4_MultiplyImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static Single Dot3(FVector4 V1, FVector4 V2) =>
            Vector4Implementation.Vector4_Dot3Implementation(V1, V2);

        public static Single Dot4(FVector4 V1, FVector4 V2) =>
            Vector4Implementation.Vector4_Dot4Implementation(V1, V2);

        public static Boolean operator ==(FVector4 A, FVector4 B) =>
            Vector4Implementation.Vector4_EqualityImplementation(A, B);

        public static Boolean operator !=(FVector4 A, FVector4 B) =>
            Vector4Implementation.Vector4_InequalityImplementation(A, B);

        public static FVector4 operator ^(FVector4 A, FVector4 B)
        {
            Vector4Implementation.Vector4_CrossProductImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public Single Component(Int32 Index) =>
            Vector4Implementation.Vector4_ComponentImplementation(this, Index);

        // @TODO KINDA_SMALL_NUMBER
        public Boolean Equals(FVector4 V, Single Tolerance) =>
            Vector4Implementation.Vector4_EqualsImplementation(this, V, Tolerance);

        // @TODO KINDA_SMALL_NUMBER
        public Boolean IsUnit3(Single LengthSquaredTolerance) =>
            Vector4Implementation.Vector4_IsUnit3Implementation(this, LengthSquaredTolerance);

        public override string ToString()
        {
            Vector4Implementation.Vector4_ToStringImplementation(this, out var OutValue);

            return OutValue.ToString();
        }

        public Boolean InitFromString(FString InSourceString) =>
            Vector4Implementation.Vector4_InitFromStringImplementation(this, InSourceString);

        // @TODO SMALL_NUMBER
        public FVector4 GetSafeNormal(Single Tolerance)
        {
            Vector4Implementation.Vector4_GetSafeNormalImplementation(this, Tolerance, out var OutValue);

            return OutValue;
        }

        public FVector4 GetUnsafeNormal3()
        {
            Vector4Implementation.Vector4_GetUnsafeNormal3Implementation(this, out var OutValue);

            return OutValue;
        }

        public FRotator ToOrientationRotator()
        {
            Vector4Implementation.Vector4_ToOrientationRotatorImplementation(this, out var OutValue);

            return OutValue;
        }

        public FQuat ToOrientationQuat()
        {
            Vector4Implementation.Vector4_ToOrientationQuatImplementation(this, out var OutValue);

            return OutValue;
        }

        public FRotator Rotation()
        {
            Vector4Implementation.Vector4_RotationImplementation(this, out var OutValue);

            return OutValue;
        }

        public void Set(Single InX, Single InY, Single InZ, Single InW) =>
            Vector4Implementation.Vector4_SetImplementation(this, InX, InY, InZ, InW);

        public Single Size3() =>
            Vector4Implementation.Vector4_Size3Implementation(this);

        public Single SizeSquared3() =>
            Vector4Implementation.Vector4_SizeSquared3Implementation(this);

        public Single Size() =>
            Vector4Implementation.Vector4_SizeImplementation(this);

        public Single SizeSquared() =>
            Vector4Implementation.Vector4_SizeSquaredImplementation(this);

        public Boolean ContainsNaN() =>
            Vector4Implementation.Vector4_ContainsNaNImplementation(this);

        // @TODO KINDA_SMALL_NUMBER
        public Boolean IsNearlyZero3(Single Tolerance) =>
            Vector4Implementation.Vector4_IsNearlyZero3Implementation(this, Tolerance);

        public FVector4 Reflect3(FVector4 Normal)
        {
            Vector4Implementation.Vector4_Reflect3Implementation(this, Normal, out var OutValue);

            return OutValue;
        }

        public void FindBestAxisVectors3(out FVector4 Axis1, out FVector4 Axis2) =>
            Vector4Implementation.Vector4_FindBestAxisVectors3Implementation(this, out Axis1, out Axis2);
    }
}