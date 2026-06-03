#include "Domain/CoreCLR/FCoreCLRDomain.h"
#if WITH_CORECLR
#include "HAL/PlatformProcess.h"
#include "HAL/PlatformMisc.h"
#include "Misc/Paths.h"
#include "Misc/App.h"
#include "Misc/FileHelper.h"
#include "HAL/FileManager.h"
#include "Reflection/FReflectionRegistry.h"
#include "Reflection/FClassReflection.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Binding/FBinding.h"
#include "CoreMacro/CoreCLRMacro.h"
#include "CoreMacro/FunctionMacro.h"
#include "CoreMacro/Macro.h"
#include "CoreMacro/PropertyMacro.h"
#include "Domain/CoreCLR/FCoreCLRFunctionLibrary.h"
#include "Domain/CoreCLR/FCoreCLRLog.h"
#include "Setting/UnrealCSharpSetting.h"

#define LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, InType, InMethod, InFn) \
{ \
	void* OutFn{}; \
	if (LoadAssemblyAndGetFunctionPointer(InAssembly, InType, InMethod, &OutFn); OutFn != nullptr) \
	{ \
		InFn = reinterpret_cast<decltype(InFn)>(OutFn); \
	} \
}

FCoreCLRDomain::~FCoreCLRDomain()
{
	if (HostFxrHandle != nullptr)
	{
		FPlatformProcess::FreeDllHandle(HostFxrHandle);

		HostFxrHandle = nullptr;
	}
}

void FCoreCLRDomain::Initialize()
{
	if (bIsInitialized)
	{
		return;
	}

	if (LoadAssemblyAndGetFunctionPointerFn != nullptr)
	{
		bIsInitialized = true;

		InitializeAssembly(FUnrealCSharpFunctionLibrary::GetFullAssemblyPublishPath());

		return;
	}

	HostFxrHandle = FPlatformProcess::GetDllHandle(*FCoreCLRFunctionLibrary::GetHostFxrPath());

	if (const auto UnrealCSharpSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
		UUnrealCSharpSetting>())
	{
		if (UnrealCSharpSetting->IsEnableDebug())
		{
			FPlatformMisc::SetEnvironmentVar(TEXT("DOTNET_EnableDiagnostics"), TEXT("1"));

			FPlatformMisc::SetEnvironmentVar(TEXT("DOTNET_EnableDiagnostics_Debugger"), TEXT("1"));

			FPlatformMisc::SetEnvironmentVar(TEXT("DOTNET_DiagnosticPorts"), TEXT(""));
		}
	}

	RegisterErrorWriter();

	const auto HostFxrInitializeForRuntimeConfigFn = GetExport<hostfxr_initialize_for_runtime_config_fn>(
		HostFxrHandle, FUNCTION_HOSTFXR_INITIALIZE_FOR_RUNTIME_CONFIG);

	const auto HostFxrGetRuntimeDelegateFn = GetExport<hostfxr_get_runtime_delegate_fn>(
		HostFxrHandle, FUNCTION_HOSTFXR_GET_RUNTIME_DELEGATE);

	const auto HostFxrCloseFn = GetExport<hostfxr_close_fn>(HostFxrHandle, FUNCTION_HOSTFXR_CLOSE);

	const auto HostPath = FCoreCLRFunctionLibrary::GetHostPath();

	auto CoreCLRDirectory = FCoreCLRFunctionLibrary::GetCoreCLRDirectory();

	FPaths::MakePlatformFilename(CoreCLRDirectory);

	const auto HostPathString = FStringToString<>(HostPath);

	const auto CoreCLRDirectoryString = FStringToString<>(CoreCLRDirectory);

	const auto HostFxrInitializeParameters = hostfxr_initialize_parameters
	{
		sizeof(hostfxr_initialize_parameters),
		reinterpret_cast<const char_t*>(HostPathString.Get()),
		reinterpret_cast<const char_t*>(CoreCLRDirectoryString.Get())
	};

	hostfxr_handle HostContextHandle{};

	const auto HostFxrInitializeForRuntimeConfigErrorCode = HostFxrInitializeForRuntimeConfigFn(
		reinterpret_cast<const char_t*>(FStringToString<>(FCoreCLRFunctionLibrary::GetRuntimeConfigPath()).Get()),
		&HostFxrInitializeParameters,
		&HostContextHandle);

	if (constexpr auto HostAlreadyInitializedErrorCode = 0x00000008;
		HostFxrInitializeForRuntimeConfigErrorCode != 0 &&
		HostFxrInitializeForRuntimeConfigErrorCode != HostAlreadyInitializedErrorCode)
	{
		return;
	}

	void* OutLoadAssemblyAndGetFunctionPointerFn{};

	if (const auto HostFxrGetRuntimeDelegateErrorCode = HostFxrGetRuntimeDelegateFn(
			HostContextHandle, hdt_load_assembly_and_get_function_pointer, &OutLoadAssemblyAndGetFunctionPointerFn);
		HostFxrGetRuntimeDelegateErrorCode != 0 || OutLoadAssemblyAndGetFunctionPointerFn == nullptr)
	{
		HostFxrCloseFn(HostContextHandle);

		HostContextHandle = nullptr;

		return;
	}

	LoadAssemblyAndGetFunctionPointerFn = reinterpret_cast<load_assembly_and_get_function_pointer_fn>(
		OutLoadAssemblyAndGetFunctionPointerFn);

	const auto InteropAssembly = FUnrealCSharpFunctionLibrary::GetFullInteropPublishPath();

	if (!IFileManager::Get().FileExists(*InteropAssembly))
	{
		bIsInitialized = true;

		return;
	}

	RegisterInterop(InteropAssembly);

	RegisterLog();

	bIsInitialized = true;

	InitializeAssembly(FUnrealCSharpFunctionLibrary::GetFullAssemblyPublishPath());
}

void FCoreCLRDomain::Tick(const float InDeltaTime)
{
	if (SynchronizationContextTickFn != nullptr)
	{
		SynchronizationContextTickFn(InDeltaTime);
	}
}

void FCoreCLRDomain::Deinitialize()
{
	if (!bIsInitialized)
	{
		return;
	}

	bIsInitialized = false;

	UnloadAssembly();

	if (const auto UnrealCSharpSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
		UUnrealCSharpSetting>())
	{
		if (UnrealCSharpSetting->IsEnableDebug())
		{
			FPlatformMisc::SetEnvironmentVar(TEXT("DOTNET_EnableDiagnostics"), TEXT("0"));

			FPlatformMisc::SetEnvironmentVar(TEXT("DOTNET_EnableDiagnostics_Debugger"), TEXT("0"));

			FPlatformMisc::SetEnvironmentVar(TEXT("DOTNET_DiagnosticPorts"), TEXT(""));
		}
	}
}

FString FCoreCLRDomain::GetNamespace(const IManagedClass InManagedClass)
{
	if (IManagedIsValid(InManagedClass))
	{
		if (TypeBridgeGetNamespaceFn != nullptr)
		{
			constexpr auto Size = 512;

			uint8 String[Size];

			if (const auto Length = TypeBridgeGetNamespaceFn(MANAGED_HANDLE_FROM_OBJECT(InManagedClass), String, Size);
				Length > 0)
			{
				return FString(UTF8_TO_TCHAR(reinterpret_cast<const char*>(String)));
			}
		}
	}

	return {};
}

FString FCoreCLRDomain::GetName(const IManagedClass InManagedClass)
{
	if (IManagedIsValid(InManagedClass))
	{
		if (TypeBridgeGetNameFn != nullptr)
		{
			constexpr auto Size = 512;

			uint8 String[Size];

			if (const auto Length = TypeBridgeGetNameFn(MANAGED_HANDLE_FROM_OBJECT(InManagedClass), String, Size);
				Length > 0)
			{
				return FString(UTF8_TO_TCHAR(reinterpret_cast<const char*>(String)));
			}
		}
	}

	return {};
}

FString FCoreCLRDomain::GetFullName(const IManagedClass InManagedClass)
{
	if (IManagedIsValid(InManagedClass))
	{
		if (TypeBridgeGetFullNameFn != nullptr)
		{
			constexpr auto Size = 512;

			uint8 String[Size];

			if (const auto Length = TypeBridgeGetFullNameFn(MANAGED_HANDLE_FROM_OBJECT(InManagedClass), String, Size);
				Length > 0)
			{
				auto Result = FString(UTF8_TO_TCHAR(reinterpret_cast<const char*>(String)));

				if (int32 Index; Result.FindLastChar(TEXT(','), Index))
				{
					Result = Result.Left(Index).TrimEnd();
				}

				return Result;
			}
		}
	}

	return {};
}

IManagedHandle FCoreCLRDomain::NewObject(const IManagedClass InManagedClass)
{
	return ObjectBridgeNewObjectFn != nullptr
		       ? ObjectBridgeNewObjectFn(MANAGED_HANDLE_FROM_OBJECT(InManagedClass))
		       : InvalidManagedHandle;
}

IManagedHandle FCoreCLRDomain::BoxValue(const IManagedClass InManagedClass, void* InValue)
{
	if (const auto Class = FReflectionRegistry::Get().GetClass(InManagedClass))
	{
		return BoxValue(Class->GetNameSpace(), Class->GetName(), InValue);
	}

	return InvalidManagedHandle;
}

IManagedHandle FCoreCLRDomain::BoxValue(const FString& InNamespace, const FString& InName, void* InValue)
{
	if (InValue != nullptr)
	{
		if (InName == TEXT("bool") || InName == TEXT("Boolean"))
		{
			if (TypeBridgeBoxBoolFn != nullptr)
			{
				return TypeBridgeBoxBoolFn(static_cast<int*>(InValue));
			}
		}
		else if (InName == TEXT("sbyte") || InName == TEXT("SByte") || InName == TEXT("int8"))
		{
			if (TypeBridgeBoxSByteFn != nullptr)
			{
				return TypeBridgeBoxSByteFn(static_cast<int8*>(InValue));
			}
		}
		else if (InName == TEXT("int16") || InName == TEXT("Int16") || InName == TEXT("short"))
		{
			if (TypeBridgeBoxInt16Fn != nullptr)
			{
				return TypeBridgeBoxInt16Fn(static_cast<int16*>(InValue));
			}
		}
		else if (InName == TEXT("int32") || InName == TEXT("Int32") || InName == TEXT("int"))
		{
			if (TypeBridgeBoxInt32Fn != nullptr)
			{
				return TypeBridgeBoxInt32Fn(static_cast<int32*>(InValue));
			}
		}
		else if (InName == TEXT("int64") || InName == TEXT("Int64") || InName == TEXT("long"))
		{
			if (TypeBridgeBoxInt64Fn != nullptr)
			{
				return TypeBridgeBoxInt64Fn(static_cast<int64*>(InValue));
			}
		}
		else if (InName == TEXT("byte") || InName == TEXT("Byte") || InName == TEXT("uint8"))
		{
			if (TypeBridgeBoxByteFn != nullptr)
			{
				return TypeBridgeBoxByteFn(static_cast<uint8*>(InValue));
			}
		}
		else if (InName == TEXT("uint16") || InName == TEXT("UInt16") || InName == TEXT("ushort"))
		{
			if (TypeBridgeBoxUInt16Fn != nullptr)
			{
				return TypeBridgeBoxUInt16Fn(static_cast<uint16*>(InValue));
			}
		}
		else if (InName == TEXT("uint32") || InName == TEXT("UInt32") || InName == TEXT("uint"))
		{
			if (TypeBridgeBoxUInt32Fn != nullptr)
			{
				return TypeBridgeBoxUInt32Fn(static_cast<uint32*>(InValue));
			}
		}
		else if (InName == TEXT("uint64") || InName == TEXT("UInt64") || InName == TEXT("ulong"))
		{
			if (TypeBridgeBoxUInt64Fn != nullptr)
			{
				return TypeBridgeBoxUInt64Fn(static_cast<uint64*>(InValue));
			}
		}
		else if (InName == TEXT("float") || InName == TEXT("Single"))
		{
			if (TypeBridgeBoxFloatFn != nullptr)
			{
				return TypeBridgeBoxFloatFn(static_cast<float*>(InValue));
			}
		}
		else if (InName == TEXT("double") || InName == TEXT("Double"))
		{
			if (TypeBridgeBoxDoubleFn != nullptr)
			{
				return TypeBridgeBoxDoubleFn(static_cast<double*>(InValue));
			}
		}
	}

	return InvalidManagedHandle;
}

void* FCoreCLRDomain::UnboxValue(const IManagedHandle InManagedHandle)
{
	static uint64 Result{};

	if (IManagedHandleIsValid(InManagedHandle))
	{
		if (TypeBridgeUnboxBoolFn != nullptr)
		{
			int32 Value{};

			if (TypeBridgeUnboxBoolFn(InManagedHandle, &Value))
			{
				*static_cast<bool*>(static_cast<void*>(&Result)) = Value != 0;

				return &Result;
			}
		}

		if (TypeBridgeUnboxSByteFn != nullptr)
		{
			if (TypeBridgeUnboxSByteFn(InManagedHandle, static_cast<int8*>(static_cast<void*>(&Result))))
			{
				return &Result;
			}
		}

		if (TypeBridgeUnboxInt16Fn != nullptr)
		{
			if (TypeBridgeUnboxInt16Fn(InManagedHandle, static_cast<int16*>(static_cast<void*>(&Result))))
			{
				return &Result;
			}
		}

		if (TypeBridgeUnboxInt32Fn != nullptr)
		{
			if (TypeBridgeUnboxInt32Fn(InManagedHandle, static_cast<int32*>(static_cast<void*>(&Result))))
			{
				return &Result;
			}
		}

		if (TypeBridgeUnboxInt64Fn != nullptr)
		{
			if (TypeBridgeUnboxInt64Fn(InManagedHandle, static_cast<int64*>(static_cast<void*>(&Result))))
			{
				return &Result;
			}
		}

		if (TypeBridgeUnboxByteFn != nullptr)
		{
			if (TypeBridgeUnboxByteFn(InManagedHandle, static_cast<uint8*>(static_cast<void*>(&Result))))
			{
				return &Result;
			}
		}

		if (TypeBridgeUnboxUInt16Fn != nullptr)
		{
			if (TypeBridgeUnboxUInt16Fn(InManagedHandle, static_cast<uint16*>(static_cast<void*>(&Result))))
			{
				return &Result;
			}
		}

		if (TypeBridgeUnboxUInt32Fn != nullptr)
		{
			if (TypeBridgeUnboxUInt32Fn(InManagedHandle, static_cast<uint32*>(static_cast<void*>(&Result))))
			{
				return &Result;
			}
		}

		if (TypeBridgeUnboxUInt64Fn != nullptr)
		{
			if (TypeBridgeUnboxUInt64Fn(InManagedHandle, static_cast<uint64*>(static_cast<void*>(&Result))))
			{
				return &Result;
			}
		}

		if (TypeBridgeUnboxFloatFn != nullptr)
		{
			if (TypeBridgeUnboxFloatFn(InManagedHandle, static_cast<float*>(static_cast<void*>(&Result))))
			{
				return &Result;
			}
		}

		if (TypeBridgeUnboxDoubleFn != nullptr)
		{
			if (TypeBridgeUnboxDoubleFn(InManagedHandle, static_cast<double*>(static_cast<void*>(&Result))))
			{
				return &Result;
			}
		}
	}

	return nullptr;
}

IManagedHandle FCoreCLRDomain::NewString(const char* InText)
{
	return StringBridgeNewStringFn != nullptr && InText != nullptr
		       ? StringBridgeNewStringFn(reinterpret_cast<const uint8*>(InText))
		       : InvalidManagedHandle;
}

FString FCoreCLRDomain::StringToFString(const IManagedHandle InManagedHandle)
{
	if (IManagedHandleIsValid(InManagedHandle))
	{
		if (StringBridgeGetStringFn != nullptr)
		{
			constexpr auto Size = 1024;

			char16_t String[Size];

			if (const auto Length = StringBridgeGetStringFn(InManagedHandle, String, Size))
			{
				return FString(StringCast<TCHAR>(
					               reinterpret_cast<const UTF16CHAR*>(String), Length).Get(), Length);
			}

			constexpr auto MaxSize = 65536;

			TArray<char16_t> StringArray;

			StringArray.SetNumUninitialized(MaxSize);

			if (const auto Length = StringBridgeGetStringFn(InManagedHandle, StringArray.GetData(), MaxSize))
			{
				return FString(StringCast<TCHAR>(
					               reinterpret_cast<const UTF16CHAR*>(StringArray.GetData()), Length).Get(), Length);
			}
		}
	}

	return {};
}

IManagedHandle FCoreCLRDomain::NewRef(const IManagedHandle InManagedHandle, const bool bPinned)
{
	if (IManagedHandleIsValid(InManagedHandle))
	{
		if (HandleDataGetTargetFn != nullptr)
		{
			if (const auto Target = HandleDataGetTargetFn(InManagedHandle))
			{
				if (HandleDataAllocFn != nullptr)
				{
					return HandleDataAllocFn(Target, bPinned ? 1 : 0);
				}
			}
		}
	}

	return InvalidManagedHandle;
}

IManagedHandle FCoreCLRDomain::NewWeakRef(const IManagedHandle InManagedHandle, const bool bTrackResurrection)
{
	if (IManagedHandleIsValid(InManagedHandle))
	{
		if (HandleDataGetTargetFn != nullptr)
		{
			if (const auto Target = HandleDataGetTargetFn(InManagedHandle))
			{
				if (HandleDataAllocWeakRefFn != nullptr)
				{
					return HandleDataAllocWeakRefFn(Target, bTrackResurrection ? 1 : 0);
				}
			}
		}
	}

	return InvalidManagedHandle;
}

IManagedHandle FCoreCLRDomain::GetTarget(const IManagedHandle InManagedHandle)
{
	if (IManagedHandleIsValid(InManagedHandle))
	{
		if (HandleDataGetTargetFn != nullptr)
		{
			if (HandleDataGetTargetFn(InManagedHandle))
			{
				return InManagedHandle;
			}
		}
	}

	return InvalidManagedHandle;
}

void FCoreCLRDomain::Free(const IManagedHandle InManagedHandle)
{
	if (IManagedHandleIsValid(InManagedHandle))
	{
		if (HandleDataFreeFn != nullptr)
		{
			HandleDataFreeFn(InManagedHandle);
		}
	}
}

IManagedArray FCoreCLRDomain::NewArray(const IManagedClass InManagedClass, const int32 InLength)
{
	if (const auto Class = FReflectionRegistry::Get().GetClass(InManagedClass))
	{
		return NewArray(Class->GetNameSpace(), Class->GetName(), InLength);
	}

	return INVALID_MANAGED;
}

IManagedArray FCoreCLRDomain::NewArray(const FString& InNamespace, const FString& InName, const int32 InLength)
{
	if (InLength > 0)
	{
		if (ArrayHelperNewArrayFn != nullptr)
		{
			return IManagedHandleToIManagedArray(ArrayHelperNewArrayFn(
				reinterpret_cast<const uint8*>(StringCast<UTF8CHAR>(*COMBINE_FULL_NAME(InNamespace, InName)).Get()),
				InLength));
		}
	}

	return INVALID_MANAGED;
}

void* FCoreCLRDomain::ArrayGet(const IManagedArray InManagedArray, const int32 InIndex)
{
	if (IManagedIsValid(InManagedArray))
	{
		if (ArrayHelperArrayGetFn != nullptr)
		{
			return reinterpret_cast<void*>(ArrayHelperArrayGetFn(
				MANAGED_HANDLE_FROM_OBJECT(InManagedArray), InIndex));
		}
	}

	return nullptr;
}

IManagedHandle FCoreCLRDomain::ArrayGetRef(const IManagedArray InManagedArray, const int32 InIndex)
{
	if (IManagedIsValid(InManagedArray))
	{
		if (ArrayHelperArrayGetRefFn != nullptr)
		{
			return ArrayHelperArrayGetRefFn(MANAGED_HANDLE_FROM_OBJECT(InManagedArray), InIndex);
		}
	}

	return InvalidManagedHandle;
}

IManagedClass FCoreCLRDomain::GetClass(const FString& InNamespace, const FString& InName)
{
	if (TypeBridgeGetClassFn != nullptr)
	{
		return IManagedHandleToIManagedClass(TypeBridgeGetClassFn(
			reinterpret_cast<const uint8*>(StringCast<UTF8CHAR>(*COMBINE_FULL_NAME(InNamespace, InName)).Get())));
	}

	return INVALID_MANAGED;
}

IManagedMethod FCoreCLRDomain::GetMethod(const IManagedClass InManagedClass, const FString& InName,
                                         const int32 InParamCount)
{
	if (IManagedIsValid(InManagedClass))
	{
		if (TypeBridgeGetMethodFn != nullptr)
		{
			return IManagedHandleToIManagedMethod(TypeBridgeGetMethodFn(
				MANAGED_HANDLE_FROM_OBJECT(InManagedClass),
				reinterpret_cast<const uint8*>(StringCast<UTF8CHAR>(*InName).Get()),
				InParamCount));
		}
	}

	return INVALID_MANAGED;
}

void FCoreCLRDomain::SetFieldStaticValue(const IManagedClass InManagedClass, const FString& InName, void* InValue)
{
	if (IManagedIsValid(InManagedClass))
	{
		if (FieldHelperSetStaticValueFn != nullptr)
		{
			FieldHelperSetStaticValueFn(MANAGED_HANDLE_FROM_OBJECT(InManagedClass),
			                            reinterpret_cast<const uint8*>(StringCast<UTF8CHAR>(*InName).Get()),
			                            IManagedHandle{*static_cast<uint32*>(InValue)});
		}
	}
}

void* FCoreCLRDomain::GetFieldStaticValue(const IManagedClass InManagedClass, const FString& InName)
{
	if (IManagedIsValid(InManagedClass))
	{
		if (FieldHelperGetStaticValueFn != nullptr)
		{
			return MANAGED_HANDLE_TO_OBJECT(FieldHelperGetStaticValueFn(MANAGED_HANDLE_FROM_OBJECT(InManagedClass),
				reinterpret_cast<const uint8*>(StringCast<
					UTF8CHAR>(*InName).Get())));
		}
	}

	return nullptr;
}

void FCoreCLRDomain::SetPropertyValue(const IManagedHandle InManagedHandle, const FString& InName, void** InParams)
{
	if (TypeBridgeGetTypeFn != nullptr)
	{
		if (const auto Class = TypeBridgeGetTypeFn(InManagedHandle);
			IManagedIsValid(Class))
		{
			const auto Name = FString::Printf(TEXT(
				"%s%s"),
			                                  *PROPERTY_SET_PREFIX,
			                                  *InName
			);

			if (const auto Method = GetMethod(IManagedHandleToIManagedClass(Class), Name, 1);
				IManagedIsValid(Method))
			{
				Invoke(InManagedHandle, Method, 1, InParams);
			}
		}
	}
}

void* FCoreCLRDomain::GetPropertyValue(const IManagedHandle InManagedHandle, const FString& InName, void** InParams)
{
	if (TypeBridgeGetTypeFn != nullptr)
	{
		if (const auto Class = TypeBridgeGetTypeFn(InManagedHandle);
			IManagedIsValid(Class))
		{
			const auto Name = FString::Printf(TEXT(
				"%s%s"),
			                                  *PROPERTY_GET_PREFIX,
			                                  *InName
			);

			if (const auto Method = GetMethod(IManagedHandleToIManagedClass(Class), Name, 0);
				IManagedIsValid(Method))
			{
				return MANAGED_HANDLE_TO_OBJECT(Invoke(InManagedHandle, Method, 0, InParams));
			}
		}
	}

	return nullptr;
}

FClassReflection* FCoreCLRDomain::MakeGenericType(const FClassReflection* InGeneric, const FClassReflection* InType)
{
	if (InGeneric != nullptr && InType != nullptr)
	{
		if (TypeBridgeGetClassFn != nullptr)
		{
			return FReflectionRegistry::Get().GetClass(
				IManagedHandleToIManagedClass(
					TypeBridgeMakeGenericTypeFn(MANAGED_HANDLE_FROM_OBJECT(InGeneric->GetManagedClass()),
					                            MANAGED_HANDLE_FROM_OBJECT(InType->GetManagedClass()))));
		}
	}

	return nullptr;
}

FClassReflection* FCoreCLRDomain::MakeGenericType(const FClassReflection* InGeneric,
                                                  const FClassReflection* InKeyType,
                                                  const FClassReflection* InValueType)
{
	if (InGeneric != nullptr && InKeyType != nullptr && InValueType != nullptr)
	{
		if (TypeBridgeMakeGenericType2Fn != nullptr)
		{
			return FReflectionRegistry::Get().GetClass(
				IManagedHandleToIManagedClass(TypeBridgeMakeGenericType2Fn(
					MANAGED_HANDLE_FROM_OBJECT(InGeneric->GetManagedClass()),
					MANAGED_HANDLE_FROM_OBJECT(InKeyType->GetManagedClass()),
					MANAGED_HANDLE_FROM_OBJECT(InValueType->GetManagedClass()))));
		}
	}

	return nullptr;
}

IManagedHandle FCoreCLRDomain::Invoke(const IManagedHandle InManagedHandle, const IManagedMethod InManagedMethod,
                                      const int32 InParamCount, void** InParams)
{
	if (IManagedIsValid(InManagedMethod))
	{
		if (MethodBridgeInvokeFn != nullptr)
		{
			return MethodBridgeInvokeFn(
				MANAGED_HANDLE_FROM_OBJECT(InManagedHandle),
				MANAGED_HANDLE_FROM_OBJECT(InManagedMethod),
				InParamCount,
				reinterpret_cast<IManagedHandle*>(InParams));
		}
	}

	return InvalidManagedHandle;
}

bool FCoreCLRDomain::IsInitialized() const
{
	return bIsInitialized;
}

TArray<IManagedHandle> FCoreCLRDomain::GetAssemblies() const
{
	return Assemblies;
}

TArray<FClassReflection*> FCoreCLRDomain::GetClassesWithAttribute(const FClassReflection* InClass,
                                                                  const IManagedHandle InManagedHandle)
{
	TArray<FClassReflection*> Result;

	if (const auto UtilsClass = FReflectionRegistry::Get().GetUtilsClass())
	{
		if (const auto GetTypesWithAttributeMethod = UtilsClass->GetMethod(FUNCTION_UTILS_GET_TYPES_WITH_ATTRIBUTE, 3))
		{
			int32 OutLength{};

			auto ManagedClass = MANAGED_HANDLE_FROM_OBJECT(InClass->GetManagedClass());

			auto ManagedHandle = InManagedHandle;

			void* InParams[3] = {
				&ManagedClass,
				&ManagedHandle,
				&OutLength
			};

			if (const auto Types = GetTypesWithAttributeMethod->Runtime_Invoke(InvalidManagedHandle, InParams);
				IManagedHandleIsValid(Types))
			{
				for (auto Index = 0; Index < OutLength; ++Index)
				{
					if (const auto Element = ArrayGetRef(IManagedHandleToIManagedArray(Types), Index);
						IManagedHandleIsValid(Element))
					{
						Result.Add(FReflectionRegistry::Get().GetClass(
							GetNamespace(IManagedHandleToIManagedClass(Element)),
							GetName(IManagedHandleToIManagedClass(Element))));

						Free(Element);
					}
				}

				Free(Types);
			}
		}
	}

	return Result;
}

void FCoreCLRDomain::InitializeAssembly(const TArray<FString>& InAssemblies)
{
	LoadAssembly(InAssemblies);

	RegisterSynchronizationContextTick();

	FReflectionRegistry::Get().Initialize();

	RegisterBinding();
}

void FCoreCLRDomain::LoadAssembly(const TArray<FString>& InAssemblies)
{
	if (!bIsInitialized)
	{
		return;
	}

	Assemblies.Empty();

	const auto PublishDirectory = StringCast<UTF16CHAR>(*FUnrealCSharpFunctionLibrary::GetFullPublishDirectory());

	for (const auto& AssemblyPath : InAssemblies)
	{
		if (!FPaths::FileExists(AssemblyPath))
		{
			continue;
		}

		if (TArray<uint8> Data; FFileHelper::LoadFileToArray(Data, *AssemblyPath))
		{
			if (AssemblyLoaderLoadFromStreamFn != nullptr)
			{
				if (const auto Handle = AssemblyLoaderLoadFromStreamFn(Data.GetData(), Data.Num(),
				                                                       reinterpret_cast<const char16_t*>(
					                                                       PublishDirectory.Get()));
					IManagedHandleIsValid(Handle))
				{
					Assemblies.Add(IManagedHandle{Handle});
				}
			}
		}
	}
}

void FCoreCLRDomain::UnloadAssembly()
{
	FReflectionRegistry::Get().Deinitialize();

	if (AssemblyLoaderUnLoadFn != nullptr)
	{
		AssemblyLoaderUnLoadFn();
	}

	Assemblies.Empty();
}

void FCoreCLRDomain::RegisterErrorWriter() const
{
	if (const auto HostFxrSetErrorWriterFn = GetExport<hostfxr_set_error_writer_fn>(
		HostFxrHandle, FUNCTION_HOSTFXR_SET_ERROR_WRITER))
	{
		HostFxrSetErrorWriterFn(&FCoreCLRLog::ErrorWriter);
	}
}

void FCoreCLRDomain::RegisterInterop(const FString& InAssembly)
{
	const auto AssemblyLoader = CORECLR_TYPE_NAME(NAMESPACE_INTEROP, CLASS_ASSEMBLY_LOADER, INTEROP_NAME);

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, AssemblyLoader, FUNCTION_ASSEMBLY_LOADER_LOAD_FROM_STREAM,
	                                       AssemblyLoaderLoadFromStreamFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, AssemblyLoader, FUNCTION_ASSEMBLY_LOADER_UNLOAD,
	                                       AssemblyLoaderUnLoadFn)

	const auto HandleData = CORECLR_TYPE_NAME(NAMESPACE_INTEROP, CLASS_HANDLE_DATA, INTEROP_NAME);

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, HandleData, FUNCTION_HANDLE_DATA_ALLOC,
	                                       HandleDataAllocFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, HandleData, FUNCTION_HANDLE_DATA_ALLOC_WEAK_REF,
	                                       HandleDataAllocWeakRefFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, HandleData, FUNCTION_HANDLE_DATA_GET_TARGET,
	                                       HandleDataGetTargetFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, HandleData, FUNCTION_HANDLE_DATA_FREE,
	                                       HandleDataFreeFn)

	const auto LogBridge = CORECLR_TYPE_NAME(NAMESPACE_INTEROP, CLASS_LOG_BRIDGE, INTEROP_NAME);

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, LogBridge, FUNCTION_LOG_BRIDGE_SET_LOG,
	                                       LogBridgeSetLogFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, LogBridge, FUNCTION_LOG_BRIDGE_INITIALIZE,
	                                       LogBridgeInitializeFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, LogBridge, FUNCTION_LOG_BRIDGE_DEINITIALIZE,
	                                       LogBridgeDeinitializeFn)

	const auto TypeBridge = CORECLR_TYPE_NAME(NAMESPACE_INTEROP, CLASS_TYPE_BRIDGE, INTEROP_NAME);

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_GET_CLASS,
	                                       TypeBridgeGetClassFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_GET_TYPE,
	                                       TypeBridgeGetTypeFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_GET_METHOD,
	                                       TypeBridgeGetMethodFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_GET_FUNCTION_POINTER,
	                                       TypeBridgeGetFunctionPointerFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_GET_NAMESPACE,
	                                       TypeBridgeGetNamespaceFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_GET_NAME,
	                                       TypeBridgeGetNameFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_GET_FULL_NAME,
	                                       TypeBridgeGetFullNameFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_MAKE_GENERIC_TYPE,
	                                       TypeBridgeMakeGenericTypeFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_MAKE_GENERIC_TYPE2,
	                                       TypeBridgeMakeGenericType2Fn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_BOOL,
	                                       TypeBridgeBoxBoolFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_SBYTE,
	                                       TypeBridgeBoxSByteFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_INT16,
	                                       TypeBridgeBoxInt16Fn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_INT32,
	                                       TypeBridgeBoxInt32Fn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_INT64,
	                                       TypeBridgeBoxInt64Fn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_BYTE,
	                                       TypeBridgeBoxByteFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_UINT16,
	                                       TypeBridgeBoxUInt16Fn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_UINT32,
	                                       TypeBridgeBoxUInt32Fn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_UINT64,
	                                       TypeBridgeBoxUInt64Fn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_FLOAT,
	                                       TypeBridgeBoxFloatFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_BOX_DOUBLE,
	                                       TypeBridgeBoxDoubleFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_BOOL,
	                                       TypeBridgeUnboxBoolFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_SBYTE,
	                                       TypeBridgeUnboxSByteFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_INT16,
	                                       TypeBridgeUnboxInt16Fn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_INT32,
	                                       TypeBridgeUnboxInt32Fn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_INT64,
	                                       TypeBridgeUnboxInt64Fn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_BYTE,
	                                       TypeBridgeUnboxByteFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_UINT16,
	                                       TypeBridgeUnboxUInt16Fn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_UINT32,
	                                       TypeBridgeUnboxUInt32Fn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_UINT64,
	                                       TypeBridgeUnboxUInt64Fn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_FLOAT,
	                                       TypeBridgeUnboxFloatFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, TypeBridge, FUNCTION_TYPE_BRIDGE_UNBOX_DOUBLE,
	                                       TypeBridgeUnboxDoubleFn)

	const auto ObjectBridge = CORECLR_TYPE_NAME(NAMESPACE_INTEROP, CLASS_OBJECT_BRIDGE, INTEROP_NAME);

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, ObjectBridge, FUNCTION_OBJECT_BRIDGE_NEW_OBJECT,
	                                       ObjectBridgeNewObjectFn)

	const auto FieldBridge = CORECLR_TYPE_NAME(NAMESPACE_INTEROP, CLASS_FIELD_BRIDGE, INTEROP_NAME);

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, FieldBridge, FUNCTION_FIELD_BRIDGE_SET_STATIC_VALUE,
	                                       FieldHelperSetStaticValueFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, FieldBridge, FUNCTION_FIELD_BRIDGE_GET_STATIC_VALUE,
	                                       FieldHelperGetStaticValueFn)

	const auto MethodBridge = CORECLR_TYPE_NAME(NAMESPACE_INTEROP, CLASS_METHOD_BRIDGE, INTEROP_NAME);

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, MethodBridge, FUNCTION_METHOD_BRIDGE_REGISTER_BINDING,
	                                       MethodBridgeRegisterBindingFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, MethodBridge, FUNCTION_METHOD_BRIDGE_INVOKE,
	                                       MethodBridgeInvokeFn)

	const auto StringBridge = CORECLR_TYPE_NAME(NAMESPACE_INTEROP, CLASS_STRING_BRIDGE, INTEROP_NAME);

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, StringBridge, FUNCTION_STRING_BRIDGE_NEW_STRING,
	                                       StringBridgeNewStringFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, StringBridge, FUNCTION_STRING_BRIDGE_GET_STRING,
	                                       StringBridgeGetStringFn)

	const auto ArrayBridge = CORECLR_TYPE_NAME(NAMESPACE_INTEROP, CLASS_ARRAY_BRIDGE, INTEROP_NAME);

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, ArrayBridge, FUNCTION_ARRAY_BRIDGE_ARRAY_NEW,
	                                       ArrayHelperNewArrayFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, ArrayBridge, FUNCTION_ARRAY_BRIDGE_ARRAY_GET,
	                                       ArrayHelperArrayGetFn)

	LOAD_ASSEMBLY_AND_GET_FUNCTION_POINTER(InAssembly, ArrayBridge, FUNCTION_ARRAY_BRIDGE_ARRAY_GET_REF,
	                                       ArrayHelperArrayGetRefFn)
}

void FCoreCLRDomain::RegisterLog() const
{
	if (LogBridgeSetLogFn != nullptr)
	{
		LogBridgeSetLogFn(reinterpret_cast<PTRINT>(&FCoreCLRLog::Log));
	}

	if (LogBridgeInitializeFn != nullptr)
	{
		LogBridgeInitializeFn();
	}
}

void FCoreCLRDomain::RegisterSynchronizationContextTick()
{
	if (TypeBridgeGetFunctionPointerFn != nullptr)
	{
		SynchronizationContextTickFn = reinterpret_cast<synchronization_context_tick_fn>(TypeBridgeGetFunctionPointerFn(
			reinterpret_cast<const char16_t*>(StringCast<UTF16CHAR>(*FUnrealCSharpFunctionLibrary::GetUEName()).Get()),
			reinterpret_cast<const char16_t*>(StringCast<UTF16CHAR>(
				*COMBINE_FULL_NAME(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT),
				                   CLASS_SYNCHRONIZATION_CONTEXT)).Get()),
			reinterpret_cast<const char16_t*>(StringCast<UTF16CHAR>(*FUNCTION_SYNCHRONIZATION_CONTEXT_TICK).Get())));
	}
}

void FCoreCLRDomain::RegisterBinding() const
{
	if (MethodBridgeRegisterBindingFn != nullptr)
	{
		TArray<TArray<ANSICHAR>> Names;

		TArray<const uint8*> MethodNames;

		TArray<PTRINT> Methods;

		for (const auto& Class : FBinding::Get().Register().GetClasses())
		{
			for (const auto& Method : Class->GetMethods())
			{
				const auto MethodName = StringCast<UTF8CHAR>(*Method.GetMethod());

				const auto Length = MethodName.Length() + 1;

				auto& Name = Names.AddDefaulted_GetRef();

				Name.SetNumUninitialized(Length);

				FMemory::Memcpy(Name.GetData(), MethodName.Get(), Length);

				MethodNames.Add(reinterpret_cast<const uint8*>(Name.GetData()));

				Methods.Add(reinterpret_cast<PTRINT>(const_cast<void*>(Method.GetFunction())));
			}
		}

		MethodBridgeRegisterBindingFn(MethodNames.GetData(), Methods.GetData(), MethodNames.Num());
	}
}


void FCoreCLRDomain::LoadAssemblyAndGetFunctionPointer(const FString& InAssembly, const FString& InType,
                                                       const FString& InMethod,
                                                       void** OutFunctionPointer) const
{
	if (LoadAssemblyAndGetFunctionPointerFn != nullptr)
	{
		LoadAssemblyAndGetFunctionPointerFn(
			StringCast<char_t>(*InAssembly).Get(),
			StringCast<char_t>(*InType).Get(),
			StringCast<char_t>(*InMethod).Get(),
			UNMANAGEDCALLERSONLY_METHOD,
			nullptr,
			OutFunctionPointer);
	}
}
#endif
