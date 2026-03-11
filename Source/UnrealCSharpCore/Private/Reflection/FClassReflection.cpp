#include "Reflection/FClassReflection.h"
#include "CoreMacro/Macro.h"
#include "CoreMacro/ClassMacro.h"
#include "CoreMacro/FunctionMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/PropertyMacro.h"
#include "Reflection/FReflectionRegistry.h"
#include "Template/TGetArrayLength.inl"

FClassReflection::FClassReflection(MonoClass* InClass, const FString& InName):
	FReflection(InName),
	Class(InClass)
{
	const auto Type = FMonoDomain::Class_Get_Type(Class);

	ReflectionType = FMonoDomain::Type_Get_Object(Type);

	Initialize();
}

FClassReflection::FClassReflection(MonoReflectionType* InReflectionType)
{
	ReflectionType = InReflectionType;

	const auto Type = FMonoDomain::Reflection_Type_Get_Type(ReflectionType);

	Class = FMonoDomain::Class_From_Type(Type);

	Initialize();
}

FClassReflection::~FClassReflection()
{
	Deinitialize();
}

void FClassReflection::Initialize()
{
	if (Class != nullptr)
	{
		VTable = FMonoDomain::Class_VTable(Class);
	}

	MonoReflectionType* OutTypeDefinition{};

	MonoString* OutName{};

	MonoString* OutNameSpace{};

	MonoString* OutPathName{};

	MonoReflectionType* OutParent{};

	MonoReflectionType* OutUnderlyingType{};

	int32 OutGenericArgumentLength{};

	MonoArray* OutGenericArguments{};

	int32 OutInterfaceLength{};

	MonoArray* OutInterfaces{};

	int32 OutClassAttributeLength{};

	MonoArray* OutClassAttributes{};

	MonoArray* OutClassAttributeValueLength{};

	MonoArray* OutClassAttributeValues{};

	int32 OutPropertyLength{};

	MonoArray* OutPropertyNames{};

	MonoArray* OutPropertyInfos{};

	MonoArray* OutPropertyTypes{};

	MonoArray* OutPropertyAttributeCounts{};

	MonoArray* OutPropertyAttributes{};

	MonoArray* OutPropertyAttributeValueCounts{};

	MonoArray* OutPropertyAttributeValues{};

	int32 OutFieldLength{};

	MonoArray* OutFieldNames{};

	MonoArray* OutFieldInfos{};

	int32 OutMethodLength{};

	MonoArray* OutMethodNames{};

	MonoArray* OutMethodInfos{};

	MonoArray* OutMethodIsStatics{};

	MonoArray* OutMethodParamCounts{};

	MonoArray* OutMethodReturnTypes{};

	MonoArray* OutMethodParamIndex{};

	MonoArray* OutMethodParamNames{};

	MonoArray* OutMethodParamTypes{};

	MonoArray* OutMethodParamRefs{};

	MonoArray* OutMethodAttributeCounts{};

	MonoArray* OutMethodAttributes{};

	MonoArray* OutMethodAttributeValueCounts{};

	MonoArray* OutMethodAttributeValues{};

	void* InParams[42] = {
		ReflectionType,
		&OutTypeDefinition,
		&OutName,
		&OutNameSpace,
		&OutPathName,
		&OutParent,
		&OutUnderlyingType,
		&bIsClass,
		&bIsEnum,
		&OutGenericArgumentLength,
		&OutGenericArguments,
		&OutInterfaceLength,
		&OutInterfaces,
		&OutClassAttributeLength,
		&OutClassAttributes,
		&OutClassAttributeValueLength,
		&OutClassAttributeValues,
		&OutPropertyLength,
		&OutPropertyNames,
		&OutPropertyInfos,
		&OutPropertyTypes,
		&OutPropertyAttributeCounts,
		&OutPropertyAttributes,
		&OutPropertyAttributeValueCounts,
		&OutPropertyAttributeValues,
		&OutFieldLength,
		&OutFieldNames,
		&OutFieldInfos,
		&OutMethodLength,
		&OutMethodNames,
		&OutMethodInfos,
		&OutMethodIsStatics,
		&OutMethodParamCounts,
		&OutMethodReturnTypes,
		&OutMethodParamIndex,
		&OutMethodParamNames,
		&OutMethodParamTypes,
		&OutMethodParamRefs,
		&OutMethodAttributeCounts,
		&OutMethodAttributes,
		&OutMethodAttributeValueCounts,
		&OutMethodAttributeValues,
	};

	if (Name == CLASS_UTILS)
	{
		if (const auto UtilsClass = FMonoDomain::Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_UTILS))
		{
			if (const auto GetTypesWithAttributeMethod = FMonoDomain::Class_Get_Method_From_Name(
				UtilsClass, FUNCTION_UTILS_GET_CLASS_REFLECTION, TGetArrayLength(InParams)))
			{
				FMonoDomain::Runtime_Invoke(GetTypesWithAttributeMethod, nullptr, InParams);
			}
		}
	}
	else
	{
		if (auto UtilsClass = FReflectionRegistry::Get().GetUtilsClass())
		{
			if (const auto GetTypesWithAttributeMethod = UtilsClass->GetMethod(
				FUNCTION_UTILS_GET_CLASS_REFLECTION, TGetArrayLength(InParams)))
			{
				GetTypesWithAttributeMethod->Runtime_Invoke(nullptr, InParams);
			}
		}
	}

	if (OutTypeDefinition != ReflectionType)
	{
		TypeDefinition = FReflectionRegistry::Get().GetClass(OutTypeDefinition);
	}
	else
	{
		TypeDefinition = this;
	}

	Name = FString(FMonoDomain::String_To_UTF8(OutName));

	NameSpace = FString(FMonoDomain::String_To_UTF8(OutNameSpace));

	PathName = FString(FMonoDomain::String_To_UTF8(OutPathName));

	if (Name != CLASS_UTILS && OutParent != nullptr)
	{
		Parent = FReflectionRegistry::Get().GetClass(OutParent);
	}

	if (OutUnderlyingType != nullptr)
	{
		UnderlyingType = FReflectionRegistry::Get().GetClass(OutUnderlyingType);
	}

	for (auto GenericArgumentIndex = 0; GenericArgumentIndex < OutGenericArgumentLength; ++GenericArgumentIndex)
	{
		GenericArguments.Add(FReflectionRegistry::Get().GetClass(
			FMonoDomain::Array_Get<MonoReflectionType*>(OutGenericArguments, GenericArgumentIndex)));
	}

	for (auto InterfaceIndex = 0; InterfaceIndex < OutInterfaceLength; ++InterfaceIndex)
	{
		Interfaces.Add(FReflectionRegistry::Get().GetClass(
			FMonoDomain::Array_Get<MonoReflectionType*>(OutInterfaces, InterfaceIndex)));
	}

	auto ClassAttributeIndex = 0;

	for (auto AttributeIndex = 0; AttributeIndex < OutClassAttributeLength; ++AttributeIndex)
	{
		const auto Attribute = FReflectionRegistry::Get().GetClass(
			FMonoDomain::Array_Get<MonoReflectionType*>(OutClassAttributes, AttributeIndex));

		Attributes.Add(Attribute);

		const auto AttributeValueCount = FMonoDomain::Array_Get<int32>(
			OutClassAttributeValueLength, AttributeIndex);

		for (auto AttributeValueIndex = 0; AttributeValueIndex < AttributeValueCount; ++AttributeValueIndex)
		{
			AttributeValues.FindOrAdd(Attribute).Add(FString(
				FMonoDomain::String_To_UTF8(FMonoDomain::Array_Get<MonoString*>(OutClassAttributeValues,
					ClassAttributeIndex + AttributeValueIndex))));
		}

		ClassAttributeIndex += AttributeValueCount;
	}

	if (Name != CLASS_UTILS)
	{
		bIsOverride = HasAttribute(FReflectionRegistry::Get().GetOverrideAttributeClass()) ||
			HasAttribute(FReflectionRegistry::Get().GetUClassAttributeClass());
	}

	auto PropertyAttributeIndex = 0;

	auto PropertyAttributeValueIndex = 0;

	for (auto PropertyIndex = 0; PropertyIndex < OutPropertyLength; ++PropertyIndex)
	{
		auto PropertyName = FString(
			FMonoDomain::String_To_UTF8(FMonoDomain::Array_Get<MonoString*>(OutPropertyNames, PropertyIndex)));

		auto AttributeCount = FMonoDomain::Array_Get<int32>(OutPropertyAttributeCounts, PropertyIndex);

		TSet<FClassReflection*> PropertyAttributes;

		TMap<FClassReflection*, TArray<FString>> PropertyAttributeValues;

		for (auto AttributeIndex = 0; AttributeIndex < AttributeCount; ++AttributeIndex)
		{
			const auto Attribute = FReflectionRegistry::Get().GetClass(
				FMonoDomain::Array_Get<MonoReflectionType*>(
					OutPropertyAttributes, PropertyAttributeIndex + AttributeIndex));

			PropertyAttributes.Add(Attribute);

			auto AttributeValueCount = FMonoDomain::Array_Get<int32>(
				OutPropertyAttributeValueCounts, PropertyAttributeIndex + AttributeIndex);

			for (auto AttributeValueIndex = 0; AttributeValueIndex < AttributeValueCount; ++AttributeValueIndex)
			{
				PropertyAttributeValues.FindOrAdd(Attribute).Add(FString(FMonoDomain::String_To_UTF8(
					FMonoDomain::Array_Get<MonoString*>(
						OutPropertyAttributeValues, PropertyAttributeValueIndex + AttributeValueIndex))));
			}

			PropertyAttributeValueIndex += AttributeValueCount;
		}

		PropertyAttributeIndex += AttributeCount;

		Properties.Add(PropertyName,
		               new FPropertyReflection(PropertyName,
		                                       FMonoDomain::Array_Get<MonoReflectionProperty*>(
			                                       OutPropertyInfos, PropertyIndex),
		                                       FMonoDomain::Array_Get<MonoReflectionType*>(
			                                       OutPropertyTypes, PropertyIndex),
		                                       PropertyAttributes, PropertyAttributeValues));
	}

	for (auto FieldIndex = 0; FieldIndex < OutFieldLength; ++FieldIndex)
	{
		auto FieldName = FString(
			FMonoDomain::String_To_UTF8(FMonoDomain::Array_Get<MonoString*>(OutFieldNames, FieldIndex)));

		Fields.Add(FieldName,
		           new FFieldReflection(FieldName,
		                                FMonoDomain::Array_Get<MonoReflectionField*>(OutFieldInfos, FieldIndex)
		           ));
	}

	auto MethodAttributeIndex = 0;

	auto MethodAttributeValueIndex = 0;

	for (auto MethodIndex = 0; MethodIndex < OutMethodLength; ++MethodIndex)
	{
		auto MethodName = FString(
			FMonoDomain::String_To_UTF8(FMonoDomain::Array_Get<MonoString*>(OutMethodNames, MethodIndex)));

		auto MethodParamCount = FMonoDomain::Array_Get<int32>(OutMethodParamCounts, MethodIndex);

		auto AttributeCount = FMonoDomain::Array_Get<int32>(OutMethodAttributeCounts, MethodIndex);

		TSet<FClassReflection*> MethodAttributes;

		TMap<FClassReflection*, TArray<FString>> MethodAttributeValue;

		for (auto AttributeIndex = 0; AttributeIndex < AttributeCount; ++AttributeIndex)
		{
			const auto Attribute = FReflectionRegistry::Get().GetClass(
				FMonoDomain::Array_Get<MonoReflectionType*>(
					OutMethodAttributes, MethodAttributeIndex + AttributeIndex));

			MethodAttributes.Add(Attribute);

			auto AttributeValueCount = FMonoDomain::Array_Get<int32>(
				OutMethodAttributeValueCounts, MethodAttributeIndex + AttributeIndex);

			for (auto AttributeValueIndex = 0; AttributeValueIndex < AttributeValueCount; ++AttributeValueIndex)
			{
				MethodAttributeValue.FindOrAdd(Attribute).Add(FString(FMonoDomain::String_To_UTF8(
					FMonoDomain::Array_Get<MonoString*>(
						OutMethodAttributeValues, MethodAttributeValueIndex + AttributeValueIndex))));
			}

			MethodAttributeValueIndex += AttributeValueCount;
		}

		MethodAttributeIndex += AttributeCount;

		auto bIsUFunction = MethodAttributes.Contains(
			FReflectionRegistry::Get().GetUFunctionAttributeClass());

		auto bMethodIsStatic = false;

		MonoReflectionType* ReturnType{};

		TArray<FParamReflection*> ParamReflections;

		if (bIsUFunction)
		{
			bMethodIsStatic = FMonoDomain::Array_Get<bool>(OutMethodIsStatics, MethodIndex);

			ReturnType = FMonoDomain::Array_Get<MonoReflectionType*>(OutMethodReturnTypes, MethodIndex);

			const auto MethodParamIndex = FMonoDomain::Array_Get<int32>(OutMethodParamIndex, MethodIndex);

			ParamReflections.Init(nullptr, MethodParamCount);

			for (auto ParamIndex = 0; ParamIndex < MethodParamCount; ++ParamIndex)
			{
				auto ParamName = FString(FMonoDomain::String_To_UTF8(
					FMonoDomain::Array_Get<MonoString*>(OutMethodParamNames, MethodParamIndex + ParamIndex)));

				ParamReflections[ParamIndex] = new FParamReflection(
					ParamName,
					FMonoDomain::Array_Get<bool>(OutMethodParamRefs, MethodParamIndex + ParamIndex),
					FMonoDomain::Array_Get<MonoReflectionType*>(OutMethodParamTypes, MethodParamIndex + ParamIndex));
			}
		}

		Methods.Add({MethodName, MethodParamCount},
		            new FMethodReflection(MethodName,
		                                  FMonoDomain::Array_Get<int32>(OutMethodParamCounts, MethodIndex),
		                                  FMonoDomain::Array_Get<MonoReflectionMethod*>(OutMethodInfos, MethodIndex),
		                                  bMethodIsStatic,
		                                  ReturnType
			                                  ? FReflectionRegistry::Get().GetClass(ReturnType)
			                                  : nullptr,
		                                  ParamReflections,
		                                  MethodAttributes,
		                                  MethodAttributeValue));
	}
}

void FClassReflection::Deinitialize()
{
	for (const auto& [PLACEHOLDER, Property] : Properties)
	{
		delete Property;
	}

	Properties.Empty();

	for (const auto& [PLACEHOLDER, Field] : Fields)
	{
		delete Field;
	}

	Fields.Empty();

	for (const auto& [PLACEHOLDER, Method] : Methods)
	{
		delete Method;
	}

	Methods.Empty();
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

FClassReflection* FClassReflection::GetTypeDefinition() const
{
	return TypeDefinition;
}

const FString& FClassReflection::GetNameSpace() const
{
	return NameSpace;
}

const FString& FClassReflection::GetPathName() const
{
	return PathName;
}

FClassReflection* FClassReflection::GetParent() const
{
	return Parent;
}

FClassReflection* FClassReflection::GetUnderlyingType() const
{
	return UnderlyingType;
}

bool FClassReflection::IsClass() const
{
	return bIsClass;
}

bool FClassReflection::IsEnum() const
{
	return bIsEnum;
}

bool FClassReflection::IsOverride() const
{
	return bIsOverride;
}

const TArray<FClassReflection*>& FClassReflection::GetGenericArguments() const
{
	return GenericArguments;
}

FClassReflection* FClassReflection::GetGenericArgument(const int32 InIndex) const
{
	return GenericArguments.IsValidIndex(InIndex) ? GenericArguments[InIndex] : nullptr;
}

const TArray<FClassReflection*>& FClassReflection::GetInterfaces() const
{
	return Interfaces;
}

const TMap<FString, FPropertyReflection*>& FClassReflection::GetProperties() const
{
	return Properties;
}

FPropertyReflection* FClassReflection::GetProperty(const FString& InName) const
{
	const auto FoundProperty = Properties.Find(InName);

	return FoundProperty != nullptr ? *FoundProperty : nullptr;
}

const TMap<FString, FFieldReflection*>& FClassReflection::GetFields() const
{
	return Fields;
}

FFieldReflection* FClassReflection::GetField(const FString& InName) const
{
	const auto FoundField = Fields.Find(InName);

	return FoundField != nullptr ? *FoundField : nullptr;
}

const TMap<TPair<FString, int32>, FMethodReflection*>& FClassReflection::GetMethods() const
{
	return Methods;
}

FMethodReflection* FClassReflection::GetMethod(const FString& InMethodName, const int32 InParamCount) const
{
	const auto FoundMethod = Methods.Find({InMethodName, InParamCount});

	return FoundMethod != nullptr ? *FoundMethod : nullptr;
}

FMethodReflection* FClassReflection::GetMethod(const MonoReflectionMethod* InReflectionMethod)
{
	for (const auto& [PLACEHOLDER, Method] : Methods)
	{
		if (Method->GetReflectionMethod() == InReflectionMethod)
		{
			return Method;
		}
	}

	return nullptr;
}

FMethodReflection* FClassReflection::GetParentMethod(const FString& InFunctionName,
                                                     const int32 InParamCount) const
{
	auto ClassReflection = this;

	while (ClassReflection != nullptr)
	{
		if (const auto FoundMethod = ClassReflection->GetMethod(InFunctionName, InParamCount))
		{
			return FoundMethod;
		}

		ClassReflection = ClassReflection->GetParent();
	}

	return nullptr;
}

MonoObject* FClassReflection::NewObject() const
{
	return FMonoDomain::Object_New(Class);
}

MonoObject* FClassReflection::InitObject(const int32 InParamCount, void** InParams) const
{
	if (const auto Object = NewObject())
	{
		if (const auto FoundMethod = GetMethod(FUNCTION_OBJECT_CONSTRUCTOR, InParamCount))
		{
			FoundMethod->Runtime_Invoke(Object, InParams);
		}

		return Object;
	}

	return nullptr;
}

void FClassReflection::ConstructorObject(MonoObject* InMonoObject, const int32 InParamCount, void** InParams) const
{
	if (const auto FoundMethod = GetMethod(FUNCTION_OBJECT_CONSTRUCTOR, InParamCount))
	{
		FoundMethod->Runtime_Invoke(InMonoObject, InParams);
	}
}

void FClassReflection::ConstructorClass() const
{
	if (const auto FoundMethod = GetMethod(FUNCTION_CLASS_CONSTRUCTOR, 0))
	{
		FoundMethod->Runtime_Invoke(Class, nullptr);
	}
}

MonoGCHandle FClassReflection::NewGCHandle(MonoObject* InMonoObject, const mono_bool bPinned) const
{
	auto GarbageCollectionHandle = FMonoDomain::GCHandle_New_V2(InMonoObject, bPinned);

	void* InParams[] = {&GarbageCollectionHandle};

	if (const auto FoundProperty = GetProperty(PROPERTY_GARBAGE_COLLECTION_HANDLE))
	{
		FoundProperty->SetValue(InMonoObject, InParams, nullptr);
	}

	return GarbageCollectionHandle;
}

MonoGCHandle FClassReflection::NewWeakRefGCHandle(MonoObject* InMonoObject, const mono_bool bTrackResurrection) const
{
	auto GarbageCollectionHandle = FMonoDomain::GCHandle_New_WeakRef_V2(InMonoObject, bTrackResurrection);

	void* InParams[] = {&GarbageCollectionHandle};

	if (const auto FoundProperty = GetProperty(PROPERTY_GARBAGE_COLLECTION_HANDLE))
	{
		FoundProperty->SetValue(InMonoObject, InParams, nullptr);
	}

	return GarbageCollectionHandle;
}

MonoObject* FClassReflection::BoxValue(void* InValue) const
{
	return FMonoDomain::Value_Box(Class, InValue);
}

MonoArray* FClassReflection::NewArray(const uint32 InNum) const
{
	return FMonoDomain::Array_New(Class, InNum);
}

bool FClassReflection::IsAssignableFrom(const FClassReflection* InSuperClass, const mono_bool bCheckInterfaces) const
{
	return this == InSuperClass || !!FMonoDomain::Class_Is_Subclass_Of(Class, InSuperClass->Class, bCheckInterfaces);
}
