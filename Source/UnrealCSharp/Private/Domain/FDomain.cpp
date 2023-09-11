#include "Domain/FDomain.h"
#include "Log/FMonoLog.h"
#include "Template/TGetArrayLength.inl"
#include "CoreMacro/ClassMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Macro/FunctionMacro.h"

FDomain::FDomain(const FMonoDomainInitializeParams& InParams)
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

void FDomain::Tick(float DeltaTime)
{
	if (const auto SynchronizationContextClass = Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_SYNCHRONIZATION_CONTEXT))
	{
		auto InParams = static_cast<void*>(&DeltaTime);

		if (const auto TickMonoMethod = Class_Get_Method_From_Name(
			SynchronizationContextClass, FUNCTION_SYNCHRONIZATION_CONTEXT_TICK, TGetArrayLength(InParams)))
		{
			Runtime_Invoke(TickMonoMethod, nullptr, &InParams);
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

MonoObject* FDomain::Object_New(MonoClass* InMonoClass, const int32 InParamCount, void** InParams) const
{
	return FMonoDomain::Object_New(InMonoClass, InParamCount, InParams);
}

void FDomain::Runtime_Object_Init(MonoObject* InMonoObject) const
{
	FMonoDomain::Runtime_Object_Init(InMonoObject);
}

MonoClass* FDomain::Class_From_Name(const FString& InNameSpace, const FString& InMonoClassName) const
{
	return FMonoDomain::Class_From_Name(InNameSpace, InMonoClassName);
}

MonoMethod* FDomain::Class_Get_Method_From_Name(MonoClass* InMonoClass, const FString& InFunctionName,
                                                const int32 InParamCount) const
{
	return FMonoDomain::Class_Get_Method_From_Name(InMonoClass, InFunctionName, InParamCount);
}

mono_bool FDomain::Class_Is_Subclass_Of(MonoClass* InMonoClass, MonoClass* InSuperMonoClass,
                                        const mono_bool bCheckInterfaces) const
{
	return FMonoDomain::Class_Is_Subclass_Of(InMonoClass, InSuperMonoClass, bCheckInterfaces);
}

const char* FDomain::Class_Get_Name(MonoClass* InMonoClass) const
{
	return FMonoDomain::Class_Get_Name(InMonoClass);
}

MonoClass* FDomain::Class_Get_Parent(MonoClass* InMonoClass) const
{
	return FMonoDomain::Class_Get_Parent(InMonoClass);
}

MonoType* FDomain::Class_Get_Type(MonoClass* InMonoClass) const
{
	return FMonoDomain::Class_Get_Type(InMonoClass);
}

MonoClassField* FDomain::Class_Get_Fields(MonoClass* InMonoClass, void** InIterator) const
{
	return FMonoDomain::Class_Get_Fields(InMonoClass, InIterator);
}

MonoProperty* FDomain::Class_Get_Properties(MonoClass* InMonoClass, void** InIterator) const
{
	return FMonoDomain::Class_Get_Properties(InMonoClass, InIterator);
}

MonoMethod* FDomain::Class_Get_Methods(MonoClass* InMonoClass, void** InIterator) const
{
	return FMonoDomain::Class_Get_Methods(InMonoClass, InIterator);
}

MonoCustomAttrInfo* FDomain::Custom_Attrs_From_Class(MonoClass* InMonoClass) const
{
	return FMonoDomain::Custom_Attrs_From_Class(InMonoClass);
}

MonoCustomAttrInfo* FDomain::Custom_Attrs_From_Field(MonoClass* InMonoClass, MonoClassField* InMonoClassField) const
{
	return FMonoDomain::Custom_Attrs_From_Field(InMonoClass, InMonoClassField);
}

MonoCustomAttrInfo* FDomain::Custom_Attrs_From_Property(MonoClass* InMonoClass, MonoProperty* InMonoProperty) const
{
	return FMonoDomain::Custom_Attrs_From_Property(InMonoClass, InMonoProperty);
}

MonoCustomAttrInfo* FDomain::Custom_Attrs_From_Method(MonoMethod* InMonoMethod) const
{
	return FMonoDomain::Custom_Attrs_From_Method(InMonoMethod);
}

mono_bool FDomain::Custom_Attrs_Has_Attr(MonoCustomAttrInfo* InMonoCustomAttrInfo, MonoClass* InMonoClass) const
{
	return FMonoDomain::Custom_Attrs_Has_Attr(InMonoCustomAttrInfo, InMonoClass);
}

const char* FDomain::Field_Get_Name(MonoClassField* InMonoClassField) const
{
	return FMonoDomain::Field_Get_Name(InMonoClassField);
}

MonoType* FDomain::Field_Get_Type(MonoClassField* InMonoClassField) const
{
	return FMonoDomain::Field_Get_Type(InMonoClassField);
}

MonoObject* FDomain::Field_Get_Value_Object(MonoDomain* InMonoDomain, MonoClassField* InMonoClassField,
                                            MonoObject* InMonoObject) const
{
	return FMonoDomain::Field_Get_Value_Object(InMonoDomain, InMonoClassField, InMonoObject);
}

const char* FDomain::Property_Get_Name(MonoProperty* InMonoProperty) const
{
	return FMonoDomain::Property_Get_Name(InMonoProperty);
}

MonoMethod* FDomain::Property_Get_Get_Method(MonoProperty* InMonoProperty) const
{
	return FMonoDomain::Property_Get_Get_Method(InMonoProperty);
}

const char* FDomain::Method_Get_Name(MonoMethod* InMonoMethod) const
{
	return FMonoDomain::Method_Get_Name(InMonoMethod);
}

void FDomain::Method_Get_Param_Names(MonoMethod* InMonoMethod, const char** InNames) const
{
	FMonoDomain::Method_Get_Param_Names(InMonoMethod, InNames);
}

MonoMethodSignature* FDomain::Method_Signature(MonoMethod* InMonoMethod) const
{
	return FMonoDomain::Method_Signature(InMonoMethod);
}

uint32_t FDomain::Signature_Get_Param_Count(MonoMethodSignature* InMonoMethodSignature) const
{
	return FMonoDomain::Signature_Get_Param_Count(InMonoMethodSignature);
}

MonoType* FDomain::Signature_Get_Params(MonoMethodSignature* InMonoMethodSignature, void** InIterator) const
{
	return FMonoDomain::Signature_Get_Params(InMonoMethodSignature, InIterator);
}

MonoType* FDomain::Signature_Get_Return_Type(MonoMethodSignature* InMonoMethodSignature) const
{
	return FMonoDomain::Signature_Get_Return_Type(InMonoMethodSignature);
}

MonoType* FDomain::Reflection_Type_Get_Type(MonoReflectionType* InMonoReflectionType) const
{
	return FMonoDomain::Reflection_Type_Get_Type(InMonoReflectionType);
}

MonoClass* FDomain::Type_Get_Class(MonoType* InMonoType) const
{
	return FMonoDomain::Type_Get_Class(InMonoType);
}

MonoReflectionType* FDomain::Type_Get_Object(MonoType* InMonoType) const
{
	return FMonoDomain::Type_Get_Object(InMonoType);
}

MonoType* FDomain::Type_Get_Underlying_Type(MonoType* InMonoType) const
{
	return FMonoDomain::Type_Get_Underlying_Type(InMonoType);
}

mono_bool FDomain::Type_Is_ByRef(MonoType* InMonoType) const
{
	return FMonoDomain::Type_Is_ByRef(InMonoType);
}

MonoReflectionMethod* FDomain::Method_Get_Object(MonoMethod* InMethod, MonoClass* InMonoClass) const
{
	return FMonoDomain::Method_Get_Object(InMethod, InMonoClass);
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

MonoObject* FDomain::Value_Box(MonoClass* InMonoClass, void* InValue) const
{
	return FMonoDomain::Value_Box(InMonoClass, InValue);
}

void* FDomain::Object_Unbox(MonoObject* InMonoObject) const
{
	return FMonoDomain::Object_Unbox(InMonoObject);
}

MonoString* FDomain::String_New(const char* InText) const
{
	return FMonoDomain::String_New(InText);
}

MonoString* FDomain::Object_To_String(MonoObject* InMonoObject, MonoObject** InExc) const
{
	return FMonoDomain::Object_To_String(InMonoObject, InExc);
}

char* FDomain::String_To_UTF8(MonoString* InMonoString) const
{
	return FMonoDomain::String_To_UTF8(InMonoString);
}

MonoArray* FDomain::Array_New(MonoClass* InMonoClass, const uint32 InNum) const
{
	return FMonoDomain::Array_New(InMonoClass, InNum);
}

uint64 FDomain::Array_Length(MonoArray* InMonoArray) const
{
	return FMonoDomain::Array_Length(InMonoArray);
}

MonoClass* FDomain::Get_Byte_Class() const
{
	return FMonoDomain::Get_Byte_Class();
}

MonoClass* FDomain::Get_Object_Class() const
{
	return FMonoDomain::Get_Object_Class();
}

MonoClass* FDomain::Get_UInt16_Class() const
{
	return FMonoDomain::Get_UInt16_Class();
}

MonoClass* FDomain::Get_UInt32_Class() const
{
	return FMonoDomain::Get_UInt32_Class();
}

MonoClass* FDomain::Get_UInt64_Class() const
{
	return FMonoDomain::Get_UInt64_Class();
}

MonoClass* FDomain::Get_SByte_Class() const
{
	return FMonoDomain::Get_SByte_Class();
}

MonoClass* FDomain::Get_Int16_Class() const
{
	return FMonoDomain::Get_Int16_Class();
}

MonoClass* FDomain::Get_Int32_Class() const
{
	return FMonoDomain::Get_Int32_Class();
}

MonoClass* FDomain::Get_Int64_Class() const
{
	return FMonoDomain::Get_Int64_Class();
}

MonoClass* FDomain::Get_Boolean_Class() const
{
	return FMonoDomain::Get_Boolean_Class();
}

MonoClass* FDomain::Get_Single_Class() const
{
	return FMonoDomain::Get_Single_Class();
}

MonoClass* FDomain::Get_Enum_Class() const
{
	return FMonoDomain::Get_Enum_Class();
}

MonoClass* FDomain::Get_Double_Class() const
{
	return FMonoDomain::Get_Double_Class();
}

uint32 FDomain::GCHandle_New(MonoObject* InMonoObject, const mono_bool bPinned) const
{
	return FMonoDomain::GCHandle_New(InMonoObject, bPinned);
}

uint32 FDomain::GCHandle_New_WeakRef(MonoObject* InMonoObject, const mono_bool bTrackResurrection) const
{
	return FMonoDomain::GCHandle_New_WeakRef(InMonoObject, bTrackResurrection);
}

MonoObject* FDomain::GCHandle_Get_Target(const uint32 InGCHandle) const
{
	return FMonoDomain::GCHandle_Get_Target(InGCHandle);
}

void FDomain::GCHandle_Free(const uint32 InGCHandle) const
{
	FMonoDomain::GCHandle_Free(InGCHandle);
}

MonoGCHandle FDomain::GCHandle_New_V2(MonoObject* InMonoObject, const mono_bool bPinned)
{
	return GCHandle_New_V2(InMonoObject, Object_Get_Class(InMonoObject), bPinned);
}

MonoGCHandle FDomain::GCHandle_New_V2(MonoObject* InMonoObject, MonoClass* InMonoClass, const mono_bool bPinned)
{
	const auto GarbageCollectionHandle = FMonoDomain::GCHandle_New_V2(InMonoObject, bPinned);

	auto InParams = static_cast<void*>(GarbageCollectionHandle);

	if (const auto SetGCHandleMonoMethod = Parent_Class_Get_Method_From_Name(
		InMonoClass, FUNCTION_SET_HANDLE, TGetArrayLength(InParams)))
	{
		Runtime_Invoke(SetGCHandleMonoMethod, InMonoObject, &InParams);
	}

	return GarbageCollectionHandle;
}

MonoGCHandle FDomain::GCHandle_New_WeakRef_V2(MonoObject* InMonoObject, const mono_bool bTrackResurrection)
{
	return GCHandle_New_WeakRef_V2(InMonoObject, Object_Get_Class(InMonoObject), bTrackResurrection);
}

MonoGCHandle FDomain::GCHandle_New_WeakRef_V2(MonoObject* InMonoObject, MonoClass* InMonoClass,
                                              mono_bool bTrackResurrection)
{
	const auto GarbageCollectionHandle = FMonoDomain::GCHandle_New_WeakRef_V2(InMonoObject, bTrackResurrection);

	auto InParams = static_cast<void*>(GarbageCollectionHandle);

	if (const auto SetGCHandleMonoMethod = Parent_Class_Get_Method_From_Name(
		InMonoClass, FUNCTION_SET_HANDLE, TGetArrayLength(InParams)))
	{
		Runtime_Invoke(SetGCHandleMonoMethod, InMonoObject, &InParams);
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

MonoMethod* FDomain::Parent_Class_Get_Method_From_Name(MonoClass* InMonoClass, const FString& InFunctionName,
                                                       const int32 InParamCount)
{
	return FMonoDomain::Parent_Class_Get_Method_From_Name(InMonoClass, InFunctionName, InParamCount);
}

MonoType* FDomain::Property_Get_Type(MonoProperty* InMonoProperty) const
{
	return FMonoDomain::Property_Get_Type(InMonoProperty);
}

void FDomain::InitializeSynchronizationContext()
{
	if (const auto SynchronizationContextClass = Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_SYNCHRONIZATION_CONTEXT))
	{
		if (const auto InitializeMonoMethod = Class_Get_Method_From_Name(
			SynchronizationContextClass, FUNCTION_SYNCHRONIZATION_CONTEXT_INITIALIZE, 0))
		{
			Runtime_Invoke(InitializeMonoMethod, nullptr, nullptr, nullptr);
		}
	}
}

void FDomain::DeinitializeSynchronizationContext()
{
	if (const auto SynchronizationContextClass = Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_SYNCHRONIZATION_CONTEXT))
	{
		if (const auto DeinitializeMonoMethod = Class_Get_Method_From_Name(
			SynchronizationContextClass, FUNCTION_SYNCHRONIZATION_CONTEXT_DEINITIALIZE, 0))
		{
			Runtime_Invoke(DeinitializeMonoMethod, nullptr, nullptr, nullptr);
		}
	}
}

MonoString* FDomain::GetTraceback() const
{
	if (FMonoDomain::Domain != nullptr)
	{
		if (const auto FoundMonoClass = Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_UTILS))
		{
			if (const auto FoundMethod = Class_Get_Method_From_Name(FoundMonoClass, FUNCTION_UTILS_GET_TRACEBACK, 0))
			{
				return reinterpret_cast<MonoString*>(Runtime_Invoke(FoundMethod, nullptr, nullptr));
			}
		}
	}

	return nullptr;
}
