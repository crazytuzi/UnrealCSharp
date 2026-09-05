#pragma once

#if WITH_LEANCLR
#include "Domain/Script/IManagedHandle.h"
#include "Domain/Script/IScriptTypes.h"
#include "Domain/Script/IScriptDomain.h"
THIRD_PARTY_INCLUDES_START
#include "metadata/rt_metadata.h"
#include "interp/interp_defs.h"
#include "vm/rt_managed_types.h"
#include "vm/settings.h"
THIRD_PARTY_INCLUDES_END

class FClassReflection;

class UNREALCSHARPCORE_API FLeanCLRDomain final : public IScriptDomain
{
public:
	FLeanCLRDomain() = default;

	virtual ~FLeanCLRDomain() override = default;

public:
	virtual void Initialize() override;

	virtual void Tick(float InDeltaTime) override;

	virtual void Deinitialize() override;

public:
	virtual FString GetNamespace(const IManagedHandle InManagedClass) override;

	virtual FString GetName(const IManagedHandle InManagedClass) override;

	virtual FString GetFullName(const IManagedHandle InManagedClass) override;

	virtual IManagedHandle NewObject(const IManagedHandle InManagedClass) override;

	virtual IManagedHandle BoxValue(const FString& InName, void* InValue) override;

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

	virtual bool IsOverride(const IManagedHandle InManagedClass) override;

	virtual void GetClassDescriptor(const IManagedHandle InManagedClass, PTRINT* OutParams) override;

	virtual void GetClassProperties(const IManagedHandle InManagedClass, PTRINT* OutParams) override;

	virtual void GetClassFields(const IManagedHandle InManagedClass, PTRINT* OutParams) override;

	virtual void GetClassMethods(const IManagedHandle InManagedClass, PTRINT* OutParams) override;

public:
	virtual bool IsInitialized() const override;

	virtual TArray<IManagedHandle> GetAssemblies() const override;

	virtual TArray<FClassReflection*> GetClassesWithAttribute(const FClassReflection* InClass,
	                                                          const IManagedHandle InManagedHandle) override;

private:
	static const leanclr::metadata::RtMethodInfo* Class_Get_Method_From_Name(
		leanclr::metadata::RtModuleDef* InManagedModule, const FString& InClassName, const FString& InMethodName);

	static bool Runtime_Invoke(const leanclr::metadata::RtMethodInfo* InManagedMethod,
	                           const leanclr::interp::RtStackObject* InParams, int32 InParamCount,
	                           leanclr::interp::RtStackObject& OutReturn);

	static bool Runtime_Invoke(const leanclr::metadata::RtMethodInfo* InManagedMethod,
	                           const leanclr::interp::RtStackObject* InParams,
	                           leanclr::interp::RtStackObject* OutReturn,
	                           leanclr::vm::RtException** InExc);

private:
	static void Unhandled_Exception(leanclr::vm::RtException* InException);

private:
	static const leanclr::metadata::RtMethodInfo* Method_Get_From_Handle(
		const leanclr::metadata::RtMethodInfo* InManagedBridge, IManagedHandle InManagedMethod);

	static bool Method_Is_ReferenceType_Constructor(const leanclr::metadata::RtMethodInfo* InManagedMethod);

	static const TPair<int32, int32>& Method_Get_Slot_Sizes(const leanclr::metadata::RtMethodInfo* InManagedMethod);

	static void Object_Constructor(const leanclr::metadata::RtMethodInfo* InManagedBridge,
	                               const leanclr::metadata::RtMethodInfo* InManagedConstructor,
	                               IManagedHandle InManagedHandle);

	static void* Object_Get_From_Handle(const leanclr::metadata::RtMethodInfo* InManagedBridge,
	                                    IManagedHandle InManagedHandle);

	static IManagedHandle Handle_Alloc_From_Object(const leanclr::metadata::RtMethodInfo* InManagedBridge,
	                                               leanclr::vm::RtObject* InManagedObject);

	static IManagedHandle Assembly_Alloc_Handle(const leanclr::metadata::RtMethodInfo* InManagedBridge,
	                                            leanclr::metadata::RtAssembly* InManagedAssembly);

	static int32 Type_Get_Boxed_Primitive_Size(const leanclr::metadata::RtElementType InElementType);

private:
	static leanclr::interp::RtStackObject Stack_Object_From(const IManagedHandle InManagedHandle);

	static leanclr::interp::RtStackObject Stack_Object_From(const int32 InValue);

	static leanclr::interp::RtStackObject Stack_Object_From(const int64 InValue);

	static leanclr::interp::RtStackObject Stack_Object_From(const float InValue);

	static leanclr::interp::RtStackObject Stack_Object_From(const void* InPointer);

	static leanclr::interp::RtStackObject Stack_Object_From(leanclr::vm::RtObject* InManagedObject);

	template <typename Result>
	static Result Stack_Object_To(const leanclr::interp::RtStackObject& InStackObject);

	template <typename T>
	struct TStackArgument;

	template <typename Return, typename... Args, auto... Index>
	static Return Bridge_Invoke_Helper(const leanclr::metadata::RtMethodInfo* InManagedMethod,
	                                   std::index_sequence<Index...>, Args&&... InArgs);

	template <typename Return = void, typename... Args>
	static Return Bridge_Invoke(const leanclr::metadata::RtMethodInfo* InManagedMethod, Args&&... InArgs);

private:
	struct FPInvokeSignature
	{
		UPTRINT Function{};

		int32 ParamCount{};

		leanclr::metadata::RtArgOrLocOrFieldReduceType ReturnType{};

		leanclr::RtErr Error{leanclr::RtErr::None};
	};

	static leanclr::RtErr PInvoke_Classify(const leanclr::metadata::RtMethodInfo* InManagedMethod,
	                                       FPInvokeSignature& OutSignature);

	static leanclr::RtResultVoid PInvoke_Dispatch(leanclr::metadata::RtManagedMethodPointer,
	                                              const leanclr::metadata::RtMethodInfo* InManagedMethod,
	                                              const leanclr::interp::RtStackObject* InParams,
	                                              leanclr::interp::RtStackObject* OutReturn) noexcept;

private:
	static bool FileLoader(const char* InAssemblyName, const char* InExtension, leanclr::vm::FileData& OutFileData);

private:
	bool InitializeAssembly(const TArray<FString>& InAssemblies);

	void LoadAssembly(const TArray<FString>& InAssemblies);

	void UnloadAssembly();

private:
	void RegisterInterop();

	void RegisterBinding() const;

private:
#define LEANCLR_INTEROP_BRIDGE_METHODS(Op) \
	Op(HandleDataGetObjectPointer, void, CLASS_HANDLE_DATA, FUNCTION_HANDLE_DATA_GET_OBJECT_POINTER, 1) \
	Op(HandleDataAlloc, void, CLASS_HANDLE_DATA, FUNCTION_HANDLE_DATA_ALLOC, 1)

#define LEANCLR_METHOD_MEMBER(Name, FnType, ClassNameMacro, MethodNameMacro, ParamCount) const leanclr::metadata::RtMethodInfo* Name##Fn{};

	COMMON_BRIDGE_METHODS(LEANCLR_METHOD_MEMBER)

	LEANCLR_INTEROP_BRIDGE_METHODS(LEANCLR_METHOD_MEMBER)

	UTILS_BRIDGE_METHODS(LEANCLR_METHOD_MEMBER)

#undef LEANCLR_METHOD_MEMBER

	TMap<IManagedHandle, TPair<const leanclr::metadata::RtMethodInfo*, bool>> MethodInvokePaths;

	leanclr::metadata::RtModuleDef* InteropModule{};

	leanclr::metadata::RtModuleDef* UEModule{};

	TArray<IManagedHandle> Assemblies;

	bool bIsInitialized{};

	static TMap<const leanclr::metadata::RtMethodInfo*, TPair<int32, int32>> MethodSlotSizes;

	static constexpr int32 MaxPInvokeArguments = 8;

	static TMap<const leanclr::metadata::RtMethodInfo*, FPInvokeSignature> PInvokeSignatures;
};

#include "FLeanCLRDomain.inl"
#endif
