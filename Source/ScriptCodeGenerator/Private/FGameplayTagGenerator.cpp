#include "FGameplayTagGenerator.h"
#include "HAL/FileManager.h"
#include "Misc/App.h"
#include "Misc/Paths.h"
#include "GameplayTagsManager.h"
#include "FGeneratorCore.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/Macro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/AccessPrivateMacro.h"
#include "UEVersion.h"

ACCESS_PRIVATE_MEMBER_PROPERTY(FGameplayTagNode, DevComment, FString)

struct FGameplayTagGenerator::FGameplayTagTreeNode
{
	FString Tag;

	FString Comment;

	TMap<FString, TUniquePtr<FGameplayTagTreeNode>> Children;
};

void FGameplayTagGenerator::Generator()
{
	FGameplayTagTreeNode Root;

	TArray<TPair<FString, FString>> Tags;

	CollectGameplayTags(Tags);

	for (const auto& Tag : Tags)
	{
		GeneratorTag(Root, Tag.Key, Tag.Value);
	}

	const auto DirectoryName = FPaths::Combine(
		FUnrealCSharpFunctionLibrary::GetGameProxyDirectory(),
		FApp::GetProjectName());

	const auto FileName = FPaths::Combine(DirectoryName, GAMEPLAY_TAGS_NAME + CSHARP_SUFFIX);

	if (Root.Children.IsEmpty())
	{
		if (auto& FileManager = IFileManager::Get();
			FileManager.FileExists(*FileName))
		{
			if (FileManager.Delete(*FileName))
			{
				FUnrealCSharpFunctionLibrary::MarkScriptChanged();
			}
		}

		return;
	}

	const auto NameSpaceContent = FString::Printf(TEXT(
		"%s.%s"
	),
	                                              *NAMESPACE_ROOT,
	                                              FApp::GetProjectName()
	);

	const auto UsingNameSpaceContent = FString::Printf(TEXT(
		"using %s.%s;\n"
	),
	                                                   *NAMESPACE_ROOT,
	                                                   *GAMEPLAY_TAGS_NAME
	);

	FString ChildrenContent;

	GeneratorChildren(ChildrenContent, Root, 2);

	const auto Content = FString::Printf(TEXT(
		"%s\n"
		"%s\n"
		"namespace %s\n"
		"{\n"
		"\tpublic static partial class GameplayTags\n"
		"\t{\n"
		"%s"
		"\t}\n"
		"}"
	),
	                                     *FGeneratorCore::GetGeneratorHeaderComment(),
	                                     *UsingNameSpaceContent,
	                                     *NameSpaceContent,
	                                     *ChildrenContent
	);

	FGeneratorCore::AddGeneratorFile(FileName);

	FUnrealCSharpFunctionLibrary::SaveStringToFile(FileName, Content);
}

void FGameplayTagGenerator::GeneratorTag(FGameplayTagTreeNode& InRoot, const FString& InTag, const FString& InComment)
{
	TArray<FString> Segments;

	InTag.ParseIntoArray(Segments, TEXT("."));

	if (!Segments.IsEmpty())
	{
		auto Node = &InRoot;

		for (const auto& Segment : Segments)
		{
			if (!Segment.IsEmpty())
			{
				auto& Child = Node->Children.FindOrAdd(Segment);

				if (!Child)
				{
					Child = MakeUnique<FGameplayTagTreeNode>();
				}

				Node = Child.Get();
			}
		}

		Node->Tag = InTag;

		Node->Comment = InComment;
	}
}

void FGameplayTagGenerator::GeneratorDocComment(FString& OutContent, const FString& InPad, const FString& InComment)
{
	if (!InComment.IsEmpty())
	{
		const auto Comment = InComment.Replace(TEXT("\r\n"), TEXT(" "))
		                              .Replace(TEXT("\n"), TEXT(" "))
		                              .Replace(TEXT("\r"), TEXT(" "))
		                              .Replace(TEXT("&"), TEXT("&amp;"))
		                              .Replace(TEXT("<"), TEXT("&lt;"))
		                              .Replace(TEXT(">"), TEXT("&gt;"));

		OutContent += FString::Printf(TEXT(
			"%s/// <summary>%s</summary>\n"
		),
		                              *InPad,
		                              *Comment
		);
	}
}

void FGameplayTagGenerator::GeneratorChildren(FString& OutContent, const FGameplayTagTreeNode& InNode,
                                              const int32 InIndent)
{
	TSet<FString> UsedNames;

	if (!InNode.Tag.IsEmpty())
	{
		UsedNames.Add(TEXT("Value"));
	}

	TArray<FString> Keys;

	InNode.Children.GetKeys(Keys);

	Keys.Sort();

	FString Pad;

	for (auto Index = 0; Index < InIndent; ++Index)
	{
		Pad += TEXT("\t");
	}

	for (auto Index = 0; Index < Keys.Num(); ++Index)
	{
		const auto& Child = **InNode.Children.Find(Keys[Index]);

		const auto Name = MakeUniqueName(FUnrealCSharpFunctionLibrary::Encode(Keys[Index], false), UsedNames);

		FString Content;

		if (Child.Children.IsEmpty())
		{
			GeneratorDocComment(Content, Pad, Child.Comment);

			Content += FString::Printf(TEXT(
				"%spublic static readonly FGameplayTag %s = new FGameplayTag { TagName = \"%s\" };\n"
			),
			                           *Pad,
			                           *Name,
			                           *Child.Tag
			);
		}
		else
		{
			Content += FString::Printf(TEXT(
				"%spublic static class %s\n"
				"%s{\n"
			),
			                           *Pad,
			                           *Name,
			                           *Pad
			);

			if (!Child.Tag.IsEmpty())
			{
				GeneratorDocComment(Content, Pad + TEXT("\t"), Child.Comment);

				Content += FString::Printf(TEXT(
					"%s\tpublic static readonly FGameplayTag Value = new FGameplayTag { TagName = \"%s\" };\n"
				),
				                           *Pad,
				                           *Child.Tag
				);

				Content += TEXT("\n");
			}

			GeneratorChildren(Content, Child, InIndent + 1);

			Content += FString::Printf(TEXT(
				"%s}\n"
			),
			                           *Pad
			);
		}

		OutContent += Content;

		if (Index != Keys.Num() - 1)
		{
			OutContent += TEXT("\n");
		}
	}
}

FString FGameplayTagGenerator::MakeUniqueName(const FString& InName, TSet<FString>& InOutUsedNames)
{
	auto Name = InName;

	auto Suffix = 2;

	while (InOutUsedNames.Contains(Name))
	{
		Name = InName + TEXT("_") + FString::FromInt(Suffix++);
	}

	InOutUsedNames.Add(Name);

	return Name;
}

void FGameplayTagGenerator::CollectGameplayTags(TArray<TPair<FString, FString>>& OutTags)
{
	TArray<TSharedPtr<FGameplayTagNode>> RootTags;

	UGameplayTagsManager::Get().GetFilteredGameplayRootTags(TEXT(""), RootTags);

	for (const auto& RootTag : RootTags)
	{
		VisitTagNodes(RootTag, OutTags);
	}
}

void FGameplayTagGenerator::VisitTagNodes(const TSharedPtr<FGameplayTagNode>& InNode,
                                          TArray<TPair<FString, FString>>& OutTags)
{
	if (InNode.IsValid())
	{
		if (InNode->IsExplicitTag() && !InNode->IsRestrictedGameplayTag())
		{
#if UE_F_GAMEPLAY_TAG_NODE_GET_DEV_COMMENT
			OutTags.Emplace(InNode->GetCompleteTagString(), InNode->GetDevComment());
#else
			OutTags.Emplace(InNode->GetCompleteTagString(),
			                InNode.Get()->*TAccessPrivate<FGameplayTagNode_DevComment>::Value);
#endif
		}

		for (const auto& Child : InNode->GetChildTagNodes())
		{
			VisitTagNodes(Child, OutTags);
		}
	}
}
