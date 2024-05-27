#pragma once

#define DOTNET_GREATER_SORT(Value, ValueToBeGreaterThan, TieBreaker) \
	(((Value) > (ValueToBeGreaterThan)) || (((Value) == (ValueToBeGreaterThan)) && (TieBreaker)))

#define DOTNET_VERSION_START(MajorVersion, MinorVersion, PatchVersion) \
	DOTNET_GREATER_SORT(DOTNET_MAJOR_VERSION, MajorVersion, DOTNET_GREATER_SORT(DOTNET_MINOR_VERSION, MinorVersion, DOTNET_GREATER_SORT(DOTNET_PATCH_VERSION, PatchVersion, true)))

#define DOTNET8 DOTNET_VERSION_START(8, 0, 0)
