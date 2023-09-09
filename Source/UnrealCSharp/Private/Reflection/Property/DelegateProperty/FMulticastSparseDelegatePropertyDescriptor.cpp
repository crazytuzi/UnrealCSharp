#include "Reflection/Property/DelegateProperty/FMulticastSparseDelegatePropertyDescriptor.h"

const FMulticastScriptDelegate* FMulticastSparseDelegatePropertyDescriptor::GetMulticastDelegate(void* InAddress) const
{
	auto MulticastDelegate = MulticastSparseDelegateProperty->GetMulticastDelegate(InAddress);

	if (MulticastDelegate == nullptr)
	{
		FMulticastScriptDelegate MulticastScriptDelegate;

		FScriptDelegate ScriptDelegate;

		ScriptDelegate.BindUFunction(nullptr, TEXT("Dummy"));

		MulticastScriptDelegate.Add(ScriptDelegate);

		MulticastSparseDelegateProperty->SetMulticastDelegate(InAddress, MulticastScriptDelegate);

		MulticastDelegate = MulticastSparseDelegateProperty->GetMulticastDelegate(InAddress);
	}

	return MulticastDelegate;
}
