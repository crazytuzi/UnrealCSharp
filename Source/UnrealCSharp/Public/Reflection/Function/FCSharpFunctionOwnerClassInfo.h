#pragma once

class UClass;

#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
struct FCSharpFunctionOwnerClassInfo
{
	UClass* OriginalOwnerClass{};

	UClass* DummyOwnerClass{};
};
#endif
