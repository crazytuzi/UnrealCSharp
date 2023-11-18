#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

struct FRegisterVector
{
	static FVector::FReal BitOrImplementation(const FVector& In, const FVector& V)
	{
		return In | V;
	}

	FRegisterVector()
	{
		TReflectionClassBuilder<FVector>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FVector, FVector::FReal),
			             {"InF"})
			.Constructor(BINDING_CONSTRUCTOR(FVector, FVector::FReal, FVector::FReal, FVector::FReal),
			             {"InX", "InY", "InZ"})
			.Constructor(BINDING_CONSTRUCTOR(FVector, const FVector2D, FVector::FReal),
			             {"V", "InZ"})
			.Constructor(BINDING_CONSTRUCTOR(FVector, const FVector4&),
			             {"V"})
			.Constructor(BINDING_CONSTRUCTOR(FVector, const FLinearColor&),
			             {"InColor"})
			.BitXor()
			.Plus()
			.Minus()
			.Multiplies()
			.Divides()
			.UnaryMinus()
			.Subscript(BINDING_SUBSCRIPT(FVector, FVector::FReal, int32),
			           {"Index"})
			.Function("operator |", FUNCTION_BIT_OR, BINDING_FUNCTION(&BitOrImplementation))
			.Property("ZeroVector", BINDING_PROPERTY(&FVector::ZeroVector))
			.Property("OneVector", BINDING_PROPERTY(&FVector::OneVector))
			.Property("UpVector", BINDING_PROPERTY(&FVector::UpVector))
			.Property("DownVector", BINDING_PROPERTY(&FVector::DownVector))
			.Property("ForwardVector", BINDING_PROPERTY(&FVector::ForwardVector))
			.Property("BackwardVector", BINDING_PROPERTY(&FVector::BackwardVector))
			.Property("RightVector", BINDING_PROPERTY(&FVector::RightVector))
			.Property("LeftVector", BINDING_PROPERTY(&FVector::LeftVector))
			.Property("XAxisVector", BINDING_PROPERTY(&FVector::XAxisVector))
			.Property("YAxisVector", BINDING_PROPERTY(&FVector::YAxisVector))
			.Property("ZAxisVector", BINDING_PROPERTY(&FVector::ZAxisVector))
			.Function("Zero", BINDING_FUNCTION(&FVector::Zero))
			.Function("One", BINDING_FUNCTION(&FVector::One))
			.Function("UnitX", BINDING_FUNCTION(&FVector::UnitX))
			.Function("UnitY", BINDING_FUNCTION(&FVector::UnitY))
			.Function("UnitZ", BINDING_FUNCTION(&FVector::UnitZ))
			.Function("Cross", BINDING_FUNCTION(&FVector::Cross),
			          {"V2"})
			.Function("CrossProduct", BINDING_FUNCTION(&FVector::CrossProduct),
			          {"A", "B"})
			.Function("Dot", BINDING_FUNCTION(&FVector::Dot),
			          {"V"})
			.Function("Dot", BINDING_FUNCTION(&FVector::DotProduct),
			          {"A", "B"})
			.Function("Equals", BINDING_FUNCTION(&FVector::Equals),
			          {"V", "Tolerance"})
			.Function("AllComponentsEqual", BINDING_FUNCTION(&FVector::AllComponentsEqual),
			          {"Tolerance"})
			.Function("Component", BINDING_OVERLOAD(FVector::FReal(FVector::*)(int32)const, &FVector::Component),
			          {"Index"})
			.Function("GetComponentForAxis", BINDING_FUNCTION(&FVector::GetComponentForAxis),
			          {"Axis"})
			.Function("SetComponentForAxis", BINDING_FUNCTION(&FVector::SetComponentForAxis),
			          {"Axis", "Component"})
			.Function("Set", BINDING_FUNCTION(&FVector::Set),
			          {"InX", "InY", "InZ"})
			.Function("GetMax", BINDING_FUNCTION(&FVector::GetMax))
			.Function("GetAbsMax", BINDING_FUNCTION(&FVector::GetAbsMax))
			.Function("GetMin", BINDING_FUNCTION(&FVector::GetMin))
			.Function("GetAbsMin", BINDING_FUNCTION(&FVector::GetAbsMin))
			.Function("ComponentMin", BINDING_FUNCTION(&FVector::ComponentMin),
			          {"Other"})
			.Function("ComponentMax", BINDING_FUNCTION(&FVector::ComponentMax),
			          {"Other"})
			.Function("GetAbs", BINDING_FUNCTION(&FVector::GetAbs))
			.Function("Size", BINDING_FUNCTION(&FVector::Size))
			.Function("Length", BINDING_FUNCTION(&FVector::Length))
			.Function("SizeSquared", BINDING_FUNCTION(&FVector::SizeSquared))
			.Function("SquaredLength", BINDING_FUNCTION(&FVector::SquaredLength))
			.Function("Size2D", BINDING_FUNCTION(&FVector::Size2D))
			.Function("SizeSquared2D", BINDING_FUNCTION(&FVector::SizeSquared2D))
			.Function("IsNearlyZero", BINDING_FUNCTION(&FVector::IsNearlyZero),
			          {"Tolerance"})
			.Function("IsZero", BINDING_FUNCTION(&FVector::IsZero))
			.Function("IsUnit", BINDING_FUNCTION(&FVector::IsUnit),
			          {"LengthSquaredTolerance"})
			.Function("IsNormalized", BINDING_FUNCTION(&FVector::IsNormalized))
			.Function("Normalize", BINDING_FUNCTION(&FVector::Normalize),
			          {"Tolerance"})
			.Function("GetUnsafeNormal", BINDING_FUNCTION(&FVector::GetUnsafeNormal))
			.Function("GetSafeNormal", BINDING_FUNCTION(&FVector::GetSafeNormal),
			          {"Tolerance", "ResultIfZero"})
			.Function("GetSafeNormal2D", BINDING_FUNCTION(&FVector::GetSafeNormal2D),
			          {"Tolerance", "ResultIfZero"})
			.Function("ToDirectionAndLength",
			          BINDING_OVERLOAD(void(FVector::*)(FVector&, double&)const, &FVector::ToDirectionAndLength),
			          {"OutDir", "OutLength"})
			.Function("ToDirectionAndLength",
			          BINDING_OVERLOAD(void(FVector::*)(FVector&, float&)const, &FVector::ToDirectionAndLength),
			          {"OutDir", "OutLength"})
			.Function("GetSignVector", BINDING_FUNCTION(&FVector::GetSignVector))
			.Function("Projection", BINDING_FUNCTION(&FVector::Projection))
			.Function("GetUnsafeNormal2D", BINDING_FUNCTION(&FVector::GetUnsafeNormal2D))
			.Function("GridSnap", BINDING_FUNCTION(&FVector::GridSnap),
			          {"GridSz"})
			.Function("BoundToCube", BINDING_FUNCTION(&FVector::BoundToCube),
			          {"Radius"})
			.Function("BoundToBox", BINDING_FUNCTION(&FVector::BoundToBox),
			          {"Min", "Max"})
			.Function("GetClampedToSize", BINDING_FUNCTION(&FVector::GetClampedToSize),
			          {"Min", "Max"})
			.Function("GetClampedToSize2D", BINDING_FUNCTION(&FVector::GetClampedToSize2D),
			          {"Min", "Max"})
			.Function("GetClampedToMaxSize", BINDING_FUNCTION(&FVector::GetClampedToMaxSize),
			          {"MaxSize"})
			.Function("GetClampedToMaxSize2D", BINDING_FUNCTION(&FVector::GetClampedToMaxSize2D),
			          {"MaxSize"})
			.Function("AddBounded", BINDING_FUNCTION(&FVector::AddBounded),
			          {"V", "Radius"})
			.Function("Reciprocal", BINDING_FUNCTION(&FVector::Reciprocal))
			.Function("IsUniform", BINDING_FUNCTION(&FVector::IsUniform),
			          {"Tolerance"})
			.Function("MirrorByVector", BINDING_FUNCTION(&FVector::MirrorByVector),
			          {"MirrorNormal"})
			.Function("MirrorByPlane", BINDING_FUNCTION(&FVector::MirrorByPlane),
			          {"Plane"})
			.Function("RotateAngleAxis", BINDING_FUNCTION(&FVector::RotateAngleAxis),
			          {"AngleDeg", "Axis"})
			.Function("CosineAngle2D", BINDING_FUNCTION(&FVector::CosineAngle2D),
			          {"B"})
			.Function("ProjectOnTo", BINDING_FUNCTION(&FVector::ProjectOnTo),
			          {"A"})
			.Function("ProjectOnToNormal", BINDING_FUNCTION(&FVector::ProjectOnToNormal),
			          {"Normal"})
			.Function("ToOrientationRotator", BINDING_FUNCTION(&FVector::ToOrientationRotator))
			.Function("ToOrientationQuat", BINDING_FUNCTION(&FVector::ToOrientationQuat))
			.Function("Rotation", BINDING_FUNCTION(&FVector::Rotation))
			.Function("FindBestAxisVectors", BINDING_FUNCTION(&FVector::FindBestAxisVectors),
			          {"Axis1", "Axis2"})
			.Function("UnwindEuler", BINDING_FUNCTION(&FVector::UnwindEuler))
			.Function("ContainsNaN", BINDING_FUNCTION(&FVector::ContainsNaN))
			.Function("ToString", BINDING_FUNCTION(&FVector::ToString))
			.Function("ToText", BINDING_FUNCTION(&FVector::ToText))
			.Function("ToCompactString", BINDING_FUNCTION(&FVector::ToCompactString))
			.Function("ToCompactText", BINDING_FUNCTION(&FVector::ToCompactText))
			.Function("InitFromString", BINDING_FUNCTION(&FVector::InitFromString),
			          {"InSourceString"})
			.Function("InitFromCompactString", BINDING_FUNCTION(&FVector::InitFromCompactString),
			          {"InSourceString"})
			.Function("UnitCartesianToSpherical", BINDING_FUNCTION(&FVector::UnitCartesianToSpherical))
			.Function("HeadingAngle", BINDING_FUNCTION(&FVector::HeadingAngle))
			.Function("CreateOrthonormalBasis", BINDING_FUNCTION(&FVector::CreateOrthonormalBasis),
			          {"XAxis", "YAxis", "ZAxis"})
			.Function("PointsAreSame", BINDING_FUNCTION(&FVector::PointsAreSame),
			          {"P", "Q"})
			.Function("PointsAreNear", BINDING_FUNCTION(&FVector::PointsAreNear),
			          {"Point1", "Point2", "Dist"})
			.Function("PointPlaneDist", BINDING_FUNCTION(&FVector::PointPlaneDist),
			          {"Point", "PlaneBase", "PlaneNormal"})
			.Function("PointPlaneProject",
			          BINDING_OVERLOAD(FVector(*)(const FVector&, const FPlane&), &FVector::PointPlaneProject),
			          {"Point", "Plane"})
			.Function("PointPlaneProject",
			          BINDING_OVERLOAD(FVector(*)(const FVector&, const FVector&, const FVector&, const FVector&),
			                           &FVector::PointPlaneProject),
			          {"Point", "A", "B", "C"})
			.Function("PointPlaneProject",
			          BINDING_OVERLOAD(FVector(*)(const FVector&, const FVector&, const FVector&),
			                           &FVector::PointPlaneProject),
			          {"Point", "PlaneBase", "PlaneNormal"})
			.Function("VectorPlaneProject", BINDING_FUNCTION(&FVector::VectorPlaneProject),
			          {"V", "PlaneNormal"})
			.Function("Dist", BINDING_FUNCTION(&FVector::Dist),
			          {"V1", "V2"})
			.Function("Distance", BINDING_FUNCTION(&FVector::Distance),
			          {"V1", "V2"})
			.Function("DistXY", BINDING_FUNCTION(&FVector::DistXY),
			          {"V1", "V2"})
			.Function("Dist2D", BINDING_FUNCTION(&FVector::Dist2D),
			          {"V1", "V2"})
			.Function("DistSquared", BINDING_FUNCTION(&FVector::DistSquared),
			          {"V1", "V2"})
			.Function("DistSquaredXY", BINDING_FUNCTION(&FVector::DistSquaredXY),
			          {"V1", "V2"})
			.Function("DistSquared2D", BINDING_FUNCTION(&FVector::DistSquared2D),
			          {"V1", "V2"})
			.Function("BoxPushOut", BINDING_FUNCTION(&FVector::BoxPushOut),
			          {"Normal", "Size"})
			.Function("Min", BINDING_FUNCTION(&FVector::Min),
			          {"A", "B"})
			.Function("Max", BINDING_FUNCTION(&FVector::Max),
			          {"A", "B"})
			.Function("Min3", BINDING_FUNCTION(&FVector::Min3),
			          {"A", "B", "C"})
			.Function("Max3", BINDING_FUNCTION(&FVector::Max3),
			          {"A", "B", "C"})
			.Function("Parallel", BINDING_FUNCTION(&FVector::Parallel),
			          {"Normal1", "Normal2", "ParallelCosineThreshold"})
			.Function("Coincident", BINDING_FUNCTION(&FVector::Coincident),
			          {"Normal1", "Normal2", "ParallelCosineThreshold"})
			.Function("Orthogonal", BINDING_FUNCTION(&FVector::Orthogonal),
			          {"Normal1", "Normal2", "OrthogonalCosineThreshold"})
			.Function("Coplanar", BINDING_FUNCTION(&FVector::Coplanar),
			          {"Base1", "Normal1", "Base2", "Normal2", "ParallelCosineThreshold"})
			.Function("Triple", BINDING_FUNCTION(&FVector::Triple),
			          {"X", "Y", "Z"})
			.Function("EvaluateBezier", BINDING_FUNCTION(&FVector::EvaluateBezier),
			          {"ControlPoints", "NumPoints", "OutPoints"})
			.Function("RadiansToDegrees", BINDING_FUNCTION(&FVector::RadiansToDegrees),
			          {"RadVector"})
			.Function("DegreesToRadians", BINDING_FUNCTION(&FVector::DegreesToRadians),
			          {"DegVector"})
			.Function("GenerateClusterCenters", BINDING_FUNCTION(&FVector::GenerateClusterCenters),
			          {"Clusters", "Points", "NumIterations", "NumConnectionsToBeValid"})
			.Register();
	}
};

static FRegisterVector RegisterVector;
