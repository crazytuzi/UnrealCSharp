#include "Reflection/Delegate/FDelegateHelper.h"

FDelegateHelper::FDelegateHelper(FScriptDelegate* InDelegate, UFunction* InSignatureFunction):
	DelegateHandler(nullptr)
{
	DelegateHandler = NewObject<UDelegateHandler>(GWorld);

	DelegateHandler->AddToRoot();

	DelegateHandler->Initialize(InDelegate, InSignatureFunction);
}

FDelegateHelper::~FDelegateHelper()
{
	Deinitialize();
}

void FDelegateHelper::Initialize()
{
}

void FDelegateHelper::Deinitialize()
{
	if (DelegateHandler != nullptr)
	{
		DelegateHandler->Deinitialize();

		DelegateHandler->RemoveFromRoot();

		DelegateHandler = nullptr;
	}
}

void FDelegateHelper::Bind(MonoObject* InDelegate) const
{
	if (DelegateHandler != nullptr)
	{
		DelegateHandler->Bind(InDelegate);
	}
}

bool FDelegateHelper::IsBound() const
{
	return DelegateHandler != nullptr ? DelegateHandler->IsBound() : false;
}

void FDelegateHelper::UnBind() const
{
	if (DelegateHandler != nullptr)
	{
		DelegateHandler->UnBind();
	}
}

void FDelegateHelper::Clear() const
{
	if (DelegateHandler != nullptr)
	{
		DelegateHandler->Clear();
	}
}

void FDelegateHelper::Execute(MonoObject** ReturnValue, MonoObject** OutValue, MonoArray* InValue) const
{
	if (DelegateHandler != nullptr)
	{
		DelegateHandler->Execute(ReturnValue, OutValue, InValue);
	}
}

UObject* FDelegateHelper::GetUObject() const
{
	return DelegateHandler != nullptr ? DelegateHandler->GetUObject() : nullptr;
}

FName FDelegateHelper::GetFunctionName() const
{
	return DelegateHandler != nullptr ? DelegateHandler->GetFunctionName() : NAME_None;
}
