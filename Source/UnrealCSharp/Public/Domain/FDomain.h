#pragma once

#include "Domain/FMonoDomain.h"

class UNREALCSHARP_API FDomain final : public FTickableGameObject
{
private:
	typedef void (*SynchronizationContextTickType)(float, MonoException**);

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

	MonoObject* Object_Init(MonoClass* InMonoClass, const int32 InParamCount = 0, void** InParams = nullptr) const;

	MonoVTable* Class_VTable(MonoClass* InMonoClass);

	MonoClass* Class_From_Name(const FString& InNameSpace, const FString& InMonoClassName) const;

	MonoMethod* Class_Get_Method_From_Name(MonoClass* InMonoClass, const FString& InFunctionName,
	                                       int32 InParamCount) const;

	mono_bool Class_Is_Subclass_Of(MonoClass* InMonoClass, MonoClass* InSuperMonoClass,
	                               mono_bool bCheckInterfaces) const;

	MonoClass* Class_Get_Parent(MonoClass* InMonoClass) const;

	const char* Class_Get_Name(MonoClass* InMonoClass) const;

	const char* Class_Get_Namespace(MonoClass* InMonoClass) const;

	MonoType* Class_Get_Type(MonoClass* InMonoClass) const;

	MonoClassField* Class_Get_Field_From_Name(MonoClass* InMonoClass, const char* InName);

	MonoClassField* Class_Get_Fields(MonoClass* InMonoClass, void** InIterator) const;

	MonoProperty* Class_Get_Properties(MonoClass* InMonoClass, void** InIterator) const;

	MonoProperty* Class_Get_Property_From_Name(MonoClass* InMonoClass, const char* InName) const;

	MonoMethod* Class_Get_Methods(MonoClass* InMonoClass, void** InIterator) const;

	MonoClass* Class_Get_Interfaces(MonoClass* InMonoClass, void** InIterator) const;

	MonoCustomAttrInfo* Custom_Attrs_From_Class(MonoClass* InMonoClass) const;

	MonoCustomAttrInfo* Custom_Attrs_From_Field(MonoClass* InMonoClass, MonoClassField* InMonoClassField) const;

	MonoCustomAttrInfo* Custom_Attrs_From_Property(MonoClass* InMonoClass, MonoProperty* InMonoProperty) const;

	MonoCustomAttrInfo* Custom_Attrs_From_Method(MonoMethod* InMonoMethod) const;

	mono_bool Custom_Attrs_Has_Attr(MonoCustomAttrInfo* InMonoCustomAttrInfo, MonoClass* InMonoClass) const;

	MonoObject* Custom_Attrs_Get_Attr(MonoCustomAttrInfo* InMonoCustomAttrInfo, MonoClass* InMonoClass) const;

	void Field_Static_Set_Value(MonoVTable* InMonoVTable, MonoClassField* InMonoClassField, void* InValue);

	const char* Field_Get_Name(MonoClassField* InMonoClassField) const;

	MonoType* Field_Get_Type(MonoClassField* InMonoClassField) const;

	MonoObject* Field_Get_Value_Object(MonoDomain* InMonoDomain, MonoClassField* InMonoClassField,
	                                   MonoObject* InMonoObject) const;

	const char* Property_Get_Name(MonoProperty* InMonoProperty) const;

	MonoMethod* Property_Get_Get_Method(MonoProperty* InMonoProperty) const;

	static MonoProperty* Class_Get_Property_From_Name(MonoClass* InMonoClass, const FString& InName);

	static void Property_Set_Value(MonoProperty* InMonoProperty, void* InMonoObject, void** InParams,
	                               MonoObject** InExc);

	static MonoObject* Property_Get_Value(MonoProperty* InMonoProperty, void* InMonoObject, void** InParams,
	                                      MonoObject** InExc);

	const char* Method_Get_Name(MonoMethod* InMonoMethod) const;

	void Method_Get_Param_Names(MonoMethod* InMonoMethod, const char** InNames) const;

	MonoMethodSignature* Method_Signature(MonoMethod* InMonoMethod) const;

	uint32_t Signature_Get_Param_Count(MonoMethodSignature* InMonoMethodSignature) const;

	MonoType* Signature_Get_Params(MonoMethodSignature* InMonoMethodSignature, void** InIterator) const;

	MonoType* Signature_Get_Return_Type(MonoMethodSignature* InMonoMethodSignature) const;

	mono_bool Signature_Is_Instance(MonoMethodSignature* InMonoMethodSignature) const;

	MonoType* Reflection_Type_Get_Type(MonoReflectionType* InMonoReflectionType) const;

	MonoClass* Type_Get_Class(MonoType* InMonoType) const;

	MonoReflectionType* Type_Get_Object(MonoType* InMonoType) const;

	MonoType* Type_Get_Underlying_Type(MonoType* InMonoType) const;

	mono_bool Type_Is_ByRef(MonoType* InMonoType) const;

	MonoReflectionMethod* Method_Get_Object(MonoMethod* InMethod, MonoClass* InMonoClass) const;

	static MonoObject* Runtime_Invoke(MonoMethod* InFunction, void* InMonoObject, void** InParams);

	MonoObject* Runtime_Invoke(MonoMethod* InFunction, void* InMonoObject, void** InParams, MonoObject** InExc) const;

	static MonoObject* Runtime_Invoke_Array(MonoMethod* InFunction, void* InMonoObject, MonoArray* InParams);

	static MonoObject* Runtime_Invoke_Array(MonoMethod* InFunction, void* InMonoObject, MonoArray* InParams,
	                                        MonoObject** InExc);

	MonoObject* Runtime_Delegate_Invoke(MonoObject* InDelegate, void** InParams) const;

	MonoObject* Runtime_Delegate_Invoke(MonoObject* InDelegate, void** InParams, MonoObject** InExc) const;

	void Unhandled_Exception(MonoObject* InException) const;

	static MonoClass* Object_Get_Class(MonoObject* InMonoObject);

	MonoObject* Value_Box(MonoClass* InMonoClass, void* InValue) const;

	void* Object_Unbox(MonoObject* InMonoObject) const;

	MonoString* String_New(const char* InText) const;

	MonoString* Object_To_String(MonoObject* InMonoObject, MonoObject** InExc) const;

	char* String_To_UTF8(MonoString* InMonoString) const;

	MonoArray* Array_New(MonoClass* InMonoClass, uint32 InNum) const;

	uint64 Array_Length(MonoArray* InMonoArray) const;

	MonoClass* Get_Byte_Class() const;

	MonoClass* Get_Object_Class() const;

	MonoClass* Get_UInt16_Class() const;

	MonoClass* Get_UInt32_Class() const;

	MonoClass* Get_UInt64_Class() const;

	MonoClass* Get_SByte_Class() const;

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

	static MonoGCHandle GCHandle_New_V2(MonoObject* InMonoObject, mono_bool bPinned);

	static MonoGCHandle GCHandle_New_V2(MonoObject* InMonoObject, MonoClass* InMonoClass, const mono_bool bPinned);

	static MonoGCHandle GCHandle_New_WeakRef_V2(MonoObject* InMonoObject, mono_bool bTrackResurrection);

	static MonoGCHandle GCHandle_New_WeakRef_V2(MonoObject* InMonoObject, MonoClass* InMonoClass,
	                                            mono_bool bTrackResurrection);

	static MonoObject* GCHandle_Get_Target_V2(MonoGCHandle InGCHandle);

	static void GCHandle_Free_V2(MonoGCHandle InGCHandle);

	static void* Method_Get_Unmanaged_Thunk(MonoMethod* InMonoMethod);

	static void Object_Constructor(MonoObject* InMonoObject, int32 InParamCount = 0, void** InParams = nullptr);

	static void StaticClassSingleton_Reset(MonoClass* InMonoClass);

	static void StaticStructSingleton_Reset(MonoClass* InMonoClass);

	static MonoMethod* Parent_Class_Get_Method_From_Name(MonoClass* InMonoClass, const FString& InFunctionName,
	                                                     int32 InParamCount);

	static MonoClassField* Self_Class_Get_Field_From_Name(MonoClass* InMonoClass, const char* InName);

	MonoType* Property_Get_Type(MonoProperty* InMonoProperty) const;

	MonoMethod* Delegate_Get_Method(MonoObject* InDelegate) const;

	static mono_bool Type_Is_Class(MonoType* InMonoType);

	static mono_bool Type_Is_Enum(MonoType* InMonoType);

	SynchronizationContextTickType SynchronizationContextTick;

public:
	void InitializeSynchronizationContext();

	void DeinitializeSynchronizationContext();

	MonoString* GetTraceback() const;
};
