#include "FGeneratorCore.h"
#include "FDelegateGenerator.h"
#include "FEnumGenerator.h"
#include "Misc/FileHelper.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"
#include "Dynamic/CSharpGeneratedClass.h"
#include "Dynamic/CSharpBlueprintGeneratedClass.h"
#include "Dynamic/CSharpScriptStruct.h"
#include "Dynamic/CSharpEnum.h"
#include "UEVersion.h"
#include "Setting/UnrealCSharpEditorSetting.h"

FString FGeneratorCore::GetPathNameAttribute(const UField* InField)
{
	if (InField == nullptr)
	{
		return TEXT("");
	}

	auto ModuleName = InField->GetOuter() ? InField->GetOuter()->GetName() : TEXT("");

	if (InField->IsNative() == false ||
		Cast<UCSharpGeneratedClass>(InField) ||
		Cast<UCSharpBlueprintGeneratedClass>(InField) ||
		Cast<UCSharpScriptStruct>(InField) ||
		Cast<UCSharpEnum>(InField))
	{
		auto Index = 0;

		if (ModuleName.FindLastChar(TEXT('/'), Index))
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
	if (Property == nullptr) return "";

	if (const auto ByteProperty = CastField<FByteProperty>(Property))
	{
		if (ByteProperty->Enum != nullptr)
		{
			FEnumGenerator::AddEnumUnderlyingType(ByteProperty->Enum, ByteProperty);

			return FUnrealCSharpFunctionLibrary::GetFullClass(ByteProperty->Enum);
		}

		return TEXT("Byte");
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

	if (const auto ClassProperty = CastField<FClassProperty>(Property))
	{
		return FString::Printf(TEXT(
			"TSubclassOf<%s>"
		),
		                       *FUnrealCSharpFunctionLibrary::GetFullClass(ClassProperty->MetaClass)
		);
	}

	if (const auto ObjectProperty = CastField<FObjectProperty>(Property))
	{
		return FUnrealCSharpFunctionLibrary::GetFullClass(ObjectProperty->PropertyClass);
	}

	if (CastField<FNameProperty>(Property)) return TEXT("FName");

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

	if (CastField<FStrProperty>(Property)) return TEXT("FString");

	if (CastField<FTextProperty>(Property)) return TEXT("FText");

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

	if (CastField<FDoubleProperty>(Property)) return TEXT("Double");

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

	return TEXT("");
}

TSet<FString> FGeneratorCore::GetPropertyTypeNameSpace(FProperty* Property)
{
	if (Property == nullptr) return {""};

	if (const auto ByteProperty = CastField<FByteProperty>(Property))
	{
		return {
			ByteProperty->Enum != nullptr
				? FUnrealCSharpFunctionLibrary::GetClassNameSpace(ByteProperty->Enum)
				: TEXT("System")
		};
	}

	if (CastField<FUInt16Property>(Property)) return {TEXT("System")};

	if (CastField<FUInt32Property>(Property)) return {TEXT("System")};

	if (CastField<FUInt64Property>(Property)) return {TEXT("System")};

	if (CastField<FInt8Property>(Property)) return {TEXT("System")};

	if (CastField<FInt16Property>(Property)) return {TEXT("System")};

	if (CastField<FIntProperty>(Property)) return {TEXT("System")};

	if (CastField<FInt64Property>(Property)) return {TEXT("System")};

	if (CastField<FBoolProperty>(Property)) return {TEXT("System")};

	if (CastField<FFloatProperty>(Property)) return {TEXT("System")};

	if (const auto ClassProperty = CastField<FClassProperty>(Property))
	{
		return {TEXT("Script.Common"), FUnrealCSharpFunctionLibrary::GetClassNameSpace(ClassProperty->MetaClass)};
	}

	if (const auto ObjectProperty = CastField<FObjectProperty>(Property))
	{
		return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(ObjectProperty->PropertyClass)};
	}

	if (CastField<FNameProperty>(Property)) return {TEXT("Script.Common")};

	if (const auto DelegateProperty = CastField<FDelegateProperty>(Property))
	{
		return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(DelegateProperty)};
	}

	if (const auto InterfaceProperty = CastField<FInterfaceProperty>(Property))
	{
		return {
			TEXT("Script.Common"), FUnrealCSharpFunctionLibrary::GetClassNameSpace(InterfaceProperty->InterfaceClass)
		};
	}

	if (const auto StructProperty = CastField<FStructProperty>(Property))
	{
		return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(StructProperty->Struct)};
	}

	if (const auto ArrayProperty = CastField<FArrayProperty>(Property))
	{
		return GetPropertyTypeNameSpace(ArrayProperty->Inner).Union({TEXT("Script.Common")});
	}

	if (const auto EnumProperty = CastField<FEnumProperty>(Property))
	{
		return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(EnumProperty->GetEnum()), TEXT("System")};
	}

	if (CastField<FStrProperty>(Property)) return {"Script.Common"};

	if (CastField<FTextProperty>(Property)) return {"Script.Common"};

	if (const auto MulticastDelegateProperty = CastField<FMulticastDelegateProperty>(Property))
	{
		return {FUnrealCSharpFunctionLibrary::GetClassNameSpace(MulticastDelegateProperty)};
	}

	if (const auto WeakObjectProperty = CastField<FWeakObjectProperty>(Property))
	{
		return {
			TEXT("Script.Common"), FUnrealCSharpFunctionLibrary::GetClassNameSpace(WeakObjectProperty->PropertyClass)
		};
	}

	if (const auto LazyObjectProperty = CastField<FLazyObjectProperty>(Property))
	{
		return {
			TEXT("Script.Common"), FUnrealCSharpFunctionLibrary::GetClassNameSpace(LazyObjectProperty->PropertyClass)
		};
	}

	if (const auto SoftClassProperty = CastField<FSoftClassProperty>(Property))
	{
		return {
			TEXT("Script.Common"), FUnrealCSharpFunctionLibrary::GetClassNameSpace(SoftClassProperty->MetaClass)
		};
	}

	if (const auto SoftObjectProperty = CastField<FSoftObjectProperty>(Property))
	{
		return {
			TEXT("Script.Common"), FUnrealCSharpFunctionLibrary::GetClassNameSpace(SoftObjectProperty->PropertyClass)
		};
	}

	if (CastField<FDoubleProperty>(Property)) return {TEXT("System")};

	if (const auto MapProperty = CastField<FMapProperty>(Property))
	{
		return GetPropertyTypeNameSpace(MapProperty->KeyProp).
		       Union(GetPropertyTypeNameSpace(MapProperty->ValueProp)).
		       Union({TEXT("Script.Common")});
	}

	if (const auto SetProperty = CastField<FSetProperty>(Property))
	{
		return GetPropertyTypeNameSpace(SetProperty->ElementProp).Union({TEXT("Script.Common")});
	}

	if (CastField<FFieldPathProperty>(Property)) return {TEXT("Script.Common"), TEXT("Script.Reflection.Property")};

	return {TEXT("")};
}

FString FGeneratorCore::GetGetAccessorType(FProperty* Property)
{
	if (CastField<FByteProperty>(Property))
	{
		return TEXT("Byte");
	}

	if (const auto EnumProperty = CastField<FEnumProperty>(Property))
	{
		return *GetPropertyType(EnumProperty->GetUnderlyingProperty());
	}

	return *GetPropertyType(Property);
}

FString FGeneratorCore::GetGetAccessorReturnParamName(FProperty* Property)
{
	if (const auto ByteProperty = CastField<FByteProperty>(Property))
	{
		if (ByteProperty->Enum != nullptr)
		{
			return FString::Printf(TEXT(
				"(%s) value"
			),
			                       *FUnrealCSharpFunctionLibrary::GetFullClass(ByteProperty->Enum));
		}
		else
		{
			return TEXT("value");
		}
	}

	if (const auto EnumProperty = CastField<FEnumProperty>(Property))
	{
		return FString::Printf(TEXT(
			"(%s) value"
		),
		                       *FUnrealCSharpFunctionLibrary::GetFullClass(EnumProperty->GetEnum()));
	}

	return TEXT("value");
}

FString FGeneratorCore::GetSetAccessorParamName(FProperty* Property)
{
	if (CastField<FByteProperty>(Property))
	{
		return TEXT("(Byte) value");
	}

	if (const auto EnumProperty = CastField<FEnumProperty>(Property))
	{
		return FString::Printf(TEXT(
			"(%s) value"
		),
		                       *GetPropertyType(EnumProperty->GetUnderlyingProperty()));
	}

	return TEXT("value");
}

bool FGeneratorCore::IsSafeProperty(FProperty* Property)
{
	if (CastField<FByteProperty>(Property) || CastField<FUInt16Property>(Property) ||
		CastField<FUInt32Property>(Property) || CastField<FUInt64Property>(Property) ||
		CastField<FInt8Property>(Property) || CastField<FInt16Property>(Property) ||
		CastField<FIntProperty>(Property) || CastField<FInt64Property>(Property) ||
		CastField<FBoolProperty>(Property) || CastField<FFloatProperty>(Property) ||
		CastField<FEnumProperty>(Property) || CastField<FDoubleProperty>(Property))
	{
		return false;
	}

	return true;
}

FString FGeneratorCore::GetOutParamString(FProperty* Property, const uint32 Index)
{
	if (Property == nullptr) return TEXT("");

	return FString::Printf(TEXT(
		"(%s) __OutValue[%d]"
	),
	                       *GetPropertyType(Property),
	                       Index);
}

FString FGeneratorCore::GetParamName(FProperty* Property)
{
	if (const auto ByteProperty = CastField<FByteProperty>(Property))
	{
		if (ByteProperty->Enum != nullptr)
		{
			return FString::Printf(TEXT(
				"(Byte) %s"
			),
			                       *GetName(ByteProperty->GetName()));
		}
	}

	if (const auto EnumProperty = CastField<FEnumProperty>(Property))
	{
		return FString::Printf(TEXT(
			"(%s) %s"
		),
		                       *GetPropertyType(EnumProperty->GetUnderlyingProperty()),
		                       *GetName(EnumProperty->GetName()));
	}

	return GetName(Property->GetName());
}

FString FGeneratorCore::GetReturnParamType(FProperty* Property)
{
	if (CastField<FByteProperty>(Property))
	{
		return TEXT("Byte");
	}

	if (const auto EnumProperty = CastField<FEnumProperty>(Property))
	{
		return GetPropertyType(EnumProperty->GetUnderlyingProperty());
	}

	return GetPropertyType(Property);
}

FString FGeneratorCore::GetReturnParamName(FProperty* Property)
{
	return FString::Printf(TEXT(
		"(%s) __ReturnValue"
	),
	                       *GetPropertyType(Property));
}

FString FGeneratorCore::GetName(FString InName)
{
	static TArray<FString, TInlineAllocator<77>> KeyWords{
		TEXT("abstract"), TEXT("as"),
		TEXT("base"), TEXT("bool"), TEXT("break"), TEXT("byte"),
		TEXT("case"), TEXT("catch"), TEXT("char"), TEXT("checked"), TEXT("class"), TEXT("const"), TEXT("continue"),
		TEXT("decimal"), TEXT("default"), TEXT("delegate"), TEXT("do"), TEXT("double"),
		TEXT("else"), TEXT("enum"), TEXT("event"), TEXT("explicit"), TEXT("extern"),
		TEXT("false"), TEXT("finally"), TEXT("fixed"), TEXT("float"), TEXT("for"), TEXT("foreach"),
		TEXT("goto"),
		TEXT("if"), TEXT("implicit"), TEXT("in"), TEXT("int"), TEXT("interface"), TEXT("internal"), TEXT("is"),
		TEXT("lock"), TEXT("long"),
		TEXT("namespace"), TEXT("new"), TEXT("null"),
		TEXT("object"), TEXT("operator"), TEXT("out"), TEXT("override"),
		TEXT("params"), TEXT("private"), TEXT("protected"), TEXT("public"),
		TEXT("readonly"), TEXT("ref"), TEXT("return"),
		TEXT("sbyte"), TEXT("sealed"), TEXT("short"), TEXT("sizeof"), TEXT("stackalloc"), TEXT("static"),
		TEXT("string"), TEXT("struct"), TEXT("switch"),
		TEXT("this"), TEXT("throw"), TEXT("true"), TEXT("try"), TEXT("typeof"),
		TEXT("uint"), TEXT("ulong"), TEXT("unchecked"), TEXT("unsafe"), TEXT("ushort"), TEXT("using"),
		TEXT("virtual"), TEXT("void"), TEXT("volatile"),
		TEXT("while")
	};

	if (KeyWords.ContainsByPredicate([&](const FString& Name)
	{
		return InName.Equals(Name);
	}))
	{
		return FString::Printf(TEXT("@%s"), *InName);
	}

	for (auto& Char : InName)
	{
		if (!(Char >= '0' && Char <= '9' || Char >= 'a' && Char <= 'z' || Char >= 'A' && Char <= 'Z'))
		{
			Char = '_';
		}
	}

	if (InName.Len() > 0)
	{
		if (InName[0] >= '0' && InName[0] <= '9')
		{
			InName = FString::Printf(TEXT(
				"_%s"
			),
			                         *InName
			);
		}
	}

	return InName;
}

bool FGeneratorCore::SaveStringToFile(const FString& FileName, const FString& String)
{
	auto& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	const auto DirectoryName = FPaths::GetPath(FileName);

	if (!PlatformFile.DirectoryExists(*DirectoryName))
	{
		PlatformFile.CreateDirectoryTree(*DirectoryName);
	}

	const auto FileManager = &IFileManager::Get();

	return FFileHelper::SaveStringToFile(String, *FileName, FFileHelper::EEncodingOptions::ForceUTF8, FileManager,
	                                     FILEWRITE_None);
}

FString FGeneratorCore::GetPluginConfig()
{
	return FPaths::ConvertRelativePathToFull(FPaths::Combine(
		FPaths::ProjectPluginsDir(), PLUGIN_NAME, CONFIG, FString::Printf(TEXT(
			"%s%s"
		),
		                                                                  *PLUGIN_NAME,
		                                                                  *INI_SUFFIX
		)));
}

FString FGeneratorCore::GetProjectConfig()
{
	return FPaths::ConvertRelativePathToFull(FPaths::Combine(
		FPaths::ProjectConfigDir(), FString::Printf(TEXT(
			"%s%s"
		),
		                                            *PLUGIN_NAME,
		                                            *INI_SUFFIX
		)));
}

bool FGeneratorCore::IsSupportedModule(const FString& InModule)
{
	static TArray<FString> Modules;

#if UE_ARRAY_IS_EMPTY
	if (Modules.IsEmpty())
#else
	if (Modules.Num() == 0)
#endif
	{
		TArray<FString> OutArray;

		GConfig->GetArray(TEXT("Generator"), TEXT("SupportedModules"), OutArray, GetPluginConfig());

		if (const auto UnrealCSharpEditorSetting = GetMutableDefault<UUnrealCSharpEditorSetting>())
		{
			OutArray.Append(UnrealCSharpEditorSetting->GetGeneratorModules());
		}

		for (const auto& Module : OutArray)
		{
			Modules.Add(FString::Printf(TEXT(
				"%s.%s"),
			                            *SCRIPT,
			                            *Module
			));
		}

		GConfig->GetArray(TEXT("Generator"), TEXT("SupportedModules"), OutArray, GetProjectConfig());

		for (const auto& Module : OutArray)
		{
			Modules.Add(FString::Printf(TEXT(
				"%s.%s"),
			                            *SCRIPT,
			                            *Module
			));
		}

		Modules.Add(FString::Printf(TEXT(
			"%s.%s"),
		                            *SCRIPT,
		                            FApp::GetProjectName()
		));
	}

	static auto GameRoot = FString::Printf(TEXT(
		"%s.Game"
	),
	                                       *SCRIPT
	);

	static auto Game = FString::Printf(TEXT(
		"%s.Game."
	),
	                                   *SCRIPT
	);

	if (InModule == GameRoot || InModule.StartsWith(Game))
	{
		return true;
	}

	return Modules.Contains(InModule);
}

TArray<FName> FGeneratorCore::GetAssetsPaths()
{
	TArray<FName> AssetsPaths;

	TArray<FString> OutArray;

	GConfig->GetArray(TEXT("Generator"), TEXT("AssetsPaths"), OutArray, GetPluginConfig());

	AssetsPaths.Append(OutArray);

	GConfig->GetArray(TEXT("Generator"), TEXT("AssetsPaths"), OutArray, GetProjectConfig());

	AssetsPaths.Append(OutArray);

	return AssetsPaths;
}
