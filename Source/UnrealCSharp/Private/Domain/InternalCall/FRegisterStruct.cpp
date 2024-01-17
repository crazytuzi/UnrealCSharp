﻿#include "Binding/Class/TReflectionClassBuilder.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"
#include "Async/Async.h"

BINDING_REFLECTION_CLASS(UStruct)

struct FRegisterStruct
{
	static MonoObject* StaticStructImplementation(MonoString* InStructName)
	{
		const auto StructName = UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(InStructName));

		const auto InStruct = LoadObject<UScriptStruct>(nullptr, StructName);

		return FCSharpEnvironment::GetEnvironment().Bind(InStruct);
	}

	static void RegisterImplementation(MonoObject* InMonoObject, MonoString* InStructName)
	{
		const auto StructName = UTF8_TO_TCHAR(
			FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(InStructName));

		FCSharpEnvironment::GetEnvironment().Bind(InMonoObject, StructName);
	}

	static bool IdenticalImplementation(const FGarbageCollectionHandle InScriptStruct,
	                                    const FGarbageCollectionHandle InA,
	                                    const FGarbageCollectionHandle InB)
	{
		if (const auto FoundScriptStruct = FCSharpEnvironment::GetEnvironment().GetObject<
			UScriptStruct>(InScriptStruct))
		{
			if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetStruct(InA))
			{
				if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetStruct(InB))
				{
					return FoundScriptStruct->CompareScriptStruct(FoundA, FoundB, PPF_None);
				}
			}
		}

		return false;
	}

	static void UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
	{
		AsyncTask(ENamedThreads::GameThread, [InGarbageCollectionHandle]
		{
			(void)FCSharpEnvironment::GetEnvironment().RemoveStructReference(InGarbageCollectionHandle);
		});
	}

	FRegisterStruct()
	{
		TReflectionClassBuilder<UStruct>(NAMESPACE_LIBRARY)
			.Function("StaticStruct", StaticStructImplementation)
			.Function("Register", RegisterImplementation)
			.Function("Identical", IdenticalImplementation)
			.Function("UnRegister", UnRegisterImplementation)
			.Register();
	}
};

static FRegisterStruct RegisterStruct;
