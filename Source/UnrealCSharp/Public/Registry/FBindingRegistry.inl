#pragma once

template <typename T>
auto FBindingRegistry::GetBinding(const MonoObject* InMonoObject)
{
	const auto FoundBinding = MonoObject2BindingMap.Find(InMonoObject);

	return FoundBinding != nullptr ? static_cast<T*>(*FoundBinding) : nullptr;
}
