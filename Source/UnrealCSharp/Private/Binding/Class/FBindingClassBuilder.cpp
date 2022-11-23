#include "Binding/Class/FBindingClassBuilder.h"
#include "Binding/FBinding.h"

FBindingClassBuilder::FBindingClassBuilder()
{
}

FBindingClassBuilder& FBindingClassBuilder::Function(const FString& InName, const void* InMethod)
{
	Functions.Emplace(InName, InMethod);

	return *this;
}

void FBindingClassBuilder::Register()
{
	for (const auto Iterator : Functions)
	{
		FBinding::Get().RegisterBinding(Iterator.Key, Iterator.Value);
	}
}
