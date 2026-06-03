#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Domain/Script/IManagedHandle.h"
#include "Domain/Script/IUnmanagedBool.h"
#include "Reflection/FReflectionRegistry.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterWeakObjectPtr
	{
		static void RegisterImplementation(const IManagedObject InManagedObject, const IManagedHandle InObject,
		                                   const IManagedReflectionType InManagedReflectionType)
		{
			const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject);

			const auto WeakObjectPtr = new TWeakObjectPtr<UObject>(FoundObject);

			const auto Class = FReflectionRegistry::Get().GetClass(InManagedReflectionType);

			FCSharpEnvironment::GetEnvironment().AddMultiReference<TWeakObjectPtr<UObject>, true, false>(
				Class, MANAGED_HANDLE_FROM_OBJECT(InManagedObject), WeakObjectPtr);
		}

		static IUnmanagedBool IdenticalImplementation(const IManagedHandle InA, const IManagedHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetMulti<TWeakObjectPtr<UObject>>(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetMulti<TWeakObjectPtr<UObject>>(InB))
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
				(void)FCSharpEnvironment::GetEnvironment().RemoveMultiReference<TWeakObjectPtr<UObject>>(
					InManagedHandle);
			});
		}

		static IManagedObject GetImplementation(const IManagedHandle InManagedHandle)
		{
			const auto Multi = FCSharpEnvironment::GetEnvironment()
				.GetMulti<TWeakObjectPtr<UObject>>(InManagedHandle);

			return FCSharpEnvironment::GetEnvironment().Bind(Multi->Get());
		}

		FRegisterWeakObjectPtr()
		{
			FClassBuilder(TEXT("TWeakObjectPtr"), NAMESPACE_LIBRARY)
				.Function("Register", RegisterImplementation)
				.Function("Identical", IdenticalImplementation)
				.Function("UnRegister", UnRegisterImplementation)
				.Function("Get", GetImplementation);
		}
	};

	[[maybe_unused]] FRegisterWeakObjectPtr RegisterWeakObjectPtr;
}
