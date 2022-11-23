#include "Binding/FBinding.h"

FBinding& FBinding::Get()
{
	static FBinding Binding;

	return Binding;
}

void FBinding::RegisterBinding(const FString& InName, const void* InMethod)
{
	Bindings.Emplace(InName, InMethod);
}

const TMap<FString, const void*>& FBinding::GetBinding() const
{
	return Bindings;
}
