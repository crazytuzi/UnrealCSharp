#pragma once

#if WITH_MONO
#include "Domain/Script/IScriptDomain.h"
#include "FMonoTypes.h"
#include "mono/metadata/appdomain.h"

class FClassReflection;

class UNREALCSHARPCORE_API FMonoDomain final : public IScriptDomain
{
public:
	FMonoDomain() = default;

	virtual ~FMonoDomain() override = default;

public:
	virtual void Initialize() override;

	virtual void Tick(float InDeltaTime) override;

	virtual void Deinitialize() override;

public:
	virtual FString GetNamespace(const IManagedClass InManagedClass) override;

	virtual FString GetName(const IManagedClass InManagedClass) override;

	virtual FString GetFullName(const IManagedClass InManagedClass) override;

	virtual IManagedHandle NewObject(const IManagedClass InManagedClass) override;

	virtual IManagedHandle BoxValue(const IManagedClass InManagedClass, void* InValue) override;

	virtual IManagedHandle BoxValue(const FString& InNamespace, const FString& InName, void* InValue) override;

	virtual void* UnboxValue(const IManagedHandle InManagedHandle) override;

	virtual IManagedHandle NewString(const char* InText) override;

	virtual FString StringToFString(const IManagedHandle InManagedHandle) override;

	virtual IManagedHandle NewRef(const IManagedHandle InManagedHandle, bool bPinned) override;

	virtual IManagedHandle NewWeakRef(const IManagedHandle InManagedHandle, bool bTrackResurrection) override;

	virtual IManagedHandle GetTarget(const IManagedHandle InManagedHandle) override;

	virtual void Free(const IManagedHandle InManagedHandle) override;

	virtual IManagedArray NewArray(const IManagedClass InManagedClass, int32 InLength) override;

	virtual IManagedArray NewArray(const FString& InNamespace, const FString& InName, int32 InLength) override;

	virtual void* ArrayGet(const IManagedArray InManagedArray, int32 InIndex) override;

	virtual IManagedHandle ArrayGetRef(const IManagedArray InManagedArray, int32 InIndex) override;

	virtual IManagedClass GetClass(const FString& InNamespace, const FString& InName) override;

	virtual IManagedMethod GetMethod(const IManagedClass InManagedClass,
	                                 const FString& InName, int32 InParamCount) override;

	virtual void SetFieldStaticValue(const IManagedClass InManagedClass, const FString& InName, void* InValue) override;

	virtual void* GetFieldStaticValue(const IManagedClass InManagedClass, const FString& InName) override;

	virtual void SetPropertyValue(const IManagedHandle InManagedHandle,
	                              const FString& InName, void** InParams) override;

	virtual void* GetPropertyValue(const IManagedHandle InManagedHandle,
	                               const FString& InName, void** InParams) override;

	virtual FClassReflection* MakeGenericType(const FClassReflection* InGeneric,
	                                          const FClassReflection* InType) override;

	virtual FClassReflection* MakeGenericType(const FClassReflection* InGeneric,
	                                          const FClassReflection* InKeyType,
	                                          const FClassReflection* InValueType) override;

	virtual IManagedHandle Invoke(const IManagedHandle InManagedHandle, const IManagedMethod InManagedMethod,
	                              int32 InParamCount = 0, void** InParams = nullptr) override;

public:
	virtual bool IsInitialized() const override;

	virtual TArray<IManagedHandle> GetAssemblies() const override;

	virtual TArray<FClassReflection*> GetClassesWithAttribute(const FClassReflection* InClass,
	                                                          const IManagedHandle InManagedHandle) override;

public:
	static IManagedObject Object_New(const IManagedClass InManagedClass);

	static IManagedObject Value_Box(const IManagedClass InManagedClass, void* InValue);

	static void* Object_Unbox(const IManagedObject InManagedObject);

	static IManagedString String_New(const char* InText);

	static FString String_To_UTF8(const IManagedString InManagedString);

	static MonoGCHandle GCHandle_New_V2(const IManagedObject InManagedObject, mono_bool bPinned);

	static MonoGCHandle GCHandle_New_WeakRef_V2(const IManagedObject InManagedObject, mono_bool bTrackResurrection);

	static IManagedObject GCHandle_Get_Target_V2(MonoGCHandle InGCHandle);

	static void GCHandle_Free_V2(MonoGCHandle InGCHandle);

	static IManagedArray Array_New(const IManagedClass InManagedClass, uint32 InNum);

	template <typename T>
	static auto Array_Addr(const IManagedArray InManagedArray, const uint64 InIndex) -> T;

	template <typename T>
	static auto Array_Get(const IManagedArray InManagedArray, const uint64 InIndex) -> T;

	template <typename T>
	static auto Array_Set(const IManagedArray InManagedArray, const uint64 InIndex, T InValue) -> void;

	static IManagedClass Class_From_Name(const FString& InNameSpace, const FString& InName);

	static IManagedMethod Class_Get_Method_From_Name(const IManagedClass InManagedClass, const FString& InName,
	                                                 int32 InParamCount);

	static void Field_Static_Set_Value(const IManagedVTable InManagedVTable,
	                                   const IManagedClassField InManagedClassField, void* InValue);

	static void Field_Static_Get_Value(const IManagedVTable InManagedVTable,
	                                   const IManagedClassField InManagedClassField, void* OutValue);

	static IManagedObject Runtime_Invoke(const IManagedMethod InManagedMethod, const IManagedObject InManagedObject,
	                                     void** InParams);

	static IManagedObject Runtime_Invoke(const IManagedMethod InManagedMethod, const IManagedObject InManagedObject,
	                                     void** InParams, IManagedObject* InExc);

public:
	static IManagedVTable Class_VTable(const IManagedClass InManagedClass);

	static IManagedReflectionType Type_Get_Object(const IManagedType InManagedType);

	static IManagedType Class_Get_Type(const IManagedClass InManagedClass);

	static IManagedClassField Class_Get_Field_From_Name(const IManagedClass InManagedClass, const char* InName);

	static IManagedType Reflection_Type_Get_Type(const IManagedReflectionType InManagedReflectionType);

	static IManagedClass Class_From_Type(const IManagedType InManagedType);

	static void Unhandled_Exception(const IManagedObject InManagedObject);

	static void Free(void* InPointer);

	static IManagedClass Get_Object_Class();

	static IManagedClass Get_Boolean_Class();

	static IManagedClass Get_SByte_Class();

	static IManagedClass Get_Int16_Class();

	static IManagedClass Get_Int32_Class();

	static IManagedClass Get_Int64_Class();

	static IManagedClass Get_Byte_Class();

	static IManagedClass Get_UInt16_Class();

	static IManagedClass Get_UInt32_Class();

	static IManagedClass Get_UInt64_Class();

	static IManagedClass Get_Single_Class();

	static IManagedClass Get_Double_Class();

	static IManagedClass Get_Enum_Class();

	static void* Method_Get_Unmanaged_Thunk(const IManagedMethod InManagedMethod);

	static IManagedObject Runtime_Invoke_Array(const IManagedMethod InManagedMethod,
	                                           const IManagedObject InManagedObject, const IManagedArray InParams);

	static IManagedObject Runtime_Invoke_Array(const IManagedMethod InManagedMethod,
	                                           const IManagedObject InManagedObject, const IManagedArray InParams,
	                                           IManagedObject* InExc);

public:
	static IManagedObject Object_Init(const IManagedClass InManagedClass, int32 InParamCount = 0,
	                                  void** InParams = nullptr);

	static void Object_Constructor(const IManagedObject InManagedObject, int32 InParamCount = 0,
	                               void** InParams = nullptr);

	static IManagedMethod Class_Get_Method_From_Params(const IManagedClass InManagedClass, const FString& InName,
	                                                   const TArray<IManagedType>& InParams);

public:
	static IManagedAssembly AssemblyPreloadHook(const IManagedAssemblyName InManagedAssemblyName,
	                                            char** OutAssemblyPath, void* InUserData);

	static void LoadAssembly(const FString& InAssemblyName, const TArray<uint8>& InData, IManagedImage* OutImage,
	                         IManagedAssembly* OutAssembly);

	static void LoadAssembly(const FString& InAssemblyName, const FString& InFile, IManagedImage* OutImage,
	                         IManagedAssembly* OutAssembly);

private:
	void InitializeAssembly(const TArray<FString>& InAssemblies);

	void DeinitializeAssembly();

	void InitializeAssemblyLoadContext();

	void DeinitializeAssemblyLoadContext();

	void LoadAssembly(const TArray<FString>& InAssemblies);

	void UnloadAssembly();

private:
	static void RegisterAssemblyPreloadHook();

	static void RegisterMonoTrace();

	void RegisterLog();

	void RegisterBinding();

	void RegisterProfiler();

	void RegisterSynchronizationContextTick();

private:
	static MonoGCHandle HandleToMonoGCHandle(const IManagedHandle InManagedHandle);

	static IManagedHandle MonoGCHandleToHandle(MonoGCHandle InMonoGCHandle);

private:
	typedef void (*SynchronizationContextTickType)(float, IManagedObject*);
	SynchronizationContextTickType SynchronizationContextTick{};

	static MonoDomain* Domain;

	MonoGCHandle AssemblyLoadContextGCHandle{};

	static TArray<MonoGCHandle> AssemblyGCHandles;

	static TArray<IManagedAssembly> Assemblies;

	static TArray<IManagedImage> Images;

	bool bIsInitialized{};
};

#include "FMonoDomain.inl"
#endif
