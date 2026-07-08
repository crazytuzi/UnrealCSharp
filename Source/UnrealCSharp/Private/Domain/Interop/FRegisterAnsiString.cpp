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
	struct FRegisterAnsiString
	{
		static void RegisterImplementation(const IManagedHandle InManagedObject, const char* InValue)
		{
			const auto AnsiString = new FAnsiString(InValue != nullptr
				                                        ? FString(UTF8_TO_TCHAR(InValue))
				                                        : FString(TEXT("")));

			FCSharpEnvironment::GetEnvironment().AddStringReference<FAnsiString, true, false>(
				FReflectionRegistry::Get().GetAnsiStringClass(), InManagedObject, AnsiString);
		}

		static uint8 IdenticalImplementation(const IManagedHandle InA, const IManagedHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetString<FAnsiString>(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetString<FAnsiString>(InB))
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
				(void)FCSharpEnvironment::GetEnvironment().RemoveStringReference<
					FAnsiString>(InManagedHandle);
			});
		}

		static IManagedHandle ToStringImplementation(const IManagedHandle InManagedHandle)
		{
			const auto AnsiString = FCSharpEnvironment::GetEnvironment().GetString<FAnsiString>(InManagedHandle);

			return AnsiString != nullptr
				       ? IScriptDomain::Get()->NewString(TCHAR_TO_UTF8(*FAnsiString(*AnsiString)))
				       : InvalidManagedHandle;
		}

		FRegisterAnsiString()
		{
			FClassBuilder(TEXT("FAnsiString"), NAMESPACE_LIBRARY)
				.Function("Register", RegisterImplementation)
				.Function("Identical", IdenticalImplementation)
				.Function("UnRegister", UnRegisterImplementation)
				.Function("ToString", ToStringImplementation);
		}
	};

	[[maybe_unused]] FRegisterAnsiString RegisterAnsiString;
}
#endif
