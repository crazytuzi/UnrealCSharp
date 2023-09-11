#include "Reflection/Property/DelegateProperty/FMulticastInlineDelegatePropertyDescriptor.h"

const FMulticastScriptDelegate* FMulticastInlineDelegatePropertyDescriptor::GetMulticastDelegate(void* InAddress) const
{
	return MulticastInlineDelegateProperty->GetMulticastDelegate(InAddress);
}
