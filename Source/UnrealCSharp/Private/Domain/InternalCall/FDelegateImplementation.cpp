#include "Domain/InternalCall/FDelegateImplementation.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FDelegateHelper.h"

void FDelegateImplementation::Delegate_BindImplementation(const void* InAddress, MonoObject* InDelegate)
{
	if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment()->GetDelegate<FDelegateHelper>(InAddress))
	{
		DelegateHelper->Bind(InDelegate);
	}
}

bool FDelegateImplementation::Delegate_IsBoundImplementation(const void* InAddress)
{
	if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment()->GetDelegate<FDelegateHelper>(InAddress))
	{
		return DelegateHelper->IsBound();
	}

	return false;
}

void FDelegateImplementation::Delegate_UnBindImplementation(const void* InAddress)
{
	if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment()->GetDelegate<FDelegateHelper>(InAddress))
	{
		DelegateHelper->UnBind();
	}
}

void FDelegateImplementation::Delegate_ClearImplementation(const void* InAddress)
{
	if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment()->GetDelegate<FDelegateHelper>(InAddress))
	{
		DelegateHelper->Clear();
	}
}

void FDelegateImplementation::Delegate_ExecuteImplementation(const void* InAddress, MonoObject** ReturnValue,
                                                             MonoObject** OutValue, MonoArray* InValue)
{
	if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment()->GetDelegate<FDelegateHelper>(InAddress))
	{
		DelegateHelper->Execute(ReturnValue, OutValue, InValue);
	}
}
