#include "Reflection/Container/FContainerHelper.h"
#include "Bridge/FTypeBridge.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/FunctionMacro.h"
#include "Macro/NamespaceMacro.h"
#include "Macro/PropertyMacro.h"
#include "Template/TGetArrayLength.h"

FProperty* FContainerHelper::Factory(MonoReflectionType* InReflectionType, const FFieldVariant& InOwner,
                                     const FName& InName, const EObjectFlags InObjectFlags)
{
	const auto PropertyType = FTypeBridge::GetPropertyType(InReflectionType);

	switch (PropertyType)
	{
	case CPT_Byte: return new FByteProperty(InOwner, InName, InObjectFlags);

	case CPT_UInt16: return new FUInt16Property(InOwner, InName, InObjectFlags);

	case CPT_UInt32: return new FUInt32Property(InOwner, InName, InObjectFlags);

	case CPT_Int8: return new FInt8Property(InOwner, InName, InObjectFlags);

	case CPT_Int16: return new FInt16Property(InOwner, InName, InObjectFlags);

	case CPT_Int: return new FIntProperty(InOwner, InName, InObjectFlags);

	case CPT_Int64: return new FInt64Property(InOwner, InName, InObjectFlags);

	case CPT_Bool: return new FBoolProperty(InOwner, InName, InObjectFlags);

	case CPT_Float: return new FFloatProperty(InOwner, InName, InObjectFlags);

	case CPT_CLASS_REFERENCE: return ManagedFactory(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);

	case CPT_ObjectReference: return ManagedFactory(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);

	case CPT_Name: return new FNameProperty(InOwner, InName, InObjectFlags);

	case CPT_Interface: return ManagedFactory(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);

	case CPT_Struct: return ManagedFactory(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);

	case CPT_ENUM: return ManagedFactory(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);

	case CPT_String: return new FStrProperty(InOwner, InName, InObjectFlags);

	case CPT_Text: return new FTextProperty(InOwner, InName, InObjectFlags);

	case CPT_WeakObjectReference: return ManagedFactory(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);

	case CPT_LazyObjectReference: return ManagedFactory(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);

	case CPT_SoftObjectReference: return ManagedFactory(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);

	case CPT_Double: return new FDoubleProperty(InOwner, InName, InObjectFlags);

	default: return nullptr;
	}
}

FProperty* FContainerHelper::ManagedFactory(const EPropertyType InPropertyType, MonoReflectionType* InReflectionType,
                                            const FFieldVariant& InOwner, const FName& InName,
                                            const EObjectFlags InObjectFlags)
{
	switch (InPropertyType)
	{
	case CPT_CLASS_REFERENCE:
		{
			const auto PathName = GetGenericPathName(InReflectionType);

			const auto InClass = LoadObject<UClass>(nullptr, *FString(PathName));

			const auto ClassProperty = new FClassProperty(InOwner, InName, InObjectFlags);

			ClassProperty->MetaClass = InClass;

			return ClassProperty;
		}

	case CPT_ObjectReference:
		{
			const auto PathName = GetPathName(InReflectionType);

			const auto InClass = LoadObject<UClass>(nullptr, *FString(PathName));

			const auto ObjectProperty = new FObjectProperty(InOwner, InName, InObjectFlags);

			ObjectProperty->PropertyClass = InClass;

			return ObjectProperty;
		}

	case CPT_Interface:
		{
			const auto PathName = GetGenericPathName(InReflectionType);

			const auto InClass = LoadObject<UClass>(nullptr, *FString(PathName));

			const auto InterfaceProperty = new FInterfaceProperty(InOwner, InName, InObjectFlags);

			InterfaceProperty->InterfaceClass = InClass;

			return InterfaceProperty;
		}

	case CPT_Struct:
		{
			const auto PathName = GetPathName(InReflectionType);

			const auto InScriptStruct = LoadObject<UScriptStruct>(nullptr, *FString(PathName));

			const auto StructProperty = new FStructProperty(InOwner, InName, InObjectFlags);

			StructProperty->Struct = InScriptStruct;

			return StructProperty;
		}

	case CPT_ENUM:
		{
			const auto PathName = GetPathName(InReflectionType);

			const auto InEnum = LoadObject<UEnum>(nullptr, *FString(PathName));

			const auto EnumProperty = new FEnumProperty(InOwner, InName, InObjectFlags);

			EnumProperty->SetEnum(InEnum);

			return EnumProperty;
		}

	case CPT_WeakObjectReference:
		{
			const auto PathName = GetGenericPathName(InReflectionType);

			const auto InClass = LoadObject<UClass>(nullptr, *FString(PathName));

			const auto WeakObjectProperty = new FWeakObjectProperty(InOwner, InName, InObjectFlags);

			WeakObjectProperty->PropertyClass = InClass;

			return WeakObjectProperty;
		}

	case CPT_LazyObjectReference:
		{
			const auto PathName = GetGenericPathName(InReflectionType);

			const auto InClass = LoadObject<UClass>(nullptr, *FString(PathName));

			const auto LazyObjectProperty = new FLazyObjectProperty(InOwner, InName, InObjectFlags);

			LazyObjectProperty->PropertyClass = InClass;

			return LazyObjectProperty;
		}

	case CPT_SoftObjectReference:
		{
			const auto PathName = GetGenericPathName(InReflectionType);

			const auto InClass = LoadObject<UClass>(nullptr, *FString(PathName));

			const auto SoftObjectProperty = new FSoftObjectProperty(InOwner, InName, InObjectFlags);

			SoftObjectProperty->PropertyClass = InClass;

			return SoftObjectProperty;
		}

	default: return nullptr;
	}
}

FString FContainerHelper::GetPathName(MonoReflectionType* InReflectionType)
{
	const auto UtilsMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_UTILS);

	auto InParams = static_cast<void*>(InReflectionType);

	const auto GetPathNameMonoMethod = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Method_From_Name(
		UtilsMonoClass, FUNCTION_UTILS_GET_PATH_NAME, TGetArrayLength(InParams));

	const auto PathNameMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Runtime_Invoke(
		GetPathNameMonoMethod, nullptr, &InParams, nullptr);

	const auto PathNameMonoString = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_To_String(
		PathNameMonoObject, nullptr);

	return FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(PathNameMonoString);
}

FString FContainerHelper::GetGenericPathName(MonoReflectionType* InReflectionType)
{
	return GetPathName(FTypeBridge::GetGenericArgument(InReflectionType));
}
