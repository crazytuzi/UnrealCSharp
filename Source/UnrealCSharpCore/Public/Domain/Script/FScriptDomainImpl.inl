void SCRIPT_DOMAIN_TYPE::Tick(const float InDeltaTime)
{
	if (SynchronizationContextTickFn != nullptr)
	{
		SynchronizationContextTickFn(InDeltaTime);
	}
}

FString SCRIPT_DOMAIN_TYPE::GetNamespace(const IManagedHandle InManagedClass)
{
	if (IManagedHandleIsValid(InManagedClass))
	{
		if (TypeBridgeGetNamespaceFn != nullptr)
		{
			constexpr auto Size = 512;

			uint8 String[Size];

			if (const auto Length = TypeBridgeGetNamespaceFn(InManagedClass, String, Size);
				Length > 0)
			{
				return FString(UTF8_TO_TCHAR(reinterpret_cast<const char*>(String)));
			}
		}
	}

	return {};
}

FString SCRIPT_DOMAIN_TYPE::GetName(const IManagedHandle InManagedClass)
{
	if (IManagedHandleIsValid(InManagedClass))
	{
		if (TypeBridgeGetNameFn != nullptr)
		{
			constexpr auto Size = 512;

			uint8 String[Size];

			if (const auto Length = TypeBridgeGetNameFn(InManagedClass, String, Size);
				Length > 0)
			{
				return FString(UTF8_TO_TCHAR(reinterpret_cast<const char*>(String)));
			}
		}
	}

	return {};
}

FString SCRIPT_DOMAIN_TYPE::GetFullName(const IManagedHandle InManagedClass)
{
	if (IManagedHandleIsValid(InManagedClass))
	{
		if (TypeBridgeGetFullNameFn != nullptr)
		{
			constexpr auto Size = 512;

			uint8 String[Size];

			if (const auto Length = TypeBridgeGetFullNameFn(InManagedClass, String, Size);
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

IManagedHandle SCRIPT_DOMAIN_TYPE::NewObject(const IManagedHandle InManagedClass)
{
	return ObjectBridgeNewObjectFn != nullptr
		       ? ObjectBridgeNewObjectFn(InManagedClass)
		       : InvalidManagedHandle;
}

IManagedHandle SCRIPT_DOMAIN_TYPE::BoxValue(const FString& InNamespace, const FString& InName, void* InValue)
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

void* SCRIPT_DOMAIN_TYPE::UnboxValue(const IManagedHandle InManagedHandle)
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

IManagedHandle SCRIPT_DOMAIN_TYPE::NewString(const char* InText)
{
	return StringBridgeNewStringFn != nullptr && InText != nullptr
		       ? StringBridgeNewStringFn(reinterpret_cast<const uint8*>(InText))
		       : InvalidManagedHandle;
}

FString SCRIPT_DOMAIN_TYPE::StringToFString(const IManagedHandle InManagedHandle)
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

IManagedHandle SCRIPT_DOMAIN_TYPE::NewArray(const FString& InNamespace, const FString& InName, const int32 InLength)
{
	if (InLength > 0)
	{
		if (ArrayBridgeNewArrayFn != nullptr)
		{
			return ArrayBridgeNewArrayFn(
				reinterpret_cast<const uint8*>(StringCast<UTF8CHAR>(*COMBINE_FULL_NAME(InNamespace, InName)).Get()),
				InLength);
		}
	}

	return InvalidManagedHandle;
}

IManagedHandle SCRIPT_DOMAIN_TYPE::ArrayGet(const IManagedHandle InManagedArray, const int32 InIndex)
{
	if (IManagedHandleIsValid(InManagedArray))
	{
		if (ArrayBridgeArrayGetFn != nullptr)
		{
			return ArrayBridgeArrayGetFn(InManagedArray, InIndex);
		}
	}

	return InvalidManagedHandle;
}

IManagedHandle SCRIPT_DOMAIN_TYPE::GetClass(const FString& InNamespace, const FString& InName)
{
	if (TypeBridgeGetClassFn != nullptr)
	{
		return TypeBridgeGetClassFn(
			reinterpret_cast<const uint8*>(StringCast<UTF8CHAR>(*COMBINE_FULL_NAME(InNamespace, InName)).Get()));
	}

	return InvalidManagedHandle;
}

IManagedHandle SCRIPT_DOMAIN_TYPE::GetMethod(const IManagedHandle InManagedClass, const FString& InName,
                                             const int32 InParamCount)
{
	if (IManagedHandleIsValid(InManagedClass))
	{
		if (TypeBridgeGetMethodFn != nullptr)
		{
			return TypeBridgeGetMethodFn(
				InManagedClass,
				reinterpret_cast<const uint8*>(StringCast<UTF8CHAR>(*InName).Get()),
				InParamCount);
		}
	}

	return InvalidManagedHandle;
}

void SCRIPT_DOMAIN_TYPE::SetFieldStaticValue(const IManagedHandle InManagedClass, const FString& InName, void* InValue)
{
	if (IManagedHandleIsValid(InManagedClass))
	{
		if (FieldBridgeSetStaticValueFn != nullptr)
		{
			FieldBridgeSetStaticValueFn(InManagedClass,
			                            reinterpret_cast<const uint8*>(StringCast<UTF8CHAR>(*InName).Get()),
			                            IManagedHandle{*static_cast<uint32*>(InValue)});
		}
	}
}

void* SCRIPT_DOMAIN_TYPE::GetFieldStaticValue(const IManagedHandle InManagedClass, const FString& InName)
{
	if (IManagedHandleIsValid(InManagedClass))
	{
		if (FieldBridgeGetStaticValueFn != nullptr)
		{
			return IManagedHandleToObject(FieldBridgeGetStaticValueFn(InManagedClass,
			                                                          reinterpret_cast<const uint8*>(StringCast<
				                                                          UTF8CHAR>(*InName).Get())));
		}
	}

	return nullptr;
}

void SCRIPT_DOMAIN_TYPE::SetPropertyValue(const IManagedHandle InManagedHandle, const FString& InName, void** InParams)
{
	if (TypeBridgeGetTypeFn != nullptr)
	{
		if (const auto Class = TypeBridgeGetTypeFn(InManagedHandle);
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
			}
		}
	}
}

FClassReflection* SCRIPT_DOMAIN_TYPE::MakeGenericType(const FClassReflection* InGeneric, const FClassReflection* InType)
{
	if (InGeneric != nullptr && InType != nullptr)
	{
		if (TypeBridgeGetClassFn != nullptr)
		{
			return FReflectionRegistry::Get().GetClass(
				TypeBridgeMakeGenericTypeFn(InGeneric->GetManagedClass(),
				                            InType->GetManagedClass()));
		}
	}

	return nullptr;
}

FClassReflection* SCRIPT_DOMAIN_TYPE::MakeGenericType(const FClassReflection* InGeneric,
                                                      const FClassReflection* InKeyType,
                                                      const FClassReflection* InValueType)
{
	if (InGeneric != nullptr && InKeyType != nullptr && InValueType != nullptr)
	{
		if (TypeBridgeMakeGenericType2Fn != nullptr)
		{
			return FReflectionRegistry::Get().GetClass(
				TypeBridgeMakeGenericType2Fn(
					InGeneric->GetManagedClass(),
					InKeyType->GetManagedClass(),
					InValueType->GetManagedClass()));
		}
	}

	return nullptr;
}

IManagedHandle SCRIPT_DOMAIN_TYPE::Invoke(const IManagedHandle InManagedHandle, const IManagedHandle InManagedMethod,
                                          const int32 InParamCount, void** InParams)
{
	if (IManagedHandleIsValid(InManagedMethod))
	{
		if (MethodBridgeInvokeFn != nullptr)
		{
			return MethodBridgeInvokeFn(
				InManagedHandle,
				InManagedMethod,
				InParamCount,
				reinterpret_cast<IManagedHandle*>(InParams));
		}
	}

	return InvalidManagedHandle;
}

void SCRIPT_DOMAIN_TYPE::GetClassReflection(const IManagedHandle InManagedClass, PTRINT* OutParams)
{
	if (UtilsGetClassReflectionFn != nullptr)
	{
		UtilsGetClassReflectionFn(InManagedClass, OutParams);
	}
}

bool SCRIPT_DOMAIN_TYPE::IsInitialized() const
{
	return bIsInitialized;
}

TArray<IManagedHandle> SCRIPT_DOMAIN_TYPE::GetAssemblies() const
{
	return Assemblies;
}

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
