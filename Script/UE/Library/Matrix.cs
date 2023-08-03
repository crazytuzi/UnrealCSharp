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
    public partial class FMatrix
    {
        public LwcType this[UInt32 InRow, UInt32 InColumn]
        {
            get => MatrixImplementation.Matrix_GetMImplementation(this, InRow, InColumn);

            set => MatrixImplementation.Matrix_SetMImplementation(this, InRow, InColumn, value);
        }

        public FMatrix M => this;

        public void SetIdentity() =>
            MatrixImplementation.Matrix_SetIdentityImplementation(this);

        public static FMatrix operator *(FMatrix A, FMatrix B)
        {
            MatrixImplementation.Matrix_MultiplyImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FMatrix operator +(FMatrix A, FMatrix B)
        {
            MatrixImplementation.Matrix_AddImplementation(A, B, out var OutValue);

            return OutValue;
        }

        public static FMatrix operator *(FMatrix A, LwcType Other)
        {
            MatrixImplementation.Matrix_MultiplyScaleImplementation(A, Other, out var OutValue);

            return OutValue;
        }

        public static Boolean operator ==(FMatrix A, FMatrix B) =>
            MatrixImplementation.Matrix_EqualityImplementation(A, B);

        // @TODO KINDA_SMALL_NUMBER
        public Boolean Equals(FMatrix Other, LwcType Tolerance) =>
            MatrixImplementation.Matrix_EqualsImplementation(this, Other, Tolerance);

        public static Boolean operator !=(FMatrix A, FMatrix B) =>
            MatrixImplementation.Matrix_InequalityImplementation(A, B);

        public FVector4 TransformFVector4(FVector4 V)
        {
            MatrixImplementation.Matrix_TransformFVector4Implementation(this, V, out var OutValue);

            return OutValue;
        }

        public FVector4 TransformPosition(FVector V)
        {
            MatrixImplementation.Matrix_TransformPositionImplementation(this, V, out var OutValue);

            return OutValue;
        }

        public FVector InverseTransformPosition(FVector V)
        {
            MatrixImplementation.Matrix_InverseTransformPositionImplementation(this, V, out var OutValue);

            return OutValue;
        }

        public FVector4 TransformVector(FVector V)
        {
            MatrixImplementation.Matrix_TransformVectorImplementation(this, V, out var OutValue);

            return OutValue;
        }

        public FVector InverseTransformVector(FVector V)
        {
            MatrixImplementation.Matrix_InverseTransformVectorImplementation(this, V, out var OutValue);

            return OutValue;
        }

        public FMatrix GetTransposed(FVector V)
        {
            MatrixImplementation.Matrix_GetTransposedImplementation(this, out var OutValue);

            return OutValue;
        }

        public LwcType Determinant() =>
            MatrixImplementation.Matrix_DeterminantImplementation(this);

        public LwcType RotDeterminant() =>
            MatrixImplementation.Matrix_RotDeterminantImplementation(this);

        public FMatrix InverseFast()
        {
            MatrixImplementation.Matrix_InverseFastImplementation(this, out var OutValue);

            return OutValue;
        }

        public FMatrix Inverse()
        {
            MatrixImplementation.Matrix_InverseImplementation(this, out var OutValue);

            return OutValue;
        }

        public FMatrix TransposeAdjoint()
        {
            MatrixImplementation.Matrix_TransposeAdjointImplementation(this, out var OutValue);

            return OutValue;
        }

        // @TODO SMALL_NUMBER
        public void RemoveScaling(FMatrix Other, LwcType Tolerance) =>
            MatrixImplementation.Matrix_RemoveScalingImplementation(this, Tolerance);

        // @TODO SMALL_NUMBER
        public FMatrix GetMatrixWithoutScale(LwcType Tolerance)
        {
            MatrixImplementation.Matrix_GetMatrixWithoutScaleImplementation(this, Tolerance, out var OutValue);

            return OutValue;
        }

        // @TODO SMALL_NUMBER
        public FVector ExtractScaling(LwcType Tolerance)
        {
            MatrixImplementation.Matrix_ExtractScalingImplementation(this, Tolerance, out var OutValue);

            return OutValue;
        }

        // @TODO SMALL_NUMBER
        public FVector GetScaleVector(LwcType Tolerance)
        {
            MatrixImplementation.Matrix_GetScaleVectorImplementation(this, Tolerance, out var OutValue);

            return OutValue;
        }

        public FMatrix RemoveTranslation()
        {
            MatrixImplementation.Matrix_RemoveTranslationImplementation(this, out var OutValue);

            return OutValue;
        }

        public FMatrix ConcatTranslation(FVector Translation)
        {
            MatrixImplementation.Matrix_ConcatTranslationImplementation(this, Translation, out var OutValue);

            return OutValue;
        }

        public Boolean ContainsNaN() =>
            MatrixImplementation.Matrix_ContainsNaNImplementation(this);

        public void ScaleTranslation(FVector Scale3D) =>
            MatrixImplementation.Matrix_ScaleTranslationImplementation(this, Scale3D);

        public LwcType GetMaximumAxisScale() =>
            MatrixImplementation.Matrix_GetMaximumAxisScaleImplementation(this);

        public FMatrix ApplyScale(LwcType Scale)
        {
            MatrixImplementation.Matrix_ApplyScaleImplementation(this, Scale, out var OutValue);

            return OutValue;
        }

        public FVector GetOrigin()
        {
            MatrixImplementation.Matrix_GetOriginImplementation(this, out var OutValue);

            return OutValue;
        }

        // @TOOD
        // GetScaledAxis

        public void GetScaledAxes(out FVector X, out FVector Y, out FVector Z) =>
            MatrixImplementation.Matrix_GetScaledAxesImplementation(this, out X, out Y, out Z);

        // @TOOD
        // GetUnitAxis

        public void GetUnitAxes(out FVector X, out FVector Y, out FVector Z) =>
            MatrixImplementation.Matrix_GetUnitAxesImplementation(this, out X, out Y, out Z);

        public void SetAxis(Int32 i, FVector Axis) =>
            MatrixImplementation.Matrix_SetAxisImplementation(this, i, Axis);

        public void SetOrigin(Int32 i, FVector NewOrigin) =>
            MatrixImplementation.Matrix_SetOriginImplementation(this, NewOrigin);

        public void SetAxes(FVector Axis0, FVector Axis1, FVector Axis2, FVector Origin) =>
            MatrixImplementation.Matrix_SetAxesImplementation(this, Axis0, Axis1, Axis2, Origin);

        public FVector GetColumn(Int32 i)
        {
            MatrixImplementation.Matrix_GetColumnImplementation(this, i, out var OutValue);

            return OutValue;
        }

        public void SetColumn(Int32 i, FVector Value) =>
            MatrixImplementation.Matrix_SetColumnImplementation(this, i, Value);

        public FRotator Rotator()
        {
            MatrixImplementation.Matrix_RotatorImplementation(this, out var OutValue);

            return OutValue;
        }

        public FQuat ToQuat()
        {
            MatrixImplementation.Matrix_ToQuatImplementation(this, out var OutValue);

            return OutValue;
        }

        public Boolean GetFrustumNearPlane(out FPlane OutPlane) =>
            MatrixImplementation.Matrix_GetFrustumNearPlaneImplementation(this, out OutPlane);

        public Boolean GetFrustumFarPlane(out FPlane OutPlane) =>
            MatrixImplementation.Matrix_GetFrustumFarPlaneImplementation(this, out OutPlane);

        public Boolean GetFrustumLeftPlane(out FPlane OutPlane) =>
            MatrixImplementation.Matrix_GetFrustumLeftPlaneImplementation(this, out OutPlane);

        public Boolean GetFrustumRightPlane(out FPlane OutPlane) =>
            MatrixImplementation.Matrix_GetFrustumRightPlaneImplementation(this, out OutPlane);

        public Boolean GetFrustumTopPlane(out FPlane OutPlane) =>
            MatrixImplementation.Matrix_GetFrustumTopPlaneImplementation(this, out OutPlane);

        public Boolean GetFrustumBottomPlane(out FPlane OutPlane) =>
            MatrixImplementation.Matrix_GetFrustumBottomPlaneImplementation(this, out OutPlane);

        // @TOOD
        // Mirror

        public override string ToString()
        {
            MatrixImplementation.Matrix_ToStringImplementation(this, out var OutValue);

            return OutValue.ToString();
        }

        public UInt32 ComputeHash() =>
            MatrixImplementation.Matrix_ComputeHashImplementation(this);

        // @TOOD
        // To3x4MatrixTranspose
    }
}