#pragma once

#include "Domain/Script/IManagedTypes.h"

#if WITH_MONO
using IManagedMarshalledString = IManagedString;

#define MANAGED_MARSHALLED_STRING_TO_F_STRING(InValue) \
	IScriptDomain::Get()->StringToFString(MANAGED_HANDLE_FROM_OBJECT(InValue))
#else
using IManagedMarshalledString = const char*;

#define MANAGED_MARSHALLED_STRING_TO_F_STRING(InValue) \
	InValue != nullptr ? FString(UTF8_TO_TCHAR(InValue)) : FString(TEXT(""))
#endif

#define MANAGED_MARSHALLED_STRING_NEW(InValue) \
	IManagedHandleToIManagedString(IScriptDomain::Get()->NewString(InValue))
