#include "Domain/InternalCall/FPlaneImplementation.h"
#include "Binding/Class/TScriptStructBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/NamespaceMacro.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"

struct FRegisterPlane
{
	FRegisterPlane()
	{
		TScriptStructBuilder<FPlane>(NAMESPACE_LIBRARY)
			.Function("IsValid", static_cast<void*>(FPlaneImplementation::Plane_IsValidImplementation))
			.Function("GetOrigin", static_cast<void*>(FPlaneImplementation::Plane_GetOriginImplementation))
			.Function("PlaneDot", static_cast<void*>(FPlaneImplementation::Plane_PlaneDotImplementation))
			.Function("Normalize", static_cast<void*>(FPlaneImplementation::Plane_NormalizeImplementation))
			.Function("Flip", static_cast<void*>(FPlaneImplementation::Plane_FlipImplementation))
			.Function("TransformBy", static_cast<void*>(FPlaneImplementation::Plane_TransformByImplementation))
			.Function("TransformByUsingAdjointT",
			          static_cast<void*>(FPlaneImplementation::Plane_TransformByUsingAdjointTImplementation))
			.Function("Equality", static_cast<void*>(FPlaneImplementation::Plane_EqualityImplementation))
			.Function("Inequality", static_cast<void*>(FPlaneImplementation::Plane_InequalityImplementation))
			.Function("Equals", static_cast<void*>(FPlaneImplementation::Plane_EqualsImplementation))
			.Function("DotProduct", static_cast<void*>(FPlaneImplementation::Plane_DotProductImplementation))
			.Function("DotProduct", static_cast<void*>(FPlaneImplementation::Plane_DotProductImplementation))
			.Function("Add", static_cast<void*>(FPlaneImplementation::Plane_AddImplementation))
			.Function("Subtract", static_cast<void*>(FPlaneImplementation::Plane_SubtractImplementation))
			.Function("Divide", static_cast<void*>(FPlaneImplementation::Plane_DivideImplementation))
			.Function("Multiply", static_cast<void*>(FPlaneImplementation::Plane_MultiplyImplementation))
			.Register();
	}
};

static FRegisterPlane RegisterPlane;

bool FPlaneImplementation::Plane_IsValidImplementation(const MonoObject* InMonoObject)
{
	const auto Plane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(InMonoObject);

	if (Plane != nullptr)
	{
		return Plane->IsValid();
	}

	return false;
}

void FPlaneImplementation::Plane_GetOriginImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Plane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector)),
		CLASS_SCRIPT_STRUCT_NAME(FVector));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Plane != nullptr && OutVector != nullptr)
	{
		*OutVector = Plane->GetOrigin();
	}
}

float FPlaneImplementation::Plane_PlaneDotImplementation(const MonoObject* InMonoObject, const MonoObject* P)
{
	const auto Plane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(P);

	if (Plane != nullptr && Vector != nullptr)
	{
		return Plane->PlaneDot(*Vector);
	}

	return 0.f;
}

bool FPlaneImplementation::Plane_NormalizeImplementation(const MonoObject* InMonoObject, const float Tolerance)
{
	const auto Plane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(InMonoObject);

	if (Plane != nullptr)
	{
		return Plane->Normalize(Tolerance);
	}

	return false;
}

void FPlaneImplementation::Plane_FlipImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Plane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FPlane)),
		CLASS_SCRIPT_STRUCT_NAME(FPlane));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(NewMonoObject);

	if (Plane != nullptr && OutPlane != nullptr)
	{
		*OutPlane = Plane->Flip();
	}
}

void FPlaneImplementation::Plane_TransformByImplementation(const MonoObject* InMonoObject, const MonoObject* M,
                                                           MonoObject** OutValue)
{
	const auto Plane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(InMonoObject);

	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(M);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FPlane)),
		CLASS_SCRIPT_STRUCT_NAME(FPlane));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(NewMonoObject);

	if (Plane != nullptr && Matrix != nullptr && OutPlane != nullptr)
	{
		*OutPlane = Plane->TransformBy(*Matrix);
	}
}

void FPlaneImplementation::Plane_TransformByUsingAdjointTImplementation(const MonoObject* InMonoObject,
                                                                        const MonoObject* M, const float DetM,
                                                                        const MonoObject* TA, MonoObject** OutValue)
{
	const auto Plane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(InMonoObject);

	const auto MatrixM = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(M);

	const auto MatrixTA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(TA);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FPlane)),
		CLASS_SCRIPT_STRUCT_NAME(FPlane));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(NewMonoObject);

	if (Plane != nullptr && MatrixM != nullptr && MatrixTA != nullptr && OutPlane != nullptr)
	{
		*OutPlane = Plane->TransformByUsingAdjointT(*MatrixM, DetM, *MatrixTA);
	}
}

bool FPlaneImplementation::Plane_EqualityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto PlaneA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(A);

	const auto PlaneB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(B);

	if (PlaneA != nullptr && PlaneB != nullptr)
	{
		return PlaneA->operator==(*PlaneB);
	}

	return false;
}

bool FPlaneImplementation::Plane_InequalityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto PlaneA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(A);

	const auto PlaneB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(B);

	if (PlaneA != nullptr && PlaneB != nullptr)
	{
		return PlaneA->operator!=(*PlaneB);
	}

	return false;
}

bool FPlaneImplementation::Plane_EqualsImplementation(const MonoObject* A, const MonoObject* B, const float Tolerance)
{
	const auto PlaneA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(A);

	const auto PlaneB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(B);

	if (PlaneA != nullptr && PlaneB != nullptr)
	{
		return PlaneA->Equals(*PlaneB, Tolerance);
	}

	return false;
}

float FPlaneImplementation::Plane_DotProductImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto PlaneA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(A);

	const auto PlaneB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(B);

	if (PlaneA != nullptr && PlaneB != nullptr)
	{
		return PlaneA->operator|(*PlaneB);
	}

	return 0.f;
}

void FPlaneImplementation::Plane_AddImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue)
{
	const auto PlaneA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(A);

	const auto PlaneB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(B);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FPlane)),
		CLASS_SCRIPT_STRUCT_NAME(FPlane));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(NewMonoObject);

	if (PlaneA != nullptr && PlaneB != nullptr && OutPlane != nullptr)
	{
		*OutPlane = PlaneA->operator+(*PlaneB);
	}
}

void FPlaneImplementation::Plane_SubtractImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue)
{
	const auto PlaneA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(A);

	const auto PlaneB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(B);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FPlane)),
		CLASS_SCRIPT_STRUCT_NAME(FPlane));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(NewMonoObject);

	if (PlaneA != nullptr && PlaneB != nullptr && OutPlane != nullptr)
	{
		*OutPlane = PlaneA->operator-(*PlaneB);
	}
}

void FPlaneImplementation::Plane_DivideImplementation(const MonoObject* InMonoObject, const float Scale,
                                                      MonoObject** OutValue)
{
	const auto Plane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FPlane)),
		CLASS_SCRIPT_STRUCT_NAME(FPlane));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(NewMonoObject);

	if (Plane != nullptr && OutPlane != nullptr)
	{
		*OutPlane = Plane->operator/(Scale);
	}
}

void FPlaneImplementation::Plane_MultiplyImplementation(const MonoObject* InMonoObject, const float Scale,
                                                        MonoObject** OutValue)
{
	const auto Plane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FPlane)),
		CLASS_SCRIPT_STRUCT_NAME(FPlane));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(NewMonoObject);

	if (Plane != nullptr && OutPlane != nullptr)
	{
		*OutPlane = Plane->operator*(Scale);
	}
}
