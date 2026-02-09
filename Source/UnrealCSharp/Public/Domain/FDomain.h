#pragma once

#include "Tickable.h"
#include "Domain/FMonoDomain.h"

class UNREALCSHARP_API FDomain final : public FTickableGameObject
{
private:
	typedef void (*SynchronizationContextTickType)(float, MonoObject**);

public:
	explicit FDomain(const FMonoDomainInitializeParams& InParams);

	virtual ~FDomain() override;

public:
	void Initialize(const FMonoDomainInitializeParams& InParams);

	void Deinitialize();

public:
	virtual void Tick(float DeltaTime) override;

	virtual bool IsTickable() const override;

	virtual TStatId GetStatId() const override;

public:
	MonoObject* Object_New(MonoClass* InMonoClass) const;

	MonoObject* Object_Init(UStruct* InStruct, const int32 InParamCount = 0, void** InParams = nullptr) const;

	static MonoObject* Runtime_Invoke(MonoMethod* InFunction, void* InMonoObject, void** InParams);

	MonoObject* Runtime_Invoke(MonoMethod* InFunction, void* InMonoObject, void** InParams, MonoObject** InExc) const;

	static MonoObject* Runtime_Invoke_Array(MonoMethod* InFunction, void* InMonoObject, MonoArray* InParams);

	static MonoObject* Runtime_Invoke_Array(MonoMethod* InFunction, void* InMonoObject, MonoArray* InParams,
	                                        MonoObject** InExc);

	MonoObject* Runtime_Delegate_Invoke(MonoObject* InDelegate, void** InParams) const;

	MonoObject* Runtime_Delegate_Invoke(MonoObject* InDelegate, void** InParams, MonoObject** InExc) const;

	void Unhandled_Exception(MonoObject* InException) const;

	static MonoClass* Object_Get_Class(MonoObject* InMonoObject);

	static MonoObject* Value_Box(MonoClass* InMonoClass, void* InValue);

	static void* Object_Unbox(MonoObject* InMonoObject);

	static MonoString* String_New(const char* InText);

	static char* String_To_UTF8(MonoString* InMonoString);

	static MonoArray* Array_New(MonoClass* InMonoClass, uint32 InNum);

	static MonoGCHandle GCHandle_New_V2(UStruct* InStruct, MonoObject* InMonoObject, mono_bool bPinned);

	static MonoGCHandle GCHandle_New_V2(MonoClass* InMonoClass, MonoObject* InMonoObject, const mono_bool bPinned);

	static MonoGCHandle GCHandle_New_WeakRef_V2(MonoClass* InMonoClass,MonoObject* InMonoObject, 
	                                            mono_bool bTrackResurrection);
	
	static MonoGCHandle GCHandle_New_WeakRef_V2(UStruct* InStruct ,MonoObject* InMonoObject, 
												mono_bool bTrackResurrection);

	static MonoObject* GCHandle_Get_Target_V2(MonoGCHandle InGCHandle);

	static void GCHandle_Free_V2(MonoGCHandle InGCHandle);

	static void* Method_Get_Unmanaged_Thunk(MonoMethod* InMonoMethod);
	
	static void Object_Constructor(MonoObject* InMonoObject, int32 InParamCount = 0, void** InParams = nullptr);

	static void Object_Constructor(UStruct* InStruct, MonoObject* InMonoObject, int32 InParamCount = 0, void** InParams = nullptr);

	static MonoMethod* Parent_Class_Get_Method_From_Name(UStruct* InStruct, const FString& InFunctionName,
	                                                     int32 InParamCount);

	MonoMethod* Delegate_Get_Method(MonoObject* InDelegate) const;

	template <typename T>
	static auto Array_Get(MonoArray* InArray, const uint64 InIndex) -> T;

	template <typename T>
	static auto Array_Set(MonoArray* InArray, const uint64 InIndex, T InValue) -> void;

	SynchronizationContextTickType SynchronizationContextTick;

public:
	void InitializeSynchronizationContext();

	void DeinitializeSynchronizationContext();

	MonoString* GetTraceback() const;
};

#include "FDomain.inl"
