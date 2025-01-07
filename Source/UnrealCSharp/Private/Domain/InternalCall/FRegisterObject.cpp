#include "Binding/Class/TBindingClassBuilder.inl"
#include "Binding/Core/TPropertyClass.inl"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Macro/BindingMacro.h"

namespace
{
	struct FRegisterObject
	{
		static bool IdenticalImplementation(const FGarbageCollectionHandle InA, const FGarbageCollectionHandle InB)
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetObject(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetObject(InB))
				{
					return FoundA == FoundB;
				}
			}

			return false;
		}

		static MonoObject* StaticClassImplementation(MonoString* InClassName)
		{
			const auto ClassName = StringCast<TCHAR>(
				FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(InClassName));

			const auto InClass = LoadObject<UClass>(nullptr, ClassName.Get());

			return FCSharpEnvironment::GetEnvironment().Bind(InClass);
		}

		static MonoObject* GetClassImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				const auto Class = FoundObject->GetClass();

				return FCSharpEnvironment::GetEnvironment().Bind(Class);
			}

			return nullptr;
		}

		static MonoObject* GetNameImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				const auto Name = FoundObject->GetName();

				const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

				const auto Object = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundMonoClass);

				FCSharpEnvironment::GetEnvironment().AddStringReference<FString, true, false>(
					Object, new FString(Name));

				return Object;
			}

			return nullptr;
		}

		static bool IsValidImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				return IsValid(FoundObject);
			}

			return false;
		}

		static bool IsAImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                              const FGarbageCollectionHandle SomeBase)
		{
			if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
			{
				if (const auto FoundClass = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(SomeBase))
				{
					return FoundObject->IsA(FoundClass);
				}
			}

			return false;
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
				.Function("IsA", IsAImplementation);
		}
	};

	[[maybe_unused]] FRegisterObject RegisterObject;
}
