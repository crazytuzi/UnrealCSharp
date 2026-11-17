#pragma once

#include "CoreMinimal.h"
#include "IScriptDomain.h"

class UNREALCSHARPCORE_API FScriptDomainFactory
{
public:
	static IScriptDomain* Create();

	static void Destroy(IScriptDomain* InScriptDomain);

private:
	FScriptDomainFactory() = delete;
};
