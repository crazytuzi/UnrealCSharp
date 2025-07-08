#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterText
	{
		static void RegisterImplementation(MonoObject* InMonoObject, MonoString* InBuffer, MonoString* InTextNamespace,
		                                   MonoString* InPackageNamespace, const bool bRequiresQuotes)
		{
			const TCHAR* Buffer{};

			if (InBuffer != nullptr)
			{
				Buffer = UTF8_TO_TCHAR(
					FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(InBuffer));
			}

			const TCHAR* TextNamespace{};

			if (InTextNamespace != nullptr)
			{
				TextNamespace = UTF8_TO_TCHAR(
					FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(InTextNamespace));
			}

			const TCHAR* PackageNamespace{};

			if (InPackageNamespace != nullptr)
			{
				PackageNamespace = UTF8_TO_TCHAR(
					FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(InPackageNamespace));
			}

			const auto OutText = new FText();

			FTextStringHelper::ReadFromBuffer(Buffer, *OutText, TextNamespace, PackageNamespace, bRequiresQuotes);

			FCSharpEnvironment::GetEnvironment().AddStringReference<FText, true, false>(InMonoObject, OutText);
		}

		static bool IdenticalImplementation(const FGarbageCollectionHandle InA, const FGarbageCollectionHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetString<FText>(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetString<FText>(InB))
				{
					return FoundA->EqualTo(*FoundB);
				}
			}

			return false;
		}

		static void UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			AsyncTask(ENamedThreads::GameThread, [InGarbageCollectionHandle]
			{
				(void)FCSharpEnvironment::GetEnvironment().RemoveStringReference<FText>(InGarbageCollectionHandle);
			});
		}

		static MonoString* ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			const auto Text = FCSharpEnvironment::GetEnvironment().GetString<FText>(InGarbageCollectionHandle);

			return FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(TCHAR_TO_UTF8(*Text->ToString()));
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
