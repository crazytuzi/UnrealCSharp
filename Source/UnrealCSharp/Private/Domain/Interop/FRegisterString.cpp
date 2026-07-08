#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Domain/Script/IManagedHandle.h"
#include "Domain/Script/IScriptDomain.h"
#include "Reflection/FReflectionRegistry.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterString
	{
		static void RegisterImplementation(const IManagedHandle InManagedObject, const char* InValue)
		{
			const auto String = new FString(InValue != nullptr ? FString(UTF8_TO_TCHAR(InValue)) : FString(TEXT("")));

			FCSharpEnvironment::GetEnvironment().AddStringReference<FString, true, false>(
				FReflectionRegistry::Get().GetStringClass(), InManagedObject, String);
		}

		static uint8 IdenticalImplementation(const IManagedHandle InA, const IManagedHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetString<FString>(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetString<FString>(InB))
				{
					return *FoundA == *FoundB ? 1 : 0;
				}
			}

			return 0;
		}

		static void UnRegisterImplementation(const IManagedHandle InManagedHandle)
		{
			AsyncTask(ENamedThreads::GameThread, [InManagedHandle]
			{
				(void)FCSharpEnvironment::GetEnvironment().RemoveStringReference<FString>(InManagedHandle);
			});
		}

		static IManagedHandle ToStringImplementation(const IManagedHandle InManagedHandle)
		{
			const auto String = FCSharpEnvironment::GetEnvironment().GetString<FString>(InManagedHandle);

			return IScriptDomain::Get()->NewString(TCHAR_TO_UTF8(**String));
		}

		FRegisterString()
		{
			FClassBuilder(TEXT("FString"), NAMESPACE_LIBRARY)
				.Function("Register", RegisterImplementation)
				.Function("Identical", IdenticalImplementation)
				.Function("UnRegister", UnRegisterImplementation)
				.Function("ToString", ToStringImplementation);
		}
	};

	[[maybe_unused]] FRegisterString RegisterString;
}
