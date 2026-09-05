#pragma once

#include "CoreMacro/PropertyMacro.h"
#include "Template/TGetUtf8String.inl"
#include "UEVersion.h"

#ifndef SCRIPT_DOMAIN_INVOKE
#define SCRIPT_DOMAIN_INVOKE(Return, Fn, ...) Fn(__VA_ARGS__)
#endif

#ifndef SCRIPT_DOMAIN_STRING_CAST
#define SCRIPT_DOMAIN_STRING_CAST(InString) \
	reinterpret_cast<const uint8*>(StringCast<UTF8CHAR>(*(InString)).Get())
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_TICK
void SCRIPT_DOMAIN_TYPE::Tick(const float InDeltaTime)
{
	if (SynchronizationContextTickFn != nullptr)
	{
		SCRIPT_DOMAIN_INVOKE(void, SynchronizationContextTickFn, InDeltaTime);
	}
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_GET_NAMESPACE
FString SCRIPT_DOMAIN_TYPE::GetNamespace(const IManagedHandle InManagedClass)
{
	return IManagedHandleIsValid(InManagedClass) && TypeBridgeGetNamespaceFn != nullptr
		       ? TGetUTF8String(
			       [this, InManagedClass](uint8* OutString, const int32 InSize)
			       {
				       return SCRIPT_DOMAIN_INVOKE(int32, TypeBridgeGetNamespaceFn, InManagedClass, OutString, InSize);
			       })
		       : FString{};
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_GET_NAME
FString SCRIPT_DOMAIN_TYPE::GetName(const IManagedHandle InManagedClass)
{
	return IManagedHandleIsValid(InManagedClass) && TypeBridgeGetNameFn != nullptr
		       ? TGetUTF8String(
			       [this, InManagedClass](uint8* OutString, const int32 InSize)
			       {
				       return SCRIPT_DOMAIN_INVOKE(int32, TypeBridgeGetNameFn, InManagedClass, OutString, InSize);
			       })
		       : FString{};
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_GET_FULL_NAME
FString SCRIPT_DOMAIN_TYPE::GetFullName(const IManagedHandle InManagedClass)
{
	auto Result = IManagedHandleIsValid(InManagedClass) && TypeBridgeGetFullNameFn != nullptr
		              ? TGetUTF8String(
			              [this, InManagedClass](uint8* OutString, const int32 InSize)
			              {
				              return SCRIPT_DOMAIN_INVOKE(int32, TypeBridgeGetFullNameFn, InManagedClass, OutString,
				                                          InSize);
			              })
		              : FString{};

	if (int32 Index; Result.FindLastChar(TEXT(','), Index))
	{
		Result = Result.Left(Index).TrimEnd();
	}

	return Result;
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_NEW_OBJECT
IManagedHandle SCRIPT_DOMAIN_TYPE::NewObject(const IManagedHandle InManagedClass)
{
	return ObjectBridgeNewObjectFn != nullptr
		       ? SCRIPT_DOMAIN_INVOKE(IManagedHandle, ObjectBridgeNewObjectFn, InManagedClass)
		       : InvalidManagedHandle;
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_BOX_VALUE
IManagedHandle SCRIPT_DOMAIN_TYPE::BoxValue(const FString& InName, void* InValue)
{
	if (InValue != nullptr)
	{
		if (InName == TEXT("bool") || InName == TEXT("Boolean"))
		{
			if (TypeBridgeBoxBoolFn != nullptr)
			{
				return SCRIPT_DOMAIN_INVOKE(IManagedHandle, TypeBridgeBoxBoolFn, static_cast<int*>(InValue));
			}
		}
		else if (InName == TEXT("sbyte") || InName == TEXT("SByte") || InName == TEXT("int8"))
		{
			if (TypeBridgeBoxSByteFn != nullptr)
			{
				return SCRIPT_DOMAIN_INVOKE(IManagedHandle, TypeBridgeBoxSByteFn, static_cast<int8*>(InValue));
			}
		}
		else if (InName == TEXT("int16") || InName == TEXT("Int16") || InName == TEXT("short"))
		{
			if (TypeBridgeBoxInt16Fn != nullptr)
			{
				return SCRIPT_DOMAIN_INVOKE(IManagedHandle, TypeBridgeBoxInt16Fn, static_cast<int16*>(InValue));
			}
		}
		else if (InName == TEXT("int32") || InName == TEXT("Int32") || InName == TEXT("int"))
		{
			if (TypeBridgeBoxInt32Fn != nullptr)
			{
				return SCRIPT_DOMAIN_INVOKE(IManagedHandle, TypeBridgeBoxInt32Fn, static_cast<int32*>(InValue));
			}
		}
		else if (InName == TEXT("int64") || InName == TEXT("Int64") || InName == TEXT("long"))
		{
			if (TypeBridgeBoxInt64Fn != nullptr)
			{
				return SCRIPT_DOMAIN_INVOKE(IManagedHandle, TypeBridgeBoxInt64Fn, static_cast<int64*>(InValue));
			}
		}
		else if (InName == TEXT("byte") || InName == TEXT("Byte") || InName == TEXT("uint8"))
		{
			if (TypeBridgeBoxByteFn != nullptr)
			{
				return SCRIPT_DOMAIN_INVOKE(IManagedHandle, TypeBridgeBoxByteFn, static_cast<uint8*>(InValue));
			}
		}
		else if (InName == TEXT("uint16") || InName == TEXT("UInt16") || InName == TEXT("ushort"))
		{
			if (TypeBridgeBoxUInt16Fn != nullptr)
			{
				return SCRIPT_DOMAIN_INVOKE(IManagedHandle, TypeBridgeBoxUInt16Fn, static_cast<uint16*>(InValue));
			}
		}
		else if (InName == TEXT("uint32") || InName == TEXT("UInt32") || InName == TEXT("uint"))
		{
			if (TypeBridgeBoxUInt32Fn != nullptr)
			{
				return SCRIPT_DOMAIN_INVOKE(IManagedHandle, TypeBridgeBoxUInt32Fn, static_cast<uint32*>(InValue));
			}
		}
		else if (InName == TEXT("uint64") || InName == TEXT("UInt64") || InName == TEXT("ulong"))
		{
			if (TypeBridgeBoxUInt64Fn != nullptr)
			{
				return SCRIPT_DOMAIN_INVOKE(IManagedHandle, TypeBridgeBoxUInt64Fn, static_cast<uint64*>(InValue));
			}
		}
		else if (InName == TEXT("float") || InName == TEXT("Single"))
		{
			if (TypeBridgeBoxFloatFn != nullptr)
			{
				return SCRIPT_DOMAIN_INVOKE(IManagedHandle, TypeBridgeBoxFloatFn, static_cast<float*>(InValue));
			}
		}
		else if (InName == TEXT("double") || InName == TEXT("Double"))
		{
			if (TypeBridgeBoxDoubleFn != nullptr)
			{
				return SCRIPT_DOMAIN_INVOKE(IManagedHandle, TypeBridgeBoxDoubleFn, static_cast<double*>(InValue));
			}
		}
	}

	return InvalidManagedHandle;
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_UNBOX_VALUE
void* SCRIPT_DOMAIN_TYPE::UnboxValue(const IManagedHandle InManagedHandle)
{
	static uint64 Result{};

	if (IManagedHandleIsValid(InManagedHandle))
	{
		if (TypeBridgeUnboxBoolFn != nullptr)
		{
			int32 Value{};

			if (SCRIPT_DOMAIN_INVOKE(int32, TypeBridgeUnboxBoolFn, InManagedHandle, &Value))
			{
				*static_cast<bool*>(static_cast<void*>(&Result)) = Value != 0;

				return &Result;
			}
		}

		if (TypeBridgeUnboxSByteFn != nullptr)
		{
			if (SCRIPT_DOMAIN_INVOKE(int32, TypeBridgeUnboxSByteFn, InManagedHandle,
			                         static_cast<int8*>(static_cast<void*>(&Result))))
			{
				return &Result;
			}
		}

		if (TypeBridgeUnboxInt16Fn != nullptr)
		{
			if (SCRIPT_DOMAIN_INVOKE(int32, TypeBridgeUnboxInt16Fn, InManagedHandle,
			                         static_cast<int16*>(static_cast<void*>(&Result))))
			{
				return &Result;
			}
		}

		if (TypeBridgeUnboxInt32Fn != nullptr)
		{
			if (SCRIPT_DOMAIN_INVOKE(int32, TypeBridgeUnboxInt32Fn, InManagedHandle,
			                         static_cast<int32*>(static_cast<void*>(&Result))))
			{
				return &Result;
			}
		}

		if (TypeBridgeUnboxInt64Fn != nullptr)
		{
			if (SCRIPT_DOMAIN_INVOKE(int32, TypeBridgeUnboxInt64Fn, InManagedHandle,
			                         static_cast<int64*>(static_cast<void*>(&Result))))
			{
				return &Result;
			}
		}

		if (TypeBridgeUnboxByteFn != nullptr)
		{
			if (SCRIPT_DOMAIN_INVOKE(int32, TypeBridgeUnboxByteFn, InManagedHandle,
			                         static_cast<uint8*>(static_cast<void*>(&Result))))
			{
				return &Result;
			}
		}

		if (TypeBridgeUnboxUInt16Fn != nullptr)
		{
			if (SCRIPT_DOMAIN_INVOKE(int32, TypeBridgeUnboxUInt16Fn, InManagedHandle,
			                         static_cast<uint16*>(static_cast<void*>(&Result))))
			{
				return &Result;
			}
		}

		if (TypeBridgeUnboxUInt32Fn != nullptr)
		{
			if (SCRIPT_DOMAIN_INVOKE(int32, TypeBridgeUnboxUInt32Fn, InManagedHandle,
			                         static_cast<uint32*>(static_cast<void*>(&Result))))
			{
				return &Result;
			}
		}

		if (TypeBridgeUnboxUInt64Fn != nullptr)
		{
			if (SCRIPT_DOMAIN_INVOKE(int32, TypeBridgeUnboxUInt64Fn, InManagedHandle,
			                         static_cast<uint64*>(static_cast<void*>(&Result))))
			{
				return &Result;
			}
		}

		if (TypeBridgeUnboxFloatFn != nullptr)
		{
			if (SCRIPT_DOMAIN_INVOKE(int32, TypeBridgeUnboxFloatFn, InManagedHandle,
			                         static_cast<float*>(static_cast<void*>(&Result))))
			{
				return &Result;
			}
		}

		if (TypeBridgeUnboxDoubleFn != nullptr)
		{
			if (SCRIPT_DOMAIN_INVOKE(int32, TypeBridgeUnboxDoubleFn, InManagedHandle,
			                         static_cast<double*>(static_cast<void*>(&Result))))
			{
				return &Result;
			}
		}
	}

	return nullptr;
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_NEW_STRING
IManagedHandle SCRIPT_DOMAIN_TYPE::NewString(const char* InText)
{
	return StringBridgeNewStringFn != nullptr && InText != nullptr
		       ? SCRIPT_DOMAIN_INVOKE(IManagedHandle, StringBridgeNewStringFn, reinterpret_cast<const uint8*>(InText))
		       : InvalidManagedHandle;
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_STRING_TO_FSTRING
FString SCRIPT_DOMAIN_TYPE::StringToFString(const IManagedHandle InManagedHandle)
{
	if (IManagedHandleIsValid(InManagedHandle))
	{
		if (StringBridgeGetStringFn != nullptr)
		{
			constexpr auto Size = 1024;

			char16_t String[Size];

			if (const auto Length = SCRIPT_DOMAIN_INVOKE(int32, StringBridgeGetStringFn, InManagedHandle, String, Size);
				Length >= 0)
			{
#if UE_F_STRING_CONSTRUCT_FROM_PTR_SIZE
				return FString::ConstructFromPtrSize(reinterpret_cast<const UCS2CHAR*>(String), Length);
#else
				return FString(Length, reinterpret_cast<const UCS2CHAR*>(String));
#endif
			}

			constexpr auto MaxSize = 65536;

			TArray<char16_t> StringArray;

			StringArray.SetNumUninitialized(MaxSize);

			if (const auto Length = SCRIPT_DOMAIN_INVOKE(int32, StringBridgeGetStringFn, InManagedHandle,
			                                             StringArray.GetData(), MaxSize);
				Length >= 0)
			{
#if UE_F_STRING_CONSTRUCT_FROM_PTR_SIZE
				return FString::ConstructFromPtrSize(reinterpret_cast<const UCS2CHAR*>(StringArray.GetData()), Length);
#else
				return FString(Length, reinterpret_cast<const UCS2CHAR*>(StringArray.GetData()));
#endif
			}
		}
	}

	return {};
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_FREE
void SCRIPT_DOMAIN_TYPE::Free(const IManagedHandle InManagedHandle)
{
	if (IManagedHandleIsValid(InManagedHandle))
	{
		if (HandleDataFreeFn != nullptr)
		{
			HandleDataFreeFn(InManagedHandle.Value);
		}
	}
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_NEW_ARRAY
IManagedHandle SCRIPT_DOMAIN_TYPE::NewArray(const FString& InNamespace, const FString& InName, const int32 InLength)
{
	return InLength > 0 && ArrayBridgeNewArrayFn != nullptr
		       ? SCRIPT_DOMAIN_INVOKE(IManagedHandle, ArrayBridgeNewArrayFn,
		                              SCRIPT_DOMAIN_STRING_CAST(COMBINE_FULL_NAME(InNamespace, InName)),
		                              InLength)
		       : InvalidManagedHandle;
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_ARRAY_GET
IManagedHandle SCRIPT_DOMAIN_TYPE::ArrayGet(const IManagedHandle InManagedArray, const int32 InIndex)
{
	return IManagedHandleIsValid(InManagedArray) && ArrayBridgeArrayGetFn != nullptr
		       ? SCRIPT_DOMAIN_INVOKE(IManagedHandle, ArrayBridgeArrayGetFn, InManagedArray, InIndex)
		       : InvalidManagedHandle;
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_GET_CLASS
IManagedHandle SCRIPT_DOMAIN_TYPE::GetClass(const FString& InNamespace, const FString& InName)
{
	return TypeBridgeGetClassFn != nullptr
		       ? SCRIPT_DOMAIN_INVOKE(IManagedHandle, TypeBridgeGetClassFn,
		                              SCRIPT_DOMAIN_STRING_CAST(COMBINE_FULL_NAME(InNamespace, InName)))
		       : InvalidManagedHandle;
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_GET_METHOD
IManagedHandle SCRIPT_DOMAIN_TYPE::GetMethod(const IManagedHandle InManagedClass, const FString& InName,
                                             const int32 InParamCount)
{
	return IManagedHandleIsValid(InManagedClass) && TypeBridgeGetMethodFn != nullptr
		       ? SCRIPT_DOMAIN_INVOKE(IManagedHandle, TypeBridgeGetMethodFn, InManagedClass,
		                              SCRIPT_DOMAIN_STRING_CAST(InName), InParamCount)
		       : InvalidManagedHandle;
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_SET_FIELD_STATIC_VALUE
void SCRIPT_DOMAIN_TYPE::SetFieldStaticValue(const IManagedHandle InManagedClass, const FString& InName, void* InValue)
{
	if (IManagedHandleIsValid(InManagedClass))
	{
		if (FieldBridgeSetStaticValueFn != nullptr)
		{
			SCRIPT_DOMAIN_INVOKE(void, FieldBridgeSetStaticValueFn, InManagedClass, SCRIPT_DOMAIN_STRING_CAST(InName),
			                     IManagedHandle{*static_cast<uint32*>(InValue)});
		}
	}
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_GET_FIELD_STATIC_VALUE
void* SCRIPT_DOMAIN_TYPE::GetFieldStaticValue(const IManagedHandle InManagedClass, const FString& InName)
{
	return IManagedHandleIsValid(InManagedClass) && FieldBridgeGetStaticValueFn != nullptr
		       ? IManagedHandleToObject(SCRIPT_DOMAIN_INVOKE(IManagedHandle, FieldBridgeGetStaticValueFn,
		                                                     InManagedClass, SCRIPT_DOMAIN_STRING_CAST(InName)))
		       : nullptr;
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_SET_PROPERTY_VALUE
void SCRIPT_DOMAIN_TYPE::SetPropertyValue(const IManagedHandle InManagedHandle, const FString& InName, void** InParams)
{
	if (TypeBridgeGetTypeFn != nullptr)
	{
		if (const auto Class = SCRIPT_DOMAIN_INVOKE(IManagedHandle, TypeBridgeGetTypeFn, InManagedHandle);
			IManagedHandleIsValid(Class))
		{
			const auto Name = FString::Printf(TEXT(
				"%s%s"),
			                                  *PROPERTY_SET_PREFIX,
			                                  *InName
			);

			if (const auto Method = GetMethod(Class, Name, 1);
				IManagedHandleIsValid(Method))
			{
				Invoke(InManagedHandle, Method, 1, InParams);

				Free(Method);
			}

			Free(Class);
		}
	}
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_MAKE_GENERIC_TYPE
FClassReflection* SCRIPT_DOMAIN_TYPE::MakeGenericType(const FClassReflection* InGeneric, const FClassReflection* InType)
{
	return TypeBridgeMakeGenericTypeFn != nullptr && InGeneric != nullptr && InType != nullptr
		       ? FReflectionRegistry::Get().GetClass(
			       SCRIPT_DOMAIN_INVOKE(IManagedHandle, TypeBridgeMakeGenericTypeFn, InGeneric->GetManagedClass(),
			                            InType->GetManagedClass()))
		       : nullptr;
}

FClassReflection* SCRIPT_DOMAIN_TYPE::MakeGenericType(const FClassReflection* InGeneric,
                                                      const FClassReflection* InKeyType,
                                                      const FClassReflection* InValueType)
{
	return TypeBridgeMakeGenericType2Fn != nullptr &&
	       InGeneric != nullptr && InKeyType != nullptr && InValueType != nullptr
		       ? FReflectionRegistry::Get().GetClass(
			       SCRIPT_DOMAIN_INVOKE(IManagedHandle, TypeBridgeMakeGenericType2Fn, InGeneric->GetManagedClass(),
			                            InKeyType->GetManagedClass(), InValueType->GetManagedClass()))
		       : nullptr;
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_INVOKE
IManagedHandle SCRIPT_DOMAIN_TYPE::Invoke(const IManagedHandle InManagedHandle, const IManagedHandle InManagedMethod,
                                          const int32 InParamCount, void** InParams)
{
	return IManagedHandleIsValid(InManagedMethod) && MethodBridgeInvokeFn != nullptr
		       ? SCRIPT_DOMAIN_INVOKE(IManagedHandle, MethodBridgeInvokeFn, InManagedHandle, InManagedMethod,
		                              InParamCount, reinterpret_cast<IManagedHandle*>(InParams))
		       : InvalidManagedHandle;
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_IS_OVERRIDE
bool SCRIPT_DOMAIN_TYPE::IsOverride(const IManagedHandle InManagedClass)
{
	return UtilsIsOverrideFn != nullptr && SCRIPT_DOMAIN_INVOKE(int32, UtilsIsOverrideFn, InManagedClass) != 0;
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_GET_CLASS_DESCRIPTOR
void SCRIPT_DOMAIN_TYPE::GetClassDescriptor(const IManagedHandle InManagedClass, PTRINT* OutParams)
{
	if (UtilsGetClassDescriptorFn != nullptr)
	{
		SCRIPT_DOMAIN_INVOKE(void, UtilsGetClassDescriptorFn, InManagedClass, OutParams);
	}
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_GET_CLASS_PROPERTIES
void SCRIPT_DOMAIN_TYPE::GetClassProperties(const IManagedHandle InManagedClass, PTRINT* OutParams)
{
	if (UtilsGetClassPropertiesFn != nullptr)
	{
		SCRIPT_DOMAIN_INVOKE(void, UtilsGetClassPropertiesFn, InManagedClass, OutParams);
	}
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_GET_CLASS_FIELDS
void SCRIPT_DOMAIN_TYPE::GetClassFields(const IManagedHandle InManagedClass, PTRINT* OutParams)
{
	if (UtilsGetClassFieldsFn != nullptr)
	{
		SCRIPT_DOMAIN_INVOKE(void, UtilsGetClassFieldsFn, InManagedClass, OutParams);
	}
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_GET_CLASS_METHODS
void SCRIPT_DOMAIN_TYPE::GetClassMethods(const IManagedHandle InManagedClass, PTRINT* OutParams)
{
	if (UtilsGetClassMethodsFn != nullptr)
	{
		SCRIPT_DOMAIN_INVOKE(void, UtilsGetClassMethodsFn, InManagedClass, OutParams);
	}
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_IS_INITIALIZED
bool SCRIPT_DOMAIN_TYPE::IsInitialized() const
{
	return bIsInitialized;
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_GET_ASSEMBLIES
TArray<IManagedHandle> SCRIPT_DOMAIN_TYPE::GetAssemblies() const
{
	return Assemblies;
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_GET_CLASSES_WITH_ATTRIBUTE
TArray<FClassReflection*> SCRIPT_DOMAIN_TYPE::GetClassesWithAttribute(const FClassReflection* InClass,
                                                                      const IManagedHandle InManagedHandle)
{
	TArray<FClassReflection*> Result;

	if (const auto UtilsClass = FReflectionRegistry::Get().GetUtilsClass())
	{
		if (const auto GetTypesWithAttributeMethod = UtilsClass->GetMethod(FUNCTION_UTILS_GET_TYPES_WITH_ATTRIBUTE, 3))
		{
			int32 OutLength{};

			auto ManagedClass = InClass->GetManagedClass();

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
					if (const auto Element = ArrayGet(Types, Index);
						IManagedHandleIsValid(Element))
					{
						Result.Add(FReflectionRegistry::Get().GetClass(
							GetNamespace(Element),
							GetName(Element)));

						Free(Element);
					}
				}

				Free(Types);
			}
		}
	}

	return Result;
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_REGISTER_LOG
void SCRIPT_DOMAIN_TYPE::RegisterLog()
{
	if (LogBridgeSetLogFn != nullptr)
	{
		LogBridgeSetLogFn(reinterpret_cast<PTRINT>(&FScriptLog::Log));
	}

	if (LogBridgeInitializeFn != nullptr)
	{
		LogBridgeInitializeFn();
	}
}
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_REGISTER_BINDING
void SCRIPT_DOMAIN_TYPE::RegisterBinding() const
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
#endif

#ifndef SCRIPT_DOMAIN_CUSTOM_REGISTER_SYNCHRONIZATION_CONTEXT_TICK
void SCRIPT_DOMAIN_TYPE::RegisterSynchronizationContextTick()
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
#endif

#undef SCRIPT_DOMAIN_STRING_CAST
#undef SCRIPT_DOMAIN_INVOKE
