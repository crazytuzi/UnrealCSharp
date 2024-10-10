#pragma once

#include "Domain/FMonoDomain.h"
#include "Dynamic/FDynamicGeneratorCore.h"

template <auto IsSoftReference>
FProperty* FTypeBridge::Factory(MonoReflectionType* InReflectionType, const FFieldVariant& InOwner,
                                const FName& InName, const EObjectFlags InObjectFlags)
{
	switch (const auto PropertyType = GetPropertyType(InReflectionType); PropertyType)
	{
	case EPropertyTypeExtent::Byte: return new FByteProperty(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::UInt16: return new FUInt16Property(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::UInt32: return new FUInt32Property(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::UInt64: return new FUInt64Property(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::Int8: return new FInt8Property(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::Int16: return new FInt16Property(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::Int: return new FIntProperty(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::Int64: return new FInt64Property(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::Bool: return new FBoolProperty(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::Float: return new FFloatProperty(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::ClassReference:
		{
			return ManagedFactory<IsSoftReference>(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::SubclassOfReference:
		{
			return ManagedFactory<IsSoftReference>(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::ObjectReference:
		{
			return ManagedFactory<IsSoftReference>(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::Name: return new FNameProperty(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::Interface:
		{
			return ManagedFactory<IsSoftReference>(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::Struct:
		{
			return ManagedFactory<IsSoftReference>(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::Enum:
		{
			return ManagedFactory<IsSoftReference>(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::String: return new FStrProperty(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::Text: return new FTextProperty(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::WeakObjectReference:
		{
			return ManagedFactory<IsSoftReference>(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::LazyObjectReference:
		{
			return ManagedFactory<IsSoftReference>(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::SoftClassReference:
		{
			return ManagedFactory<IsSoftReference>(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::SoftObjectReference:
		{
			return ManagedFactory<IsSoftReference>(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::Double: return new FDoubleProperty(InOwner, InName, InObjectFlags);

	case EPropertyTypeExtent::Map:
		{
			return ManagedFactory<IsSoftReference>(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::Set:
		{
			return ManagedFactory<IsSoftReference>(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);
		}

	case EPropertyTypeExtent::Array:
		{
			return ManagedFactory<IsSoftReference>(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);
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
FProperty* FTypeBridge::ManagedFactory(const EPropertyTypeExtent InPropertyType,
                                       MonoReflectionType* InReflectionType, const FFieldVariant& InOwner,
                                       const FName& InName, const EObjectFlags InObjectFlags)
{
	switch (InPropertyType)
	{
	case EPropertyTypeExtent::ClassReference:
		{
			const auto PathName = GetGenericPathName(InReflectionType);

			const auto ClassProperty = new FClassProperty(InOwner, InName, InObjectFlags);

			ClassProperty->MetaClass = UObject::StaticClass();

			return ClassProperty;
		}

	case EPropertyTypeExtent::SubclassOfReference:
		{
			const auto PathName = GetGenericPathName(InReflectionType);

			const auto ClassProperty = new FClassProperty(InOwner, InName, InObjectFlags);

			ClassProperty->SetPropertyFlags(CPF_UObjectWrapper);

			SetClass<IsSoftReference>(PathName, [PathName, ClassProperty]()
			{
				const auto InClass = LoadObject<UClass>(nullptr, *PathName);

				ClassProperty->MetaClass = InClass;
			});

			return ClassProperty;
		}

	case EPropertyTypeExtent::ObjectReference:
		{
			const auto PathName = GetPathName(InReflectionType);

			const auto ObjectProperty = new FObjectProperty(InOwner, InName, InObjectFlags);

			SetClass<IsSoftReference>(PathName, [PathName, ObjectProperty]()
			{
				const auto InClass = LoadObject<UClass>(nullptr, *PathName);

				ObjectProperty->PropertyClass = InClass;
			});

			return ObjectProperty;
		}

	case EPropertyTypeExtent::Interface:
		{
			const auto PathName = GetGenericPathName(InReflectionType);

			const auto InterfaceProperty = new FInterfaceProperty(InOwner, InName, InObjectFlags);

			SetClass<IsSoftReference>(PathName, [PathName, InterfaceProperty]()
			{
				const auto InClass = LoadObject<UClass>(nullptr, *PathName);

				InterfaceProperty->InterfaceClass = InClass;
			});

			return InterfaceProperty;
		}

	case EPropertyTypeExtent::Struct:
		{
			const auto PathName = GetPathName(InReflectionType);

			const auto InScriptStruct = LoadObject<UScriptStruct>(nullptr, *PathName);

			const auto StructProperty = new FStructProperty(InOwner, InName, InObjectFlags);

			StructProperty->ElementSize = InScriptStruct->GetStructureSize();

			StructProperty->Struct = InScriptStruct;

			return StructProperty;
		}

	case EPropertyTypeExtent::Map:
		{
			const auto MapProperty = new FMapProperty(InOwner, InName, InObjectFlags);

			MapProperty->KeyProp = Factory<IsSoftReference>(GetGenericArgument(InReflectionType), MapProperty, "",
			                                                EObjectFlags::RF_Transient);

			MapProperty->ValueProp = Factory<IsSoftReference>(GetGenericArgument(InReflectionType, 1), MapProperty, "",
			                                                  EObjectFlags::RF_Transient);

			return MapProperty;
		}

	case EPropertyTypeExtent::Set:
		{
			const auto SetProperty = new FSetProperty(InOwner, InName, InObjectFlags);

			SetProperty->ElementProp = Factory<IsSoftReference>(GetGenericArgument(InReflectionType), SetProperty, "",
			                                                    EObjectFlags::RF_Transient);

			return SetProperty;
		}

	case EPropertyTypeExtent::Array:
		{
			const auto ArrayProperty = new FArrayProperty(InOwner, InName, InObjectFlags);

			ArrayProperty->Inner = Factory<IsSoftReference>(GetGenericArgument(InReflectionType), ArrayProperty, "",
			                                                EObjectFlags::RF_Transient);

			return ArrayProperty;
		}

	case EPropertyTypeExtent::Enum:
		{
			const auto PathName = GetPathName(InReflectionType);

			const auto InEnum = LoadObject<UEnum>(nullptr, *PathName);

			const auto EnumProperty = new FEnumProperty(InOwner, InName, InObjectFlags);

			const auto InType = FMonoDomain::Reflection_Type_Get_Type(
				GetType(InReflectionType));

			const auto UnderlyingType = FMonoDomain::
				Type_Get_Underlying_Type(InType);

			const auto UnderlyingReflectionType = FMonoDomain::Type_Get_Object(
				UnderlyingType);

			const auto UnderlyingProperty = Factory(UnderlyingReflectionType, EnumProperty, "",
			                                        EObjectFlags::RF_NoFlags);

			EnumProperty->ElementSize = UnderlyingProperty->ElementSize;

			EnumProperty->SetEnum(InEnum);

			EnumProperty->AddCppProperty(UnderlyingProperty);

			return EnumProperty;
		}

	case EPropertyTypeExtent::WeakObjectReference:
		{
			const auto PathName = GetGenericPathName(InReflectionType);

			const auto WeakObjectProperty = new FWeakObjectProperty(InOwner, InName, InObjectFlags);

			SetClass<IsSoftReference>(PathName, [PathName, WeakObjectProperty]()
			{
				const auto InClass = LoadObject<UClass>(nullptr, *PathName);

				WeakObjectProperty->PropertyClass = InClass;
			});

			return WeakObjectProperty;
		}

	case EPropertyTypeExtent::LazyObjectReference:
		{
			const auto PathName = GetGenericPathName(InReflectionType);

			const auto LazyObjectProperty = new FLazyObjectProperty(InOwner, InName, InObjectFlags);

			SetClass<IsSoftReference>(PathName, [PathName, LazyObjectProperty]()
			{
				const auto InClass = LoadObject<UClass>(nullptr, *PathName);

				LazyObjectProperty->PropertyClass = InClass;
			});

			return LazyObjectProperty;
		}

	case EPropertyTypeExtent::SoftClassReference:
		{
			const auto PathName = GetGenericPathName(InReflectionType);

			const auto SoftClassProperty = new FSoftClassProperty(InOwner, InName, InObjectFlags);

			SetClass<IsSoftReference>(PathName, [PathName, SoftClassProperty]()
			{
				const auto InClass = LoadObject<UClass>(nullptr, *PathName);

				SoftClassProperty->MetaClass = InClass;
			});

			return SoftClassProperty;
		}

	case EPropertyTypeExtent::SoftObjectReference:
		{
			const auto PathName = GetGenericPathName(InReflectionType);

			const auto SoftObjectProperty = new FSoftObjectProperty(InOwner, InName, InObjectFlags);

			SetClass<IsSoftReference>(PathName, [PathName, SoftObjectProperty]()
			{
				const auto InClass = LoadObject<UClass>(nullptr, *PathName);

				SoftObjectProperty->PropertyClass = InClass;
			});

			return SoftObjectProperty;
		}

	default: return nullptr;
	}
}
