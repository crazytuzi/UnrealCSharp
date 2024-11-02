#pragma once

class UNREALCSHARPCORE_API FUnrealCSharpCoreModuleDelegates
{
public:
	DECLARE_MULTICAST_DELEGATE(FOnBeginGenerator);

	DECLARE_MULTICAST_DELEGATE(FOnEndGenerator);

	DECLARE_MULTICAST_DELEGATE(FOnClassHierarchyUpdated);

	static FOnBeginGenerator OnBeginGenerator;

	static FOnEndGenerator OnEndGenerator;

	static FOnClassHierarchyUpdated OnClassHierarchyUpdated;
};
