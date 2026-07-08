#pragma once

#if WITH_MONO
#include "Domain/Script/IManagedHandle.h"
#include "Domain/Script/IScriptTypes.h"
#include "Domain/Script/IScriptDomain.h"
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
	virtual FString GetNamespace(const IManagedHandle InManagedClass) override;

	virtual FString GetName(const IManagedHandle InManagedClass) override;

	virtual FString GetFullName(const IManagedHandle InManagedClass) override;

	virtual IManagedHandle NewObject(const IManagedHandle InManagedClass) override;

	virtual IManagedHandle BoxValue(const FString& InNamespace, const FString& InName, void* InValue) override;

	virtual void* UnboxValue(const IManagedHandle InManagedHandle) override;

	virtual IManagedHandle NewString(const char* InText) override;

	virtual FString StringToFString(const IManagedHandle InManagedHandle) override;

	virtual void Free(const IManagedHandle InManagedHandle) override;

	virtual IManagedHandle NewArray(const FString& InNamespace, const FString& InName, int32 InLength) override;

	virtual IManagedHandle ArrayGet(const IManagedHandle InManagedArray, int32 InIndex) override;

	virtual IManagedHandle GetClass(const FString& InNamespace, const FString& InName) override;

	virtual IManagedHandle GetMethod(const IManagedHandle InManagedClass,
	                                 const FString& InName, int32 InParamCount) override;

	virtual void SetFieldStaticValue(const IManagedHandle InManagedClass, const FString& InName,
	                                 void* InValue) override;

	virtual void* GetFieldStaticValue(const IManagedHandle InManagedClass, const FString& InName) override;

	virtual void SetPropertyValue(const IManagedHandle InManagedHandle,
	                              const FString& InName, void** InParams) override;

	virtual FClassReflection* MakeGenericType(const FClassReflection* InGeneric,
	                                          const FClassReflection* InType) override;

	virtual FClassReflection* MakeGenericType(const FClassReflection* InGeneric,
	                                          const FClassReflection* InKeyType,
	                                          const FClassReflection* InValueType) override;

	virtual IManagedHandle Invoke(const IManagedHandle InManagedHandle, const IManagedHandle InManagedMethod,
	                              int32 InParamCount = 0, void** InParams = nullptr) override;

	virtual void GetClassReflection(const IManagedHandle InManagedClass, PTRINT* OutParams) override;

public:
	virtual bool IsInitialized() const override;

	virtual TArray<IManagedHandle> GetAssemblies() const override;

	virtual TArray<FClassReflection*> GetClassesWithAttribute(const FClassReflection* InClass,
	                                                          const IManagedHandle InManagedHandle) override;

public:
	static MonoObject* Object_New(MonoClass* InManagedClass);

	static MonoObject* Value_Box(MonoClass* InManagedClass, void* InValue);

	static MonoString* String_New(const char* InText);

	static MonoMethod* Class_Get_Method_From_Name(MonoClass* InManagedClass, const FString& InName,
	                                              int32 InParamCount);

	static MonoObject* Runtime_Invoke(MonoMethod* InManagedMethod, MonoObject* InManagedObject,
	                                  void** InParams);

	static MonoObject* Runtime_Invoke(MonoMethod* InManagedMethod, MonoObject* InManagedObject,
	                                  void** InParams, MonoObject** InExc);

public:
	static void Unhandled_Exception(MonoObject* InManagedObject);

	static void Free(void* InPointer);

	static void* Method_Get_Unmanaged_Callers_Only_Ftnptr(MonoMethod* InManagedMethod);

public:
	static MonoObject* Object_Init(MonoClass* InManagedClass, int32 InParamCount = 0,
	                               void** InParams = nullptr);

	static void Object_Constructor(MonoObject* InManagedObject, int32 InParamCount = 0,
	                               void** InParams = nullptr);

	static MonoMethod* Class_Get_Method_From_Params(MonoClass* InManagedClass, const FString& InName,
	                                                const TArray<MonoType*>& InParams);

public:
	static MonoAssembly* AssemblyPreloadHook(MonoAssemblyName* InManagedAssemblyName,
	                                         char** OutAssemblyPath, void* InUserData);

	static void LoadAssembly(const FString& InAssemblyName, const TArray<uint8>& InData, MonoImage** OutImage,
	                         MonoAssembly** OutAssembly);

private:
	void InitializeAssembly(const TArray<FString>& InAssemblies);

	void LoadAssembly(const TArray<FString>& InAssemblies);

	void UnloadAssembly();

private:
	static void RegisterAssemblyPreloadHook();

	static void RegisterMonoTrace();

	void RegisterProfiler();

	void RegisterInterop(const FString& InAssembly);

	void RegisterLog();

	void RegisterBinding() const;

	void RegisterSynchronizationContextTick();

private:
	SCRIPT_TYPES

	TArray<IManagedHandle> Assemblies;

	bool bIsInitialized{};

	static MonoDomain* Domain;
};
#endif
