﻿#include "FGeneratorCore.h"
#include "FDelegateGenerator.h"
#include "FEnumGenerator.h"
#include "Misc/FileHelper.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"
#include "Dynamic/CSharpClass.h"
#include "Dynamic/CSharpBlueprintGeneratedClass.h"
#include "Dynamic/CSharpScriptStruct.h"
#include "Dynamic/CSharpEnum.h"
#include "Setting/UnrealCSharpEditorSetting.h"

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

	if (InField->IsNative() == false ||
		Cast<UCSharpClass>(InField) ||
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
			                       *FUnrealCSharpFunctionLibrary::Encode(ByteProperty->GetName()));
		}
	}

	if (const auto EnumProperty = CastField<FEnumProperty>(Property))
	{
		return FString::Printf(TEXT(
			"(%s) %s"
		),
		                       *GetPropertyType(EnumProperty->GetUnderlyingProperty()),
		                       *FUnrealCSharpFunctionLibrary::Encode(EnumProperty->GetName()));
	}

	return FUnrealCSharpFunctionLibrary::Encode(Property->GetName());
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

bool FGeneratorCore::IsSupported(FProperty* Property)
{
	if (Property == nullptr) return false;

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
	if (const auto UnrealCSharpEditorSetting = GetMutableDefault<UUnrealCSharpEditorSetting>())
	{
		for (const auto& Module : UnrealCSharpEditorSetting->GetSupportedModule())
		{
			SupportedModule.Add(FString::Printf(TEXT(
				"%s.%s"),
			                                    *SCRIPT,
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
				                *SCRIPT,
				                *AssetPath

				),
				FString::Printf(TEXT(
					"%s.%s."
				),
				                *SCRIPT,
				                *AssetPath
				)
			});
		}

		for (const auto& AssetClass : UnrealCSharpEditorSetting->GetSupportedAssetClass())
		{
			SupportedAssetClassName.Add(AssetClass->GetFName());
		}
	}
}

void FGeneratorCore::EndGenerator()
{
	SupportedModule.Empty();

	SupportedAssetPath.Empty();

	SupportedAssetPathNameSpace.Empty();

	SupportedMap.Empty();

	SupportedAssetClassName.Empty();

	FEnumGenerator::EnumUnderlyingType.Empty();
}
