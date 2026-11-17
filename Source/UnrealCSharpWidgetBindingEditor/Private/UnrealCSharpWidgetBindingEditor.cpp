#include "Modules/ModuleManager.h"

#include "CSharpPropertyBindingExtension.h"
#include "UMGEditorModule.h"

class FUnrealCSharpWidgetBindingEditorModule final : public IModuleInterface
{
public:
	virtual void StartupModule() override
	{
		Extension = MakeShared<FCSharpPropertyBindingExtension>();

		auto& UMGEditorModule = FModuleManager::LoadModuleChecked<IUMGEditorModule>(TEXT("UMGEditor"));

		UMGEditorModule.GetPropertyBindingExtensibilityManager()->AddExtension(Extension.ToSharedRef());
	}

	virtual void ShutdownModule() override
	{
		if (Extension.IsValid())
		{
			if (const auto UMGEditorModule = FModuleManager::GetModulePtr<IUMGEditorModule>(TEXT("UMGEditor")))
			{
				if (const auto Manager = UMGEditorModule->GetPropertyBindingExtensibilityManager())
				{
					Manager->RemoveExtension(Extension.ToSharedRef());
				}
			}

			Extension.Reset();
		}
	}

private:
	TSharedPtr<FCSharpPropertyBindingExtension> Extension;
};

IMPLEMENT_MODULE(FUnrealCSharpWidgetBindingEditorModule, UnrealCSharpWidgetBindingEditor)
