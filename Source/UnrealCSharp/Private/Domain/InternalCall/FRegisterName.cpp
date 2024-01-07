#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"
#include "Async/Async.h"

struct FRegisterName
{
	static void RegisterImplementation(MonoObject* InMonoObject, MonoString* InValue)
	{
		const auto Name = new FName(UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(InValue)));

		FCSharpEnvironment::GetEnvironment().AddStringReference<FName>(InMonoObject, Name);
	}

	static bool IdenticalImplementation(const FGarbageCollectionHandle InA, const FGarbageCollectionHandle InB)
	{
		if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetString<FName>(InA))
		{
			if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetString<FName>(InB))
			{
				return *FoundA == *FoundB;
			}
		}

		return false;
	}

	static void UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
	{
		AsyncTask(ENamedThreads::GameThread, [InGarbageCollectionHandle]
		{
			(void)FCSharpEnvironment::GetEnvironment().RemoveStringReference<FName>(InGarbageCollectionHandle);
		});
	}

	static void ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoString** OutValue)
	{
		const auto Name = FCSharpEnvironment::GetEnvironment().GetString<FName>(InGarbageCollectionHandle);

		*OutValue = FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(TCHAR_TO_UTF8(*Name->ToString()));
	}

	FRegisterName()
	{
		FClassBuilder(TEXT("Name"), NAMESPACE_LIBRARY)
			.Function("Register", RegisterImplementation)
			.Function("Identical", IdenticalImplementation)
			.Function("UnRegister", UnRegisterImplementation)
			.Function("ToString", ToStringImplementation)
			.Register();
	}
};

static FRegisterName RegisterName;
