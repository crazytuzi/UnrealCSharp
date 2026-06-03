#include "Engine/World.h"
#include "Binding/Class/TBindingClassBuilder.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Domain/Script/IManagedHandle.h"
#include "Domain/Script/IUnmanagedBool.h"
#include "Domain/Script/IManagedMarshalledString.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/CompilerMacro.h"
#include "Macro/BindingMacro.h"

PRAGMA_DISABLE_DANGLING_WARNINGS

namespace
{
	struct FRegisterObject
	{
		static IUnmanagedBool IdenticalImplementation(const IManagedHandle InA, const IManagedHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetObject(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetObject(InB))
				{
					return BoolToIUnmanagedBool(FoundA == FoundB);
				}
			}

			return IUnmanagedFalse;
		}

		static IManagedObject StaticClassImplementation(IManagedMarshalledString InClassName)
		{
			const auto ClassName = MANAGED_MARSHALLED_STRING_TO_F_STRING(InClassName);

			const auto InClass = LoadObject<UClass>(nullptr, *ClassName);

			return FCSharpEnvironment::GetEnvironment().Bind(InClass);
		}

		static IManagedObject GetClassImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InManagedHandle))
			{
				const auto Class = FoundObject->GetClass();

				return FCSharpEnvironment::GetEnvironment().Bind(Class);
			}

			return INVALID_MANAGED;
		}

		static IManagedString GetNameImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InManagedHandle))
			{
				const auto Name = FoundObject->GetName();

				return MANAGED_MARSHALLED_STRING_NEW(TCHAR_TO_UTF8(*Name));
			}

			return INVALID_MANAGED;
		}

		static IUnmanagedBool IsValidImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InManagedHandle))
			{
				return BoolToIUnmanagedBool(IsValid(FoundObject));
			}

			return IUnmanagedFalse;
		}

		static IUnmanagedBool IsAImplementation(const IManagedHandle InManagedHandle,
		                                        const IManagedHandle SomeBase)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InManagedHandle))
			{
				if (const auto FoundClass = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(SomeBase))
				{
					return BoolToIUnmanagedBool(FoundObject->IsA(FoundClass));
				}
			}

			return IUnmanagedFalse;
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

		static IUnmanagedBool IsRootedImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InManagedHandle))
			{
				return BoolToIUnmanagedBool(FoundObject->IsRooted());
			}

			return IUnmanagedFalse;
		}

		static IUnmanagedBool AddReferenceImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InManagedHandle))
			{
				return BoolToIUnmanagedBool(FCSharpEnvironment::GetEnvironment().AddReference(FoundObject));
			}

			return IUnmanagedFalse;
		}

		static IUnmanagedBool RemoveReferenceImplementation(const IManagedHandle InManagedHandle)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InManagedHandle))
			{
				return BoolToIUnmanagedBool(FCSharpEnvironment::GetEnvironment().RemoveReference(FoundObject));
			}

			return IUnmanagedFalse;
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
