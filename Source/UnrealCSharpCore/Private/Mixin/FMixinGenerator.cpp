#include "Mixin/FMixinGenerator.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"
#include "Domain/FMonoDomain.h"
#include "Mixin/FMixinClassGenerator.h"

void FMixinGenerator::Generator()
{
	FMonoDomain::Initialize({
		"",
		FUnrealCSharpFunctionLibrary::GetScriptPath() / FUnrealCSharpFunctionLibrary::GetAssemblyUtilProjectName() +
		DLL_SUFFIX,
		{
			FUnrealCSharpFunctionLibrary::GetScriptPath() / FUnrealCSharpFunctionLibrary::GetUEProjectName() +
			DLL_SUFFIX,
			FUnrealCSharpFunctionLibrary::GetScriptPath() / FUnrealCSharpFunctionLibrary::GetGameProjectName() +
			DLL_SUFFIX
		}
	});

	FMixinClassGenerator::Generator();

	FMonoDomain::Deinitialize();
}

#if WITH_EDITOR
void FMixinGenerator::Generator(const TArray<FFileChangeData>& FileChangeData)
{
	FMonoDomain::Initialize({
		"",
		FUnrealCSharpFunctionLibrary::GetScriptPath() / FUnrealCSharpFunctionLibrary::GetAssemblyUtilProjectName() +
		DLL_SUFFIX,
		{
			FUnrealCSharpFunctionLibrary::GetScriptPath() / FUnrealCSharpFunctionLibrary::GetUEProjectName() +
			DLL_SUFFIX,
			FUnrealCSharpFunctionLibrary::GetScriptPath() / FUnrealCSharpFunctionLibrary::GetGameProjectName() +
			DLL_SUFFIX
		}
	});

	for (const auto& Data : FileChangeData)
	{
		if (FPaths::GetExtension(Data.Filename) == TEXT("cs"))
		{
			auto Filename = FPaths::GetBaseFilename(Data.Filename);

			// @TODO
			if (auto Class = LoadClass<UObject>(UObject::StaticClass()->GetPackage(), *FString(Filename)))
			{
				FMixinClassGenerator::Generator(FMonoDomain::Class_From_Name(
					FUnrealCSharpFunctionLibrary::GetClassNameSpace(Class),
					FUnrealCSharpFunctionLibrary::GetFullClass(Class)));

				Class = LoadClass<UObject>(UObject::StaticClass()->GetPackage(), *FString(Filename));

				for (TObjectIterator<UBlueprintGeneratedClass> ClassIterator; ClassIterator; ++ClassIterator)
				{
					if (ClassIterator->IsChildOf(Class))
					{
						ClassIterator->UpdateCustomPropertyListForPostConstruction();

						ClassIterator->Bind();

						ClassIterator->StaticLink(true);
					}
				}
			}
			else
			{
				FMixinClassGenerator::Generator(FMonoDomain::Class_From_Name(
					FUnrealCSharpFunctionLibrary::GetClassNameSpace(UObject::StaticClass()),
					Filename));
			}
		}
	}

	FMonoDomain::Deinitialize();
}
#endif
