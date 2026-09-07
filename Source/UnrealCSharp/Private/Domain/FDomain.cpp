#include "Domain/FDomain.h"
#include "Domain/Script/IScriptDomain.h"
#include "Domain/Script/FScriptDomainFactory.h"
#include "Template/TGetArrayLength.inl"
#include "CoreMacro/ClassMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Macro/FunctionMacro.h"
#include "Reflection/FReflectionRegistry.h"

FDomain::FDomain()
{
	Initialize();
}

FDomain::~FDomain()
{
	Deinitialize();
}

void FDomain::Initialize()
{
	auto ScriptDomain = IScriptDomain::Get();

	if (ScriptDomain == nullptr)
	{
		ScriptDomain = FScriptDomainFactory::Create();

		IScriptDomain::Set(ScriptDomain);
	}

	ScriptDomain->Initialize();

	InitializeSynchronizationContext();
}

void FDomain::Deinitialize()
{
	DeinitializeSynchronizationContext();

	if (const auto ScriptDomain = IScriptDomain::Get())
	{
		FScriptDomainFactory::Destroy(ScriptDomain);
	}
}

void FDomain::Tick(const float DeltaTime)
{
	if (const auto ScriptDomain = IScriptDomain::Get())
	{
		ScriptDomain->Tick(DeltaTime);
	}
}

bool FDomain::IsTickable() const
{
	return FTickableGameObject::IsTickable();
}

TStatId FDomain::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(FMonoDomain, STATGROUP_Tickables);
}

void* FDomain::Object_Unbox(const IManagedHandle InManagedHandle)
{
	if (const auto ScriptDomain = IScriptDomain::Get())
	{
		return ScriptDomain->UnboxValue(InManagedHandle);
	}

	return nullptr;
}

IManagedHandle FDomain::String_New(const char* InText)
{
	if (const auto ScriptDomain = IScriptDomain::Get())
	{
		return ScriptDomain->NewString(InText);
	}

	return InvalidManagedHandle;
}

FString FDomain::StringToFString(const IManagedHandle InManagedHandle)
{
	if (const auto ScriptDomain = IScriptDomain::Get())
	{
		return ScriptDomain->StringToFString(InManagedHandle);
	}

	return FString();
}

void FDomain::GCHandle_Free(const IManagedHandle InManagedHandle)
{
	if (const auto ScriptDomain = IScriptDomain::Get())
	{
		ScriptDomain->Free(InManagedHandle);
	}
}

bool FDomain::IsLoadSucceed()
{
	if (const auto ScriptDomain = IScriptDomain::Get())
	{
		return ScriptDomain->IsInitialized();
	}

	return false;
}

FString FDomain::GetTraceback()
{
	if (const auto UtilsClass = FReflectionRegistry::Get().GetUtilsClass())
	{
		if (const auto TracebackMethod = UtilsClass->GetMethod(FUNCTION_UTILS_GET_TRACEBACK, 0))
		{
			const auto Traceback = TracebackMethod->Runtime_Invoke();

			auto Result = StringToFString(Traceback);

			GCHandle_Free(Traceback);

			return Result;
		}
	}

	return {};
}

void FDomain::InitializeSynchronizationContext()
{
	if (const auto SynchronizationContextClass = FReflectionRegistry::Get().GetClass(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_SYNCHRONIZATION_CONTEXT))
	{
		if (const auto InitializeMethod = SynchronizationContextClass->GetMethod(
			FUNCTION_SYNCHRONIZATION_CONTEXT_INITIALIZE, 0))
		{
			InitializeMethod->Runtime_Invoke();
		}
	}
}

void FDomain::DeinitializeSynchronizationContext()
{
	if (const auto SynchronizationContextClass = FReflectionRegistry::Get().GetClass(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_SYNCHRONIZATION_CONTEXT))
	{
		if (const auto DeinitializeMethod = SynchronizationContextClass->GetMethod(
			FUNCTION_SYNCHRONIZATION_CONTEXT_DEINITIALIZE, 0))
		{
			DeinitializeMethod->Runtime_Invoke();
		}
	}
}
