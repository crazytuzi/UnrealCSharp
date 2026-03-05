#include "Registry/FDynamicRegistry.h"
#include "Delegate/FUnrealCSharpModuleDelegates.h"
#include "Dynamic/FDynamicClassGenerator.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/FReflectionRegistry.h"

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
	if (FDomain::IsLoadSucceed())
	{
		FDynamicGeneratorCore::Generator(FReflectionRegistry::Get().GetUClassAttributeClass(),
		                                 [](FClassReflection* InClass)
		                                 {
			                                 if (const auto DynamicClass = FDynamicClassGenerator::GetDynamicClass(
				                                 InClass))
			                                 {
				                                 FCSharpEnvironment::GetEnvironment().Bind<true>(DynamicClass);
			                                 }
		                                 }
		);
	}
}
