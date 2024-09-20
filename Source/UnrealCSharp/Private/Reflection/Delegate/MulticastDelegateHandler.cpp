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
			for (const auto& [Key, Value, GC] : DelegateWrappers)
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

	for (auto& Delegate : DelegateWrappers) 
	{
		FGarbageCollectionHandle::Free<false>(Delegate.GCHandle);
	}
	DelegateWrappers.Empty();

	ScriptDelegate.Unbind();
}

bool UMulticastDelegateHandler::IsBound() const
{
	return MulticastScriptDelegate != nullptr ? MulticastScriptDelegate->IsBound() : false;
}

bool UMulticastDelegateHandler::Contains(UObject* InObject, MonoObject* InMonoDelegate) const
{
	return DelegateWrappers.Contains(FDelegateWrapper{InObject, InMonoDelegate});
}

void UMulticastDelegateHandler::Add(UObject* InObject, MonoObject* InMonoDelegate)
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
;
	DelegateWrappers.Add({InObject, InMonoDelegate, FGarbageCollectionHandle::NewRef(InMonoDelegate, true) });
}

void UMulticastDelegateHandler::AddUnique(UObject* InObject, MonoObject* InMonoDelegate)
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
	DelegateWrappers.AddUnique({InObject, InMonoDelegate, FGarbageCollectionHandle::NewRef(InMonoDelegate, true) });
}

void UMulticastDelegateHandler::Remove(UObject* InObject, MonoObject* InMonoDelegate)
{
	DelegateWrappers.Remove({InObject, InMonoDelegate});

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
