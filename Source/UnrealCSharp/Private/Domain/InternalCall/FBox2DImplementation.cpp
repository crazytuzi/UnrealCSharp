#include "Domain/InternalCall/FBox2DImplementation.h"
#include "Binding/Class/TScriptStructBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/NamespaceMacro.h"
#include "FUnrealCSharpFunctionLibrary.h"

struct FRegisterBox2D
{
	FRegisterBox2D()
	{
		TScriptStructBuilder<FBox2D>(NAMESPACE_LIBRARY)
			.Function("Equality", static_cast<void*>(FBox2DImplementation::Box2D_EqualityImplementation))
			.Function("Inequality", static_cast<void*>(FBox2DImplementation::Box2D_InequalityImplementation))
			.Function("AddVector2D", static_cast<void*>(FBox2DImplementation::Box2D_AddVector2DImplementation))
			.Function("Add", static_cast<void*>(FBox2DImplementation::Box2D_AddImplementation))
			.Function("GetReference", static_cast<void*>(FBox2DImplementation::Box2D_GetReferenceImplementation))
			.Function("SetReference", static_cast<void*>(FBox2DImplementation::Box2D_SetReferenceImplementation))
			.Function("ComputeSquaredDistanceToPoint",
			          static_cast<void*>(FBox2DImplementation::Box2D_ComputeSquaredDistanceToPointImplementation))
			.Function("ExpandBy", static_cast<void*>(FBox2DImplementation::Box2D_ExpandByImplementation))
			.Function("GetArea", static_cast<void*>(FBox2DImplementation::Box2D_GetAreaImplementation))
			.Function("GetCenter", static_cast<void*>(FBox2DImplementation::Box2D_GetCenterImplementation))
			.Function("GetCenterAndExtents",
			          static_cast<void*>(FBox2DImplementation::Box2D_GetCenterAndExtentsImplementation))
			.Function("GetClosestPointTo",
			          static_cast<void*>(FBox2DImplementation::Box2D_GetClosestPointToImplementation))
			.Function("GetExtent", static_cast<void*>(FBox2DImplementation::Box2D_GetExtentImplementation))
			.Function("GetSize", static_cast<void*>(FBox2DImplementation::Box2D_GetSizeImplementation))
			.Function("Init", static_cast<void*>(FBox2DImplementation::Box2D_InitImplementation))
			.Function("Intersect", static_cast<void*>(FBox2DImplementation::Box2D_IntersectImplementation))
			.Function("IsInsideVector2D",
			          static_cast<void*>(FBox2DImplementation::Box2D_IsInsideVector2DImplementation))
			.Function("IsInsideBox2D", static_cast<void*>(FBox2DImplementation::Box2D_IsInsideBox2DImplementation))
			.Function("ShiftBy", static_cast<void*>(FBox2DImplementation::Box2D_ShiftByImplementation))
			.Function("ToString", static_cast<void*>(FBox2DImplementation::Box2D_ToStringImplementation))
			.Register();
	}
};

static FRegisterBox2D RegisterBox2D;

bool FBox2DImplementation::Box2D_EqualityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto Box2DA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(A);

	const auto Box2DB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(B);

	if (Box2DA != nullptr && Box2DB != nullptr)
	{
		return Box2DA->operator==(*Box2DB);
	}

	return false;
}

bool FBox2DImplementation::Box2D_InequalityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto Box2DA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(A);

	const auto Box2DB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(B);

	if (Box2DA != nullptr && Box2DB != nullptr)
	{
		return Box2DA->operator==(*Box2DB);
	}

	return false;
}

void FBox2DImplementation::Box2D_AddVector2DImplementation(const MonoObject* A, const MonoObject* B,
                                                           MonoObject** OutValue)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(A);

	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(B);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FBox2D)),
		CLASS_SCRIPT_STRUCT_NAME(FBox2D));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutBox2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(NewMonoObject);

	if (Box2D != nullptr && Vector2D != nullptr && OutBox2D != nullptr)
	{
		*OutBox2D = Box2D->operator+(*Vector2D);
	}
}

void FBox2DImplementation::Box2D_AddImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue)
{
	const auto Box2DA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(A);

	const auto Box2DB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(B);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FBox2D)),
		CLASS_SCRIPT_STRUCT_NAME(FBox2D));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutBox2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(NewMonoObject);

	if (Box2DA != nullptr && Box2DB != nullptr && OutBox2D != nullptr)
	{
		*OutBox2D = Box2DA->operator+(*Box2DB);
	}
}

void FBox2DImplementation::Box2D_GetReferenceImplementation(const MonoObject* InMonoObject, const int32 Index,
                                                            MonoObject** OutValue)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector2D)),
		CLASS_SCRIPT_STRUCT_NAME(FVector2D));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(NewMonoObject);

	if (Box2D != nullptr && OutVector2D != nullptr)
	{
		*OutVector2D = Box2D->operator[](Index);
	}
}

void FBox2DImplementation::Box2D_SetReferenceImplementation(const MonoObject* InMonoObject, const int32 Index,
                                                            const MonoObject* InValue)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(InMonoObject);

	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InValue);

	if (Box2D != nullptr && Vector2D != nullptr)
	{
		Box2D->operator[](Index) = *Vector2D;
	}
}

float FBox2DImplementation::Box2D_ComputeSquaredDistanceToPointImplementation(
	const MonoObject* InMonoObject, const MonoObject* Point)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(InMonoObject);

	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(Point);

	if (Box2D != nullptr && Vector2D != nullptr)
	{
		return Box2D->ComputeSquaredDistanceToPoint(*Vector2D);
	}

	return 0.f;
}

void FBox2DImplementation::Box2D_ExpandByImplementation(const MonoObject* InMonoObject, const float W,
                                                        MonoObject** OutValue)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FBox2D)),
		CLASS_SCRIPT_STRUCT_NAME(FBox2D));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutBox2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(NewMonoObject);

	if (Box2D != nullptr && OutBox2D != nullptr)
	{
		*OutBox2D = Box2D->ExpandBy(W);
	}
}

float FBox2DImplementation::Box2D_GetAreaImplementation(const MonoObject* InMonoObject)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(InMonoObject);

	if (Box2D != nullptr)
	{
		return Box2D->GetArea();
	}

	return 0.f;
}

void FBox2DImplementation::Box2D_GetCenterImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector2D)),
		CLASS_SCRIPT_STRUCT_NAME(FVector2D));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(NewMonoObject);

	if (Box2D != nullptr && OutVector2D != nullptr)
	{
		*OutVector2D = Box2D->GetCenter();
	}
}

void FBox2DImplementation::Box2D_GetCenterAndExtentsImplementation(const MonoObject* InMonoObject, MonoObject** center,
                                                                   MonoObject** Extents)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector2D)),
		CLASS_SCRIPT_STRUCT_NAME(FVector2D));

	const auto NewMonoObject1 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*center = NewMonoObject1;

	const auto OutCenterVector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(
		NewMonoObject1);

	const auto NewMonoObject2 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*Extents = NewMonoObject2;

	const auto OutExtentsVector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(
		NewMonoObject2);

	if (Box2D != nullptr && OutCenterVector2D != nullptr && OutExtentsVector2D != nullptr)
	{
		Box2D->GetCenterAndExtents(*OutCenterVector2D, *OutExtentsVector2D);
	}
}

void FBox2DImplementation::Box2D_GetClosestPointToImplementation(const MonoObject* InMonoObject,
                                                                 const MonoObject* Point, MonoObject** OutValue)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(InMonoObject);

	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(Point);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector2D)),
		CLASS_SCRIPT_STRUCT_NAME(FVector2D));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(NewMonoObject);

	if (Box2D != nullptr && Vector2D != nullptr && OutVector2D != nullptr)
	{
		*OutVector2D = Box2D->GetClosestPointTo(*Vector2D);
	}
}

void FBox2DImplementation::Box2D_GetExtentImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector2D)),
		CLASS_SCRIPT_STRUCT_NAME(FVector2D));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(NewMonoObject);

	if (Box2D != nullptr && OutVector2D != nullptr)
	{
		*OutVector2D = Box2D->GetExtent();
	}
}

void FBox2DImplementation::Box2D_GetSizeImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector2D)),
		CLASS_SCRIPT_STRUCT_NAME(FVector2D));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(NewMonoObject);

	if (Box2D != nullptr && OutVector2D != nullptr)
	{
		*OutVector2D = Box2D->GetSize();
	}
}

void FBox2DImplementation::Box2D_InitImplementation(const MonoObject* InMonoObject)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(InMonoObject);

	if (Box2D != nullptr)
	{
		Box2D->Init();
	}
}

bool FBox2DImplementation::Box2D_IntersectImplementation(const MonoObject* InMonoObject, const MonoObject* other)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(InMonoObject);

	const auto Box2DOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(other);

	if (Box2D != nullptr && Box2DOther != nullptr)
	{
		return Box2D->Intersect(*Box2DOther);
	}

	return false;
}

bool FBox2DImplementation::Box2D_IsInsideVector2DImplementation(const MonoObject* InMonoObject,
                                                                const MonoObject* TestPoint)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(InMonoObject);

	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(TestPoint);

	if (Box2D != nullptr && Vector2D != nullptr)
	{
		return Box2D->IsInside(*Vector2D);
	}

	return false;
}

bool FBox2DImplementation::Box2D_IsInsideBox2DImplementation(const MonoObject* InMonoObject, const MonoObject* Other)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(InMonoObject);

	const auto Box2DOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(Other);

	if (Box2D != nullptr && Box2DOther != nullptr)
	{
		return Box2D->IsInside(*Box2DOther);
	}

	return false;
}

void FBox2DImplementation::Box2D_ShiftByImplementation(const MonoObject* InMonoObject, const MonoObject* Offset,
                                                       MonoObject** OutValue)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(InMonoObject);

	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(Offset);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FBox2D)),
		CLASS_SCRIPT_STRUCT_NAME(FBox2D));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutBox2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(NewMonoObject);

	if (Box2D != nullptr && OutBox2D != nullptr)
	{
		*OutBox2D = Box2D->ShiftBy(*Vector2D);
	}
}

void FBox2DImplementation::Box2D_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(InMonoObject);

	if (Box2D != nullptr)
	{
		const auto ResultString = Box2D->ToString();

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}
