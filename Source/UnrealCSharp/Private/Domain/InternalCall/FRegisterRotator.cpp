#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"
#include "FRegisterForceInit.h"

namespace
{
	struct FRegisterRotator
	{
		static FRotator MultipliesImplementation(const FRotator& In, const int32 Scale)
		{
			return &In != nullptr ? In * Scale : decltype(In * Scale)();
		}

		static FRotator MultipliesImplementation(const FRotator& In, const float Scale)
		{
			return &In != nullptr ? In * Scale : decltype(In * Scale)();
		}

		static FRotator MultipliesImplementation(const FRotator& In, const double Scale)
		{
			return &In != nullptr ? In * Scale : decltype(In * Scale)();
		}

		FRegisterRotator()
		{
			TBindingClassBuilder<FRotator>(NAMESPACE_BINDING)
				.Constructor(BINDING_CONSTRUCTOR(FRotator, FRotator::FReal),
				             TArray<FString>{"InF"})
				.Constructor(BINDING_CONSTRUCTOR(FRotator, FRotator::FReal, FRotator::FReal, FRotator::FReal),
				             TArray<FString>{"InPitch", "InYaw", "InRoll"})
				.Constructor(BINDING_CONSTRUCTOR(FRotator, EForceInit))
				.Constructor(BINDING_CONSTRUCTOR(FRotator, FQuat),
				             TArray<FString>{"Quat"})
				.Plus()
				.Minus()
				.Function("operator *", FUNCTION_MULTIPLIES,
				          BINDING_OVERLOAD(FRotator(*)(const FRotator&, const int32), &MultipliesImplementation))
				.Function("operator *", FUNCTION_MULTIPLIES,
				          BINDING_OVERLOAD(FRotator(*)(const FRotator&, const float), &MultipliesImplementation))
				.Function("operator *", FUNCTION_MULTIPLIES,
				          BINDING_OVERLOAD(FRotator(*)(const FRotator&, const double), &MultipliesImplementation))
				.Function("IsNearlyZero", BINDING_FUNCTION(&FRotator::IsNearlyZero,
				                                           TArray<FString>{"Tolerance"}, KINDA_SMALL_NUMBER))
				.Function("IsZero", BINDING_FUNCTION(&FRotator::IsZero))
				.Function("Equals", BINDING_FUNCTION(&FRotator::IsNearlyZero,
				                                     TArray<FString>{"R", "Tolerance"}, KINDA_SMALL_NUMBER))
				.Function("Add", BINDING_FUNCTION(&FRotator::Add,
				                                  TArray<FString>{"DeltaPitch", "DeltaYaw", "DeltaRoll"}))
				.Function("GetInverse", BINDING_FUNCTION(&FRotator::GetInverse))
				.Function("GridSnap", BINDING_FUNCTION(&FRotator::GridSnap,
				                                       TArray<FString>{"RotGrid"}))
				.Function("Vector", BINDING_FUNCTION(&FRotator::Vector))
				.Function("Quaternion", BINDING_FUNCTION(&FRotator::Quaternion))
				.Function("Euler", BINDING_FUNCTION(&FRotator::Euler))
				.Function("RotateVector", BINDING_FUNCTION(&FRotator::RotateVector,
				                                           TArray<FString>{"V"}))
				.Function("UnrotateVector", BINDING_FUNCTION(&FRotator::UnrotateVector,
				                                             TArray<FString>{"V"}))
				.Function("Clamp", BINDING_FUNCTION(&FRotator::Clamp))
				.Function("GetNormalized", BINDING_FUNCTION(&FRotator::GetNormalized))
				.Function("GetDenormalized", BINDING_FUNCTION(&FRotator::GetDenormalized))
				.Function("GetComponentForAxis", BINDING_FUNCTION(&FRotator::GetComponentForAxis,
				                                                  TArray<FString>{"Axis"}))
				.Function("SetComponentForAxis", BINDING_FUNCTION(&FRotator::GetComponentForAxis,
				                                                  TArray<FString>{"Axis", "Component"}))
				.Function("Normalize", BINDING_FUNCTION(&FRotator::Normalize))
				.Function("GetWindingAndRemainder", BINDING_FUNCTION(&FRotator::GetWindingAndRemainder,
				                                                     TArray<FString>{"Winding", "Remainder"}))
				.Function("GetManhattanDistance", BINDING_FUNCTION(&FRotator::GetManhattanDistance,
				                                                   TArray<FString>{"Rotator"}))
				.Function("GetEquivalentRotator", BINDING_FUNCTION(&FRotator::GetEquivalentRotator))
				.Function("SetClosestToMe", BINDING_FUNCTION(&FRotator::SetClosestToMe,
				                                             TArray<FString>{"MakeClosest"}))
				.Function("ToString", BINDING_FUNCTION(&FRotator::ToString,
				                                       EFunctionInteract::New))
				.Function("ToCompactString", BINDING_FUNCTION(&FRotator::ToCompactString))
				.Function("InitFromString", BINDING_FUNCTION(&FRotator::InitFromString,
				                                             TArray<FString>{"InSourceString"}))
				.Function("ContainsNaN", BINDING_FUNCTION(&FRotator::ContainsNaN))
				.Function("ClampAxis", BINDING_FUNCTION(&FRotator::ClampAxis,
				                                        TArray<FString>{"Angle"}))
				.Function("NormalizeAxis", BINDING_FUNCTION(&FRotator::NormalizeAxis,
				                                            TArray<FString>{"Angle"}))
				.Function("CompressAxisToByte", BINDING_FUNCTION(&FRotator::CompressAxisToByte,
				                                                 TArray<FString>{"Angle"}))
				.Function("DecompressAxisFromByte", BINDING_FUNCTION(&FRotator::DecompressAxisFromByte,
				                                                     TArray<FString>{"Angle"}))
				.Function("CompressAxisToShort", BINDING_FUNCTION(&FRotator::CompressAxisToShort,
				                                                  TArray<FString>{"Angle"}))
				.Function("DecompressAxisFromShort", BINDING_FUNCTION(&FRotator::DecompressAxisFromShort,
				                                                      TArray<FString>{"Angle"}))
				.Function("MakeFromEuler", BINDING_FUNCTION(&FRotator::MakeFromEuler,
				                                            TArray<FString>{"Euler"}));
		}
	};

	[[maybe_unused]] FRegisterRotator RegisterRotator;
}
