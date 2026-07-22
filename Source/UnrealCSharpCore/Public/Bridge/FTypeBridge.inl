#pragma once

#include "Dynamic/FDynamicGeneratorCore.h"
#include "UEVersion.h"

template <auto IsSoftReference>
FProperty* FTypeBridge::Factory(FClassReflection* InClass, const FFieldVariant& InOwner, const FName& InName,
                                const EObjectFlags InObjectFlags)
{
	switch (const auto PropertyType = GetPropertyType(InClass); PropertyType)
	{
	case EPropertyTypeExtent::Byte:
#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
		return new FByteProperty(InOwner, InName, InObjectFlags);
#else
		return new FByteProperty(InOwner, InName);
#endif

	case EPropertyTypeExtent::UInt16:
#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
		return new FUInt16Property(InOwner, InName, InObjectFlags);
#else
		return new FUInt16Property(InOwner, InName);
#endif

	case EPropertyTypeExtent::UInt32:
#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
		return new FUInt32Property(InOwner, InName, InObjectFlags);
#else
		return new FUInt32Property(InOwner, InName);
#endif

	case EPropertyTypeExtent::UInt64:
#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
		return new FUInt64Property(InOwner, InName, InObjectFlags);
#else
		return new FUInt64Property(InOwner, InName);
#endif

	case EPropertyTypeExtent::Int8:
#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
		return new FInt8Property(InOwner, InName, InObjectFlags);
#else
		return new FInt8Property(InOwner, InName);
#endif

	case EPropertyTypeExtent::Int16:
#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
		return new FInt16Property(InOwner, InName, InObjectFlags);
#else
		return new FInt16Property(InOwner, InName);
#endif

	case EPropertyTypeExtent::Int:
#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
		return new FIntProperty(InOwner, InName, InObjectFlags);
#else
		return new FIntProperty(InOwner, InName);
#endif

	case EPropertyTypeExtent::Int64:
#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
		return new FInt64Property(InOwner, InName, InObjectFlags);
#else
		return new FInt64Property(InOwner, InName);
#endif

	case EPropertyTypeExtent::Bool:
#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
		return new FBoolProperty(InOwner, InName, InObjectFlags);
#else
		return new FBoolProperty(InOwner, InName);
#endif

	case EPropertyTypeExtent::Float:
#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
		return new FFloatProperty(InOwner, InName, InObjectFlags);
#else
		return new FFloatProperty(InOwner, InName);
#endif

	case EPropertyTypeExtent::ClassReference:
		{
			return ManagedFactory<IsSoftReference>(PropertyType, InClass, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::SubclassOfReference:
		{
			return ManagedFactory<IsSoftReference>(PropertyType, InClass, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::ObjectReference:
		{
			return ManagedFactory<IsSoftReference>(PropertyType, InClass, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::Name:
#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
		return new FNameProperty(InOwner, InName, InObjectFlags);
#else
		return new FNameProperty(InOwner, InName);
#endif

	case EPropertyTypeExtent::Interface:
		{
			return ManagedFactory<IsSoftReference>(PropertyType, InClass, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::Struct:
		{
			return ManagedFactory<IsSoftReference>(PropertyType, InClass, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::Enum:
		{
			return ManagedFactory<IsSoftReference>(PropertyType, InClass, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::String:
#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
		return new FStrProperty(InOwner, InName, InObjectFlags);
#else
		return new FStrProperty(InOwner, InName);
#endif

#if UE_F_UTF8_STR_PROPERTY
	case EPropertyTypeExtent::Utf8String:
#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
		return new FUtf8StrProperty(InOwner, InName, InObjectFlags);
#else
		return new FUtf8StrProperty(InOwner, InName);
#endif
#endif

#if UE_F_ANSI_STR_PROPERTY
	case EPropertyTypeExtent::AnsiString:
#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
		return new FAnsiStrProperty(InOwner, InName, InObjectFlags);
#else
		return new FAnsiStrProperty(InOwner, InName);
#endif
#endif

	case EPropertyTypeExtent::Text:
#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
		return new FTextProperty(InOwner, InName, InObjectFlags);
#else
		return new FTextProperty(InOwner, InName);
#endif

	case EPropertyTypeExtent::WeakObjectReference:
		{
			return ManagedFactory<IsSoftReference>(PropertyType, InClass, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::LazyObjectReference:
		{
			return ManagedFactory<IsSoftReference>(PropertyType, InClass, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::SoftClassReference:
		{
			return ManagedFactory<IsSoftReference>(PropertyType, InClass, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::SoftObjectReference:
		{
			return ManagedFactory<IsSoftReference>(PropertyType, InClass, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::Double:
#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
		return new FDoubleProperty(InOwner, InName, InObjectFlags);
#else
		return new FDoubleProperty(InOwner, InName);
#endif

	case EPropertyTypeExtent::Map:
		{
			return ManagedFactory<IsSoftReference>(PropertyType, InClass, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::Set:
		{
			return ManagedFactory<IsSoftReference>(PropertyType, InClass, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::Array:
		{
			return ManagedFactory<IsSoftReference>(PropertyType, InClass, InOwner, InName, InObjectFlags);
		}

	default: return nullptr;
	}
}

template <auto IsSoftReference>
void SetClass(const FString& InPathName, const TFunction<void()>& InSetClass)
{
	if constexpr (IsSoftReference)
	{
		if (int32 Index; InPathName.FindLastChar('.', Index))
		{
			if (const auto Name = InPathName.RightChop(Index + 1);
				FDynamicGeneratorCore::IsCompleted(Name))
			{
				InSetClass();
			}
			else
			{
				FDynamicGeneratorCore::OnCompleted(Name, [InSetClass]()
				{
					InSetClass();
				});
			}
		}
	}
	else
	{
		InSetClass();
	}
}

template <auto IsSoftReference>
FProperty* FTypeBridge::ManagedFactory(EPropertyTypeExtent InPropertyType, FClassReflection* InClass,
                                       const FFieldVariant& InOwner, const FName& InName,
                                       const EObjectFlags InObjectFlags)
{
	switch (InPropertyType)
	{
	case EPropertyTypeExtent::ClassReference:
		{
#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
			const auto ClassProperty = new FClassProperty(InOwner, InName, InObjectFlags);
#else
			const auto ClassProperty = new FClassProperty(InOwner, InName);
#endif

			ClassProperty->PropertyClass = UObject::StaticClass();

			ClassProperty->MetaClass = UObject::StaticClass();

			return ClassProperty;
		}

	case EPropertyTypeExtent::SubclassOfReference:
		{
			const auto PathName = InClass->GetGenericArgument()->GetPathName();

#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
			const auto ClassProperty = new FClassProperty(InOwner, InName, InObjectFlags);
#else
			const auto ClassProperty = new FClassProperty(InOwner, InName);
#endif

			ClassProperty->SetPropertyFlags(CPF_UObjectWrapper);

			SetClass<IsSoftReference>(PathName, [PathName, ClassProperty]()
			{
				const auto Class = LoadObject<UClass>(nullptr, *PathName);

				ClassProperty->PropertyClass = Class;

				ClassProperty->MetaClass = Class;
			});

			return ClassProperty;
		}

	case EPropertyTypeExtent::ObjectReference:
		{
			const auto PathName = InClass->GetPathName();

#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
			const auto ObjectProperty = new FObjectProperty(InOwner, InName, InObjectFlags);
#else
			const auto ObjectProperty = new FObjectProperty(InOwner, InName);
#endif

			SetClass<IsSoftReference>(PathName, [PathName, ObjectProperty]()
			{
				const auto Class = LoadObject<UClass>(nullptr, *PathName);

				ObjectProperty->PropertyClass = Class;
			});

			return ObjectProperty;
		}

	case EPropertyTypeExtent::Interface:
		{
			const auto PathName = InClass->GetGenericArgument()->GetPathName();

#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
			const auto InterfaceProperty = new FInterfaceProperty(InOwner, InName, InObjectFlags);
#else
			const auto InterfaceProperty = new FInterfaceProperty(InOwner, InName);
#endif

			SetClass<IsSoftReference>(PathName, [PathName, InterfaceProperty]()
			{
				const auto Class = LoadObject<UClass>(nullptr, *PathName);

				InterfaceProperty->InterfaceClass = Class;
			});

			return InterfaceProperty;
		}

	case EPropertyTypeExtent::Struct:
		{
			const auto PathName = InClass->GetPathName();

			const auto InScriptStruct = LoadObject<UScriptStruct>(nullptr, *PathName);

#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
			const auto StructProperty = new FStructProperty(InOwner, InName, InObjectFlags);
#else
			const auto StructProperty = new FStructProperty(InOwner, InName);
#endif

#if UE_F_PROPERTY_SET_ELEMENT_SIZE
			StructProperty->SetElementSize(InScriptStruct->GetStructureSize());
#else
			StructProperty->ElementSize = InScriptStruct->GetStructureSize();
#endif

			StructProperty->Struct = InScriptStruct;

			return StructProperty;
		}

	case EPropertyTypeExtent::Map:
		{
#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
			const auto MapProperty = new FMapProperty(InOwner, InName, InObjectFlags);
#else
			const auto MapProperty = new FMapProperty(InOwner, InName);
#endif

			MapProperty->KeyProp = Factory<IsSoftReference>(InClass->GetGenericArgument(),
			                                                MapProperty, "",
			                                                EObjectFlags::RF_Transient);

			MapProperty->ValueProp = Factory<IsSoftReference>(InClass->GetGenericArgument(1),
			                                                  MapProperty, "",
			                                                  EObjectFlags::RF_Transient);

			return MapProperty;
		}

	case EPropertyTypeExtent::Set:
		{
#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
			const auto SetProperty = new FSetProperty(InOwner, InName, InObjectFlags);
#else
			const auto SetProperty = new FSetProperty(InOwner, InName);
#endif

			SetProperty->ElementProp = Factory<IsSoftReference>(InClass->GetGenericArgument(),
			                                                    SetProperty, "",
			                                                    EObjectFlags::RF_Transient);

			return SetProperty;
		}

	case EPropertyTypeExtent::Array:
		{
#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
			const auto ArrayProperty = new FArrayProperty(InOwner, InName, InObjectFlags);
#else
			const auto ArrayProperty = new FArrayProperty(InOwner, InName);
#endif

			ArrayProperty->Inner = Factory<IsSoftReference>(InClass->GetGenericArgument(),
			                                                ArrayProperty, "",
			                                                EObjectFlags::RF_Transient);

			return ArrayProperty;
		}

	case EPropertyTypeExtent::Enum:
		{
			const auto PathName = InClass->GetPathName();

			const auto InEnum = LoadObject<UEnum>(nullptr, *PathName);

#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
			const auto EnumProperty = new FEnumProperty(InOwner, InName, InObjectFlags);
#else
			const auto EnumProperty = new FEnumProperty(InOwner, InName);
#endif

			const auto UnderlyingProperty = Factory(InClass->GetUnderlyingType(),
			                                        EnumProperty, "", EObjectFlags::RF_NoFlags);

#if UE_F_PROPERTY_SET_ELEMENT_SIZE && UE_F_PROPERTY_GET_ELEMENT_SIZE
			EnumProperty->SetElementSize(UnderlyingProperty->GetElementSize());
#else
			EnumProperty->ElementSize = UnderlyingProperty->ElementSize;
#endif

			EnumProperty->SetEnum(InEnum);

			EnumProperty->AddCppProperty(UnderlyingProperty);

			return EnumProperty;
		}

	case EPropertyTypeExtent::WeakObjectReference:
		{
			const auto PathName = InClass->GetGenericArgument()->GetPathName();

#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
			const auto WeakObjectProperty = new FWeakObjectProperty(InOwner, InName, InObjectFlags);
#else
			const auto WeakObjectProperty = new FWeakObjectProperty(InOwner, InName);
#endif

			SetClass<IsSoftReference>(PathName, [PathName, WeakObjectProperty]()
			{
				const auto Class = LoadObject<UClass>(nullptr, *PathName);

				WeakObjectProperty->PropertyClass = Class;
			});

			return WeakObjectProperty;
		}

	case EPropertyTypeExtent::LazyObjectReference:
		{
			const auto PathName = InClass->GetGenericArgument()->GetPathName();

#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
			const auto LazyObjectProperty = new FLazyObjectProperty(InOwner, InName, InObjectFlags);
#else
			const auto LazyObjectProperty = new FLazyObjectProperty(InOwner, InName);
#endif

			SetClass<IsSoftReference>(PathName, [PathName, LazyObjectProperty]()
			{
				const auto Class = LoadObject<UClass>(nullptr, *PathName);

				LazyObjectProperty->PropertyClass = Class;
			});

			return LazyObjectProperty;
		}

	case EPropertyTypeExtent::SoftClassReference:
		{
			const auto PathName = InClass->GetGenericArgument()->GetPathName();

#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
			const auto SoftClassProperty = new FSoftClassProperty(InOwner, InName, InObjectFlags);
#else
			const auto SoftClassProperty = new FSoftClassProperty(InOwner, InName);
#endif

			SetClass<IsSoftReference>(PathName, [PathName, SoftClassProperty]()
			{
				const auto Class = LoadObject<UClass>(nullptr, *PathName);

				SoftClassProperty->PropertyClass = Class;

				SoftClassProperty->MetaClass = Class;
			});

			return SoftClassProperty;
		}

	case EPropertyTypeExtent::SoftObjectReference:
		{
			const auto PathName = InClass->GetGenericArgument()->GetPathName();

#if UE_F_PROPERTY_CONSTRUCTOR_E_OBJECT_FLAGS
			const auto SoftObjectProperty = new FSoftObjectProperty(InOwner, InName, InObjectFlags);
#else
			const auto SoftObjectProperty = new FSoftObjectProperty(InOwner, InName);
#endif

			SetClass<IsSoftReference>(PathName, [PathName, SoftObjectProperty]()
			{
				const auto Class = LoadObject<UClass>(nullptr, *PathName);

				SoftObjectProperty->PropertyClass = Class;
			});

			return SoftObjectProperty;
		}

	default: return nullptr;
	}
}
