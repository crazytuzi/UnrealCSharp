#include "UEVersion.h"
#if UE_F_OPTIONAL_PROPERTY
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"
#include "Reflection/Optional/FOptionalHelper.h"
#include "UObject/PropertyOptional.h"

namespace
{
	struct FRegisterOptional
	{
		static void Register1Implementation(MonoObject* InMonoObject)
		{
			const auto OptionalProperty = new FOptionalProperty(nullptr, "", EObjectFlags::RF_Transient);

			const auto ValueProperty = FTypeBridge::Factory(FTypeBridge::GetGenericArgument(InMonoObject),
			                                                OptionalProperty, "",
			                                                EObjectFlags::RF_Transient);

			ValueProperty->SetPropertyFlags(CPF_HasGetValueTypeHash);

			OptionalProperty->SetValueProperty(ValueProperty);

			const auto OptionalHelper = new FOptionalHelper(OptionalProperty, nullptr, true, true);

			FCSharpEnvironment::GetEnvironment().AddOptionalReference<FOptionalHelper, false>(
				nullptr, OptionalHelper, InMonoObject);
		}

		static void Register2Implementation(MonoObject* InMonoObject, MonoObject* InValue)
		{
			const auto OptionalProperty = new FOptionalProperty(nullptr, "", EObjectFlags::RF_Transient);

			const auto ValueProperty = FTypeBridge::Factory(FTypeBridge::GetGenericArgument(InMonoObject),
			                                                OptionalProperty, "",
			                                                EObjectFlags::RF_Transient);

			ValueProperty->SetPropertyFlags(CPF_HasGetValueTypeHash);

			OptionalProperty->SetValueProperty(ValueProperty);

			const auto OptionalHelper = new FOptionalHelper(OptionalProperty, nullptr, true, true);

			FCSharpEnvironment::GetEnvironment().AddOptionalReference<FOptionalHelper, false>(
				nullptr, OptionalHelper, InMonoObject);

			OptionalHelper->Set(OptionalHelper->GetValuePropertyDescriptor()->IsPrimitiveProperty()
				                    ? FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InValue)
				                    : static_cast<void*>(
					                    FGarbageCollectionHandle::MonoObject2GarbageCollectionHandle(InValue)));
		}

		static bool IdenticalImplementation(const FGarbageCollectionHandle InA, const FGarbageCollectionHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetOptional(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetOptional(InB))
				{
					return FOptionalHelper::Identical(FoundA, FoundB);
				}
			}

			return false;
		}

		static void UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			AsyncTask(ENamedThreads::GameThread, [InGarbageCollectionHandle]
			{
				(void)FCSharpEnvironment::GetEnvironment().RemoveOptionalReference(InGarbageCollectionHandle);
			});
		}

		static void ResetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			if (const auto OptionalHelper = FCSharpEnvironment::GetEnvironment().GetOptional(
				InGarbageCollectionHandle))
			{
				OptionalHelper->Reset();
			}
		}

		static bool IsSetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			if (const auto OptionalHelper = FCSharpEnvironment::GetEnvironment().GetOptional(
				InGarbageCollectionHandle))
			{
				return OptionalHelper->IsSet();
			}

			return false;
		}

		static MonoObject* GetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			MonoObject* ReturnValue{};

			if (const auto OptionalHelper = FCSharpEnvironment::GetEnvironment().GetOptional(
				InGarbageCollectionHandle))
			{
				const auto Value = OptionalHelper->Get();

				OptionalHelper->GetValuePropertyDescriptor()->Get(Value, reinterpret_cast<void**>(&ReturnValue));
			}

			return ReturnValue;
		}

		static void SetImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                              MonoObject* InValue)
		{
			if (const auto OptionalHelper = FCSharpEnvironment::GetEnvironment().GetOptional(
				InGarbageCollectionHandle))
			{
				OptionalHelper->Set(OptionalHelper->GetValuePropertyDescriptor()->IsPrimitiveProperty()
					                    ? FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InValue)
					                    : static_cast<void*>(
						                    FGarbageCollectionHandle::MonoObject2GarbageCollectionHandle(InValue)));
			}
		}

		FRegisterOptional()
		{
			FClassBuilder(TEXT("TOptional"), NAMESPACE_LIBRARY, true)
				.Function("Register1", Register1Implementation)
				.Function("Register2", Register2Implementation)
				.Function("Identical", IdenticalImplementation)
				.Function("UnRegister", UnRegisterImplementation)
				.Function("Reset", ResetImplementation)
				.Function("IsSet", IsSetImplementation)
				.Function("Get", GetImplementation)
				.Function("Set", SetImplementation);
		}
	};

	[[maybe_unused]] FRegisterOptional RegisterOptional;
}
#endif
