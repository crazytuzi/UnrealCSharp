#include "Reflection/FClassReflection.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/ClassMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Reflection/FReflectionRegistry.h"
#include "Template/TGetArrayLength.inl"

FClassReflection::FClassReflection(const TWeakObjectPtr<UStruct>& InStruct, MonoClass* InClass):
FReflection(InStruct->GetName()),
Class(InClass)
{
	Type = FMonoDomain::Class_Get_Type(Class);
		
	ReflectionType = FMonoDomain::Type_Get_Object(Type);
	
	Parent = FReflectionRegistry::Get().GetClassReflection(InStruct->GetSuperStruct());
	
	Initialize();
}

FClassReflection::FClassReflection(const TWeakObjectPtr<UField>& InStruct, MonoClass* InClass):
FReflection(InStruct->GetName()),
Class(InClass)
{
	Type = FMonoDomain::Class_Get_Type(Class);
		
	ReflectionType = FMonoDomain::Type_Get_Object(Type);
	
	Initialize();
}

FClassReflection::FClassReflection(MonoClass* InClass) : FReflection({}),
                                                         Class(InClass)
{
	Type = FMonoDomain::Class_Get_Type(Class);

	ReflectionType = FMonoDomain::Type_Get_Object(Type);

	Initialize();
}

FClassReflection::FClassReflection(const FString& InName, MonoClass* InClass):
FReflection(InName),
Class(InClass)
{
	Type = FMonoDomain::Class_Get_Type(Class);
		
	ReflectionType = FMonoDomain::Type_Get_Object(Type);
	
	Initialize();
}

void FClassReflection::Initialize()
{
	if (Class != nullptr)
	{
		VTable = FMonoDomain::Class_VTable(Class);
	}
	
	int OutPropertyLength{};
	
	MonoArray* OutPropertyNames = nullptr;
	
	MonoArray* OutPropertyInfos = nullptr;

	int OutFieldLength{};
	
	MonoArray* OutFieldNames = nullptr;
	
	MonoArray* OutFieldInfos = nullptr;

	int OutMethodLength{};
	
	MonoArray* OutMethodNames = nullptr;
	
	MonoArray* OutMethodInfos = nullptr;

	MonoArray* OutMethodIsOverrides = nullptr;
	
	MonoArray* OutMethodParamsNumber = nullptr;

	void* InParams[13] = {
		ReflectionType,
		&bIsOverride,
		&OutPropertyLength,
		&OutPropertyNames,
		&OutPropertyInfos,
		&OutFieldLength,
		&OutFieldNames,
		&OutFieldInfos,
		&OutMethodLength,
		&OutMethodNames,
		&OutMethodInfos,
		&OutMethodIsOverrides,
		&OutMethodParamsNumber
	};
	
	MonoMethod* GetTypesWithAttributeMethod{};
	
	if (Name == CLASS_UTILS)
	{
		const auto UtilsMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_UTILS);

		GetTypesWithAttributeMethod = FMonoDomain::Class_Get_Method_From_Name(
			UtilsMonoClass, "GetPropertyInfo", TGetArrayLength(InParams));
		
	}
	else
	{
		GetTypesWithAttributeMethod = FReflectionRegistry::Get_Utils_Class()->Get_Method_From_Name("GetPropertyInfo", TGetArrayLength(InParams))->GetMethod();
	}

	FMonoDomain::Runtime_Invoke(
		GetTypesWithAttributeMethod, nullptr, InParams);
	
	for (auto Index = 0; Index < OutPropertyLength; ++Index)
	{
		auto PropertyName = FString(FMonoDomain::String_To_UTF8(FMonoDomain::Array_Get<MonoString*>(OutPropertyNames, Index)));

		// UE_LOG(LogTemp, Log, TEXT("PropertyName %s"), *PropertyName);
		
		Properties.Add(PropertyName,
		               new FPropertyReflection(PropertyName,
		                                       FMonoDomain::Array_Get<MonoReflectionProperty*>(OutPropertyInfos, Index)
		                                       ));
	}
	
	for (auto Index = 0; Index < OutFieldLength; ++Index)
	{
		auto FieldName = FString(FMonoDomain::String_To_UTF8(FMonoDomain::Array_Get<MonoString*>(OutFieldNames, Index)));

		// UE_LOG(LogTemp, Log, TEXT("FieldName %s"), *FieldName);
		
		Fields.Add(FieldName,
					   new FFieldReflection(FieldName,
											   FMonoDomain::Array_Get<MonoReflectionField*>(OutFieldInfos, Index)
											   ));
	}
	
	for (auto Index = 0; Index < OutMethodLength; ++Index)
	{
		auto MethodName = FString(FMonoDomain::String_To_UTF8(FMonoDomain::Array_Get<MonoString*>(OutMethodNames, Index)));

		// UE_LOG(LogTemp, Log, TEXT("MethodName %s"), *MethodName);
		
		auto Count = FMonoDomain::Array_Get<int32>(OutMethodParamsNumber, Index);
		
		Methods.Add({MethodName ,Count},
					   new FMethodReflection(MethodName,
					   FMonoDomain::Array_Get<bool>(OutMethodIsOverrides, Index),
					   FMonoDomain::Array_Get<int32>(OutMethodParamsNumber, Index),
											   FMonoDomain::Array_Get<MonoReflectionMethod*>(OutMethodInfos, Index)
											   ));
	}
}

void FClassReflection::Deinitialize()
{
}

bool FClassReflection::IsOverride() const
{
	return bIsOverride;
}

MonoClass* FClassReflection::GetClass() const
{
	return Class;
}

MonoVTable* FClassReflection::GetVTable() const
{
	return VTable;
}

MonoReflectionType* FClassReflection::GetReflectionType() const
{
	return ReflectionType;
}

const TMap<FString, FPropertyReflection*>& FClassReflection::GetProperties() const
{
	return Properties;
}

const TMap<FString, FFieldReflection*>& FClassReflection::GetFields() const
{
	return Fields;
}

const TMap<TPair<FString, int32>, FMethodReflection*>& FClassReflection::GetMethods() const
{
	return Methods;
}

FPropertyReflection* FClassReflection::GetPropertyReflection(const FString& InName) const
{
	auto FoundPropertyReflection = Properties.Find(InName);
	
	return FoundPropertyReflection != nullptr ? *FoundPropertyReflection : nullptr;
}

void FClassReflection::Property_Set_Value(const FString& InName, void* InMonoObject, void** InParams,
	MonoObject** InExc) const
{
	if (const auto FoundPropertyReflection = GetPropertyReflection(InName))
	{
		FMonoDomain::Property_Set_Value(FoundPropertyReflection->GetProperty(), InMonoObject, InParams, InExc);
	}
}

FFieldReflection* FClassReflection::Class_Get_Field_From_Name(const FString& InName) const
{
	auto FoundFieldReflection = Fields.Find(InName);
	
	return FoundFieldReflection != nullptr ? *FoundFieldReflection : nullptr;
}

void FClassReflection::Field_Static_Set_Value(const FString& InName, void* InValue) const
{
	if (const auto FoundFieldReflection = Class_Get_Field_From_Name(InName))
	{
		FMonoDomain::Field_Static_Set_Value(VTable, FoundFieldReflection->GetField(), InValue);
	}
}

FMethodReflection* FClassReflection::Get_Method_From_Name(const FString& InFunctionName, const int32 InParamCount)
{
	const auto FoundMethod = Methods.Find({InFunctionName, InParamCount});
	
	return FoundMethod != nullptr ? *FoundMethod : nullptr;
}

MonoClass* FClassReflection::GetMonoClass(const TWeakObjectPtr<UField>& InStruct)
{
	if (const auto InClass = Cast<UClass>(InStruct))
	{
		if (InClass->HasAnyClassFlags(CLASS_Interface))
		{
			return FMonoDomain::Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InClass),
			FUnrealCSharpFunctionLibrary::GetFullInterface(InClass));
		}
		
		return FMonoDomain::Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InClass),
			FUnrealCSharpFunctionLibrary::GetFullClass(InClass));
	}
	
	if (const auto InScriptStruct = Cast<UScriptStruct>(InStruct))
	{
		return FMonoDomain::Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InScriptStruct),
			FUnrealCSharpFunctionLibrary::GetFullClass(InScriptStruct));
	}
	
	if (const auto InEnum = Cast<UEnum>(InStruct))
	{
		return FMonoDomain::Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InEnum),
			FUnrealCSharpFunctionLibrary::GetFullClass(InEnum));
	}
	
	return nullptr;
}
