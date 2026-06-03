#include "UEVersion.h"
#if UE_F_UTF8_STR_PROPERTY
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
	struct FRegisterAnsiString
	{
		static void RegisterImplementation(const IManagedObject InManagedObject, const IManagedMarshalledString InValue)
		{
			const auto AnsiString = new FAnsiString(MANAGED_MARSHALLED_STRING_TO_F_STRING(InValue));

			FCSharpEnvironment::GetEnvironment().AddStringReference<FAnsiString, true, false>(
				FReflectionRegistry::Get().GetAnsiStringClass(), MANAGED_HANDLE_FROM_OBJECT(InManagedObject),
				AnsiString);
		}

		static IUnmanagedBool IdenticalImplementation(const IManagedHandle InA, const IManagedHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetString<FAnsiString>(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetString<FAnsiString>(InB))
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
					FAnsiString>(InManagedHandle);
			});
		}

		static IManagedString ToStringImplementation(const IManagedHandle InManagedHandle)
		{
			const auto AnsiString = FCSharpEnvironment::GetEnvironment().GetString<FAnsiString>(InManagedHandle);

			return AnsiString != nullptr
				       ? MANAGED_MARSHALLED_STRING_NEW(TCHAR_TO_UTF8(*FAnsiString(*AnsiString)))
				       : INVALID_MANAGED;
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
