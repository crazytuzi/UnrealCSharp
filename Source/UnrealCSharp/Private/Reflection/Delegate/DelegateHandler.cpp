#include "Reflection/Delegate/DelegateHandler.h"

void UDelegateHandler::ProcessEvent(UFunction* Function, void* Parms)
{
	if (Function != nullptr && Function->GetName() == "CSharpCallBack")
	{
		DelegateDescriptor->CallCSharp(Delegate, Parms);
	}
	else
	{
		UObject::ProcessEvent(Function, Parms);
	}
}

void UDelegateHandler::BeginDestroy()
{
	Deinitialize();

	UObject::BeginDestroy();
}

void UDelegateHandler::CSharpCallBack()
{
}

void UDelegateHandler::Initialize(FScriptDelegate* InScriptDelegate, UFunction* InSignatureFunction)
{
	ScriptDelegate = InScriptDelegate;

	DelegateDescriptor = new FCSharpDelegateDescriptor(InSignatureFunction);
}

void UDelegateHandler::Deinitialize()
{
	if (ScriptDelegate != nullptr)
	{
		// @TODO
		ScriptDelegate->Unbind();

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
			ScriptDelegate->BindUFunction(this, "CSharpCallBack");
		}
	}

	Delegate = InDelegate;
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

	Delegate = nullptr;
}

void UDelegateHandler::Clear()
{
	if (ScriptDelegate != nullptr)
	{
		ScriptDelegate->Clear();
	}

	Delegate = nullptr;
}

void UDelegateHandler::Execute(MonoObject** ReturnValue, MonoObject** OutValue, MonoArray* InValue) const
{
	if (ScriptDelegate != nullptr)
	{
		if (ScriptDelegate->IsBound())
		{
			DelegateDescriptor->CallUnreal(ScriptDelegate, ReturnValue, OutValue, InValue);
		}
	}
}
