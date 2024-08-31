#include "FGeneratorCore.h"
#include "FDelegateGenerator.h"
#include "FEnumGenerator.h"
#include "Binding/TypeInfo/TName.inl"
#include "Binding/TypeInfo/TNameSpace.inl"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/PropertyMacro.h"
#include "Setting/UnrealCSharpEditorSetting.h"
#include "UEVersion.h"
#if UE_F_OPTIONAL_PROPERTY
#include "UObject/PropertyOptional.h"
#endif

TMap<FString, TArray<FString>> FGeneratorCore::OverrideFunctionsMap;

bool FGeneratorCore::bIsSkipGenerateEngineModules;

bool FGeneratorCore::bIsGenerateAllModules;

TArray<FString> FGeneratorCore::SupportedModule;

TArray<FName> FGeneratorCore::SupportedAssetPath;

TArray<FString> FGeneratorCore::SupportedAssetPathNameSpace;

TMap<TWeakObjectPtr<const UObject>, bool> FGeneratorCore::SupportedMap;

TArray<FName> FGeneratorCore::SupportedAssetClassName;

FString FGeneratorCore::GetPathNameAttribute(const UField* InField)
{
	if (InField == nullptr)
	{
		return TEXT("");
	}

	auto ModuleName = InField->GetOuter() ? InField->GetOuter()->GetName() : TEXT("");

	if (!InField->IsNative())
	{
		if (auto Index = 0; ModuleName.FindLastChar(TEXT('/'), Index))
		{
			ModuleName = ModuleName.Left(Index);
		}
	}

	auto Name = InField->GetName();

	if (Name.EndsWith("_C"))
	{
		Name = Name.LeftChop(2);
	}

	const auto PathName = FString::Printf(TEXT(
		"%s%s"
	),
	                                      *Name,
	                                      InField->IsNative()
		                                      ? TEXT("")
		                                      : *FString::Printf(TEXT(
			                                      ".%s"
		                                      ),
		                                                         *InField->GetName()));

	return FString::Printf(TEXT(
		"%s%s%s"
	),
	                       *ModuleName,
	                       *FString(InField->IsNative() ? TEXT(".") : TEXT("/")),
	                       *PathName);
}

FString FGeneratorCore::GetPropertyType(FProperty* Property)
{
	if (Property == nullptr) return TEXT("");

	if (const auto ByteProperty = CastField<FByteProperty>(Property))
	{
		if (ByteProperty->Enum != nullptr)
		{
			FEnumGenerator::AddEnumUnderlyingType(ByteProperty->Enum, ByteProperty);

			return FUnrealCSharpFunctionLibrary::GetFullClass(ByteProperty->Enum);
		}

		return TName<uint8, uint8>::Get();
	}

	if (CastField<FUInt16Property>(Property)) return TName<uint16, uint16>::Get();

	if (CastField<FUInt32Property>(Property)) return TName<uint32, uint32>::Get();

	if (CastField<FUInt64Property>(Property)) return TName<uint64, uint64>::Get();

	if (CastField<FInt8Property>(Property)) return TName<int8, int8>::Get();

	if (CastField<FInt16Property>(Property)) return TName<int16, int16>::Get();

	if (CastField<FIntProperty>(Property)) return TName<int32, int32>::Get();

	if (CastField<FInt64Property>(Property)) return TName<int64, int64>::Get();

	if (CastField<FBoolProperty>(Property)) return TName<bool, bool>::Get();

	if (CastField<FFloatProperty>(Property)) return TName<float, float>::Get();

	if (const auto ClassProperty = CastField<FClassProperty>(Property))
	{
		if (ClassProperty->HasAnyPropertyFlags(CPF_UObjectWrapper))
		{
			return FString::Printf(TEXT(
				"TSubclassOf<%s>"
			),
			                       *FUnrealCSharpFunctionLibrary::GetFullClass(ClassProperty->MetaClass)
			);
		}
		else
		{
			return TName<UClass*, UClass*>::Get();
		}
	}

	if (const auto ObjectProperty = CastField<FObjectProperty>(Property))
	{
		return FUnrealCSharpFunctionLibrary::GetFullClass(ObjectProperty->PropertyClass);
	}

	if (CastField<FNameProperty>(Property)) return TName<FName, FName>::Get();

	if (const auto DelegateProperty = CastField<FDelegateProperty>(Property))
	{
		return FUnrealCSharpFunctionLibrary::GetFullClass(DelegateProperty);
	}

	if (const auto InterfaceProperty = CastField<FInterfaceProperty>(Property))
	{
		return FString::Printf(TEXT(
			"TScriptInterface<%s>"
		),
		                       *FUnrealCSharpFunctionLibrary::GetFullInterface(InterfaceProperty->InterfaceClass)
		);
	}

	if (const auto StructProperty = CastField<FStructProperty>(Property))
	{
		return FUnrealCSharpFunctionLibrary::GetFullClass(StructProperty->Struct);
	}

	if (const auto ArrayProperty = CastField<FArrayProperty>(Property))
	{
		FDelegateGenerator::Generator(ArrayProperty->Inner);

		return FString::Printf(TEXT(
			"TArray<%s>"
		),
		                       *GetPropertyType(ArrayProperty->Inner)
		);
	}

	if (const auto EnumProperty = CastField<FEnumProperty>(Property))
	{
		FEnumGenerator::AddEnumUnderlyingType(EnumProperty->GetEnum(), EnumProperty->GetUnderlyingProperty());

		return FUnrealCSharpFunctionLibrary::GetFullClass(EnumProperty->GetEnum());
	}

	if (CastField<FStrProperty>(Property)) return TName<FString, FString>::Get();

	if (CastField<FTextProperty>(Property)) return TName<FText, FText>::Get();

	if (const auto MulticastDelegateProperty = CastField<FMulticastDelegateProperty>(Property))
	{
		return FUnrealCSharpFunctionLibrary::GetFullClass(MulticastDelegateProperty);
	}

	if (const auto WeakObjectProperty = CastField<FWeakObjectProperty>(Property))
	{
		return FString::Printf(TEXT(
			"TWeakObjectPtr<%s>"
		),
		                       *FUnrealCSharpFunctionLibrary::GetFullClass(WeakObjectProperty->PropertyClass)
		);
	}

	if (const auto LazyObjectProperty = CastField<FLazyObjectProperty>(Property))
	{
		return FString::Printf(TEXT(
			"TLazyObjectPtr<%s>"
		),
		                       *FUnrealCSharpFunctionLibrary::GetFullClass(LazyObjectProperty->PropertyClass)
		);
	}

	if (const auto SoftClassProperty = CastField<FSoftClassProperty>(Property))
	{
		return FString::Printf(TEXT(
			"TSoftClassPtr<%s>"
		),
		                       *FUnrealCSharpFunctionLibrary::GetFullClass(SoftClassProperty->MetaClass)
		);
	}

	if (const auto SoftObjectProperty = CastField<FSoftObjectProperty>(Property))
	{
		return FString::Printf(TEXT(
			"TSoftObjectPtr<%s>"
		),
		                       *FUnrealCSharpFunctionLibrary::GetFullClass(SoftObjectProperty->PropertyClass)
		);
	}

	if (CastField<FDoubleProperty>(Property)) return TName<double, double>::Get();

	if (const auto MapProperty = CastField<FMapProperty>(Property))
	{
		FDelegateGenerator::Generator(MapProperty->KeyProp);

		FDelegateGenerator::Generator(MapProperty->ValueProp);

		return FString::Printf(TEXT(
			"TMap<%s, %s>"
		),
		                       *GetPropertyType(MapProperty->KeyProp),
		                       *GetPropertyType(MapProperty->ValueProp)
		);
	}

	if (const auto SetProperty = CastField<FSetProperty>(Property))
	{
		FDelegateGenerator::Generator(SetProperty->ElementProp);

		return FString::Printf(TEXT(
			"TSet<%s>"
		),
		                       *GetPropertyType(SetProperty->ElementProp)
		);
	}

	if (const auto FieldPathProperty = CastField<FFieldPathProperty>(Property))
	{
		return FString::Printf(TEXT(
			"TFieldPath<F%s>"
		),
		                       *FieldPathProperty->PropertyClass->GetName()
		);
	}

#if UE_F_OPTIONAL_PROPERTY
	if (const auto OptionalProperty = CastField<FOptionalProperty>(Property))
	{
		return FString::Printf(TEXT(
			"TOptional<%s>"
		),
		                       *GetPropertyType(OptionalProperty->GetValueProperty())
		);
	}
#endif

	return TEXT("");
}

TSet<FString> FGeneratorCore::GetPropertyTypeNameSpace(FProperty* Property)
{
	if (Property == nullptr) return {TEXT("")};

	if (const auto ByteProperty = CastField<FByteProperty>(Property))
	{
		return ByteProperty->Enum != nullptr
			       ? TSet<FString>{FUnrealCSharpFunctionLibrary::GetClassNameSpace(ByteProperty->Enum)}
			       : TSet<FString>{TNameSpace<uint8, uint8>::Get()};
	}

	if (CastField<FUInt16Property>(Property)) return TSet<FString>{TNameSpace<uint16, uint16>::Get()};

	if (CastField<FUInt32Property>(Property)) return TSet<FString>{TNameSpace<uint32, uint32>::Get()};

	if (CastField<FUInt64Property>(Property)) return TSet<FString>{TNameSpace<uint64, uint64>::Get()};

	if (CastField<FInt8Property>(Property)) return TSet<FString>{TNameSpace<int8, int8>::Get()};

	if (CastField<FInt16Property>(Property)) return TSet<FString>{TNameSpace<int16, int16>::Get()};

	if (CastField<FIntProperty>(Property)) return TSet<FString>{TNameSpace<int32, int32>::Get()};

	if (CastField<FInt64Property>(Property)) return TSet<FString>{TNameSpace<int64, int64>::Get()};

	if (CastField<FBoolProperty>(Property)) return TSet<FString>{TNameSpace<bool, bool>::Get()};

	if (CastField<FFloatProperty>(Property)) return TSet<FString>{TNameSpace<float, float>::Get()};

	if (const auto ClassProperty = CastField<FClassProperty>(Property))
	{
		return {
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT),
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(ClassProperty->MetaClass)
		};
	}

	if (const auto ObjectProperty = CastField<FObjectProperty>(Property))
	{
		return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(ObjectProperty->PropertyClass)};
	}

	if (CastField<FNameProperty>(Property)) return TSet<FString>{TNameSpace<FName, FName>::Get()};

	if (const auto DelegateProperty = CastField<FDelegateProperty>(Property))
	{
		return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(DelegateProperty)};
	}

	if (const auto InterfaceProperty = CastField<FInterfaceProperty>(Property))
	{
		return {
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT),
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(InterfaceProperty->InterfaceClass)
		};
	}

	if (const auto StructProperty = CastField<FStructProperty>(Property))
	{
		return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(StructProperty->Struct)};
	}

	if (const auto ArrayProperty = CastField<FArrayProperty>(Property))
	{
		return GetPropertyTypeNameSpace(ArrayProperty->Inner).Union({
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT)
		});
	}

	if (const auto EnumProperty = CastField<FEnumProperty>(Property))
	{
		return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(EnumProperty->GetEnum())};
	}

	if (CastField<FStrProperty>(Property)) return TSet<FString>{TNameSpace<FString, FString>::Get()};

	if (CastField<FTextProperty>(Property)) return TSet<FString>{TNameSpace<FText, FText>::Get()};

	if (const auto MulticastDelegateProperty = CastField<FMulticastDelegateProperty>(Property))
	{
		return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(MulticastDelegateProperty)};
	}

	if (const auto WeakObjectProperty = CastField<FWeakObjectProperty>(Property))
	{
		return {
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT),
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(WeakObjectProperty->PropertyClass)
		};
	}

	if (const auto LazyObjectProperty = CastField<FLazyObjectProperty>(Property))
	{
		return {
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT),
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(LazyObjectProperty->PropertyClass)
		};
	}

	if (const auto SoftClassProperty = CastField<FSoftClassProperty>(Property))
	{
		return {
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT),
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(SoftClassProperty->MetaClass)
		};
	}

	if (const auto SoftObjectProperty = CastField<FSoftObjectProperty>(Property))
	{
		return {
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT),
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(SoftObjectProperty->PropertyClass)
		};
	}

	if (CastField<FDoubleProperty>(Property)) return TSet<FString>{TNameSpace<double, double>::Get()};

	if (const auto MapProperty = CastField<FMapProperty>(Property))
	{
		return GetPropertyTypeNameSpace(MapProperty->KeyProp).
		       Union(GetPropertyTypeNameSpace(MapProperty->ValueProp)).
		       Union({COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT)});
	}

	if (const auto SetProperty = CastField<FSetProperty>(Property))
	{
		return GetPropertyTypeNameSpace(SetProperty->ElementProp).Union({
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT)
		});
	}

	if (CastField<FFieldPathProperty>(Property))
	{
		return {
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT),
			COMBINE_NAMESPACE(COMBINE_NAMESPACE(NAMESPACE_ROOT, FString(TEXT("Reflection"))), FString(TEXT("Property")))
		};
	}

#if UE_F_OPTIONAL_PROPERTY
	if (const auto OptionalProperty = CastField<FOptionalProperty>(Property))
	{
		return GetPropertyTypeNameSpace(OptionalProperty->GetValueProperty()).Union({
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT)
		});
	}
#endif

	return {TEXT("")};
}

FString FGeneratorCore::GetBufferCast(FProperty* Property)
{
	if (const auto EnumProperty = CastField<FEnumProperty>(Property))
	{
		return GetBufferCast(EnumProperty->GetUnderlyingProperty());
	}

	if (CastField<FByteProperty>(Property)) return TEXT("byte");

	if (CastField<FUInt16Property>(Property)) return TEXT("ushort");

	if (CastField<FUInt32Property>(Property)) return TEXT("uint");

	if (CastField<FUInt64Property>(Property)) return TEXT("ulong");

	if (CastField<FInt8Property>(Property)) return TEXT("sbyte");

	if (CastField<FInt16Property>(Property)) return TEXT("short");

	if (CastField<FIntProperty>(Property)) return TEXT("int");

	if (CastField<FInt64Property>(Property)) return TEXT("long");

	if (CastField<FBoolProperty>(Property)) return TEXT("bool");

	if (CastField<FFloatProperty>(Property)) return TEXT("float");

	if (CastField<FDoubleProperty>(Property)) return TEXT("double");

	return TEXT("nint");
}

int32 FGeneratorCore::GetBufferSize(FProperty* Property)
{
	return IsPrimitiveProperty(Property) ? Property->ElementSize : sizeof(void*);
}

FString FGeneratorCore::GetTypeImplementation(FProperty* Property)
{
	if (CastField<FByteProperty>(Property))
	{
		return TEXT("Byte");
	}

	if (const auto EnumProperty = CastField<FEnumProperty>(Property))
	{
		return GetTypeImplementation(EnumProperty->GetUnderlyingProperty());
	}

	if (CastField<FUInt16Property>(Property)) return TEXT("UInt16");

	if (CastField<FUInt32Property>(Property)) return TEXT("UInt32");

	if (CastField<FUInt64Property>(Property)) return TEXT("UInt64");

	if (CastField<FInt8Property>(Property)) return TEXT("SByte");

	if (CastField<FInt16Property>(Property)) return TEXT("Int16");

	if (CastField<FIntProperty>(Property)) return TEXT("Int32");

	if (CastField<FInt64Property>(Property)) return TEXT("Int64");

	if (CastField<FBoolProperty>(Property)) return TEXT("Boolean");

	if (CastField<FFloatProperty>(Property)) return TEXT("Single");

	if (CastField<FDoubleProperty>(Property)) return TEXT("Double");

	return TEXT("");
}

FString FGeneratorCore::GetGetAccessorReturnParamName(FProperty* Property)
{
	if (const auto ByteProperty = CastField<FByteProperty>(Property))
	{
		if (ByteProperty->Enum != nullptr)
		{
			return FString::Printf(TEXT(
				"(%s)"
			),
			                       *FUnrealCSharpFunctionLibrary::GetFullClass(ByteProperty->Enum));
		}
		else
		{
			return TEXT("");
		}
	}

	if (const auto EnumProperty = CastField<FEnumProperty>(Property))
	{
		return FString::Printf(TEXT(
			"(%s)"
		),
		                       *FUnrealCSharpFunctionLibrary::GetFullClass(EnumProperty->GetEnum()));
	}

	return TEXT("");
}

FString FGeneratorCore::GetSetAccessorParamName(FProperty* Property)
{
	if (CastField<FByteProperty>(Property))
	{
		return FString::Printf(TEXT(
			"(%s)value"
		),
		                       *TName<uint8, uint8>::Get()
		);
	}

	if (const auto EnumProperty = CastField<FEnumProperty>(Property))
	{
		return FString::Printf(TEXT(
			"(%s)value"
		),
		                       *GetPropertyType(EnumProperty->GetUnderlyingProperty()));
	}

	if (IsPrimitiveProperty(Property))
	{
		return TEXT("value");
	}
	else
	{
		return FString::Printf(TEXT(
			"value.%s"),
		                       *PROPERTY_GARBAGE_COLLECTION_HANDLE
		);
	}
}

bool FGeneratorCore::IsPrimitiveProperty(FProperty* Property)
{
	if (CastField<FByteProperty>(Property) || CastField<FUInt16Property>(Property) ||
		CastField<FUInt32Property>(Property) || CastField<FUInt64Property>(Property) ||
		CastField<FInt8Property>(Property) || CastField<FInt16Property>(Property) ||
		CastField<FIntProperty>(Property) || CastField<FInt64Property>(Property) ||
		CastField<FBoolProperty>(Property) || CastField<FFloatProperty>(Property) ||
		CastField<FEnumProperty>(Property) || CastField<FDoubleProperty>(Property))
	{
		return true;
	}

	return false;
}

FString FGeneratorCore::GetParamName(FProperty* Property)
{
	if (const auto ByteProperty = CastField<FByteProperty>(Property))
	{
		if (ByteProperty->Enum != nullptr)
		{
			return FString::Printf(TEXT(
				"(%s)%s"
			),
			                       *TName<uint8, uint8>::Get(),
			                       *FUnrealCSharpFunctionLibrary::Encode(ByteProperty));
		}
	}

	if (const auto EnumProperty = CastField<FEnumProperty>(Property))
	{
		return FString::Printf(TEXT(
			"(%s)%s"
		),
		                       *GetPropertyType(EnumProperty->GetUnderlyingProperty()),
		                       *FUnrealCSharpFunctionLibrary::Encode(EnumProperty));
	}

	if (IsPrimitiveProperty(Property))
	{
		return FUnrealCSharpFunctionLibrary::Encode(Property);
	}
	else
	{
		return FString::Printf(TEXT(
			"%s?.%s ?? nint.Zero"),
		                       *FUnrealCSharpFunctionLibrary::Encode(Property),
		                       *PROPERTY_GARBAGE_COLLECTION_HANDLE
		);
	}
}

FString FGeneratorCore::GetFunctionPrefix(FProperty* Property)
{
	return Property != nullptr
		       ? IsPrimitiveProperty(Property)
			         ? TEXT("Primitive")
			         : TEXT("Compound")
		       : TEXT("Generic");
}

int32 FGeneratorCore::GetFunctionIndex(const bool bHasReturn, const bool bHasInput, const bool bHasOutput,
                                       const bool bIsNative, const bool bIsNet)
{
	return static_cast<int32>(bHasReturn) |
		static_cast<int32>(bHasInput) << 1 |
		static_cast<int32>(bHasOutput) << 2 |
		static_cast<int32>(bIsNative) << 3 |
		static_cast<int32>(bIsNet) << 4;
}

FString FGeneratorCore::GetModuleRelativePath(const UField* InField)
{
	return InField != nullptr
		       ? GetModuleRelativePath(InField->GetMetaData(TEXT("ModuleRelativePath")))
		       : FString();
}

FString FGeneratorCore::GetModuleRelativePath(const UEnum* InEnum)
{
	return InEnum != nullptr
		       ? GetModuleRelativePath(InEnum->GetMetaData(TEXT("ModuleRelativePath")))
		       : FString();
}

FString FGeneratorCore::GetModuleRelativePath(const FDelegateProperty* InDelegateProperty)
{
	return InDelegateProperty != nullptr
		       ? GetModuleRelativePath(InDelegateProperty->GetMetaData(TEXT("ModuleRelativePath")))
		       : FString();
}

FString FGeneratorCore::GetModuleRelativePath(const FMulticastDelegateProperty* InMulticastDelegateProperty)
{
	return InMulticastDelegateProperty != nullptr
		       ? GetModuleRelativePath(InMulticastDelegateProperty->GetMetaData(TEXT("ModuleRelativePath")))
		       : FString();
}

FString FGeneratorCore::GetModuleRelativePath(const FString& InModuleRelativePath)
{
	return InModuleRelativePath.Replace(TEXT("Public/"), TEXT("")).Replace(TEXT("Private/"), TEXT(""));
}

TArray<FString> FGeneratorCore::GetOverrideFunctions(const FString& InNameSpace, const FString& InClass)
{
	const auto FoundFunctions = OverrideFunctionsMap.Find(FString::Printf(TEXT(
		"%s.%s"
	),
	                                                                      *InNameSpace,
	                                                                      *InClass
	));

	return FoundFunctions != nullptr ? *FoundFunctions : TArray<FString>{};
}

bool FGeneratorCore::IsSkip(const UField* InField)
{
	return bIsSkipGenerateEngineModules && !FUnrealCSharpFunctionLibrary::IsGameField(InField);
}

bool FGeneratorCore::IsSupported(FProperty* Property)
{
	if (Property == nullptr) return false;

	if (bIsGenerateAllModules && Property->IsNative()) return true;

	if (const auto ByteProperty = CastField<FByteProperty>(Property))
	{
		return ByteProperty->Enum != nullptr ? IsSupported(ByteProperty->Enum) : true;
	}

	if (CastField<FUInt16Property>(Property)) return true;

	if (CastField<FUInt32Property>(Property)) return true;

	if (CastField<FUInt64Property>(Property)) return true;

	if (CastField<FInt8Property>(Property)) return true;

	if (CastField<FInt16Property>(Property)) return true;

	if (CastField<FIntProperty>(Property)) return true;

	if (CastField<FInt64Property>(Property)) return true;

	if (CastField<FBoolProperty>(Property)) return true;

	if (CastField<FFloatProperty>(Property)) return true;

	if (const auto ClassProperty = CastField<FClassProperty>(Property))
	{
		return IsSupported(ClassProperty->MetaClass);
	}

	if (const auto ObjectProperty = CastField<FObjectProperty>(Property))
	{
		return IsSupported(ObjectProperty->PropertyClass);
	}

	if (CastField<FNameProperty>(Property)) return true;

	if (const auto DelegateProperty = CastField<FDelegateProperty>(Property))
	{
		return IsSupported(DelegateProperty->SignatureFunction);
	}

	if (const auto InterfaceProperty = CastField<FInterfaceProperty>(Property))
	{
		return IsSupported(InterfaceProperty->InterfaceClass);
	}

	if (const auto StructProperty = CastField<FStructProperty>(Property))
	{
		return IsSupported(StructProperty->Struct);
	}

	if (const auto ArrayProperty = CastField<FArrayProperty>(Property))
	{
		return IsSupported(ArrayProperty->Inner);
	}

	if (const auto EnumProperty = CastField<FEnumProperty>(Property))
	{
		return IsSupported(EnumProperty->GetEnum());
	}

	if (CastField<FStrProperty>(Property)) return true;

	if (CastField<FTextProperty>(Property)) return true;

	if (const auto MulticastDelegateProperty = CastField<FMulticastDelegateProperty>(Property))
	{
		return IsSupported(MulticastDelegateProperty->SignatureFunction);
	}

	if (const auto WeakObjectProperty = CastField<FWeakObjectProperty>(Property))
	{
		return IsSupported(WeakObjectProperty->PropertyClass);
	}

	if (const auto LazyObjectProperty = CastField<FLazyObjectProperty>(Property))
	{
		return IsSupported(LazyObjectProperty->PropertyClass);
	}

	if (const auto SoftClassProperty = CastField<FSoftClassProperty>(Property))
	{
		return IsSupported(SoftClassProperty->MetaClass);
	}

	if (const auto SoftObjectProperty = CastField<FSoftObjectProperty>(Property))
	{
		return IsSupported(SoftObjectProperty->PropertyClass);
	}

	if (CastField<FDoubleProperty>(Property)) return true;

	if (const auto MapProperty = CastField<FMapProperty>(Property))
	{
		return IsSupported(MapProperty->KeyProp) && IsSupported(MapProperty->ValueProp);
	}

	if (const auto SetProperty = CastField<FSetProperty>(Property))
	{
		return IsSupported(SetProperty->ElementProp);
	}

	if (CastField<FFieldPathProperty>(Property)) return false;

	return false;
}

bool FGeneratorCore::IsSupported(const UClass* InClass)
{
	if (bIsGenerateAllModules && InClass->IsNative()) return true;

	if (const auto FoundSupported = SupportedMap.Find(InClass))
	{
		return *FoundSupported;
	}

	if (!IsSupportedModule(FUnrealCSharpFunctionLibrary::GetClassNameSpace(InClass)))
	{
		SupportedMap.Add(InClass, false);

		return false;
	}

	if (const auto SuperClass = InClass->GetSuperClass())
	{
		if (!IsSupported(SuperClass))
		{
			SupportedMap.Add(InClass, false);

			return false;
		}
	}

	for (const auto Interface : InClass->Interfaces)
	{
		if (!IsSupported(Interface.Class))
		{
			SupportedMap.Add(InClass, false);

			return false;
		}
	}

	SupportedMap.Add(InClass, true);

	return true;
}

bool FGeneratorCore::IsSupported(const UFunction* InFunction)
{
	if (bIsGenerateAllModules && InFunction->IsNative()) return true;

	if (const auto FoundSupported = SupportedMap.Find(InFunction))
	{
		return *FoundSupported;
	}

	for (TFieldIterator<FProperty> ParamIterator(InFunction); ParamIterator && (ParamIterator->PropertyFlags
		     & CPF_Parm); ++ParamIterator)
	{
		if (!IsSupported(*ParamIterator))
		{
			SupportedMap.Add(InFunction, false);

			return false;
		}
	}

	SupportedMap.Add(InFunction, true);

	return true;
}

bool FGeneratorCore::IsSupported(const UStruct* InStruct)
{
	if (bIsGenerateAllModules && InStruct->IsNative()) return true;

	if (const auto FoundSupported = SupportedMap.Find(InStruct))
	{
		return *FoundSupported;
	}

	if (!IsSupportedModule(FUnrealCSharpFunctionLibrary::GetClassNameSpace(InStruct)))
	{
		SupportedMap.Add(InStruct, false);

		return false;
	}

	if (const auto SuperStruct = InStruct->GetSuperStruct())
	{
		if (!IsSupported(SuperStruct))
		{
			SupportedMap.Add(InStruct, false);

			return false;
		}
	}

	SupportedMap.Add(InStruct, true);

	return true;
}

bool FGeneratorCore::IsSupported(const UEnum* InEnum)
{
	if (bIsGenerateAllModules && InEnum->IsNative()) return true;

	if (const auto FoundSupported = SupportedMap.Find(InEnum))
	{
		return *FoundSupported;
	}

	if (!IsSupportedModule(FUnrealCSharpFunctionLibrary::GetClassNameSpace(InEnum)))
	{
		SupportedMap.Add(InEnum, false);

		return false;
	}

	SupportedMap.Add(InEnum, true);

	return true;
}

bool FGeneratorCore::IsSupportedModule(const FString& InModule)
{
	for (auto Index = 0; Index < SupportedAssetPathNameSpace.Num(); Index += 2)
	{
		if (InModule == SupportedAssetPathNameSpace[Index] ||
			InModule.StartsWith(SupportedAssetPathNameSpace[Index + 1]))
		{
			return true;
		}
	}

	return SupportedModule.Contains(InModule);
}

const TArray<FName>& FGeneratorCore::GetSupportedAssetPath()
{
	return SupportedAssetPath;
}

const TArray<FName>& FGeneratorCore::GetSupportedAssetClassName()
{
	return SupportedAssetClassName;
}

void FGeneratorCore::BeginGenerator()
{
	if (const auto UnrealCSharpEditorSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
		UUnrealCSharpEditorSetting>())
	{
		bIsSkipGenerateEngineModules = UnrealCSharpEditorSetting->IsSkipGenerateEngineModules();

		bIsGenerateAllModules = UnrealCSharpEditorSetting->IsGenerateAllModules();

		for (const auto& Module : UnrealCSharpEditorSetting->GetSupportedModule())
		{
			SupportedModule.Add(FString::Printf(TEXT(
				"%s.%s"),
			                                    *NAMESPACE_ROOT,
			                                    *Module
			));
		}

		for (auto AssetPath : UnrealCSharpEditorSetting->GetSupportedAssetPath())
		{
			AssetPath = AssetPath == FApp::GetProjectName() ? TEXT("Game") : AssetPath;

			SupportedAssetPath.Add(*FString::Printf(TEXT(
				"/%s"),
			                                        *AssetPath
			));

			SupportedAssetPathNameSpace.Append({
				FString::Printf(TEXT(
					"%s.%s"
				),
				                *NAMESPACE_ROOT,
				                *AssetPath

				),
				FString::Printf(TEXT(
					"%s.%s."
				),
				                *NAMESPACE_ROOT,
				                *AssetPath
				)
			});
		}

		for (const auto& AssetClass : UnrealCSharpEditorSetting->GetSupportedAssetClass())
		{
			SupportedAssetClassName.Add(AssetClass->GetFName());
		}
	}

	OverrideFunctionsMap = FUnrealCSharpFunctionLibrary::LoadFileToArray(FString::Printf(TEXT(
		"%s/%s.json"
	),
		*FUnrealCSharpFunctionLibrary::GetCodeAnalysisPath(),
		*OVERRIDE_FUNCTION
	));
}

void FGeneratorCore::EndGenerator()
{
	bIsSkipGenerateEngineModules = false;

	bIsGenerateAllModules = false;

	SupportedModule.Empty();

	SupportedAssetPath.Empty();

	SupportedAssetPathNameSpace.Empty();

	SupportedMap.Empty();

	SupportedAssetClassName.Empty();

	FDelegateGenerator::Delegate.Empty();

	FEnumGenerator::EnumUnderlyingType.Empty();
}
