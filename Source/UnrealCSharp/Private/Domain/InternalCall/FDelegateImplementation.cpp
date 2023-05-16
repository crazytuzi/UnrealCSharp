#include "Domain/InternalCall/FDelegateImplementation.h"
#include "Binding/Class/FBindingClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FDelegateHelper.h"
#include "Macro/NamespaceMacro.h"
#include "Async/Async.h"

struct FRegisterDelegate
{
	FRegisterDelegate()
	{
		FBindingClassBuilder(TEXT("Delegate"), NAMESPACE_LIBRARY)
			.Function("Register", static_cast<void*>(FDelegateImplementation::Delegate_RegisterImplementation))
			.Function("UnRegister", static_cast<void*>(FDelegateImplementation::Delegate_UnRegisterImplementation))
			.Function("Bind", static_cast<void*>(FDelegateImplementation::Delegate_BindImplementation))
			.Function("IsBound", static_cast<void*>(FDelegateImplementation::Delegate_IsBoundImplementation))
			.Function("UnBind", static_cast<void*>(FDelegateImplementation::Delegate_UnBindImplementation))
			.Function("Clear", static_cast<void*>(FDelegateImplementation::Delegate_ClearImplementation))
			.Function("Execute", static_cast<void*>(FDelegateImplementation::Delegate_ExecuteImplementation))
			.Register();
	}
};

static FRegisterDelegate RegisterDelegate;

void FDelegateImplementation::Delegate_RegisterImplementation(MonoObject* InMonoObject)
{
	FCSharpEnvironment::GetEnvironment().Bind<FDelegateHelper>(InMonoObject);
}

void FDelegateImplementation::Delegate_UnRegisterImplementation(const MonoObject* InMonoObject)
{
	AsyncTask(ENamedThreads::GameThread, [this, InMonoObject]
	{
		(void)FCSharpEnvironment::GetEnvironment().RemoveDelegateReference(InMonoObject);
	});
}

void FDelegateImplementation::Delegate_BindImplementation(const MonoObject* InMonoObject, MonoObject* InDelegate)
{
	if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(InMonoObject))
	{
		DelegateHelper->Bind(InDelegate);
	}
}

bool FDelegateImplementation::Delegate_IsBoundImplementation(const MonoObject* InMonoObject)
{
	if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(InMonoObject))
	{
		return DelegateHelper->IsBound();
	}

	return false;
}

void FDelegateImplementation::Delegate_UnBindImplementation(const MonoObject* InMonoObject)
{
	if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(InMonoObject))
	{
		DelegateHelper->UnBind();
	}
}

void FDelegateImplementation::Delegate_ClearImplementation(const MonoObject* InMonoObject)
{
	if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(InMonoObject))
	{
		DelegateHelper->Clear();
	}
}

void FDelegateImplementation::Delegate_ExecuteImplementation(const MonoObject* InMonoObject, MonoObject** ReturnValue,
                                                             MonoObject** OutValue, MonoArray* InValue)
{
	if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(InMonoObject))
	{
		DelegateHelper->Execute(ReturnValue, OutValue, InValue);
	}
}
