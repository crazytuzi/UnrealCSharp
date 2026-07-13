#pragma once

#if WITH_CORECLR
#include "Domain/Script/IManagedHandle.h"
#include "Domain/Script/IScriptTypes.h"
#include "Domain/Script/IScriptDomain.h"
#include "corehost/hostfxr.h"
#include "corehost/coreclr_delegates.h"

class UNREALCSHARPCORE_API FCoreCLRDomain final : public IScriptDomain
{
public:
	FCoreCLRDomain() = default;

	virtual ~FCoreCLRDomain() override;

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

	virtual IManagedHandle GetMethod(const IManagedHandle InManagedClass, const FString& InName,
	                                 int32 InParamCount) override;

	virtual void SetFieldStaticValue(const IManagedHandle InManagedClass, const FString& InName,
	                                 void* InValue) override;

	virtual void* GetFieldStaticValue(const IManagedHandle InManagedClass, const FString& InName) override;

	virtual void SetPropertyValue(const IManagedHandle InManagedHandle, const FString& InName,
	                              void** InParams) override;

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

private:
	void InitializeAssembly(const TArray<FString>& InAssemblies);

	void LoadAssembly(const TArray<FString>& InAssemblies);

	void UnloadAssembly();

private:
	void RegisterErrorWriter() const;

	void RegisterInterop(const FString& InAssembly);

	void RegisterLog();

	void RegisterBinding() const;

	void RegisterSynchronizationContextTick();

private:
	template <typename T>
	static T GetExport(void* InHandle, const FString& InName)
	{
		return reinterpret_cast<T>(FPlatformProcess::GetDllExport(InHandle, *InName));
	}

	template <typename T = void>
	static auto FStringToString(const FString& InString)
	{
		if constexpr (std::is_same_v<char_t, TCHAR>)
		{
			return StringCast<TCHAR>(*InString);
		}
		else
		{
			return StringCast<UTF8CHAR>(*InString);
		}
	}

	void LoadAssemblyAndGetFunctionPointer(const FString& InAssembly, const FString& InType, const FString& InMethod,
	                                       void** OutFunctionPointer) const;

private:
	void* HostFxrHandle{};

	hostfxr_handle HostContextHandle{};

	hostfxr_close_fn HostFxrCloseFn{};

	SCRIPT_TYPES

	TArray<IManagedHandle> Assemblies;

	bool bIsInitialized{};

	load_assembly_and_get_function_pointer_fn LoadAssemblyAndGetFunctionPointerFn{};
};
#endif
