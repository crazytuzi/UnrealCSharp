#pragma once

#if WITH_CORECLR
#include "Domain/Script/IScriptDomain.h"
#include "FCoreCLRTypes.h"
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

	virtual IManagedMethod GetMethod(const IManagedClass InManagedClass, const FString& InName,
	                                 int32 InParamCount) override;

	virtual void SetFieldStaticValue(const IManagedClass InManagedClass, const FString& InName, void* InValue) override;

	virtual void* GetFieldStaticValue(const IManagedClass InManagedClass, const FString& InName) override;

	virtual void SetPropertyValue(const IManagedHandle InManagedHandle, const FString& InName,
	                              void** InParams) override;

	virtual void* GetPropertyValue(const IManagedHandle InManagedHandle, const FString& InName,
	                               void** InParams) override;

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

private:
	void InitializeAssembly(const TArray<FString>& InAssemblies);

	void LoadAssembly(const TArray<FString>& InAssemblies);

	void UnloadAssembly();

private:
	void RegisterErrorWriter() const;

	void RegisterInterop(const FString& InAssembly);

	void RegisterLog() const;

	void RegisterSynchronizationContextTick();

	void RegisterBinding() const;

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

	bool bIsInitialized{};

	TArray<IManagedHandle> Assemblies;

	load_assembly_and_get_function_pointer_fn LoadAssemblyAndGetFunctionPointerFn{};

	assembly_loader_Load_from_stream_fn AssemblyLoaderLoadFromStreamFn{};

	assembly_loader_unload_fn AssemblyLoaderUnLoadFn{};

	handle_data_alloc_fn HandleDataAllocFn{};

	handle_data_alloc_weak_ref_fn HandleDataAllocWeakRefFn{};

	handle_data_get_target_fn HandleDataGetTargetFn{};

	handle_data_free_fn HandleDataFreeFn{};

	log_bridge_set_log_fn LogBridgeSetLogFn{};

	log_bridge_initialize_fn LogBridgeInitializeFn{};

	log_bridge_deinitialize_fn LogBridgeDeinitializeFn{};

	type_bridge_get_class_fn TypeBridgeGetClassFn{};

	type_bridge_get_type_fn TypeBridgeGetTypeFn{};

	type_bridge_get_method_fn TypeBridgeGetMethodFn{};

	type_bridge_get_function_pointer_fn TypeBridgeGetFunctionPointerFn{};

	type_bridge_get_namespace_fn TypeBridgeGetNamespaceFn{};

	type_bridge_get_name_fn TypeBridgeGetNameFn{};

	type_bridge_get_full_name_fn TypeBridgeGetFullNameFn{};

	type_bridge_make_generic_type_fn TypeBridgeMakeGenericTypeFn{};

	type_bridge_make_generic_type2_fn TypeBridgeMakeGenericType2Fn{};

	type_bridge_box_bool_fn TypeBridgeBoxBoolFn{};

	type_bridge_box_sbyte_fn TypeBridgeBoxSByteFn{};

	type_bridge_box_int16_fn TypeBridgeBoxInt16Fn{};

	type_bridge_box_int32_fn TypeBridgeBoxInt32Fn{};

	type_bridge_box_int64_fn TypeBridgeBoxInt64Fn{};

	type_bridge_box_byte_fn TypeBridgeBoxByteFn{};

	type_bridge_box_uint16_fn TypeBridgeBoxUInt16Fn{};

	type_bridge_box_uint32_fn TypeBridgeBoxUInt32Fn{};

	type_bridge_box_uint64_fn TypeBridgeBoxUInt64Fn{};

	type_bridge_box_float_fn TypeBridgeBoxFloatFn{};

	type_bridge_box_double_fn TypeBridgeBoxDoubleFn{};

	type_bridge_unbox_bool_fn TypeBridgeUnboxBoolFn{};

	type_bridge_unbox_sbyte_fn TypeBridgeUnboxSByteFn{};

	type_bridge_unbox_int16_fn TypeBridgeUnboxInt16Fn{};

	type_bridge_unbox_int32_fn TypeBridgeUnboxInt32Fn{};

	type_bridge_unbox_int64_fn TypeBridgeUnboxInt64Fn{};

	type_bridge_unbox_byte_fn TypeBridgeUnboxByteFn{};

	type_bridge_unbox_uint16_fn TypeBridgeUnboxUInt16Fn{};

	type_bridge_unbox_uint32_fn TypeBridgeUnboxUInt32Fn{};

	type_bridge_unbox_uint64_fn TypeBridgeUnboxUInt64Fn{};

	type_bridge_unbox_float_fn TypeBridgeUnboxFloatFn{};

	type_bridge_unbox_double_fn TypeBridgeUnboxDoubleFn{};

	object_bridge_new_object_fn ObjectBridgeNewObjectFn{};

	field_bridge_set_static_value_fn FieldHelperSetStaticValueFn{};

	field_bridge_get_static_value_fn FieldHelperGetStaticValueFn{};

	method_bridge_register_binding_fn MethodBridgeRegisterBindingFn{};

	method_bridge_invoke_fn MethodBridgeInvokeFn{};

	string_bridge_new_string_fn StringBridgeNewStringFn{};

	string_bridge_get_string_fn StringBridgeGetStringFn{};

	array_bridge_new_array_fn ArrayHelperNewArrayFn{};

	array_bridge_array_get_fn ArrayHelperArrayGetFn{};

	array_bridge_array_get_ref_fn ArrayHelperArrayGetRefFn{};

	synchronization_context_tick_fn SynchronizationContextTickFn{};
};
#endif
