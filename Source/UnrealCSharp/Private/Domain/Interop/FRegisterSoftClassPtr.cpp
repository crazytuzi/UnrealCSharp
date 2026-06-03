#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Domain/Script/IManagedHandle.h"
#include "Domain/Script/IUnmanagedBool.h"
#include "Reflection/FReflectionRegistry.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterSoftClassPtr
	{
		static void RegisterImplementation(const IManagedObject InManagedObject, const IManagedHandle InClass,
		                                   const IManagedReflectionType InManagedReflectionType)
		{
			const auto FoundClass = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(InClass);

			const auto SoftClassPtr = new TSoftClassPtr<UObject>(FoundClass);

			const auto Class = FReflectionRegistry::Get().GetClass(InManagedReflectionType);

			FCSharpEnvironment::GetEnvironment().AddMultiReference<TSoftClassPtr<UObject>, true, false>(
				Class, MANAGED_HANDLE_FROM_OBJECT(InManagedObject), SoftClassPtr);
		}

		static IUnmanagedBool IdenticalImplementation(const IManagedHandle InA, const IManagedHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftClassPtr<UObject>>(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftClassPtr<UObject>>(InB))
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
				(void)FCSharpEnvironment::GetEnvironment().RemoveMultiReference<TSoftClassPtr<UObject>>(
					InManagedHandle);
			});
		}

		static IManagedObject GetImplementation(const IManagedHandle InManagedHandle)
		{
			const auto Multi = FCSharpEnvironment::GetEnvironment().GetMulti<TSoftClassPtr<UObject>>(
				InManagedHandle);

			return FCSharpEnvironment::GetEnvironment().Bind(Multi->Get());
		}

		static IManagedObject LoadSynchronousImplementation(const IManagedHandle InManagedHandle)
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
