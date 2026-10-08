#include "Domain/Script/FScriptDomainFactory.h"
#if WITH_MONO
#include "Domain/Mono/FMonoDomain.h"
#endif
#if WITH_CORECLR
#include "Domain/CoreCLR/FCoreCLRDomain.h"
#endif
#if WITH_LEANCLR
#include "Domain/LeanCLR/FLeanCLRDomain.h"
#endif

IScriptDomain* FScriptDomainFactory::Create()
{
#if WITH_MONO
	return new FMonoDomain();
#elif WITH_CORECLR
	return new FCoreCLRDomain();
#elif WITH_LEANCLR
	return new FLeanCLRDomain();
#else
	return nullptr;
#endif
}

void FScriptDomainFactory::Destroy(IScriptDomain* InScriptDomain)
{
	if (InScriptDomain != nullptr)
	{
		if (InScriptDomain->IsInitialized())
		{
			InScriptDomain->Deinitialize();
		}

		delete InScriptDomain;

		IScriptDomain::Set(nullptr);
	}
}
