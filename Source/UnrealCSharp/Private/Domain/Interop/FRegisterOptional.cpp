#include "UEVersion.h"
#if UE_F_OPTIONAL_PROPERTY
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Domain/Script/IManagedTypes.h"
#include "Domain/Script/IUnmanagedBool.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"
#include "Reflection/Optional/FOptionalHelper.h"
#include "UObject/PropertyOptional.h"

namespace
{
	struct FRegisterOptional
	{
		static void Register1Implementation(const IManagedObject InManagedObject,
		                                    const IManagedReflectionType InManagedReflectionType)
		{
			const auto Class = FReflectionRegistry::Get().GetClass(InManagedReflectionType);

			const auto OptionalProperty = new FOptionalProperty(nullptr, "", EObjectFlags::RF_Transient);

			const auto ValueProperty = FTypeBridge::Factory(Class->GetGenericArgument(),
			                                                OptionalProperty, "",
			                                                EObjectFlags::RF_Transient);

			ValueProperty->SetPropertyFlags(CPF_HasGetValueTypeHash);

			OptionalProperty->SetValueProperty(ValueProperty);

			const auto OptionalHelper = new FOptionalHelper(OptionalProperty, nullptr, true, true);

			FCSharpEnvironment::GetEnvironment().AddOptionalReference<FOptionalHelper, false>(
				nullptr, OptionalHelper, Class, MANAGED_HANDLE_FROM_OBJECT(InManagedObject));
		}

		static void Register2Implementation(const IManagedObject InManagedObject, const IManagedObject InValue,
		                                    const IManagedReflectionType InManagedReflectionType)
		{
			const auto Class = FReflectionRegistry::Get().GetClass(InManagedReflectionType);

			const auto OptionalProperty = new FOptionalProperty(nullptr, "", EObjectFlags::RF_Transient);

			const auto ValueProperty = FTypeBridge::Factory(Class->GetGenericArgument(),
			                                                OptionalProperty, "",
			                                                EObjectFlags::RF_Transient);

			ValueProperty->SetPropertyFlags(CPF_HasGetValueTypeHash);

			OptionalProperty->SetValueProperty(ValueProperty);

			const auto OptionalHelper = new FOptionalHelper(OptionalProperty, nullptr, true, true);

			FCSharpEnvironment::GetEnvironment().AddOptionalReference<FOptionalHelper, false>(
				nullptr, OptionalHelper, Class, MANAGED_HANDLE_FROM_OBJECT(InManagedObject));

			if (OptionalHelper->GetValuePropertyDescriptor()->IsPrimitiveProperty())
			{
				OptionalHelper->Set(FDomain::Object_Unbox(MANAGED_HANDLE_FROM_OBJECT(InValue)));
			}
			else
			{
				auto ManagedHandle = Class->GetGenericArgument()->GetGCHandle(InValue);

				OptionalHelper->Set(&ManagedHandle);
			}
		}

		static IUnmanagedBool IdenticalImplementation(const IManagedHandle InA, const IManagedHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetOptional(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetOptional(InB))
				{
					return BoolToIUnmanagedBool(FOptionalHelper::Identical(FoundA, FoundB));
				}
			}

			return IUnmanagedFalse;
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
			if (const auto OptionalHelper = FCSharpEnvironment::GetEnvironment().GetOptional(
				InManagedHandle))
			{
				OptionalHelper->Reset();
			}
		}

		static IUnmanagedBool IsSetImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto OptionalHelper = FCSharpEnvironment::GetEnvironment().GetOptional(
				InManagedHandle))
			{
				return BoolToIUnmanagedBool(OptionalHelper->IsSet());
			}

			return IUnmanagedFalse;
		}

		static IManagedObject GetImplementation(const IManagedHandle InManagedHandle)
		{
			IManagedObject ReturnValue{};

			if (const auto OptionalHelper = FCSharpEnvironment::GetEnvironment().GetOptional(
				InManagedHandle))
			{
				const auto Value = OptionalHelper->Get();

				OptionalHelper->GetValuePropertyDescriptor()->Get(Value, reinterpret_cast<void**>(&ReturnValue));
			}

			return ReturnValue;
		}

		static void SetImplementation(const IManagedHandle InManagedHandle,
		                              const IManagedObject InValue, const IManagedReflectionType InReflectionType)
		{
			if (const auto OptionalHelper = FCSharpEnvironment::GetEnvironment().GetOptional(
				InManagedHandle))
			{
				if (OptionalHelper->GetValuePropertyDescriptor()->IsPrimitiveProperty())
				{
					OptionalHelper->Set(FDomain::Object_Unbox(MANAGED_HANDLE_FROM_OBJECT(InValue)));
				}
				else
				{
					const auto Class = FReflectionRegistry::Get().GetClass(InReflectionType);

					auto ManagedHandle = Class->GetGenericArgument()->GetGCHandle(InValue);

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
