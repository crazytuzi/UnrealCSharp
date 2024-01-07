#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Binding/Core/TPropertyClass.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/BindingMacro.h"
#include "Macro/NamespaceMacro.h"

BINDING_REFLECTION_CLASS(UObject);

struct FRegisterObject
{
	static void StaticClassImplementation(MonoString* InClassName, MonoObject** OutValue)
	{
		const auto ClassName =
			UTF8_TO_TCHAR(FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(InClassName));

		const auto InClass = LoadObject<UClass>(nullptr, ClassName);

		*OutValue = FCSharpEnvironment::GetEnvironment().Bind(InClass);
	}

	static void GetClassImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                   MonoObject** OutValue)
	{
		if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
		{
			const auto Class = FoundObject->GetClass();

			*OutValue = FCSharpEnvironment::GetEnvironment().Bind(Class);
		}
	}

	static void GetNameImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                  MonoObject** OutValue)
	{
		if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
		{
			const auto Name = FoundObject->GetName();

			const auto FoundMonoClass = TPropertyClass<FString, FString>::Get();

			*OutValue = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Init(FoundMonoClass);

			FCSharpEnvironment::GetEnvironment().AddStringReference<FString>(*OutValue, new FString(Name), true);
		}
	}

	static void GetWorldImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                   MonoObject** OutValue)
	{
		if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InGarbageCollectionHandle))
		{
			const auto World = FoundObject->GetWorld();

			*OutValue = FCSharpEnvironment::GetEnvironment().Bind(World);
		}
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
		TReflectionClassBuilder<UObject>(NAMESPACE_LIBRARY)
			.Function("StaticClass", StaticClassImplementation)
			.Function("GetClass", GetClassImplementation)
			.Function("GetName", GetNameImplementation)
			.Function("GetWorld", GetWorldImplementation)
			.Function("IsValid", IsValidImplementation)
			.Function("IsA", IsAImplementation)
			.Register();
	}
};

static FRegisterObject RegisterObject;
