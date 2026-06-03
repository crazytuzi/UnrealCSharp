#include "UEVersion.h"
#if UE_F_UTF8_STR_PROPERTY
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Domain/Script/IManagedHandle.h"
#include "Domain/Script/IManagedMarshalledString.h"
#include "Domain/Script/IUnmanagedBool.h"
#include "Reflection/FReflectionRegistry.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterUtf8String
	{
		static void RegisterImplementation(const IManagedObject InManagedObject,
		                                   const IManagedMarshalledString InManagedMarshalledString)
		{
			const auto Utf8String = new FUtf8String(MANAGED_MARSHALLED_STRING_TO_F_STRING(InManagedMarshalledString));

			FCSharpEnvironment::GetEnvironment().AddStringReference<FUtf8String, true, false>(
				FReflectionRegistry::Get().GetUtf8StringClass(),
				MANAGED_HANDLE_FROM_OBJECT(InManagedObject), Utf8String);
		}

		static IUnmanagedBool IdenticalImplementation(const IManagedHandle InA, const IManagedHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetString<FUtf8String>(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetString<FUtf8String>(InB))
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
				(void)FCSharpEnvironment::GetEnvironment().RemoveStringReference<
					FUtf8String>(InManagedHandle);
			});
		}

		static IManagedString ToStringImplementation(const IManagedHandle InManagedHandle)
		{
			const auto Utf8String = FCSharpEnvironment::GetEnvironment().GetString<FUtf8String>(InManagedHandle);

			return MANAGED_MARSHALLED_STRING_NEW(TCHAR_TO_UTF8(*FUtf8String(*Utf8String)));
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
