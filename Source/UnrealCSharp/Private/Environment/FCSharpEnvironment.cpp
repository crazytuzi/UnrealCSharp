﻿#include "Environment/FCSharpEnvironment.h"
#include "Registry/FContainerRegistry.h"
#include "Registry/FDelegateRegistry.h"
#include "Registry/FBindingRegistry.h"
#include "Registry/FCSharpBind.h"
#include "CoreMacro/Macro.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Delegate/FUnrealCSharpModuleDelegates.h"
#include "Log/UnrealCSharpLog.h"
#include "Setting/UnrealCSharpSetting.h"
#include <signal.h>

void SignalHandler(int32)
{
	UE_LOG(LogUnrealCSharp, Error, TEXT("%s"),
	       *FString(UTF8_TO_TCHAR(FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(
		       FCSharpEnvironment::GetEnvironment().GetDomain()->GetTraceback()))));

	GLog->Flush();
}

FCSharpEnvironment FCSharpEnvironment::Environment;

FCSharpEnvironment::FCSharpEnvironment()
{
	OnUnrealCSharpModuleActiveDelegateHandle = FUnrealCSharpModuleDelegates::OnUnrealCSharpModuleActive.AddRaw(
		this, &FCSharpEnvironment::OnUnrealCSharpModuleActive);

	OnUnrealCSharpModuleInActiveDelegateHandle = FUnrealCSharpModuleDelegates::OnUnrealCSharpModuleInActive.AddRaw(
		this, &FCSharpEnvironment::OnUnrealCSharpModuleInActive);
}

FCSharpEnvironment::~FCSharpEnvironment()
{
	if (OnUnrealCSharpModuleInActiveDelegateHandle.IsValid())
	{
		FUnrealCSharpModuleDelegates::OnUnrealCSharpModuleInActive.Remove(OnUnrealCSharpModuleInActiveDelegateHandle);
	}

	if (OnUnrealCSharpModuleActiveDelegateHandle.IsValid())
	{
		FUnrealCSharpModuleDelegates::OnUnrealCSharpModuleActive.Remove(OnUnrealCSharpModuleActiveDelegateHandle);
	}
}

void FCSharpEnvironment::Initialize()
{
	Domain = new FDomain({
		"",
		FUnrealCSharpFunctionLibrary::GetAssemblyUtilPath() /
		FUnrealCSharpFunctionLibrary::GetAssemblyUtilProjectName() + DLL_SUFFIX,
		{
			FUnrealCSharpFunctionLibrary::GetScriptPath() / FUnrealCSharpFunctionLibrary::GetUEProjectName() +
			DLL_SUFFIX,
			FUnrealCSharpFunctionLibrary::GetScriptPath() / FUnrealCSharpFunctionLibrary::GetGameProjectName() +
			DLL_SUFFIX
		}
	});

	CSharpBind = new FCSharpBind();

	ClassRegistry = new FClassRegistry();

	ReferenceRegistry = new FReferenceRegistry();

	ObjectRegistry = new FObjectRegistry();

	StructRegistry = new FStructRegistry();

	ContainerRegistry = new FContainerRegistry();

	DelegateRegistry = new FDelegateRegistry();

	MultiRegistry = new FMultiRegistry();

	DynamicRegistry = new FDynamicRegistry();

	BindingRegistry = new FBindingRegistry();

	OnAsyncLoadingFlushUpdateHandle = FCoreDelegates::OnAsyncLoadingFlushUpdate.AddRaw(
		this, &FCSharpEnvironment::OnAsyncLoadingFlushUpdate);

	static TSet<int32> SignalTypes = {
		// interrupt
		SIGINT,
		// illegal instruction - invalid function image
		SIGILL,
		// floating point exception
		SIGFPE,
		// segment violation
		SIGSEGV,
		// Software termination signal from kill
		SIGTERM,
#if PLATFORM_WINDOWS
		// Ctrl-Break sequence
		SIGBREAK,
#endif
		// abnormal termination triggered by abort call
		SIGABRT,
	};

	for (const auto SignalType : SignalTypes)
	{
		signal(SignalType, SignalHandler);
	}

	FUnrealCSharpModuleDelegates::OnCSharpEnvironmentInitialize.Broadcast();
}

void FCSharpEnvironment::Deinitialize()
{
	AsyncLoadingObjectArray.Empty();

	if (OnAsyncLoadingFlushUpdateHandle.IsValid())
	{
		FCoreDelegates::OnAsyncLoadingFlushUpdate.Remove(OnAsyncLoadingFlushUpdateHandle);
	}

	if (BindingRegistry != nullptr)
	{
		delete BindingRegistry;

		BindingRegistry = nullptr;
	}

	if (DynamicRegistry != nullptr)
	{
		delete DynamicRegistry;

		DynamicRegistry = nullptr;
	}

	if (MultiRegistry != nullptr)
	{
		delete MultiRegistry;

		MultiRegistry = nullptr;
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

	if (ReferenceRegistry != nullptr)
	{
		delete ReferenceRegistry;

		ReferenceRegistry = nullptr;
	}

	if (ClassRegistry != nullptr)
	{
		delete ClassRegistry;

		ClassRegistry = nullptr;
	}

	if (CSharpBind != nullptr)
	{
		delete CSharpBind;

		CSharpBind = nullptr;
	}

	if (Domain != nullptr)
	{
		delete Domain;

		Domain = nullptr;
	}
}

FCSharpEnvironment& FCSharpEnvironment::GetEnvironment()
{
	return Environment;
}

FDomain* FCSharpEnvironment::GetDomain() const
{
	return Domain;
}

void FCSharpEnvironment::NotifyUObjectCreated(const UObjectBase* Object, int32 Index)
{
	if (const auto InObject = static_cast<UObject*>(const_cast<UObjectBase*>(Object)))
	{
		if (InObject->HasAnyFlags(EObjectFlags::RF_ClassDefaultObject | EObjectFlags::RF_ArchetypeObject))
		{
			if (const auto UnrealCSharpSetting = GetMutableDefault<UUnrealCSharpSetting>())
			{
				for (const auto& BindClass : UnrealCSharpSetting->GetBindClass())
				{
					if (InObject->IsA(BindClass.Class))
					{
						if (BindClass.bNeedMonoClass)
						{
							FScopeLock Lock(&CriticalSection);

							AsyncLoadingObjectArray.Add(InObject);
						}
						else
						{
							Bind(InObject, false);
						}

						return;
					}
				}
			}

			return;
		}

		if (IsInGameThread())
		{
			Bind(InObject, true);
		}
		else
		{
			FScopeLock Lock(&CriticalSection);

			AsyncLoadingObjectArray.Add(InObject);
		}
	}
}

void FCSharpEnvironment::NotifyUObjectDeleted(const UObjectBase* Object, int32 Index)
{
	if (const auto InObject = static_cast<UObject*>(const_cast<UObjectBase*>(Object)))
	{
		if (const auto InClass = Cast<UClass>(InObject))
		{
			RemoveClassDescriptor(InClass);
		}
		else
		{
			(void)RemoveObjectReference(InObject);
		}
	}
}

void FCSharpEnvironment::OnUObjectArrayShutdown()
{
}

void FCSharpEnvironment::OnUnrealCSharpModuleActive()
{
	Initialize();
}

void FCSharpEnvironment::OnUnrealCSharpModuleInActive()
{
	Deinitialize();
}

void FCSharpEnvironment::OnAsyncLoadingFlushUpdate()
{
	TArray<int32> RemovedIndexes;

	TArray<UObject*> PendingBindObjects;

	{
		TArray<FWeakObjectPtr> LocalAsyncLoadingObjectArray;

		{
			FScopeLock Lock(&CriticalSection);

			LocalAsyncLoadingObjectArray.Append(AsyncLoadingObjectArray);
		}

		for (auto i = LocalAsyncLoadingObjectArray.Num() - 1; i >= 0; --i)
		{
			auto ObjectPtr = LocalAsyncLoadingObjectArray[i];

			if (!ObjectPtr.IsValid())
			{
				RemovedIndexes.Add(i);

				continue;
			}

			auto Object = ObjectPtr.Get();

			if (Object->HasAnyFlags(RF_NeedPostLoad)
				|| Object->HasAnyInternalFlags(EInternalObjectFlags::AsyncLoading | EInternalObjectFlags::Async)
				|| Object->GetClass()->HasAnyInternalFlags(
					EInternalObjectFlags::AsyncLoading | EInternalObjectFlags::Async))
			{
				continue;
			}

			PendingBindObjects.Add(Object);

			RemovedIndexes.Add(i);
		}
	}

	{
		FScopeLock Lock(&CriticalSection);

		for (auto i = 0; i < RemovedIndexes.Num(); ++i)
		{
			AsyncLoadingObjectArray.RemoveAt(RemovedIndexes[i]);
		}
	}

	for (auto i = 0; i < PendingBindObjects.Num(); ++i)
	{
		Bind(PendingBindObjects[i], true);
	}
}

MonoObject* FCSharpEnvironment::Bind(UObject* Object) const
{
	return FCSharpBind::Bind(Domain, Object);
}

bool FCSharpEnvironment::Bind(UObject* Object, const bool bNeedMonoClass) const
{
	return FCSharpBind::Bind(Domain, Object, bNeedMonoClass);
}

bool FCSharpEnvironment::Bind(UStruct* InStruct, const bool bNeedMonoClass) const
{
	return FCSharpBind::Bind(Domain, InStruct, bNeedMonoClass);
}

bool FCSharpEnvironment::Bind(MonoObject* InMonoObject, const FName& InStructName) const
{
	return FCSharpBind::Bind(Domain, InMonoObject, InStructName);
}

bool FCSharpEnvironment::Bind(UFunction* InFunction) const
{
	if (ClassRegistry != nullptr)
	{
		const auto Class = Cast<UClass>(InFunction->GetOuter());

		return FCSharpBind::Bind(ClassRegistry->GetClassDescriptor(Class), Class, InFunction);
	}

	return false;
}

FClassDescriptor* FCSharpEnvironment::GetClassDescriptor(const UStruct* InStruct) const
{
	return ClassRegistry != nullptr ? ClassRegistry->GetClassDescriptor(InStruct) : nullptr;
}

FClassDescriptor* FCSharpEnvironment::GetClassDescriptor(const FName& InClassName) const
{
	return ClassRegistry != nullptr ? ClassRegistry->GetClassDescriptor(InClassName) : nullptr;
}

FClassDescriptor* FCSharpEnvironment::AddClassDescriptor(const FDomain* InDomain, UStruct* InStruct) const
{
	return ClassRegistry != nullptr ? ClassRegistry->AddClassDescriptor(InDomain, InStruct) : nullptr;
}

void FCSharpEnvironment::RemoveClassDescriptor(const UStruct* InStruct) const
{
	if (ClassRegistry != nullptr)
	{
		ClassRegistry->RemoveClassDescriptor(InStruct);
	}
}

FFunctionDescriptor* FCSharpEnvironment::GetOrAddFunctionDescriptor(const UStruct* InStruct,
                                                                    const FName& InFunctionName) const
{
	const auto FoundClassDescriptor = GetClassDescriptor(InStruct);

	return FoundClassDescriptor != nullptr ? FoundClassDescriptor->GetOrAddFunctionDescriptor(InFunctionName) : nullptr;
}

FFunctionDescriptor* FCSharpEnvironment::GetFunctionDescriptor(const uint32 InFunctionHash) const
{
	return ClassRegistry != nullptr ? ClassRegistry->GetFunctionDescriptor(InFunctionHash) : nullptr;
}

FFunctionDescriptor* FCSharpEnvironment::GetOrAddFunctionDescriptor(const uint32 InFunctionHash) const
{
	return ClassRegistry != nullptr ? ClassRegistry->GetOrAddFunctionDescriptor(InFunctionHash) : nullptr;
}

void FCSharpEnvironment::AddFunctionDescriptor(const uint32 InFunctionHash,
                                               FFunctionDescriptor* InFunctionDescriptor) const
{
	if (ClassRegistry != nullptr)
	{
		ClassRegistry->AddFunctionDescriptor(InFunctionHash, InFunctionDescriptor);
	}
}

void FCSharpEnvironment::AddFunctionHash(const uint32 InFunctionHash, FClassDescriptor* InClassDescriptor,
                                         const FName& InFunctionName) const
{
	if (ClassRegistry != nullptr)
	{
		ClassRegistry->AddFunctionHash(InFunctionHash, InClassDescriptor, InFunctionName);
	}
}

void FCSharpEnvironment::RemoveFunctionDescriptor(const uint32 InFunctionHash) const
{
	if (ClassRegistry != nullptr)
	{
		ClassRegistry->RemoveFunctionDescriptor(InFunctionHash);
	}
}

FPropertyDescriptor* FCSharpEnvironment::GetOrAddPropertyDescriptor(const uint32 InPropertyHash) const
{
	return ClassRegistry != nullptr ? ClassRegistry->GetOrAddPropertyDescriptor(InPropertyHash) : nullptr;
}

void FCSharpEnvironment::AddPropertyDescriptor(const uint32 InPropertyHash,
                                               FPropertyDescriptor* InPropertyDescriptor) const
{
	if (ClassRegistry != nullptr)
	{
		ClassRegistry->AddPropertyDescriptor(InPropertyHash, InPropertyDescriptor);
	}
}

void FCSharpEnvironment::AddPropertyHash(const uint32 InPropertyHash, FClassDescriptor* InClassDescriptor,
                                         const FName& InPropertyName) const
{
	if (ClassRegistry != nullptr)
	{
		ClassRegistry->AddPropertyHash(InPropertyHash, InClassDescriptor, InPropertyName);
	}
}

void FCSharpEnvironment::RemovePropertyDescriptor(const uint32 InPropertyHash) const
{
	if (ClassRegistry != nullptr)
	{
		ClassRegistry->RemovePropertyDescriptor(InPropertyHash);
	}
}

bool FCSharpEnvironment::AddObjectReference(UObject* InObject, MonoObject* InMonoObject) const
{
	return ObjectRegistry != nullptr ? ObjectRegistry->AddReference(InObject, InMonoObject) : false;
}

MonoObject* FCSharpEnvironment::GetObject(const UObject* InObject) const
{
	return ObjectRegistry != nullptr ? ObjectRegistry->GetObject(InObject) : nullptr;
}

bool FCSharpEnvironment::RemoveObjectReference(const UObject* InObject) const
{
	return ObjectRegistry != nullptr ? ObjectRegistry->RemoveReference(InObject) : false;
}

bool FCSharpEnvironment::RemoveObjectReference(const FGarbageCollectionHandle& InGarbageCollectionHandle) const
{
	return ObjectRegistry != nullptr ? ObjectRegistry->RemoveReference(InGarbageCollectionHandle) : false;
}

bool FCSharpEnvironment::AddStructReference(UScriptStruct* InScriptStruct, const void* InStruct,
                                            MonoObject* InMonoObject, const bool bNeedFree) const
{
	return StructRegistry != nullptr
		       ? StructRegistry->AddReference(InScriptStruct, InStruct, InMonoObject, bNeedFree)
		       : false;
}

bool FCSharpEnvironment::AddStructReference(const FGarbageCollectionHandle& InOwner, UScriptStruct* InScriptStruct,
                                            const void* InStruct, MonoObject* InMonoObject) const
{
	return StructRegistry != nullptr
		       ? StructRegistry->AddReference(InOwner, InScriptStruct, InStruct, InMonoObject)
		       : false;
}

MonoObject* FCSharpEnvironment::GetObject(UScriptStruct* InScriptStruct, const void* InStruct) const
{
	return StructRegistry != nullptr ? StructRegistry->GetObject(InScriptStruct, InStruct) : nullptr;
}

void* FCSharpEnvironment::GetStruct(const FGarbageCollectionHandle& InGarbageCollectionHandle) const
{
	return StructRegistry != nullptr ? StructRegistry->GetStruct(InGarbageCollectionHandle) : nullptr;
}

void* FCSharpEnvironment::GetStruct(const MonoObject* InMonoObject) const
{
	return StructRegistry != nullptr ? StructRegistry->GetStruct(InMonoObject) : nullptr;
}

bool FCSharpEnvironment::RemoveStructReference(const FGarbageCollectionHandle& InGarbageCollectionHandle) const
{
	return StructRegistry != nullptr ? StructRegistry->RemoveReference(InGarbageCollectionHandle) : false;
}

FGarbageCollectionHandle FCSharpEnvironment::GetGarbageCollectionHandle(const UObject* InObject) const
{
	return ObjectRegistry != nullptr
		       ? ObjectRegistry->GetGarbageCollectionHandle(InObject)
		       : FGarbageCollectionHandle();
}

FGarbageCollectionHandle FCSharpEnvironment::GetGarbageCollectionHandle(
	void* InAddress, const FProperty* InProperty) const
{
	const auto Owner = static_cast<uint8*>(InAddress) - InProperty->GetOffset_ForInternal();

	if (InProperty->GetOwnerClass())
	{
		return GetGarbageCollectionHandle(reinterpret_cast<UObject*>(Owner));
	}
	else
	{
		return StructRegistry != nullptr
			       ? StructRegistry->GetGarbageCollectionHandle(InProperty->GetOwner<UScriptStruct>(), Owner)
			       : FGarbageCollectionHandle();
	}
}

MonoObject* FCSharpEnvironment::GetBinding(void* InObject) const
{
	return BindingRegistry != nullptr ? BindingRegistry->GetObject(InObject) : nullptr;
}

bool FCSharpEnvironment::RemoveBindingReference(const FGarbageCollectionHandle& InGarbageCollectionHandle) const
{
	return BindingRegistry != nullptr ? BindingRegistry->RemoveReference(InGarbageCollectionHandle) : false;
}

bool FCSharpEnvironment::AddReference(const FGarbageCollectionHandle& InOwner, FReference* InReference) const
{
	return ReferenceRegistry != nullptr ? ReferenceRegistry->AddReference(InOwner, InReference) : false;
}

bool FCSharpEnvironment::RemoveReference(const FGarbageCollectionHandle& InOwner) const
{
	return ReferenceRegistry != nullptr ? ReferenceRegistry->RemoveReference(InOwner) : false;
}
