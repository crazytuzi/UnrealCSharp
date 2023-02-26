#include "Reflection/Delegate/FMulticastDelegateHelper.h"

FMulticastDelegateHelper::FMulticastDelegateHelper(FMulticastScriptDelegate* InMulticastDelegate,
                                                   UFunction* InSignatureFunction):
	MulticastDelegateHandler(nullptr)
{
	MulticastDelegateHandler = NewObject<UMulticastDelegateHandler>();

	MulticastDelegateHandler->AddToRoot();

	MulticastDelegateHandler->Initialize(InMulticastDelegate, InSignatureFunction);
}

FMulticastDelegateHelper::~FMulticastDelegateHelper()
{
	Deinitialize();
}

void FMulticastDelegateHelper::Initialize()
{
}

void FMulticastDelegateHelper::Deinitialize()
{
	if (MulticastDelegateHandler != nullptr)
	{
		MulticastDelegateHandler->Deinitialize();
		
		MulticastDelegateHandler->RemoveFromRoot();

		MulticastDelegateHandler = nullptr;
	}
}

bool FMulticastDelegateHelper::IsBound() const
{
	return MulticastDelegateHandler != nullptr ? MulticastDelegateHandler->IsBound() : false;
}

bool FMulticastDelegateHelper::Contains(MonoObject* InMulticastDelegate) const
{
	return MulticastDelegateHandler != nullptr ? MulticastDelegateHandler->Contains(InMulticastDelegate) : false;
}

void FMulticastDelegateHelper::Add(MonoObject* InMulticastDelegate) const
{
	if (MulticastDelegateHandler != nullptr)
	{
		MulticastDelegateHandler->Add(InMulticastDelegate);
	}
}

void FMulticastDelegateHelper::AddUnique(MonoObject* InMulticastDelegate) const
{
	if (MulticastDelegateHandler != nullptr)
	{
		MulticastDelegateHandler->AddUnique(InMulticastDelegate);
	}
}

void FMulticastDelegateHelper::Remove(MonoObject* InMulticastDelegate) const
{
	if (MulticastDelegateHandler != nullptr)
	{
		MulticastDelegateHandler->Remove(InMulticastDelegate);
	}
}

void FMulticastDelegateHelper::RemoveAll(MonoObject* InObject) const
{
	if (MulticastDelegateHandler != nullptr)
	{
		MulticastDelegateHandler->RemoveAll(InObject);
	}
}

void FMulticastDelegateHelper::Clear() const
{
	if (MulticastDelegateHandler != nullptr)
	{
		MulticastDelegateHandler->Clear();
	}
}

void FMulticastDelegateHelper::Broadcast(MonoObject** OutValue, MonoArray* InValue) const
{
	if (MulticastDelegateHandler != nullptr)
	{
		MulticastDelegateHandler->Broadcast(OutValue, InValue);
	}
}
