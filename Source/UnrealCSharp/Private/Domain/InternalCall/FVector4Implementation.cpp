#include "Domain/InternalCall/FVector4Implementation.h"
#include "Binding/Class/TScriptStructBuilder.inl"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/ClassMacro.h"
#include "Macro/ClassMacro.h"
#include "Macro/NamespaceMacro.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"

struct FRegisterVector4
{
	FRegisterVector4()
	{
		TScriptStructBuilder<FVector4>(NAMESPACE_LIBRARY)
			.Function("GetComponent", static_cast<void*>(FVector4Implementation::Vector4_GetComponentImplementation))
			.Function("SetComponent", static_cast<void*>(FVector4Implementation::Vector4_SetComponentImplementation))
			.Function("Negated", static_cast<void*>(FVector4Implementation::Vector4_NegatedImplementation))
			.Function("Add", static_cast<void*>(FVector4Implementation::Vector4_AddImplementation))
			.Function("Subtract", static_cast<void*>(FVector4Implementation::Vector4_SubtractImplementation))
			.Function("MultiplyScale", static_cast<void*>(FVector4Implementation::Vector4_MultiplyScaleImplementation))
			.Function("DivideScale", static_cast<void*>(FVector4Implementation::Vector4_DivideScaleImplementation))
			.Function("Divide", static_cast<void*>(FVector4Implementation::Vector4_DivideImplementation))
			.Function("Multiply", static_cast<void*>(FVector4Implementation::Vector4_MultiplyImplementation))
			.Function("Dot3", static_cast<void*>(FVector4Implementation::Vector4_Dot3Implementation))
			.Function("Dot4", static_cast<void*>(FVector4Implementation::Vector4_Dot4Implementation))
			.Function("Equality", static_cast<void*>(FVector4Implementation::Vector4_EqualityImplementation))
			.Function("Inequality", static_cast<void*>(FVector4Implementation::Vector4_InequalityImplementation))
			.Function("CrossProduct", static_cast<void*>(FVector4Implementation::Vector4_CrossProductImplementation))
			.Function("Component", static_cast<void*>(FVector4Implementation::Vector4_ComponentImplementation))
			.Function("Equals", static_cast<void*>(FVector4Implementation::Vector4_EqualsImplementation))
			.Function("IsUnit3", static_cast<void*>(FVector4Implementation::Vector4_IsUnit3Implementation))
			.Function("ToString", static_cast<void*>(FVector4Implementation::Vector4_ToStringImplementation))
			.Function("InitFromString",
			          static_cast<void*>(FVector4Implementation::Vector4_InitFromStringImplementation))
			.Function("GetSafeNormal", static_cast<void*>(FVector4Implementation::Vector4_GetSafeNormalImplementation))
			.Function("GetUnsafeNormal3",
			          static_cast<void*>(FVector4Implementation::Vector4_GetUnsafeNormal3Implementation))
			.Function("ToOrientationRotator",
			          static_cast<void*>(FVector4Implementation::Vector4_ToOrientationRotatorImplementation))
			.Function("ToOrientationQuat",
			          static_cast<void*>(FVector4Implementation::Vector4_ToOrientationQuatImplementation))
			.Function("Rotation", static_cast<void*>(FVector4Implementation::Vector4_RotationImplementation))
			.Function("Set", static_cast<void*>(FVector4Implementation::Vector4_SetImplementation))
			.Function("Size3", static_cast<void*>(FVector4Implementation::Vector4_Size3Implementation))
			.Function("SizeSquared3", static_cast<void*>(FVector4Implementation::Vector4_SizeSquared3Implementation))
			.Function("Size", static_cast<void*>(FVector4Implementation::Vector4_SizeImplementation))
			.Function("SizeSquared", static_cast<void*>(FVector4Implementation::Vector4_SizeSquaredImplementation))
			.Function("ContainsNaN", static_cast<void*>(FVector4Implementation::Vector4_ContainsNaNImplementation))
			.Function("IsNearlyZero3", static_cast<void*>(FVector4Implementation::Vector4_IsNearlyZero3Implementation))
			.Function("Reflect3", static_cast<void*>(FVector4Implementation::Vector4_Reflect3Implementation))
			.Function("FindBestAxisVectors3",
			          static_cast<void*>(FVector4Implementation::Vector4_FindBestAxisVectors3Implementation))
			.Register();
	}
};

static FRegisterVector4 RegisterVector4;

float FVector4Implementation::Vector4_GetComponentImplementation(const MonoObject* InMonoObject,
                                                                 const int32 ComponentIndex)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(InMonoObject);

	if (Vector4 != nullptr)
	{
		return Vector4->operator[](ComponentIndex);
	}

	return 0.f;
}

void FVector4Implementation::Vector4_SetComponentImplementation(const MonoObject* InMonoObject,
                                                                const int32 ComponentIndex, const float InValue)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(InMonoObject);

	if (Vector4 != nullptr)
	{
		Vector4->operator[](ComponentIndex) = InValue;
	}
}

void FVector4Implementation::Vector4_NegatedImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector4)),
		CLASS_SCRIPT_STRUCT_NAME(FVector4));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(NewMonoObject);

	if (Vector4 != nullptr && OutVector4 != nullptr)
	{
		*OutVector4 = Vector4->operator-();
	}
}

void FVector4Implementation::Vector4_AddImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue)
{
	const auto Vector4A = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(A);

	const auto Vector4B = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(B);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector4)),
		CLASS_SCRIPT_STRUCT_NAME(FVector4));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(NewMonoObject);

	if (Vector4A != nullptr && Vector4B != nullptr && OutVector4 != nullptr)
	{
		*OutVector4 = Vector4A->operator+(*Vector4B);
	}
}

void FVector4Implementation::Vector4_SubtractImplementation(const MonoObject* A, const MonoObject* B,
                                                            MonoObject** OutValue)
{
	const auto Vector4A = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(A);

	const auto Vector4B = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(B);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector4)),
		CLASS_SCRIPT_STRUCT_NAME(FVector4));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(NewMonoObject);

	if (Vector4A != nullptr && Vector4B != nullptr && OutVector4 != nullptr)
	{
		*OutVector4 = Vector4A->operator-(*Vector4B);
	}
}

void FVector4Implementation::Vector4_MultiplyScaleImplementation(const MonoObject* InMonoObject, const float Scale,
                                                                 MonoObject** OutValue)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector4)),
		CLASS_SCRIPT_STRUCT_NAME(FVector4));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(NewMonoObject);

	if (Vector4 != nullptr && OutVector4 != nullptr)
	{
		*OutVector4 = Vector4->operator*(Scale);
	}
}

void FVector4Implementation::Vector4_DivideScaleImplementation(const MonoObject* InMonoObject, const float Scale,
                                                               MonoObject** OutValue)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector4)),
		CLASS_SCRIPT_STRUCT_NAME(FVector4));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(NewMonoObject);

	if (Vector4 != nullptr && OutVector4 != nullptr)
	{
		*OutVector4 = Vector4->operator/(Scale);
	}
}

void FVector4Implementation::Vector4_DivideImplementation(const MonoObject* A, const MonoObject* B,
                                                          MonoObject** OutValue)
{
	const auto Vector4A = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(A);

	const auto Vector4B = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(B);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector4)),
		CLASS_SCRIPT_STRUCT_NAME(FVector4));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(NewMonoObject);

	if (Vector4A != nullptr && Vector4B != nullptr && OutVector4 != nullptr)
	{
		*OutVector4 = Vector4A->operator/(*Vector4B);
	}
}

void FVector4Implementation::Vector4_MultiplyImplementation(const MonoObject* A, const MonoObject* B,
                                                            MonoObject** OutValue)
{
	const auto Vector4A = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(A);

	const auto Vector4B = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(B);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector4)),
		CLASS_SCRIPT_STRUCT_NAME(FVector4));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(NewMonoObject);

	if (Vector4A != nullptr && Vector4B != nullptr && OutVector4 != nullptr)
	{
		*OutVector4 = Vector4A->operator*(*Vector4B);
	}
}

float FVector4Implementation::Vector4_Dot3Implementation(const MonoObject* A, const MonoObject* B)
{
	const auto Vector4A = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(A);

	const auto Vector4B = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(B);

	if (Vector4A != nullptr && Vector4B != nullptr)
	{
		return Dot3(*Vector4A, *Vector4B);
	}

	return 0.f;
}

float FVector4Implementation::Vector4_Dot4Implementation(const MonoObject* A, const MonoObject* B)
{
	const auto Vector4A = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(A);

	const auto Vector4B = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(B);

	if (Vector4A != nullptr && Vector4B != nullptr)
	{
		return Dot4(*Vector4A, *Vector4B);
	}

	return 0.f;
}

bool FVector4Implementation::Vector4_EqualityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto Vector4A = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(A);

	const auto Vector4B = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(B);

	if (Vector4A != nullptr && Vector4B != nullptr)
	{
		return Vector4A->operator==(*Vector4B);
	}

	return false;
}

bool FVector4Implementation::Vector4_InequalityImplementation(const MonoObject* A, const MonoObject* B)
{
	const auto Vector4A = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(A);

	const auto Vector4B = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(B);

	if (Vector4A != nullptr && Vector4B != nullptr)
	{
		return Vector4A->operator!=(*Vector4B);
	}

	return false;
}

void FVector4Implementation::Vector4_CrossProductImplementation(const MonoObject* A, const MonoObject* B,
                                                                MonoObject** OutValue)
{
	const auto Vector4A = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(A);

	const auto Vector4B = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(B);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector4)),
		CLASS_SCRIPT_STRUCT_NAME(FVector4));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(NewMonoObject);

	if (Vector4A != nullptr && Vector4B != nullptr && OutVector4 != nullptr)
	{
		*OutVector4 = Vector4A->operator^(*Vector4B);
	}
}

float FVector4Implementation::Vector4_ComponentImplementation(const MonoObject* InMonoObject, const int32 Index)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(InMonoObject);

	if (Vector4 != nullptr)
	{
		return Vector4->Component(Index);
	}

	return 0.f;
}

bool FVector4Implementation::Vector4_EqualsImplementation(const MonoObject* A, const MonoObject* B,
                                                          const float Tolerance)
{
	const auto Vector4A = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(A);

	const auto Vector4B = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(B);

	if (Vector4A != nullptr && Vector4B != nullptr)
	{
		return Vector4A->Equals(*Vector4B, Tolerance);
	}

	return false;
}

bool FVector4Implementation::Vector4_IsUnit3Implementation(const MonoObject* InMonoObject,
                                                           const float LengthSquaredTolerance)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(InMonoObject);

	if (Vector4 != nullptr)
	{
		return Vector4->IsUnit3(LengthSquaredTolerance);
	}

	return false;
}

void FVector4Implementation::Vector4_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(InMonoObject);

	if (Vector4 != nullptr)
	{
		const auto ResultString = Vector4->ToString();

		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_F_STRING);

		auto NewMonoString = static_cast<void*>(FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(
			TCHAR_TO_UTF8(*ResultString)));

		const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(
			FoundMonoClass, 1, &NewMonoString);

		*OutValue = NewMonoObject;
	}
}

bool FVector4Implementation::Vector4_InitFromStringImplementation(const MonoObject* InMonoObject,
                                                                  MonoObject* InSourceString)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(InMonoObject);

	if (Vector4 != nullptr && InSourceString != nullptr)
	{
		return Vector4->InitFromString(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(FCSharpEnvironment::GetEnvironment().
				GetDomain()->Object_To_String(InSourceString, nullptr))));
	}

	return false;
}

void FVector4Implementation::Vector4_GetSafeNormalImplementation(const MonoObject* InMonoObject, const float Tolerance,
                                                                 MonoObject** OutValue)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector4)),
		CLASS_SCRIPT_STRUCT_NAME(FVector4));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(NewMonoObject);

	if (Vector4 != nullptr && OutVector4 != nullptr)
	{
		*OutVector4 = Vector4->GetSafeNormal(Tolerance);
	}
}

void FVector4Implementation::Vector4_GetUnsafeNormal3Implementation(const MonoObject* InMonoObject,
                                                                    MonoObject** OutValue)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector4)),
		CLASS_SCRIPT_STRUCT_NAME(FVector4));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(NewMonoObject);

	if (Vector4 != nullptr && OutVector4 != nullptr)
	{
		*OutVector4 = Vector4->GetUnsafeNormal3();
	}
}

void FVector4Implementation::Vector4_ToOrientationRotatorImplementation(const MonoObject* InMonoObject,
                                                                        MonoObject** OutValue)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FRotator)),
		CLASS_SCRIPT_STRUCT_NAME(FRotator));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Vector4 != nullptr && OutRotator != nullptr)
	{
		*OutRotator = Vector4->ToOrientationRotator();
	}
}

void FVector4Implementation::Vector4_ToOrientationQuatImplementation(const MonoObject* InMonoObject,
                                                                     MonoObject** OutValue)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FQuat)),
		CLASS_SCRIPT_STRUCT_NAME(FQuat));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutQuat = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FQuat>(NewMonoObject);

	if (Vector4 != nullptr && OutQuat != nullptr)
	{
		*OutQuat = Vector4->ToOrientationQuat();
	}
}

void FVector4Implementation::Vector4_RotationImplementation(const MonoObject* InMonoObject, MonoObject** OutValue)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FRotator)),
		CLASS_SCRIPT_STRUCT_NAME(FRotator));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutRotator = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FRotator>(NewMonoObject);

	if (Vector4 != nullptr && OutRotator != nullptr)
	{
		*OutRotator = Vector4->Rotation();
	}
}

void FVector4Implementation::Vector4_SetImplementation(const MonoObject* InMonoObject, const float InX, const float InY,
                                                       const float InZ, const float InW)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(InMonoObject);

	if (Vector4 != nullptr)
	{
		return Vector4->Set(InX, InY, InZ, InW);
	}
}

float FVector4Implementation::Vector4_Size3Implementation(const MonoObject* InMonoObject)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(InMonoObject);

	if (Vector4 != nullptr)
	{
		return Vector4->Size3();
	}

	return 0.f;
}

float FVector4Implementation::Vector4_SizeSquared3Implementation(const MonoObject* InMonoObject)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(InMonoObject);

	if (Vector4 != nullptr)
	{
		return Vector4->SizeSquared3();
	}

	return 0.f;
}

float FVector4Implementation::Vector4_SizeImplementation(const MonoObject* InMonoObject)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(InMonoObject);

	if (Vector4 != nullptr)
	{
		return Vector4->Size();
	}

	return 0.f;
}

float FVector4Implementation::Vector4_SizeSquaredImplementation(const MonoObject* InMonoObject)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(InMonoObject);

	if (Vector4 != nullptr)
	{
		return Vector4->SizeSquared();
	}

	return 0.f;
}

bool FVector4Implementation::Vector4_ContainsNaNImplementation(const MonoObject* InMonoObject)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(InMonoObject);

	if (Vector4 != nullptr)
	{
		return Vector4->ContainsNaN();
	}

	return false;
}

bool FVector4Implementation::Vector4_IsNearlyZero3Implementation(const MonoObject* InMonoObject, const float Tolerance)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(InMonoObject);

	if (Vector4 != nullptr)
	{
		return Vector4->IsNearlyZero3(Tolerance);
	}

	return false;
}

void FVector4Implementation::Vector4_Reflect3Implementation(const MonoObject* InMonoObject, const MonoObject* Normal,
                                                            MonoObject** OutValue)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(InMonoObject);

	const auto Vector4Normal = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(Normal);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector4)),
		CLASS_SCRIPT_STRUCT_NAME(FVector4));

	const auto NewMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

	*OutValue = NewMonoObject;

	const auto OutVector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(NewMonoObject);

	if (Vector4 != nullptr && Vector4Normal != nullptr && OutVector4 != nullptr)
	{
		*OutVector4 = Vector4->Reflect3(*Vector4Normal);
	}
}

void FVector4Implementation::Vector4_FindBestAxisVectors3Implementation(const MonoObject* InMonoObject,
                                                                        MonoObject** Axis1, MonoObject** Axis2)
{
	const auto Vector4 = FCSharpEnvironment::GetEnvironment().GetAddress<UScriptStruct, FVector4>(InMonoObject);

	const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(CLASS_SCRIPT_STRUCT(FVector4)),
		CLASS_SCRIPT_STRUCT_NAME(FVector4));

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
