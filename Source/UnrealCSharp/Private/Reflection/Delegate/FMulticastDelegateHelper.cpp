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

bool FMulticastDelegateHelper::Contains(UObject* InObject, MonoMethod* InMonoMethod) const
{
	return MulticastDelegateHandler != nullptr ? MulticastDelegateHandler->Contains(InObject, InMonoMethod) : false;
}

void FMulticastDelegateHelper::Add(UObject* InObject, MonoMethod* InMonoMethod) const
{
	if (MulticastDelegateHandler != nullptr)
	{
		MulticastDelegateHandler->Add(InObject, InMonoMethod);
	}
}

void FMulticastDelegateHelper::AddUnique(UObject* InObject, MonoMethod* InMonoMethod) const
{
	if (MulticastDelegateHandler != nullptr)
	{
		MulticastDelegateHandler->AddUnique(InObject, InMonoMethod);
	}
}

void FMulticastDelegateHelper::Remove(UObject* InObject, MonoMethod* InMonoMethod) const
{
	if (MulticastDelegateHandler != nullptr)
	{
		MulticastDelegateHandler->Remove(InObject, InMonoMethod);
	}
}

void FMulticastDelegateHelper::RemoveAll(UObject* InObject) const
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

UObject* FMulticastDelegateHelper::GetUObject() const
{
	return MulticastDelegateHandler != nullptr ? MulticastDelegateHandler->GetUObject() : nullptr;
}

FName FMulticastDelegateHelper::GetFunctionName() const
{
	return MulticastDelegateHandler != nullptr ? MulticastDelegateHandler->GetFunctionName() : NAME_None;
}
