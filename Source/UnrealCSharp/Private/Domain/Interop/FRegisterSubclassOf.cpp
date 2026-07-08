#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Domain/Script/IManagedHandle.h"
#include "Reflection/FReflectionRegistry.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterSubclassOf
	{
		static void RegisterImplementation(const IManagedHandle InManagedObject,
		                                   const IManagedHandle InClass, const IManagedHandle InManagedType)
		{
			const auto FoundClass = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(InClass);

			const auto SubclassOf = new TSubclassOf<UObject>(FoundClass);

			const auto Class = FReflectionRegistry::Get().GetClass(InManagedType);

			FCSharpEnvironment::GetEnvironment().AddMultiReference<TSubclassOf<UObject>, true, false>(
				Class, InManagedObject, SubclassOf);
		}

		static uint8 IdenticalImplementation(const IManagedHandle InA, const IManagedHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetMulti<TSubclassOf<UObject>>(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetMulti<TSubclassOf<UObject>>(InB))
				{
					return *FoundA == *FoundB ? 1 : 0;
				}
			}

			return 0;
		}

		static void UnRegisterImplementation(const IManagedHandle InManagedHandle)
		{
			AsyncTask(ENamedThreads::GameThread, [InManagedHandle]
			{
				(void)FCSharpEnvironment::GetEnvironment().RemoveMultiReference<TSubclassOf<UObject>>(InManagedHandle);
			});
		}

		static IManagedHandle GetImplementation(const IManagedHandle InManagedHandle)
		{
			const auto Multi = FCSharpEnvironment::GetEnvironment().GetMulti<TSubclassOf<UObject>>(
				InManagedHandle);

			return FCSharpEnvironment::GetEnvironment().Bind(Multi->Get());
		}

		FRegisterSubclassOf()
		{
			FClassBuilder(TEXT("TSubclassOf"), NAMESPACE_LIBRARY)
				.Function("Register", RegisterImplementation)
				.Function("Identical", IdenticalImplementation)
				.Function("UnRegister", UnRegisterImplementation)
				.Function("Get", GetImplementation);
		}
	};

	[[maybe_unused]] FRegisterSubclassOf RegisterSubclassOf;
}
