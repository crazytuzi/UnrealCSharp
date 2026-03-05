#pragma once

#include "FMonoObjectTypes.h"
#include "FMonoDomainInitializeParams.h"
#include "mono/metadata/appdomain.h"

class UNREALCSHARPCORE_API FMonoDomain
{
public:
	static void Initialize(const FMonoDomainInitializeParams& InParams);

	static void Deinitialize();

public:
	static MonoObject* Object_New(MonoClass* InMonoClass);

	static MonoObject* Object_Init(MonoClass* InMonoClass, const int32 InParamCount = 0, void** InParams = nullptr);

	static MonoVTable* Class_VTable(MonoClass* InMonoClass);

	static MonoClass* Class_From_Name(const FString& InNameSpace, const FString& InMonoClassName);

	static MonoMethod* Class_Get_Method_From_Name(MonoClass* InMonoClass, const FString& InFunctionName,
	                                              int32 InParamCount);

	static mono_bool Class_Is_Subclass_Of(MonoClass* InMonoClass, MonoClass* InSuperMonoClass,
	                                      mono_bool bCheckInterfaces);

	static MonoType* Class_Get_Type(MonoClass* InMonoClass);

	static void Field_Static_Set_Value(MonoVTable* InMonoVTable, MonoClassField* InMonoClassField, void* InValue);

	static MonoObject* Field_Get_Value_Object(MonoClassField* InMonoClassField, MonoObject* InMonoObject);

	static void Property_Set_Value(MonoProperty* InMonoProperty, void* InMonoObject, void** InParams,
	                               MonoObject** InExc);

	static MonoObject* Property_Get_Value(MonoProperty* InMonoProperty, void* InMonoObject, void** InParams,
	                                      MonoObject** InExc);

	static MonoType* Reflection_Type_Get_Type(MonoReflectionType* InMonoReflectionType);

	static MonoClass* Class_From_Type(MonoType* InMonoType);

	static MonoReflectionType* Type_Get_Object(MonoType* InMonoType);

	static MonoObject* Runtime_Invoke(MonoMethod* InFunction, void* InMonoObject, void** InParams);

	static MonoObject* Runtime_Invoke(MonoMethod* InFunction, void* InMonoObject, void** InParams, MonoObject** InExc);

	static MonoObject* Runtime_Invoke_Array(MonoMethod* InFunction, void* InMonoObject, MonoArray* InParams);

	static MonoObject* Runtime_Invoke_Array(MonoMethod* InFunction, void* InMonoObject, MonoArray* InParams,
	                                        MonoObject** InExc);

	static void Unhandled_Exception(MonoObject* InException);

	static MonoObject* Value_Box(MonoClass* InMonoClass, void* InValue);

	static void* Object_Unbox(MonoObject* InMonoObject);

	static MonoString* String_New(const char* InText);

	static char* String_To_UTF8(MonoString* InMonoString);

	static MonoArray* Array_New(MonoClass* InMonoClass, uint32 InNum);

	static MonoClass* Get_Byte_Class();

	static MonoClass* Get_Object_Class();

	static MonoClass* Get_UInt16_Class();

	static MonoClass* Get_UInt32_Class();

	static MonoClass* Get_UInt64_Class();

	static MonoClass* Get_SByte_Class();

	static MonoClass* Get_Int16_Class();

	static MonoClass* Get_Int32_Class();

	static MonoClass* Get_Int64_Class();

	static MonoClass* Get_Boolean_Class();

	static MonoClass* Get_Single_Class();

	static MonoClass* Get_Enum_Class();

	static MonoClass* Get_Double_Class();

	static MonoGCHandle GCHandle_New_V2(MonoObject* InMonoObject, mono_bool bPinned);

	static MonoGCHandle GCHandle_New_WeakRef_V2(MonoObject* InMonoObject, mono_bool bTrackResurrection);

	static MonoObject* GCHandle_Get_Target_V2(MonoGCHandle InGCHandle);

	static void GCHandle_Free_V2(MonoGCHandle InGCHandle);

	static void* Method_Get_Unmanaged_Thunk(MonoMethod* InMonoMethod);

public:
	static void Object_Constructor(MonoObject* InMonoObject, int32 InParamCount = 0, void** InParams = nullptr);

	static MonoMethod* Class_Get_Method_From_Params(MonoClass* InMonoClass, const FString& InMethodName,
	                                                const TArray<MonoType*>& InParams);

	static const TArray<MonoGCHandle>& GetAssemblyGCHandles();

	static bool IsLoadSucceed();

	template <typename T>
	static auto Array_Addr(MonoArray* InArray, const uint64 InIndex) -> T;

	template <typename T>
	static auto Array_Get(MonoArray* InArray, const uint64 InIndex) -> T;

	template <typename T>
	static auto Array_Set(MonoArray* InArray, const uint64 InIndex, T InValue) -> void;

public:
	static MonoAssembly* AssemblyPreloadHook(MonoAssemblyName* InAssemblyName, char** OutAssemblyPath,
	                                         void* InUserData);

	static void LoadAssembly(const FString& InAssemblyName, const TArray<uint8>& InData,
	                         MonoImage** OutImage, MonoAssembly** OutAssembly);

	static void LoadAssembly(const FString& InAssemblyName, const FString& InFile,
	                         MonoImage** OutImage, MonoAssembly** OutAssembly);

	static void InitializeAssembly(const TArray<FString>& InAssemblies);

	static void DeinitializeAssembly();

	static void InitializeAssemblyLoadContext();

	static void DeinitializeAssemblyLoadContext();

	static void LoadAssembly(const TArray<FString>& InAssemblies);

	static void UnloadAssembly();

private:
	static void RegisterAssemblyPreloadHook();

	static void RegisterMonoTrace();

	static void RegisterLog();

	static void RegisterBinding();

	static void RegisterProfiler();

private:
	static MonoDomain* Domain;

	static MonoGCHandle AssemblyLoadContextGCHandle;

	static TArray<MonoGCHandle> AssemblyGCHandles;

	static TArray<MonoAssembly*> Assemblies;

	static TArray<MonoImage*> Images;

	static bool bLoadSucceed;
};

#include "FMonoDomain.inl"
