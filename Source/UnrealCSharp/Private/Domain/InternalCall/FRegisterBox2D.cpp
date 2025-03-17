#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"
#include "UEVersion.h"
#include "FRegisterForceInit.h"

namespace
{
	struct FRegisterBox2D
	{
		static FBox2D PlusImplementation(const FBox2D& In, const FVector2D& Other)
		{
			return &In != nullptr && (&Other != nullptr) ? In + Other : decltype(In + Other)();
		}

		FRegisterBox2D()
		{
			TBindingClassBuilder<FBox2D>(NAMESPACE_BINDING)
				.Constructor(BINDING_CONSTRUCTOR(FBox2D, EForceInit))
				.Constructor(BINDING_CONSTRUCTOR(FBox2D, const FVector2D&, const FVector2D&),
				             TArray<FString>{"InMin", "InMax"})
				.Constructor(BINDING_CONSTRUCTOR(FBox2D, const FVector2D*, const int32),
				             TArray<FString>{"Points", "Count"})
				.Constructor(BINDING_CONSTRUCTOR(FBox2D, const TArray<FVector2D>&),
				             TArray<FString>{"Points"})
				.Plus()
				.Subscript(BINDING_SUBSCRIPT(FBox2D, FVector2D, int32,
				                             TArray<FString>{"Index"}))
				.Function("operator +", FUNCTION_PLUS, BINDING_FUNCTION(&PlusImplementation))
				.Function("ComputeSquaredDistanceToPoint", BINDING_FUNCTION(&FBox2D::ComputeSquaredDistanceToPoint,
				                                                            TArray<FString>{"Point"}))
				.Function("ExpandBy", BINDING_OVERLOAD(FBox2D(FBox2D::*)(const FBox2D::FReal)const, &FBox2D::ExpandBy,
				                                       TArray<FString>{"W"}))
#if UE_BOX_2D_EXPAND_BY_VECTOR2
				.Function("ExpandBy", BINDING_OVERLOAD(FBox2D(FBox2D::*)(const FVector2D&)const, &FBox2D::ExpandBy,
				                                       TArray<FString>{"V"}))
#endif
				.Function("GetArea", BINDING_FUNCTION(&FBox2D::GetArea))
				.Function("GetCenter", BINDING_FUNCTION(&FBox2D::GetCenter))
				.Function("GetCenterAndExtents", BINDING_FUNCTION(&FBox2D::GetCenterAndExtents,
				                                                  TArray<FString>{"center", "Extents"}))
				.Function("GetClosestPointTo", BINDING_FUNCTION(&FBox2D::GetClosestPointTo,
				                                                TArray<FString>{"Point"}))
				.Function("GetExtent", BINDING_FUNCTION(&FBox2D::GetExtent))
				.Function("GetSize", BINDING_FUNCTION(&FBox2D::GetSize))
				.Function("Init", BINDING_FUNCTION(&FBox2D::Init))
				.Function("Overlap", BINDING_FUNCTION(&FBox2D::Overlap,
				                                      TArray<FString>{"Other"}))
				.Function("Intersect", BINDING_FUNCTION(&FBox2D::Intersect,
				                                        TArray<FString>{"other"}))
				.Function("IsInside", BINDING_OVERLOAD(bool(FBox2D::*)(const FVector2D&)const, &FBox2D::IsInside,
				                                       TArray<FString>{"TestPoint"}))
				.Function("IsInside", BINDING_OVERLOAD(bool(FBox2D::*)(const FBox2D&)const, &FBox2D::IsInside,
				                                       TArray<FString>{"Other"}))
				.Function("ShiftBy", BINDING_FUNCTION(&FBox2D::ShiftBy,
				                                      TArray<FString>{"Offset"}))
				.Function("ToString", BINDING_FUNCTION(&FBox2D::ToString,
				                                       EFunctionInteract::New));
		}
	};

	[[maybe_unused]] FRegisterBox2D RegisterBox2D;
}
