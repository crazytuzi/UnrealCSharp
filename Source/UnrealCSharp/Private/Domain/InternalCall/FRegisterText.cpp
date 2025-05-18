#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterText
	{
		static void RegisterImplementation(MonoObject* InMonoObject, MonoString* InValue)
		{
			const auto Text = new FText(FText::FromString(UTF8_TO_TCHAR(
				FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(InValue))));

			FCSharpEnvironment::GetEnvironment().AddStringReference<FText, true, false>(InMonoObject, Text);
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

		static MonoObject* CreateFromBufferImplementation(MonoString* InBuffer, MonoString* InTextNamespace,
			MonoString* InPackageNamespace, const bool bRequiresQuotes)
		{
			const auto Buffer = InBuffer != nullptr
									? UTF8_TO_TCHAR(
										FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(
											InBuffer))
									: nullptr;

			const auto TextNamespace = InTextNamespace != nullptr
											? UTF8_TO_TCHAR(
												FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(
													InTextNamespace))
											: nullptr;

			const auto PackageNamespace = InPackageNamespace != nullptr
												? UTF8_TO_TCHAR(
													FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(
														InPackageNamespace))
												: nullptr;

			const auto OutText = new FText();

			FTextStringHelper::ReadFromBuffer(Buffer, *OutText, TextNamespace, PackageNamespace, bRequiresQuotes);

			const auto FoundMonoClass = TPropertyClass<FText, FText>::Get();

			const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

			FCSharpEnvironment::GetEnvironment().AddStringReference<FText, true, false>(Object, OutText);

			return Object;
		}

		FRegisterText()
		{
			FClassBuilder(TEXT("FText"), NAMESPACE_LIBRARY)
				.Function("Register", RegisterImplementation)
				.Function("Identical", IdenticalImplementation)
				.Function("UnRegister", UnRegisterImplementation)
				.Function("ToString", ToStringImplementation)
				.Function("CreateFromBuffer", CreateFromBufferImplementation);
		}
	};

	[[maybe_unused]] FRegisterText RegisterText;
}
