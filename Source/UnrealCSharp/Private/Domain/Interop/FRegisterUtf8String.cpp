#include "UEVersion.h"
#if UE_F_UTF8_STR_PROPERTY
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Domain/Script/IManagedHandle.h"
#include "Domain/Script/IScriptDomain.h"
#include "Reflection/FReflectionRegistry.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterUtf8String
	{
		static void RegisterImplementation(const IManagedHandle InManagedObject, const char* InValue)
		{
			const auto Utf8String = new FUtf8String(InValue != nullptr
				                                        ? FString(UTF8_TO_TCHAR(InValue))
				                                        : FString(TEXT("")));

			FCSharpEnvironment::GetEnvironment().AddStringReference<FUtf8String, true, false>(
				FReflectionRegistry::Get().GetUtf8StringClass(), InManagedObject, Utf8String);
		}

		static uint8 IdenticalImplementation(const IManagedHandle InA, const IManagedHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetString<FUtf8String>(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetString<FUtf8String>(InB))
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
				(void)FCSharpEnvironment::GetEnvironment().RemoveStringReference<FUtf8String>(InManagedHandle);
			});
		}

		static IManagedHandle ToStringImplementation(const IManagedHandle InManagedHandle)
		{
			const auto Utf8String = FCSharpEnvironment::GetEnvironment().GetString<FUtf8String>(InManagedHandle);

			return IScriptDomain::Get()->NewString(TCHAR_TO_UTF8(*FUtf8String(*Utf8String)));
		}

		FRegisterUtf8String()
		{
			FClassBuilder(TEXT("FUtf8String"), NAMESPACE_LIBRARY)
				.Function("Register", RegisterImplementation)
				.Function("Identical", IdenticalImplementation)
				.Function("UnRegister", UnRegisterImplementation)
				.Function("ToString", ToStringImplementation);
		}
	};

	[[maybe_unused]] FRegisterUtf8String RegisterUtf8String;
}
#endif
