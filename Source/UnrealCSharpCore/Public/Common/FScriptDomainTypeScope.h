#pragma once

#include "CoreMinimal.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"

#if WITH_EDITOR
struct FScriptDomainTypeScope
{
	explicit FScriptDomainTypeScope(const EScriptDomainType InScriptDomainType):
		ScriptDomainType(FUnrealCSharpFunctionLibrary::GetScriptDomainType())
	{
		FUnrealCSharpFunctionLibrary::SetScriptDomainType(InScriptDomainType);
	}

	~FScriptDomainTypeScope()
	{
		FUnrealCSharpFunctionLibrary::SetScriptDomainType(ScriptDomainType);
	}

	FScriptDomainTypeScope(const FScriptDomainTypeScope&) = delete;

	FScriptDomainTypeScope& operator=(const FScriptDomainTypeScope&) = delete;

private:
	EScriptDomainType ScriptDomainType;
};
#endif
