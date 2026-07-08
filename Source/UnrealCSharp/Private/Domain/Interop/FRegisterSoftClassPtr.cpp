#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Domain/Script/IManagedHandle.h"
#include "Reflection/FReflectionRegistry.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterSoftClassPtr
	{
		static void RegisterImplementation(const IManagedHandle InManagedObject,
		                                   const IManagedHandle InClass, const IManagedHandle InManagedType)
		{
			const auto FoundClass = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(InClass);

			const auto SoftClassPtr = new TSoftClassPtr<UObject>(FoundClass);

			const auto Class = FReflectionRegistry::Get().GetClass(InManagedType);

			FCSharpEnvironment::GetEnvironment().AddMultiReference<TSoftClassPtr<UObject>, true, false>(
				Class, InManagedObject, SoftClassPtr);
		}

		static uint8 IdenticalImplementation(const IManagedHandle InA, const IManagedHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftClassPtr<UObject>>(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftClassPtr<UObject>>(InB))
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
				(void)FCSharpEnvironment::GetEnvironment().RemoveMultiReference<TSoftClassPtr<UObject>>(
					InManagedHandle);
			});
		}

		static IManagedHandle GetImplementation(const IManagedHandle InManagedHandle)
		{
			const auto Multi = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftClassPtr<UObject>>(
				InManagedHandle);

			return FCSharpEnvironment::GetEnvironment().Bind(Multi->Get());
		}

		static IManagedHandle LoadSynchronousImplementation(const IManagedHandle InManagedHandle)
		{
			const auto Multi = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftClassPtr<UObject>>(
				InManagedHandle);

			return FCSharpEnvironment::GetEnvironment().Bind(Multi->LoadSynchronous());
		}

		FRegisterSoftClassPtr()
		{
			FClassBuilder(TEXT("TSoftClassPtr"), NAMESPACE_LIBRARY)
				.Function("Register", RegisterImplementation)
				.Function("Identical", IdenticalImplementation)
				.Function("UnRegister", UnRegisterImplementation)
				.Function("Get", GetImplementation)
				.Function("LoadSynchronous", LoadSynchronousImplementation);
		}
	};

	[[maybe_unused]] FRegisterSoftClassPtr RegisterSoftClassPtr;
}
