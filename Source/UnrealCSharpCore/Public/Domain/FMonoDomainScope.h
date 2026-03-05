#pragma once

#include "FMonoDomain.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"

class FMonoDomainScope
{
public:
	explicit FMonoDomainScope(const TFunction<void()>& InFunction)
	{
		if (!FMonoDomain::IsLoadSucceed())
		{
			FMonoDomain::Initialize({
				"",
				FUnrealCSharpFunctionLibrary::GetFullAssemblyPublishPath()
			});
		}

		if (FMonoDomain::IsLoadSucceed())
		{
			InFunction();
		}
	}

	~FMonoDomainScope()
	{
		if (FMonoDomain::IsLoadSucceed())
		{
			FMonoDomain::Deinitialize();
		}
	}
};
