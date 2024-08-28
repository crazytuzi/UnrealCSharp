#pragma once

#include "FMonoDomain.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"

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
		}
	}

	~FMonoDomainScope()
	{
		if (FMonoDomain::bLoadSucceed)
		{
			FMonoDomain::Deinitialize();
		}
	}
};
