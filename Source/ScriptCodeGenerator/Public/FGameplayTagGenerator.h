#pragma once

#include "CoreMinimal.h"

struct FGameplayTagNode;

class FGameplayTagGenerator
{
public:
	static SCRIPTCODEGENERATOR_API void Generator();

private:
	struct FGameplayTagTreeNode;

	static void GeneratorTag(FGameplayTagTreeNode& InRoot, const FString& InTag, const FString& InComment);

	static void GeneratorDocComment(FString& OutContent, const FString& InPad, const FString& InComment);

	static void GeneratorChildren(FString& OutContent, const FGameplayTagTreeNode& InNode, int32 InIndent);

	static FString MakeUniqueName(const FString& InName, TSet<FString>& InOutUsedNames);

	static void CollectGameplayTags(TArray<TTuple<FString, FString>>& OutTags);

	static void VisitTagNodes(const TSharedPtr<FGameplayTagNode>& InNode,
	                          TArray<TTuple<FString, FString>>& OutTags);
};
