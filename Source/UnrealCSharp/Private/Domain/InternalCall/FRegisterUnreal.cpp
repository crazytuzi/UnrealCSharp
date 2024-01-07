#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Macro/NamespaceMacro.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"

struct FRegisterUnreal
{
	static void NewObjectImplementation(const FGarbageCollectionHandle Outer,
	                                    const FGarbageCollectionHandle Class, const MonoObject* Name,
	                                    MonoObject** OutValue)
	{
		const auto ObjectOuter = FCSharpEnvironment::GetEnvironment().GetObject(Outer);

		const auto ObjectClass = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(Class);

		const auto ObjectName = FCSharpEnvironment::GetEnvironment().GetString<FName>(Name);

		const auto Object = NewObject<UObject>(ObjectOuter, ObjectClass, *ObjectName);

		*OutValue = FCSharpEnvironment::GetEnvironment().Bind(Object);
	}

	static void DuplicateObjectImplementation(const FGarbageCollectionHandle SourceObject,
	                                          const FGarbageCollectionHandle Outer, const MonoObject* Name,
	                                          MonoObject** OutValue)
	{
		const auto ObjectSourceObject = FCSharpEnvironment::GetEnvironment().GetObject(SourceObject);

		const auto ObjectOuter = FCSharpEnvironment::GetEnvironment().GetObject(Outer);

		const auto ObjectName = FCSharpEnvironment::GetEnvironment().GetString<FName>(Name);

		const auto Object = DuplicateObject<UObject>(ObjectSourceObject, ObjectOuter, *ObjectName);

		*OutValue = FCSharpEnvironment::GetEnvironment().Bind(Object);
	}

	static void LoadObjectImplementation(const FGarbageCollectionHandle Outer,
	                                     MonoString* Name, MonoObject** OutValue)
	{
		const auto ObjectOuter = FCSharpEnvironment::GetEnvironment().GetObject(Outer);

		const auto ObjectName = UTF8_TO_TCHAR(FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(Name));

		const auto Object = LoadObject<UObject>(ObjectOuter, ObjectName);

		*OutValue = FCSharpEnvironment::GetEnvironment().Bind(Object);
	}

	static void LoadClassImplementation(const FGarbageCollectionHandle Outer,
	                                    MonoString* Name, MonoObject** OutValue)
	{
		const auto ObjectOuter = FCSharpEnvironment::GetEnvironment().GetObject(Outer);

		const auto ObjectName = UTF8_TO_TCHAR(FCSharpEnvironment::GetEnvironment().GetDomain()->String_To_UTF8(Name));

		const auto Class = LoadClass<UObject>(ObjectOuter, ObjectName);

		*OutValue = FCSharpEnvironment::GetEnvironment().Bind(Class);
	}

	static void CreateWidgetImplementation(const FGarbageCollectionHandle InOwningObject,
	                                       const FGarbageCollectionHandle InUserWidgetClass, MonoObject** OutValue)
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

		*OutValue = FCSharpEnvironment::GetEnvironment().Bind(UserWidget);
	}

	static void GWorldImplementation(MonoObject** OutValue)
	{
		*OutValue = FCSharpEnvironment::GetEnvironment().Bind(GWorld);
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
