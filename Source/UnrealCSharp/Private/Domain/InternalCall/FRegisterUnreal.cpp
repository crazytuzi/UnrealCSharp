#include "Binding/Class/FClassBuilder.h"
#include "Binding/Enum/TBindingEnumBuilder.inl"
#include "Environment/FCSharpEnvironment.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"

BINDING_ENGINE_ENUM(EObjectFlags)

BINDING_ENGINE_ENUM(ELoadFlags)

struct FRegisterObjectFlags
{
	FRegisterObjectFlags()
	{
		TBindingEnumBuilder<EObjectFlags>()
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
			.Enumerator("RF_AllocatedInSharedPage", EObjectFlags::RF_AllocatedInSharedPage)
			.Register();
	}
};

static FRegisterObjectFlags RegisterObjectFlags;

struct FRegisterLoadFlags
{
	FRegisterLoadFlags()
	{
		TBindingEnumBuilder<ELoadFlags>()
			.Enumerator("LOAD_None", ELoadFlags::LOAD_None)
			.Enumerator("LOAD_Async", ELoadFlags::LOAD_Async)
			.Enumerator("LOAD_NoWarn", ELoadFlags::LOAD_NoWarn)
			.Enumerator("LOAD_EditorOnly", ELoadFlags::LOAD_EditorOnly)
			.Enumerator("LOAD_ResolvingDeferredExports", ELoadFlags::LOAD_ResolvingDeferredExports)
			.Enumerator("LOAD_Verify", ELoadFlags::LOAD_Verify)
			.Enumerator("LOAD_NoVerify", ELoadFlags::LOAD_NoVerify)
			.Enumerator("LOAD_IsVerifying", ELoadFlags::LOAD_IsVerifying)
			.Enumerator("LOAD_DisableDependencyPreloading", ELoadFlags::LOAD_DisableDependencyPreloading)
			.Enumerator("LOAD_Quiet", ELoadFlags::LOAD_Quiet)
			.Enumerator("LOAD_FindIfFail", ELoadFlags::LOAD_FindIfFail)
			.Enumerator("LOAD_MemoryReader", ELoadFlags::LOAD_MemoryReader)
			.Enumerator("LOAD_NoRedirects", ELoadFlags::LOAD_NoRedirects)
			.Enumerator("LOAD_ForDiff", ELoadFlags::LOAD_ForDiff)
			.Enumerator("LOAD_PackageForPIE", ELoadFlags::LOAD_PackageForPIE)
			.Enumerator("LOAD_DeferDependencyLoads", ELoadFlags::LOAD_DeferDependencyLoads)
			.Enumerator("LOAD_ForFileDiff", ELoadFlags::LOAD_ForFileDiff)
			.Enumerator("LOAD_DisableCompileOnLoad", ELoadFlags::LOAD_DisableCompileOnLoad)
			.Register();
	}
};

static FRegisterLoadFlags RegisterLoadFlags;

struct FRegisterUnreal
{
	static MonoObject* NewObjectImplementation(const FGarbageCollectionHandle Outer,
	                                           const FGarbageCollectionHandle Class,
	                                           const FGarbageCollectionHandle Name,
	                                           const EObjectFlags Flags,
	                                           const FGarbageCollectionHandle Template,
	                                           const bool bCopyTransientsFromClassDefaults)
	{
		const auto ObjectOuter = FCSharpEnvironment::GetEnvironment().GetObject(Outer);

		const auto ObjectClass = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(Class);

		const auto ObjectName = FCSharpEnvironment::GetEnvironment().GetString<FName>(Name);

		const auto ObjectTemplate = FCSharpEnvironment::GetEnvironment().GetObject(Template);

		const auto Object = NewObject<UObject>(ObjectOuter,
		                                       ObjectClass,
		                                       *ObjectName,
		                                       Flags,
		                                       ObjectTemplate,
		                                       bCopyTransientsFromClassDefaults);

		return FCSharpEnvironment::GetEnvironment().Bind(Object);
	}

	static MonoObject* DuplicateObjectImplementation(const FGarbageCollectionHandle SourceObject,
	                                                 const FGarbageCollectionHandle Outer,
	                                                 const FGarbageCollectionHandle Name)
	{
		const auto ObjectSourceObject = FCSharpEnvironment::GetEnvironment().GetObject(SourceObject);

		const auto ObjectOuter = FCSharpEnvironment::GetEnvironment().GetObject(Outer);

		const auto ObjectName = FCSharpEnvironment::GetEnvironment().GetString<FName>(Name);

		const auto Object = DuplicateObject<UObject>(ObjectSourceObject,
		                                             ObjectOuter,
		                                             *ObjectName);

		return FCSharpEnvironment::GetEnvironment().Bind(Object);
	}

	static MonoObject* LoadObjectImplementation(const FGarbageCollectionHandle Outer,
	                                            const FGarbageCollectionHandle Name,
	                                            const FGarbageCollectionHandle Filename,
	                                            const ELoadFlags LoadFlags,
	                                            const FGarbageCollectionHandle Sandbox)
	{
		const auto ObjectOuter = FCSharpEnvironment::GetEnvironment().GetObject(Outer);

		const auto ObjectName = FCSharpEnvironment::GetEnvironment().GetString<FString>(Name);

		const auto ObjectFilename = FCSharpEnvironment::GetEnvironment().GetString<FString>(Filename);

		const auto ObjectSandbox = FCSharpEnvironment::GetEnvironment().GetObject<UPackageMap>(Sandbox);

		const auto Object = LoadObject<UObject>(ObjectOuter,
		                                        ObjectName != nullptr ? **ObjectName : nullptr,
		                                        ObjectFilename != nullptr ? **ObjectFilename : nullptr,
		                                        LoadFlags,
		                                        ObjectSandbox
		);

		return FCSharpEnvironment::GetEnvironment().Bind(Object);
	}

	static MonoObject* LoadClassImplementation(const FGarbageCollectionHandle Outer,
	                                           const FGarbageCollectionHandle Name,
	                                           const FGarbageCollectionHandle Filename,
	                                           const ELoadFlags LoadFlags,
	                                           const FGarbageCollectionHandle Sandbox)
	{
		const auto ObjectOuter = FCSharpEnvironment::GetEnvironment().GetObject(Outer);

		const auto ObjectName = FCSharpEnvironment::GetEnvironment().GetString<FString>(Name);

		const auto ObjectFilename = FCSharpEnvironment::GetEnvironment().GetString<FString>(Filename);

		const auto ObjectSandbox = FCSharpEnvironment::GetEnvironment().GetObject<UPackageMap>(Sandbox);

		const auto Class = LoadClass<UObject>(ObjectOuter,
		                                      ObjectName != nullptr ? **ObjectName : nullptr,
		                                      ObjectFilename != nullptr ? **ObjectFilename : nullptr,
		                                      LoadFlags,
		                                      ObjectSandbox
		);

		return FCSharpEnvironment::GetEnvironment().Bind(Class);
	}

	static MonoObject* CreateWidgetImplementation(const FGarbageCollectionHandle InOwningObject,
	                                              const FGarbageCollectionHandle InUserWidgetClass)
	{
		const auto OwningObject = FCSharpEnvironment::GetEnvironment().GetObject<UObject>(InOwningObject);

		const auto Class = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(InUserWidgetClass);

		UUserWidget* UserWidget = nullptr;

		if (OwningObject->IsA(UWidget::StaticClass()))
		{
			UserWidget = CreateWidget(Cast<UWidget>(OwningObject), Class);
		}
		else if (OwningObject->IsA(UWidgetTree::StaticClass()))
		{
			UserWidget = CreateWidget(Cast<UWidgetTree>(OwningObject), Class);
		}
		else if (OwningObject->IsA(APlayerController::StaticClass()))
		{
			UserWidget = CreateWidget(Cast<APlayerController>(OwningObject), Class);
		}
		else if (OwningObject->IsA(UGameInstance::StaticClass()))
		{
			UserWidget = CreateWidget(Cast<UGameInstance>(OwningObject), Class);
		}
		else if (OwningObject->IsA(UWorld::StaticClass()))
		{
			UserWidget = CreateWidget(Cast<UWorld>(OwningObject), Class);
		}

		return FCSharpEnvironment::GetEnvironment().Bind(UserWidget);
	}

	static MonoObject* GWorldImplementation()
	{
		return FCSharpEnvironment::GetEnvironment().Bind(GWorld);
	}

	FRegisterUnreal()
	{
		FClassBuilder(TEXT("Unreal"), NAMESPACE_LIBRARY)
			.Function("NewObject", NewObjectImplementation)
			.Function("DuplicateObject", DuplicateObjectImplementation)
			.Function("LoadObject", LoadObjectImplementation)
			.Function("LoadClass", LoadClassImplementation)
			.Function("CreateWidget", CreateWidgetImplementation)
			.Function("GWorld", GWorldImplementation)
			.Register();
	}
};

static FRegisterUnreal RegisterUnreal;
