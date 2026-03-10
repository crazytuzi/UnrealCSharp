#include "Domain/FDomain.h"
#include "Log/FMonoLog.h"
#include "Template/TGetArrayLength.inl"
#include "CoreMacro/ClassMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Macro/FunctionMacro.h"
#include "Reflection/FReflectionRegistry.h"

FDomain::FDomain(const FMonoDomainInitializeParams& InParams):
	SynchronizationContextTick{nullptr}
{
	Initialize(InParams);
}

FDomain::~FDomain()
{
	Deinitialize();
}

void FDomain::Initialize(const FMonoDomainInitializeParams& InParams)
{
	FMonoDomain::Initialize(InParams);

	InitializeSynchronizationContext();
}

void FDomain::Deinitialize()
{
	DeinitializeSynchronizationContext();

	FMonoDomain::Deinitialize();
}

void FDomain::Tick(const float DeltaTime)
{
	if (SynchronizationContextTick != nullptr)
	{
		MonoObject* Exception{};

		SynchronizationContextTick(DeltaTime, &Exception);

		if (Exception != nullptr)
		{
			FMonoDomain::Unhandled_Exception(Exception);
		}
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

void* FDomain::Object_Unbox(MonoObject* InMonoObject)
{
	return FMonoDomain::Object_Unbox(InMonoObject);
}

MonoString* FDomain::String_New(const char* InText)
{
	return FMonoDomain::String_New(InText);
}

FMonoUTF8Scope FDomain::String_To_UTF8(MonoString* InMonoString)
{
	return FMonoDomain::String_To_UTF8(InMonoString);
}

MonoObject* FDomain::GCHandle_Get_Target_V2(const MonoGCHandle InGCHandle)
{
	return FMonoDomain::GCHandle_Get_Target_V2(InGCHandle);
}

void FDomain::GCHandle_Free_V2(const MonoGCHandle InGCHandle)
{
	return FMonoDomain::GCHandle_Free_V2(InGCHandle);
}

bool FDomain::IsLoadSucceed()
{
	return FMonoDomain::IsLoadSucceed();
}

FString FDomain::GetTraceback()
{
	if (const auto UtilsClass = FReflectionRegistry::Get().GetUtilsClass())
	{
		if (const auto TracebackMethod = UtilsClass->GetMethod(FUNCTION_UTILS_GET_TRACEBACK, 0))
		{
			return FString(UTF8_TO_TCHAR(String_To_UTF8((MonoString*)TracebackMethod->Runtime_Invoke())));
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

		if (const auto TickMethod = SynchronizationContextClass->GetMethod(
			FUNCTION_SYNCHRONIZATION_CONTEXT_TICK, 1))
		{
			SynchronizationContextTick = (SynchronizationContextTickType)TickMethod->Method_Get_Unmanaged_Thunk();
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
