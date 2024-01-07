#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"
#include "Async/Async.h"

struct FRegisterText
{
	static void RegisterImplementation(MonoObject* InMonoObject, MonoString* InValue)
	{
		const auto Text = new FText(FText::FromString(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(InValue))));

		FCSharpEnvironment::GetEnvironment().AddStringReference<FText>(InMonoObject, Text);
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

	static void ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoString** OutValue)
	{
		const auto Text = FCSharpEnvironment::GetEnvironment().GetString<FText>(InGarbageCollectionHandle);

		*OutValue = FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(TCHAR_TO_UTF8(*Text->ToString()));
	}

	FRegisterText()
	{
		FClassBuilder(TEXT("Text"), NAMESPACE_LIBRARY)
			.Function("Register", RegisterImplementation)
			.Function("Identical", IdenticalImplementation)
			.Function("UnRegister", UnRegisterImplementation)
			.Function("ToString", ToStringImplementation)
			.Register();
	}
};

static FRegisterText RegisterText;
