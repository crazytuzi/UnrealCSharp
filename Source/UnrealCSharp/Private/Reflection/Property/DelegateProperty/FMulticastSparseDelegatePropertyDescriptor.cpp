#include "Reflection/Property/DelegateProperty/FMulticastSparseDelegatePropertyDescriptor.h"

const FMulticastScriptDelegate* FMulticastSparseDelegatePropertyDescriptor::GetMulticastDelegate(void* InAddress) const
{
	auto MulticastDelegate = Property->GetMulticastDelegate(InAddress);

	if (MulticastDelegate == nullptr)
	{
		FMulticastScriptDelegate MulticastScriptDelegate;

		FScriptDelegate ScriptDelegate;

		ScriptDelegate.BindUFunction(nullptr, TEXT("Dummy"));

		MulticastScriptDelegate.Add(ScriptDelegate);

		Property->SetMulticastDelegate(InAddress, MulticastScriptDelegate);

		MulticastDelegate = Property->GetMulticastDelegate(InAddress);
	}

	return MulticastDelegate;
}
