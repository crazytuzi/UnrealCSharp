#include "Listener/FUObjectListener.h"
#include "Environment/FCSharpEnvironment.h"
#include "Delegate/FUnrealCSharpModuleDelegates.h"

FUObjectListener::FUObjectListener()
{
	OnUnrealCSharpModuleActiveDelegateHandle = FUnrealCSharpModuleDelegates::OnUnrealCSharpModuleActive.AddRaw(
		this, &FUObjectListener::OnUnrealCSharpModuleActive);

	OnUnrealCSharpModuleInActiveDelegateHandle = FUnrealCSharpModuleDelegates::OnUnrealCSharpModuleInActive.AddRaw(
		this, &FUObjectListener::OnUnrealCSharpModuleInActive);
}

FUObjectListener::~FUObjectListener()
{
	if (OnUnrealCSharpModuleActiveDelegateHandle.IsValid())
	{
		FUnrealCSharpModuleDelegates::OnUnrealCSharpModuleActive.Remove(OnUnrealCSharpModuleActiveDelegateHandle);
	}

	if (OnUnrealCSharpModuleInActiveDelegateHandle.IsValid())
	{
		FUnrealCSharpModuleDelegates::OnUnrealCSharpModuleInActive.Remove(OnUnrealCSharpModuleInActiveDelegateHandle);
	}
}

void FUObjectListener::OnUnrealCSharpModuleActive()
{
	GUObjectArray.AddUObjectCreateListener(this);

	GUObjectArray.AddUObjectDeleteListener(this);
}

void FUObjectListener::OnUnrealCSharpModuleInActive()
{
	GUObjectArray.RemoveUObjectCreateListener(this);

	GUObjectArray.RemoveUObjectDeleteListener(this);
}

void FUObjectListener::NotifyUObjectCreated(const UObjectBase* Object, const int32 Index)
{
	FCSharpEnvironment::GetEnvironment().NotifyUObjectCreated(Object, Index);
}

void FUObjectListener::NotifyUObjectDeleted(const UObjectBase* Object, const int32 Index)
{
	FCSharpEnvironment::GetEnvironment().NotifyUObjectDeleted(Object, Index);
}

void FUObjectListener::OnUObjectArrayShutdown()
{
	FCSharpEnvironment::GetEnvironment().OnUObjectArrayShutdown();
}
