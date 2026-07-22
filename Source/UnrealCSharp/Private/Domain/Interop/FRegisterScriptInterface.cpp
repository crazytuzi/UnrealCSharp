#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Domain/Script/IManagedHandle.h"
#include "Reflection/FReflectionRegistry.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"
#include "UEVersion.h"

namespace
{
	struct FRegisterScriptInterface
	{
		static void RegisterImplementation(const IManagedHandle InManagedObject,
		                                   const IManagedHandle InObject, const IManagedHandle InManagedType)
		{
			const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject);

#if UE_T_SCRIPT_INTERFACE_CONSTRUCTOR_U_OBJECT
			const auto ScriptInterface = new TScriptInterface<IInterface>(FoundObject);
#else
			const auto ScriptInterface = new TScriptInterface<IInterface>();

			ScriptInterface->SetObject(FoundObject);

			static_cast<FScriptInterface*>(ScriptInterface)->SetInterface(FoundObject);
#endif

			const auto Class = FReflectionRegistry::Get().GetClass(InManagedType);

			FCSharpEnvironment::GetEnvironment().AddMultiReference<TScriptInterface<IInterface>, true, false>(
				Class, InManagedObject, ScriptInterface);
		}

		static uint8 IdenticalImplementation(const IManagedHandle InA, const IManagedHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().
				GetMulti<TScriptInterface<IInterface>>(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().
					GetMulti<TScriptInterface<IInterface>>(InB))
				{
#if UE_T_SCRIPT_INTERFACE_CONSTRUCTOR_U_OBJECT
					return *FoundA == *FoundB ? 1 : 0;
#else
					return FoundA->GetObject() == FoundB->GetObject() ? 1 : 0;
#endif
				}
			}

			return 0;
		}

		static void UnRegisterImplementation(const IManagedHandle InManagedHandle)
		{
			AsyncTask(ENamedThreads::GameThread, [InManagedHandle]
			{
				(void)FCSharpEnvironment::GetEnvironment().RemoveMultiReference<TScriptInterface<IInterface>>(
					InManagedHandle);
			});
		}

		static IManagedHandle GetObjectImplementation(const IManagedHandle InManagedHandle)
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
