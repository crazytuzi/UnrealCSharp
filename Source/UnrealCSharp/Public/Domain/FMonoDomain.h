#pragma once

#include "mono/metadata/appdomain.h"

struct FMonoDomainInitializeParams
{
	FString Domain;

	TArray<FString> Assemblies;

	FMonoDomainInitializeParams(const FString& InDomain, const TArray<FString>& InAssemblies):
		Domain(InDomain),
		Assemblies(InAssemblies)
	{
	}
};

class FMonoDomain
{
public:
	explicit FMonoDomain(const FMonoDomainInitializeParams& Params);

	~FMonoDomain();

public:
	void Initialize(const FMonoDomainInitializeParams& Params);

	void Deinitialize();

public:
	MonoObject* Object_New(MonoClass* InMonoClass) const;

	MonoObject* Object_New(MonoClass* InMonoClass, const int32 InParamCount, void** InParams) const;

	void Runtime_Object_Init(MonoObject* InMonoObject) const;

	MonoClass* Class_From_Name(const FString& InNameSpace, const FString& InMonoClassName) const;

	MonoMethod* Class_Get_Method_From_Name(MonoClass* InMonoClass, const FString& InFunctionName,
	                                       int32 InParamCount) const;

	MonoMethod* Parent_Class_Get_Method_From_Name(MonoClass* InMonoClass, const FString& InFunctionName,
	                                              int32 InParamCount) const;

	mono_bool Class_Is_Subclass_Of(MonoClass* InMonoClass, MonoClass* InSuperMonoClass, mono_bool bCheckInterfaces);

	MonoType* Class_Get_Type(MonoClass* InMonoClass) const;

	MonoType* Reflection_Type_Get_Type(MonoReflectionType* InMonoReflectionType);

	MonoClass* Type_Get_Class(MonoType* InMonoType);

	MonoReflectionType* Type_Get_Object(MonoType* InMonoType);

	MonoType* Type_Get_Underlying_Type(MonoType* InMonoType) const;

	MonoReflectionMethod* Method_Get_Object(MonoMethod* InMethod, MonoClass* InMonoClass);

	MonoObject* Runtime_Invoke(MonoMethod* InFunction, void* InMonoObject, void** InParams) const;

	MonoObject* Runtime_Invoke(MonoMethod* InFunction, void* InMonoObject, void** InParams, MonoObject** InExc) const;

	MonoObject* Runtime_Delegate_Invoke(MonoObject* InDelegate, void** InParams);

	MonoObject* Runtime_Delegate_Invoke(MonoObject* InDelegate, void** InParams, MonoObject** InExc);

	void Unhandled_Exception(MonoObject* InException) const;

	MonoClass* Object_Get_Class(MonoObject* InMonoObject);

	MonoObject* Value_Box(MonoClass* InMonoClass, void* InValue) const;

	void* Object_Unbox(MonoObject* InMonoObject) const;

	MonoString* String_New(const char* InText) const;

	MonoString* Object_To_String(MonoObject* InMonoObject, MonoObject** InExc) const;

	char* String_To_UTF8(MonoString* InMonoString) const;

	MonoArray* Array_New(MonoClass* InMonoClass, uint32 InNum);

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

	uint32 GCHandle_New(MonoObject* InMonoObject, mono_bool bPinned);

	uint32 GCHandle_New_WeakRef(MonoObject* InMonoObject, mono_bool bTrackResurrection);

	MonoObject* GCHandle_Get_Target(uint32 InGCHandle);

	void GCHandle_Free(uint32 InGCHandle);

private:
	void RegisterMonoTrace();

	void RegisterLog();

	void RegisterBinding();

private:
	static MonoDomain* RootDomain;

	MonoDomain* Domain;

	TArray<MonoAssembly*> Assemblies;

	TArray<MonoImage*> Images;
};
