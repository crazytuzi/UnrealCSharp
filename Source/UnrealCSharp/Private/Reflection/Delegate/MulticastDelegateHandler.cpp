#include "Reflection/Delegate/MulticastDelegateHandler.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/FunctionMacro.h"
#include "Template/TGetArrayLength.inl"

void UMulticastDelegateHandler::ProcessEvent(UFunction* Function, void* Parms)
{
	if (Function != nullptr && Function->GetName() == FUNCTION_CSHARP_CALLBACK)
	{
		if (DelegateDescriptor != nullptr)
		{
			for (const auto& [Key, Value] : DelegateWrappers)
			{
				DelegateDescriptor->CallDelegate(Key.Get(), Value, Parms);
			}
		}
	}
	else
	{
		UObject::ProcessEvent(Function, Parms);
	}
}

void UMulticastDelegateHandler::CSharpCallBack()
{
}

void UMulticastDelegateHandler::Initialize(FMulticastScriptDelegate* InMulticastScriptDelegate,
                                           UFunction* InSignatureFunction)
{
	bNeedFree = InMulticastScriptDelegate == nullptr;

	MulticastScriptDelegate = InMulticastScriptDelegate != nullptr
		                          ? InMulticastScriptDelegate
		                          : new FMulticastScriptDelegate();

	DelegateDescriptor = new FCSharpDelegateDescriptor(InSignatureFunction);
}

void UMulticastDelegateHandler::Deinitialize()
{
	if (MulticastScriptDelegate != nullptr)
	{
		if (bNeedFree)
		{
			MulticastScriptDelegate->RemoveAll(this);

			delete MulticastScriptDelegate;
		}

		MulticastScriptDelegate = nullptr;
	}

	if (DelegateDescriptor != nullptr)
	{
		delete DelegateDescriptor;

		DelegateDescriptor = nullptr;
	}

	DelegateWrappers.Empty();

	ScriptDelegate.Unbind();
}

bool UMulticastDelegateHandler::IsBound() const
{
	return MulticastScriptDelegate != nullptr ? MulticastScriptDelegate->IsBound() : false;
}

bool UMulticastDelegateHandler::Contains(UObject* InObject, MonoMethod* InMonoMethod) const
{
	return DelegateWrappers.Contains(FDelegateWrapper{InObject, InMonoMethod});
}

void UMulticastDelegateHandler::Add(UObject* InObject, MonoMethod* InMonoMethod)
{
	if (MulticastScriptDelegate != nullptr)
	{
		if (!MulticastScriptDelegate->Contains(ScriptDelegate))
		{
			ScriptDelegate.Unbind();

			ScriptDelegate.BindUFunction(this, *FUNCTION_CSHARP_CALLBACK);

			MulticastScriptDelegate->Add(ScriptDelegate);
		}
	}

	DelegateWrappers.Add({InObject, InMonoMethod});
}

void UMulticastDelegateHandler::AddUnique(UObject* InObject, MonoMethod* InMonoMethod)
{
	if (MulticastScriptDelegate != nullptr)
	{
		if (!MulticastScriptDelegate->Contains(ScriptDelegate))
		{
			ScriptDelegate.Unbind();

			ScriptDelegate.BindUFunction(this, *FUNCTION_CSHARP_CALLBACK);

			MulticastScriptDelegate->Add(ScriptDelegate);
		}
	}

	DelegateWrappers.AddUnique({InObject, InMonoMethod});
}

void UMulticastDelegateHandler::Remove(UObject* InObject, MonoMethod* InMonoMethod)
{
	DelegateWrappers.Remove({InObject, InMonoMethod});

	if (DelegateWrappers.IsEmpty())
	{
		if (MulticastScriptDelegate != nullptr)
		{
			MulticastScriptDelegate->RemoveAll(this);

			ScriptDelegate.Unbind();
		}
	}
}

void UMulticastDelegateHandler::RemoveAll(UObject* InObject)
{
	DelegateWrappers.RemoveAll([InObject](const FDelegateWrapper& Element)
	{
		return Element.Object == InObject;
	});

	if (DelegateWrappers.IsEmpty())
	{
		if (MulticastScriptDelegate != nullptr)
		{
			MulticastScriptDelegate->RemoveAll(this);

			ScriptDelegate.Unbind();
		}
	}
}

void UMulticastDelegateHandler::Clear()
{
	if (MulticastScriptDelegate != nullptr)
	{
		MulticastScriptDelegate->Clear();
	}

	DelegateWrappers.Empty();

	ScriptDelegate.Unbind();
}

UObject* UMulticastDelegateHandler::GetUObject() const
{
	return const_cast<UObject*>(ScriptDelegate.GetUObject());
}

FName UMulticastDelegateHandler::GetFunctionName() const
{
	return ScriptDelegate.GetFunctionName();
}

UFunction* UMulticastDelegateHandler::GetCallBack() const
{
	return FindFunction(*FUNCTION_CSHARP_CALLBACK);
}
