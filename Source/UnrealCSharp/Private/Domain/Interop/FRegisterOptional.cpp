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
		static void Register1Implementation(const IManagedHandle InManagedObject, const IManagedHandle InManagedType)
		{
			const auto Class = FReflectionRegistry::Get().GetClass(InManagedType);

			const auto OptionalProperty = new FOptionalProperty(nullptr, "", EObjectFlags::RF_Transient);

			const auto ValueProperty = FTypeBridge::Factory(Class->GetGenericArgument(),
			                                                OptionalProperty, "",
			                                                EObjectFlags::RF_Transient);

			ValueProperty->SetPropertyFlags(CPF_HasGetValueTypeHash);

			OptionalProperty->SetValueProperty(ValueProperty);

			const auto OptionalHelper = new FOptionalHelper(OptionalProperty, nullptr, true, true);

			FCSharpEnvironment::GetEnvironment().AddOptionalReference<FOptionalHelper, false>(
				nullptr, OptionalHelper, Class, InManagedObject);
		}

		static void Register2Implementation(const IManagedHandle InManagedObject,
		                                    const IManagedHandle InValue, const IManagedHandle InManagedType)
		{
			const auto Class = FReflectionRegistry::Get().GetClass(InManagedType);

			const auto OptionalProperty = new FOptionalProperty(nullptr, "", EObjectFlags::RF_Transient);

			const auto ValueProperty = FTypeBridge::Factory(Class->GetGenericArgument(),
			                                                OptionalProperty, "",
			                                                EObjectFlags::RF_Transient);

			ValueProperty->SetPropertyFlags(CPF_HasGetValueTypeHash);

			OptionalProperty->SetValueProperty(ValueProperty);

			const auto OptionalHelper = new FOptionalHelper(OptionalProperty, nullptr, true, true);

			FCSharpEnvironment::GetEnvironment().AddOptionalReference<FOptionalHelper, false>(
				nullptr, OptionalHelper, Class, InManagedObject);

			if (OptionalHelper->GetValuePropertyDescriptor()->IsPrimitiveProperty())
			{
				OptionalHelper->Set(FDomain::Object_Unbox(InValue));
			}
			else
			{
				auto ManagedHandle = InValue;

				OptionalHelper->Set(&ManagedHandle);
			}
		}

		static uint8 IdenticalImplementation(const IManagedHandle InA, const IManagedHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetOptional(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetOptional(InB))
				{
					return FOptionalHelper::Identical(FoundA, FoundB) ? 1 : 0;
				}
			}

			return 0;
		}

		static void UnRegisterImplementation(const IManagedHandle InManagedHandle)
		{
			AsyncTask(ENamedThreads::GameThread, [InManagedHandle]
			{
				(void)FCSharpEnvironment::GetEnvironment().RemoveOptionalReference(InManagedHandle);
			});
		}

		static void ResetImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto OptionalHelper = FCSharpEnvironment::GetEnvironment().GetOptional(InManagedHandle))
			{
				OptionalHelper->Reset();
			}
		}

		static uint8 IsSetImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto OptionalHelper = FCSharpEnvironment::GetEnvironment().GetOptional(InManagedHandle))
			{
				return OptionalHelper->IsSet() ? 1 : 0;
			}

			return 0;
		}

		static IManagedHandle GetImplementation(const IManagedHandle InManagedHandle)
		{
			IManagedHandle ReturnValue{};

			if (const auto OptionalHelper = FCSharpEnvironment::GetEnvironment().GetOptional(InManagedHandle))
			{
				const auto Value = OptionalHelper->Get();

				OptionalHelper->GetValuePropertyDescriptor()->Get(Value, reinterpret_cast<void**>(&ReturnValue));
			}

			return ReturnValue;
		}

		static void SetImplementation(const IManagedHandle InManagedHandle, const IManagedHandle InValue)
		{
			if (const auto OptionalHelper = FCSharpEnvironment::GetEnvironment().GetOptional(InManagedHandle))
			{
				if (OptionalHelper->GetValuePropertyDescriptor()->IsPrimitiveProperty())
				{
					OptionalHelper->Set(FDomain::Object_Unbox(InValue));
				}
				else
				{
					auto ManagedHandle = InValue;

					OptionalHelper->Set(&ManagedHandle);
				}
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
