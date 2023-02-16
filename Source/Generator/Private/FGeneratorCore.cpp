#include "FGeneratorCore.h"
#include "FDelegateGenerator.h"
#include "FEnumGenerator.h"
#include "Misc/FileHelper.h"
#include "FUnrealCSharpFunctionLibrary.h"

// FString FGeneratorCore::GetModuleName(const UField* InField)
// {
// 	if (InField == nullptr)
// 	{
// 		return TEXT("");
// 	}
//
// 	auto ModuleName = InField->GetOuter() ? InField->GetOuter()->GetName() : TEXT("");
//
// 	if (InField->IsNative())
// 	{
// 		ModuleName = ModuleName.Replace(TEXT("/Script/"), TEXT("/"));
// 	}
// 	else
// 	{
// 		auto Index = 0;
//
// 		if (ModuleName.FindLastChar(TEXT('/'), Index))
// 		{
// 			ModuleName = ModuleName.Left(Index);
// 		}
// 	}
//
// 	return ModuleName;
// }

FString FGeneratorCore::GetPathNameAttribute(const UField* InField)
{
	if (InField == nullptr)
	{
		return TEXT("");
	}

	auto ModuleName = InField->GetOuter() ? InField->GetOuter()->GetName() : TEXT("");

	if (InField->IsNative() == false)
	{
		auto Index = 0;

		if (ModuleName.FindLastChar(TEXT('/'), Index))
		{
			ModuleName = ModuleName.Left(Index);
		}
	}

	const auto PathName = FString::Printf(TEXT(
		"%s%s"
	),
	                                      *InField->GetName().Replace(TEXT("_C"),TEXT("")),
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

FString FGeneratorCore::GetFullClass(const UEnum* InEnum)
{
	if (InEnum == nullptr)
	{
		return TEXT("");
	}

	return InEnum->GetName();
}

FString FGeneratorCore::GetClassNameSpace(const UEnum* InStruct)
{
	if (InStruct == nullptr)
	{
		return "";
	}

	FString ModuleName = InStruct->GetOuter() ? InStruct->GetOuter()->GetName() : TEXT("");

	if (InStruct->IsNative())
	{
		ModuleName = ModuleName.Replace(TEXT("/Script/"), TEXT("/"));
	}

	return FString::Printf(TEXT(
		"%s%s"
	),
	                       TEXT("Script"),
	                       *ModuleName.Replace(TEXT("/"), TEXT(".")));
}

FString FGeneratorCore::GetPropertyType(FProperty* Property)
{
	if (Property == nullptr) return "";

	if (const auto ByteProperty = CastField<FByteProperty>(Property))
	{
		return ByteProperty->Enum != nullptr ? GetFullClass(ByteProperty->Enum) : TEXT("Byte");
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

		return GetFullClass(EnumProperty->GetEnum());
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
			"TMap<%s,%s>"
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
		return {ByteProperty->Enum != nullptr ? GetClassNameSpace(ByteProperty->Enum) : TEXT("System")};
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
		return {GetClassNameSpace(EnumProperty->GetEnum()), TEXT("System")};
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
			                       *GetFullClass(ByteProperty->Enum));
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
		                       *GetFullClass(EnumProperty->GetEnum()));
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

	if (const auto ByteProperty = CastField<FByteProperty>(Property))
	{
		if (ByteProperty->Enum != nullptr)
		{
			return FString::Printf(TEXT(
				"(%s) (*(Byte*)((IntPtr) __OutValue.Value[%d]).ToPointer())"
			),
			                       *GetPropertyType(Property), Index);
		}
		else
		{
			return FString::Printf(TEXT(
				"*(%s*) ((IntPtr) __OutValue.Value[%d]).ToPointer()"
			),
			                       *GetPropertyType(Property),
			                       Index);
		}
	}

	if (const auto EnumProperty = CastField<FEnumProperty>(Property))
	{
		return FString::Printf(TEXT(
			"(%s) (*(%s*)((IntPtr) __OutValue.Value[%d]).ToPointer())"
		),
		                       *GetPropertyType(Property),
		                       *GetPropertyType(EnumProperty->GetUnderlyingProperty()),
		                       Index);
	}

	if (CastField<FUInt16Property>(Property) || CastField<FUInt32Property>(Property) ||
		CastField<FUInt64Property>(Property) || CastField<FInt8Property>(Property) ||
		CastField<FInt16Property>(Property) || CastField<FIntProperty>(Property) ||
		CastField<FInt64Property>(Property) || CastField<FBoolProperty>(Property) ||
		CastField<FFloatProperty>(Property) || CastField<FDoubleProperty>(Property))
	{
		return FString::Printf(TEXT(
			"*(%s*) ((IntPtr) __OutValue.Value[%d]).ToPointer()"
		),
		                       *GetPropertyType(Property),
		                       Index);
	}

	return FString::Printf(TEXT(
		"(%s) __OutValue.Value[%d]"
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
	if (const auto ByteProperty = CastField<FByteProperty>(Property))
	{
		if (ByteProperty->Enum != nullptr)
		{
			return FString::Printf(TEXT(
				"(%s) __ReturnValue"
			),
			                       *GetFullClass(ByteProperty->Enum));
		}
	}

	if (const auto EnumProperty = CastField<FEnumProperty>(Property))
	{
		return FString::Printf(TEXT(
			"(%s) __ReturnValue"
		),
		                       *GetFullClass(EnumProperty->GetEnum()));
	}

	return TEXT("__ReturnValue");
}

FString FGeneratorCore::GetName(FString InName)
{
	static TSet<FName> KeyWords{
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

	if (KeyWords.Contains(*InName))
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
