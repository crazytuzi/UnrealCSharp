#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Domain/Script/IManagedHandle.h"
#include "Domain/Script/IManagedMarshalledString.h"
#include "Domain/Script/IUnmanagedBool.h"
#include "Reflection/FReflectionRegistry.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/CompilerMacro.h"
#include "Async/Async.h"

PRAGMA_DISABLE_DANGLING_WARNINGS

namespace
{
	struct FRegisterText
	{
		static void RegisterImplementation(const IManagedObject InManagedObject,
		                                   const IManagedMarshalledString InBuffer,
		                                   const IManagedMarshalledString InTextNamespace,
		                                   const IManagedMarshalledString InPackageNamespace,
		                                   const bool bRequiresQuotes)
		{
			const auto Buffer = InBuffer != nullptr
				                    ? MANAGED_MARSHALLED_STRING_TO_F_STRING(InBuffer)
				                    : TEXT("");

			const auto TextNamespace = InTextNamespace != nullptr
				                           ? MANAGED_MARSHALLED_STRING_TO_F_STRING(InTextNamespace)
				                           : TEXT("");

			const auto PackageNamespace = InPackageNamespace != nullptr
				                              ? MANAGED_MARSHALLED_STRING_TO_F_STRING(InPackageNamespace)
				                              : TEXT("");

			const auto OutText = new FText();

			FTextStringHelper::ReadFromBuffer(
				InBuffer != nullptr ? *Buffer : nullptr,
				*OutText,
				InTextNamespace != nullptr ? *TextNamespace : nullptr,
				InPackageNamespace != nullptr ? *PackageNamespace : nullptr,
				bRequiresQuotes);

			FCSharpEnvironment::GetEnvironment().AddStringReference<FText, true, false>(
				FReflectionRegistry::Get().GetTextClass(), MANAGED_HANDLE_FROM_OBJECT(InManagedObject), OutText);
		}

		static IUnmanagedBool IdenticalImplementation(const IManagedHandle InA, const IManagedHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetString<FText>(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetString<FText>(InB))
				{
					return BoolToIUnmanagedBool(FoundA->EqualTo(*FoundB));
				}
			}

			return IUnmanagedFalse;
		}

		static void UnRegisterImplementation(const IManagedHandle InManagedHandle)
		{
			AsyncTask(ENamedThreads::GameThread, [InManagedHandle]
			{
				(void)FCSharpEnvironment::GetEnvironment().RemoveStringReference<FText>(InManagedHandle);
			});
		}

		static IManagedString ToStringImplementation(const IManagedHandle InManagedHandle)
		{
			const auto Text = FCSharpEnvironment::GetEnvironment().GetString<FText>(InManagedHandle);

			return MANAGED_MARSHALLED_STRING_NEW(TCHAR_TO_UTF8(*Text->ToString()));
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
