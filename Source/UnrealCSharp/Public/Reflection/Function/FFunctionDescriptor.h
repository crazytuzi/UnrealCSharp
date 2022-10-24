#pragma once

class FFunctionDescriptor
{
public:
	FFunctionDescriptor();

	~FFunctionDescriptor();

public:
	void Initialize();

	void Deinitialize();

public:
	bool CallCSharp(FFrame& Stack, RESULT_DECL);

private:
	friend class FCSharpBind;

	TWeakObjectPtr<UFunction> OriginalFunction = nullptr;

	TWeakObjectPtr<UFunction> CallCSharpFunction = nullptr;

	EFunctionFlags OriginalFunctionFlags;

	FNativeFuncPtr OriginalNativeFuncPtr;

	TArray<uint8> OriginalScript;
};
