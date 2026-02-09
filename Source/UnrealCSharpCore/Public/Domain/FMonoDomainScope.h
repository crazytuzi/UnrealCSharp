#pragma once

#include "FMonoDomain.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Reflection/FReflectionRegistry.h"

class FMonoDomainScope
{
public:
	explicit FMonoDomainScope(const TFunction<void()>& InFunction)
	{
		if (!FMonoDomain::bLoadSucceed)
		{
			FMonoDomain::Initialize({
				"",
				FUnrealCSharpFunctionLibrary::GetFullAssemblyPublishPath()
			});
		}

		if (FMonoDomain::bLoadSucceed)
		{
			InFunction();
			
			FReflectionRegistry::Get().Initialize();
		}
	}

	~FMonoDomainScope()
	{
		if (FMonoDomain::bLoadSucceed)
		{
			FReflectionRegistry::Get().Deinitialize();
			
			FMonoDomain::Deinitialize();
		}
	}
};
