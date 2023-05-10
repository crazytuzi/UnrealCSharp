#pragma once

#include "Domain/FMonoDomain.h"

class FDomain final : public FTickableGameObject
{
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

	MonoObject* Object_New(MonoClass* InMonoClass, const int32 InParamCount, void** InParams) const;

	void Runtime_Object_Init(MonoObject* InMonoObject) const;

	MonoClass* Class_From_Name(const FString& InNameSpace, const FString& InMonoClassName) const;

	MonoMethod* Class_Get_Method_From_Name(MonoClass* InMonoClass, const FString& InFunctionName,
	                                       int32 InParamCount) const;

	mono_bool Class_Is_Subclass_Of(MonoClass* InMonoClass, MonoClass* InSuperMonoClass,
	                               mono_bool bCheckInterfaces) const;

	const char* Class_Get_Name(MonoClass* InMonoClass) const;

	MonoClass* Class_Get_Parent(MonoClass* InMonoClass) const;

	MonoType* Class_Get_Type(MonoClass* InMonoClass) const;

	MonoClassField* Class_Get_Fields(MonoClass* InMonoClass, void** InIterator) const;

	MonoCustomAttrInfo* Custom_Attrs_From_Field(MonoClass* InMonoClass, MonoClassField* InMonoClassField) const;

	mono_bool Custom_Attrs_Has_Attr(MonoCustomAttrInfo* InMonoCustomAttrInfo, MonoClass* InMonoClass) const;

	const char* Field_Get_Name(MonoClassField* InMonoClassField) const;

	MonoType* Field_Get_Type(MonoClassField* InMonoClassField) const;

	MonoType* Reflection_Type_Get_Type(MonoReflectionType* InMonoReflectionType) const;

	MonoClass* Type_Get_Class(MonoType* InMonoType) const;

	MonoReflectionType* Type_Get_Object(MonoType* InMonoType) const;

	MonoType* Type_Get_Underlying_Type(MonoType* InMonoType) const;

	MonoReflectionMethod* Method_Get_Object(MonoMethod* InMethod, MonoClass* InMonoClass) const;

	MonoObject* Runtime_Invoke(MonoMethod* InFunction, void* InMonoObject, void** InParams) const;

	MonoObject* Runtime_Invoke(MonoMethod* InFunction, void* InMonoObject, void** InParams, MonoObject** InExc) const;

	MonoObject* Runtime_Delegate_Invoke(MonoObject* InDelegate, void** InParams) const;

	MonoObject* Runtime_Delegate_Invoke(MonoObject* InDelegate, void** InParams, MonoObject** InExc) const;

	void Unhandled_Exception(MonoObject* InException) const;

	MonoClass* Object_Get_Class(MonoObject* InMonoObject) const;

	MonoObject* Value_Box(MonoClass* InMonoClass, void* InValue) const;

	void* Object_Unbox(MonoObject* InMonoObject) const;

	MonoString* String_New(const char* InText) const;

	MonoString* Object_To_String(MonoObject* InMonoObject, MonoObject** InExc) const;

	char* String_To_UTF8(MonoString* InMonoString) const;

	MonoArray* Array_New(MonoClass* InMonoClass, uint32 InNum) const;

	uint64 Array_Length(MonoArray* InMonoArray) const;

	MonoClass* Get_Byte_Class() const;

	MonoClass* Get_Object_Class() const;

	MonoClass* Get_UInt16_Class() const;;

	MonoClass* Get_UInt32_Class() const;

	MonoClass* Get_UInt64_Class() const;

	MonoClass* Get_Int16_Class() const;

	MonoClass* Get_Int32_Class() const;

	MonoClass* Get_Int64_Class() const;

	MonoClass* Get_Boolean_Class() const;

	MonoClass* Get_Single_Class() const;

	MonoClass* Get_Enum_Class() const;

	MonoClass* Get_Double_Class() const;

	uint32 GCHandle_New(MonoObject* InMonoObject, mono_bool bPinned) const;

	uint32 GCHandle_New_WeakRef(MonoObject* InMonoObject, mono_bool bTrackResurrection) const;

	MonoObject* GCHandle_Get_Target(uint32 InGCHandle) const;

	void GCHandle_Free(uint32 InGCHandle) const;

	MonoMethod* Parent_Class_Get_Method_From_Name(MonoClass* InMonoClass, const FString& InFunctionName,
	                                              int32 InParamCount) const;

public:
	void InitializeSynchronizationContext();

	void DeinitializeSynchronizationContext();

	MonoString* GetTraceback() const;

private:
	void RegisterBinding() const;
};
