#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

namespace
{
	struct FRegisterScriptInterface
	{
		static void RegisterImplementation(MonoObject* InMonoObject, const FGarbageCollectionHandle InObject)
		{
			const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject);

			const auto ScriptInterface = new TScriptInterface<IInterface>(FoundObject);

			FCSharpEnvironment::GetEnvironment().AddMultiReference<TScriptInterface<IInterface>, true, false>(
				InMonoObject, ScriptInterface);
		}

		static bool IdenticalImplementation(const FGarbageCollectionHandle InA, const FGarbageCollectionHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().
				GetMulti<TScriptInterface<IInterface>>(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().
					GetMulti<TScriptInterface<IInterface>>(InB))
				{
					return *FoundA == *FoundB;
				}
			}

			return false;
		}

		static void UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			AsyncTask(ENamedThreads::GameThread, [InGarbageCollectionHandle]
			{
				(void)FCSharpEnvironment::GetEnvironment().RemoveMultiReference<TScriptInterface<IInterface>>(
					InGarbageCollectionHandle);
			});
		}

		static MonoObject* GetObjectImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			const auto Multi = FCSharpEnvironment::GetEnvironment().GetMulti<TScriptInterface<IInterface>>(
				InGarbageCollectionHandle);

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
