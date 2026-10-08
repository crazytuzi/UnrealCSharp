#include "Binding/Class/TBindingClassBuilder.inl"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/CompilerMacro.h"
#include "UObject/UnrealType.h"
#include "Templates/TypeHash.h"
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

		static bool StructHash(const UStruct* InStruct, const void* InValue, uint32& OutHash)
		{
			for (auto Property = InStruct->PropertyLink; Property != nullptr; Property = Property->PropertyLinkNext)
			{
				const auto Value = Property->ContainerPtrToValuePtr<void>(const_cast<void*>(InValue));

				if (const auto StructProperty = CastField<FStructProperty>(Property))
				{
					if (!StructHash(StructProperty->Struct, Value, OutHash))
					{
						return false;
					}
				}
				else if (Property->HasAnyPropertyFlags(CPF_HasGetValueTypeHash))
				{
					if (const auto FloatProperty = CastField<FFloatProperty>(Property))
					{
						OutHash = HashCombineFast(OutHash, *static_cast<const float*>(Value) == 0.0f
							                                   ? 0
							                                   : FloatProperty->GetValueTypeHash(Value));
					}
					else if (const auto DoubleProperty = CastField<FDoubleProperty>(Property))
					{
						OutHash = HashCombineFast(OutHash, *static_cast<const double*>(Value) == 0.0
							                                   ? 0
							                                   : DoubleProperty->GetValueTypeHash(Value));
					}
					else if (const auto WeakObjectProperty = CastField<FWeakObjectProperty>(Property))
					{
						OutHash = HashCombineFast(OutHash, static_cast<const FWeakObjectPtr*>(Value)->IsValid()
							                                   ? WeakObjectProperty->GetValueTypeHash(Value)
							                                   : 0);
					}
					else
					{
						OutHash = HashCombineFast(OutHash, Property->GetValueTypeHash(Value));
					}
				}
				else
				{
					return false;
				}
			}

			return true;
		}

		static int32 GetTypeHashImplementation(const IManagedHandle InScriptStruct,
		                                       const IManagedHandle InManagedHandle)
		{
			if (const auto FoundScriptStruct = FCSharpEnvironment::GetEnvironment().GetObject<
				UScriptStruct>(InScriptStruct))
			{
				if (const auto FoundStruct = FCSharpEnvironment::GetEnvironment().GetStruct<>(InManagedHandle))
				{
					if (auto Hash = 0u; StructHash(FoundScriptStruct, FoundStruct, Hash))
					{
						return static_cast<int32>(Hash);
					}

					if (const auto CppStructOps = FoundScriptStruct->GetCppStructOps();
						(FoundScriptStruct->StructFlags & STRUCT_IdenticalNative) != 0 &&
						CppStructOps != nullptr && CppStructOps->HasGetTypeHash())
					{
						return static_cast<int32>(FoundScriptStruct->GetStructTypeHash(FoundStruct));
					}
				}
			}

			return 0;
		}

		static void UnRegisterImplementation(const IManagedHandle InManagedHandle)
		{
			if (IsInGameThread())
			{
				(void)FCSharpEnvironment::GetEnvironment().RemoveStructReference(InManagedHandle);
			}
			else
			{
				AsyncTask(ENamedThreads::GameThread, [InManagedHandle]
				{
					(void)FCSharpEnvironment::GetEnvironment().RemoveStructReference(InManagedHandle);
				});
			}
		}

		FRegisterStruct()
		{
			TBindingClassBuilder<UStruct>(NAMESPACE_LIBRARY)
				.Function("StaticStruct", StaticStructImplementation)
				.Function("Register", RegisterImplementation)
				.Function("Identical", IdenticalImplementation)
				.Function("GetTypeHash", GetTypeHashImplementation)
				.Function("UnRegister", UnRegisterImplementation);
		}
	};

	[[maybe_unused]] FRegisterStruct RegisterStruct;
}

PRAGMA_ENABLE_DANGLING_WARNINGS
