#include "Domain/FDomain.h"
#include "Log/FMonoLog.h"
#include "Template/TGetArrayLength.inl"
#include "CoreMacro/ClassMacro.h"
#include "CoreMacro/FunctionMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/PropertyMacro.h"
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
			Unhandled_Exception(Exception);
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

MonoObject* FDomain::Object_New(MonoClass* InMonoClass) const
{
	return FMonoDomain::Object_New(InMonoClass);
}

MonoObject* FDomain::Object_Init(UStruct* InStruct, const int32 InParamCount, void** InParams) const
{
	if (const auto ClassReflection = FReflectionRegistry::Get().GetClassReflection(InStruct))
	{
		if (const auto NewMonoObject = Object_New(ClassReflection->GetClass()))
		{
			if (const auto MethodReflection = ClassReflection->Get_Method_From_Name(FUNCTION_OBJECT_CONSTRUCTOR, InParamCount))
			{
				Runtime_Invoke(MethodReflection->GetMethod(), NewMonoObject, InParams);
			}

			return NewMonoObject;
		}

	}
	
	return nullptr;
}

MonoObject* FDomain::Runtime_Invoke(MonoMethod* InFunction, void* InMonoObject, void** InParams)
{
	return FMonoDomain::Runtime_Invoke(InFunction, InMonoObject, InParams);
}

MonoObject* FDomain::Runtime_Invoke(MonoMethod* InFunction, void* InMonoObject, void** InParams,
                                    MonoObject** InExc) const
{
	return FMonoDomain::Runtime_Invoke(InFunction, InMonoObject, InParams, InExc);
}

MonoObject* FDomain::Runtime_Invoke_Array(MonoMethod* InFunction, void* InMonoObject, MonoArray* InParams)
{
	return FMonoDomain::Runtime_Invoke_Array(InFunction, InMonoObject, InParams);
}

MonoObject* FDomain::Runtime_Invoke_Array(MonoMethod* InFunction, void* InMonoObject, MonoArray* InParams,
                                          MonoObject** InExc)
{
	return FMonoDomain::Runtime_Invoke_Array(InFunction, InMonoObject, InParams, InExc);
}

MonoObject* FDomain::Runtime_Delegate_Invoke(MonoObject* InDelegate, void** InParams) const
{
	return FMonoDomain::Runtime_Delegate_Invoke(InDelegate, InParams);
}

MonoObject* FDomain::Runtime_Delegate_Invoke(MonoObject* InDelegate, void** InParams, MonoObject** InExc) const
{
	return FMonoDomain::Runtime_Delegate_Invoke(InDelegate, InParams, InExc);
}

void FDomain::Unhandled_Exception(MonoObject* InException) const
{
	FMonoDomain::Unhandled_Exception(InException);
}

MonoClass* FDomain::Object_Get_Class(MonoObject* InMonoObject)
{
	return FMonoDomain::Object_Get_Class(InMonoObject);
}

MonoObject* FDomain::Value_Box(MonoClass* InMonoClass, void* InValue)
{
	return FMonoDomain::Value_Box(InMonoClass, InValue);
}

void* FDomain::Object_Unbox(MonoObject* InMonoObject)
{
	return FMonoDomain::Object_Unbox(InMonoObject);
}

MonoString* FDomain::String_New(const char* InText)
{
	return FMonoDomain::String_New(InText);
}

char* FDomain::String_To_UTF8(MonoString* InMonoString)
{
	return FMonoDomain::String_To_UTF8(InMonoString);
}

MonoArray* FDomain::Array_New(MonoClass* InMonoClass, const uint32 InNum)
{
	return FMonoDomain::Array_New(InMonoClass, InNum);
}

MonoGCHandle FDomain::GCHandle_New_V2(UStruct* InStruct, MonoObject* InMonoObject, mono_bool bPinned)
{
	auto GarbageCollectionHandle = FMonoDomain::GCHandle_New_V2(InMonoObject, bPinned);

	void* InParams[] = {&GarbageCollectionHandle};
	
	if (const auto FoundProperty = FReflectionRegistry::Get().GetClassReflection(InStruct))
	{
		FoundProperty->Property_Set_Value(PROPERTY_GARBAGE_COLLECTION_HANDLE, InMonoObject, InParams, nullptr);
	}

	return GarbageCollectionHandle;
}

MonoGCHandle FDomain::GCHandle_New_V2(MonoClass* InMonoClass, MonoObject* InMonoObject, const mono_bool bPinned)
{
	auto GarbageCollectionHandle = FMonoDomain::GCHandle_New_V2(InMonoObject, bPinned);

	void* InParams[] = {&GarbageCollectionHandle};
	
	if (const auto ClassReflection = FReflectionRegistry::Get().GetClassReflection(InMonoClass))
	{
		ClassReflection->Property_Set_Value(PROPERTY_GARBAGE_COLLECTION_HANDLE, InMonoObject, InParams, nullptr);
	}
	
	return GarbageCollectionHandle;
}

MonoGCHandle FDomain::GCHandle_New_WeakRef_V2(MonoClass* InMonoClass,MonoObject* InMonoObject,
                                              mono_bool bTrackResurrection)
{
	auto GarbageCollectionHandle = FMonoDomain::GCHandle_New_WeakRef_V2(InMonoObject, bTrackResurrection);

	void* InParams[] = {&GarbageCollectionHandle};
	
	if (const auto ClassReflection = FReflectionRegistry::Get().GetClassReflection(InMonoClass))
	{
		ClassReflection->Property_Set_Value(PROPERTY_GARBAGE_COLLECTION_HANDLE, InMonoObject, InParams, nullptr);
	}

	return GarbageCollectionHandle;
}

MonoGCHandle FDomain::GCHandle_New_WeakRef_V2(UStruct* InStruct, MonoObject* InMonoObject, mono_bool bTrackResurrection)
{
	auto GarbageCollectionHandle = FMonoDomain::GCHandle_New_WeakRef_V2(InMonoObject, bTrackResurrection);

	void* InParams[] = {&GarbageCollectionHandle};
	
	if (const auto ClassReflection = FReflectionRegistry::Get().GetClassReflection(InStruct))
	{
		ClassReflection->Property_Set_Value(PROPERTY_GARBAGE_COLLECTION_HANDLE, InMonoObject, InParams, nullptr);
	}

	return GarbageCollectionHandle;
}

MonoObject* FDomain::GCHandle_Get_Target_V2(const MonoGCHandle InGCHandle)
{
	return FMonoDomain::GCHandle_Get_Target_V2(InGCHandle);
}

void FDomain::GCHandle_Free_V2(const MonoGCHandle InGCHandle)
{
	return FMonoDomain::GCHandle_Free_V2(InGCHandle);
}

void* FDomain::Method_Get_Unmanaged_Thunk(MonoMethod* InMonoMethod)
{
	return FMonoDomain::Method_Get_Unmanaged_Thunk(InMonoMethod);
}

void FDomain::Object_Constructor(MonoObject* InMonoObject, int32 InParamCount, void** InParams)
{
	FMonoDomain::Object_Constructor(InMonoObject, InParamCount, InParams);
}

void FDomain::Object_Constructor(UStruct* InStruct, MonoObject* InMonoObject, const int32 InParamCount, void** InParams)
{
	if (auto Class = FReflectionRegistry::Get().GetClassReflection(InStruct))
	{
		if (auto Method = Class->Get_Method_From_Name(FUNCTION_OBJECT_CONSTRUCTOR, InParamCount))
		{
			Runtime_Invoke(Method->Method, InMonoObject, InParams);
		}
	}
}

MonoMethod* FDomain::Parent_Class_Get_Method_From_Name(UStruct* InStruct, const FString& InFunctionName,
                                                       const int32 InParamCount)
{
	auto Class = FReflectionRegistry::Get().GetClassReflection(InStruct);
	
	while (Class != nullptr)
	{
		if (const auto FoundMethod = Class->Get_Method_From_Name(InFunctionName, InParamCount))
		{
			return FoundMethod->Method;
		}

		Class = Class->Parent;
	}

	return nullptr;
}

MonoMethod* FDomain::Delegate_Get_Method(MonoObject* InDelegate) const
{
	return FMonoDomain::Delegate_Get_Method(InDelegate);
}

void FDomain::InitializeSynchronizationContext()
{
	if (const auto SynchronizationContextClass = FReflectionRegistry::Get().GetClassReflection(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_SYNCHRONIZATION_CONTEXT))
	{
		if (auto InitializeMonoMethod = SynchronizationContextClass->Get_Method_From_Name(FUNCTION_SYNCHRONIZATION_CONTEXT_INITIALIZE, 0))
		{
			Runtime_Invoke(InitializeMonoMethod->GetMethod(), nullptr, nullptr, nullptr);
		}
		
		if (const auto TickMonoMethod = SynchronizationContextClass->Get_Method_From_Name(FUNCTION_SYNCHRONIZATION_CONTEXT_TICK, 1))
		{
			SynchronizationContextTick = (SynchronizationContextTickType)Method_Get_Unmanaged_Thunk(TickMonoMethod->GetMethod());
		}
	}
}

void FDomain::DeinitializeSynchronizationContext()
{
	if (const auto SynchronizationContextClass = FReflectionRegistry::Get().GetClassReflection(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_SYNCHRONIZATION_CONTEXT))
	{
		if (auto DeinitializeMonoMethod = SynchronizationContextClass->Get_Method_From_Name(FUNCTION_SYNCHRONIZATION_CONTEXT_DEINITIALIZE, 0))
		{
			Runtime_Invoke(DeinitializeMonoMethod->GetMethod(), nullptr, nullptr, nullptr);
		}
	}
}

MonoString* FDomain::GetTraceback() const
{
	if (FMonoDomain::Domain != nullptr)
	{
		if (const auto TracebackClass = FReflectionRegistry::Get().Get_Utils_Class())
		{
			if (const auto TracebackMethod = TracebackClass->Get_Method_From_Name(FUNCTION_UTILS_GET_TRACEBACK, 0))
			{
				Runtime_Invoke(TracebackMethod->GetMethod(), nullptr, nullptr, nullptr);
			}
		}
	}

	return nullptr;
}
