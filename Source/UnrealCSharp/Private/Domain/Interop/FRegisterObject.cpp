#include "Engine/World.h"
#include "Binding/Class/TBindingClassBuilder.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Domain/Script/IManagedHandle.h"
#include "Domain/Script/IScriptDomain.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/CompilerMacro.h"
#include "Macro/BindingMacro.h"

PRAGMA_DISABLE_DANGLING_WARNINGS

namespace
{
	struct FRegisterObject
	{
		static uint8 IdenticalImplementation(const IManagedHandle InA, const IManagedHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetObject(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetObject(InB))
				{
					return FoundA == FoundB ? 1 : 0;
				}
			}

			return 0;
		}

		static IManagedHandle StaticClassImplementation(const char* InClassName)
		{
			const auto ClassName = InClassName != nullptr ? FString(UTF8_TO_TCHAR(InClassName)) : FString(TEXT(""));

			const auto InClass = LoadObject<UClass>(nullptr, *ClassName);

			return FCSharpEnvironment::GetEnvironment().Bind(InClass);
		}

		static IManagedHandle GetClassImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InManagedHandle))
			{
				const auto Class = FoundObject->GetClass();

				return FCSharpEnvironment::GetEnvironment().Bind(Class);
			}

			return InvalidManagedHandle;
		}

		static IManagedHandle GetNameImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InManagedHandle))
			{
				const auto Name = FoundObject->GetName();

				return IScriptDomain::Get()->NewString(TCHAR_TO_UTF8(*Name));
			}

			return InvalidManagedHandle;
		}

		static uint8 IsValidImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InManagedHandle))
			{
				return IsValid(FoundObject) ? 1 : 0;
			}

			return 0;
		}

		static uint8 IsAImplementation(const IManagedHandle InManagedHandle, const IManagedHandle SomeBase)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InManagedHandle))
			{
				if (const auto FoundClass = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(SomeBase))
				{
					return FoundObject->IsA(FoundClass) ? 1 : 0;
				}
			}

			return 0;
		}

		static void AddToRootImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InManagedHandle))
			{
				FoundObject->AddToRoot();
			}
		}

		static void RemoveFromRootImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InManagedHandle))
			{
				FoundObject->RemoveFromRoot();
			}
		}

		static uint8 IsRootedImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InManagedHandle))
			{
				return FoundObject->IsRooted() ? 1 : 0;
			}

			return 0;
		}

		static uint8 AddReferenceImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InManagedHandle))
			{
				return FCSharpEnvironment::GetEnvironment().AddReference(FoundObject) ? 1 : 0;
			}

			return 0;
		}

		static uint8 RemoveReferenceImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InManagedHandle))
			{
				return FCSharpEnvironment::GetEnvironment().RemoveReference(FoundObject) ? 1 : 0;
			}

			return 0;
		}

		FRegisterObject()
		{
			TBindingClassBuilder<UObject>(NAMESPACE_LIBRARY)
				.Function("Identical", IdenticalImplementation)
				.Function("StaticClass", StaticClassImplementation)
				.Function("GetClass", GetClassImplementation)
				.Function("GetName", GetNameImplementation)
				.Function("GetWorld", BINDING_FUNCTION(&UObject::GetWorld))
				.Function("IsValid", IsValidImplementation)
				.Function("IsA", IsAImplementation)
				.Function("AddToRoot", AddToRootImplementation)
				.Function("RemoveFromRoot", RemoveFromRootImplementation)
				.Function("IsRooted", IsRootedImplementation)
				.Function("AddReference", AddReferenceImplementation)
				.Function("RemoveReference", RemoveReferenceImplementation);
		}
	};

	[[maybe_unused]] FRegisterObject RegisterObject;
}

PRAGMA_ENABLE_DANGLING_WARNINGS
