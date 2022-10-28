#pragma once

#include "mono/metadata/appdomain.h"

struct FMonoDomainInitializeParams
{
	FString Domain;

	FString Assembly;

	FMonoDomainInitializeParams(const FString& InDomain, const FString& InAssembly):
		Domain(InDomain),
		Assembly(InAssembly)
	{
	}
};

class FMonoDomain
{
public:
	explicit FMonoDomain(const FMonoDomainInitializeParams& Params);

	~FMonoDomain();

public:
	void Initialize(const FMonoDomainInitializeParams& Params);

	void Deinitialize();

public:
	MonoObject* Object_New(MonoClass* InMonoClass, bool bInit = true) const;

	MonoClass* Class_From_Name(const FString& InNameSpace, const FString& InMonoClassName) const;

	MonoMethod* Class_Get_Method_From_Name(MonoClass* InMonoClass, const FString& InFunctionName,
	                                       int32 InParamCount) const;

	MonoObject* Runtime_Invoke(MonoMethod* InFunction, void* InMonoObject, void** InParams, MonoObject** InExc);

	void* Object_Unbox(MonoObject* InMonoObject);

private:
	void RegisterMonoTrace();

	void RegisterReflectionPropertyImplementation();

	void RegisterReflectionFunctionImplementation();

	void RegisterLog();

private:
	MonoDomain* Domain;

	MonoAssembly* Assembly;

	MonoImage* Image;
};
