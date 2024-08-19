#pragma once

#include "Binding/Enum/TBindingEnumBuilder.inl"
#include "Macro/BindingMacro.h"

BINDING_ENUM(EObjectFlags)

struct FRegisterObjectFlags
{
	FRegisterObjectFlags()
	{
		TBindingEnumBuilder<EObjectFlags, false>()
			.Enumerator("RF_NoFlags", EObjectFlags::RF_NoFlags)
			.Enumerator("RF_Public", EObjectFlags::RF_Public)
			.Enumerator("RF_Standalone", EObjectFlags::RF_Standalone)
			.Enumerator("RF_MarkAsNative", EObjectFlags::RF_MarkAsNative)
			.Enumerator("RF_Transactional", EObjectFlags::RF_Transactional)
			.Enumerator("RF_ClassDefaultObject", EObjectFlags::RF_ClassDefaultObject)
			.Enumerator("RF_ArchetypeObject", EObjectFlags::RF_ArchetypeObject)
			.Enumerator("RF_Transient", EObjectFlags::RF_Transient)
			.Enumerator("RF_MarkAsRootSet", EObjectFlags::RF_MarkAsRootSet)
			.Enumerator("RF_TagGarbageTemp", EObjectFlags::RF_TagGarbageTemp)
			.Enumerator("RF_NeedInitialization", EObjectFlags::RF_NeedInitialization)
			.Enumerator("RF_NeedLoad", EObjectFlags::RF_NeedLoad)
			.Enumerator("RF_KeepForCooker", EObjectFlags::RF_KeepForCooker)
			.Enumerator("RF_NeedPostLoad", EObjectFlags::RF_NeedPostLoad)
			.Enumerator("RF_NeedPostLoadSubobjects", EObjectFlags::RF_NeedPostLoadSubobjects)
			.Enumerator("RF_NewerVersionExists", EObjectFlags::RF_NewerVersionExists)
			.Enumerator("RF_BeginDestroyed", EObjectFlags::RF_BeginDestroyed)
			.Enumerator("RF_FinishDestroyed", EObjectFlags::RF_FinishDestroyed)
			.Enumerator("RF_BeingRegenerated", EObjectFlags::RF_BeingRegenerated)
			.Enumerator("RF_DefaultSubObject", EObjectFlags::RF_DefaultSubObject)
			.Enumerator("RF_WasLoaded", EObjectFlags::RF_WasLoaded)
			.Enumerator("RF_TextExportTransient", EObjectFlags::RF_TextExportTransient)
			.Enumerator("RF_LoadCompleted", EObjectFlags::RF_LoadCompleted)
			.Enumerator("RF_InheritableComponentTemplate", EObjectFlags::RF_InheritableComponentTemplate)
			.Enumerator("RF_DuplicateTransient", EObjectFlags::RF_DuplicateTransient)
			.Enumerator("RF_StrongRefOnFrame", EObjectFlags::RF_StrongRefOnFrame)
			.Enumerator("RF_NonPIEDuplicateTransient", EObjectFlags::RF_NonPIEDuplicateTransient)
			.Enumerator("RF_WillBeLoaded", EObjectFlags::RF_WillBeLoaded)
			.Enumerator("RF_AllocatedInSharedPage", EObjectFlags::RF_AllocatedInSharedPage);
	}
};

static FRegisterObjectFlags RegisterObjectFlags;
