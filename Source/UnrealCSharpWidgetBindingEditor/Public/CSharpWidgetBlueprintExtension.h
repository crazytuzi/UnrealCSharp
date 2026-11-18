#pragma once

#include "CoreMinimal.h"
#include "CSharpWidgetBinding.h"
#include "WidgetBlueprintExtension.h"
#include "CSharpWidgetBlueprintExtension.generated.h"

UCLASS()
class UNREALCSHARPWIDGETBINDINGEDITOR_API UCSharpWidgetBlueprintExtension : public UWidgetBlueprintExtension
{
	GENERATED_BODY()

public:
	const FCSharpWidgetBinding* FindBinding(const FName& InWidgetName, const FName& InPropertyName) const;

	void SetBinding(const FCSharpWidgetBinding& InBinding);

	bool RemoveBinding(const FName& InWidgetName, const FName& InPropertyName);

	const TArray<FCSharpWidgetBinding>& GetBindings() const;

	static FName GetWidgetKey(const UWidgetBlueprint* InWidgetBlueprint, const UWidget* InWidget);

protected:
	virtual void HandleBeginCompilation(FWidgetBlueprintCompilerContext& InCreationContext) override;

	virtual void HandleFinishCompilingClass(UWidgetBlueprintGeneratedClass* Class) override;

	virtual void HandleEndCompilation() override;

private:
	bool ValidateBinding(const FCSharpWidgetBinding& InBinding, UWidgetBlueprintGeneratedClass* InClass,
	                     FCSharpWidgetBinding& OutBinding) const;

private:
	UPROPERTY()
	TArray<FCSharpWidgetBinding> Bindings;

	FWidgetBlueprintCompilerContext* CompilerContext = nullptr;
};
