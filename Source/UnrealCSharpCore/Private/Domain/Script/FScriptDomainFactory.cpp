#include "Domain/Script/FScriptDomainFactory.h"
#include "Log/UnrealCSharpLog.h"
#if WITH_MONO
#include "Domain/Mono/FMonoDomain.h"
#endif
#if WITH_CORECLR
#include "Domain/CoreCLR/FCoreCLRDomain.h"
#endif
#if WITH_LEANCLR
#include "Domain/LeanCLR/FLeanCLRDomain.h"
#endif

EScriptDomainType FScriptDomainFactory::GetScriptDomainType()
{
	if (const auto UnrealCSharpSetting = GetDefault<UUnrealCSharpSetting>())
	{
		return UnrealCSharpSetting->GetScriptDomainType(FPlatformProperties::IniPlatformName());
	}

	return EScriptDomainType::Mono;
}

IScriptDomain* FScriptDomainFactory::Create()
{
	if (const auto ScriptDomainType = GetScriptDomainType();
		ScriptDomainType == EScriptDomainType::Mono)
	{
#if WITH_MONO
		return new FMonoDomain();
#endif
	}
	else if (ScriptDomainType == EScriptDomainType::CoreCLR)
	{
#if WITH_CORECLR
		return new FCoreCLRDomain();
#endif
	}
	else if (ScriptDomainType == EScriptDomainType::LeanCLR)
	{
#if WITH_LEANCLR
		return new FLeanCLRDomain();
#endif
	}

	UE_LOG(LogUnrealCSharp, Error,
	       TEXT("FScriptDomainFactory::Create fell through. Type=%d, Core WITH_MONO=%d, WITH_CORECLR=%d"),
	       static_cast<int32>(GetScriptDomainType()), WITH_MONO, WITH_CORECLR);

	return nullptr;
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
