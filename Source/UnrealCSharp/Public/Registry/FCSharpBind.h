#pragma once

#include "Reflection/Class/FClassDescriptor.h"
#include "Reflection/Function/FCSharpFunctionOwnerClassInfo.h"

class UNREALCSHARP_API FCSharpBind
{
public:
	FCSharpBind();

	~FCSharpBind();

public:
	void Initialize();

	void Deinitialize();

public:
	template <auto IsNeedOverride>
	static auto Bind(UStruct* InStruct);

	static IManagedHandle Bind(UObject* InObject);

	static IManagedHandle Bind(UClass* InClass);

	template <auto IsNeedOverride>
	static auto Bind(UObject* InObject);

	template <typename T>
	static auto Bind(FClassReflection* InClassReflection, FClassReflection* InPropertyClassReflection,
	                 const IManagedHandle InManagedObject);

	template <typename T>
	static auto Bind(FClassReflection* InClassReflection, FClassReflection* InKeyClassReflection,
	                 FClassReflection* InValueClassReflection, const IManagedHandle InManagedObject);

	static bool Bind(const IManagedHandle InManagedObject, const FName& InStructName);

	template <typename T>
	static auto Bind(FClassReflection* InClassReflection, const IManagedHandle InManagedObject);

	static bool Bind(FClassDescriptor* InClassDescriptor, UClass* InClass, UFunction* InFunction);

	static bool Bind(FClassDescriptor* InClassDescriptor,
	                 UClass* InClass, const FString& InMethodName, UFunction* InFunction);

	static bool BindClassDefaultObject(UObject* InObject);

#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
	static void SuspendDummyOwnerClasses();

	static void ResumeDummyOwnerClasses();
#endif

private:
	template <auto IsNeedOverride>
	static auto BindImplementation(UObject* InObject) -> IManagedHandle;

	static bool BindImplementation(UStruct* InStruct);

	static bool BindImplementation(FClassDescriptor* InClassDescriptor, UClass* InClass,
	                               const FString& InMethodName, UFunction* InFunction);

	template <typename T>
	static auto BindImplementation(FClassReflection* InClassReflection, FClassReflection* InPropertyClassReflection,
	                               const IManagedHandle InManagedObject);

	template <typename T>
	static auto BindImplementation(FClassReflection* InClassReflection, FClassReflection* InKeyClassReflection,
	                               FClassReflection* InValueClassReflection, const IManagedHandle InManagedObject);

	static bool BindImplementation(const IManagedHandle InManagedObject, const FName& InStructName);

	template <typename T>
	static auto BindImplementation(FClassReflection* InClassReflection, const IManagedHandle InManagedObject);

private:
	static bool CanBind(UStruct* InStruct);

private:
	static UFunction* GetOriginalFunction(FClassDescriptor* InClassDescriptor, UFunction* InFunction);

	static bool IsCallCSharpFunction(const UFunction* InFunction);

#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
	static FCSharpFunctionOwnerClassInfo RegisterCallCSharpNativeFunction(UClass* InClass, UFunction* InFunction);
#else
	static void RegisterCallCSharpNativeFunction(UClass* InClass, UFunction* InFunction);
#endif

#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
	static UClass* GetOrCreateDummyOwnerClass(UClass* InClass);

	static UClass* GetOrCreateDummyOwnerClass(UFunction* InFunction);

	static UClass* GetOriginalOwnerClass(const UFunction* InFunction);
#endif

	static void RegisterScriptTick(const UClass* InClass, const UFunction* InFunction);

	static UFunction* DuplicateFunction(UFunction* InOriginalFunction, UClass* InClass, const FName& InFunctionName);

private:
	void OnCSharpEnvironmentInitialize();

private:
	static TSet<TWeakObjectPtr<UStruct>> NotOverrideTypes;

#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
	static TMap<TWeakObjectPtr<UClass>, TWeakObjectPtr<UClass>> OriginalOwnerClass2DummyOwnerClass;

	static const TCHAR* const DummyOwnerClassNamePrefix;
#endif

	FDelegateHandle OnCSharpEnvironmentInitializeDelegateHandle;
};

#include "FCSharpBind.inl"
