using System;
using Script.Library;

namespace Script.CoreUObject
{
    public partial class FMatrix
    {
        public LwcType this[UInt32 InRow, UInt32 InColumn]
        {
            get => MatrixImplementation.Matrix_GetMImplementation(GetHandle(), InRow, InColumn);

            set => MatrixImplementation.Matrix_SetMImplementation(GetHandle(), InRow, InColumn, value);
        }

        public FMatrix M => this;

        public void SetIdentity() =>
            MatrixImplementation.Matrix_SetIdentityImplementation(GetHandle());

        public static FMatrix operator *(FMatrix A, FMatrix B)
        {
            MatrixImplementation.Matrix_MultiplyImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FMatrix operator +(FMatrix A, FMatrix B)
        {
            MatrixImplementation.Matrix_AddImplementation(A.GetHandle(), B.GetHandle(), out var OutValue);

            return OutValue;
        }

        public static FMatrix operator *(FMatrix A, LwcType Other)
        {
            MatrixImplementation.Matrix_MultiplyScaleImplementation(A.GetHandle(), Other, out var OutValue);

            return OutValue;
        }

        // @TODO KINDA_SMALL_NUMBER
        public Boolean Equals(FMatrix Other, LwcType Tolerance) =>
            MatrixImplementation.Matrix_EqualsImplementation(GetHandle(), Other.GetHandle(), Tolerance);

        public FVector4 TransformFVector4(FVector4 V)
        {
            MatrixImplementation.Matrix_TransformFVector4Implementation(GetHandle(), V, out var OutValue);

            return OutValue;
        }

        public FVector4 TransformPosition(FVector V)
        {
            MatrixImplementation.Matrix_TransformPositionImplementation(GetHandle(), V, out var OutValue);

            return OutValue;
        }

        public FVector InverseTransformPosition(FVector V)
        {
            MatrixImplementation.Matrix_InverseTransformPositionImplementation(GetHandle(), V, out var OutValue);

            return OutValue;
        }

        public FVector4 TransformVector(FVector V)
        {
            MatrixImplementation.Matrix_TransformVectorImplementation(GetHandle(), V, out var OutValue);

            return OutValue;
        }

        public FVector InverseTransformVector(FVector V)
        {
            MatrixImplementation.Matrix_InverseTransformVectorImplementation(GetHandle(), V, out var OutValue);

            return OutValue;
        }

        public FMatrix GetTransposed(FVector V)
        {
            MatrixImplementation.Matrix_GetTransposedImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public LwcType Determinant() =>
            MatrixImplementation.Matrix_DeterminantImplementation(GetHandle());

        public LwcType RotDeterminant() =>
            MatrixImplementation.Matrix_RotDeterminantImplementation(GetHandle());

        public FMatrix InverseFast()
        {
            MatrixImplementation.Matrix_InverseFastImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FMatrix Inverse()
        {
            MatrixImplementation.Matrix_InverseImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FMatrix TransposeAdjoint()
        {
            MatrixImplementation.Matrix_TransposeAdjointImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        // @TODO SMALL_NUMBER
        public void RemoveScaling(FMatrix Other, LwcType Tolerance) =>
            MatrixImplementation.Matrix_RemoveScalingImplementation(GetHandle(), Tolerance);

        // @TODO SMALL_NUMBER
        public FMatrix GetMatrixWithoutScale(LwcType Tolerance)
        {
            MatrixImplementation.Matrix_GetMatrixWithoutScaleImplementation(GetHandle(), Tolerance, out var OutValue);

            return OutValue;
        }

        // @TODO SMALL_NUMBER
        public FVector ExtractScaling(LwcType Tolerance)
        {
            MatrixImplementation.Matrix_ExtractScalingImplementation(GetHandle(), Tolerance, out var OutValue);

            return OutValue;
        }

        // @TODO SMALL_NUMBER
        public FVector GetScaleVector(LwcType Tolerance)
        {
            MatrixImplementation.Matrix_GetScaleVectorImplementation(GetHandle(), Tolerance, out var OutValue);

            return OutValue;
        }

        public FMatrix RemoveTranslation()
        {
            MatrixImplementation.Matrix_RemoveTranslationImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FMatrix ConcatTranslation(FVector Translation)
        {
            MatrixImplementation.Matrix_ConcatTranslationImplementation(GetHandle(), Translation, out var OutValue);

            return OutValue;
        }

        public Boolean ContainsNaN() =>
            MatrixImplementation.Matrix_ContainsNaNImplementation(GetHandle());

        public void ScaleTranslation(FVector Scale3D) =>
            MatrixImplementation.Matrix_ScaleTranslationImplementation(GetHandle(), Scale3D);

        public LwcType GetMaximumAxisScale() =>
            MatrixImplementation.Matrix_GetMaximumAxisScaleImplementation(GetHandle());

        public FMatrix ApplyScale(LwcType Scale)
        {
            MatrixImplementation.Matrix_ApplyScaleImplementation(GetHandle(), Scale, out var OutValue);

            return OutValue;
        }

        public FVector GetOrigin()
        {
            MatrixImplementation.Matrix_GetOriginImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        // @TOOD
        // GetScaledAxis

        public void GetScaledAxes(out FVector X, out FVector Y, out FVector Z) =>
            MatrixImplementation.Matrix_GetScaledAxesImplementation(GetHandle(), out X, out Y, out Z);

        // @TOOD
        // GetUnitAxis

        public void GetUnitAxes(out FVector X, out FVector Y, out FVector Z) =>
            MatrixImplementation.Matrix_GetUnitAxesImplementation(GetHandle(), out X, out Y, out Z);

        public void SetAxis(Int32 i, FVector Axis) =>
            MatrixImplementation.Matrix_SetAxisImplementation(GetHandle(), i, Axis);

        public void SetOrigin(Int32 i, FVector NewOrigin) =>
            MatrixImplementation.Matrix_SetOriginImplementation(GetHandle(), NewOrigin);

        public void SetAxes(FVector Axis0, FVector Axis1, FVector Axis2, FVector Origin) =>
            MatrixImplementation.Matrix_SetAxesImplementation(GetHandle(), Axis0, Axis1, Axis2, Origin);

        public FVector GetColumn(Int32 i)
        {
            MatrixImplementation.Matrix_GetColumnImplementation(GetHandle(), i, out var OutValue);

            return OutValue;
        }

        public void SetColumn(Int32 i, FVector Value) =>
            MatrixImplementation.Matrix_SetColumnImplementation(GetHandle(), i, Value);

        public FRotator Rotator()
        {
            MatrixImplementation.Matrix_RotatorImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FQuat ToQuat()
        {
            MatrixImplementation.Matrix_ToQuatImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public Boolean GetFrustumNearPlane(out FPlane OutPlane) =>
            MatrixImplementation.Matrix_GetFrustumNearPlaneImplementation(GetHandle(), out OutPlane);

        public Boolean GetFrustumFarPlane(out FPlane OutPlane) =>
            MatrixImplementation.Matrix_GetFrustumFarPlaneImplementation(GetHandle(), out OutPlane);

        public Boolean GetFrustumLeftPlane(out FPlane OutPlane) =>
            MatrixImplementation.Matrix_GetFrustumLeftPlaneImplementation(GetHandle(), out OutPlane);

        public Boolean GetFrustumRightPlane(out FPlane OutPlane) =>
            MatrixImplementation.Matrix_GetFrustumRightPlaneImplementation(GetHandle(), out OutPlane);

        public Boolean GetFrustumTopPlane(out FPlane OutPlane) =>
            MatrixImplementation.Matrix_GetFrustumTopPlaneImplementation(GetHandle(), out OutPlane);

        public Boolean GetFrustumBottomPlane(out FPlane OutPlane) =>
            MatrixImplementation.Matrix_GetFrustumBottomPlaneImplementation(GetHandle(), out OutPlane);

        // @TOOD
        // Mirror

        public override string ToString()
        {
            MatrixImplementation.Matrix_ToStringImplementation(GetHandle(), out var OutValue);

            return OutValue.ToString();
        }

        public UInt32 ComputeHash() =>
            MatrixImplementation.Matrix_ComputeHashImplementation(GetHandle());

        // @TOOD
        // To3x4MatrixTranspose
    }
}