#include "Environment/FCSharpEnvironment.h"
#include "Registry/FContainerRegistry.h"
#include "Registry/FDelegateRegistry.h"
#include "Registry/FBindingRegistry.h"
#include "Registry/FCSharpBind.h"
#include "CoreMacro/AccessPrivateMacro.h"
#include "Delegate/FUnrealCSharpModuleDelegates.h"
#include "Log/UnrealCSharpLog.h"
#include <signal.h>
#include "UEVersion.h"

ACCESS_PRIVATE_MEMBER_PROPERTY(UObjectBase, ObjectFlags, EObjectFlags)

#if PLATFORM_MAC
TMap<int32, struct sigaction> SignalActions;
#endif

void SignalHandler(int32 Signal)
{
	UE_LOG(LogUnrealCSharp, Error, TEXT("%s"), *FDomain::GetTraceback());

	GLog->Flush();

#if PLATFORM_MAC
	sigaction(Signal, &SignalActions[Signal], nullptr);
#endif
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
	Domain = new FDomain();

	DynamicRegistry = new FDynamicRegistry();

	CSharpBind = new FCSharpBind();

	ClassRegistry = new FClassRegistry();

	ReferenceRegistry = new FReferenceRegistry();

	ObjectRegistry = new FObjectRegistry();

	StructRegistry = new FStructRegistry();

	ContainerRegistry = new FContainerRegistry();

	DelegateRegistry = new FDelegateRegistry();

	MultiRegistry = new FMultiRegistry();

	StringRegistry = new FStringRegistry();

	BindingRegistry = new FBindingRegistry();

#if UE_F_OPTIONAL_PROPERTY
	OptionalRegistry = new FOptionalRegistry();
#endif

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
#if PLATFORM_MAC
		struct sigaction SigAction;

		FMemory::Memzero(&SigAction, sizeof(struct sigaction));

		SigAction.sa_handler = SignalHandler;

		sigemptyset(&SigAction.sa_mask);

		if (!SignalActions.Contains(SignalType))
		{
			sigaction(SignalType, &SigAction, &SignalActions.Add(SignalType));
		}
		else
		{
			sigaction(SignalType, &SigAction, nullptr);
		}
#else
		signal(SignalType, SignalHandler);
#endif
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

#if UE_F_OPTIONAL_PROPERTY
	if (OptionalRegistry != nullptr)
	{
		delete OptionalRegistry;

		OptionalRegistry = nullptr;
	}
#endif

	if (BindingRegistry != nullptr)
	{
		delete BindingRegistry;

		BindingRegistry = nullptr;
	}

	if (StringRegistry != nullptr)
	{
		delete StringRegistry;

		StringRegistry = nullptr;
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

	if (DynamicRegistry != nullptr)
	{
		delete DynamicRegistry;

		DynamicRegistry = nullptr;
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

void FCSharpEnvironment::NotifyUObjectCreated(const UObjectBase* Object, int32 Index)
{
	if (const auto InObject = static_cast<UObject*>(const_cast<UObjectBase*>(Object)))
	{
		if (InObject->HasAnyFlags(EObjectFlags::RF_ClassDefaultObject))
		{
			FScopeLock Lock(&CriticalSection);

			AsyncLoadingObjectArray.Add(InObject);

			return;
		}

		if (IsInGameThread())
		{
			Bind<true>(InObject);
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
		if (const auto InStruct = Cast<UStruct>(InObject))
		{
			RemoveClassDescriptor(InStruct);
		}
		else
		{
			(void)RemoveObjectReference(InObject);
		}

		{
			FScopeLock Lock(&CriticalSection);

			AsyncLoadingObjectArray.Remove(InObject);
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

			if (Object->*TAccessPrivate<UObjectBase_ObjectFlags>::Value & ~RF_AllFlags ||
				Object->HasAnyFlags(RF_NeedPostLoad) ||
				Object->HasAnyInternalFlags(
#if UE_E_INTERNAL_OBJECT_FLAGS_ASYNC_LOADING
					EInternalObjectFlags_AsyncLoading
#else
					EInternalObjectFlags::AsyncLoading
#endif
					| EInternalObjectFlags::Async) ||
				Object->GetClass()->HasAnyInternalFlags(
#if UE_E_INTERNAL_OBJECT_FLAGS_ASYNC_LOADING
					EInternalObjectFlags_AsyncLoading
#else
					EInternalObjectFlags::AsyncLoading
#endif
					| EInternalObjectFlags::Async))
			{
				continue;
			}

			PendingBindObjects.Add(Object);

			RemovedIndexes.Add(i);
		}
	}

	{
		FScopeLock Lock(&CriticalSection);

		for (const auto RemovedIndex : RemovedIndexes)
		{
			AsyncLoadingObjectArray.RemoveAt(RemovedIndex);
		}
	}

	for (const auto& PendingBindObject : PendingBindObjects)
	{
		if (PendingBindObject->HasAnyFlags(EObjectFlags::RF_ClassDefaultObject))
		{
			FCSharpBind::BindClassDefaultObject(PendingBindObject);
		}
		else
		{
			Bind<true>(PendingBindObject);
		}

		if (const auto FoundManagedHandle = GetObject(PendingBindObject);
			IManagedHandleIsValid(FoundManagedHandle))
		{
			if (const auto FoundClass = FReflectionRegistry::Get().GetClass(PendingBindObject->GetClass()))
			{
				FoundClass->ConstructorObject(FoundManagedHandle);
			}
		}
	}
}

IManagedObject FCSharpEnvironment::Bind(UObject* Object) const
{
	return FCSharpBind::Bind(Object);
}

IManagedObject FCSharpEnvironment::Bind(const UObject* Object) const
{
	return Bind(const_cast<UObject*>(Object));
}

IManagedObject FCSharpEnvironment::Bind(UClass* Class) const
{
	return FCSharpBind::Bind(Class);
}

bool FCSharpEnvironment::Bind(const IManagedObject InManagedObject, const FName& InStructName) const
{
	return FCSharpBind::Bind(InManagedObject, InStructName);
}

FClassDescriptor* FCSharpEnvironment::GetClassDescriptor(const UStruct* InStruct) const
{
	return ClassRegistry != nullptr ? ClassRegistry->GetClassDescriptor(InStruct) : nullptr;
}

FClassDescriptor* FCSharpEnvironment::GetClassDescriptor(const FName& InClassName) const
{
	return ClassRegistry != nullptr ? ClassRegistry->GetClassDescriptor(InClassName) : nullptr;
}

FClassDescriptor* FCSharpEnvironment::AddClassDescriptor(UStruct* InStruct) const
{
	return ClassRegistry != nullptr ? ClassRegistry->AddClassDescriptor(InStruct) : nullptr;
}

void FCSharpEnvironment::RemoveClassDescriptor(const UStruct* InStruct) const
{
	if (ClassRegistry != nullptr)
	{
		ClassRegistry->RemoveClassDescriptor(InStruct);
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

void FCSharpEnvironment::AddPropertyHash(const uint32 InPropertyHash, FClassDescriptor* InClassDescriptor,
                                         FProperty* InProperty) const
{
	if (ClassRegistry != nullptr)
	{
		ClassRegistry->AddPropertyHash(InPropertyHash, InClassDescriptor, InProperty);
	}
}

void FCSharpEnvironment::RemovePropertyDescriptor(const uint32 InPropertyHash) const
{
	if (ClassRegistry != nullptr)
	{
		ClassRegistry->RemovePropertyDescriptor(InPropertyHash);
	}
}

bool FCSharpEnvironment::AddObjectReference(const FClassReflection* InClass, UObject* InObject,
                                            const IManagedHandle InManagedHandle) const
{
	return ObjectRegistry != nullptr ? ObjectRegistry->AddReference(InClass, InObject, InManagedHandle) : false;
}

IManagedHandle FCSharpEnvironment::GetObject(const UObject* InObject) const
{
	return ObjectRegistry != nullptr ? ObjectRegistry->GetObject(InObject) : InvalidManagedHandle;
}

bool FCSharpEnvironment::RemoveObjectReference(const UObject* InObject) const
{
	return ObjectRegistry != nullptr ? ObjectRegistry->RemoveReference(InObject) : false;
}

bool FCSharpEnvironment::RemoveObjectReference(const IManagedHandle InManagedHandle) const
{
	return ObjectRegistry != nullptr ? ObjectRegistry->RemoveReference(InManagedHandle) : false;
}

bool FCSharpEnvironment::AddStructReference(const IManagedHandle InOwner, UScriptStruct* InScriptStruct,
                                            const void* InStruct, const IManagedHandle InManagedHandle) const
{
	return StructRegistry != nullptr
		       ? StructRegistry->AddReference(InOwner, InScriptStruct, InStruct, InManagedHandle)
		       : false;
}

IManagedHandle FCSharpEnvironment::GetObject(UScriptStruct* InScriptStruct, const void* InStruct) const
{
	return StructRegistry != nullptr ? StructRegistry->GetObject(InScriptStruct, InStruct) : InvalidManagedHandle;
}

bool FCSharpEnvironment::RemoveStructReference(const IManagedHandle InManagedHandle) const
{
	return StructRegistry != nullptr ? StructRegistry->RemoveReference(InManagedHandle) : false;
}

IManagedHandle FCSharpEnvironment::GeManagedHandle(const UObject* InObject) const
{
	return ObjectRegistry != nullptr
		       ? ObjectRegistry->GetManagedHandle(InObject)
		       : IManagedHandle();
}

IManagedHandle FCSharpEnvironment::GeManagedHandle(void* InAddress, const FProperty* InProperty) const
{
	const auto Owner = static_cast<uint8*>(InAddress) - InProperty->GetOffset_ForInternal();

	if (InProperty->GetOwnerClass())
	{
		return GeManagedHandle(reinterpret_cast<UObject*>(Owner));
	}
	else
	{
		return StructRegistry != nullptr
			       ? StructRegistry->GetManagedHandle(InProperty->GetOwner<UScriptStruct>(), Owner)
			       : IManagedHandle();
	}
}

IManagedHandle FCSharpEnvironment::GetBinding(void* InObject) const
{
	return BindingRegistry != nullptr ? BindingRegistry->GetObject(InObject) : InvalidManagedHandle;
}

bool FCSharpEnvironment::RemoveBindingReference(const IManagedHandle InManagedHandle) const
{
	return BindingRegistry != nullptr ? BindingRegistry->RemoveReference(InManagedHandle) : false;
}

#if UE_F_OPTIONAL_PROPERTY
FOptionalHelper* FCSharpEnvironment::GetOptional(const IManagedHandle InManagedHandle) const
{
	return OptionalRegistry != nullptr
		       ? OptionalRegistry->GetOptional(InManagedHandle)
		       : nullptr;
}

bool FCSharpEnvironment::RemoveOptionalReference(const IManagedHandle InManagedHandle) const
{
	return OptionalRegistry != nullptr ? OptionalRegistry->RemoveReference(InManagedHandle) : false;
}
#endif

bool FCSharpEnvironment::AddReference(const IManagedHandle InOwner, FReference* InReference) const
{
	return ReferenceRegistry != nullptr ? ReferenceRegistry->AddReference(InOwner, InReference) : false;
}

bool FCSharpEnvironment::RemoveReference(const IManagedHandle InOwner) const
{
	return ReferenceRegistry != nullptr ? ReferenceRegistry->RemoveReference(InOwner) : false;
}

bool FCSharpEnvironment::AddReference(UObject* InObject) const
{
	return ReferenceRegistry != nullptr ? ReferenceRegistry->AddReference(InObject) : false;
}

bool FCSharpEnvironment::RemoveReference(UObject* InObject) const
{
	return ReferenceRegistry != nullptr ? ReferenceRegistry->RemoveReference(InObject) : false;
}

FCSharpBind* FCSharpEnvironment::GetBind() const
{
	return CSharpBind;
}
