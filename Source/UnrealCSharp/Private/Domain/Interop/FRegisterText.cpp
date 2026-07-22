#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Domain/Script/IManagedHandle.h"
#include "Domain/Script/IScriptDomain.h"
#include "Reflection/FReflectionRegistry.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/CompilerMacro.h"
#include "Async/Async.h"

PRAGMA_DISABLE_DANGLING_WARNINGS

namespace
{
	struct FRegisterText
	{
		static void RegisterImplementation(const IManagedHandle InManagedObject,
		                                   const char* InBuffer,
		                                   const char* InTextNamespace,
		                                   const char* InPackageNamespace,
		                                   const uint8 bRequiresQuotes)
		{
			const auto Buffer = InBuffer != nullptr
				                    ? FString(UTF8_TO_TCHAR(InBuffer))
				                    : FString(TEXT(""));

			const auto TextNamespace = InTextNamespace != nullptr
				                           ? FString(UTF8_TO_TCHAR(InTextNamespace))
				                           : FString(TEXT(""));

			const auto PackageNamespace = InPackageNamespace != nullptr
				                              ? FString(UTF8_TO_TCHAR(InPackageNamespace))
				                              : FString(TEXT(""));

			const auto OutText = new FText();

			FTextStringHelper::ReadFromBuffer(
				InBuffer != nullptr ? *Buffer : nullptr,
				*OutText,
				InTextNamespace != nullptr ? *TextNamespace : nullptr,
				InPackageNamespace != nullptr ? *PackageNamespace : nullptr,
				bRequiresQuotes != 0);

			FCSharpEnvironment::GetEnvironment().AddStringReference<FText, true, false>(
				FReflectionRegistry::Get().GetTextClass(), InManagedObject, OutText);
		}

		static uint8 IdenticalImplementation(const IManagedHandle InA, const IManagedHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetString<FText>(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetString<FText>(InB))
				{
					return FoundA->EqualTo(*FoundB) ? 1 : 0;
				}
			}

			return 0;
		}

		static void UnRegisterImplementation(const IManagedHandle InManagedHandle)
		{
			AsyncTask(ENamedThreads::GameThread, [InManagedHandle]
			{
				(void)FCSharpEnvironment::GetEnvironment().RemoveStringReference<FText>(InManagedHandle);
			});
		}

		static IManagedHandle ToStringImplementation(const IManagedHandle InManagedHandle)
		{
			const auto Text = FCSharpEnvironment::GetEnvironment().GetString<FText>(InManagedHandle);

			return IScriptDomain::Get()->NewString(TCHAR_TO_UTF8(*Text->ToString()));
		}

		FRegisterText()
		{
			FClassBuilder(TEXT("FText"), NAMESPACE_LIBRARY)
				.Function("Register", RegisterImplementation)
				.Function("Identical", IdenticalImplementation)
				.Function("UnRegister", UnRegisterImplementation)
				.Function("ToString", ToStringImplementation);
		}
	};

	[[maybe_unused]] FRegisterText RegisterText;
}

PRAGMA_ENABLE_DANGLING_WARNINGS
