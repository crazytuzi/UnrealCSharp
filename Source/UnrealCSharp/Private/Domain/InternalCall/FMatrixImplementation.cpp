#include "Domain/InternalCall/FMatrixImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterMatrix
{
	FRegisterMatrix()
	{
		TReflectionClassBuilder<FMatrix>(NAMESPACE_LIBRARY)
			.Property("M", FMatrixImplementation::Matrix_GetMImplementation,
			          FMatrixImplementation::Matrix_SetMImplementation)
			.Function("SetIdentity", FMatrixImplementation::Matrix_SetIdentityImplementation)
			.Function("Multiply", FMatrixImplementation::Matrix_MultiplyImplementation)
			.Function("Add", FMatrixImplementation::Matrix_AddImplementation)
			.Function("MultiplyScale", FMatrixImplementation::Matrix_MultiplyScaleImplementation)
			.Function("Equals", FMatrixImplementation::Matrix_EqualsImplementation)
			.Function("TransformFVector4", FMatrixImplementation::Matrix_TransformFVector4Implementation)
			.Function("TransformPosition", FMatrixImplementation::Matrix_TransformPositionImplementation)
			.Function("InverseTransformPosition", FMatrixImplementation::Matrix_InverseTransformPositionImplementation)
			.Function("TransformVector", FMatrixImplementation::Matrix_TransformVectorImplementation)
			.Function("InverseTransformVector", FMatrixImplementation::Matrix_InverseTransformVectorImplementation)
			.Function("GetTransposed", FMatrixImplementation::Matrix_GetTransposedImplementation)
			.Function("Determinant", FMatrixImplementation::Matrix_DeterminantImplementation)
			.Function("RotDeterminant", FMatrixImplementation::Matrix_RotDeterminantImplementation)
			.Function("InverseFast", FMatrixImplementation::Matrix_InverseFastImplementation)
			.Function("Inverse", FMatrixImplementation::Matrix_InverseImplementation)
			.Function("TransposeAdjoint", FMatrixImplementation::Matrix_TransposeAdjointImplementation)
			.Function("RemoveScaling", FMatrixImplementation::Matrix_RemoveScalingImplementation)
			.Function("GetMatrixWithoutScale", FMatrixImplementation::Matrix_GetMatrixWithoutScaleImplementation)
			.Function("ExtractScaling", FMatrixImplementation::Matrix_ExtractScalingImplementation)
			.Function("GetScaleVector", FMatrixImplementation::Matrix_GetScaleVectorImplementation)
			.Function("RemoveTranslation", FMatrixImplementation::Matrix_RemoveTranslationImplementation)
			.Function("ConcatTranslation", FMatrixImplementation::Matrix_ConcatTranslationImplementation)
			.Function("ContainsNaN", FMatrixImplementation::Matrix_ContainsNaNImplementation)
			.Function("ScaleTranslation", FMatrixImplementation::Matrix_ScaleTranslationImplementation)
			.Function("GetMaximumAxisScale", FMatrixImplementation::Matrix_GetMaximumAxisScaleImplementation)
			.Function("ApplyScale", FMatrixImplementation::Matrix_ApplyScaleImplementation)
			.Function("GetOrigin", FMatrixImplementation::Matrix_GetOriginImplementation)
			.Function("GetScaledAxes", FMatrixImplementation::Matrix_GetScaledAxesImplementation)
			.Function("GetUnitAxes", FMatrixImplementation::Matrix_GetUnitAxesImplementation)
			.Function("SetAxis", FMatrixImplementation::Matrix_SetAxisImplementation)
			.Function("SetOrigin", FMatrixImplementation::Matrix_SetOriginImplementation)
			.Function("SetAxes", FMatrixImplementation::Matrix_SetAxesImplementation)
			.Function("GetColumn", FMatrixImplementation::Matrix_GetColumnImplementation)
			.Function("SetColumn", FMatrixImplementation::Matrix_SetColumnImplementation)
			.Function("Rotator", FMatrixImplementation::Matrix_RotatorImplementation)
			.Function("ToQuat", FMatrixImplementation::Matrix_ToQuatImplementation)
			.Function("GetFrustumNearPlane", FMatrixImplementation::Matrix_GetFrustumNearPlaneImplementation)
			.Function("GetFrustumFarPlane", FMatrixImplementation::Matrix_GetFrustumFarPlaneImplementation)
			.Function("GetFrustumLeftPlane", FMatrixImplementation::Matrix_GetFrustumLeftPlaneImplementation)
			.Function("GetFrustumRightPlane", FMatrixImplementation::Matrix_GetFrustumRightPlaneImplementation)
			.Function("GetFrustumTopPlane", FMatrixImplementation::Matrix_GetFrustumTopPlaneImplementation)
			.Function("GetFrustumBottomPlane", FMatrixImplementation::Matrix_GetFrustumBottomPlaneImplementation)
			.Function("ToString", FMatrixImplementation::Matrix_ToStringImplementation)
			.Function("ComputeHash", FMatrixImplementation::Matrix_ComputeHashImplementation)
			.Register();
	}
};

static FRegisterMatrix RegisterMatrix;

FMatrixImplementation::LwcType FMatrixImplementation::Matrix_GetMImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const uint32 InRow, const uint32 InColumn)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	if (Matrix != nullptr)
	{
		return Matrix->M[InRow][InColumn];
	}

	return 0.f;
}

void FMatrixImplementation::Matrix_SetMImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                      const uint32 InRow, const uint32 InColumn, const LwcType InValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	if (Matrix != nullptr)
	{
		Matrix->M[InRow][InColumn] = InValue;
	}
}

void FMatrixImplementation::Matrix_SetIdentityImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	if (Matrix != nullptr)
	{
		Matrix->SetIdentity();
	}
}

void FMatrixImplementation::Matrix_MultiplyImplementation(const FGarbageCollectionHandle A,
                                                          const FGarbageCollectionHandle B, MonoObject** OutValue)
{
	const auto MatrixA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(A);

	const auto MatrixB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(B);

	const auto FoundMonoClass = TPropertyClass<FMatrix, FMatrix>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = new FMatrix(MatrixA->operator*(*MatrixB));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FMatrix>::Get(), OutMatrix,
	                                                        NewMonoObject);
}

void FMatrixImplementation::Matrix_AddImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
                                                     MonoObject** OutValue)
{
	const auto MatrixA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(A);

	const auto MatrixB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(B);

	const auto FoundMonoClass = TPropertyClass<FMatrix, FMatrix>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = new FMatrix(MatrixA->operator+(*MatrixB));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FMatrix>::Get(), OutMatrix,
	                                                        NewMonoObject);
}

void FMatrixImplementation::Matrix_MultiplyScaleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                               const LwcType Other, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FMatrix, FMatrix>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = new FMatrix(Matrix->operator*(Other));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FMatrix>::Get(), OutMatrix,
	                                                        NewMonoObject);
}

bool FMatrixImplementation::Matrix_EqualsImplementation(const FGarbageCollectionHandle A,
                                                        const FGarbageCollectionHandle B, const LwcType Tolerance)
{
	const auto MatrixA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(A);

	const auto MatrixB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(B);

	if (MatrixA != nullptr && MatrixB != nullptr)
	{
		return MatrixA->Equals(*MatrixB, Tolerance);
	}

	return false;
}

void FMatrixImplementation::Matrix_TransformFVector4Implementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* V, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(V);

	const auto FoundMonoClass = TPropertyClass<FVector4, FVector4>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = new FVector4(Matrix->TransformFVector4(*Vector4));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector4>::Get(), OutVector4,
	                                                        NewMonoObject);
}

void FMatrixImplementation::Matrix_TransformPositionImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* V, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = TPropertyClass<FVector4, FVector4>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = new FVector4(Matrix->TransformPosition(*Vector));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector4>::Get(), OutVector4,
	                                                        NewMonoObject);
}

void FMatrixImplementation::Matrix_InverseTransformPositionImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* V, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Matrix->InverseTransformPosition(*Vector));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FMatrixImplementation::Matrix_TransformVectorImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* V, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = TPropertyClass<FVector4, FVector4>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = new FVector4(Matrix->TransformVector(*Vector));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector4>::Get(), OutVector4,
	                                                        NewMonoObject);
}

void FMatrixImplementation::Matrix_InverseTransformVectorImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* V, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Matrix->InverseTransformVector(*Vector));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FMatrixImplementation::Matrix_GetTransposedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                               MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FMatrix, FMatrix>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = new FMatrix(Matrix->GetTransposed());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FMatrix>::Get(), OutMatrix,
	                                                        NewMonoObject);
}

FMatrixImplementation::LwcType FMatrixImplementation::Matrix_DeterminantImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	if (Matrix != nullptr)
	{
		return Matrix->Determinant();
	}

	return 0.f;
}

FMatrixImplementation::LwcType FMatrixImplementation::Matrix_RotDeterminantImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	if (Matrix != nullptr)
	{
		return Matrix->RotDeterminant();
	}

	return 0.f;
}

void FMatrixImplementation::Matrix_InverseFastImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                             MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FMatrix, FMatrix>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = new FMatrix(Matrix->InverseFast());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FMatrix>::Get(), OutMatrix,
	                                                        NewMonoObject);
}

void FMatrixImplementation::Matrix_InverseImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                         MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FMatrix, FMatrix>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = new FMatrix(Matrix->Inverse());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FMatrix>::Get(), OutMatrix,
	                                                        NewMonoObject);
}

void FMatrixImplementation::Matrix_TransposeAdjointImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FMatrix, FMatrix>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = new FMatrix(Matrix->TransposeAdjoint());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FMatrix>::Get(), OutMatrix,
	                                                        NewMonoObject);
}

void FMatrixImplementation::Matrix_RemoveScalingImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                               const LwcType Tolerance)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	if (Matrix != nullptr)
	{
		Matrix->RemoveScaling(Tolerance);
	}
}

void FMatrixImplementation::Matrix_GetMatrixWithoutScaleImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const LwcType Tolerance, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FMatrix, FMatrix>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = new FMatrix(Matrix->GetMatrixWithoutScale(Tolerance));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FMatrix>::Get(), OutMatrix,
	                                                        NewMonoObject);
}

void FMatrixImplementation::Matrix_ExtractScalingImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const LwcType Tolerance, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Matrix->ExtractScaling(Tolerance));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FMatrixImplementation::Matrix_GetScaleVectorImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const LwcType Tolerance, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Matrix->GetScaleVector(Tolerance));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FMatrixImplementation::Matrix_RemoveTranslationImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FMatrix, FMatrix>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = new FMatrix(Matrix->RemoveTranslation());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FMatrix>::Get(), OutMatrix,
	                                                        NewMonoObject);
}

void FMatrixImplementation::Matrix_ConcatTranslationImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Translation, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Translation);

	const auto FoundMonoClass = TPropertyClass<FMatrix, FMatrix>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = new FMatrix(Matrix->ConcatTranslation(*Vector));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FMatrix>::Get(), OutMatrix,
	                                                        NewMonoObject);
}

bool FMatrixImplementation::Matrix_ContainsNaNImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	if (Matrix != nullptr)
	{
		return Matrix->ContainsNaN();
	}

	return false;
}

void FMatrixImplementation::Matrix_ScaleTranslationImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Scale3D)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Scale3D);

	if (Matrix != nullptr && Vector != nullptr)
	{
		Matrix->ScaleTranslation(*Vector);
	}
}

FMatrixImplementation::LwcType FMatrixImplementation::Matrix_GetMaximumAxisScaleImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	if (Matrix != nullptr)
	{
		return Matrix->GetMaximumAxisScale();
	}

	return 0.f;
}

void FMatrixImplementation::Matrix_ApplyScaleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                            const LwcType Scale, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FMatrix, FMatrix>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = new FMatrix(Matrix->ApplyScale(Scale));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FMatrix>::Get(), OutMatrix,
	                                                        NewMonoObject);
}

void FMatrixImplementation::Matrix_GetOriginImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                           MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Matrix->GetOrigin());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FMatrixImplementation::Matrix_GetScaledAxesImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                               MonoObject** X, MonoObject** Y, MonoObject** Z)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject1 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*X = NewMonoObject1;

	const auto NewMonoObject2 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*Y = NewMonoObject2;

	const auto NewMonoObject3 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*Z = NewMonoObject3;

	const auto OutVectorX = new FVector();

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVectorX,
	                                                        NewMonoObject1);

	const auto OutVectorY = new FVector();

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVectorY,
	                                                        NewMonoObject2);

	const auto OutVectorZ = new FVector();

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVectorZ,
	                                                        NewMonoObject3);

	Matrix->GetScaledAxes(*OutVectorX, *OutVectorY, *OutVectorZ);
}

void FMatrixImplementation::Matrix_GetUnitAxesImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                             MonoObject** X, MonoObject** Y, MonoObject** Z)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject1 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*X = NewMonoObject1;

	const auto NewMonoObject2 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*Y = NewMonoObject2;

	const auto NewMonoObject3 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*Z = NewMonoObject3;

	const auto OutVectorX = new FVector();

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVectorX,
	                                                        NewMonoObject1);

	const auto OutVectorY = new FVector();

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVectorY,
	                                                        NewMonoObject2);

	const auto OutVectorZ = new FVector();

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVectorZ,
	                                                        NewMonoObject3);

	Matrix->GetUnitAxes(*OutVectorX, *OutVectorY, *OutVectorZ);
}

void FMatrixImplementation::Matrix_SetAxisImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                         const int32 i, const MonoObject* Axis)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Axis);

	if (Matrix != nullptr && Vector != nullptr)
	{
		Matrix->SetAxis(i, *Vector);
	}
}

void FMatrixImplementation::Matrix_SetOriginImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                           const MonoObject* NewOrigin)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewOrigin);

	if (Matrix != nullptr && Vector != nullptr)
	{
		Matrix->SetOrigin(*Vector);
	}
}

void FMatrixImplementation::Matrix_SetAxesImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                         const MonoObject* Axis0, const MonoObject* Axis1,
                                                         const MonoObject* Axis2, const MonoObject* Origin)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto VectorAxis0 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Axis0);

	const auto VectorAxis1 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Axis1);

	const auto VectorAxis2 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Axis2);

	const auto VectorOrigin = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Origin);

	if (Matrix != nullptr && VectorAxis0 != nullptr && VectorAxis1 != nullptr && VectorAxis2 != nullptr && VectorOrigin
		!= nullptr)
	{
		Matrix->SetAxes(VectorAxis0, VectorAxis1, VectorAxis2, VectorOrigin);
	}
}

void FMatrixImplementation::Matrix_GetColumnImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                           const int32 i, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Matrix->GetColumn(i));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

void FMatrixImplementation::Matrix_SetColumnImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                           const int32 i, const MonoObject* Value)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Value);

	if (Matrix != nullptr && Vector != nullptr)
	{
		Matrix->SetColumn(i, *Vector);
	}
}

void FMatrixImplementation::Matrix_RotatorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                         MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FRotator, FRotator>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = new FRotator(Matrix->Rotator());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FRotator>::Get(), OutRotator,
	                                                        NewMonoObject);
}

void FMatrixImplementation::Matrix_ToQuatImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                        MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = new FQuat(Matrix->ToQuat());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FQuat>::Get(), OutQuat,
	                                                        NewMonoObject);
}

bool FMatrixImplementation::Matrix_GetFrustumNearPlaneImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FPlane, FPlane>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = new FPlane();

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FPlane>::Get(), OutPlane,
	                                                        NewMonoObject);

	return Matrix->GetFrustumNearPlane(*OutPlane);
}

bool FMatrixImplementation::Matrix_GetFrustumFarPlaneImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FPlane, FPlane>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = new FPlane();

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FPlane>::Get(), OutPlane,
	                                                        NewMonoObject);

	return Matrix->GetFrustumFarPlane(*OutPlane);
}

bool FMatrixImplementation::Matrix_GetFrustumLeftPlaneImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FPlane, FPlane>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = new FPlane();

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FPlane>::Get(), OutPlane,
	                                                        NewMonoObject);

	return Matrix->GetFrustumLeftPlane(*OutPlane);
}

bool FMatrixImplementation::Matrix_GetFrustumRightPlaneImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FPlane, FPlane>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = new FPlane();

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FPlane>::Get(), OutPlane,
	                                                        NewMonoObject);

	return Matrix->GetFrustumRightPlane(*OutPlane);
}

bool FMatrixImplementation::Matrix_GetFrustumTopPlaneImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FPlane, FPlane>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = new FPlane();

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FPlane>::Get(), OutPlane,
	                                                        NewMonoObject);

	return Matrix->GetFrustumTopPlane(*OutPlane);
}

bool FMatrixImplementation::Matrix_GetFrustumBottomPlaneImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FPlane, FPlane>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = new FPlane();

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FPlane>::Get(), OutPlane,
	                                                        NewMonoObject);

	return Matrix->GetFrustumBottomPlane(*OutPlane);
}

void FMatrixImplementation::Matrix_ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                          MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	if (Matrix != nullptr)
	{
		const auto ResultString = Matrix->ToString();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Init(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

uint32 FMatrixImplementation::Matrix_ComputeHashImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(
		InGarbageCollectionHandle);

	if (Matrix != nullptr)
	{
		return Matrix->ComputeHash();
	}

	return 0u;
}
