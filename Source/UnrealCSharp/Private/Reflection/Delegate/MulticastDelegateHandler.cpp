// Fill out your copyright notice in the Description page of Project Settings.


#include "Reflection/Delegate/MulticastDelegateHandler.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/ClassMacro.h"
#include "Macro/FunctionMacro.h"
#include "Template/TGetArrayLength.inl"

void UMulticastDelegateHandler::ProcessEvent(UFunction* Function, void* Parms)
{
	if (Function != nullptr && Function->GetName() == "CSharpCallBack")
	{
		if (DelegateDescriptor != nullptr)
		{
			for (const auto& DelegateGarbageCollectionHandle : DelegateGarbageCollectionHandles)
			{
				if (const auto Delegate = static_cast<MonoObject*>(DelegateGarbageCollectionHandle))
				{
					DelegateDescriptor->CallDelegate(Delegate, Parms);
				}
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

	for (auto& DelegateGarbageCollectionHandle : DelegateGarbageCollectionHandles)
	{
		if (DelegateGarbageCollectionHandle.IsValid())
		{
			FGarbageCollectionHandle::Free(DelegateGarbageCollectionHandle);
		}
	}

	DelegateGarbageCollectionHandles.Empty();

	ScriptDelegate.Unbind();
}

bool UMulticastDelegateHandler::IsBound() const
{
	return MulticastScriptDelegate != nullptr ? MulticastScriptDelegate->IsBound() : false;
}

bool UMulticastDelegateHandler::Contains(MonoObject* InMulticastDelegate) const
{
	if (const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_UTILS))
	{
		void* Params[2];

		if (const auto FoundMonoMethod = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_Get_Method_From_Name(
			FoundMonoClass, FUNCTION_UTILS_MULTICAST_DELEGATE_GET_TARGET, TGetArrayLength(Params)))
		{
			for (const auto& DelegateGarbageCollectionHandle : DelegateGarbageCollectionHandles)
			{
				if (const auto Delegate = static_cast<MonoObject*>(DelegateGarbageCollectionHandle))
				{
					Params[0] = Delegate;

					Params[1] = InMulticastDelegate;

					const auto ResultMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Runtime_Invoke(
						FoundMonoMethod, nullptr, Params);

					if (*static_cast<bool*>(FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(
						ResultMonoObject)))
					{
						return true;
					}
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

	DelegateGarbageCollectionHandles.Emplace(FGarbageCollectionHandle::NewRef(InMulticastDelegate, true));
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
		DelegateGarbageCollectionHandles.Emplace(FGarbageCollectionHandle::NewRef(InMulticastDelegate, true));
	}
}

void UMulticastDelegateHandler::Remove(MonoObject* InMulticastDelegate)
{
	if (const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_UTILS))
	{
		void* Params[2];

		if (const auto FoundMonoMethod = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_Get_Method_From_Name(
			FoundMonoClass, FUNCTION_UTILS_MULTICAST_DELEGATE_EQUALS, TGetArrayLength(Params)))
		{
			for (const auto& DelegateGarbageCollectionHandle : DelegateGarbageCollectionHandles)
			{
				if (const auto Delegate = static_cast<MonoObject*>(DelegateGarbageCollectionHandle))
				{
					Params[0] = Delegate;

					Params[1] = InMulticastDelegate;

					const auto ResultMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Runtime_Invoke(
						FoundMonoMethod, nullptr, Params);

					if (*static_cast<bool*>(FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(
						ResultMonoObject)))
					{
						DelegateGarbageCollectionHandles.Remove(Delegate);

						break;
					}
				}
			}
		}
	}

	if (DelegateGarbageCollectionHandles.IsEmpty())
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
	DelegateGarbageCollectionHandles.RemoveAll([InObject](FGarbageCollectionHandle Element)
	{
		if (!Element.IsValid())
		{
			return true;
		}

		const auto FoundMonoObject = static_cast<MonoObject*>(Element);

		if (const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_UTILS))
		{
			auto Params = static_cast<void*>(FoundMonoObject);

			if (const auto FoundMonoMethod = FCSharpEnvironment::GetEnvironment().GetDomain()->
				Class_Get_Method_From_Name(FoundMonoClass, FUNCTION_UTILS_MULTICAST_DELEGATE_GET_TARGET,
				                           TGetArrayLength(Params)))
			{
				const auto TargetMonoObject = FCSharpEnvironment::GetEnvironment().GetDomain()->Runtime_Invoke(
					FoundMonoMethod, nullptr, &Params);

				return TargetMonoObject == InObject;
			}
		}

		return false;
	});

	if (DelegateGarbageCollectionHandles.IsEmpty())
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

	for (auto& DelegateGarbageCollectionHandle : DelegateGarbageCollectionHandles)
	{
		if (DelegateGarbageCollectionHandle.IsValid())
		{
			FGarbageCollectionHandle::Free(DelegateGarbageCollectionHandle);
		}
	}

	DelegateGarbageCollectionHandles.Empty();

	ScriptDelegate.Unbind();
}

MonoObject* UMulticastDelegateHandler::Broadcast(MonoObject** OutValue, MonoArray* InValue) const
{
	if (MulticastScriptDelegate != nullptr)
	{
		if (MulticastScriptDelegate->IsBound())
		{
			if (DelegateDescriptor != nullptr)
			{
				return DelegateDescriptor->ProcessMulticastDelegate(MulticastScriptDelegate, OutValue, InValue);
			}
		}
	}

	return nullptr;
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
	return FindFunction(TEXT("CSharpCallBack"));
}
