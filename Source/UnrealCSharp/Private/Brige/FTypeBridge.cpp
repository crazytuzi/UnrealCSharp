#include "Bridge/FTypeBridge.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/NamespaceMacro.h"
#include "Macro/PropertyMacro.h"

EPropertyType FTypeBridge::GetPropertyType(MonoClass* InMonoClass)
{
	static TMap<FString, EPropertyType> ManagedMonoClassMap
	{
		{CLASS_U_OBJECT, CPT_ObjectReference},
		{CLASS_F_NAME, CPT_Name},
		{CLASS_U_STRUCT, CPT_Struct},
		{CLASS_F_STRING, CPT_String},
		{CLASS_F_TEXT, CPT_Text}
	};

	if (InMonoClass == nullptr) return CPT_None;

	for (const auto& ManagedMonoClassPair : ManagedMonoClassMap)
	{
		if (const auto ManagedMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), ManagedMonoClassPair.Key))
		{
			if (FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Is_Subclass_Of(
				InMonoClass, ManagedMonoClass, false))
			{
				return ManagedMonoClassPair.Value;
			}
		}
	}

	if (InMonoClass == FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Byte_Class()) return CPT_Byte;

	if (InMonoClass == FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_UInt16_Class()) return CPT_UInt16;

	if (InMonoClass == FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_UInt32_Class()) return CPT_UInt32;

	if (InMonoClass == FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_UInt64_Class()) return CPT_UInt64;

	if (InMonoClass == FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Byte_Class()) return CPT_Int8;

	if (InMonoClass == FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Int16_Class()) return CPT_Int16;

	if (InMonoClass == FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Int32_Class()) return CPT_Int;

	if (InMonoClass == FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Int64_Class()) return CPT_Int64;

	if (InMonoClass == FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Boolean_Class()) return CPT_Bool;

	if (InMonoClass == FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Single_Class()) return CPT_Float;

	if (FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Is_Subclass_Of(
		InMonoClass, FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Enum_Class(), false))
		return CPT_ENUM;

	if (InMonoClass == FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Double_Class()) return CPT_Double;

	return CPT_None;
}

MonoClass* FTypeBridge::GetMonoClass(const FProperty* InProperty)
{
	const auto InPropertyType = FPropertyDescriptor::GetPropertyType(InProperty);

	switch (InPropertyType)
	{
	case CPT_Byte: return FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Byte_Class();

	case CPT_UInt16: return FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_UInt16_Class();

	case CPT_UInt32: return FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_UInt32_Class();

	case CPT_UInt64: return FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_UInt64_Class();

	case CPT_Int8: return FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Byte_Class();

	case CPT_Int16: return FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Int16_Class();

	case CPT_Int: return FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Int32_Class();

	case CPT_Int64: return FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Int64_Class();

	case CPT_Bool:

	case CPT_Bool8:

	case CPT_Bool16:

	case CPT_Bool32:

	case CPT_Bool64: return FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Boolean_Class();

	case CPT_Float: return FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Single_Class();

	case CPT_ObjectReference:
		{
			// @TODO
		};

	case CPT_Name:
		{
			// @TODO
		};

	case CPT_Delegate:
		{
			// @TODO
		};

	case CPT_Interface:
		{
			// @TODO
		};

	case CPT_Struct:
		{
			// @TODO
		};

	case CPT_ENUM:
		{
			// @TODO
		};

	case CPT_ARRAY:
		{
			// @TODO
		};

	case CPT_String:
		{
			// @TODO
		};

	case CPT_Text:
		{
			// @TODO
		};

	case CPT_MulticastDelegate:
		{
			// @TODO
		};

	case CPT_WeakObjectReference:
		{
			// @TODO
		};

	case CPT_LazyObjectReference:
		{
			// @TODO
		};

	case CPT_SoftObjectReference:
		{
			// @TODO
		};

	case CPT_Double: return FCSharpEnvironment::GetEnvironment()->GetDomain()->Get_Double_Class();

	case CPT_Map:
		{
			// @TODO
		};

	case CPT_Set:
		{
			// @TODO
		};

	default: return nullptr;
	}
}

FString FTypeBridge::GetFullClass(const UStruct* InStruct)
{
	if (InStruct == nullptr)
	{
		return TEXT("");
	}

	return FString::Printf(TEXT(
		"%s%s"
	),
	                       InStruct->IsNative() ? InStruct->GetPrefixCPP() : TEXT(""), *InStruct->GetName());
}

FString FTypeBridge::GetFullInterface(const UStruct* InStruct)
{
	return FString::Printf(TEXT(
		"I%s"
	),
	                       *GetFullClass(InStruct).RightChop(1));
}

FString FTypeBridge::GetClassNameSpace(const UStruct* InStruct)
{
	if (InStruct == nullptr)
	{
		return TEXT("");
	}

	auto ModuleName = InStruct->GetOuter() ? InStruct->GetOuter()->GetName() : TEXT("");

	if (InStruct->IsNative())
	{
		ModuleName = ModuleName.Replace(TEXT("/Script/"), TEXT("/"));
	}

	return FString::Printf(TEXT(
		"%s%s"
	),
	                       *NAMESPACE_ROOT,
	                       *ModuleName.Replace(TEXT("/"), TEXT(".")));
}

FString FTypeBridge::GetFullClass(const FDelegateProperty* InDelegateProperty)
{
	if (InDelegateProperty == nullptr)
	{
		return TEXT("");
	}

	const auto SignatureFunction = InDelegateProperty->SignatureFunction;

	if (SignatureFunction == nullptr)
	{
		return TEXT("");
	}

	auto DelegateName = SignatureFunction->GetName();

	DelegateName.LeftChopInline(FString(HEADER_GENERATED_DELEGATE_SIGNATURE_SUFFIX).Len(), false);

	return FString::Printf(TEXT(
		"F%s"
	),
	                       *DelegateName);
}

FString FTypeBridge::GetClassNameSpace(const FDelegateProperty* InDelegateProperty)
{
	if (InDelegateProperty == nullptr)
	{
		return TEXT("");
	}

	const auto SignatureFunction = InDelegateProperty->SignatureFunction;

	if (SignatureFunction == nullptr)
	{
		return TEXT("");
	}

	if (const auto Class = Cast<UClass>(SignatureFunction->GetOuter()))
	{
		return FString::Printf(TEXT(
			"%s.%s"
		),
		                       *GetClassNameSpace(Class),
		                       *SignatureFunction->GetOuter()->GetName());
	}

	if (const auto Package = Cast<UPackage>(SignatureFunction->GetOuter()))
	{
		const auto ModuleName = Package->GetName().Replace(TEXT("/Script/"), TEXT("/"));

		return FString::Printf(TEXT(
			"%s%s"
		),
		                       *NAMESPACE_ROOT,
		                       *ModuleName.Replace(TEXT("/"), TEXT(".")));
	}

	return TEXT("");
}

FString FTypeBridge::GetFullClass(const FMulticastDelegateProperty* InMulticastDelegateProperty)
{
	if (InMulticastDelegateProperty == nullptr)
	{
		return TEXT("");
	}

	const auto SignatureFunction = InMulticastDelegateProperty->SignatureFunction;

	if (SignatureFunction == nullptr)
	{
		return TEXT("");
	}

	auto DelegateName = SignatureFunction->GetName();

	DelegateName.LeftChopInline(FString(HEADER_GENERATED_DELEGATE_SIGNATURE_SUFFIX).Len(), false);

	return FString::Printf(TEXT(
		"F%s"
	),
	                       *DelegateName);
}

FString FTypeBridge::GetClassNameSpace(const FMulticastDelegateProperty* InMulticastDelegateProperty)
{
	if (InMulticastDelegateProperty == nullptr)
	{
		return TEXT("");
	}

	const auto SignatureFunction = InMulticastDelegateProperty->SignatureFunction;

	if (SignatureFunction == nullptr)
	{
		return TEXT("");
	}

	if (const auto Class = Cast<UClass>(SignatureFunction->GetOuter()))
	{
		return FString::Printf(TEXT(
			"%s.%s"
		),
		                       *GetClassNameSpace(Class),
		                       *SignatureFunction->GetOuter()->GetName());
	}

	if (const auto Package = Cast<UPackage>(SignatureFunction->GetOuter()))
	{
		const auto ModuleName = Package->GetName().Replace(TEXT("/Script/"), TEXT("/"));

		return FString::Printf(TEXT(
			"%s%s"
		),
		                       *NAMESPACE_ROOT,
		                       *ModuleName.Replace(TEXT("/"), TEXT(".")));
	}

	return TEXT("");
}
