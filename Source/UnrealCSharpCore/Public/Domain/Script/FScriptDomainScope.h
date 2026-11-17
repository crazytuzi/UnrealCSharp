#pragma once

#include "Domain/Script/IScriptDomain.h"
#include "Domain/Script/FScriptDomainFactory.h"

class FScriptDomainScope
{
public:
	explicit FScriptDomainScope(const TFunction<void()>& InFunction)
	{
		auto ScriptDomain = IScriptDomain::Get();

		auto bNeedDestroy = false;

		if (ScriptDomain == nullptr)
		{
			ScriptDomain = FScriptDomainFactory::Create();

			if (ScriptDomain != nullptr)
			{
				IScriptDomain::Set(ScriptDomain);

				bNeedDestroy = true;
			}
		}

		if (ScriptDomain != nullptr)
		{
			if (!ScriptDomain->IsInitialized())
			{
				ScriptDomain->Initialize();
			}

			if (ScriptDomain->IsInitialized())
			{
				InFunction();
			}
			else if (bNeedDestroy)
			{
				FScriptDomainFactory::Destroy(ScriptDomain);
			}
		}
	}

	~FScriptDomainScope() = default;

	FScriptDomainScope(const FScriptDomainScope&) = delete;

	FScriptDomainScope& operator=(const FScriptDomainScope&) = delete;
};
