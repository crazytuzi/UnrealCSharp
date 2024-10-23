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

bool FMulticastDelegateHelper::Contains(UObject* InObject, MonoObject* InMonoDelegate) const
{
	return MulticastDelegateHandler != nullptr ? MulticastDelegateHandler->Contains(InObject, InMonoDelegate) : false;
}

void FMulticastDelegateHelper::Add(UObject* InObject, MonoObject* InMonoDelegate) const
{
	if (MulticastDelegateHandler != nullptr)
	{
		MulticastDelegateHandler->Add(InObject, InMonoDelegate);
	}
}

void FMulticastDelegateHelper::AddUnique(UObject* InObject, MonoObject* InMonoDelegate) const
{
	if (MulticastDelegateHandler != nullptr)
	{
		MulticastDelegateHandler->AddUnique(InObject, InMonoDelegate);
	}
}

void FMulticastDelegateHelper::Remove(UObject* InObject, MonoObject* InMonoObject) const
{
	if (MulticastDelegateHandler != nullptr)
	{
		MulticastDelegateHandler->Remove(InObject, InMonoObject);
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
