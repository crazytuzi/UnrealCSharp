#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Domain/Script/IManagedHandle.h"
#include "Domain/Script/IUnmanagedBool.h"
#include "Reflection/FReflectionRegistry.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterScriptInterface
	{
		static void RegisterImplementation(const IManagedObject InManagedObject, const IManagedHandle InObject,
		                                   const IManagedReflectionType InManagedReflectionType)
		{
			const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject);

			const auto ScriptInterface = new TScriptInterface<IInterface>(FoundObject);

			const auto Class = FReflectionRegistry::Get().GetClass(InManagedReflectionType);

			FCSharpEnvironment::GetEnvironment().AddMultiReference<TScriptInterface<IInterface>, true, false>(
				Class, MANAGED_HANDLE_FROM_OBJECT(InManagedObject), ScriptInterface);
		}

		static IUnmanagedBool IdenticalImplementation(const IManagedHandle InA, const IManagedHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().
				GetMulti<TScriptInterface<IInterface>>(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().
					GetMulti<TScriptInterface<IInterface>>(InB))
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
				(void)FCSharpEnvironment::GetEnvironment().RemoveMultiReference<TScriptInterface<IInterface>>(
					InManagedHandle);
			});
		}

		static IManagedObject GetObjectImplementation(const IManagedHandle InManagedHandle)
		{
			const auto Multi = FCSharpEnvironment::GetEnvironment().GetMulti<TScriptInterface<IInterface>>(
				InManagedHandle);

			return FCSharpEnvironment::GetEnvironment().Bind(Multi->GetObject());
		}

		FRegisterScriptInterface()
		{
			FClassBuilder(TEXT("TScriptInterface"), NAMESPACE_LIBRARY)
				.Function("Register", RegisterImplementation)
				.Function("Identical", IdenticalImplementation)
				.Function("UnRegister", UnRegisterImplementation)
				.Function("GetObject", GetObjectImplementation);
		}
	};

	[[maybe_unused]] FRegisterScriptInterface RegisterScriptInterface;
}
