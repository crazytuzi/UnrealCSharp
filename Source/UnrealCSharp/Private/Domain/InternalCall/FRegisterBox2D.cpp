#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"
#include "UEVersion.h"

struct FRegisterBox2D
{
	static FBox2D PlusImplementation(const FBox2D& In, const FVector2D& Other)
	{
		return In + Other;
	}

	FRegisterBox2D()
	{
		TBindingClassBuilder<FBox2D>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FBox2D, EForceInit))
			.Constructor(BINDING_CONSTRUCTOR(FBox2D, const FVector2D&, const FVector2D&),
			             {"InMin", "InMax"})
			.Constructor(BINDING_CONSTRUCTOR(FBox2D, const FVector2D*, const int32),
			             {"Points", "Count"})
			.Constructor(BINDING_CONSTRUCTOR(FBox2D, const TArray<FVector2D>&),
			             {"Points"})
			.Plus()
			.Subscript(BINDING_SUBSCRIPT(FBox2D, FVector2D, int32),
			           {"Index"})
			.Function("operator +", FUNCTION_PLUS, BINDING_FUNCTION(&PlusImplementation))
			.Function("ComputeSquaredDistanceToPoint", BINDING_FUNCTION(&FBox2D::ComputeSquaredDistanceToPoint),
			          {"Point"})
			.Function("ExpandBy", BINDING_OVERLOAD(FBox2D(FBox2D::*)(const FBox2D::FReal)const, &FBox2D::ExpandBy),
			          {"W"})
#if UE_BOX_2D_EXPAND_BY_VECTOR2
			.Function("ExpandBy", BINDING_OVERLOAD(FBox2D(FBox2D::*)(const FVector2D&)const, &FBox2D::ExpandBy),
			          {"V"})
#endif
			.Function("GetArea", BINDING_FUNCTION(&FBox2D::GetArea))
			.Function("GetCenter", BINDING_FUNCTION(&FBox2D::GetCenter))
			.Function("GetCenterAndExtents", BINDING_FUNCTION(&FBox2D::GetCenterAndExtents),
			          {"center", "Extents"})
			.Function("GetClosestPointTo", BINDING_FUNCTION(&FBox2D::GetClosestPointTo),
			          {"Point"})
			.Function("GetExtent", BINDING_FUNCTION(&FBox2D::GetExtent))
			.Function("GetSize", BINDING_FUNCTION(&FBox2D::GetSize))
			.Function("Init", BINDING_FUNCTION(&FBox2D::Init))
			.Function("Overlap", BINDING_FUNCTION(&FBox2D::Overlap),
			          {"Other"})
			.Function("Intersect", BINDING_FUNCTION(&FBox2D::Intersect),
			          {"other"})
			.Function("IsInside", BINDING_OVERLOAD(bool(FBox2D::*)(const FVector2D&)const, &FBox2D::IsInside),
			          {"TestPoint"})
			.Function("IsInside", BINDING_OVERLOAD(bool(FBox2D::*)(const FBox2D&)const, &FBox2D::IsInside),
			          {"Other"})
			.Function("ShiftBy", BINDING_FUNCTION(&FBox2D::ShiftBy),
			          {"Offset"})
			.Function("ToString", BINDING_FUNCTION(&FBox2D::ToString),
			          {}, EFunctionInteract::New)
			.Register();
	}
};

static FRegisterBox2D RegisterBox2D;
