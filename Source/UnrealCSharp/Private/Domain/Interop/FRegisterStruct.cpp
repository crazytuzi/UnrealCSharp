#include "Binding/Class/TBindingClassBuilder.inl"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/CompilerMacro.h"
#include "Async/Async.h"

PRAGMA_DISABLE_DANGLING_WARNINGS

namespace
{
	struct FRegisterStruct
	{
		static IManagedHandle StaticStructImplementation(const char* InStructName)
		{
			const auto StructName = InStructName != nullptr ? FString(UTF8_TO_TCHAR(InStructName)) : FString(TEXT(""));

			const auto InStruct = LoadObject<UScriptStruct>(nullptr, *StructName);

			return FCSharpEnvironment::GetEnvironment().Bind(InStruct);
		}

		static void RegisterImplementation(const IManagedHandle InManagedHandle, const char* InStructName)
		{
			const auto StructName = InStructName != nullptr ? FString(UTF8_TO_TCHAR(InStructName)) : FString(TEXT(""));

			(void)FCSharpEnvironment::GetEnvironment().Bind(InManagedHandle, *StructName);
		}

		static uint8 IdenticalImplementation(const IManagedHandle InScriptStruct,
		                                     const IManagedHandle InA, const IManagedHandle InB)
		{
			if (const auto FoundScriptStruct = FCSharpEnvironment::GetEnvironment().GetObject<
				UScriptStruct>(InScriptStruct))
			{
				if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetStruct<>(InA))
				{
					if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetStruct<>(InB))
					{
						return FoundScriptStruct->CompareScriptStruct(FoundA, FoundB, PPF_None) ? 1 : 0;
					}
				}
			}

			return 0;
		}

		static void UnRegisterImplementation(const IManagedHandle InManagedHandle)
		{
			AsyncTask(ENamedThreads::GameThread, [InManagedHandle]
			{
				(void)FCSharpEnvironment::GetEnvironment().RemoveStructReference(InManagedHandle);
			});
		}

		FRegisterStruct()
		{
			TBindingClassBuilder<UStruct>(NAMESPACE_LIBRARY)
				.Function("StaticStruct", StaticStructImplementation)
				.Function("Register", RegisterImplementation)
				.Function("Identical", IdenticalImplementation)
				.Function("UnRegister", UnRegisterImplementation);
		}
	};

	[[maybe_unused]] FRegisterStruct RegisterStruct;
}

PRAGMA_ENABLE_DANGLING_WARNINGS
