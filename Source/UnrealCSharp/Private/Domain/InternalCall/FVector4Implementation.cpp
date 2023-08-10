#include "Domain/InternalCall/FVector4Implementation.h"
#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/ScriptStruct/TScriptStruct.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterVector4
{
	FRegisterVector4()
	{
		TReflectionClassBuilder<FVector4>(NAMESPACE_LIBRARY)
			.Function("GetComponent", FVector4Implementation::Vector4_GetComponentImplementation)
			.Function("SetComponent", FVector4Implementation::Vector4_SetComponentImplementation)
			.Function("Negated", FVector4Implementation::Vector4_NegatedImplementation)
			.Function("Add", FVector4Implementation::Vector4_AddImplementation)
			.Function("Subtract", FVector4Implementation::Vector4_SubtractImplementation)
			.Function("MultiplyScale", FVector4Implementation::Vector4_MultiplyScaleImplementation)
			.Function("DivideScale", FVector4Implementation::Vector4_DivideScaleImplementation)
			.Function("Divide", FVector4Implementation::Vector4_DivideImplementation)
			.Function("Multiply", FVector4Implementation::Vector4_MultiplyImplementation)
			.Function("Dot3", FVector4Implementation::Vector4_Dot3Implementation)
			.Function("Dot4", FVector4Implementation::Vector4_Dot4Implementation)
			.Function("Equality", FVector4Implementation::Vector4_EqualityImplementation)
			.Function("Inequality", FVector4Implementation::Vector4_InequalityImplementation)
			.Function("CrossProduct", FVector4Implementation::Vector4_CrossProductImplementation)
			.Function("Component", FVector4Implementation::Vector4_ComponentImplementation)
			.Function("Equals", FVector4Implementation::Vector4_EqualsImplementation)
			.Function("IsUnit3", FVector4Implementation::Vector4_IsUnit3Implementation)
			.Function("ToString", FVector4Implementation::Vector4_ToStringImplementation)
			.Function("InitFromString", FVector4Implementation::Vector4_InitFromStringImplementation)
			.Function("GetSafeNormal", FVector4Implementation::Vector4_GetSafeNormalImplementation)
			.Function("GetUnsafeNormal3", FVector4Implementation::Vector4_GetUnsafeNormal3Implementation)
			.Function("ToOrientationRotator", FVector4Implementation::Vector4_ToOrientationRotatorImplementation)
			.Function("ToOrientationQuat", FVector4Implementation::Vector4_ToOrientationQuatImplementation)
			.Function("Rotation", FVector4Implementation::Vector4_RotationImplementation)
			.Function("Set", FVector4Implementation::Vector4_SetImplementation)
			.Function("Size3", FVector4Implementation::Vector4_Size3Implementation)
			.Function("SizeSquared3", FVector4Implementation::Vector4_SizeSquared3Implementation)
			.Function("Size", FVector4Implementation::Vector4_SizeImplementation)
			.Function("SizeSquared", FVector4Implementation::Vector4_SizeSquaredImplementation)
			.Function("ContainsNaN", FVector4Implementation::Vector4_ContainsNaNImplementation)
			.Function("IsNearlyZero3", FVector4Implementation::Vector4_IsNearlyZero3Implementation)
			.Function("Reflect3", FVector4Implementation::Vector4_Reflect3Implementation)
			.Function("FindBestAxisVectors3", FVector4Implementation::Vector4_FindBestAxisVectors3Implementation)
			.Register();
	}
};

static FRegisterVector4 RegisterVector4;

FVector4Implementation::LwcType FVector4Implementation::Vector4_GetComponentImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const int32 ComponentIndex)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(
		InGarbageCollectionHandle);

	if (Vector4 != nullptr)
	{
		return Vector4->operator[](ComponentIndex);
	}

	return 0.f;
}

void FVector4Implementation::Vector4_SetComponentImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const int32 ComponentIndex, const LwcType InValue)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(
		InGarbageCollectionHandle);

	if (Vector4 != nullptr)
	{
		Vector4->operator[](ComponentIndex) = InValue;
	}
}

void FVector4Implementation::Vector4_NegatedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                           MonoObject** OutValue)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector4, FVector4>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(NewMonoObject);

	if (Vector4 != nullptr && OutVector4 != nullptr)
	{
		*OutVector4 = Vector4->operator-();
	}
}

void FVector4Implementation::Vector4_AddImplementation(const FGarbageCollectionHandle A,
                                                       const FGarbageCollectionHandle B, MonoObject** OutValue)
{
	const auto Vector4A = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(A);

	const auto Vector4B = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(B);

	const auto FoundMonoClass = TPropertyClass<FVector4, FVector4>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(NewMonoObject);

	if (Vector4A != nullptr && Vector4B != nullptr && OutVector4 != nullptr)
	{
		*OutVector4 = Vector4A->operator+(*Vector4B);
	}
}

void FVector4Implementation::Vector4_SubtractImplementation(const FGarbageCollectionHandle A,
                                                            const FGarbageCollectionHandle B, MonoObject** OutValue)
{
	const auto Vector4A = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(A);

	const auto Vector4B = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(B);

	const auto FoundMonoClass = TPropertyClass<FVector4, FVector4>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(NewMonoObject);

	if (Vector4A != nullptr && Vector4B != nullptr && OutVector4 != nullptr)
	{
		*OutVector4 = Vector4A->operator-(*Vector4B);
	}
}

void FVector4Implementation::Vector4_MultiplyScaleImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const LwcType Scale, MonoObject** OutValue)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector4, FVector4>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(NewMonoObject);

	if (Vector4 != nullptr && OutVector4 != nullptr)
	{
		*OutVector4 = Vector4->operator*(Scale);
	}
}

void FVector4Implementation::Vector4_DivideScaleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                               const LwcType Scale, MonoObject** OutValue)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector4, FVector4>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(NewMonoObject);

	if (Vector4 != nullptr && OutVector4 != nullptr)
	{
		*OutVector4 = Vector4->operator/(Scale);
	}
}

void FVector4Implementation::Vector4_DivideImplementation(const FGarbageCollectionHandle A,
                                                          const FGarbageCollectionHandle B, MonoObject** OutValue)
{
	const auto Vector4A = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(A);

	const auto Vector4B = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(B);

	const auto FoundMonoClass = TPropertyClass<FVector4, FVector4>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(NewMonoObject);

	if (Vector4A != nullptr && Vector4B != nullptr && OutVector4 != nullptr)
	{
		*OutVector4 = Vector4A->operator/(*Vector4B);
	}
}

void FVector4Implementation::Vector4_MultiplyImplementation(const FGarbageCollectionHandle A,
                                                            const FGarbageCollectionHandle B, MonoObject** OutValue)
{
	const auto Vector4A = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(A);

	const auto Vector4B = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(B);

	const auto FoundMonoClass = TPropertyClass<FVector4, FVector4>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(NewMonoObject);

	if (Vector4A != nullptr && Vector4B != nullptr && OutVector4 != nullptr)
	{
		*OutVector4 = Vector4A->operator*(*Vector4B);
	}
}

FVector4Implementation::LwcType FVector4Implementation::Vector4_Dot3Implementation(
	const FGarbageCollectionHandle A, const FGarbageCollectionHandle B)
{
	const auto Vector4A = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(A);

	const auto Vector4B = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(B);

	if (Vector4A != nullptr && Vector4B != nullptr)
	{
		return Dot3(*Vector4A, *Vector4B);
	}

	return 0.f;
}

FVector4Implementation::LwcType FVector4Implementation::Vector4_Dot4Implementation(
	const FGarbageCollectionHandle A, const FGarbageCollectionHandle B)
{
	const auto Vector4A = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(A);

	const auto Vector4B = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(B);

	if (Vector4A != nullptr && Vector4B != nullptr)
	{
		return Dot4(*Vector4A, *Vector4B);
	}

	return 0.f;
}

bool FVector4Implementation::Vector4_EqualityImplementation(const FGarbageCollectionHandle A,
                                                            const FGarbageCollectionHandle B)
{
	const auto Vector4A = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(A);

	const auto Vector4B = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(B);

	if (Vector4A != nullptr && Vector4B != nullptr)
	{
		return Vector4A->operator==(*Vector4B);
	}

	return false;
}

bool FVector4Implementation::Vector4_InequalityImplementation(const FGarbageCollectionHandle A,
                                                              const FGarbageCollectionHandle B)
{
	const auto Vector4A = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(A);

	const auto Vector4B = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(B);

	if (Vector4A != nullptr && Vector4B != nullptr)
	{
		return Vector4A->operator!=(*Vector4B);
	}

	return false;
}

void FVector4Implementation::Vector4_CrossProductImplementation(const FGarbageCollectionHandle A,
                                                                const FGarbageCollectionHandle B, MonoObject** OutValue)
{
	const auto Vector4A = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(A);

	const auto Vector4B = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(B);

	const auto FoundMonoClass = TPropertyClass<FVector4, FVector4>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(NewMonoObject);

	if (Vector4A != nullptr && Vector4B != nullptr && OutVector4 != nullptr)
	{
		*OutVector4 = Vector4A->operator^(*Vector4B);
	}
}

FVector4Implementation::LwcType FVector4Implementation::Vector4_ComponentImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const int32 Index)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(
		InGarbageCollectionHandle);

	if (Vector4 != nullptr)
	{
		return Vector4->Component(Index);
	}

	return 0.f;
}

bool FVector4Implementation::Vector4_EqualsImplementation(const FGarbageCollectionHandle A,
                                                          const FGarbageCollectionHandle B, const LwcType Tolerance)
{
	const auto Vector4A = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(A);

	const auto Vector4B = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(B);

	if (Vector4A != nullptr && Vector4B != nullptr)
	{
		return Vector4A->Equals(*Vector4B, Tolerance);
	}

	return false;
}

bool FVector4Implementation::Vector4_IsUnit3Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                           const LwcType LengthSquaredTolerance)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(
		InGarbageCollectionHandle);

	if (Vector4 != nullptr)
	{
		return Vector4->IsUnit3(LengthSquaredTolerance);
	}

	return false;
}

void FVector4Implementation::Vector4_ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                            MonoObject** OutValue)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(
		InGarbageCollectionHandle);

	if (Vector4 != nullptr)
	{
		const auto ResultString = Vector4->ToString();

		const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

bool FVector4Implementation::Vector4_InitFromStringImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject* InSourceString)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(
		InGarbageCollectionHandle);

	if (Vector4 != nullptr && InSourceString != nullptr)
	{
		return Vector4->InitFromString(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(InSourceString, nullptr))));
	}

	return false;
}

void FVector4Implementation::Vector4_GetSafeNormalImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const LwcType Tolerance, MonoObject** OutValue)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector4, FVector4>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(NewMonoObject);

	if (Vector4 != nullptr && OutVector4 != nullptr)
	{
		*OutVector4 = Vector4->GetSafeNormal(Tolerance);
	}
}

void FVector4Implementation::Vector4_GetUnsafeNormal3Implementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector4, FVector4>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(NewMonoObject);

	if (Vector4 != nullptr && OutVector4 != nullptr)
	{
		*OutVector4 = Vector4->GetUnsafeNormal3();
	}
}

void FVector4Implementation::Vector4_ToOrientationRotatorImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FRotator, FRotator>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Vector4 != nullptr && OutRotator != nullptr)
	{
		*OutRotator = Vector4->ToOrientationRotator();
	}
}

void FVector4Implementation::Vector4_ToOrientationQuatImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FQuat, FQuat>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (Vector4 != nullptr && OutQuat != nullptr)
	{
		*OutQuat = Vector4->ToOrientationQuat();
	}
}

void FVector4Implementation::Vector4_RotationImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                            MonoObject** OutValue)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FRotator, FRotator>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Vector4 != nullptr && OutRotator != nullptr)
	{
		*OutRotator = Vector4->Rotation();
	}
}

void FVector4Implementation::Vector4_SetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                       const LwcType InX, const LwcType InY, const LwcType InZ,
                                                       const LwcType InW)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(
		InGarbageCollectionHandle);

	if (Vector4 != nullptr)
	{
		return Vector4->Set(InX, InY, InZ, InW);
	}
}

FVector4Implementation::LwcType FVector4Implementation::Vector4_Size3Implementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(
		InGarbageCollectionHandle);

	if (Vector4 != nullptr)
	{
		return Vector4->Size3();
	}

	return 0.f;
}

FVector4Implementation::LwcType FVector4Implementation::Vector4_SizeSquared3Implementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(
		InGarbageCollectionHandle);

	if (Vector4 != nullptr)
	{
		return Vector4->SizeSquared3();
	}

	return 0.f;
}

FVector4Implementation::LwcType FVector4Implementation::Vector4_SizeImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(
		InGarbageCollectionHandle);

	if (Vector4 != nullptr)
	{
		return Vector4->Size();
	}

	return 0.f;
}

FVector4Implementation::LwcType FVector4Implementation::Vector4_SizeSquaredImplementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(
		InGarbageCollectionHandle);

	if (Vector4 != nullptr)
	{
		return Vector4->SizeSquared();
	}

	return 0.f;
}

bool FVector4Implementation::Vector4_ContainsNaNImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(
		InGarbageCollectionHandle);

	if (Vector4 != nullptr)
	{
		return Vector4->ContainsNaN();
	}

	return false;
}

bool FVector4Implementation::Vector4_IsNearlyZero3Implementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, const LwcType Tolerance)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(
		InGarbageCollectionHandle);

	if (Vector4 != nullptr)
	{
		return Vector4->IsNearlyZero3(Tolerance);
	}

	return false;
}

void FVector4Implementation::Vector4_Reflect3Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
                                                            const MonoObject* Normal, MonoObject** OutValue)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(
		InGarbageCollectionHandle);

	const auto Vector4Normal = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(Normal);

	const auto FoundMonoClass = TPropertyClass<FVector4, FVector4>::Get();

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(NewMonoObject);

	if (Vector4 != nullptr && Vector4Normal != nullptr && OutVector4 != nullptr)
	{
		*OutVector4 = Vector4->Reflect3(*Vector4Normal);
	}
}

void FVector4Implementation::Vector4_FindBestAxisVectors3Implementation(
	const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** Axis1, MonoObject** Axis2)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(
		InGarbageCollectionHandle);

	const auto FoundMonoClass = TPropertyClass<FVector4, FVector4>::Get();

	const auto NewMonoObject1 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*Axis1 = NewMonoObject1;

	const auto OutAxis1Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FVector4>(NewMonoObject1);

	const auto NewMonoObject2 = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*Axis2 = NewMonoObject2;

	const auto OutAxis2Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<
		UScriptStruct, FVector4>(NewMonoObject2);

	if (Vector4 != nullptr && OutAxis1Vector4 != nullptr && OutAxis2Vector4 != nullptr)
	{
		Vector4->FindBestAxisVectors3(*OutAxis1Vector4, *OutAxis2Vector4);
	}
}
