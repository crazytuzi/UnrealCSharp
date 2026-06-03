#include "Domain/Mono/FMonoDomain.h"
#if WITH_MONO
#include "Misc/FileHelper.h"
#include "Domain/Script/IManagedHandle.h"
#include "Domain/Mono/FMonoFunctionLibrary.h"
#include "Domain/Mono/FMonoLog.h"
#include "CoreMacro/FunctionMacro.h"
#include "CoreMacro/MonoMacro.h"
#include "CoreMacro/CompilerMacro.h"
#include "CoreMacro/ClassMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/PropertyMacro.h"
#include "Template/TGetArrayLength.inl"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Binding/FBinding.h"
#include "Setting/UnrealCSharpSetting.h"
#include "Reflection/FReflectionRegistry.h"
#include "Reflection/FClassReflection.h"
#include "Reflection/FMethodReflection.h"
#include "mono/metadata/object.h"
#include "mono/jit/jit.h"
#include "mono/metadata/assembly.h"
#include "mono/utils/mono-logger.h"
#include "mono/metadata/mono-debug.h"
#include "mono/metadata/class.h"
#include "mono/metadata/reflection.h"
#include "DotnetVersion.h"
#if DOTNET9
#include "mono/jit/mono-private-unstable.h"
#endif
#if UE_TRACE_ENABLED
#include "Domain/Mono/FMonoProfiler.h"
#endif

PRAGMA_DISABLE_DANGLING_WARNINGS

MonoDomain* FMonoDomain::Domain{};

TArray<MonoGCHandle> FMonoDomain::AssemblyGCHandles{};

TArray<IManagedAssembly> FMonoDomain::Assemblies{};

TArray<IManagedImage> FMonoDomain::Images{};

#if PLATFORM_IOS
extern void* mono_aot_module_System_Private_CoreLib_info;
#endif

void FMonoDomain::Initialize()
{
	RegisterMonoTrace();

	RegisterAssemblyPreloadHook();

	if (Domain == nullptr)
	{
#if PLATFORM_IOS
		mono_jit_set_aot_mode(MONO_AOT_MODE_INTERP);

		mono_aot_register_module(static_cast<void**>(mono_aot_module_System_Private_CoreLib_info));

#if !DOTNET9
		mono_dllmap_insert(NULL, "System.Native", NULL, "__Internal", NULL);

		mono_dllmap_insert(NULL, "System.Net.Security.Native", NULL, "__Internal", NULL);

		mono_dllmap_insert(NULL, "System.IO.Compression.Native", NULL, "__Internal", NULL);

		mono_dllmap_insert(NULL, "System.Security.Cryptography.Native.Apple", NULL, "__Internal", NULL);

#if DOTNET8
		mono_dllmap_insert(NULL, "System.Globalization.Native", NULL, "__Internal", NULL);
#endif
#endif

		setenv("DOTNET_SYSTEM_GLOBALIZATION_INVARIANT", "1", TRUE);
#else
#if DOTNET9
#if PLATFORM_WINDOWS
		const auto LibDirectory = FMonoFunctionLibrary::GetLibDirectory();

		const char* PropertyKeys[] = {
			"NATIVE_DLL_SEARCH_DIRECTORIES"
		};
		const char* PropertyValues[] = {
			TCHAR_TO_ANSI(*LibDirectory),
		};

		monovm_initialize(std::size(PropertyKeys), PropertyKeys, PropertyValues);
#endif
#endif

		mono_jit_set_aot_mode(MONO_AOT_MODE_NONE);
#endif

		if (const auto UnrealCSharpSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
			UUnrealCSharpSetting>())
		{
			if (UnrealCSharpSetting->IsEnableDebug())
			{
				const auto Config = FString::Printf(TEXT(
					"--debugger-agent=transport=dt_socket,server=y,suspend=n,address=%s:%d"
				),
				                                    *UnrealCSharpSetting->GetHost(),
				                                    UnrealCSharpSetting->GetPort()
				);

				char* Options[] = {
					TCHAR_TO_ANSI(TEXT("--soft-breakpoints")),
					TCHAR_TO_ANSI(*Config)
				};

				mono_jit_parse_options(sizeof(Options) / sizeof(char*), Options);
			}
		}

		mono_debug_init(MONO_DEBUG_FORMAT_MONO);

		Domain = mono_jit_init("UnrealCSharp");

		mono_domain_set(Domain, false);

		RegisterProfiler();
	}

	InitializeAssembly(FUnrealCSharpFunctionLibrary::GetFullAssemblyPublishPath());

	if (bIsInitialized)
	{
		FReflectionRegistry::Get().Initialize();
	}

	RegisterLog();

	RegisterBinding();

	if (bIsInitialized)
	{
		RegisterSynchronizationContextTick();
	}
}

void FMonoDomain::Tick(const float InDeltaTime)
{
	if (SynchronizationContextTick != nullptr)
	{
		IManagedObject Exception = INVALID_MANAGED;

		SynchronizationContextTick(InDeltaTime, &Exception);

		if (IManagedIsValid(Exception))
		{
			Unhandled_Exception(Exception);
		}
	}
}

void FMonoDomain::Deinitialize()
{
	if (bIsInitialized)
	{
		FReflectionRegistry::Get().Deinitialize();
	}

	UnloadAssembly();

	DeinitializeAssembly();
}

FString FMonoDomain::GetNamespace(const IManagedClass InManagedClass)
{
	return FString(mono_class_get_namespace(InManagedClass));
}

FString FMonoDomain::GetName(const IManagedClass InManagedClass)
{
	return FString(mono_class_get_name(InManagedClass));
}

FString FMonoDomain::GetFullName(const IManagedClass InManagedClass)
{
	return COMBINE_FULL_NAME(GetNamespace(InManagedClass), GetName(InManagedClass));
}

IManagedHandle FMonoDomain::NewObject(const IManagedClass InManagedClass)
{
	const auto Object = Object_New(InManagedClass);

	return IManagedIsValid(Object) ? MANAGED_HANDLE_FROM_OBJECT(Object) : InvalidManagedHandle;
}

IManagedHandle FMonoDomain::BoxValue(const IManagedClass InManagedClass, void* InValue)
{
	return MANAGED_HANDLE_FROM_OBJECT(Value_Box(InManagedClass, InValue));
}

IManagedHandle FMonoDomain::BoxValue(const FString& InNamespace, const FString& InName, void* InValue)
{
	const auto FoundClass = FReflectionRegistry::Get().GetClass(InNamespace, InName);

	return FoundClass != nullptr ? BoxValue(FoundClass->GetManagedClass(), InValue) : InvalidManagedHandle;
}

void* FMonoDomain::UnboxValue(const IManagedHandle InManagedHandle)
{
	const auto Object = MANAGED_HANDLE_CAST_TO_OBJECT(IManagedObject, InManagedHandle);

	return IManagedIsValid(Object) ? Object_Unbox(Object) : nullptr;
}

IManagedHandle FMonoDomain::NewString(const char* InText)
{
	return MANAGED_HANDLE_FROM_OBJECT(String_New(InText));
}

FString FMonoDomain::StringToFString(const IManagedHandle InManagedHandle)
{
	return String_To_UTF8(MANAGED_HANDLE_CAST_TO_OBJECT(IManagedString, InManagedHandle));
}

IManagedHandle FMonoDomain::NewRef(const IManagedHandle InManagedHandle, const bool bPinned)
{
	if (IManagedHandleIsValid(InManagedHandle))
	{
		if (const auto Object = MANAGED_HANDLE_CAST_TO_OBJECT(IManagedObject, InManagedHandle); IManagedIsValid(Object))
		{
			return MonoGCHandleToHandle(GCHandle_New_V2(Object, bPinned ? 1 : 0));
		}
	}

	return InvalidManagedHandle;
}

IManagedHandle FMonoDomain::NewWeakRef(const IManagedHandle InManagedHandle, const bool bTrackResurrection)
{
	if (IManagedHandleIsValid(InManagedHandle))
	{
		if (const auto Object = MANAGED_HANDLE_CAST_TO_OBJECT(IManagedObject, InManagedHandle); IManagedIsValid(Object))
		{
			return MonoGCHandleToHandle(GCHandle_New_WeakRef_V2(Object, bTrackResurrection ? 1 : 0));
		}
	}

	return InvalidManagedHandle;
}

IManagedHandle FMonoDomain::GetTarget(const IManagedHandle InManagedHandle)
{
	if (IManagedHandleIsValid(InManagedHandle))
	{
		if (const auto Object = GCHandle_Get_Target_V2(HandleToMonoGCHandle(InManagedHandle)); IManagedIsValid(Object))
		{
			return MANAGED_HANDLE_FROM_OBJECT(Object);
		}
	}

	return InvalidManagedHandle;
}

void FMonoDomain::Free(const IManagedHandle InManagedHandle)
{
	if (IManagedHandleIsValid(InManagedHandle))
	{
		GCHandle_Free_V2(HandleToMonoGCHandle(InManagedHandle));
	}
}

IManagedArray FMonoDomain::NewArray(const IManagedClass InManagedClass, const int32 InLength)
{
	return Array_New(InManagedClass, static_cast<uint32>(InLength));
}

IManagedArray FMonoDomain::NewArray(const FString& InNamespace, const FString& InName, const int32 InLength)
{
	return NewArray(Class_From_Name(InNamespace, InName), InLength);
}

void* FMonoDomain::ArrayGet(const IManagedArray InManagedArray, const int32 InIndex)
{
	if (IManagedIsValid(InManagedArray))
	{
		return Array_Addr<void*>(InManagedArray, static_cast<uint64>(InIndex));
	}

	return nullptr;
}

IManagedHandle FMonoDomain::ArrayGetRef(const IManagedArray InManagedArray, const int32 InIndex)
{
	return InvalidManagedHandle;
}

IManagedClass FMonoDomain::GetClass(const FString& InNamespace, const FString& InName)
{
	return Class_From_Name(InNamespace, InName);
}

IManagedMethod FMonoDomain::GetMethod(const IManagedClass InManagedClass, const FString& InName,
                                      const int32 InParamCount)
{
	return Class_Get_Method_From_Name(InManagedClass, InName, InParamCount);
}

void FMonoDomain::SetFieldStaticValue(const IManagedClass InManagedClass, const FString& InName, void* InValue)
{
	if (IManagedIsValid(InManagedClass))
	{
		if (const auto Field = Class_Get_Field_From_Name(InManagedClass, FTCHARToUTF8(*InName).Get());
			IManagedIsValid(Field))
		{
			if (const auto VTable = Class_VTable(InManagedClass); IManagedIsValid(VTable))
			{
				Field_Static_Set_Value(VTable, Field, InValue);
			}
		}
	}
}

void* FMonoDomain::GetFieldStaticValue(const IManagedClass InManagedClass, const FString& InName)
{
	if (IManagedIsValid(InManagedClass))
	{
		if (const auto Field = Class_Get_Field_From_Name(InManagedClass, FTCHARToUTF8(*InName).Get());
			IManagedIsValid(Field))
		{
			if (const auto VTable = Class_VTable(InManagedClass); IManagedIsValid(VTable))
			{
				void* OutValue{};

				Field_Static_Get_Value(VTable, Field, &OutValue);

				return OutValue;
			}
		}
	}

	return nullptr;
}

void FMonoDomain::SetPropertyValue(const IManagedHandle InManagedHandle, const FString& InName, void** InParams)
{
	if (IManagedHandleIsValid(InManagedHandle))
	{
		if (const auto Object = IManagedHandleToIManagedObject(InManagedHandle); IManagedIsValid(Object))
		{
			const auto Name = FString::Printf(TEXT(
				"%s%s"),
			                                  *PROPERTY_SET_PREFIX,
			                                  *InName
			);

			IManagedMethod Method{};

			for (auto Class = mono_object_get_class(Object); Class && !Method; Class = mono_class_get_parent(Class))
			{
				Method = Class_Get_Method_From_Name(Class, Name, 1);
			}

			if (IManagedIsValid(Method))
			{
				IManagedObject Exception{};

				Runtime_Invoke(Method, Object, InParams, &Exception);

				if (IManagedIsValid(Exception))
				{
					Unhandled_Exception(Exception);
				}
			}
		}
	}
}

void* FMonoDomain::GetPropertyValue(const IManagedHandle InManagedHandle, const FString& InName, void** InParams)
{
	if (IManagedHandleIsValid(InManagedHandle))
	{
		if (const auto Object = IManagedHandleToIManagedObject(InManagedHandle); IManagedIsValid(Object))
		{
			const auto Name = FString::Printf(TEXT(
				"%s%s"),
			                                  *PROPERTY_GET_PREFIX,
			                                  *InName
			);

			IManagedMethod Method{};

			for (auto Class = mono_object_get_class(Object); Class && !Method; Class = mono_class_get_parent(Class))
			{
				Method = Class_Get_Method_From_Name(Class, Name, 0);
			}

			if (IManagedIsValid(Method))
			{
				IManagedObject Exception{};

				const auto Value = Runtime_Invoke(Method, Object, InParams, &Exception);

				if (IManagedIsValid(Exception))
				{
					Unhandled_Exception(Exception);

					return nullptr;
				}

				return Value;
			}
		}
	}

	return nullptr;
}

FClassReflection* FMonoDomain::MakeGenericType(const FClassReflection* InGeneric, const FClassReflection* InType)
{
	if (InGeneric == nullptr || InType == nullptr)
	{
		return nullptr;
	}

	auto const Array = FReflectionRegistry::Get().GetObjectClass()->NewArray(1);

	Array_Set(Array, 0, InType->GetManagedReflectionType());

	void* Params[2];

	Params[0] = InGeneric->GetManagedReflectionType();

	Params[1] = Array;

	const auto UtilsClass = FReflectionRegistry::Get().GetUtilsClass();

	const auto MakeGenericTypeInstanceMethod = UtilsClass->GetMethod(
		FUNCTION_UTILS_MAKE_GENERIC_TYPE_INSTANCE, TGetArrayLength(Params));

	return FReflectionRegistry::Get().GetClass(
		(IManagedReflectionType)MakeGenericTypeInstanceMethod->Runtime_Invoke(InvalidManagedHandle, Params));
}

FClassReflection* FMonoDomain::MakeGenericType(const FClassReflection* InGeneric,
                                               const FClassReflection* InKeyType, const FClassReflection* InValueType)
{
	if (InGeneric == nullptr || InKeyType == nullptr || InValueType == nullptr)
	{
		return nullptr;
	}

	auto const Array = FReflectionRegistry::Get().GetObjectClass()->NewArray(2);

	Array_Set(Array, 0, InKeyType->GetManagedReflectionType());

	Array_Set(Array, 1, InValueType->GetManagedReflectionType());

	void* Params[2];

	Params[0] = InGeneric->GetManagedReflectionType();

	Params[1] = Array;

	const auto UtilsClass = FReflectionRegistry::Get().GetUtilsClass();

	const auto MakeGenericTypeInstanceMethod = UtilsClass->GetMethod(
		FUNCTION_UTILS_MAKE_GENERIC_TYPE_INSTANCE, TGetArrayLength(Params));

	return FReflectionRegistry::Get().GetClass(
		(IManagedReflectionType)MakeGenericTypeInstanceMethod->Runtime_Invoke(InvalidManagedHandle, Params));
}

IManagedHandle FMonoDomain::Invoke(const IManagedHandle InManagedHandle, const IManagedMethod InManagedMethod,
                                   const int32 InParamCount, void** InParams)
{
	return MANAGED_HANDLE_FROM_OBJECT(Runtime_Invoke(InManagedMethod,
	                                                 MANAGED_HANDLE_CAST_TO_OBJECT(IManagedObject, InManagedHandle),
	                                                 InParams));
}

bool FMonoDomain::IsInitialized() const
{
	return bIsInitialized;
}

TArray<IManagedHandle> FMonoDomain::GetAssemblies() const
{
	TArray<IManagedHandle> Result;

	for (const auto Assembly : AssemblyGCHandles)
	{
		Result.Add(MonoGCHandleToHandle(Assembly));
	}

	return Result;
}

TArray<FClassReflection*> FMonoDomain::GetClassesWithAttribute(const FClassReflection* InClass,
                                                               const IManagedHandle InManagedHandle)
{
	TArray<FClassReflection*> Result;

	if (const auto UtilsClass = FReflectionRegistry::Get().GetUtilsClass())
	{
		int32 OutLength{};

		void* InParams[3] = {
			InClass->GetManagedReflectionType(),
			GCHandle_Get_Target_V2(HandleToMonoGCHandle(InManagedHandle)),
			&OutLength
		};

		if (const auto GetTypesWithAttributeMethod = UtilsClass->GetMethod(
			FUNCTION_UTILS_GET_TYPES_WITH_ATTRIBUTE, TGetArrayLength(InParams)))
		{
			const auto Types = MANAGED_HANDLE_CAST_TO_OBJECT(IManagedArray, GetTypesWithAttributeMethod->Runtime_Invoke(
				                                                 InvalidManagedHandle, InParams));

			for (auto Index = 0; Index < OutLength; ++Index)
			{
				Result.Add(FReflectionRegistry::Get().GetClass(Array_Get<IManagedReflectionType>(Types, Index)));
			}
		}
	}

	return Result;
}

IManagedObject FMonoDomain::Object_New(const IManagedClass InManagedClass)
{
	return Domain != nullptr && IManagedIsValid(InManagedClass)
		       ? mono_object_new(Domain, InManagedClass)
		       : INVALID_MANAGED;
}

IManagedObject FMonoDomain::Value_Box(const IManagedClass InManagedClass, void* InValue)
{
	return Domain != nullptr && IManagedIsValid(InManagedClass)
		       ? mono_value_box(Domain, InManagedClass, InValue)
		       : INVALID_MANAGED;
}

void* FMonoDomain::Object_Unbox(const IManagedObject InManagedObject)
{
	return IManagedIsValid(InManagedObject) ? mono_object_unbox(InManagedObject) : nullptr;
}

IManagedString FMonoDomain::String_New(const char* InText)
{
	return Domain != nullptr && InText != nullptr ? mono_string_new(Domain, InText) : INVALID_MANAGED;
}

FString FMonoDomain::String_To_UTF8(const IManagedString InManagedString)
{
	const auto String = mono_string_to_utf8(InManagedString);

	auto Result = FString(UTF8_TO_TCHAR(String));

	Free(String);

	return Result;
}

MonoGCHandle FMonoDomain::GCHandle_New_V2(const IManagedObject InManagedObject, const mono_bool bPinned)
{
	return mono_gchandle_new_v2(InManagedObject, bPinned);
}

MonoGCHandle FMonoDomain::GCHandle_New_WeakRef_V2(const IManagedObject InManagedObject,
                                                  const mono_bool bTrackResurrection)
{
	return mono_gchandle_new_weakref_v2(InManagedObject, bTrackResurrection);
}

IManagedObject FMonoDomain::GCHandle_Get_Target_V2(const MonoGCHandle InGCHandle)
{
	return mono_gchandle_get_target_v2(InGCHandle);
}

void FMonoDomain::GCHandle_Free_V2(const MonoGCHandle InGCHandle)
{
	return mono_gchandle_free_v2(InGCHandle);
}

IManagedArray FMonoDomain::Array_New(const IManagedClass InManagedClass, const uint32 InNum)
{
	return mono_array_new(Domain, InManagedClass, InNum);
}

IManagedClass FMonoDomain::Class_From_Name(const FString& InNameSpace, const FString& InName)
{
	for (const auto& Image : Images)
	{
		if (const auto& Class = mono_class_from_name(Image, TCHAR_TO_ANSI(*InNameSpace),
		                                             TCHAR_TO_ANSI(*InName)))
		{
			return Class;
		}
	}

	return INVALID_MANAGED;
}

IManagedMethod FMonoDomain::Class_Get_Method_From_Name(const IManagedClass InManagedClass, const FString& InName,
                                                       const int32 InParamCount)
{
	return IManagedIsValid(InManagedClass)
		       ? mono_class_get_method_from_name(InManagedClass, TCHAR_TO_ANSI(*InName), InParamCount)
		       : INVALID_MANAGED;
}

void FMonoDomain::Field_Static_Set_Value(const IManagedVTable InManagedVTable,
                                         const IManagedClassField InManagedClassField, void* InValue)
{
	mono_field_static_set_value(InManagedVTable, InManagedClassField, InValue);
}

void FMonoDomain::Field_Static_Get_Value(const IManagedVTable InManagedVTable,
                                         const IManagedClassField InManagedClassField, void* OutValue)
{
	mono_field_static_get_value(InManagedVTable, InManagedClassField, OutValue);
}

IManagedObject FMonoDomain::Runtime_Invoke(const IManagedMethod InManagedMethod, const IManagedObject InManagedObject,
                                           void** InParams)
{
	IManagedObject Exception{};

	const auto ReturnValue = Runtime_Invoke(InManagedMethod, InManagedObject, InParams, &Exception);

	if (Exception != nullptr)
	{
		Unhandled_Exception(Exception);

		return INVALID_MANAGED;
	}

	return ReturnValue;
}

IManagedObject FMonoDomain::Runtime_Invoke(const IManagedMethod InManagedMethod, const IManagedObject InManagedObject,
                                           void** InParams, IManagedObject* InExc)
{
	return IManagedIsValid(InManagedMethod)
		       ? mono_runtime_invoke(InManagedMethod, InManagedObject, InParams, InExc)
		       : INVALID_MANAGED;
}

IManagedVTable FMonoDomain::Class_VTable(const IManagedClass InManagedClass)
{
	return Domain != nullptr && IManagedIsValid(InManagedClass)
		       ? mono_class_vtable(Domain, InManagedClass)
		       : INVALID_MANAGED;
}

IManagedReflectionType FMonoDomain::Type_Get_Object(const IManagedType InManagedType)
{
	return Domain != nullptr && IManagedIsValid(InManagedType)
		       ? mono_type_get_object(Domain, InManagedType)
		       : INVALID_MANAGED;
}

IManagedType FMonoDomain::Class_Get_Type(const IManagedClass InManagedClass)
{
	return IManagedIsValid(InManagedClass) ? mono_class_get_type(InManagedClass) : INVALID_MANAGED;
}

IManagedClassField FMonoDomain::Class_Get_Field_From_Name(const IManagedClass InManagedClass, const char* InName)
{
	return IManagedIsValid(InManagedClass) && InName != nullptr
		       ? mono_class_get_field_from_name(InManagedClass, InName)
		       : INVALID_MANAGED;
}

IManagedType FMonoDomain::Reflection_Type_Get_Type(const IManagedReflectionType InManagedReflectionType)
{
	return IManagedIsValid(InManagedReflectionType) ? mono_reflection_type_get_type(InManagedReflectionType) : nullptr;
}

IManagedClass FMonoDomain::Class_From_Type(const IManagedType InManagedType)
{
	return mono_class_from_mono_type(InManagedType);
}

void FMonoDomain::Unhandled_Exception(const IManagedObject InManagedObject)
{
	mono_unhandled_exception(InManagedObject);
}

void FMonoDomain::Free(void* InPointer)
{
	if (InPointer != nullptr)
	{
		mono_free(InPointer);
	}
}

IManagedClass FMonoDomain::Get_Object_Class()
{
	return mono_get_object_class();
}

IManagedClass FMonoDomain::Get_Boolean_Class()
{
	return mono_get_boolean_class();
}

IManagedClass FMonoDomain::Get_SByte_Class()
{
	return mono_get_sbyte_class();
}

IManagedClass FMonoDomain::Get_Int16_Class()
{
	return mono_get_int16_class();
}

IManagedClass FMonoDomain::Get_Int32_Class()
{
	return mono_get_int32_class();
}

IManagedClass FMonoDomain::Get_Int64_Class()
{
	return mono_get_int64_class();
}

IManagedClass FMonoDomain::Get_Byte_Class()
{
	return mono_get_byte_class();
}

IManagedClass FMonoDomain::Get_UInt16_Class()
{
	return mono_get_uint16_class();
}

IManagedClass FMonoDomain::Get_UInt32_Class()
{
	return mono_get_uint32_class();
}

IManagedClass FMonoDomain::Get_UInt64_Class()
{
	return mono_get_uint64_class();
}

IManagedClass FMonoDomain::Get_Single_Class()
{
	return mono_get_single_class();
}

IManagedClass FMonoDomain::Get_Double_Class()
{
	return mono_get_double_class();
}

IManagedClass FMonoDomain::Get_Enum_Class()
{
	return mono_get_enum_class();
}

void* FMonoDomain::Method_Get_Unmanaged_Thunk(const IManagedMethod InManagedMethod)
{
	return mono_method_get_unmanaged_thunk(InManagedMethod);
}

IManagedObject FMonoDomain::Runtime_Invoke_Array(const IManagedMethod InManagedMethod,
                                                 const IManagedObject InManagedObject, const IManagedArray InParams)
{
	IManagedObject Exception{};

	const auto ReturnValue = Runtime_Invoke_Array(InManagedMethod, InManagedObject, InParams, &Exception);

	if (Exception != nullptr)
	{
		Unhandled_Exception(Exception);

		return INVALID_MANAGED;
	}

	return ReturnValue;
}

IManagedObject FMonoDomain::Runtime_Invoke_Array(const IManagedMethod InManagedMethod,
                                                 const IManagedObject InManagedObject, const IManagedArray InParams,
                                                 IManagedObject* InExc)
{
	return IManagedIsValid(InManagedMethod)
		       ? mono_runtime_invoke_array(InManagedMethod, InManagedObject, InParams, InExc)
		       : INVALID_MANAGED;
}

IManagedObject FMonoDomain::Object_Init(const IManagedClass InManagedClass, const int32 InParamCount, void** InParams)
{
	if (const auto Object = Object_New(InManagedClass); IManagedIsValid(Object))
	{
		Object_Constructor(Object, InParamCount, InParams);

		return Object;
	}

	return INVALID_MANAGED;
}

void FMonoDomain::Object_Constructor(const IManagedObject InManagedObject, const int32 InParamCount, void** InParams)
{
	if (const auto FoundClass = mono_object_get_class(InManagedObject))
	{
		if (const auto FoundMethod = Class_Get_Method_From_Name(FoundClass, FUNCTION_OBJECT_CONSTRUCTOR,
		                                                        InParamCount))
		{
			Runtime_Invoke(FoundMethod, InManagedObject, InParams);
		}
	}
}

IManagedMethod FMonoDomain::Class_Get_Method_From_Params(const IManagedClass InManagedClass, const FString& InName,
                                                         const TArray<IManagedType>& InParams)
{
	void* MethodIter{};

	while (const auto Method = mono_class_get_methods(InManagedClass, &MethodIter))
	{
		if (strcmp(mono_method_get_name(Method), TCHAR_TO_ANSI(*InName)))
		{
			continue;
		}

		const auto Signature = mono_method_signature(Method);

		if (mono_signature_get_param_count(Signature) != InParams.Num())
		{
			continue;
		}

		void* ParamIter = {};

		auto Index = 0;

		auto bIsSame = true;

		while (const auto ParamType = mono_signature_get_params(Signature, &ParamIter))
		{
			if (strcmp(mono_type_get_name_full(ParamType, MONO_TYPE_NAME_FORMAT_FULL_NAME),
			           mono_type_get_name_full(InParams[Index], MONO_TYPE_NAME_FORMAT_FULL_NAME)))
			{
				bIsSame = false;

				break;
			}

			Index++;
		}

		if (bIsSame == true)
		{
			return Method;
		}
	}

	return INVALID_MANAGED;
}

IManagedAssembly FMonoDomain::AssemblyPreloadHook(const IManagedAssemblyName InManagedAssemblyName,
                                                  char** OutAssemblyPath, void* InUserData)
{
	auto AssemblyName = FString(mono_assembly_name_get_name(InManagedAssemblyName));

	if (AssemblyName == ASSEMBLY_CORE_LIB_RESOURCE_NAME)
	{
		AssemblyName = ASSEMBLY_CORE_LIB_NAME;
	}

	if (const auto AssemblyLoader = FMonoFunctionLibrary::GetAssemblyLoader())
	{
		if (const auto Data = AssemblyLoader->Load(AssemblyName);
			!Data.IsEmpty())
		{
			IManagedAssembly Assembly{};

			LoadAssembly(AssemblyName, Data, nullptr, &Assembly);

			return Assembly;
		}
	}

	return INVALID_MANAGED;
}

void FMonoDomain::LoadAssembly(const FString& InAssemblyName, const TArray<uint8>& InData, IManagedImage* OutImage,
                               IManagedAssembly* OutAssembly)
{
	auto ImageOpenStatus = MonoImageOpenStatus::MONO_IMAGE_OK;

	const auto Image = mono_image_open_from_data_with_name((char*)InData.GetData(), InData.Num(),
	                                                       true, &ImageOpenStatus,
	                                                       false, TCHAR_TO_UTF8(*InAssemblyName));

	if (ImageOpenStatus != MonoImageOpenStatus::MONO_IMAGE_OK)
	{
		// @TODO
		return;
	}

	const auto Assembly = mono_assembly_load_from_full(Image, TCHAR_TO_UTF8(*InAssemblyName), &ImageOpenStatus, false);

	if (ImageOpenStatus != MonoImageOpenStatus::MONO_IMAGE_OK)
	{
		// @TODO
		return;
	}

	if (OutImage != nullptr)
	{
		*OutImage = Image;
	}

	if (OutAssembly != nullptr)
	{
		*OutAssembly = Assembly;
	}
}

void FMonoDomain::LoadAssembly(const FString& InAssemblyName, const FString& InFile, IManagedImage* OutImage,
                               IManagedAssembly* OutAssembly)
{
	TArray<uint8> Data;

	FFileHelper::LoadFileToArray(Data, *InFile);

	LoadAssembly(InAssemblyName, Data, OutImage, OutAssembly);
}

void FMonoDomain::InitializeAssembly(const TArray<FString>& InAssemblies)
{
#if WITH_EDITOR
	InitializeAssemblyLoadContext();
#endif

	LoadAssembly(InAssemblies);
}

void FMonoDomain::DeinitializeAssembly()
{
	UnloadAssembly();

#if WITH_EDITOR
	DeinitializeAssemblyLoadContext();
#endif
}

void FMonoDomain::InitializeAssemblyLoadContext()
{
	const auto Name = mono_assembly_name_new("System.Runtime.Loader");

	auto Assembly = mono_assembly_loaded(Name);

	if (Assembly == nullptr)
	{
		Assembly = mono_assembly_load(Name, nullptr, nullptr);
	}

	const auto Image = mono_assembly_get_image(Assembly);

	const auto AssemblyLoadContextClass = mono_class_from_name(Image, "System.Runtime.Loader", "AssemblyLoadContext");

	void* Params[2];

	auto bIsCollectible = true;

	Params[0] = String_New("MonoCSharp");

	Params[1] = Value_Box(Get_Boolean_Class(), &bIsCollectible);

	const auto AssemblyLoadContextObject = Object_Init(AssemblyLoadContextClass, 2, Params);

	AssemblyLoadContextGCHandle = GCHandle_New_V2(AssemblyLoadContextObject, false);
}

void FMonoDomain::DeinitializeAssemblyLoadContext()
{
	if (AssemblyLoadContextGCHandle == nullptr)
	{
		return;
	}

	const auto AssemblyLoadContextObject = GCHandle_Get_Target_V2(AssemblyLoadContextGCHandle);

	const auto AssemblyLoadContextClass = mono_object_get_class(AssemblyLoadContextObject);

	const auto UnloadMethod = Class_Get_Method_From_Name(AssemblyLoadContextClass, TEXT("Unload"), 0);

	IManagedObject Exception{};

	Runtime_Invoke(UnloadMethod, AssemblyLoadContextObject, nullptr, &Exception);

	GCHandle_Free_V2(AssemblyLoadContextGCHandle);

	AssemblyLoadContextGCHandle = nullptr;
}

void FMonoDomain::LoadAssembly(const TArray<FString>& InAssemblies)
{
#if WITH_EDITOR
	const auto Name = mono_assembly_name_new("System.Runtime");

	auto Assembly = mono_assembly_loaded(Name);

	if (Assembly == nullptr)
	{
		Assembly = mono_assembly_load(Name, nullptr, nullptr);
	}

	const auto Image = mono_assembly_get_image(Assembly);

	const auto StreamReaderClass = mono_class_from_name(Image, "System.IO", "StreamReader");

	const auto TextReaderClass = mono_class_from_name(Image, "System.IO", "TextReader");

	const auto BaseStreamProperty = mono_class_get_property_from_name(StreamReaderClass, "BaseStream");

	const auto BaseStreamGetterMethod = mono_property_get_get_method(BaseStreamProperty);

	const auto StreamReaderConstructorMethod = Class_Get_Method_From_Params(
		StreamReaderClass, FUNCTION_OBJECT_CONSTRUCTOR,
		TArray<IManagedType>{
			mono_class_get_type(mono_get_string_class())
		});

	const auto TextReaderDisposeMethod = Class_Get_Method_From_Name(TextReaderClass, TEXT("Dispose"), 0);

	const auto AssemblyLoadContextObject = GCHandle_Get_Target_V2(AssemblyLoadContextGCHandle);

	const auto AssemblyLoadContextClass = mono_object_get_class(AssemblyLoadContextObject);

	const auto AlcLoadFromStreamMethod = Class_Get_Method_From_Name(AssemblyLoadContextClass, "LoadFromStream", 1);

	for (const auto& AssemblyPath : InAssemblies)
	{
		if (!FPaths::FileExists(AssemblyPath))
		{
			continue;
		}

		void* Params[1];

		Params[0] = String_New(TCHAR_TO_UTF8(*AssemblyPath));

		const auto StreamObject = Object_New(StreamReaderClass);

		Runtime_Invoke(StreamReaderConstructorMethod, StreamObject, Params);

		const auto BaseStream = Runtime_Invoke(BaseStreamGetterMethod, StreamObject, nullptr);

		Params[0] = BaseStream;

		const auto Result = Runtime_Invoke(AlcLoadFromStreamMethod, AssemblyLoadContextObject, Params);

		Runtime_Invoke(TextReaderDisposeMethod, StreamObject, nullptr);

		auto GCHandle = GCHandle_New_V2(Result, true);

		AssemblyGCHandles.Add(GCHandle);

		const auto ReflectionAssembly = (IManagedReflectionAssembly)GCHandle_Get_Target_V2(GCHandle);

		Assembly = mono_reflection_assembly_get_assembly(ReflectionAssembly);

		Assemblies.Add(Assembly);

		Images.Add(mono_assembly_get_image(Assembly));
	}
#else
	for (const auto& AssemblyPath : InAssemblies)
	{
		if (!FPaths::FileExists(AssemblyPath))
		{
			continue;
		}

		IManagedImage Image{};

		IManagedAssembly Assembly{};

		LoadAssembly(FPaths::GetBaseFilename(AssemblyPath), AssemblyPath, &Image, &Assembly);

		if (IManagedIsValid(Image))
		{
			Images.Add(Image);
		}

		if (IManagedIsValid(Assembly))
		{
			Assemblies.Add(Assembly);

			const auto ReflectionAssembly = mono_assembly_get_object(Domain, Assembly);

			auto GCHandle = GCHandle_New_V2((IManagedObject)ReflectionAssembly, true);

			AssemblyGCHandles.Add(GCHandle);
		}
	}
#endif

	bIsInitialized = Assemblies.Num() == InAssemblies.Num();
}

void FMonoDomain::UnloadAssembly()
{
	for (const auto GCHandle : AssemblyGCHandles)
	{
		GCHandle_Free_V2(GCHandle);
	}

	AssemblyGCHandles.Reset();

	for (const auto& Image : Images)
	{
		mono_image_close(Image);
	}

	Images.Reset();

	Assemblies.Reset();

	bIsInitialized = false;
}

void FMonoDomain::RegisterAssemblyPreloadHook()
{
	mono_install_assembly_preload_hook(AssemblyPreloadHook, nullptr);
}

void FMonoDomain::RegisterMonoTrace()
{
	mono_trace_set_log_handler(FMonoLog::Log, nullptr);

	mono_trace_set_print_handler(FMonoLog::Printf);

	mono_trace_set_printerr_handler(FMonoLog::PrintfError);
}

void FMonoDomain::RegisterLog()
{
	if (Domain != nullptr)
	{
		if (const auto UtilsClass = FReflectionRegistry::Get().GetUtilsClass())
		{
			if (const auto FoundMethod = UtilsClass->GetMethod(FUNCTION_UTILS_SET_OUT, 0))
			{
				FoundMethod->Runtime_Invoke(InvalidManagedHandle, nullptr);
			}
		}
	}
}

void FMonoDomain::RegisterBinding()
{
	for (const auto& Class : FBinding::Get().Register().GetClasses())
	{
		for (const auto& Method : Class->GetMethods())
		{
			mono_add_internal_call(TCHAR_TO_ANSI(*Method.GetMethod()), Method.GetFunction());
		}
	}
}

void FMonoDomain::RegisterProfiler()
{
#if UE_TRACE_ENABLED
	FMonoProfiler::Register();
#endif
}

void FMonoDomain::RegisterSynchronizationContextTick()
{
	if (const auto SynchronizationContextClass = FReflectionRegistry::Get().GetClass(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_SYNCHRONIZATION_CONTEXT))
	{
		if (const auto TickMethod = SynchronizationContextClass->GetMethod(FUNCTION_SYNCHRONIZATION_CONTEXT_TICK, 1))
		{
			SynchronizationContextTick = reinterpret_cast<SynchronizationContextTickType>(
				TickMethod->Method_Get_Unmanaged_Thunk());
		}
	}
}

MonoGCHandle FMonoDomain::HandleToMonoGCHandle(const IManagedHandle InManagedHandle)
{
	return reinterpret_cast<MonoGCHandle>(static_cast<UPTRINT>(InManagedHandle));
}

IManagedHandle FMonoDomain::MonoGCHandleToHandle(MonoGCHandle InMonoGCHandle)
{
	return static_cast<IManagedHandle>(reinterpret_cast<UPTRINT>(InMonoGCHandle));
}

PRAGMA_ENABLE_DANGLING_WARNINGS
#endif
