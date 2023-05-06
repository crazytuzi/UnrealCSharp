#pragma once

#include "mono/metadata/appdomain.h"

struct UNREALCSHARPCORE_API FMonoDomainInitializeParams
{
	FString Domain;

	FString AssemblyUtil;

	TArray<FString> Assemblies;

	FMonoDomainInitializeParams(const FString& InDomain, const FString& InAssemblyUtil,
	                            const TArray<FString>& InAssemblies):
		Domain(InDomain),
		AssemblyUtil(InAssemblyUtil),
		Assemblies(InAssemblies)
	{
	}
};

class FMonoDomain
{
public:
	static UNREALCSHARPCORE_API void Initialize(const FMonoDomainInitializeParams& InParams);

	static UNREALCSHARPCORE_API void Deinitialize();

public:
	static UNREALCSHARPCORE_API MonoObject* Object_New(MonoClass* InMonoClass);

	static UNREALCSHARPCORE_API MonoObject* Object_New(MonoClass* InMonoClass, const int32 InParamCount,
	                                                   void** InParams);

	static UNREALCSHARPCORE_API void Runtime_Object_Init(MonoObject* InMonoObject);

	static UNREALCSHARPCORE_API MonoClass* Class_From_Name(const FString& InNameSpace, const FString& InMonoClassName);

	static UNREALCSHARPCORE_API MonoMethod* Class_Get_Method_From_Name(MonoClass* InMonoClass,
	                                                                   const FString& InFunctionName,
	                                                                   int32 InParamCount);

	static UNREALCSHARPCORE_API mono_bool Class_Is_Subclass_Of(MonoClass* InMonoClass, MonoClass* InSuperMonoClass,
	                                                           mono_bool bCheckInterfaces);

	static UNREALCSHARPCORE_API const char* Class_Get_Name(MonoClass* InMonoClass);

	static UNREALCSHARPCORE_API MonoClass* Class_Get_Parent(MonoClass* InMonoClass);

	static UNREALCSHARPCORE_API MonoType* Class_Get_Type(MonoClass* InMonoClass);

	static UNREALCSHARPCORE_API MonoType* Reflection_Type_Get_Type(MonoReflectionType* InMonoReflectionType);

	static UNREALCSHARPCORE_API MonoClass* Type_Get_Class(MonoType* InMonoType);

	static UNREALCSHARPCORE_API MonoReflectionType* Type_Get_Object(MonoType* InMonoType);

	static UNREALCSHARPCORE_API MonoType* Type_Get_Underlying_Type(MonoType* InMonoType);

	static UNREALCSHARPCORE_API MonoReflectionMethod* Method_Get_Object(MonoMethod* InMethod, MonoClass* InMonoClass);

	static UNREALCSHARPCORE_API MonoObject* Runtime_Invoke(MonoMethod* InFunction, void* InMonoObject, void** InParams);

	static UNREALCSHARPCORE_API MonoObject* Runtime_Invoke(MonoMethod* InFunction, void* InMonoObject, void** InParams,
	                                                       MonoObject** InExc);

	static UNREALCSHARPCORE_API MonoObject* Runtime_Delegate_Invoke(MonoObject* InDelegate, void** InParams);

	static UNREALCSHARPCORE_API MonoObject* Runtime_Delegate_Invoke(MonoObject* InDelegate, void** InParams,
	                                                                MonoObject** InExc);

	static UNREALCSHARPCORE_API void Unhandled_Exception(MonoObject* InException);

	static UNREALCSHARPCORE_API MonoClass* Object_Get_Class(MonoObject* InMonoObject);

	static UNREALCSHARPCORE_API MonoObject* Value_Box(MonoClass* InMonoClass, void* InValue);

	static UNREALCSHARPCORE_API void* Object_Unbox(MonoObject* InMonoObject);

	static UNREALCSHARPCORE_API MonoString* String_New(const char* InText);

	static UNREALCSHARPCORE_API MonoString* Object_To_String(MonoObject* InMonoObject, MonoObject** InExc);

	static UNREALCSHARPCORE_API char* String_To_UTF8(MonoString* InMonoString);

	static UNREALCSHARPCORE_API MonoArray* Array_New(MonoClass* InMonoClass, uint32 InNum);

	static UNREALCSHARPCORE_API uint64 Array_Length(MonoArray* InMonoArray);

	static UNREALCSHARPCORE_API MonoClass* Get_Byte_Class();

	static UNREALCSHARPCORE_API MonoClass* Get_Object_Class();

	static UNREALCSHARPCORE_API MonoClass* Get_UInt16_Class();;

	static UNREALCSHARPCORE_API MonoClass* Get_UInt32_Class();

	static UNREALCSHARPCORE_API MonoClass* Get_UInt64_Class();

	static UNREALCSHARPCORE_API MonoClass* Get_Int16_Class();

	static UNREALCSHARPCORE_API MonoClass* Get_Int32_Class();

	static UNREALCSHARPCORE_API MonoClass* Get_Int64_Class();

	static UNREALCSHARPCORE_API MonoClass* Get_Boolean_Class();

	static UNREALCSHARPCORE_API MonoClass* Get_Single_Class();

	static UNREALCSHARPCORE_API MonoClass* Get_Enum_Class();

	static UNREALCSHARPCORE_API MonoClass* Get_Double_Class();

	static UNREALCSHARPCORE_API uint32 GCHandle_New(MonoObject* InMonoObject, mono_bool bPinned);

	static UNREALCSHARPCORE_API uint32 GCHandle_New_WeakRef(MonoObject* InMonoObject, mono_bool bTrackResurrection);

	static UNREALCSHARPCORE_API MonoObject* GCHandle_Get_Target(uint32 InGCHandle);

	static UNREALCSHARPCORE_API void GCHandle_Free(uint32 InGCHandle);

public:
	static UNREALCSHARPCORE_API MonoMethod* Parent_Class_Get_Method_From_Name(
		MonoClass* InMonoClass, const FString& InFunctionName,
		int32 InParamCount);

public:
	static UNREALCSHARPCORE_API void InitializeAssembly(const TArray<FString>& InAssemblies);

	static UNREALCSHARPCORE_API void DeinitializeAssembly();

	static UNREALCSHARPCORE_API void InitializeAssemblyLoadContext();

	static UNREALCSHARPCORE_API void DeinitializeAssemblyLoadContext();

	static UNREALCSHARPCORE_API void LoadAssembly(const TArray<FString>& InAssemblies);

	static UNREALCSHARPCORE_API void UnloadAssembly();

private:
	static void RegisterMonoTrace();

	static void RegisterLog();

public:
	static UNREALCSHARPCORE_API MonoDomain* Domain;

	static UNREALCSHARPCORE_API MonoAssembly* AssemblyUtilAssembly;

	static UNREALCSHARPCORE_API MonoImage* AssemblyUtilImage;

	static UNREALCSHARPCORE_API TArray<MonoGCHandle> AssemblyGCHandles;

	static UNREALCSHARPCORE_API TArray<MonoAssembly*> Assemblies;

	static UNREALCSHARPCORE_API TArray<MonoImage*> Images;
};
