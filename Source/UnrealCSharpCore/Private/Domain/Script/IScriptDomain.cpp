#include "Domain/Script/IScriptDomain.h"

IScriptDomain* IScriptDomain::ScriptDomain{};

IScriptDomain* IScriptDomain::Get()
{
	return ScriptDomain;
}

void IScriptDomain::Set(IScriptDomain* InScriptDomain)
{
	ScriptDomain = InScriptDomain;
}
