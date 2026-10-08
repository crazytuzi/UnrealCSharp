#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Domain/Script/IManagedHandle.h"
#include "Domain/Script/IScriptDomain.h"
#include "Reflection/FReflectionRegistry.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterName
	{
		static void RegisterImplementation(const IManagedHandle InManagedObject, const char* InValue)
		{
			const auto Name = new FName(InValue != nullptr ? FString(UTF8_TO_TCHAR(InValue)) : FString(TEXT("")));

			FCSharpEnvironment::GetEnvironment().AddStringReference<FName, true, false>(
				FReflectionRegistry::Get().GetNameClass(), InManagedObject, Name);
		}

		static uint8 IdenticalImplementation(const IManagedHandle InA, const IManagedHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetString<FName>(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetString<FName>(InB))
				{
					return *FoundA == *FoundB ? 1 : 0;
				}
			}

			return 0;
		}

		static int32 GetTypeHashImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto FoundName = FCSharpEnvironment::GetEnvironment().GetString<FName>(InManagedHandle))
			{
				return static_cast<int32>(GetTypeHash(*FoundName));
			}

			return 0;
		}

		static void UnRegisterImplementation(const IManagedHandle InManagedHandle)
		{
			if (IsInGameThread())
			{
				(void)FCSharpEnvironment::GetEnvironment().RemoveStringReference<FName>(InManagedHandle);
			}
			else
			{
				AsyncTask(ENamedThreads::GameThread, [InManagedHandle]
				{
					(void)FCSharpEnvironment::GetEnvironment().RemoveStringReference<FName>(InManagedHandle);
				});
			}
		}

		static IManagedHandle ToStringImplementation(const IManagedHandle InManagedHandle)
		{
			const auto Name = FCSharpEnvironment::GetEnvironment().GetString<FName>(InManagedHandle);

			return Name != nullptr
				       ? IScriptDomain::Get()->NewString(TCHAR_TO_UTF8(*Name->ToString()))
				       : InvalidManagedHandle;
		}

		static IManagedHandle NAME_NoneImplementation()
		{
			if (const auto FoundClass = TPropertyClass<FName, FName>::Get())
			{
				const auto Object = FoundClass->NewObject();

				FCSharpEnvironment::GetEnvironment().AddStringReference<FName, true, false>(
					FoundClass, Object, new FName(NAME_None));

				return Object;
			}

			return InvalidManagedHandle;
		}

		FRegisterName()
		{
			FClassBuilder(TEXT("FName"), NAMESPACE_LIBRARY)
				.Function("Register", RegisterImplementation)
				.Function("Identical", IdenticalImplementation)
				.Function("GetTypeHash", GetTypeHashImplementation)
				.Function("UnRegister", UnRegisterImplementation)
				.Function("ToString", ToStringImplementation)
				.Function("NAME_None", NAME_NoneImplementation);
		}
	};

	[[maybe_unused]] FRegisterName RegisterName;
}
