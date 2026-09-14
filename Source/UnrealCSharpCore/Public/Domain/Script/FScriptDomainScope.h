#pragma once

#include "Domain/Script/IScriptDomain.h"
#include "Domain/Script/FScriptDomainFactory.h"

class FScriptDomainScope
{
public:
	explicit FScriptDomainScope(const TFunction<void()>& InFunction)
	{
		auto ScriptDomain = IScriptDomain::Get();

		if (ScriptDomain == nullptr)
		{
			ScriptDomain = FScriptDomainFactory::Create();

			if (ScriptDomain != nullptr)
			{
				IScriptDomain::Set(ScriptDomain);

				Domain = ScriptDomain;
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
		}
	}

	~FScriptDomainScope()
	{
		if (Domain != nullptr)
		{
			FScriptDomainFactory::Destroy(Domain);
		}
	}

	FScriptDomainScope(const FScriptDomainScope&) = delete;

	FScriptDomainScope& operator=(const FScriptDomainScope&) = delete;

private:
	IScriptDomain* Domain{};
};
