#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Macro/NamespaceMacro.h"
#include "FRegisterForceInit.h"

namespace
{
	struct FRegisterVector4
	{
		static FVector4 MultipliesImplementation(const FVector4& In, const int32 Scale)
		{
			return &In != nullptr ? In * Scale : decltype(In * Scale)();
		}

		static FVector4 MultipliesImplementation(const FVector4& In, const float Scale)
		{
			return &In != nullptr ? In * Scale : decltype(In * Scale)();
		}

		static FVector4 MultipliesImplementation(const FVector4& In, const double Scale)
		{
			return &In != nullptr ? In * Scale : decltype(In * Scale)();
		}

		static FVector4 MultipliesImplementation(const int32 Scale, const FVector4& In)
		{
			return &In != nullptr ? Scale * In : decltype(Scale * In)();
		}

		static FVector4 MultipliesImplementation(const float Scale, const FVector4& In)
		{
			return &In != nullptr ? Scale * In : decltype(Scale * In)();
		}

		static FVector4 MultipliesImplementation(const double Scale, const FVector4& In)
		{
			return &In != nullptr ? Scale * In : decltype(Scale * In)();
		}

		static FVector4 DividesImplementation(const FVector4& In, const int32 Scale)
		{
			return &In != nullptr ? In / Scale : decltype(In / Scale)();
		}

		static FVector4 DividesImplementation(const FVector4& In, const float Scale)
		{
			return &In != nullptr ? In / Scale : decltype(In / Scale)();
		}

		static FVector4 DividesImplementation(const FVector4& In, const double Scale)
		{
			return &In != nullptr ? In / Scale : decltype(In / Scale)();
		}

		FRegisterVector4()
		{
			TBindingClassBuilder<FVector4>(NAMESPACE_BINDING)
				.Constructor(BINDING_CONSTRUCTOR(FVector4, const FVector&),
				             TArray<FString>{"InVector"})
				.Constructor(BINDING_CONSTRUCTOR(FVector4, const FLinearColor&),
				             TArray<FString>{"InColor"})
				.Constructor(BINDING_CONSTRUCTOR(FVector4, const FLinearColor&, FVector4::FReal),
				             TArray<FString>{"InColor", "InOverrideW"})
				.Constructor(BINDING_CONSTRUCTOR(FVector4, FVector4::FReal, FVector4::FReal, FVector4::FReal,
				                                 FVector4::FReal),
				             TArray<FString>{"InX", "InY", "InZ", "InW"})
				.Constructor(BINDING_CONSTRUCTOR(FVector4, FVector2D, FVector2D),
				             TArray<FString>{"InXY", "InZW"})
				.Constructor(BINDING_CONSTRUCTOR(FVector4, EForceInit))
				.Subscript(BINDING_SUBSCRIPT(FVector4, FVector4::FReal, int32,
				                             TArray<FString>{"ComponentIndex"}))
				.UnaryMinus()
				.Plus()
				.Minus()
				.Multiplies()
				.Divides()
				.BitXor()
				.Function("operator *", FUNCTION_MULTIPLIES,
				          BINDING_OVERLOAD(FVector4(*)(const FVector4&, const int32), &MultipliesImplementation))
				.Function("operator *", FUNCTION_MULTIPLIES,
				          BINDING_OVERLOAD(FVector4(*)(const FVector4&, const float), &MultipliesImplementation))
				.Function("operator *", FUNCTION_MULTIPLIES,
				          BINDING_OVERLOAD(FVector4(*)(const FVector4&, const double), &MultipliesImplementation))
				.Function("operator *", FUNCTION_MULTIPLIES,
				          BINDING_OVERLOAD(FVector4(*)(const int32, const FVector4&), &MultipliesImplementation))
				.Function("operator *", FUNCTION_MULTIPLIES,
				          BINDING_OVERLOAD(FVector4(*)(const float, const FVector4&), &MultipliesImplementation))
				.Function("operator *", FUNCTION_MULTIPLIES,
				          BINDING_OVERLOAD(FVector4(*)(const double, const FVector4&), &MultipliesImplementation))
				.Function("operator /", FUNCTION_DIVIDES,
				          BINDING_OVERLOAD(FVector4(*)(const FVector4&, const int32), &DividesImplementation))
				.Function("operator /", FUNCTION_DIVIDES,
				          BINDING_OVERLOAD(FVector4(*)(const FVector4&, const float), &DividesImplementation))
				.Function("operator /", FUNCTION_DIVIDES,
				          BINDING_OVERLOAD(FVector4(*)(const FVector4&, const double), &DividesImplementation))
				.Function("Zero", BINDING_FUNCTION(&FVector4::Zero))
				.Function("One", BINDING_FUNCTION(&FVector4::One))
				.Function("Component",
				          BINDING_OVERLOAD(const FVector4::FReal&(FVector4::*)(int32)const, &FVector4::Component,
				                           TArray<FString>{"Index"}))
				.Function("Equals", BINDING_FUNCTION(&FVector4::Equals,
				                                     TArray<FString>{"V", "Tolerance"}, KINDA_SMALL_NUMBER))
				.Function("IsUnit3", BINDING_FUNCTION(&FVector4::IsUnit3,
				                                      TArray<FString>{"LengthSquaredTolerance"}, KINDA_SMALL_NUMBER))
				.Function("ToString", BINDING_FUNCTION(&FVector4::ToString,
				                                       EFunctionInteract::New))
				.Function("InitFromString", BINDING_FUNCTION(&FVector4::InitFromString,
				                                             TArray<FString>{"InSourceString"}))
				.Function("GetSafeNormal", BINDING_FUNCTION(&FVector4::GetSafeNormal,
				                                            TArray<FString>{"Tolerance"}, SMALL_NUMBER))
				.Function("GetUnsafeNormal3", BINDING_FUNCTION(&FVector4::GetUnsafeNormal3))
				.Function("ToOrientationRotator", BINDING_FUNCTION(&FVector4::ToOrientationRotator))
				.Function("ToOrientationQuat", BINDING_FUNCTION(&FVector4::ToOrientationQuat))
				.Function("Rotation", BINDING_FUNCTION(&FVector4::Rotation))
				.Function("Set", BINDING_FUNCTION(&FVector4::Set,
				                                  TArray<FString>{"InX", "InY", "InZ", "InW"}))
				.Function("Size3", BINDING_FUNCTION(&FVector4::Size3))
				.Function("SizeSquared3", BINDING_FUNCTION(&FVector4::SizeSquared3))
				.Function("Size", BINDING_FUNCTION(&FVector4::Size))
				.Function("SizeSquared", BINDING_FUNCTION(&FVector4::SizeSquared))
				.Function("ContainsNaN", BINDING_FUNCTION(&FVector4::ContainsNaN))
				.Function("IsNearlyZero3", BINDING_FUNCTION(&FVector4::IsNearlyZero3,
				                                            TArray<FString>{"Tolerance"}, KINDA_SMALL_NUMBER))
				.Function("Reflect3", BINDING_FUNCTION(&FVector4::Reflect3,
				                                       TArray<FString>{"Normal"}))
				.Function("FindBestAxisVectors3", BINDING_FUNCTION(&FVector4::FindBestAxisVectors3,
				                                                   TArray<FString>{"Axis1", "Axis2"}));
		}
	};

	[[maybe_unused]] FRegisterVector4 RegisterVector4;
}
