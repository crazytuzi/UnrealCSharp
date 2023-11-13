#include "Domain/InternalCall/FBox2DImplementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterBox2D
{
	FRegisterBox2D()
	{
		TReflectionClassBuilder<FBox2D>(NAMESPACE_LIBRARY)
			.Function("AddVector2D", FBox2DImplementation::Box2D_AddVector2DImplementation)
			.Function("Add", FBox2DImplementation::Box2D_AddImplementation)
			.Function("GetReference", FBox2DImplementation::Box2D_GetReferenceImplementation)
			.Function("SetReference", FBox2DImplementation::Box2D_SetReferenceImplementation)
			.Function("ComputeSquaredDistanceToPoint",
			          FBox2DImplementation::Box2D_ComputeSquaredDistanceToPointImplementation)
			.Function("ExpandBy", FBox2DImplementation::Box2D_ExpandByImplementation)
			.Function("GetArea", FBox2DImplementation::Box2D_GetAreaImplementation)
			.Function("GetCenter", FBox2DImplementation::Box2D_GetCenterImplementation)
			.Function("GetCenterAndExtents", FBox2DImplementation::Box2D_GetCenterAndExtentsImplementation)
			.Function("GetClosestPointTo", FBox2DImplementation::Box2D_GetClosestPointToImplementation)
			.Function("GetExtent", FBox2DImplementation::Box2D_GetExtentImplementation)
			.Function("GetSize", FBox2DImplementation::Box2D_GetSizeImplementation)
			.Function("Init", FBox2DImplementation::Box2D_InitImplementation)
			.Function("Intersect", FBox2DImplementation::Box2D_IntersectImplementation)
			.Function("IsInsideVector2D", FBox2DImplementation::Box2D_IsInsideVector2DImplementation)
			.Function("IsInsideBox2D", FBox2DImplementation::Box2D_IsInsideBox2DImplementation)
			.Function("ShiftBy", FBox2DImplementation::Box2D_ShiftByImplementation)
			.Function("ToString", FBox2DImplementation::Box2D_ToStringImplementation)
			.Register();
	}
};

static FRegisterBox2D RegisterBox2D;

void FBox2DImplementation::Box2D_AddVector2DImplementation(const FGarbageCollectionHandle A,
                                                           const FGarbageCollectionHandle B, MonoObject** OutValue)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(A);

	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(B);

	const auto FoundMonoClass = TPropertyClass<FBox2D, FBox2D>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutBox2D = new FBox2D(Box2D->operator+(*Vector2D));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FBox2D>::Get(), OutBox2D,
	                                                        NewMonoObject);
}

void FBox2DImplementation::Box2D_AddImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
                                                   MonoObject** OutValue)
{
	const auto Box2DA = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(A);

	const auto Box2DB = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(B);

	const auto FoundMonoClass = TPropertyClass<FBox2D, FBox2D>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutBox2D = new FBox2D(Box2DA->operator+(*Box2DB));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FBox2D>::Get(), OutBox2D,
	                                                        NewMonoObject);
}

void FBox2DImplementation::Box2D_GetReferenceImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                            const int32 Index, MonoObject** OutValue)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FBox2D>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector2D, FVector2D>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = new FVector2D(Box2D->operator[](Index));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector2D>::Get(), OutVector2D,
	                                                        NewMonoObject);
}

void FBox2DImplementation::Box2D_SetReferenceImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                            const int32 Index, const MonoObject* InValue)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FBox2D>(InGarbageCollectionHandle);

	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(InValue);

	if (Box2D != nullptr && Vector2D != nullptr)
	{
		Box2D->operator[](Index) = *Vector2D;
	}
}

FBox2DImplementation::LwcType FBox2DImplementation::Box2D_ComputeSquaredDistanceToPointImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Point)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FBox2D>(InGarbageCollectionHandle);

	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(Point);

	if (Box2D != nullptr && Vector2D != nullptr)
	{
		return Box2D->ComputeSquaredDistanceToPoint(*Vector2D);
	}

	return 0.f;
}

void FBox2DImplementation::Box2D_ExpandByImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                        const LwcType W, MonoObject** OutValue)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FBox2D>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FBox2D, FBox2D>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutBox2D = new FBox2D(Box2D->ExpandBy(W));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FBox2D>::Get(), OutBox2D,
	                                                        NewMonoObject);
}

FBox2DImplementation::LwcType FBox2DImplementation::Box2D_GetAreaImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FBox2D>(InGarbageCollectionHandle);

	if (Box2D != nullptr)
	{
		return Box2D->GetArea();
	}

	return 0.f;
}

void FBox2DImplementation::Box2D_GetCenterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                         MonoObject** OutValue)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FBox2D>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector2D, FVector2D>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = new FVector2D(Box2D->GetCenter());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector2D>::Get(), OutVector2D,
	                                                        NewMonoObject);
}

void FBox2DImplementation::Box2D_GetCenterAndExtentsImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** center, MonoObject** Extents)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FBox2D>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector2D, FVector2D>::Get();

	const auto NewMonoObject1 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*center = NewMonoObject1;

	const auto OutCenterVector2D = new FVector2D();

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector2D>::Get(), OutCenterVector2D,
	                                                        NewMonoObject1);

	const auto NewMonoObject2 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*Extents = NewMonoObject2;

	const auto OutExtentsVector2D = new FVector2D();

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector2D>::Get(), OutExtentsVector2D,
	                                                        NewMonoObject2);

	if (Box2D != nullptr && OutCenterVector2D != nullptr && OutExtentsVector2D != nullptr)
	{
		Box2D->GetCenterAndExtents(*OutCenterVector2D, *OutExtentsVector2D);
	}
}

void FBox2DImplementation::Box2D_GetClosestPointToImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Point, MonoObject** OutValue)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FBox2D>(InGarbageCollectionHandle);

	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(Point);

	const auto FoundMonoClass = TPropertyClass<FVector2D, FVector2D>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = new FVector2D(Box2D->GetClosestPointTo(*Vector2D));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector2D>::Get(), OutVector2D,
	                                                        NewMonoObject);
}

void FBox2DImplementation::Box2D_GetExtentImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                         MonoObject** OutValue)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FBox2D>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector2D, FVector2D>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = new FVector2D(Box2D->GetExtent());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector2D>::Get(), OutVector2D,
	                                                        NewMonoObject);
}

void FBox2DImplementation::Box2D_GetSizeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                       MonoObject** OutValue)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FBox2D>(InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector2D, FVector2D>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector2D = new FVector2D(Box2D->GetSize());

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FVector2D>::Get(), OutVector2D,
	                                                        NewMonoObject);
}

void FBox2DImplementation::Box2D_InitImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FBox2D>(InGarbageCollectionHandle);

	if (Box2D != nullptr)
	{
		Box2D->Init();
	}
}

bool FBox2DImplementation::Box2D_IntersectImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                         const MonoObject* other)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FBox2D>(InGarbageCollectionHandle);

	const auto Box2DOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(other);

	if (Box2D != nullptr && Box2DOther != nullptr)
	{
		return Box2D->Intersect(*Box2DOther);
	}

	return false;
}

bool FBox2DImplementation::Box2D_IsInsideVector2DImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* TestPoint)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FBox2D>(InGarbageCollectionHandle);

	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(TestPoint);

	if (Box2D != nullptr && Vector2D != nullptr)
	{
		return Box2D->IsInside(*Vector2D);
	}

	return false;
}

bool FBox2DImplementation::Box2D_IsInsideBox2DImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                             const MonoObject* Other)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FBox2D>(InGarbageCollectionHandle);

	const auto Box2DOther = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FBox2D>(Other);

	if (Box2D != nullptr && Box2DOther != nullptr)
	{
		return Box2D->IsInside(*Box2DOther);
	}

	return false;
}

void FBox2DImplementation::Box2D_ShiftByImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                       const MonoObject* Offset, MonoObject** OutValue)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FBox2D>(InGarbageCollectionHandle);

	const auto Vector2D = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector2D>(Offset);

	const auto FoundMonoClass = TPropertyClass<FBox2D, FBox2D>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutBox2D = new FBox2D(Box2D->ShiftBy(*Vector2D));

	FCSharpEnvironment::GetEnvironment().AddStructReference(TBaseStructure<FBox2D>::Get(), OutBox2D,
	                                                        NewMonoObject);
}

void FBox2DImplementation::Box2D_ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                        MonoObject** OutValue)
{
	const auto Box2D = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FBox2D>(InGarbageCollectionHandle);

	if (Box2D != nullptr)
	{
		const auto ResultString = Box2D->ToString();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Init(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}
