#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"
#include "UObject/Field.h"

namespace
{
	struct FRegisterFieldPath
	{
		static void Register1Implementation(const IManagedHandle InManagedObject)
		{
			FCSharpEnvironment::GetEnvironment().AddFieldPathReference<true, false>(
				nullptr, InManagedObject, new FFieldPath());
		}

		static void Register2Implementation(const IManagedHandle InManagedObject, const IManagedHandle InManagedField)
		{
			if (const auto Field = FCSharpEnvironment::GetEnvironment().GetField(InManagedField))
			{
				FCSharpEnvironment::GetEnvironment().AddFieldPathReference<true, false>(
					nullptr, InManagedObject, new FFieldPath(Field));
			}
		}

		static uint8 IdenticalImplementation(const IManagedHandle InA, const IManagedHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetFieldPath(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetFieldPath(InB))
				{
					return *FoundA == *FoundB ? 1 : 0;
				}
			}

			return 0;
		}

		static void UnRegisterImplementation(const IManagedHandle InManagedHandle)
		{
			if (IsInGameThread())
			{
				(void)FCSharpEnvironment::GetEnvironment().RemoveFieldPathReference(InManagedHandle);
			}
			else
			{
				AsyncTask(ENamedThreads::GameThread, [InManagedHandle]
				{
					(void)FCSharpEnvironment::GetEnvironment().RemoveFieldPathReference(InManagedHandle);
				});
			}
		}

		static void ResetImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto FieldPath = FCSharpEnvironment::GetEnvironment().GetFieldPath(InManagedHandle))
			{
				FieldPath->Reset();
			}
		}

		static uint8 IsValidImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto FieldPath = FCSharpEnvironment::GetEnvironment().GetFieldPath(InManagedHandle))
			{
				return FieldPath->GetTyped(FField::StaticClass()) != nullptr ? 1 : 0;
			}

			return 0;
		}

		static IManagedHandle GetImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto FieldPath = FCSharpEnvironment::GetEnvironment().GetFieldPath(InManagedHandle))
			{
				return FCSharpEnvironment::GetEnvironment().GetFieldObject(
					FieldPath->GetTyped(FField::StaticClass()));
			}

			return InvalidManagedHandle;
		}

		static void SetImplementation(const IManagedHandle InManagedHandle, const IManagedHandle InManagedField)
		{
			if (const auto FieldPath = FCSharpEnvironment::GetEnvironment().GetFieldPath(InManagedHandle))
			{
				if (const auto Field = FCSharpEnvironment::GetEnvironment().GetField(InManagedField))
				{
					FieldPath->Generate(Field);
				}
			}
		}

		FRegisterFieldPath()
		{
			FClassBuilder(TEXT("TFieldPath"), NAMESPACE_LIBRARY)
				.Function("Register1", Register1Implementation)
				.Function("Register2", Register2Implementation)
				.Function("Identical", IdenticalImplementation)
				.Function("UnRegister", UnRegisterImplementation)
				.Function("Reset", ResetImplementation)
				.Function("IsValid", IsValidImplementation)
				.Function("Get", GetImplementation)
				.Function("Set", SetImplementation);
		}
	};

	[[maybe_unused]] FRegisterFieldPath RegisterFieldPath;
}
