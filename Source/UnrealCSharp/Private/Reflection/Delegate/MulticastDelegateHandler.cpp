// Fill out your copyright notice in the Description page of Project Settings.


#include "Reflection/Delegate/MulticastDelegateHandler.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/ClassMacro.h"
#include "Macro/FunctionMacro.h"
#include "Macro/NamespaceMacro.h"

void UMulticastDelegateHandler::ProcessEvent(UFunction* Function, void* Parms)
{
	if (Function != nullptr && Function->GetName() == "CSharpCallBack")
	{
		if (DelegateDescriptor != nullptr)
		{
			for (const auto& Delegate : Delegates)
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

void UMulticastDelegateHandler::CSharpCallBack()
{
}

void UMulticastDelegateHandler::Initialize(FMulticastScriptDelegate* InMulticastScriptDelegate,
                                           UFunction* InSignatureFunction)
{
	MulticastScriptDelegate = InMulticastScriptDelegate;

	DelegateDescriptor = new FCSharpDelegateDescriptor(InSignatureFunction);
}

void UMulticastDelegateHandler::Deinitialize()
{
	if (MulticastScriptDelegate != nullptr)
	{
		MulticastScriptDelegate->RemoveAll(this);

		MulticastScriptDelegate = nullptr;
	}

	if (DelegateDescriptor != nullptr)
	{
		delete DelegateDescriptor;

		DelegateDescriptor = nullptr;
	}

	Delegates.Emplace();

	ScriptDelegate.Unbind();
}

bool UMulticastDelegateHandler::IsBound() const
{
	return MulticastScriptDelegate != nullptr ? MulticastScriptDelegate->IsBound() : nullptr;
}

bool UMulticastDelegateHandler::Contains(MonoObject* InMulticastDelegate) const
{
	if (const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DELEGATE),CLASS_MULTICAST_DELEGATE_UTILS))
	{
		if (const auto FoundMonoMethod = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Method_From_Name(
			FoundMonoClass,FUNCTION_MULTICAST_DELEGATE_EQUALS, 2))
		{
			for (const auto Delegate : Delegates)
			{
				void* Params[2];

				Params[0] = Delegate;

				Params[1] = InMulticastDelegate;

				const auto ResultMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Runtime_Invoke(
					FoundMonoMethod, nullptr, Params, nullptr);

				if (*static_cast<bool*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_Unbox(
					ResultMonoObject)))
				{
					return true;
				}
			}
		}
	}

	return false;
}

void UMulticastDelegateHandler::Add(MonoObject* InMulticastDelegate)
{
	if (MulticastScriptDelegate != nullptr)
	{
		if (!MulticastScriptDelegate->Contains(ScriptDelegate))
		{
			ScriptDelegate.Unbind();

			ScriptDelegate.BindUFunction(this, "CSharpCallBack");

			MulticastScriptDelegate->Add(ScriptDelegate);
		}
	}

	Delegates.Emplace(InMulticastDelegate);
}

void UMulticastDelegateHandler::AddUnique(MonoObject* InMulticastDelegate)
{
	if (MulticastScriptDelegate != nullptr)
	{
		if (!MulticastScriptDelegate->Contains(ScriptDelegate))
		{
			ScriptDelegate.Unbind();

			ScriptDelegate.BindUFunction(this, "CSharpCallBack");

			MulticastScriptDelegate->Add(ScriptDelegate);
		}
	}

	if (!Contains(InMulticastDelegate))
	{
		Delegates.Emplace(InMulticastDelegate);
	}
}

void UMulticastDelegateHandler::Remove(MonoObject* InMulticastDelegate)
{
	if (const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DELEGATE),CLASS_MULTICAST_DELEGATE_UTILS))
	{
		if (const auto FoundMonoMethod = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_Get_Method_From_Name(
			FoundMonoClass,FUNCTION_MULTICAST_DELEGATE_EQUALS, 2))
		{
			for (const auto Delegate : Delegates)
			{
				void* Params[2];

				Params[0] = Delegate;

				Params[1] = InMulticastDelegate;

				const auto ResultMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Runtime_Invoke(
					FoundMonoMethod, nullptr, Params, nullptr);

				if (*static_cast<bool*>(FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_Unbox(
					ResultMonoObject)))
				{
					Delegates.Remove(Delegate);

					break;
				}
			}
		}
	}

	if (Delegates.Num() == 0)
	{
		if (MulticastScriptDelegate != nullptr)
		{
			MulticastScriptDelegate->RemoveAll(this);

			ScriptDelegate.Unbind();
		}
	}
}

void UMulticastDelegateHandler::RemoveAll(MonoObject* InObject)
{
	Delegates.RemoveAll([InObject](MonoObject* Element)
	{
		if (Element == nullptr)
		{
			return true;
		}

		if (const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_DELEGATE),CLASS_MULTICAST_DELEGATE_UTILS))
		{
			if (const auto FoundMonoMethod = FCSharpEnvironment::GetEnvironment()->GetDomain()->
				Class_Get_Method_From_Name(FoundMonoClass,FUNCTION_MULTICAST_DELEGATE_GET_TARGET, 1))
			{
				void* Params[1];

				Params[0] = Element;

				const auto TargetMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Runtime_Invoke(
					FoundMonoMethod, nullptr, Params, nullptr);

				return TargetMonoObject == InObject ? true : false;
			}
		}

		return false;
	});

	if (Delegates.Num() == 0)
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

	Delegates.Empty();

	ScriptDelegate.Unbind();
}

void UMulticastDelegateHandler::Broadcast(MonoObject** OutValue, MonoArray* InValue) const
{
	if (MulticastScriptDelegate != nullptr)
	{
		if (MulticastScriptDelegate->IsBound())
		{
			if (DelegateDescriptor != nullptr)
			{
				DelegateDescriptor->ProcessMulticastDelegate(MulticastScriptDelegate, OutValue, InValue);
			}
		}
	}
}
