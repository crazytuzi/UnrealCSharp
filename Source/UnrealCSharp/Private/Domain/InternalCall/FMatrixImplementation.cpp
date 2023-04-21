#include "Domain/InternalCall/FMatrixImplementation.h"
#include "Binding/Class/TScriptStructBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/NamespaceMacro.h"
#include "FUnrealCSharpFunctionLibrary.h"

struct FRegisterMatrix
{
	FRegisterMatrix()
	{
		TScriptStructBuilder<FMatrix>(NAMESPACE_LIBRARY)
			.Property("M", static_cast<void*>(FMatrixImplementation::Matrix_GetMImplementation),
			          static_cast<void*>(FMatrixImplementation::Matrix_SetMImplementation))
			.Function("SetIdentity", static_cast<void*>(FMatrixImplementation::Matrix_SetIdentityImplementation))
			.Function("Multiply", static_cast<void*>(FMatrixImplementation::Matrix_MultiplyImplementation))
			.Function("Add", static_cast<void*>(FMatrixImplementation::Matrix_AddImplementation))
			.Function("MultiplyScale", static_cast<void*>(FMatrixImplementation::Matrix_MultiplyScaleImplementation))
			.Function("Equality", static_cast<void*>(FMatrixImplementation::Matrix_EqualityImplementation))
			.Function("Equals", static_cast<void*>(FMatrixImplementation::Matrix_EqualsImplementation))
			.Function("Inequality", static_cast<void*>(FMatrixImplementation::Matrix_InequalityImplementation))
			.Function("TransformFVector4",
			          static_cast<void*>(FMatrixImplementation::Matrix_TransformFVector4Implementation))
			.Function("TransformPosition",
			          static_cast<void*>(FMatrixImplementation::Matrix_TransformPositionImplementation))
			.Function("InverseTransformPosition",
			          static_cast<void*>(FMatrixImplementation::Matrix_InverseTransformPositionImplementation))
			.Function("TransformVector",
			          static_cast<void*>(FMatrixImplementation::Matrix_TransformVectorImplementation))
			.Function("InverseTransformVector",
			          static_cast<void*>(FMatrixImplementation::Matrix_InverseTransformVectorImplementation))
			.Function("GetTransposed", static_cast<void*>(FMatrixImplementation::Matrix_GetTransposedImplementation))
			.Function("Determinant", static_cast<void*>(FMatrixImplementation::Matrix_DeterminantImplementation))
			.Function("RotDeterminant", static_cast<void*>(FMatrixImplementation::Matrix_RotDeterminantImplementation))
			.Function("InverseFast", static_cast<void*>(FMatrixImplementation::Matrix_InverseFastImplementation))
			.Function("Inverse", static_cast<void*>(FMatrixImplementation::Matrix_InverseImplementation))
			.Function("TransposeAdjoint",
			          static_cast<void*>(FMatrixImplementation::Matrix_TransposeAdjointImplementation))
			.Function("RemoveScaling", static_cast<void*>(FMatrixImplementation::Matrix_RemoveScalingImplementation))
			.Function("GetMatrixWithoutScale",
			          static_cast<void*>(FMatrixImplementation::Matrix_GetMatrixWithoutScaleImplementation))
			.Function("ExtractScaling", static_cast<void*>(FMatrixImplementation::Matrix_ExtractScalingImplementation))
			.Function("GetScaleVector", static_cast<void*>(FMatrixImplementation::Matrix_GetScaleVectorImplementation))
			.Function("RemoveTranslation",
			          static_cast<void*>(FMatrixImplementation::Matrix_RemoveTranslationImplementation))
			.Function("ConcatTranslation",
			          static_cast<void*>(FMatrixImplementation::Matrix_ConcatTranslationImplementation))
			.Function("ContainsNaN", static_cast<void*>(FMatrixImplementation::Matrix_ContainsNaNImplementation))
			.Function("ScaleTranslation",
			          static_cast<void*>(FMatrixImplementation::Matrix_ScaleTranslationImplementation))
			.Function("GetMaximumAxisScale",
			          static_cast<void*>(FMatrixImplementation::Matrix_GetMaximumAxisScaleImplementation))
			.Function("ApplyScale", static_cast<void*>(FMatrixImplementation::Matrix_ApplyScaleImplementation))
			.Function("GetOrigin", static_cast<void*>(FMatrixImplementation::Matrix_GetOriginImplementation))
			.Function("GetScaledAxes", static_cast<void*>(FMatrixImplementation::Matrix_GetScaledAxesImplementation))
			.Function("GetUnitAxes", static_cast<void*>(FMatrixImplementation::Matrix_GetUnitAxesImplementation))
			.Function("SetAxis", static_cast<void*>(FMatrixImplementation::Matrix_SetAxisImplementation))
			.Function("SetOrigin", static_cast<void*>(FMatrixImplementation::Matrix_SetOriginImplementation))
			.Function("SetAxes", static_cast<void*>(FMatrixImplementation::Matrix_SetAxesImplementation))
			.Function("GetColumn", static_cast<void*>(FMatrixImplementation::Matrix_GetColumnImplementation))
			.Function("SetColumn", static_cast<void*>(FMatrixImplementation::Matrix_SetColumnImplementation))
			.Function("Rotator", static_cast<void*>(FMatrixImplementation::Matrix_RotatorImplementation))
			.Function("ToQuat", static_cast<void*>(FMatrixImplementation::Matrix_ToQuatImplementation))
			.Function("GetFrustumNearPlane",
			          static_cast<void*>(FMatrixImplementation::Matrix_GetFrustumNearPlaneImplementation))
			.Function("GetFrustumFarPlane",
			          static_cast<void*>(FMatrixImplementation::Matrix_GetFrustumFarPlaneImplementation))
			.Function("GetFrustumLeftPlane",
			          static_cast<void*>(FMatrixImplementation::Matrix_GetFrustumLeftPlaneImplementation))
			.Function("GetFrustumRightPlane",
			          static_cast<void*>(FMatrixImplementation::Matrix_GetFrustumRightPlaneImplementation))
			.Function("GetFrustumTopPlane",
			          static_cast<void*>(FMatrixImplementation::Matrix_GetFrustumTopPlaneImplementation))
			.Function("GetFrustumBottomPlane",
			          static_cast<void*>(FMatrixImplementation::Matrix_GetFrustumBottomPlaneImplementation))
			.Function("ToString", static_cast<void*>(FMatrixImplementation::Matrix_ToStringImplementation))
			.Function("ComputeHash", static_cast<void*>(FMatrixImplementation::Matrix_ComputeHashImplementation))
			.Register();
	}
};

static FRegisterMatrix RegisterMatrix;

float FMatrixImplementation::Matrix_GetMImplementation(const MonoObject* InMonoObject, const uint32 InRow,
                                                       const uint32 InColumn)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	if (Matrix != nullptr)
	{
		return Matrix->M[InRow][InColumn];
	}

	return 0.f;
}

void FMatrixImplementation::Matrix_SetMImplementation(const MonoObject* InMonoObject, const uint32 InRow,
                                                      const uint32 InColumn, const float InValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	if (Matrix != nullptr)
	{
		Matrix->M[InRow][InColumn] = InValue;
	}
}

void FMatrixImplementation::Matrix_SetIdentityImplementation(const MonoObject* InMonoObject)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	if (Matrix != nullptr)
	{
		Matrix->SetIdentity();
	}
}

void FMatrixImplementation::Matrix_MultiplyImplementation(const MonoObject* A, const MonoObject* B,
                                                          MonoObject** OutValue)
{
	const auto MatrixA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(A);

	const auto MatrixB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(B);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FMatrix)),
		CLASS_SCRIPT_STRUCT_NAME(FMatrix));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(NewMonoObject);

	if (MatrixA != nullptr && MatrixB != nullptr && OutMatrix != nullptr)
	{
		*OutMatrix = MatrixA->operator*(*MatrixB);
	}
}

void FMatrixImplementation::Matrix_AddImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue)
{
	const auto MatrixA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(A);

	const auto MatrixB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(B);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FMatrix)),
		CLASS_SCRIPT_STRUCT_NAME(FMatrix));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(NewMonoObject);

	if (MatrixA != nullptr && MatrixB != nullptr && OutMatrix != nullptr)
	{
		*OutMatrix = MatrixA->operator+(*MatrixB);
	}
}

void FMatrixImplementation::Matrix_MultiplyScaleImplementation(const MonoObject* InMonoObject, const float Other,
                                                               MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FMatrix)),
		CLASS_SCRIPT_STRUCT_NAME(FMatrix));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(NewMonoObject);

	if (Matrix != nullptr && OutMatrix != nullptr)
	{
		*OutMatrix = Matrix->operator*(Other);
	}
}

bool FMatrixImplementation::Matrix_EqualityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto MatrixA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(A);

	const auto MatrixB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(B);

	if (MatrixA != nullptr && MatrixB != nullptr)
	{
		return MatrixA->operator==(*MatrixB);
	}

	return false;
}

bool FMatrixImplementation::Matrix_EqualsImplementation(const MonoObject* A, const MonoObject* B, const float Tolerance)
{
	const auto MatrixA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(A);

	const auto MatrixB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(B);

	if (MatrixA != nullptr && MatrixB != nullptr)
	{
		return MatrixA->Equals(*MatrixB, Tolerance);
	}

	return false;
}

bool FMatrixImplementation::Matrix_InequalityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto MatrixA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(A);

	const auto MatrixB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(B);

	if (MatrixA != nullptr && MatrixB != nullptr)
	{
		return MatrixA->operator!=(*MatrixB);
	}

	return false;
}

void FMatrixImplementation::Matrix_TransformFVector4Implementation(const MonoObject* InMonoObject, const MonoObject* V,
                                                                   MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(V);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector4)),
		CLASS_SCRIPT_STRUCT_NAME(FVector4));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(NewMonoObject);

	if (Matrix != nullptr && Vector4 != nullptr && OutVector4 != nullptr)
	{
		*OutVector4 = Matrix->TransformFVector4(*Vector4);
	}
}

void FMatrixImplementation::Matrix_TransformPositionImplementation(const MonoObject* InMonoObject, const MonoObject* V,
                                                                   MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector4)),
		CLASS_SCRIPT_STRUCT_NAME(FVector4));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(NewMonoObject);

	if (Matrix != nullptr && Vector != nullptr && OutVector4 != nullptr)
	{
		*OutVector4 = Matrix->TransformPosition(*Vector);
	}
}

void FMatrixImplementation::Matrix_InverseTransformPositionImplementation(
	const MonoObject* InMonoObject, const MonoObject* V, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Matrix != nullptr && Vector != nullptr && OutVector != nullptr)
	{
		*OutVector = Matrix->InverseTransformPosition(*Vector);
	}
}

void FMatrixImplementation::Matrix_TransformVectorImplementation(const MonoObject* InMonoObject, const MonoObject* V,
                                                                 MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector4)),
		CLASS_SCRIPT_STRUCT_NAME(FVector4));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(NewMonoObject);

	if (Matrix != nullptr && Vector != nullptr && OutVector4 != nullptr)
	{
		*OutVector4 = Matrix->TransformVector(*Vector);
	}
}

void FMatrixImplementation::Matrix_InverseTransformVectorImplementation(const MonoObject* InMonoObject,
                                                                        const MonoObject* V, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(V);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Matrix != nullptr && Vector != nullptr && OutVector != nullptr)
	{
		*OutVector = Matrix->InverseTransformVector(*Vector);
	}
}

void FMatrixImplementation::Matrix_GetTransposedImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FMatrix)),
		CLASS_SCRIPT_STRUCT_NAME(FMatrix));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(NewMonoObject);

	if (Matrix != nullptr && OutMatrix != nullptr)
	{
		*OutMatrix = Matrix->GetTransposed();
	}
}

float FMatrixImplementation::Matrix_DeterminantImplementation(const MonoObject* InMonoObject)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	if (Matrix != nullptr)
	{
		return Matrix->Determinant();
	}

	return 0.f;
}

float FMatrixImplementation::Matrix_RotDeterminantImplementation(const MonoObject* InMonoObject)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	if (Matrix != nullptr)
	{
		return Matrix->RotDeterminant();
	}

	return 0.f;
}

void FMatrixImplementation::Matrix_InverseFastImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FMatrix)),
		CLASS_SCRIPT_STRUCT_NAME(FMatrix));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(NewMonoObject);

	if (Matrix != nullptr && OutMatrix != nullptr)
	{
		*OutMatrix = Matrix->InverseFast();
	}
}

void FMatrixImplementation::Matrix_InverseImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FMatrix)),
		CLASS_SCRIPT_STRUCT_NAME(FMatrix));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(NewMonoObject);

	if (Matrix != nullptr && OutMatrix != nullptr)
	{
		*OutMatrix = Matrix->Inverse();
	}
}

void FMatrixImplementation::Matrix_TransposeAdjointImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FMatrix)),
		CLASS_SCRIPT_STRUCT_NAME(FMatrix));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(NewMonoObject);

	if (Matrix != nullptr && OutMatrix != nullptr)
	{
		*OutMatrix = Matrix->TransposeAdjoint();
	}
}

void FMatrixImplementation::Matrix_RemoveScalingImplementation(const MonoObject* InMonoObject, const float Tolerance)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	if (Matrix != nullptr)
	{
		Matrix->RemoveScaling(Tolerance);
	}
}

void FMatrixImplementation::Matrix_GetMatrixWithoutScaleImplementation(const MonoObject* InMonoObject,
                                                                       const float Tolerance, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FMatrix)),
		CLASS_SCRIPT_STRUCT_NAME(FMatrix));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(NewMonoObject);

	if (Matrix != nullptr && OutMatrix != nullptr)
	{
		*OutMatrix = Matrix->GetMatrixWithoutScale(Tolerance);
	}
}

void FMatrixImplementation::Matrix_ExtractScalingImplementation(const MonoObject* InMonoObject, const float Tolerance,
                                                                MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Matrix != nullptr && OutVector != nullptr)
	{
		*OutVector = Matrix->ExtractScaling(Tolerance);
	}
}

void FMatrixImplementation::Matrix_GetScaleVectorImplementation(const MonoObject* InMonoObject, const float Tolerance,
                                                                MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Matrix != nullptr && OutVector != nullptr)
	{
		*OutVector = Matrix->GetScaleVector(Tolerance);
	}
}

void FMatrixImplementation::Matrix_RemoveTranslationImplementation(const MonoObject* InMonoObject,
                                                                   MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FMatrix)),
		CLASS_SCRIPT_STRUCT_NAME(FMatrix));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(NewMonoObject);

	if (Matrix != nullptr && OutMatrix != nullptr)
	{
		*OutMatrix = Matrix->RemoveTranslation();
	}
}

void FMatrixImplementation::Matrix_ConcatTranslationImplementation(const MonoObject* InMonoObject,
                                                                   const MonoObject* Translation, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Translation);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FMatrix)),
		CLASS_SCRIPT_STRUCT_NAME(FMatrix));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(NewMonoObject);

	if (Matrix != nullptr && Vector != nullptr && OutMatrix != nullptr)
	{
		*OutMatrix = Matrix->ConcatTranslation(*Vector);
	}
}

bool FMatrixImplementation::Matrix_ContainsNaNImplementation(const MonoObject* InMonoObject)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	if (Matrix != nullptr)
	{
		return Matrix->ContainsNaN();
	}

	return false;
}

void FMatrixImplementation::Matrix_ScaleTranslationImplementation(const MonoObject* InMonoObject,
                                                                  const MonoObject* Scale3D)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Scale3D);

	if (Matrix != nullptr && Vector != nullptr)
	{
		Matrix->ScaleTranslation(*Vector);
	}
}

float FMatrixImplementation::Matrix_GetMaximumAxisScaleImplementation(const MonoObject* InMonoObject)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	if (Matrix != nullptr)
	{
		return Matrix->GetMaximumAxisScale();
	}

	return 0.f;
}

void FMatrixImplementation::Matrix_ApplyScaleImplementation(const MonoObject* InMonoObject, const float Scale,
                                                            MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FMatrix)),
		CLASS_SCRIPT_STRUCT_NAME(FMatrix));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutMatrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(NewMonoObject);

	if (Matrix != nullptr && OutMatrix != nullptr)
	{
		*OutMatrix = Matrix->ApplyScale(Scale);
	}
}

void FMatrixImplementation::Matrix_GetOriginImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Matrix != nullptr && OutVector != nullptr)
	{
		*OutVector = Matrix->GetOrigin();
	}
}

void FMatrixImplementation::Matrix_GetScaledAxesImplementation(const MonoObject* InMonoObject, MonoObject** X,
                                                               MonoObject** Y, MonoObject** Z)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject1 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*X = NewMonoObject1;

	const auto NewMonoObject2 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*Y = NewMonoObject2;

	const auto NewMonoObject3 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*Z = NewMonoObject3;

	const auto OutVectorX = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject1);

	const auto OutVectorY = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject2);

	const auto OutVectorZ = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject3);

	if (Matrix != nullptr && OutVectorX != nullptr && OutVectorY != nullptr && OutVectorZ != nullptr)
	{
		Matrix->GetScaledAxes(*OutVectorX, *OutVectorY, *OutVectorZ);
	}
}

void FMatrixImplementation::Matrix_GetUnitAxesImplementation(const MonoObject* InMonoObject, MonoObject** X,
                                                             MonoObject** Y, MonoObject** Z)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject1 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*X = NewMonoObject1;

	const auto NewMonoObject2 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*Y = NewMonoObject2;

	const auto NewMonoObject3 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*Z = NewMonoObject3;

	const auto OutVectorX = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject1);

	const auto OutVectorY = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject2);

	const auto OutVectorZ = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject3);

	if (Matrix != nullptr && OutVectorX != nullptr && OutVectorY != nullptr && OutVectorZ != nullptr)
	{
		Matrix->GetUnitAxes(*OutVectorX, *OutVectorY, *OutVectorZ);
	}
}

void FMatrixImplementation::Matrix_SetAxisImplementation(const MonoObject* InMonoObject, const int32 i,
                                                         const MonoObject* Axis)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Axis);

	if (Matrix != nullptr && Vector != nullptr)
	{
		Matrix->SetAxis(i, *Vector);
	}
}

void FMatrixImplementation::Matrix_SetOriginImplementation(const MonoObject* InMonoObject, const MonoObject* NewOrigin)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewOrigin);

	if (Matrix != nullptr && Vector != nullptr)
	{
		Matrix->SetOrigin(*Vector);
	}
}

void FMatrixImplementation::Matrix_SetAxesImplementation(const MonoObject* InMonoObject, const MonoObject* Axis0,
                                                         const MonoObject* Axis1, const MonoObject* Axis2,
                                                         const MonoObject* Origin)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

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

void FMatrixImplementation::Matrix_GetColumnImplementation(const MonoObject* InMonoObject, const int32 i,
                                                           MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Matrix != nullptr && OutVector != nullptr)
	{
		*OutVector = Matrix->GetColumn(i);
	}
}

void FMatrixImplementation::Matrix_SetColumnImplementation(const MonoObject* InMonoObject, const int32 i,
                                                           const MonoObject* Value)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(Value);

	if (Matrix != nullptr && Vector != nullptr)
	{
		Matrix->SetColumn(i, *Vector);
	}
}

void FMatrixImplementation::Matrix_RotatorImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FRotator)),
		CLASS_SCRIPT_STRUCT_NAME(FRotator));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Matrix != nullptr && OutRotator != nullptr)
	{
		*OutRotator = Matrix->Rotator();
	}
}

void FMatrixImplementation::Matrix_ToQuatImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FQuat)),
		CLASS_SCRIPT_STRUCT_NAME(FQuat));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (Matrix != nullptr && OutQuat != nullptr)
	{
		*OutQuat = Matrix->ToQuat();
	}
}

bool FMatrixImplementation::Matrix_GetFrustumNearPlaneImplementation(const MonoObject* InMonoObject,
                                                                     MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FPlane)),
		CLASS_SCRIPT_STRUCT_NAME(FPlane));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(NewMonoObject);

	if (Matrix != nullptr && OutPlane != nullptr)
	{
		return Matrix->GetFrustumNearPlane(*OutPlane);
	}

	return false;
}

bool FMatrixImplementation::Matrix_GetFrustumFarPlaneImplementation(const MonoObject* InMonoObject,
                                                                    MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FPlane)),
		CLASS_SCRIPT_STRUCT_NAME(FPlane));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(NewMonoObject);

	if (Matrix != nullptr && OutPlane != nullptr)
	{
		return Matrix->GetFrustumFarPlane(*OutPlane);
	}

	return false;
}

bool FMatrixImplementation::Matrix_GetFrustumLeftPlaneImplementation(const MonoObject* InMonoObject,
                                                                     MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FPlane)),
		CLASS_SCRIPT_STRUCT_NAME(FPlane));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(NewMonoObject);

	if (Matrix != nullptr && OutPlane != nullptr)
	{
		return Matrix->GetFrustumLeftPlane(*OutPlane);
	}

	return false;
}

bool FMatrixImplementation::Matrix_GetFrustumRightPlaneImplementation(const MonoObject* InMonoObject,
                                                                      MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FPlane)),
		CLASS_SCRIPT_STRUCT_NAME(FPlane));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(NewMonoObject);

	if (Matrix != nullptr && OutPlane != nullptr)
	{
		return Matrix->GetFrustumRightPlane(*OutPlane);
	}

	return false;
}

bool FMatrixImplementation::Matrix_GetFrustumTopPlaneImplementation(const MonoObject* InMonoObject,
                                                                    MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FPlane)),
		CLASS_SCRIPT_STRUCT_NAME(FPlane));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(NewMonoObject);

	if (Matrix != nullptr && OutPlane != nullptr)
	{
		return Matrix->GetFrustumTopPlane(*OutPlane);
	}

	return false;
}

bool FMatrixImplementation::Matrix_GetFrustumBottomPlaneImplementation(const MonoObject* InMonoObject,
                                                                       MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FPlane)),
		CLASS_SCRIPT_STRUCT_NAME(FPlane));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(NewMonoObject);

	if (Matrix != nullptr && OutPlane != nullptr)
	{
		return Matrix->GetFrustumBottomPlane(*OutPlane);
	}

	return false;
}

void FMatrixImplementation::Matrix_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	if (Matrix != nullptr)
	{
		const auto ResultString = Matrix->ToString();

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

uint32 FMatrixImplementation::Matrix_ComputeHashImplementation(const MonoObject* InMonoObject)
{
	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(InMonoObject);

	if (Matrix != nullptr)
	{
		return Matrix->ComputeHash();
	}

	return 0u;
}
