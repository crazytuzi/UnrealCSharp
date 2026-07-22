#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Domain/Script/IManagedHandle.h"
#include "Reflection/FReflectionRegistry.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterSoftObjectPtr
	{
		static void RegisterImplementation(const IManagedHandle InManagedObject,
		                                   const IManagedHandle InObject, const IManagedHandle InManagedType)
		{
			const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject);

			const auto SoftObjectPtr = new TSoftObjectPtr<UObject>(FoundObject);

			const auto Class = FReflectionRegistry::Get().GetClass(InManagedType);

			FCSharpEnvironment::GetEnvironment().AddMultiReference<TSoftObjectPtr<UObject>, true, false>(
				Class, InManagedObject, SoftObjectPtr);
		}

		static uint8 IdenticalImplementation(const IManagedHandle InA, const IManagedHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftObjectPtr<UObject>>(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftObjectPtr<UObject>>(InB))
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
				(void)FCSharpEnvironment::GetEnvironment().RemoveMultiReference<TSoftObjectPtr<UObject>>(
					InManagedHandle);
			});
		}

		static IManagedHandle GetImplementation(const IManagedHandle InManagedHandle)
		{
			const auto Multi = FCSharpEnvironment::GetEnvironment().
				GetMulti<TSoftObjectPtr<UObject>>(InManagedHandle);

			return FCSharpEnvironment::GetEnvironment().Bind(Multi->Get());
		}

		static IManagedHandle LoadSynchronousImplementation(const IManagedHandle InManagedHandle)
		{
			const auto Multi = FCSharpEnvironment::GetEnvironment().
				GetMulti<TSoftObjectPtr<UObject>>(InManagedHandle);

			return FCSharpEnvironment::GetEnvironment().Bind(Multi->LoadSynchronous());
		}

		FRegisterSoftObjectPtr()
		{
			FClassBuilder(TEXT("TSoftObjectPtr"), NAMESPACE_LIBRARY)
				.Function("Register", RegisterImplementation)
				.Function("Identical", IdenticalImplementation)
				.Function("UnRegister", UnRegisterImplementation)
				.Function("Get", GetImplementation)
				.Function("LoadSynchronous", LoadSynchronousImplementation);
		}
	};

	[[maybe_unused]] FRegisterSoftObjectPtr RegisterSoftObjectPtr;
}
