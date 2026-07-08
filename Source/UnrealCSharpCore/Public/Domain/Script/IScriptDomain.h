#pragma once

#include "CoreMinimal.h"
#include "IManagedHandle.h"

class FClassReflection;

class UNREALCSHARPCORE_API IScriptDomain
{
public:
	virtual ~IScriptDomain() = default;

	static void Set(IScriptDomain* InScriptDomain);

	static IScriptDomain* Get();

public:
	virtual void Initialize() = 0;

	virtual void Tick(float InDeltaTime) = 0;

	virtual void Deinitialize() = 0;

public:
	virtual FString GetNamespace(const IManagedHandle InManagedClass) = 0;

	virtual FString GetName(const IManagedHandle InManagedClass) = 0;

	virtual FString GetFullName(const IManagedHandle InManagedClass) = 0;

	virtual IManagedHandle NewObject(const IManagedHandle InManagedClass) = 0;

	virtual IManagedHandle BoxValue(const FString& InNamespace, const FString& InName, void* InValue) = 0;

	virtual void* UnboxValue(const IManagedHandle InManagedHandle) = 0;

	virtual IManagedHandle NewString(const char* InText) = 0;

	virtual FString StringToFString(const IManagedHandle InManagedHandle) = 0;

	virtual void Free(const IManagedHandle InManagedHandle) = 0;

	virtual IManagedHandle NewArray(const FString& InNamespace, const FString& InName, int32 InLength) = 0;

	virtual IManagedHandle ArrayGet(const IManagedHandle InManagedArray, int32 InIndex) = 0;

	virtual IManagedHandle GetClass(const FString& InNamespace, const FString& InName) = 0;

	virtual IManagedHandle GetMethod(const IManagedHandle InManagedClass, const FString& InName,
	                                 int32 InParamCount) = 0;

	virtual void SetFieldStaticValue(const IManagedHandle InManagedClass, const FString& InName, void* InValue) = 0;

	virtual void* GetFieldStaticValue(const IManagedHandle InManagedClass, const FString& InName) = 0;

	virtual void SetPropertyValue(const IManagedHandle InManagedHandle, const FString& InName, void** InParams) = 0;

	virtual FClassReflection* MakeGenericType(const FClassReflection* InGeneric, const FClassReflection* InType) = 0;

	virtual FClassReflection* MakeGenericType(const FClassReflection* InGeneric,
	                                          const FClassReflection* InKeyType,
	                                          const FClassReflection* InValueType) = 0;

	virtual IManagedHandle Invoke(const IManagedHandle InManagedHandle, const IManagedHandle InManagedMethod,
	                              int32 InParamCount = 0, void** InParams = nullptr) = 0;

	virtual void GetClassReflection(const IManagedHandle InManagedClass, PTRINT* OutParams) = 0;

public:
	virtual bool IsInitialized() const = 0;

	virtual TArray<IManagedHandle> GetAssemblies() const = 0;

	virtual TArray<FClassReflection*> GetClassesWithAttribute(const FClassReflection* InClass,
	                                                          const IManagedHandle InManagedHandle) = 0;

private:
	static IScriptDomain* ScriptDomain;
};
