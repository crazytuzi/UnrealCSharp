#include "Reflection/Delegate/FDelegateHelper.h"

FDelegateHelper::FDelegateHelper()
{
	Initialize(nullptr, nullptr);
}

FDelegateHelper::FDelegateHelper(FScriptDelegate* InDelegate, UFunction* InSignatureFunction)
{
	Initialize(InDelegate, InSignatureFunction);
}

FDelegateHelper::~FDelegateHelper()
{
	Deinitialize();
}

void FDelegateHelper::Initialize(FScriptDelegate* InDelegate, UFunction* InSignatureFunction)
{
	DelegateHandler = NewObject<UDelegateHandler>();

	DelegateHandler->AddToRoot();

	DelegateHandler->Initialize(InDelegate,
	                            InSignatureFunction != nullptr
		                            ? InSignatureFunction
		                            : DelegateHandler->GetCallBack());
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

MonoObject* FDelegateHelper::Execute(MonoObject** OutValue, MonoArray* InValue) const
{
	if (DelegateHandler != nullptr)
	{
		return DelegateHandler->Execute(OutValue, InValue);
	}

	return nullptr;
}

UObject* FDelegateHelper::GetUObject() const
{
	return DelegateHandler != nullptr ? DelegateHandler->GetUObject() : nullptr;
}

FName FDelegateHelper::GetFunctionName() const
{
	return DelegateHandler != nullptr ? DelegateHandler->GetFunctionName() : NAME_None;
}
