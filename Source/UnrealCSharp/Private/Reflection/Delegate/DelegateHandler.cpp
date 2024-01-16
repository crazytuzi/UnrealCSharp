#include "Reflection/Delegate/DelegateHandler.h"

void UDelegateHandler::ProcessEvent(UFunction* Function, void* Parms)
{
	if (Function != nullptr && Function->GetName() == TEXT("CSharpCallBack"))
	{
		if (DelegateDescriptor != nullptr)
		{
			if (const auto Delegate = static_cast<MonoObject*>(DelegateGarbageCollectionHandle))
			{
				DelegateDescriptor->CallDelegate(Delegate, Parms);
			}
		}
	}
	else
	{
		UObject::ProcessEvent(Function, Parms);
	}
}

void UDelegateHandler::CSharpCallBack()
{
}

void UDelegateHandler::Initialize(FScriptDelegate* InScriptDelegate, UFunction* InSignatureFunction)
{
	bNeedFree = InScriptDelegate == nullptr;

	ScriptDelegate = InScriptDelegate != nullptr ? InScriptDelegate : new FScriptDelegate();

	DelegateDescriptor = new FCSharpDelegateDescriptor(InSignatureFunction);
}

void UDelegateHandler::Deinitialize()
{
	if (DelegateGarbageCollectionHandle.IsValid())
	{
		FGarbageCollectionHandle::Free(DelegateGarbageCollectionHandle);
	}

	if (ScriptDelegate != nullptr)
	{
		if (bNeedFree)
		{
			ScriptDelegate->Unbind();

			delete ScriptDelegate;
		}

		ScriptDelegate = nullptr;
	}

	if (DelegateDescriptor != nullptr)
	{
		delete DelegateDescriptor;

		DelegateDescriptor = nullptr;
	}
}

void UDelegateHandler::Bind(MonoObject* InDelegate)
{
	if (ScriptDelegate != nullptr)
	{
		if (!ScriptDelegate->IsBound())
		{
			ScriptDelegate->BindUFunction(this, TEXT("CSharpCallBack"));
		}
	}

	DelegateGarbageCollectionHandle = FGarbageCollectionHandle::NewRef(InDelegate, true);
}

bool UDelegateHandler::IsBound() const
{
	return ScriptDelegate != nullptr ? ScriptDelegate->IsBound() : false;
}

void UDelegateHandler::UnBind()
{
	if (ScriptDelegate != nullptr)
	{
		ScriptDelegate->Unbind();
	}

	if (DelegateGarbageCollectionHandle.IsValid())
	{
		FGarbageCollectionHandle::Free(DelegateGarbageCollectionHandle);
	}
}

void UDelegateHandler::Clear()
{
	if (ScriptDelegate != nullptr)
	{
		ScriptDelegate->Clear();
	}

	if (DelegateGarbageCollectionHandle.IsValid())
	{
		FGarbageCollectionHandle::Free(DelegateGarbageCollectionHandle);
	}
}

void UDelegateHandler::Execute(MonoObject** ReturnValue, MonoObject** OutValue, MonoArray* InValue) const
{
	if (ScriptDelegate != nullptr)
	{
		if (ScriptDelegate->IsBound())
		{
			if (DelegateDescriptor != nullptr)
			{
				DelegateDescriptor->ProcessDelegate(ScriptDelegate, ReturnValue, OutValue, InValue);
			}
		}
	}
}

UObject* UDelegateHandler::GetUObject() const
{
	return ScriptDelegate != nullptr ? ScriptDelegate->GetUObject() : nullptr;
}

FName UDelegateHandler::GetFunctionName() const
{
	return ScriptDelegate != nullptr ? ScriptDelegate->GetFunctionName() : NAME_None;
}

UFunction* UDelegateHandler::GetCallBack() const
{
	return FindFunction(TEXT("CSharpCallBack"));
}
