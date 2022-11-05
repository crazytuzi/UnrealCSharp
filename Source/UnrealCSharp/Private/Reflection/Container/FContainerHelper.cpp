#include "Reflection/Container/FContainerHelper.h"
#include "Bridge/FTypeBridge.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/FunctionMacro.h"
#include "Macro/NamespaceMacro.h"
#include "Macro/PropertyMacro.h"

FProperty* FContainerHelper::Factory(MonoReflectionType* InReflectionType, const FFieldVariant& InOwner,
                                     const FName& InName, const EObjectFlags InObjectFlags)
{
	const auto InMonoType = mono_reflection_type_get_type(InReflectionType);

	const auto InMonoClass = mono_type_get_class(InMonoType);

	const auto PropertyType = FTypeBridge::GetPropertyType(InMonoClass);

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

	case CPT_ObjectReference: return ManagedFactory(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);

	case CPT_Name: return new FNameProperty(InOwner, InName, InObjectFlags);

	case CPT_Struct: return ManagedFactory(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);

	case CPT_ENUM: return ManagedFactory(PropertyType, InReflectionType, InOwner, InName, InObjectFlags);

	case CPT_String: return new FStrProperty(InOwner, InName, InObjectFlags);

	case CPT_Text: return new FTextProperty(InOwner, InName, InObjectFlags);

	case CPT_Double: return new FDoubleProperty(InOwner, InName, InObjectFlags);

	default: return nullptr;
	}
}

FProperty* FContainerHelper::ManagedFactory(const EPropertyType InPropertyType, MonoReflectionType* InReflectionType,
                                            const FFieldVariant& InOwner, const FName& InName,
                                            const EObjectFlags InObjectFlags)
{
	const auto ContainerUtilsMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CONTAINER), CLASS_CONTAINER_UTILS);

	const auto GetPathNameMonoMethod = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Method_From_Name(
		ContainerUtilsMonoClass,FUNCTION_GET_PATH_NAME, 1);

	auto InParams = static_cast<void*>(InReflectionType);

	const auto PathNameMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Runtime_Invoke(
		GetPathNameMonoMethod, nullptr, &InParams, nullptr);

	const auto PathNameMonoString = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_To_String(
		PathNameMonoObject, nullptr);

	const auto PathName = FCSharpEnvironment::GetEnvironment()->GetDomain()->String_To_UTF8(PathNameMonoString);

	switch (InPropertyType)
	{
	case CPT_ObjectReference:
		{
			const auto InClass = LoadObject<UClass>(nullptr, *FString(PathName));

			const auto ObjectProperty = new FObjectProperty(InOwner, InName, InObjectFlags, 0, EPropertyFlags::CPF_None,
			                                                InClass);

			ObjectProperty->PropertyClass = InClass;

			return ObjectProperty;
		};

	case CPT_Struct:
		{
			const auto InScriptStruct = LoadObject<UScriptStruct>(nullptr, *FString(PathName));

			const auto StructProperty = new FStructProperty(InOwner, InName, InObjectFlags);

			StructProperty->Struct = InScriptStruct;

			return StructProperty;
		}

	case CPT_ENUM:
		{
			const auto InEnum = LoadObject<UEnum>(nullptr, *FString(PathName));

			const auto EnumProperty = new FEnumProperty(InOwner, InName, InObjectFlags);

			EnumProperty->SetEnum(InEnum);

			return EnumProperty;
		}

	default: return nullptr;
	}
}
