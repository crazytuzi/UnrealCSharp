#include "Domain/InternalCall/FVector2DImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterVector2D
{
	FRegisterVector2D()
	{
		TReflectionClassBuilder<FVector2D>(NAMESPACE_LIBRARY)
			.Function("Add", FVector2DImplementation::Vector2D_AddImplementation)
			.Function("Subtract", FVector2DImplementation::Vector2D_SubtractImplementation)
			.Function("MultiplyScale", FVector2DImplementation::Vector2D_MultiplyScaleImplementation)
			.Function("DivideScale", FVector2DImplementation::Vector2D_DivideScaleImplementation)
			.Function("AddA", FVector2DImplementation::Vector2D_AddAImplementation)
			.Function("SubtractA", FVector2DImplementation::Vector2D_SubtractAImplementation)
			.Function("Multiply", FVector2DImplementation::Vector2D_MultiplyImplementation)
			.Function("Divide", FVector2DImplementation::Vector2D_DivideImplementation)
			.Function("DotProduct", FVector2DImplementation::Vector2D_DotProductImplementation)
			.Function("CrossProduct", FVector2DImplementation::Vector2D_CrossProductImplementation)
			.Function("Equality", FVector2DImplementation::Vector2D_EqualityImplementation)
			.Function("Inequality", FVector2DImplementation::Vector2D_InequalityImplementation)
			.Function("LessThan", FVector2DImplementation::Vector2D_LessThanImplementation)
			.Function("GreaterThan", FVector2DImplementation::Vector2D_GreaterThanImplementation)
			.Function("LessThanOrEqual", FVector2DImplementation::Vector2D_LessThanOrEqualImplementation)
			.Function("GreaterThanOrEqual", FVector2DImplementation::Vector2D_GreaterThanOrEqualImplementation)
			.Function("Negated", FVector2DImplementation::Vector2D_NegatedImplementation)
			.Function("GetComponent", FVector2DImplementation::Vector2D_GetComponentImplementation)
			.Function("SetComponent", FVector2DImplementation::Vector2D_SetComponentImplementation)
			.Function("Component", FVector2DImplementation::Vector2D_ComponentImplementation)
			.Function("DistSquared", FVector2DImplementation::Vector2D_DistSquaredImplementation)
			.Function("Distance", FVector2DImplementation::Vector2D_DistanceImplementation)
			.Function("Max", FVector2DImplementation::Vector2D_MaxImplementation)
			.Function("Min", FVector2DImplementation::Vector2D_MinImplementation)
			.Function("Equals", FVector2DImplementation::Vector2D_EqualsImplementation)
			.Function("Set", FVector2DImplementation::Vector2D_SetImplementation)
			.Function("GetMax", FVector2DImplementation::Vector2D_GetMaxImplementation)
			.Function("GetAbsMax", FVector2DImplementation::Vector2D_GetAbsMaxImplementation)
			.Function("GetMin", FVector2DImplementation::Vector2D_GetMinImplementation)
			.Function("Size", FVector2DImplementation::Vector2D_SizeImplementation)
			.Function("SizeSquared", FVector2DImplementation::Vector2D_SizeSquaredImplementation)
			.Function("GetRotated", FVector2DImplementation::Vector2D_GetRotatedImplementation)
			.Function("GetSafeNormal", FVector2DImplementation::Vector2D_GetSafeNormalImplementation)
			.Function("Normalize", FVector2DImplementation::Vector2D_NormalizeImplementation)
			.Function("IsNearlyZero", FVector2DImplementation::Vector2D_IsNearlyZeroImplementation)
			.Function("IntPoint", FVector2DImplementation::Vector2D_IntPointImplementation)
			.Function("RoundToVector", FVector2DImplementation::Vector2D_RoundToVectorImplementation)
			.Function("ClampAxes", FVector2DImplementation::Vector2D_ClampAxesImplementation)
			.Function("GetSignVector", FVector2DImplementation::Vector2D_GetSignVectorImplementation)
			.Function("GetAbs", FVector2DImplementation::Vector2D_GetAbsImplementation)
			.Function("ToString", FVector2DImplementation::Vector2D_ToStringImplementation)
			.Function("InitFromString", FVector2DImplementation::Vector2D_InitFromStringImplementation)
			.Function("ContainsNaN", FVector2DImplementation::Vector2D_ContainsNaNImplementation)
			.Register();
	}
};

static FRegisterVector2D RegisterVector2D;

void FVector2DImplementation::Vector2D_AddImplementation(const MonoObject* A, const MonoObject* B,
                                                         MonoObject** OutValue)
{
	const auto Vector2DA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(A);

	const auto Vector2DB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(B);

	const auto FoundMonoClass = TPropertyClass<FVector2D, FVector2D>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(NewMonoObject);

	if (Vector2DA != nullptr && Vector2DB != nullptr && OutVector2D != nullptr)
	{
		*OutVector2D = Vector2DA->operator+(*Vector2DB);
	}
}

void FVector2DImplementation::Vector2D_SubtractImplementation(const MonoObject* A, const MonoObject* B,
                                                              MonoObject** OutValue)
{
	const auto Vector2DA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(A);

	const auto Vector2DB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(B);

	const auto FoundMonoClass = TPropertyClass<FVector2D, FVector2D>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(NewMonoObject);

	if (Vector2DA != nullptr && Vector2DB != nullptr && OutVector2D != nullptr)
	{
		*OutVector2D = Vector2DA->operator-(*Vector2DB);
	}
}

void FVector2DImplementation::Vector2D_MultiplyScaleImplementation(const MonoObject* InMonoObject, const LwcType Scale,
                                                                   MonoObject** OutValue)
{
	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FVector2D, FVector2D>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(NewMonoObject);

	if (Vector2D != nullptr && OutVector2D != nullptr)
	{
		*OutVector2D = Vector2D->operator*(Scale);
	}
}

void FVector2DImplementation::Vector2D_DivideScaleImplementation(const MonoObject* InMonoObject, const LwcType Scale,
                                                                 MonoObject** OutValue)
{
	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FVector2D, FVector2D>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(NewMonoObject);

	if (Vector2D != nullptr && OutVector2D != nullptr)
	{
		*OutVector2D = Vector2D->operator/(Scale);
	}
}

void FVector2DImplementation::Vector2D_AddAImplementation(const MonoObject* InMonoObject, const LwcType A,
                                                          MonoObject** OutValue)
{
	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FVector2D, FVector2D>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(NewMonoObject);

	if (Vector2D != nullptr && OutVector2D != nullptr)
	{
		*OutVector2D = Vector2D->operator+(A);
	}
}

void FVector2DImplementation::Vector2D_SubtractAImplementation(const MonoObject* InMonoObject, const LwcType A,
                                                               MonoObject** OutValue)
{
	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FVector2D, FVector2D>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(NewMonoObject);

	if (Vector2D != nullptr && OutVector2D != nullptr)
	{
		*OutVector2D = Vector2D->operator-(A);
	}
}

void FVector2DImplementation::Vector2D_MultiplyImplementation(const MonoObject* A, const MonoObject* B,
                                                              MonoObject** OutValue)
{
	const auto Vector2DA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(A);

	const auto Vector2DB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(B);

	const auto FoundMonoClass = TPropertyClass<FVector2D, FVector2D>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(NewMonoObject);

	if (Vector2DA != nullptr && Vector2DB != nullptr && OutVector2D != nullptr)
	{
		*OutVector2D = Vector2DA->operator*(*Vector2DB);
	}
}

void FVector2DImplementation::Vector2D_DivideImplementation(const MonoObject* A, const MonoObject* B,
                                                            MonoObject** OutValue)
{
	const auto Vector2DA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(A);

	const auto Vector2DB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(B);

	const auto FoundMonoClass = TPropertyClass<FVector2D, FVector2D>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(NewMonoObject);

	if (Vector2DA != nullptr && Vector2DB != nullptr && OutVector2D != nullptr)
	{
		*OutVector2D = Vector2DA->operator/(*Vector2DB);
	}
}

FVector2DImplementation::LwcType FVector2DImplementation::Vector2D_DotProductImplementation(
	const MonoObject* A, const MonoObject* B)
{
	const auto Vector2DA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(A);

	const auto Vector2DB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(B);

	if (Vector2DA != nullptr && Vector2DB != nullptr)
	{
		return Vector2DA->operator|(*Vector2DB);
	}

	return 0.f;
}

FVector2DImplementation::LwcType FVector2DImplementation::Vector2D_CrossProductImplementation(
	const MonoObject* A, const MonoObject* B)
{
	const auto Vector2DA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(A);

	const auto Vector2DB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(B);

	if (Vector2DA != nullptr && Vector2DB != nullptr)
	{
		return Vector2DA->operator^(*Vector2DB);
	}

	return 0.f;
}

bool FVector2DImplementation::Vector2D_EqualityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto Vector2DA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(A);

	const auto Vector2DB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(B);

	if (Vector2DA != nullptr && Vector2DB != nullptr)
	{
		return Vector2DA->operator==(*Vector2DB);
	}

	return false;
}

bool FVector2DImplementation::Vector2D_InequalityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto Vector2DA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(A);

	const auto Vector2DB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(B);

	if (Vector2DA != nullptr && Vector2DB != nullptr)
	{
		return Vector2DA->operator!=(*Vector2DB);
	}

	return false;
}

bool FVector2DImplementation::Vector2D_LessThanImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto Vector2DA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(A);

	const auto Vector2DB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(B);

	if (Vector2DA != nullptr && Vector2DB != nullptr)
	{
		return Vector2DA->operator<(*Vector2DB);
	}

	return false;
}

bool FVector2DImplementation::Vector2D_GreaterThanImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto Vector2DA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(A);

	const auto Vector2DB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(B);

	if (Vector2DA != nullptr && Vector2DB != nullptr)
	{
		return Vector2DA->operator>(*Vector2DB);
	}

	return false;
}

bool FVector2DImplementation::Vector2D_LessThanOrEqualImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto Vector2DA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(A);

	const auto Vector2DB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(B);

	if (Vector2DA != nullptr && Vector2DB != nullptr)
	{
		return Vector2DA->operator<=(*Vector2DB);
	}

	return false;
}

bool FVector2DImplementation::Vector2D_GreaterThanOrEqualImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto Vector2DA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(A);

	const auto Vector2DB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(B);

	if (Vector2DA != nullptr && Vector2DB != nullptr)
	{
		return Vector2DA->operator>=(*Vector2DB);
	}

	return false;
}

void FVector2DImplementation::Vector2D_NegatedImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FVector2D, FVector2D>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(NewMonoObject);

	if (Vector2D != nullptr && OutVector2D != nullptr)
	{
		*OutVector2D = Vector2D->operator-();
	}
}

FVector2DImplementation::LwcType FVector2DImplementation::Vector2D_GetComponentImplementation(
	const MonoObject* InMonoObject, const int32 Index)
{
	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InMonoObject);

	if (Vector2D != nullptr)
	{
		return Vector2D->operator[](Index);
	}

	return 0.f;
}

void FVector2DImplementation::Vector2D_SetComponentImplementation(const MonoObject* InMonoObject, const int32 Index,
                                                                  const LwcType InValue)
{
	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InMonoObject);

	if (Vector2D != nullptr)
	{
		Vector2D->operator[](Index) = InValue;
	}
}

FVector2DImplementation::LwcType FVector2DImplementation::Vector2D_ComponentImplementation(
	const MonoObject* InMonoObject, const int32 Index)
{
	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InMonoObject);

	if (Vector2D != nullptr)
	{
		return Vector2D->Component(Index);
	}

	return 0.f;
}

FVector2DImplementation::LwcType FVector2DImplementation::Vector2D_DistSquaredImplementation(
	const MonoObject* A, const MonoObject* B)
{
	const auto Vector2DA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(A);

	const auto Vector2DB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(B);

	if (Vector2DA != nullptr && Vector2DB != nullptr)
	{
		return FVector2D::DistSquared(*Vector2DA, *Vector2DB);
	}

	return 0.f;
}

FVector2DImplementation::LwcType FVector2DImplementation::Vector2D_DistanceImplementation(
	const MonoObject* A, const MonoObject* B)
{
	const auto Vector2DA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(A);

	const auto Vector2DB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(B);

	if (Vector2DA != nullptr && Vector2DB != nullptr)
	{
		return FVector2D::Distance(*Vector2DA, *Vector2DB);
	}

	return 0.f;
}

void FVector2DImplementation::Vector2D_MaxImplementation(const MonoObject* A, const MonoObject* B,
                                                         MonoObject** OutValue)
{
	const auto Vector2DA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(A);

	const auto Vector2DB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(B);

	const auto FoundMonoClass = TPropertyClass<FVector2D, FVector2D>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(NewMonoObject);

	if (Vector2DA != nullptr && Vector2DB != nullptr && OutVector2D != nullptr)
	{
		*OutVector2D = FVector2D::Max(*Vector2DA, *Vector2DB);
	}
}

void FVector2DImplementation::Vector2D_MinImplementation(const MonoObject* A, const MonoObject* B,
                                                         MonoObject** OutValue)
{
	const auto Vector2DA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(A);

	const auto Vector2DB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(B);

	const auto FoundMonoClass = TPropertyClass<FVector2D, FVector2D>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(NewMonoObject);

	if (Vector2DA != nullptr && Vector2DB != nullptr && OutVector2D != nullptr)
	{
		*OutVector2D = FVector2D::Min(*Vector2DA, *Vector2DB);
	}
}

bool FVector2DImplementation::Vector2D_EqualsImplementation(const MonoObject* A, const MonoObject* B,
                                                            const LwcType Tolerance)
{
	const auto Vector2DA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(A);

	const auto Vector2DB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(B);

	if (Vector2DA != nullptr && Vector2DB != nullptr)
	{
		return Vector2DA->Equals(*Vector2DB, Tolerance);
	}

	return false;
}

void FVector2DImplementation::Vector2D_SetImplementation(const MonoObject* InMonoObject, const LwcType InX,
                                                         const LwcType InY)
{
	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InMonoObject);

	if (Vector2D != nullptr)
	{
		Vector2D->Set(InX, InY);
	}
}

FVector2DImplementation::LwcType FVector2DImplementation::Vector2D_GetMaxImplementation(const MonoObject* InMonoObject)
{
	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InMonoObject);

	if (Vector2D != nullptr)
	{
		return Vector2D->GetMax();
	}

	return 0.f;
}

FVector2DImplementation::LwcType FVector2DImplementation::Vector2D_GetAbsMaxImplementation(
	const MonoObject* InMonoObject)
{
	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InMonoObject);

	if (Vector2D != nullptr)
	{
		return Vector2D->GetAbsMax();
	}

	return 0.f;
}

FVector2DImplementation::LwcType FVector2DImplementation::Vector2D_GetMinImplementation(const MonoObject* InMonoObject)
{
	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InMonoObject);

	if (Vector2D != nullptr)
	{
		return Vector2D->GetMin();
	}

	return 0.f;
}

FVector2DImplementation::LwcType FVector2DImplementation::Vector2D_SizeImplementation(const MonoObject* InMonoObject)
{
	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InMonoObject);

	if (Vector2D != nullptr)
	{
		return Vector2D->Size();
	}

	return 0.f;
}

FVector2DImplementation::LwcType FVector2DImplementation::Vector2D_SizeSquaredImplementation(
	const MonoObject* InMonoObject)
{
	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InMonoObject);

	if (Vector2D != nullptr)
	{
		return Vector2D->SizeSquared();
	}

	return 0.f;
}

void FVector2DImplementation::Vector2D_GetRotatedImplementation(const MonoObject* InMonoObject, const LwcType AngleDeg,
                                                                MonoObject** OutValue)
{
	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FVector2D, FVector2D>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(NewMonoObject);

	if (Vector2D != nullptr && OutVector2D != nullptr)
	{
		*OutVector2D = Vector2D->GetRotated(AngleDeg);
	}
}

void FVector2DImplementation::Vector2D_GetSafeNormalImplementation(const MonoObject* InMonoObject,
                                                                   const LwcType Tolerance, MonoObject** OutValue)
{
	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FVector2D, FVector2D>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(NewMonoObject);

	if (Vector2D != nullptr && OutVector2D != nullptr)
	{
		*OutVector2D = Vector2D->GetSafeNormal(Tolerance);
	}
}

void FVector2DImplementation::Vector2D_NormalizeImplementation(const MonoObject* InMonoObject, const LwcType Tolerance)
{
	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InMonoObject);

	if (Vector2D != nullptr)
	{
		Vector2D->Normalize(Tolerance);
	}
}

bool FVector2DImplementation::Vector2D_IsNearlyZeroImplementation(const MonoObject* InMonoObject,
                                                                  const LwcType Tolerance)
{
	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InMonoObject);

	if (Vector2D != nullptr)
	{
		return Vector2D->IsNearlyZero(Tolerance);
	}

	return false;
}

void FVector2DImplementation::Vector2D_IntPointImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FIntPoint, FIntPoint>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutIntPoint = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FIntPoint>(NewMonoObject);

	if (Vector2D != nullptr && OutIntPoint != nullptr)
	{
		*OutIntPoint = Vector2D->IntPoint();
	}
}

void FVector2DImplementation::Vector2D_RoundToVectorImplementation(const MonoObject* InMonoObject,
                                                                   MonoObject** OutValue)
{
	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FVector2D, FVector2D>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(NewMonoObject);

	if (Vector2D != nullptr && OutVector2D != nullptr)
	{
		*OutVector2D = Vector2D->RoundToVector();
	}
}

void FVector2DImplementation::Vector2D_ClampAxesImplementation(const MonoObject* InMonoObject, const LwcType MinAxisVal,
                                                               const LwcType MaxAxisVal, MonoObject** OutValue)
{
	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FVector2D, FVector2D>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(NewMonoObject);

	if (Vector2D != nullptr && OutVector2D != nullptr)
	{
		*OutVector2D = Vector2D->ClampAxes(MinAxisVal, MaxAxisVal);
	}
}

void FVector2DImplementation::Vector2D_GetSignVectorImplementation(const MonoObject* InMonoObject,
                                                                   MonoObject** OutValue)
{
	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FVector2D, FVector2D>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(NewMonoObject);

	if (Vector2D != nullptr && OutVector2D != nullptr)
	{
		*OutVector2D = Vector2D->GetSignVector();
	}
}

void FVector2DImplementation::Vector2D_GetAbsImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FVector2D, FVector2D>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(NewMonoObject);

	if (Vector2D != nullptr && OutVector2D != nullptr)
	{
		*OutVector2D = Vector2D->GetAbs();
	}
}

void FVector2DImplementation::Vector2D_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InMonoObject);

	if (Vector2D != nullptr)
	{
		const auto ResultString = Vector2D->ToString();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

bool FVector2DImplementation::Vector2D_InitFromStringImplementation(const MonoObject* InMonoObject,
                                                                    MonoObject* InSourceString)
{
	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InMonoObject);

	if (Vector2D != nullptr && InSourceString != nullptr)
	{
		return Vector2D->InitFromString(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(InSourceString, nullptr))));
	}

	return false;
}

bool FVector2DImplementation::Vector2D_ContainsNaNImplementation(const MonoObject* InMonoObject)
{
	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InMonoObject);

	if (Vector2D != nullptr)
	{
		return Vector2D->ContainsNaN();
	}

	return false;
}

void FVector2DImplementation::Vector2D_SphericalToUnitCartesianImplementation(
	const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InMonoObject);

	const auto FoundMonoClass = TPropertyClass<FVector, FVector>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector>(NewMonoObject);

	if (Vector2D != nullptr && OutVector != nullptr)
	{
		*OutVector = Vector2D->SphericalToUnitCartesian();
	}
}
