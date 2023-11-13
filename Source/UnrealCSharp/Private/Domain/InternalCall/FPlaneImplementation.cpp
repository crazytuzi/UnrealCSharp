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

bool FPlaneImplementation::Plane_IsValidImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Plane = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPlane>(InGarbageCollectionHandle);

	if (Plane != nullptr)
	{
		return Plane->IsValid();
	}

	return false;
}

void FPlaneImplementation::Plane_GetOriginImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                         MonoObject** OutValue)
{
	const auto Plane = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPlane>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = new FVector(Plane->GetOrigin());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector>::Get(), OutVector,
	                                                        NewMonoObject);
}

FPlaneImplementation::LwcType FPlaneImplementation::Plane_PlaneDotImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* P)
{
	const auto Plane = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPlane>(InGarbageCollectionHandle);

	const auto Vector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(P);

	if (Plane != nullptr && Vector != nullptr)
	{
		return Plane->PlaneDot(*Vector);
	}

	return 0.f;
}

bool FPlaneImplementation::Plane_NormalizeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                         const LwcType Tolerance)
{
	const auto Plane = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPlane>(InGarbageCollectionHandle);

	if (Plane != nullptr)
	{
		return Plane->Normalize(Tolerance);
	}

	return false;
}

void FPlaneImplementation::Plane_FlipImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                    MonoObject** OutValue)
{
	const auto Plane = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPlane>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FPlane, FPlane>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = new FPlane(Plane->Flip());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FPlane>::Get(), OutPlane,
	                                                        NewMonoObject);
}

void FPlaneImplementation::Plane_TransformByImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                           const MonoObject* M, MonoObject** OutValue)
{
	const auto Plane = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPlane>(InGarbageCollectionHandle);

	const auto Matrix = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(M);

	const auto FoundMonoClass = TPropertyClass<FPlane, FPlane>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = new FPlane(Plane->TransformBy(*Matrix));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FPlane>::Get(), OutPlane,
	                                                        NewMonoObject);
}

void FPlaneImplementation::Plane_TransformByUsingAdjointTImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* M, const LwcType DetM,
	const MonoObject* TA, MonoObject** OutValue)
{
	const auto Plane = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPlane>(InGarbageCollectionHandle);

	const auto MatrixM = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(M);

	const auto MatrixTA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FMatrix>(TA);

	const auto FoundMonoClass = TPropertyClass<FPlane, FPlane>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = new FPlane(Plane->TransformByUsingAdjointT(*MatrixM, DetM, *MatrixTA));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FPlane>::Get(), OutPlane,
	                                                        NewMonoObject);
}

bool FPlaneImplementation::Plane_EqualsImplementation(const FGarbageCollectionHandle A,
                                                      const FGarbageCollectionHandle B, const LwcType Tolerance)
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
	const FGarbageCollectionHandle A, const FGarbageCollectionHandle B)
{
	const auto PlaneA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(A);

	const auto PlaneB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(B);

	if (PlaneA != nullptr && PlaneB != nullptr)
	{
		return PlaneA->operator|(*PlaneB);
	}

	return 0.f;
}

void FPlaneImplementation::Plane_AddImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
                                                   MonoObject** OutValue)
{
	const auto PlaneA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(A);

	const auto PlaneB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(B);

	const auto FoundMonoClass = TPropertyClass<FPlane, FPlane>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = new FPlane(PlaneA->operator+(*PlaneB));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FPlane>::Get(), OutPlane,
	                                                        NewMonoObject);
}

void FPlaneImplementation::Plane_SubtractImplementation(const FGarbageCollectionHandle A,
                                                        const FGarbageCollectionHandle B, MonoObject** OutValue)
{
	const auto PlaneA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(A);

	const auto PlaneB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FPlane>(B);

	const auto FoundMonoClass = TPropertyClass<FPlane, FPlane>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = new FPlane(PlaneA->operator-(*PlaneB));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FPlane>::Get(), OutPlane,
	                                                        NewMonoObject);
}

void FPlaneImplementation::Plane_DivideImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                      const LwcType Scale, MonoObject** OutValue)
{
	const auto Plane = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPlane>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FPlane, FPlane>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = new FPlane(Plane->operator/(Scale));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FPlane>::Get(), OutPlane,
	                                                        NewMonoObject);
}

void FPlaneImplementation::Plane_MultiplyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                        const LwcType Scale, MonoObject** OutValue)
{
	const auto Plane = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FPlane>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FPlane, FPlane>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutPlane = new FPlane(Plane->operator*(Scale));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FPlane>::Get(), OutPlane,
	                                                        NewMonoObject);
}
