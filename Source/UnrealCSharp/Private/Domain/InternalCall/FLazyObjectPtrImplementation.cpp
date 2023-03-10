#include "Domain/InternalCall/FLazyObjectPtrImplementation.h"
#include "Binding/Class/FBindingClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"
#include "FUnrealCSharpFunctionLibrary.h"

struct FRegisterLazyObjectPtr
{
	FRegisterLazyObjectPtr()
	{
		FBindingClassBuilder(TEXT("LazyObjectPtr"), NAMESPACE_LIBRARY)
			.Function("Register",
			          static_cast<void*>(FLazyObjectPtrImplementation::LazyObjectPtr_RegisterImplementation))
			.Function("UnRegister",
			          static_cast<void*>(FLazyObjectPtrImplementation::LazyObjectPtr_UnRegisterImplementation))
			.Function("Get",
			          static_cast<void*>(FLazyObjectPtrImplementation::LazyObjectPtr_GetImplementation))
			.Register();
	}
};

static FRegisterLazyObjectPtr RegisterLazyObjectPtr;

void FLazyObjectPtrImplementation::LazyObjectPtr_RegisterImplementation(MonoObject* InMonoObject,
                                                                        const MonoObject* InObject)
{
	const auto FoundObject = FCSharpEnvironment::GetEnvironment()->GetObject(InObject);

	FCSharpEnvironment::GetEnvironment()->AddMultiReference<TLazyObjectPtr<UObject>>(InMonoObject, FoundObject);
}

void FLazyObjectPtrImplementation::LazyObjectPtr_UnRegisterImplementation(const MonoObject* InMonoObject)
{
	FCSharpEnvironment::GetEnvironment()->RemoveMultiReference<TLazyObjectPtr<UObject>>(InMonoObject);
}

void FLazyObjectPtrImplementation::LazyObjectPtr_GetImplementation(const MonoObject* InMonoObject,
                                                                   MonoObject** OutValue)
{
	const auto Multi = FCSharpEnvironment::GetEnvironment()->GetMulti<TLazyObjectPtr<UObject>>(InMonoObject);

	auto FoundMonoObject = FCSharpEnvironment::GetEnvironment()->GetObject(Multi.Get());

	if (FoundMonoObject == nullptr)
	{
		const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetDomain()->Class_From_Name(
			FUnrealCSharpFunctionLibrary::GetClassNameSpace(Multi->GetClass()),
			FUnrealCSharpFunctionLibrary::GetFullClass(Multi->GetClass()));

		FoundMonoObject = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_New(FoundMonoClass);

		FCSharpEnvironment::GetEnvironment()->Bind(Multi->GetClass(), false);

		FCSharpEnvironment::GetEnvironment()->AddObjectReference(Multi.Get(), FoundMonoObject);
	}

	*OutValue = FoundMonoObject;
}
