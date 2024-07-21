#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"

namespace
{
	struct FRegisterRandomStream
	{
		FRegisterRandomStream()
		{
			TBindingClassBuilder<FRandomStream>(NAMESPACE_BINDING)
				.Constructor(BINDING_CONSTRUCTOR(FRandomStream, int32),
				             TArray<FString>{"InSeed"})
				.Constructor(BINDING_CONSTRUCTOR(FRandomStream, FName),
				             TArray<FString>{"InName"})
				.Function("Initialize", BINDING_OVERLOAD(void(FRandomStream::*)(int32), &FRandomStream::Initialize,
				                                         TArray<FString>{"InSeed"}))
				.Function("Initialize", BINDING_OVERLOAD(void(FRandomStream::*)(FName), &FRandomStream::Initialize,
				                                         TArray<FString>{"InName"}))
				.Function("Reset", BINDING_FUNCTION(&FRandomStream::Reset))
				.Function("GetInitialSeed", BINDING_FUNCTION(&FRandomStream::GetInitialSeed))
				.Function("GenerateNewSeed", BINDING_FUNCTION(&FRandomStream::GenerateNewSeed))
				.Function("GetFraction", BINDING_FUNCTION(&FRandomStream::GetFraction))
				.Function("GetUnsignedInt", BINDING_FUNCTION(&FRandomStream::GetUnsignedInt))
				.Function("GetUnitVector", BINDING_FUNCTION(&FRandomStream::GetUnitVector))
				.Function("GetCurrentSeed", BINDING_FUNCTION(&FRandomStream::GetCurrentSeed))
				.Function("FRand", BINDING_FUNCTION(&FRandomStream::FRand))
				.Function("RandHelper", BINDING_FUNCTION(&FRandomStream::RandHelper,
				                                         TArray<FString>{"A"}))
				.Function("RandRange", BINDING_FUNCTION(&FRandomStream::RandRange,
				                                        TArray<FString>{"Min", "Max"}))
				.Function("FRandRange", BINDING_FUNCTION(&FRandomStream::FRandRange,
				                                         TArray<FString>{"InMin", "InMax"}))
				.Function("VRand", BINDING_FUNCTION(&FRandomStream::VRand))
				.Function("RandPointInBox", BINDING_FUNCTION(&FRandomStream::RandPointInBox,
				                                             TArray<FString>{"Box"}))
				.Function("VRandCone",
				          BINDING_OVERLOAD(FVector(FRandomStream::*)(FVector const&, float)const,
				                           &FRandomStream::VRandCone,
				                           TArray<FString>{"Dir", "ConeHalfAngleRad"}))
				.Function("VRandCone",
				          BINDING_OVERLOAD(FVector(FRandomStream::*)(FVector const&, float, float)const,
				                           &FRandomStream::VRandCone,
				                           TArray<FString>{"Dir", "HorizontalConeHalfAngleRad",
				                           "VerticalConeHalfAngleRad"}))
				.Function("ToString", BINDING_FUNCTION(&FRandomStream::ToString,
				                                       EFunctionInteract::New));
		}
	};

	FRegisterRandomStream RegisterRandomStream;
}
