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
	struct FRegisterName
	{
		static void RegisterImplementation(const IManagedObject InManagedObject, const IManagedMarshalledString InValue)
		{
			const auto Name = new FName(MANAGED_MARSHALLED_STRING_TO_F_STRING(InValue));

			FCSharpEnvironment::GetEnvironment().AddStringReference<FName, true, false>(
				FReflectionRegistry::Get().GetNameClass(), MANAGED_HANDLE_FROM_OBJECT(InManagedObject), Name);
		}

		static IUnmanagedBool IdenticalImplementation(const IManagedHandle InA, const IManagedHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetString<FName>(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetString<FName>(InB))
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
				(void)FCSharpEnvironment::GetEnvironment().RemoveStringReference<FName>(InManagedHandle);
			});
		}

		static IManagedString ToStringImplementation(const IManagedHandle InManagedHandle)
		{
			const auto Name = FCSharpEnvironment::GetEnvironment().GetString<FName>(InManagedHandle);

			return MANAGED_MARSHALLED_STRING_NEW(TCHAR_TO_UTF8(*Name->ToString()));
		}

		static IManagedObject NAME_NoneImplementation()
		{
			const auto FoundClass = TPropertyClass<FName, FName>::Get();

			const auto Object = FoundClass->NewObject();

			FCSharpEnvironment::GetEnvironment().AddStringReference<FName, true, false>(
				FoundClass, Object, new FName(NAME_None));

			return IManagedHandleToIManagedObject(Object);
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
