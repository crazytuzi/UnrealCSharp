#include "Mixin/FMixinGeneratorCore.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/PropertyAttributeMacro.h"
#include "Domain/FMonoDomain.h"

void FMixinGeneratorCore::SetPropertyFlags(FProperty* InProperty, MonoCustomAttrInfo* InMonoCustomAttrInfo)
{
	if (InProperty == nullptr || InMonoCustomAttrInfo == nullptr)
	{
		return;
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_EDIT_ANYWHERE_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_Edit);
	}

	if (AttrsHasAttr(InMonoCustomAttrInfo, CLASS_BLUEPRINT_READ_WRITE_ATTRIBUTE))
	{
		InProperty->SetPropertyFlags(CPF_BlueprintVisible);
	}
}

bool FMixinGeneratorCore::AttrsHasAttr(MonoCustomAttrInfo* InMonoCustomAttrInfo, const FString& InAttributeName)
{
	if (const auto AttributeMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_MIXIN), InAttributeName))
	{
		return !!FMonoDomain::Custom_Attrs_Has_Attr(InMonoCustomAttrInfo, AttributeMonoClass);
	}

	return false;
}
