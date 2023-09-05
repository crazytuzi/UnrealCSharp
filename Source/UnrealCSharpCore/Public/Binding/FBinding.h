#pragma once

class UNREALCSHARPCORE_API FBinding
{
public:
	static FBinding& Get();

	void RegisterBinding(const FString& InName, const void* InMethod);

	const TMap<FString, const void*>& GetBinding() const;

private:
	TMap<FString, const void*> Bindings;
};
