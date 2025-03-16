#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

namespace
{
	struct FRegisterVector
	{
		static FVector::FReal BitOrImplementation(const FVector& In, const FVector& V)
		{
			return &In != nullptr && (&V != nullptr) ? In | V : decltype(In | V)();
		}

		static FVector MinusImplementation(const FVector& In, const int32 Bias)
		{
			return &In != nullptr ? In - Bias : decltype(In - Bias)();
		}

		static FVector MinusImplementation(const FVector& In, const float Bias)
		{
			return &In != nullptr ? In - Bias : decltype(In - Bias)();
		}

		static FVector MinusImplementation(const FVector& In, const double Bias)
		{
			return &In != nullptr ? In - Bias : decltype(In - Bias)();
		}

		static FVector PlusImplementation(const FVector& In, const int32 Bias)
		{
			return &In != nullptr ? In + Bias : decltype(In + Bias)();
		}

		static FVector PlusImplementation(const FVector& In, const float Bias)
		{
			return &In != nullptr ? In + Bias : decltype(In + Bias)();
		}

		static FVector PlusImplementation(const FVector& In, const double Bias)
		{
			return &In != nullptr ? In + Bias : decltype(In + Bias)();
		}

		static FVector MultipliesImplementation(const FVector& In, const int32 Scale)
		{
			return &In != nullptr ? In * Scale : decltype(In * Scale)();
		}

		static FVector MultipliesImplementation(const FVector& In, const float Scale)
		{
			return &In != nullptr ? In * Scale : decltype(In * Scale)();
		}

		static FVector MultipliesImplementation(const FVector& In, const double Scale)
		{
			return &In != nullptr ? In * Scale : decltype(In * Scale)();
		}

		static FVector MultipliesImplementation(const int32 Scale, const FVector& In)
		{
			return &In != nullptr ? Scale * In : decltype(Scale * In)();
		}

		static FVector MultipliesImplementation(const float Scale, const FVector& In)
		{
			return &In != nullptr ? Scale * In : decltype(Scale * In)();
		}

		static FVector MultipliesImplementation(const double Scale, const FVector& In)
		{
			return &In != nullptr ? Scale * In : decltype(Scale * In)();
		}

		static FVector DividesImplementation(const FVector& In, const int32 Scale)
		{
			return &In != nullptr ? In / Scale : decltype(In / Scale)();
		}

		static FVector DividesImplementation(const FVector& In, const float Scale)
		{
			return &In != nullptr ? In / Scale : decltype(In / Scale)();
		}

		static FVector DividesImplementation(const FVector& In, const double Scale)
		{
			return &In != nullptr ? In / Scale : decltype(In / Scale)();
		}

		FRegisterVector()
		{
			TBindingClassBuilder<FVector>(NAMESPACE_BINDING)
				.Constructor(BINDING_CONSTRUCTOR(FVector, FVector::FReal),
				             TArray<FString>{"InF"})
				.Constructor(BINDING_CONSTRUCTOR(FVector, FVector::FReal, FVector::FReal, FVector::FReal),
				             TArray<FString>{"InX", "InY", "InZ"})
				.Constructor(BINDING_CONSTRUCTOR(FVector, const FVector2D, FVector::FReal),
				             TArray<FString>{"V", "InZ"})
				.Constructor(BINDING_CONSTRUCTOR(FVector, const FVector4&),
				             TArray<FString>{"V"})
				.Constructor(BINDING_CONSTRUCTOR(FVector, const FLinearColor&),
				             TArray<FString>{"InColor"})
				.BitXor()
				.Plus()
				.Minus()
				.Multiplies()
				.Divides()
				.UnaryMinus()
				.Subscript(BINDING_SUBSCRIPT(FVector, FVector::FReal, int32,
				                             TArray<FString>{"Index"}))
				.Function("operator |", FUNCTION_BIT_OR, BINDING_FUNCTION(&BitOrImplementation))
				.Function("operator -", FUNCTION_MINUS,
				          BINDING_OVERLOAD(FVector(*)(const FVector&, const int32), &MinusImplementation))
				.Function("operator -", FUNCTION_MINUS,
				          BINDING_OVERLOAD(FVector(*)(const FVector&, const float), &MinusImplementation))
				.Function("operator -", FUNCTION_MINUS,
				          BINDING_OVERLOAD(FVector(*)(const FVector&, const double), &MinusImplementation))
				.Function("operator +", FUNCTION_PLUS,
				          BINDING_OVERLOAD(FVector(*)(const FVector&, const int32), &PlusImplementation))
				.Function("operator +", FUNCTION_PLUS,
				          BINDING_OVERLOAD(FVector(*)(const FVector&, const float), &PlusImplementation))
				.Function("operator +", FUNCTION_PLUS,
				          BINDING_OVERLOAD(FVector(*)(const FVector&, const double), &PlusImplementation))
				.Function("operator *", FUNCTION_MULTIPLIES,
				          BINDING_OVERLOAD(FVector(*)(const FVector&, const int32), &MultipliesImplementation))
				.Function("operator *", FUNCTION_MULTIPLIES,
				          BINDING_OVERLOAD(FVector(*)(const FVector&, const float), &MultipliesImplementation))
				.Function("operator *", FUNCTION_MULTIPLIES,
				          BINDING_OVERLOAD(FVector(*)(const FVector&, const double), &MultipliesImplementation))
				.Function("operator *", FUNCTION_MULTIPLIES,
				          BINDING_OVERLOAD(FVector(*)(const int32, const FVector&), &MultipliesImplementation))
				.Function("operator *", FUNCTION_MULTIPLIES,
				          BINDING_OVERLOAD(FVector(*)(const float, const FVector&), &MultipliesImplementation))
				.Function("operator *", FUNCTION_MULTIPLIES,
				          BINDING_OVERLOAD(FVector(*)(const double, const FVector&), &MultipliesImplementation))
				.Function("operator /", FUNCTION_DIVIDES,
				          BINDING_OVERLOAD(FVector(*)(const FVector&, const int32), &DividesImplementation))
				.Function("operator /", FUNCTION_DIVIDES,
				          BINDING_OVERLOAD(FVector(*)(const FVector&, const float), &DividesImplementation))
				.Function("operator /", FUNCTION_DIVIDES,
				          BINDING_OVERLOAD(FVector(*)(const FVector&, const double), &DividesImplementation))
				.Property("ZeroVector", BINDING_READONLY_PROPERTY(&FVector::ZeroVector))
				.Property("OneVector", BINDING_READONLY_PROPERTY(&FVector::OneVector))
				.Property("UpVector", BINDING_READONLY_PROPERTY(&FVector::UpVector))
				.Property("DownVector", BINDING_READONLY_PROPERTY(&FVector::DownVector))
				.Property("ForwardVector", BINDING_READONLY_PROPERTY(&FVector::ForwardVector))
				.Property("BackwardVector", BINDING_READONLY_PROPERTY(&FVector::BackwardVector))
				.Property("RightVector", BINDING_READONLY_PROPERTY(&FVector::RightVector))
				.Property("LeftVector", BINDING_READONLY_PROPERTY(&FVector::LeftVector))
				.Property("XAxisVector", BINDING_READONLY_PROPERTY(&FVector::XAxisVector))
				.Property("YAxisVector", BINDING_READONLY_PROPERTY(&FVector::YAxisVector))
				.Property("ZAxisVector", BINDING_READONLY_PROPERTY(&FVector::ZAxisVector))
				.Function("Zero", BINDING_FUNCTION(&FVector::Zero))
				.Function("One", BINDING_FUNCTION(&FVector::One))
				.Function("UnitX", BINDING_FUNCTION(&FVector::UnitX))
				.Function("UnitY", BINDING_FUNCTION(&FVector::UnitY))
				.Function("UnitZ", BINDING_FUNCTION(&FVector::UnitZ))
				.Function("Cross", BINDING_FUNCTION(&FVector::Cross,
				                                    TArray<FString>{"V2"}))
				.Function("CrossProduct", BINDING_FUNCTION(&FVector::CrossProduct,
				                                           TArray<FString>{"A", "B"}))
				.Function("Dot", BINDING_FUNCTION(&FVector::Dot,
				                                  TArray<FString>{"V"}))
				.Function("Dot", BINDING_FUNCTION(&FVector::DotProduct,
				                                  TArray<FString>{"A", "B"}))
				.Function("Equals", BINDING_FUNCTION(&FVector::Equals,
				                                     TArray<FString>{"V", "Tolerance"}, KINDA_SMALL_NUMBER))
				.Function("AllComponentsEqual", BINDING_FUNCTION(&FVector::AllComponentsEqual,
				                                                 TArray<FString>{"Tolerance"}, KINDA_SMALL_NUMBER))
				.Function("Component", BINDING_OVERLOAD(FVector::FReal(FVector::*)(int32)const, &FVector::Component,
				                                        TArray<FString>{"Index"}))
				.Function("GetComponentForAxis", BINDING_FUNCTION(&FVector::GetComponentForAxis,
				                                                  TArray<FString>{"Axis"}))
				.Function("SetComponentForAxis", BINDING_FUNCTION(&FVector::SetComponentForAxis,
				                                                  TArray<FString>{"Axis", "Component"}))
				.Function("Set", BINDING_FUNCTION(&FVector::Set,
				                                  TArray<FString>{"InX", "InY", "InZ"}))
				.Function("GetMax", BINDING_FUNCTION(&FVector::GetMax))
				.Function("GetAbsMax", BINDING_FUNCTION(&FVector::GetAbsMax))
				.Function("GetMin", BINDING_FUNCTION(&FVector::GetMin))
				.Function("GetAbsMin", BINDING_FUNCTION(&FVector::GetAbsMin))
				.Function("ComponentMin", BINDING_FUNCTION(&FVector::ComponentMin,
				                                           TArray<FString>{"Other"}))
				.Function("ComponentMax", BINDING_FUNCTION(&FVector::ComponentMax,
				                                           TArray<FString>{"Other"}))
				.Function("GetAbs", BINDING_FUNCTION(&FVector::GetAbs))
				.Function("Size", BINDING_FUNCTION(&FVector::Size))
				.Function("Length", BINDING_FUNCTION(&FVector::Length))
				.Function("SizeSquared", BINDING_FUNCTION(&FVector::SizeSquared))
				.Function("SquaredLength", BINDING_FUNCTION(&FVector::SquaredLength))
				.Function("Size2D", BINDING_FUNCTION(&FVector::Size2D))
				.Function("SizeSquared2D", BINDING_FUNCTION(&FVector::SizeSquared2D))
				.Function("IsNearlyZero", BINDING_FUNCTION(&FVector::IsNearlyZero,
				                                           TArray<FString>{"Tolerance"}, KINDA_SMALL_NUMBER))
				.Function("IsZero", BINDING_FUNCTION(&FVector::IsZero))
				.Function("IsUnit", BINDING_FUNCTION(&FVector::IsUnit,
				                                     TArray<FString>{"LengthSquaredTolerance"}, KINDA_SMALL_NUMBER))
				.Function("IsNormalized", BINDING_FUNCTION(&FVector::IsNormalized))
				.Function("Normalize", BINDING_FUNCTION(&FVector::Normalize,
				                                        TArray<FString>{"Tolerance"}, SMALL_NUMBER))
				.Function("GetUnsafeNormal", BINDING_FUNCTION(&FVector::GetUnsafeNormal))
				.Function("GetSafeNormal", BINDING_FUNCTION(&FVector::GetSafeNormal,
				                                            TArray<FString>{"Tolerance", "ResultIfZero"},
				                                            SMALL_NUMBER, FVector::ZeroVector))
				.Function("GetSafeNormal2D", BINDING_FUNCTION(&FVector::GetSafeNormal2D,
				                                              TArray<FString>{"Tolerance", "ResultIfZero"},
				                                              SMALL_NUMBER, FVector::ZeroVector))
				.Function("ToDirectionAndLength",
				          BINDING_OVERLOAD(void(FVector::*)(FVector&, double&)const, &FVector::ToDirectionAndLength,
				                           TArray<FString>{"OutDir", "OutLength"}))
				.Function("ToDirectionAndLength",
				          BINDING_OVERLOAD(void(FVector::*)(FVector&, float&)const, &FVector::ToDirectionAndLength,
				                           TArray<FString>{"OutDir", "OutLength"}))
				.Function("GetSignVector", BINDING_FUNCTION(&FVector::GetSignVector))
				.Function("Projection", BINDING_FUNCTION(&FVector::Projection))
				.Function("GetUnsafeNormal2D", BINDING_FUNCTION(&FVector::GetUnsafeNormal2D))
				.Function("GridSnap", BINDING_FUNCTION(&FVector::GridSnap,
				                                       TArray<FString>{"GridSz"}))
				.Function("BoundToCube", BINDING_FUNCTION(&FVector::BoundToCube,
				                                          TArray<FString>{"Radius"}))
				.Function("BoundToBox", BINDING_FUNCTION(&FVector::BoundToBox,
				                                         TArray<FString>{"Min", "Max"}))
				.Function("GetClampedToSize", BINDING_FUNCTION(&FVector::GetClampedToSize,
				                                               TArray<FString>{"Min", "Max"}))
				.Function("GetClampedToSize2D", BINDING_FUNCTION(&FVector::GetClampedToSize2D,
				                                                 TArray<FString>{"Min", "Max"}))
				.Function("GetClampedToMaxSize", BINDING_FUNCTION(&FVector::GetClampedToMaxSize,
				                                                  TArray<FString>{"MaxSize"}))
				.Function("GetClampedToMaxSize2D", BINDING_FUNCTION(&FVector::GetClampedToMaxSize2D,
				                                                    TArray<FString>{"MaxSize"}))
				.Function("AddBounded", BINDING_FUNCTION(&FVector::AddBounded,
				                                         TArray<FString>{"V", "Radius"}, MAX_int16))
				.Function("Reciprocal", BINDING_FUNCTION(&FVector::Reciprocal))
				.Function("IsUniform", BINDING_FUNCTION(&FVector::IsUniform,
				                                        TArray<FString>{"Tolerance"}, KINDA_SMALL_NUMBER))
				.Function("MirrorByVector", BINDING_FUNCTION(&FVector::MirrorByVector,
				                                             TArray<FString>{"MirrorNormal"}))
				.Function("MirrorByPlane", BINDING_FUNCTION(&FVector::MirrorByPlane,
				                                            TArray<FString>{"Plane"}))
				.Function("RotateAngleAxis", BINDING_FUNCTION(&FVector::RotateAngleAxis,
				                                              TArray<FString>{"AngleDeg", "Axis"}))
				.Function("CosineAngle2D", BINDING_FUNCTION(&FVector::CosineAngle2D,
				                                            TArray<FString>{"B"}))
				.Function("ProjectOnTo", BINDING_FUNCTION(&FVector::ProjectOnTo,
				                                          TArray<FString>{"A"}))
				.Function("ProjectOnToNormal", BINDING_FUNCTION(&FVector::ProjectOnToNormal,
				                                                TArray<FString>{"Normal"}))
				.Function("ToOrientationRotator", BINDING_FUNCTION(&FVector::ToOrientationRotator))
				.Function("ToOrientationQuat", BINDING_FUNCTION(&FVector::ToOrientationQuat))
				.Function("Rotation", BINDING_FUNCTION(&FVector::Rotation))
				.Function("FindBestAxisVectors", BINDING_FUNCTION(&FVector::FindBestAxisVectors,
				                                                  TArray<FString>{"Axis1", "Axis2"}))
				.Function("UnwindEuler", BINDING_FUNCTION(&FVector::UnwindEuler))
				.Function("ContainsNaN", BINDING_FUNCTION(&FVector::ContainsNaN))
				.Function("ToString", BINDING_FUNCTION(&FVector::ToString,
				                                       EFunctionInteract::New))
				.Function("ToText", BINDING_FUNCTION(&FVector::ToText))
				.Function("ToCompactString", BINDING_FUNCTION(&FVector::ToCompactString))
				.Function("ToCompactText", BINDING_FUNCTION(&FVector::ToCompactText))
				.Function("InitFromString", BINDING_FUNCTION(&FVector::InitFromString,
				                                             TArray<FString>{"InSourceString"}))
				.Function("InitFromCompactString", BINDING_FUNCTION(&FVector::InitFromCompactString,
				                                                    TArray<FString>{"InSourceString"}))
				.Function("UnitCartesianToSpherical", BINDING_FUNCTION(&FVector::UnitCartesianToSpherical))
				.Function("HeadingAngle", BINDING_FUNCTION(&FVector::HeadingAngle))
				.Function("CreateOrthonormalBasis", BINDING_FUNCTION(&FVector::CreateOrthonormalBasis,
				                                                     TArray<FString>{"XAxis", "YAxis", "ZAxis"}))
				.Function("PointsAreSame", BINDING_FUNCTION(&FVector::PointsAreSame,
				                                            TArray<FString>{"P", "Q"}))
				.Function("PointsAreNear", BINDING_FUNCTION(&FVector::PointsAreNear,
				                                            TArray<FString>{"Point1", "Point2", "Dist"}))
				.Function("PointPlaneDist", BINDING_FUNCTION(&FVector::PointPlaneDist,
				                                             TArray<FString>{"Point", "PlaneBase", "PlaneNormal"}))
				.Function("PointPlaneProject",
				          BINDING_OVERLOAD(FVector(*)(const FVector&, const FPlane&), &FVector::PointPlaneProject,
				                           TArray<FString>{"Point", "Plane"}))
				.Function("PointPlaneProject",
				          BINDING_OVERLOAD(FVector(*)(const FVector&, const FVector&, const FVector&, const FVector&),
				                           &FVector::PointPlaneProject,
				                           TArray<FString>{"Point", "A", "B", "C"}))
				.Function("PointPlaneProject",
				          BINDING_OVERLOAD(FVector(*)(const FVector&, const FVector&, const FVector&),
				                           &FVector::PointPlaneProject,
				                           TArray<FString>{"Point", "PlaneBase", "PlaneNormal"}))
				.Function("VectorPlaneProject", BINDING_FUNCTION(&FVector::VectorPlaneProject,
				                                                 TArray<FString>{"V", "PlaneNormal"}))
				.Function("Dist", BINDING_FUNCTION(&FVector::Dist,
				                                   TArray<FString>{"V1", "V2"}))
				.Function("Distance", BINDING_FUNCTION(&FVector::Distance,
				                                       TArray<FString>{"V1", "V2"}))
				.Function("DistXY", BINDING_FUNCTION(&FVector::DistXY,
				                                     TArray<FString>{"V1", "V2"}))
				.Function("Dist2D", BINDING_FUNCTION(&FVector::Dist2D,
				                                     TArray<FString>{"V1", "V2"}))
				.Function("DistSquared", BINDING_FUNCTION(&FVector::DistSquared,
				                                          TArray<FString>{"V1", "V2"}))
				.Function("DistSquaredXY", BINDING_FUNCTION(&FVector::DistSquaredXY,
				                                            TArray<FString>{"V1", "V2"}))
				.Function("DistSquared2D", BINDING_FUNCTION(&FVector::DistSquared2D,
				                                            TArray<FString>{"V1", "V2"}))
				.Function("BoxPushOut", BINDING_FUNCTION(&FVector::BoxPushOut,
				                                         TArray<FString>{"Normal", "Size"}))
				.Function("Min", BINDING_FUNCTION(&FVector::Min,
				                                  TArray<FString>{"A", "B"}))
				.Function("Max", BINDING_FUNCTION(&FVector::Max,
				                                  TArray<FString>{"A", "B"}))
				.Function("Min3", BINDING_FUNCTION(&FVector::Min3,
				                                   TArray<FString>{"A", "B", "C"}))
				.Function("Max3", BINDING_FUNCTION(&FVector::Max3,
				                                   TArray<FString>{"A", "B", "C"}))
				.Function("Parallel", BINDING_FUNCTION(&FVector::Parallel,
				                                       TArray<FString>{"Normal1", "Normal2", "ParallelCosineThreshold"},
				                                       THRESH_NORMALS_ARE_PARALLEL)
				)
				.Function("Coincident", BINDING_FUNCTION(&FVector::Coincident,
				                                         TArray<FString>{"Normal1", "Normal2",
				                                         "ParallelCosineThreshold"},
				                                         THRESH_NORMALS_ARE_PARALLEL)
				)
				.Function("Orthogonal", BINDING_FUNCTION(&FVector::Orthogonal,
				                                         TArray<FString>{"Normal1", "Normal2",
				                                         "OrthogonalCosineThreshold"},
				                                         THRESH_NORMALS_ARE_ORTHOGONAL)
				)
				.Function("Coplanar", BINDING_FUNCTION(&FVector::Coplanar,
				                                       TArray<FString>{"Base1", "Normal1",
				                                       "Base2", "Normal2", "ParallelCosineThreshold"},
				                                       THRESH_NORMALS_ARE_PARALLEL)
				)
				.Function("Triple", BINDING_FUNCTION(&FVector::Triple,
				                                     TArray<FString>{"X", "Y", "Z"}))
				.Function("EvaluateBezier", BINDING_FUNCTION(&FVector::EvaluateBezier,
				                                             TArray<FString>{"ControlPoints", "NumPoints",
				                                             "OutPoints"}))
				.Function("RadiansToDegrees", BINDING_FUNCTION(&FVector::RadiansToDegrees,
				                                               TArray<FString>{"RadVector"}))
				.Function("DegreesToRadians", BINDING_FUNCTION(&FVector::DegreesToRadians,
				                                               TArray<FString>{"DegVector"}))
				.Function("GenerateClusterCenters", BINDING_FUNCTION(&FVector::GenerateClusterCenters,
				                                                     TArray<FString>{"Clusters", "Points",
				                                                     "NumIterations", "NumConnectionsToBeValid"}));
		}
	};

	[[maybe_unused]] FRegisterVector RegisterVector;
}
