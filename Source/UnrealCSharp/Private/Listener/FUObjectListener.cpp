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
