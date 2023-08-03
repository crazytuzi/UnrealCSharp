#include "Domain/InternalCall/FPlaneImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterPlane
{
	FRegisterPlane()
	{
		TReflectionClassBuilder<FPlane>(NAMESPACE_LIBRARY)
			.Function("IsValid", FPlaneImplementation::Plane_IsValidImplementation)
			.Function("GetOrigin", FPlaneImplementation::Plane_GetOriginImplementation)
			.Function("PlaneDot", FPlaneImplementation::Plane_PlaneDotImplementation)
			.Function("Normalize", FPlaneImplementation::Plane_NormalizeImplementation)
			.Function("Flip", FPlaneImplementation::Plane_FlipImplementation)
			.Function("TransformBy", FPlaneImplementation::Plane_TransformByImplementation)
			.Function("TransformByUsingAdjointT", FPlaneImplementation::Plane_TransformByUsingAdjointTImplementation)
			.Function("Equality", FPlaneImplementation::Plane_EqualityImplementation)
			.Function("Inequality", FPlaneImplementation::Plane_InequalityImplementation)
			.Function("Equals", FPlaneImplementation::Plane_EqualsImplementation)
			.Function("DotProduct", FPlaneImplementation::Plane_DotProductImplementation)
			.Function("DotProduct", FPlaneImplementation::Plane_DotProductImplementation)
			.Function("Add", FPlaneImplementation::Plane_AddImplementation)
			.Function("Subtract", FPlaneImplementation::Plane_SubtractImplementation)
			.Function("Divide", FPlaneImplementation::Plane_DivideImplementation)
			.Function("Multiply", FPlaneImplementation::Plane_MultiplyImplementation)
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

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Plane != nullptr && OutVector != nullptr)
	{
		*OutVector = Plane->GetOrigin();
	}
}

FPlaneImplementation::LwcType FPlaneImplementation::Plane_PlaneDotImplementation(
	const MonoObject* InMonoObject, const MonoObject* P)
{
	const auto Plane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(InMonoObject);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(P);

	if (Plane != nullptr && Vector != nullptr)
	{
		return Plane->PlaneDot(*Vector);
	}

	return 0.f;
}

bool FPlaneImplementation::Plane_NormalizeImplementation(const MonoObject* InMonoObject, const LwcType Tolerance)
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

	const auto FoundMonoClass = TPropertyClass<FPlane, FPlane>::Get();

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

	const auto FoundMonoClass = TPropertyClass<FPlane, FPlane>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(NewMonoObject);

	if (Plane != nullptr && Matrix != nullptr && OutPlane != nullptr)
	{
		*OutPlane = Plane->TransformBy(*Matrix);
	}
}

void FPlaneImplementation::Plane_TransformByUsingAdjointTImplementation(const MonoObject* InMonoObject,
                                                                        const MonoObject* M, const LwcType DetM,
                                                                        const MonoObject* TA, MonoObject** OutValue)
{
	const auto Plane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(InMonoObject);

	const auto MatrixM = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(M);

	const auto MatrixTA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(TA);

	const auto FoundMonoClass = TPropertyClass<FPlane, FPlane>::Get();

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

bool FPlaneImplementation::Plane_EqualsImplementation(const MonoObject* A, const MonoObject* B, const LwcType Tolerance)
{
	const auto PlaneA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(A);

	const auto PlaneB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(B);

	if (PlaneA != nullptr && PlaneB != nullptr)
	{
		return PlaneA->Equals(*PlaneB, Tolerance);
	}

	return false;
}

FPlaneImplementation::LwcType FPlaneImplementation::Plane_DotProductImplementation(
	const MonoObject* A, const MonoObject* B)
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

	const auto FoundMonoClass = TPropertyClass<FPlane, FPlane>::Get();

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

	const auto FoundMonoClass = TPropertyClass<FPlane, FPlane>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(NewMonoObject);

	if (PlaneA != nullptr && PlaneB != nullptr && OutPlane != nullptr)
	{
		*OutPlane = PlaneA->operator-(*PlaneB);
	}
}

void FPlaneImplementation::Plane_DivideImplementation(const MonoObject* InMonoObject, const LwcType Scale,
                                                      MonoObject** OutValue)
{
	const auto Plane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FPlane, FPlane>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(NewMonoObject);

	if (Plane != nullptr && OutPlane != nullptr)
	{
		*OutPlane = Plane->operator/(Scale);
	}
}

void FPlaneImplementation::Plane_MultiplyImplementation(const MonoObject* InMonoObject, const LwcType Scale,
                                                        MonoObject** OutValue)
{
	const auto Plane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FPlane, FPlane>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(NewMonoObject);

	if (Plane != nullptr && OutPlane != nullptr)
	{
		*OutPlane = Plane->operator*(Scale);
	}
}
