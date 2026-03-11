#pragma once

class UNREALCSHARPCORE_API FMonoUTF8Scope
{
public:
	explicit FMonoUTF8Scope(char* InString);

	FMonoUTF8Scope(const FMonoUTF8Scope&) = delete;

	FMonoUTF8Scope& operator=(const FMonoUTF8Scope&) = delete;

	~FMonoUTF8Scope();

	operator const char*() const;

private:
	char* String{};
};
