#include "Environment/FCSharpEnvironment.h"
#include "Delegate/FUnrealCSharpModuleDelegates.h"
#include "Macro/NamespaceMacro.h"
#include "mono/metadata/object.h"

FCSharpEnvironment* FCSharpEnvironment::Environment = nullptr;

FMonoDomain* FCSharpEnvironment::Domain = nullptr;

FCSharpEnvironment::FCSharpEnvironment()
{
	Initialize();
}

FCSharpEnvironment::~FCSharpEnvironment()
{
	Deinitialize();
}

void FCSharpEnvironment::Initialize()
{
	ClassRegistry = new FClassRegistry();

	ObjectRegistry = new FObjectRegistry();

	StructRegistry = new FStructRegistry();

	ContainerRegistry = new FContainerRegistry();

	DelegateRegistry = new FDelegateRegistry();

	BindingRegistry = new FBindingRegistry();

	OnUnrealCSharpModuleInActiveDelegateHandle = FUnrealCSharpModuleDelegates::OnUnrealCSharpModuleInActive.AddRaw(
		this, &FCSharpEnvironment::OnUnrealCSharpModuleInActive);
}

void FCSharpEnvironment::Deinitialize()
{
	if (OnUnrealCSharpModuleInActiveDelegateHandle.IsValid())
	{
		FUnrealCSharpModuleDelegates::OnUnrealCSharpModuleInActive.Remove(OnUnrealCSharpModuleInActiveDelegateHandle);
	}

	if (BindingRegistry != nullptr)
	{
		delete BindingRegistry;

		BindingRegistry = nullptr;
	}

	if (DelegateRegistry != nullptr)
	{
		delete DelegateRegistry;

		DelegateRegistry = nullptr;
	}

	if (ContainerRegistry != nullptr)
	{
		delete ContainerRegistry;

		ContainerRegistry = nullptr;
	}

	if (StructRegistry != nullptr)
	{
		delete StructRegistry;

		StructRegistry = nullptr;
	}

	if (ObjectRegistry != nullptr)
	{
		delete ObjectRegistry;

		ObjectRegistry = nullptr;
	}

	if (ClassRegistry != nullptr)
	{
		delete ClassRegistry;

		ClassRegistry = nullptr;
	}
}

FCSharpEnvironment* FCSharpEnvironment::GetEnvironment()
{
	if (Environment == nullptr)
	{
		Environment = new FCSharpEnvironment();

		if (Domain == nullptr)
		{
			Domain = new FMonoDomain({
				"",
				FPaths::ConvertRelativePathToFull(
					FPaths::Combine(FPaths::ProjectContentDir(), NAMESPACE_ROOT, NAMESPACE_ROOT + ".dll"))
			});
		}

		return Environment;
	}

	return Environment;
}

FMonoDomain* FCSharpEnvironment::GetDomain() const
{
	return Domain;
}

void FCSharpEnvironment::NotifyUObjectCreated(const UObjectBase* Object, int32 Index)
{
	if (const auto InObject = static_cast<UObject*>(const_cast<UObjectBase*>(Object)))
	{
		Bind(InObject);
	}
}

void FCSharpEnvironment::NotifyUObjectDeleted(const UObjectBase* Object, int32 Index)
{
	if (const auto InObject = static_cast<UObject*>(const_cast<UObjectBase*>(Object)))
	{
		if (const auto InClass = Cast<UClass>(InObject))
		{
			DeleteClassDescriptor(InClass);
		}
		else
		{
			RemoveObjectReference(InObject);
		}
	}
}

void FCSharpEnvironment::OnUObjectArrayShutdown()
{
}

void FCSharpEnvironment::OnUnrealCSharpModuleInActive()
{
	if (Environment != nullptr)
	{
		delete Environment;

		Environment = nullptr;
	}
}

bool FCSharpEnvironment::Bind(UObject* Object) const
{
	return FCSharpBind::Bind(Domain, Object);
}

bool FCSharpEnvironment::Bind(MonoObject* InMonoObject, MonoReflectionType* InKeyReflectionType,
                              MonoReflectionType* InValueReflectionType) const
{
	return FCSharpBind::Bind(InMonoObject, InKeyReflectionType, InValueReflectionType);
}

bool FCSharpEnvironment::Bind(MonoObject* InMonoObject, const FName& InStructName) const
{
	return FCSharpBind::Bind(Domain, InMonoObject, InStructName);
}

FClassDescriptor* FCSharpEnvironment::GetClassDescriptor(const UStruct* InStruct) const
{
	return ClassRegistry != nullptr ? ClassRegistry->GetClassDescriptor(InStruct) : nullptr;
}

FClassDescriptor* FCSharpEnvironment::GetClassDescriptor(const FName& InClassName) const
{
	return ClassRegistry != nullptr ? ClassRegistry->GetClassDescriptor(InClassName) : nullptr;
}

FClassDescriptor* FCSharpEnvironment::NewClassDescriptor(const FMonoDomain* InMonoDomain, UStruct* InStruct) const
{
	return ClassRegistry != nullptr ? ClassRegistry->NewClassDescriptor(InMonoDomain, InStruct) : nullptr;
}

void FCSharpEnvironment::DeleteClassDescriptor(const UStruct* InStruct) const
{
	if (ClassRegistry != nullptr)
	{
		ClassRegistry->DeleteClassDescriptor(InStruct);
	}
}

FFunctionDescriptor* FCSharpEnvironment::GetFunctionDescriptor(const UStruct* InStruct,
                                                               const FName& InFunctionName) const
{
	const auto FoundClassDescriptor = GetClassDescriptor(InStruct);

	return FoundClassDescriptor != nullptr ? FoundClassDescriptor->GetFunctionDescriptor(InFunctionName) : nullptr;
}

FFunctionDescriptor* FCSharpEnvironment::GetFunctionDescriptor(const FName& InClassName,
                                                               const FName& InFunctionName) const
{
	const auto FoundClassDescriptor = GetClassDescriptor(InClassName);

	return FoundClassDescriptor != nullptr ? FoundClassDescriptor->GetFunctionDescriptor(InFunctionName) : nullptr;
}

FPropertyDescriptor* FCSharpEnvironment::GetPropertyDescriptor(const UStruct* InStruct,
                                                               const FName& InPropertyName) const
{
	const auto FoundClassDescriptor = GetClassDescriptor(InStruct);

	return FoundClassDescriptor != nullptr ? FoundClassDescriptor->GetPropertyDescriptor(InPropertyName) : nullptr;
}

void* FCSharpEnvironment::GetAddress(const MonoObject* InMonoObject, UStruct*& InStruct) const
{
	if (ObjectRegistry != nullptr)
	{
		if (const auto FoundObject = ObjectRegistry->GetAddress(InMonoObject, InStruct))
		{
			return FoundObject;
		}
	}

	if (StructRegistry != nullptr)
	{
		if (const auto FoundStruct = StructRegistry->GetAddress(InMonoObject, InStruct))
		{
			return FoundStruct;
		}
	}

	return nullptr;
}

bool FCSharpEnvironment::AddObjectReference(UObject* InObject, MonoObject* InMonoObject) const
{
	return ObjectRegistry != nullptr ? ObjectRegistry->AddReference(InObject, InMonoObject) : false;
}

MonoObject* FCSharpEnvironment::GetObject(const UObject* InObject) const
{
	return ObjectRegistry != nullptr ? ObjectRegistry->GetObject(InObject) : nullptr;
}

UObject* FCSharpEnvironment::GetObject(const MonoObject* InMonoObject) const
{
	return ObjectRegistry != nullptr ? ObjectRegistry->GetObject(InMonoObject) : nullptr;
}

bool FCSharpEnvironment::RemoveObjectReference(const UObject* InObject) const
{
	return ObjectRegistry != nullptr ? ObjectRegistry->RemoveReference(InObject) : false;
}

bool FCSharpEnvironment::RemoveObjectReference(const MonoObject* InMonoObject) const
{
	return ObjectRegistry != nullptr ? ObjectRegistry->RemoveReference(InMonoObject) : false;
}

bool FCSharpEnvironment::AddStructReference(UScriptStruct* InScriptStruct, void* InStruct, MonoObject* InMonoObject,
                                            const bool bNeedFree) const
{
	return StructRegistry != nullptr
		       ? StructRegistry->AddReference(InScriptStruct, InStruct, InMonoObject, bNeedFree)
		       : false;
}

MonoObject* FCSharpEnvironment::GetObject(const void* InStruct) const
{
	return StructRegistry != nullptr ? StructRegistry->GetObject(InStruct) : nullptr;
}

void* FCSharpEnvironment::GetStruct(const MonoObject* InMonoObject) const
{
	return StructRegistry != nullptr ? StructRegistry->GetStruct(InMonoObject) : nullptr;
}

bool FCSharpEnvironment::RemoveStructReference(const void* InStruct) const
{
	return StructRegistry != nullptr ? StructRegistry->RemoveReference(InStruct) : false;
}

bool FCSharpEnvironment::RemoveStructReference(const MonoObject* InMonoObject) const
{
	return StructRegistry != nullptr ? StructRegistry->RemoveReference(InMonoObject) : false;
}

MonoObject* FCSharpEnvironment::GetContainerObject(const void* InContainer) const
{
	return ContainerRegistry != nullptr ? ContainerRegistry->GetObject(InContainer) : nullptr;
}

bool FCSharpEnvironment::AddContainerReference(void* InContainer, MonoObject* InMonoObject) const
{
	return ContainerRegistry != nullptr ? ContainerRegistry->AddReference(InContainer, InMonoObject) : false;
}

bool FCSharpEnvironment::AddContainerReference(void* InAddress, void* InContainer, MonoObject* InMonoObject) const
{
	return ContainerRegistry != nullptr
		       ? ContainerRegistry->AddReference(InAddress, InContainer, InMonoObject)
		       : false;
}

MonoObject* FCSharpEnvironment::GetDelegateObject(const void* InDelegate) const
{
	return DelegateRegistry != nullptr ? DelegateRegistry->GetObject(InDelegate) : nullptr;
}

bool FCSharpEnvironment::AddDelegateReference(void* InAddress, void* InDelegate, MonoObject* InMonoObject) const
{
	return DelegateRegistry != nullptr ? DelegateRegistry->AddReference(InAddress, InDelegate, InMonoObject) : false;
}

bool FCSharpEnvironment::AddBindingReference(void* InBinding, MonoObject* InMonoObject) const
{
	return BindingRegistry != nullptr ? BindingRegistry->AddReference(InBinding, InMonoObject) : false;
}
