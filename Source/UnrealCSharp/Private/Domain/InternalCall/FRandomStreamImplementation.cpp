#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Macro/NamespaceMacro.h"

struct FRegisterRandomStream
{
	FRegisterRandomStream()
	{
		TReflectionClassBuilder<FRandomStream>(NAMESPACE_BINDING)
			.Constructor(BINDING_CONSTRUCTOR(FRandomStream, int32),
			             {"InSeed"})
			.Constructor(BINDING_CONSTRUCTOR(FRandomStream, FName),
			             {"InName"})
			.Function("Initialize", BINDING_OVERLOAD(void(FRandomStream::*)(int32), &FRandomStream::Initialize),
			          {"InSeed"})
			.Function("Initialize", BINDING_OVERLOAD(void(FRandomStream::*)(FName), &FRandomStream::Initialize),
			          {"InName"})
			.Function("Reset", BINDING_FUNCTION(&FRandomStream::Reset))
			.Function("GetInitialSeed", BINDING_FUNCTION(&FRandomStream::GetInitialSeed))
			.Function("GenerateNewSeed", BINDING_FUNCTION(&FRandomStream::GenerateNewSeed))
			.Function("GetFraction", BINDING_FUNCTION(&FRandomStream::GetFraction))
			.Function("GetUnsignedInt", BINDING_FUNCTION(&FRandomStream::GetUnsignedInt))
			.Function("GetUnitVector", BINDING_FUNCTION(&FRandomStream::GetUnitVector))
			.Function("GetCurrentSeed", BINDING_FUNCTION(&FRandomStream::GetCurrentSeed))
			.Function("FRand", BINDING_FUNCTION(&FRandomStream::FRand))
			.Function("RandHelper", BINDING_FUNCTION(&FRandomStream::RandHelper),
			          {"A"})
			.Function("RandRange", BINDING_FUNCTION(&FRandomStream::RandRange),
			          {"Min", "Max"})
			.Function("FRandRange", BINDING_FUNCTION(&FRandomStream::FRandRange),
			          {"InMin", "InMax"})
			.Function("VRand", BINDING_FUNCTION(&FRandomStream::VRand))
			.Function("RandPointInBox", BINDING_FUNCTION(&FRandomStream::RandPointInBox),
			          {"Box"})
			.Function("VRandCone",
			          BINDING_OVERLOAD(FVector(FRandomStream::*)(FVector const&, float)const,
			                           &FRandomStream::VRandCone),
			          {"Dir", "ConeHalfAngleRad"})
			.Function("VRandCone",
			          BINDING_OVERLOAD(FVector(FRandomStream::*)(FVector const&, float, float)const,
			                           &FRandomStream::VRandCone),
			          {"Dir", "HorizontalConeHalfAngleRad", "VerticalConeHalfAngleRad"})
			.Function("ToString", BINDING_FUNCTION(&FRandomStream::ToString))
			.Register();
	}
};

static FRegisterRandomStream RegisterRandomStream;
