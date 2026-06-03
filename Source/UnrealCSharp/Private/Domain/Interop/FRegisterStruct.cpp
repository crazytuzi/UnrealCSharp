#include "Binding/Class/TBindingClassBuilder.inl"
#include "Environment/FCSharpEnvironment.h"
#include "Domain/Script/IManagedMarshalledString.h"
#include "Domain/Script/IUnmanagedBool.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/CompilerMacro.h"
#include "Async/Async.h"

PRAGMA_DISABLE_DANGLING_WARNINGS

namespace
{
	struct FRegisterStruct
	{
		static IManagedObject StaticStructImplementation(const IManagedMarshalledString InStructName)
		{
			const auto StructName = MANAGED_MARSHALLED_STRING_TO_F_STRING(InStructName);

			const auto InStruct = LoadObject<UScriptStruct>(nullptr, *StructName);

			return FCSharpEnvironment::GetEnvironment().Bind(InStruct);
		}

		static void RegisterImplementation(const IManagedObject InManagedObject,
		                                   const IManagedMarshalledString InStructName)
		{
			const auto StructName = MANAGED_MARSHALLED_STRING_TO_F_STRING(InStructName);

			(void)FCSharpEnvironment::GetEnvironment().Bind(InManagedObject, *StructName);
		}

		static IUnmanagedBool IdenticalImplementation(const IManagedHandle InScriptStruct,
		                                              const IManagedHandle InA,
		                                              const IManagedHandle InB)
		{
			if (const auto FoundScriptStruct = FCSharpEnvironment::GetEnvironment().GetObject<
				UScriptStruct>(InScriptStruct))
			{
				if (const auto FoundA = FCSharpEnvironment::GetEnvironment().GetStruct<>(InA))
				{
					if (const auto FoundB = FCSharpEnvironment::GetEnvironment().GetStruct<>(InB))
					{
						return BoolToIUnmanagedBool(FoundScriptStruct->CompareScriptStruct(FoundA, FoundB, PPF_None));
					}
				}
			}

			return IUnmanagedFalse;
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
