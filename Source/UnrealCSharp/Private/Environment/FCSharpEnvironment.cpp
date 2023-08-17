#include "Environment/FCSharpEnvironment.h"
#include "Registry/FCSharpBind.h"
#include "CoreMacro/Macro.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Delegate/FUnrealCSharpModuleDelegates.h"
#include "Log/UnrealCSharpLog.h"
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

	ClassRegistry = new FClassRegistry();

	ReferenceRegistry = new FReferenceRegistry();

	ObjectRegistry = new FObjectRegistry();

	StructRegistry = new FStructRegistry();

	ContainerRegistry = new FContainerRegistry();

	DelegateRegistry = new FDelegateRegistry();

	MultiRegistry = new FMultiRegistry();

	MixinRegistry = new FMixinRegistry();

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

	if (MixinRegistry != nullptr)
	{
		delete MixinRegistry;

		MixinRegistry = nullptr;
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
			DeleteClassDescriptor(InClass);
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

FClassDescriptor* FCSharpEnvironment::NewClassDescriptor(const FDomain* InDomain, UStruct* InStruct) const
{
	return ClassRegistry != nullptr ? ClassRegistry->NewClassDescriptor(InDomain, InStruct) : nullptr;
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

FFunctionDescriptor* FCSharpEnvironment::GetFunctionDescriptor(const UStruct* InStruct,
                                                               MonoString* InFunctionName) const
{
	return ClassRegistry != nullptr ? ClassRegistry->GetFunctionDescriptor(Domain, InStruct, InFunctionName) : nullptr;
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

FPropertyDescriptor* FCSharpEnvironment::GetPropertyDescriptor(const UStruct* InStruct,
                                                               MonoString* InPropertyName) const
{
	return ClassRegistry != nullptr ? ClassRegistry->GetPropertyDescriptor(Domain, InStruct, InPropertyName) : nullptr;
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

bool FCSharpEnvironment::AddStructReference(UScriptStruct* InScriptStruct, const void* InOwner, const void* InStruct,
                                            MonoObject* InMonoObject, const bool bNeedFree) const
{
	return StructRegistry != nullptr
		       ? StructRegistry->AddReference(InScriptStruct, InOwner, InStruct, InMonoObject, bNeedFree)
		       : false;
}

MonoObject* FCSharpEnvironment::GetObject(const void* InOwner, const void* InStruct) const
{
	return StructRegistry != nullptr ? StructRegistry->GetObject(InOwner, InStruct) : nullptr;
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

FGarbageCollectionHandle FCSharpEnvironment::GetGarbageCollectionHandle(void* InAddress, const int32 InOffset) const
{
	const auto Owner = static_cast<uint8*>(InAddress) - InOffset;

	auto OwnerGarbageCollectionHandle = ObjectRegistry != nullptr
		                                    ? ObjectRegistry->GetGarbageCollectionHandle(
			                                    reinterpret_cast<UObject*>(Owner))
		                                    : FGarbageCollectionHandle();

	if (!OwnerGarbageCollectionHandle.IsValid())
	{
		OwnerGarbageCollectionHandle = StructRegistry != nullptr
			                               ? StructRegistry->GetGarbageCollectionHandle(InAddress, Owner)
			                               : FGarbageCollectionHandle();
	}

	return OwnerGarbageCollectionHandle;
}

MonoObject* FCSharpEnvironment::GetContainerObject(const void* InAddress) const
{
	return ContainerRegistry != nullptr ? ContainerRegistry->GetObject(InAddress) : nullptr;
}

bool FCSharpEnvironment::AddContainerReference(void* InAddress, void* InContainer, MonoObject* InMonoObject) const
{
	return ContainerRegistry != nullptr ? ContainerRegistry->AddReference(InAddress, InContainer, InMonoObject) : false;
}

bool FCSharpEnvironment::AddContainerReference(const FGarbageCollectionHandle& InOwner, void* InAddress,
                                               void* InContainer, MonoObject* InMonoObject) const
{
	return ContainerRegistry != nullptr
		       ? ContainerRegistry->AddReference(InOwner, InAddress, InContainer, InMonoObject)
		       : false;
}

bool FCSharpEnvironment::RemoveContainerReference(const FGarbageCollectionHandle& InGarbageCollectionHandle) const
{
	return ContainerRegistry != nullptr ? ContainerRegistry->RemoveReference(InGarbageCollectionHandle) : false;
}

MonoObject* FCSharpEnvironment::GetDelegateObject(const void* InAddress) const
{
	return DelegateRegistry != nullptr ? DelegateRegistry->GetObject(InAddress) : nullptr;
}

bool FCSharpEnvironment::AddDelegateReference(void* InAddress, void* InDelegate, MonoObject* InMonoObject) const
{
	return DelegateRegistry != nullptr
		       ? DelegateRegistry->AddReference(InAddress, InDelegate, InMonoObject)
		       : false;
}

bool FCSharpEnvironment::AddDelegateReference(const FGarbageCollectionHandle& InOwner, void* InAddress,
                                              void* InDelegate, MonoObject* InMonoObject) const
{
	return DelegateRegistry != nullptr
		       ? DelegateRegistry->AddReference(InOwner, InAddress, InDelegate, InMonoObject)
		       : false;
}

bool FCSharpEnvironment::RemoveDelegateReference(const FGarbageCollectionHandle& InGarbageCollectionHandle) const
{
	return DelegateRegistry != nullptr ? DelegateRegistry->RemoveReference(InGarbageCollectionHandle) : false;
}

MonoObject* FCSharpEnvironment::GetBinding(const void* InObject) const
{
	return BindingRegistry != nullptr ? BindingRegistry->GetObject(InObject) : nullptr;
}

bool FCSharpEnvironment::AddBindingReference(MonoObject* InMonoObject, const void* InObject, const bool bNeedFree) const
{
	return BindingRegistry != nullptr ? BindingRegistry->AddReference(InObject, InMonoObject, bNeedFree) : false;
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
