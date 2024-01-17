﻿#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterLazyObjectPtr
{
	static void RegisterImplementation(MonoObject* InMonoObject, const FGarbageCollectionHandle InObject)
	{
		const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject);

		const auto LazyObjectPtr = new TLazyObjectPtr<UObject>(FoundObject);

		FCSharpEnvironment::GetEnvironment().AddMultiReference<TLazyObjectPtr<UObject>>(InMonoObject, LazyObjectPtr);
	}

	static bool IdenticalImplementation(const FGarbageCollectionHandle InA, const FGarbageCollectionHandle InB)
	{
		if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetMulti<TLazyObjectPtr<UObject>>(InA))
		{
			if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetMulti<TLazyObjectPtr<UObject>>(InB))
			{
				return *FoundA == *FoundB;
			}
		}

		return false;
	}

	static void UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
	{
		(void)FCSharpEnvironment::GetEnvironment().RemoveMultiReference<TLazyObjectPtr<UObject>>(
			InGarbageCollectionHandle);
	}

	static MonoObject* GetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
	{
		const auto Multi = FCSharpEnvironment::GetEnvironment().GetMulti<TLazyObjectPtr<
			UObject>>(InGarbageCollectionHandle);

		return FCSharpEnvironment::GetEnvironment().Bind(Multi->Get());
	}

	FRegisterLazyObjectPtr()
	{
		FClassBuilder(TEXT("TLazyObjectPtr"), NAMESPACE_LIBRARY)
			.Function("Register", RegisterImplementation)
			.Function("Identical", IdenticalImplementation)
			.Function("UnRegister", UnRegisterImplementation)
			.Function("Get", GetImplementation)
			.Register();
	}
};

static FRegisterLazyObjectPtr RegisterLazyObjectPtr;
