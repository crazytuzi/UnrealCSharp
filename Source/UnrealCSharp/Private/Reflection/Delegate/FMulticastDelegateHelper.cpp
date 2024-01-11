#include "Reflection/Delegate/FMulticastDelegateHelper.h"

FMulticastDelegateHelper::FMulticastDelegateHelper()
{
	Initialize(nullptr, nullptr);
}

FMulticastDelegateHelper::FMulticastDelegateHelper(FMulticastScriptDelegate* InMulticastDelegate,
                                                   UFunction* InSignatureFunction)
{
	Initialize(InMulticastDelegate, InSignatureFunction);
}

FMulticastDelegateHelper::~FMulticastDelegateHelper()
{
	Deinitialize();
}

void FMulticastDelegateHelper::Initialize(FMulticastScriptDelegate* InMulticastDelegate, UFunction* InSignatureFunction)
{
	MulticastDelegateHandler = NewObject<UMulticastDelegateHandler>();

	MulticastDelegateHandler->AddToRoot();

	MulticastDelegateHandler->Initialize(InMulticastDelegate,
	                                     InSignatureFunction != nullptr
		                                     ? InSignatureFunction
		                                     : MulticastDelegateHandler->GetCallBack());
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

MonoObject* FMulticastDelegateHelper::Broadcast(MonoObject** OutValue, MonoArray* InValue) const
{
	if (MulticastDelegateHandler != nullptr)
	{
		return MulticastDelegateHandler->Broadcast(OutValue, InValue);
	}

	return nullptr;
}

UObject* FMulticastDelegateHelper::GetUObject() const
{
	return MulticastDelegateHandler != nullptr ? MulticastDelegateHandler->GetUObject() : nullptr;
}

FName FMulticastDelegateHelper::GetFunctionName() const
{
	return MulticastDelegateHandler != nullptr ? MulticastDelegateHandler->GetFunctionName() : NAME_None;
}
