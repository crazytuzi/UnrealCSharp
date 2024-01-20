﻿#include "Registry/FDynamicRegistry.h"
#include "CoreMacro/ClassMacro.h"
#include "CoreMacro/FunctionMacro.h"
#include "CoreMacro/MonoMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Delegate/FUnrealCSharpModuleDelegates.h"
#include "Dynamic/FDynamicClassGenerator.h"
#include "Environment/FCSharpEnvironment.h"
#include "Template/TGetArrayLength.inl"

FDynamicRegistry::FDynamicRegistry()
{
	Initialize();
}

FDynamicRegistry::~FDynamicRegistry()
{
	Deinitialize();
}

void FDynamicRegistry::Initialize()
{
	OnCSharpEnvironmentInitializeDelegateHandle = FUnrealCSharpModuleDelegates::OnCSharpEnvironmentInitialize.AddRaw(
		this, &FDynamicRegistry::OnCSharpEnvironmentInitialize);
}

void FDynamicRegistry::Deinitialize()
{
	if (OnCSharpEnvironmentInitializeDelegateHandle.IsValid())
	{
		FUnrealCSharpModuleDelegates::OnCSharpEnvironmentInitialize.Remove(OnCSharpEnvironmentInitializeDelegateHandle);
	}
}

void FDynamicRegistry::OnCSharpEnvironmentInitialize() const
{
	RegisterDynamic();
}

void FDynamicRegistry::RegisterDynamic() const
{
	const auto AttributeMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DYNAMIC), CLASS_U_CLASS_ATTRIBUTE);

	const auto AttributeMonoType = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_Get_Type(AttributeMonoClass);

	const auto AttributeMonoReflectionType = FCSharpEnvironment::GetEnvironment().GetDomain()->Type_Get_Object(
		AttributeMonoType);

	const auto UtilsMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_UTILS);

	void* InParams[2] = {
		AttributeMonoReflectionType,
		FMonoDomain::GCHandle_Get_Target_V2(FMonoDomain::AssemblyGCHandles[1])
	};

	const auto GetTypesWithAttributeMethod = FMonoDomain::Class_Get_Method_From_Name(
		UtilsMonoClass, FUNCTION_UTILS_GET_TYPES_WITH_ATTRIBUTE, TGetArrayLength(InParams));

	const auto Types = reinterpret_cast<MonoArray*>(FMonoDomain::Runtime_Invoke(
		GetTypesWithAttributeMethod, nullptr, InParams));

	const auto Length = FMonoDomain::Array_Length(Types);

	for (auto Index = 0; Index < Length; ++Index)
	{
		const auto ReflectionType = ARRAY_GET(Types, MonoReflectionType*, Index);

		const auto Type = FMonoDomain::Reflection_Type_Get_Type(ReflectionType);

		const auto Class = FMonoDomain::Type_Get_Class(Type);

		if (const auto DynamicClass = FDynamicClassGenerator::GetDynamicClass(Class))
		{
			FCSharpEnvironment::GetEnvironment().Bind(DynamicClass, true);
		}
	}
}
