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
	struct FRegisterUtf8String
	{
		static void RegisterImplementation(const IManagedHandle InManagedObject, const char* InValue)
		{
			const auto Utf8String = new FUtf8String(InValue != nullptr
				                                        ? FString(UTF8_TO_TCHAR(InValue))
				                                        : FString(TEXT("")));

			FCSharpEnvironment::GetEnvironment().AddStringReference<FUtf8String, true, false>(
				FReflectionRegistry::Get().GetUtf8StringClass(), InManagedObject, Utf8String);
		}

		static uint8 IdenticalImplementation(const IManagedHandle InA, const IManagedHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetString<FUtf8String>(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetString<FUtf8String>(InB))
				{
					return *FoundA == *FoundB ? 1 : 0;
				}
			}

			return 0;
		}

		static int32 GetTypeHashImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto FoundUtf8String = FCSharpEnvironment::GetEnvironment().
				GetString<FUtf8String>(InManagedHandle))
			{
				return static_cast<int32>(GetTypeHash(*FoundUtf8String));
			}

			return 0;
		}

		static void UnRegisterImplementation(const IManagedHandle InManagedHandle)
		{
			if (IsInGameThread())
			{
				(void)FCSharpEnvironment::GetEnvironment().RemoveStringReference<FUtf8String>(InManagedHandle);
			}
			else
			{
				AsyncTask(ENamedThreads::GameThread, [InManagedHandle]
				{
					(void)FCSharpEnvironment::GetEnvironment().RemoveStringReference<FUtf8String>(InManagedHandle);
				});
			}
		}

		static IManagedHandle ToStringImplementation(const IManagedHandle InManagedHandle)
		{
			const auto Utf8String = FCSharpEnvironment::GetEnvironment().GetString<FUtf8String>(InManagedHandle);

			return Utf8String != nullptr
				       ? IScriptDomain::Get()->NewString(reinterpret_cast<const char*>(**Utf8String))
				       : InvalidManagedHandle;
		}

		FRegisterUtf8String()
		{
			FClassBuilder(TEXT("FUtf8String"), NAMESPACE_LIBRARY)
				.Function("Register", RegisterImplementation)
				.Function("Identical", IdenticalImplementation)
				.Function("GetTypeHash", GetTypeHashImplementation)
				.Function("UnRegister", UnRegisterImplementation)
				.Function("ToString", ToStringImplementation);
		}
	};

	[[maybe_unused]] FRegisterUtf8String RegisterUtf8String;
}
#endif
