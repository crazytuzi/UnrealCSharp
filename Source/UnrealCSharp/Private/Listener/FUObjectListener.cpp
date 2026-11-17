#include "Listener/FUObjectListener.h"
#include "Environment/FCSharpEnvironment.h"
#include "Delegate/FUnrealCSharpModuleDelegates.h"

FUObjectListener::FUObjectListener()
{
	OnUnrealCSharpModuleActiveDelegateHandle = FUnrealCSharpModuleDelegates::GetOnUnrealCSharpModuleActive().
		AddRaw(this, &FUObjectListener::OnUnrealCSharpModuleActive);

	OnUnrealCSharpModuleInActiveDelegateHandle = FUnrealCSharpModuleDelegates::GetOnUnrealCSharpModuleInActive().
		AddRaw(this, &FUObjectListener::OnUnrealCSharpModuleInActive);
}

FUObjectListener::~FUObjectListener()
{
	RemoveListeners();

	if (OnUnrealCSharpModuleActiveDelegateHandle.IsValid())
	{
		FUnrealCSharpModuleDelegates::GetOnUnrealCSharpModuleActive().
			Remove(OnUnrealCSharpModuleActiveDelegateHandle);
	}

	if (OnUnrealCSharpModuleInActiveDelegateHandle.IsValid())
	{
		FUnrealCSharpModuleDelegates::GetOnUnrealCSharpModuleInActive().
			Remove(OnUnrealCSharpModuleInActiveDelegateHandle);
	}
}

void FUObjectListener::AddListeners()
{
	if (bIsRegistered)
	{
		return;
	}

	bIsRegistered = true;

	GUObjectArray.AddUObjectCreateListener(this);

	GUObjectArray.AddUObjectDeleteListener(this);
}

void FUObjectListener::RemoveListeners()
{
	if (!bIsRegistered)
	{
		return;
	}

	bIsRegistered = false;

	GUObjectArray.RemoveUObjectCreateListener(this);

	GUObjectArray.RemoveUObjectDeleteListener(this);
}

void FUObjectListener::OnUnrealCSharpModuleActive()
{
	AddListeners();
}

void FUObjectListener::OnUnrealCSharpModuleInActive()
{
	RemoveListeners();
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
	RemoveListeners();

	FCSharpEnvironment::GetEnvironment().OnUObjectArrayShutdown();
}
