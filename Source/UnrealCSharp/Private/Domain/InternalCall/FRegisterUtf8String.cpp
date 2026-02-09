#include "UEVersion.h"
#if UE_F_UTF8_STR_PROPERTY
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterUtf8String
	{
		static void RegisterImplementation(MonoObject* InMonoObject, MonoString* InValue)
		{
			const auto Utf8String = new FUtf8String(UTF8_TO_TCHAR(FDomain::String_To_UTF8(InValue)));

			FCSharpEnvironment::GetEnvironment().AddStringReference<FUtf8String, true, false>(FReflectionRegistry::Get().Get_Utf8String_Class(), InMonoObject, Utf8String);
		}

		static bool IdenticalImplementation(const FGarbageCollectionHandle InA, const FGarbageCollectionHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetString<FUtf8String>(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetString<FUtf8String>(InB))
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
					FUtf8String>(InGarbageCollectionHandle);
			});
		}

		static MonoString* ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			auto Utf8String = FCSharpEnvironment::GetEnvironment().GetString<FUtf8String>(InGarbageCollectionHandle);

			return FDomain::String_New(TCHAR_TO_UTF8(*FUtf8String(*Utf8String)));
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
