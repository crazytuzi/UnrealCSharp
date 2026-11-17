#pragma once

#include "CoreMinimal.h"
#include "Extensions/WidgetBlueprintGeneratedClassExtension.h"
#include "CSharpWidgetBinding.generated.h"

USTRUCT()
struct UNREALCSHARPBLUEPRINTFUNCTION_API FCSharpWidgetBinding
{
	GENERATED_BODY()

	UPROPERTY()
	FName WidgetName;

	UPROPERTY()
	FName PropertyName;

	UPROPERTY()
	uint8 Kind = 0;

	UPROPERTY()
	FName MemberName;

	UPROPERTY()
	int32 ParamCount = 0;

	UPROPERTY()
	uint32 SignatureHash = 0;

	UPROPERTY()
	TObjectPtr<UClass> OwnerClass;

	UPROPERTY()
	FString DisplayName;

	bool Matches(const FName& InWidgetName, const FName& InPropertyName) const
	{
		return WidgetName == InWidgetName && PropertyName == InPropertyName;
	}

	static FName GetDelegatePropertyName(const FName& InPropertyName);

	static FDelegateProperty* FindDelegateProperty(const UClass* InWidgetClass, const FName& InPropertyName);
};

UCLASS()
class UNREALCSHARPBLUEPRINTFUNCTION_API UCSharpWidgetBindingClassExtension : public UWidgetBlueprintGeneratedClassExtension
{
	GENERATED_BODY()

public:
	virtual void Initialize(UUserWidget* UserWidget) override;

public:
	UPROPERTY()
	TArray<FCSharpWidgetBinding> Bindings;
};
