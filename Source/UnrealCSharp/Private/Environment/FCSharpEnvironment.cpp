#include "Environment/FCSharpEnvironment.h"
#include "Delegate/FUnrealCSharpModuleDelegates.h"
#include "Registry/FCSharpBind.h"
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

	OnUnrealCSharpModuleInActiveDelegateHandle = FUnrealCSharpModuleDelegates::OnUnrealCSharpModuleInActive.AddRaw(
		this, &FCSharpEnvironment::OnUnrealCSharpModuleInActive);
}

void FCSharpEnvironment::Deinitialize()
{
	if (OnUnrealCSharpModuleInActiveDelegateHandle.IsValid())
	{
		FUnrealCSharpModuleDelegates::OnUnrealCSharpModuleInActive.Remove(OnUnrealCSharpModuleInActiveDelegateHandle);
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
			Domain = new FMonoDomain({"", ""});
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
			RemoveReference(InObject);
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

FClassDescriptor* FCSharpEnvironment::GetClassDescriptor(const UClass* InClass) const
{
	return ClassRegistry != nullptr ? ClassRegistry->GetClassDescriptor(InClass) : nullptr;
}

FClassDescriptor* FCSharpEnvironment::NewClassDescriptor(const FMonoDomain* InMonoDomain, UClass* InClass) const
{
	return ClassRegistry != nullptr ? ClassRegistry->NewClassDescriptor(InMonoDomain, InClass) : nullptr;
}

void FCSharpEnvironment::DeleteClassDescriptor(const UClass* InClass) const
{
	if (ClassRegistry != nullptr)
	{
		ClassRegistry->DeleteClassDescriptor(InClass);
	}
}

FFunctionDescriptor* FCSharpEnvironment::GetFunctionDescriptor(const UClass* InClass, const FName& InFunctionName) const
{
	const auto FoundClassDescriptor = GetClassDescriptor(InClass);

	return FoundClassDescriptor != nullptr ? FoundClassDescriptor->GetFunctionDescriptor(InFunctionName) : nullptr;
}

FPropertyDescriptor* FCSharpEnvironment::GetPropertyDescriptor(const UClass* InClass, const FName& InPropertyName) const
{
	const auto FoundClassDescriptor = GetClassDescriptor(InClass);

	return FoundClassDescriptor != nullptr ? FoundClassDescriptor->GetPropertyDescriptor(InPropertyName) : nullptr;
}

bool FCSharpEnvironment::AddReference(UObject* InObject, MonoObject* InMonoObject) const
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

bool FCSharpEnvironment::RemoveReference(const UObject* InObject) const
{
	return ObjectRegistry != nullptr ? ObjectRegistry->RemoveReference(InObject) : nullptr;
}

bool FCSharpEnvironment::RemoveReference(const MonoObject* InMonoObject) const
{
	return ObjectRegistry != nullptr ? ObjectRegistry->RemoveReference(InMonoObject) : nullptr;
}
