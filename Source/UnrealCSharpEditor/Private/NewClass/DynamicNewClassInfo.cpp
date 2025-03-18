#include "NewClass/DynamicNewClassInfo.h"
#include "UEVersion.h"

#define LOCTEXT_NAMESPACE "DynamicNewClassInfo"

FDynamicNewClassInfo::FDynamicNewClassInfo(const Super& InSuper):
	Super(InSuper)
{
}

FText FDynamicNewClassInfo::GetClassName() const
{
	switch (ClassType)
	{
	case EClassType::UObject:
		{
			return BaseClass ? BaseClass->GetDisplayNameText() : FText::GetEmpty();
		}
	case EClassType::EmptyCpp:
		{
			return LOCTEXT("NoParentClass", "None");
		}
	case EClassType::SlateWidget:
		{
			return LOCTEXT("SlateWidgetParentClass", "Slate Widget");
		}
	case EClassType::SlateWidgetStyle:
		{
			return LOCTEXT("SlateWidgetStyleParentClass", "Slate Widget Style");
		}
	case EClassType::UInterface:
		{
			return LOCTEXT("UInterfaceParentClass", "Unreal Interface");
		}
	default:
		break;
	}

	return FText::GetEmpty();
}

FString FDynamicNewClassInfo::GetClassNameCPP() const
{
	switch (ClassType)
	{
	case EClassType::UObject:
		{
			return BaseClass ? BaseClass->GetName() : TEXT("");
		}
	case EClassType::EmptyCpp:
		{
			return TEXT("");
		}
	case EClassType::SlateWidget:
		{
			return TEXT("CompoundWidget");
		}
	case EClassType::SlateWidgetStyle:
		{
			return TEXT("SlateWidgetStyle");
		}
	case EClassType::UInterface:
		{
			return TEXT("Interface");
		}
	default:
		break;
	}

	return TEXT("");
}

FText FDynamicNewClassInfo::GetClassDescription(const bool bFullDescription) const
{
	switch (ClassType)
	{
	case EClassType::UObject:
		{
			if (BaseClass)
			{
				auto ClassDescription = BaseClass->GetToolTipText(!bFullDescription).ToString();

				if (!bFullDescription)
				{
					if (auto FullStopIndex = 0; ClassDescription.FindChar('.', FullStopIndex))
					{
						ClassDescription.LeftInline(FullStopIndex + 1,
#if UE_F_STRING_LEFT_CHOP_IN_LINE_E_ALLOW_SHRINKING
						                            EAllowShrinking::No
#else
						                            false
#endif
						);
					}

					ClassDescription.ReplaceInline(TEXT("\n"), TEXT(" "), ESearchCase::CaseSensitive);
				}

				return FText::FromString(ClassDescription);
			}
		}
		break;
	case EClassType::EmptyCpp:
		{
			return LOCTEXT("EmptyClassDescription", "An empty C++ class with a default constructor and destructor.");
		}
	case EClassType::SlateWidget:
		{
			return LOCTEXT("SlateWidgetClassDescription", "A custom Slate widget, deriving from SCompoundWidget.");
		}
	case EClassType::SlateWidgetStyle:
		{
			return LOCTEXT("SlateWidgetStyleClassDescription",
			               "A custom Slate widget style, deriving from FSlateWidgetStyle, along with its associated UObject wrapper class.");
		}
	case EClassType::UInterface:
		{
			return LOCTEXT("UInterfaceClassDescription",
			               "A UObject Interface class, to be implemented by other UObject-based classes.");
		}
	default:
		break;
	}

	return FText::GetEmpty();
}

#undef LOCTEXT_NAMESPACE
