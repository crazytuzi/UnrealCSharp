#include "UEVersion.h"
#if UE_F_UTF8_STR_PROPERTY
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterAnsiString
	{
		static void RegisterImplementation(MonoObject* InMonoObject, MonoString* InValue)
		{
			const auto AnsiString = new FAnsiString(UTF8_TO_TCHAR(FDomain::String_To_UTF8(InValue)));

			FCSharpEnvironment::GetEnvironment().AddStringReference<FAnsiString, true, false>(FReflectionRegistry::Get().Get_AnsiString_Class(), InMonoObject, AnsiString);
		}

		static bool IdenticalImplementation(const FGarbageCollectionHandle InA, const FGarbageCollectionHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetString<FAnsiString>(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetString<FAnsiString>(InB))
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
				(void)FCSharpEnvironment::GetEnvironment().RemoveStringReference<
					FAnsiString>(InGarbageCollectionHandle);
			});
		}

		static MonoString* ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			auto AnsiString = FCSharpEnvironment::GetEnvironment().GetString<FAnsiString>(InGarbageCollectionHandle);

			return FDomain::String_New(TCHAR_TO_UTF8(*FAnsiString(*AnsiString)));
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
