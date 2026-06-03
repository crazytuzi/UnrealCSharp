#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Domain/Script/IManagedHandle.h"
#include "Domain/Script/IUnmanagedBool.h"
#include "Domain/Script/IManagedMarshalledString.h"
#include "Reflection/FReflectionRegistry.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterString
	{
		static void RegisterImplementation(const IManagedObject InManagedObject, const IManagedMarshalledString InValue)
		{
			const auto String = new FString(MANAGED_MARSHALLED_STRING_TO_F_STRING(InValue));

			FCSharpEnvironment::GetEnvironment().AddStringReference<FString, true, false>(
				FReflectionRegistry::Get().GetStringClass(), MANAGED_HANDLE_FROM_OBJECT(InManagedObject), String);
		}

		static IUnmanagedBool IdenticalImplementation(const IManagedHandle InA, const IManagedHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetString<FString>(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetString<FString>(InB))
				{
					return BoolToIUnmanagedBool(*FoundA == *FoundB);
				}
			}

			return IUnmanagedFalse;
		}

		static void UnRegisterImplementation(const IManagedHandle InManagedHandle)
		{
			AsyncTask(ENamedThreads::GameThread, [InManagedHandle]
			{
				(void)FCSharpEnvironment::GetEnvironment().RemoveStringReference<FString>(InManagedHandle);
			});
		}

		static IManagedString ToStringImplementation(const IManagedHandle InManagedHandle)
		{
			const auto String = FCSharpEnvironment::GetEnvironment().GetString<FString>(InManagedHandle);

			return MANAGED_MARSHALLED_STRING_NEW(TCHAR_TO_UTF8(**String));
		}

		FRegisterString()
		{
			FClassBuilder(TEXT("FString"), NAMESPACE_LIBRARY)
				.Function("Register", RegisterImplementation)
				.Function("Identical", IdenticalImplementation)
				.Function("UnRegister", UnRegisterImplementation)
				.Function("ToString", ToStringImplementation);
		}
	};

	[[maybe_unused]] FRegisterString RegisterString;
}
