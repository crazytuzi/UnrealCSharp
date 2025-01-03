#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterName
	{
		static void RegisterImplementation(MonoObject* InMonoObject, MonoString* InValue)
		{
			const auto Name = new FName(UTF8_TO_TCHAR(
				FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(InValue)));

			FCSharpEnvironment::GetEnvironment().AddStringReference<FName, true, false>(InMonoObject, Name);
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

		static MonoString* ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			const auto Name = FCSharpEnvironment::GetEnvironment().GetString<FName>(InGarbageCollectionHandle);

			return FCSharpEnvironment::GetEnvironment().GetDomain()->String_New(TCHAR_TO_UTF8(*Name->ToString()));
		}

		static MonoObject* NAME_NoneImplementation()
		{
			const auto FoundMonoClass = TPropertyClass<FName, FName>::Get();

			const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

			FCSharpEnvironment::GetEnvironment().AddStringReference<FName, true, false>(Object, new FName(NAME_None));

			return Object;
		}

		FRegisterName()
		{
			FClassBuilder(TEXT("FName"), NAMESPACE_LIBRARY)
				.Function("Register", RegisterImplementation)
				.Function("Identical", IdenticalImplementation)
				.Function("UnRegister", UnRegisterImplementation)
				.Function("ToString", ToStringImplementation)
				.Function("NAME_None", NAME_NoneImplementation);
		}
	};

	[[maybe_unused]] FRegisterName RegisterName;
}
