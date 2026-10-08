#include "Registry/FCSharpBind.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Blueprint/UserWidget.h"
#include "Domain/Script/IManagedHandle.h"
#include "Reflection/Function/FCSharpFunctionDescriptor.h"
#include "Reflection/Function/CSharpFunction.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Delegate/FUnrealCSharpModuleDelegates.h"
#include "Template/TGetArrayLength.inl"
#include "Template/TFieldIteratorExt.inl"
#include "Setting/UnrealCSharpSetting.h"
#include "Reflection/FReflectionRegistry.h"
#include "Macro/FunctionMacro.h"
#include "UEVersion.h"

TSet<TWeakObjectPtr<UStruct>> FCSharpBind::NotOverrideTypes;

#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
TMap<TWeakObjectPtr<UClass>, TWeakObjectPtr<UClass>> FCSharpBind::OriginalOwnerClass2DummyOwnerClass;

const TCHAR* const FCSharpBind::DummyOwnerClassNamePrefix = TEXT("DummyOwnerClass");
#endif

FCSharpBind::FCSharpBind()
{
	Initialize();
}

FCSharpBind::~FCSharpBind()
{
	Deinitialize();
}

void FCSharpBind::Initialize()
{
	NotOverrideTypes.Empty();

	OnCSharpEnvironmentInitializeDelegateHandle = FUnrealCSharpModuleDelegates::OnCSharpEnvironmentInitialize.AddRaw(
		this, &FCSharpBind::OnCSharpEnvironmentInitialize);
}

void FCSharpBind::Deinitialize()
{
	if (OnCSharpEnvironmentInitializeDelegateHandle.IsValid())
	{
		FUnrealCSharpModuleDelegates::OnCSharpEnvironmentInitialize.Remove(OnCSharpEnvironmentInitializeDelegateHandle);
	}

#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
	for (auto Iterator = OriginalOwnerClass2DummyOwnerClass.CreateIterator(); Iterator; ++Iterator)
	{
		if (const auto DummyOwnerClass = Iterator.Value().GetEvenIfUnreachable())
		{
			if (DummyOwnerClass->IsRooted())
			{
				DummyOwnerClass->RemoveFromRoot();
			}
			else
			{
				DummyOwnerClass->MarkAsGarbage();
			}
		}

		Iterator.RemoveCurrent();
	}
#endif
}

IManagedHandle FCSharpBind::Bind(UObject* InObject)
{
	if (InObject != nullptr)
	{
		if (const auto FoundManagedHandle = FCSharpEnvironment::GetEnvironment().GetObject(InObject);
			IManagedHandleIsValid(FoundManagedHandle))
		{
			return FoundManagedHandle;
		}

		return Bind<false>(InObject);
	}

	return InvalidManagedHandle;
}

IManagedHandle FCSharpBind::Bind(UClass* InClass)
{
	Bind<false>(InClass);

	return Bind(static_cast<UObject*>(InClass));
}

bool FCSharpBind::Bind(const IManagedHandle InManagedObject, const FName& InStructName)
{
	return BindImplementation(InManagedObject, InStructName);
}

bool FCSharpBind::Bind(FClassDescriptor* InClassDescriptor, UClass* InClass, UFunction* InFunction)
{
	return InFunction != nullptr
		       ? Bind(InClassDescriptor, InClass, InFunction->GetName(), InFunction)
		       : false;
}

bool FCSharpBind::Bind(FClassDescriptor* InClassDescriptor, UClass* InClass,
                       const FString& InMethodName, UFunction* InFunction)
{
	return BindImplementation(InClassDescriptor, InClass, InMethodName, InFunction);
}

bool FCSharpBind::BindClassDefaultObject(UObject* InObject)
{
	if (CanBind(InObject->GetClass()))
	{
		FClassRegistry::AddClassConstructor(InObject->GetClass());

		Bind<false>(InObject);

		return true;
	}
	else
	{
		if (const auto UnrealCSharpSetting = FUnrealCSharpFunctionLibrary::GetMutableDefaultSafe<
			UUnrealCSharpSetting>())
		{
			for (const auto& [Class, bNeedOverrideAttribute] : UnrealCSharpSetting->GetBindClass())
			{
				if (InObject->IsA(Class))
				{
					return bNeedOverrideAttribute ? false : IManagedHandleIsValid(Bind<false>(InObject));
				}
			}
		}
	}

	return false;
}

#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
void FCSharpBind::SuspendDummyOwnerClasses()
{
	FCSharpFunctionRegister::IteratorRegister(
		[](const FCSharpFunctionRegister& InRegister)
		{
			InRegister.SuspendDummyOwnerClass();
		});
}

void FCSharpBind::ResumeDummyOwnerClasses()
{
	FCSharpFunctionRegister::IteratorRegister(
		[](const FCSharpFunctionRegister& InRegister)
		{
			InRegister.ResumeDummyOwnerClass();
		});
}
#endif

bool FCSharpBind::BindImplementation(UStruct* InStruct)
{
	if (InStruct == nullptr)
	{
		return false;
	}

	auto SuperStruct = InStruct->GetSuperStruct();

	while (SuperStruct != nullptr)
	{
		Bind<false>(SuperStruct);

		SuperStruct = SuperStruct->GetSuperStruct();
	}

	const auto NewClassDescriptor = FCSharpEnvironment::GetEnvironment().AddClassDescriptor(InStruct);

	if (NewClassDescriptor == nullptr)
	{
		return false;
	}

	const auto Class = NewClassDescriptor->GetClass();

	if (Class == nullptr)
	{
		FCSharpEnvironment::GetEnvironment().RemoveClassDescriptor(InStruct);

		return false;
	}

	TSet<FString> Fields;

	for (const auto& [Name, Field] : Class->GetFields())
	{
		if (Name.StartsWith(TEXT("__")))
		{
			Fields.Add(Name.RightChop(2));
		}
	}

	TMap<FString, FProperty*> Properties;

	for (TFieldIterator<FProperty> It(InStruct, EFieldIteratorFlags::ExcludeSuper,
	                                  EFieldIteratorFlags::ExcludeDeprecated); It; ++It)
	{
		if (const auto Property = *It)
		{
			Properties.Add(FUnrealCSharpFunctionLibrary::Encode(Property), Property);
		}
	}

	for (const auto& [PropertyName, Property] : Properties)
	{
		for (const auto& Field : Fields)
		{
			if (Field == PropertyName)
			{
				auto FieldHash = FUnrealCSharpFunctionLibrary::GetHash(Property);

				if (auto FoundField = Class->GetField(FString::Printf(TEXT(
					"__%s"
				),
				                                                      *Field)))
				{
					FoundField->SetValue(Class, &FieldHash);
				}

				FCSharpEnvironment::GetEnvironment().AddPropertyHash(FieldHash, NewClassDescriptor, Property);

				Fields.Remove(Field);

				break;
			}
		}
	}

	if (const auto FoundClass = Cast<UClass>(InStruct))
	{
		TMap<FString, UFunction*> Functions;

		for (TFieldIterator<UFunction> It(FoundClass, EFieldIteratorFlags::ExcludeSuper,
		                                  EFieldIteratorFlags::ExcludeDeprecated,
		                                  EFieldIteratorFlags::ExcludeInterfaces); It; ++It)
		{
			if (const auto Function = *It)
			{
				Functions.Add(FUnrealCSharpFunctionLibrary::Encode(Function), Function);
			}
		}

		for (const auto& Interface : FoundClass->Interfaces)
		{
			for (TFieldIterator<UFunction> It(Interface.Class, EFieldIteratorFlags::ExcludeSuper,
			                                  EFieldIteratorFlags::ExcludeDeprecated,
			                                  EFieldIteratorFlags::ExcludeInterfaces); It; ++It)
			{
				if (const auto Function = FoundClass->FindFunctionByName(It->GetFName()))
				{
					Functions.Add(FUnrealCSharpFunctionLibrary::Encode(Function), Function);
				}
			}
		}

		for (const auto& [FunctionName, Function] : Functions)
		{
			for (const auto& Field : Fields)
			{
				if (Field == FunctionName)
				{
					auto FieldHash = FUnrealCSharpFunctionLibrary::GetHash(Function);

					if (auto FoundField = Class->GetField(FString::Printf(TEXT(
						"__%s"
					),
					                                                      *Field)))
					{
						FoundField->SetValue(Class, &FieldHash);
					}

					FCSharpEnvironment::GetEnvironment().AddFunctionHash<FUnrealFunctionDescriptor>(
						FieldHash, NewClassDescriptor, Function);

					Fields.Remove(Field);

					break;
				}
			}
		}

		Functions.Empty();

		for (TFieldIteratorExt<UFunction> It(FoundClass, EFieldIteratorFlags::IncludeSuper,
		                                     EFieldIteratorFlags::ExcludeDeprecated,
		                                     EFieldIteratorFlags::IncludeInterfaces); It; ++It)
		{
			if (auto Function = *It)
			{
				if (Function->HasAnyFunctionFlags(FUNC_BlueprintEvent) &&
#if UE_DO_NATIVE_IMPL_OPTIMIZATION && !WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
					!Function->HasAnyFunctionFlags(FUNC_Native) &&
#endif
					!Function->HasAnyFunctionFlags(FUNC_Final))
				{
					if (const auto Name = Function->GetName(); !Functions.Contains(Name))
					{
						Functions.Emplace(FUnrealCSharpFunctionLibrary::Encode(
							                  Function->HasAnyFunctionFlags(FUNC_Net)
								                  ? FString::Printf(TEXT(
									                  "%s%s"
								                  ),
								                                    *Name,
								                                    *FUNCTION_IMPLEMENTATION_SUFFIX
								                  )
								                  : Name,
							                  Function->IsNative()),
						                  Function);
					}
				}
			}
		}

		for (const auto& [FunctionName, Function] : Functions)
		{
			const auto FunctionParamCount = Function->ReturnValueOffset != MAX_uint16
				                                ? Function->NumParms - 1
				                                : Function->NumParms;

			if (const auto Method = Class->GetMethod(FunctionName, FunctionParamCount);
				Method != nullptr && Method->IsOverride())
			{
				Bind(NewClassDescriptor, FoundClass, FunctionName, Function);
			}
		}
	}

	return true;
}

bool FCSharpBind::BindImplementation(FClassDescriptor* InClassDescriptor, UClass* InClass,
                                     const FString& InMethodName, UFunction* InFunction)
{
	if (InClassDescriptor == nullptr || InClass == nullptr || InFunction == nullptr)
	{
		return false;
	}

	if (InClassDescriptor->HasFunctionDescriptor(FUnrealCSharpFunctionLibrary::GetHash(InFunction)))
	{
		return false;
	}

	const auto OriginalFunction = GetOriginalFunction(InClassDescriptor, InFunction);

	if (OriginalFunction == nullptr)
	{
		return false;
	}

	const auto FunctionName = OriginalFunction->GetFName();

	if (OriginalFunction->GetOuter() == InClass)
	{
		const auto& NewFunctionName = FUnrealCSharpFunctionLibrary::GetOverrideFunctionName(FunctionName);

		const auto OverrideFunction = DuplicateFunction(OriginalFunction, InClass, *NewFunctionName);

		const auto OriginalFunctionFlags = OriginalFunction->FunctionFlags;

		const auto OriginalNativeFunc = OriginalFunction->GetNativeFunc();

#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
		const auto OwnerClassInfo = RegisterCallCSharpNativeFunction(InClass, OriginalFunction);
#else
		RegisterCallCSharpNativeFunction(InClass, OriginalFunction);
#endif

		auto FunctionHash = FUnrealCSharpFunctionLibrary::GetHash(OriginalFunction);

		FCSharpEnvironment::GetEnvironment().AddFunctionHash<FCSharpFunctionDescriptor>(
			FunctionHash, InClassDescriptor, OriginalFunction,
#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
			FCSharpFunctionRegister(OriginalFunction, OverrideFunction,
			                        OriginalFunctionFlags, OriginalNativeFunc, OwnerClassInfo));
#else
		FCSharpFunctionRegister(OriginalFunction, OverrideFunction,
		                        OriginalFunctionFlags, OriginalNativeFunc));
#endif

		if (FUnrealCSharpFunctionLibrary::EnableCallOverrideFunction())
		{
			const auto& OverrideMethodName = FUnrealCSharpFunctionLibrary::GetOverrideFunctionName(InMethodName);

			auto OverrideFunctionHash = FUnrealCSharpFunctionLibrary::GetHash(OverrideFunction);

			if (const auto FoundClass = FReflectionRegistry::Get().GetClass(InClass))
			{
				if (const auto FoundField = FoundClass->GetField(FString::Printf(TEXT(
					"__%s"
				),
					*OverrideMethodName
				)))
				{
					FoundField->SetValue(FoundClass, &OverrideFunctionHash);
				}
			}

			FCSharpEnvironment::GetEnvironment().AddFunctionHash<FUnrealFunctionDescriptor>(
				OverrideFunctionHash, InClassDescriptor, OverrideFunction);
		}
	}
	else
	{
		auto NewFunction = InClass->FindFunctionByName(FunctionName, EIncludeSuperFlag::ExcludeSuper);

		if (NewFunction != nullptr)
		{
			return false;
		}

		NewFunction = DuplicateFunction(OriginalFunction, InClass, FunctionName);

#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
		const auto OwnerClassInfo = RegisterCallCSharpNativeFunction(InClass, NewFunction);
#else
		RegisterCallCSharpNativeFunction(InClass, NewFunction);
#endif

		auto FunctionHash = FUnrealCSharpFunctionLibrary::GetHash(NewFunction);

		FCSharpEnvironment::GetEnvironment().AddFunctionHash<FCSharpFunctionDescriptor>(
			FunctionHash, InClassDescriptor, NewFunction,
#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
			FCSharpFunctionRegister(NewFunction, OriginalFunction, FUNC_None, nullptr, OwnerClassInfo));
#else
		FCSharpFunctionRegister(NewFunction, OriginalFunction, FUNC_None, nullptr));
#endif
	}

	return true;
}

bool FCSharpBind::BindImplementation(const IManagedHandle InManagedObject, const FName& InStructName)
{
	const auto InScriptStruct = LoadObject<UScriptStruct>(nullptr, *InStructName.ToString());

	if (InScriptStruct == nullptr)
	{
		return false;
	}

	if (!Bind<false>(InScriptStruct))
	{
		return false;
	}

	const auto StructureSize = InScriptStruct->GetStructureSize() ? InScriptStruct->GetStructureSize() : 1;

	const auto Structure = static_cast<void*>(static_cast<uint8*>(FMemory::Malloc(StructureSize)));

	InScriptStruct->InitializeStruct(Structure);

	FCSharpEnvironment::GetEnvironment().AddStructReference<true>(InScriptStruct, Structure, InManagedObject);

	return true;
}

bool FCSharpBind::CanBind(UStruct* InStruct)
{
	if (NotOverrideTypes.Contains(InStruct))
	{
		return false;
	}

	if (auto FoundClass = FReflectionRegistry::Get().GetClass(InStruct))
	{
		return FoundClass->IsOverride();
	}

	return false;
}

UFunction* FCSharpBind::GetOriginalFunction(FClassDescriptor* InClassDescriptor, UFunction* InFunction)
{
	if (InClassDescriptor == nullptr || InFunction == nullptr)
	{
		return nullptr;
	}

	if (!IsCallCSharpFunction(InFunction))
	{
		return InFunction;
	}

	const auto FoundFunctionDescriptor = static_cast<FCSharpFunctionDescriptor*>(
		InClassDescriptor->GetFunctionDescriptor(InFunction->GetName()));

	if (const auto OriginalFunction = FoundFunctionDescriptor != nullptr
		                                  ? FoundFunctionDescriptor->GetOriginalFunction().Get()
		                                  : nullptr;
		OriginalFunction != nullptr && !IsCallCSharpFunction(OriginalFunction))
	{
		return OriginalFunction;
	}

	const auto SuperClass = InFunction->GetOuterUClass()->GetSuperClass();

	const auto SuperOriginalFunction = SuperClass != nullptr
		                                   ? SuperClass->FindFunctionByName(InFunction->GetFName())
		                                   : nullptr;

	return GetOriginalFunction(InClassDescriptor, SuperOriginalFunction);
}

bool FCSharpBind::IsCallCSharpFunction(const UFunction* InFunction)
{
	return InFunction != nullptr && InFunction->GetNativeFunc() == &UCSharpFunction::execCallCSharp;
}

#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
FCSharpFunctionOwnerClassInfo FCSharpBind::RegisterCallCSharpNativeFunction(UClass* InClass, UFunction* InFunction)
#else
void FCSharpBind::RegisterCallCSharpNativeFunction(UClass* InClass, UFunction* InFunction)
#endif
{
#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
	FCSharpFunctionOwnerClassInfo OwnerClassInfo;
#endif

	if (InClass != nullptr && InFunction != nullptr)
	{
#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
		OwnerClassInfo.OriginalOwnerClass = GetOriginalOwnerClass(InFunction);

		OwnerClassInfo.DummyOwnerClass = GetOrCreateDummyOwnerClass(InFunction);
#endif

		InFunction->SetNativeFunc(UCSharpFunction::execCallCSharp);

		InFunction->FunctionFlags |= FUNC_Native;

		if (!InClass->NativeFunctionLookupTable.ContainsByPredicate(
			[InFunction](const FNativeFunctionLookup& InNativeFunctionLookup)
			{
				return InNativeFunctionLookup.Name == InFunction->GetFName();
			}))
		{
			InClass->AddNativeFunction(*InFunction->GetName(), &UCSharpFunction::execCallCSharp);
		}

		RegisterScriptTick(InClass, InFunction);
	}

#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
	return OwnerClassInfo;
#endif
}

#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
UClass* FCSharpBind::GetOrCreateDummyOwnerClass(UClass* InClass)
{
	UClass* DummyOwnerClass{};

	if (InClass != nullptr)
	{
		if (const auto FoundDummyOwnerClass = OriginalOwnerClass2DummyOwnerClass.Find(InClass))
		{
			DummyOwnerClass = FoundDummyOwnerClass->Get();
		}

		if (DummyOwnerClass == nullptr)
		{
			const auto Name = MakeUniqueObjectName(
				UObject::StaticClass()->GetPackage(),
				UClass::StaticClass(),
				*FString::Printf(TEXT(
					"%s%s"
				),
				                 DummyOwnerClassNamePrefix,
				                 *InClass->GetName())
			);

			if (const auto DummyClass = NewObject<UClass>(
				UObject::StaticClass()->GetPackage(),
				UClass::StaticClass(),
				Name,
				RF_Public | RF_Transient))
			{
				DummyClass->AddToRoot();

				DummyClass->SetSuperStruct(UObject::StaticClass());

				DummyClass->ClassConstructor = UObject::StaticClass()->ClassConstructor;

				DummyClass->ClassWithin = UObject::StaticClass()->ClassWithin;

				DummyClass->ClassCastFlags = UObject::StaticClass()->ClassCastFlags;

				DummyClass->ClassFlags |= CLASS_TokenStreamAssembled;

				DummyClass->PropertiesSize = UObject::StaticClass()->GetPropertiesSize();

				DummyClass->MinAlignment = UObject::StaticClass()->GetMinAlignment();

				(void)DummyClass->GetDefaultObject(true);

				OriginalOwnerClass2DummyOwnerClass.Add(InClass, DummyClass);

				DummyOwnerClass = DummyClass;
			}
		}
	}

	return DummyOwnerClass;
}

UClass* FCSharpBind::GetOrCreateDummyOwnerClass(UFunction* InFunction)
{
	UClass* DummyOwnerClass{};

	if (InFunction != nullptr)
	{
		if (const auto OuterClass = Cast<UClass>(InFunction->GetOuter());
			OuterClass != nullptr && OuterClass->GetName().StartsWith(DummyOwnerClassNamePrefix))
		{
			DummyOwnerClass = OuterClass;
		}
		else
		{
			if (const auto OwnerClass = InFunction->GetOwnerClass();
				OwnerClass != nullptr && InFunction->HasAnyFunctionFlags(FUNC_Native))
			{
				DummyOwnerClass = GetOrCreateDummyOwnerClass(OwnerClass);

				if (DummyOwnerClass != nullptr)
				{
					InFunction->Rename(nullptr, DummyOwnerClass,
					                   REN_DontCreateRedirectors | REN_NonTransactional | REN_DoNotDirty);
				}
			}
		}
	}

	return DummyOwnerClass;
}

UClass* FCSharpBind::GetOriginalOwnerClass(const UFunction* InFunction)
{
	UClass* OriginalOwnerClass{};

	if (InFunction != nullptr)
	{
		if (const auto OuterClass = Cast<UClass>(InFunction->GetOuter());
			OuterClass != nullptr && OuterClass->GetName().StartsWith(DummyOwnerClassNamePrefix))
		{
			if (const auto FoundOriginalOwnerClass = OriginalOwnerClass2DummyOwnerClass.FindKey(OuterClass))
			{
				OriginalOwnerClass = FoundOriginalOwnerClass->Get();
			}
		}
		else
		{
			OriginalOwnerClass = OuterClass;
		}
	}

	return OriginalOwnerClass;
}
#endif

void FCSharpBind::RegisterScriptTick(const UClass* InClass, const UFunction* InFunction)
{
	if (InClass != nullptr && InFunction != nullptr)
	{
		static const FName ReceiveTickName(GET_FUNCTION_NAME_CHECKED(AActor, ReceiveTick));

		static const FName TickName(GET_FUNCTION_NAME_CHECKED(UUserWidget, Tick));

		static const FName OnPaintName(GET_FUNCTION_NAME_CHECKED(UUserWidget, OnPaint));

		const auto FunctionName = InFunction->GetFName();

		const auto bIsReceiveTick = FunctionName == ReceiveTickName &&
			(InClass->IsChildOf<AActor>() || InClass->IsChildOf<UActorComponent>()) &&
			(InClass->HasAnyClassFlags(CLASS_CompiledFromBlueprint) || !InClass->HasAnyClassFlags(CLASS_Native));

		const auto bIsTick = FunctionName == TickName && InClass->IsChildOf<UUserWidget>();

		const auto bIsOnPaint = FunctionName == OnPaintName && InClass->IsChildOf<UUserWidget>();

		if (bIsReceiveTick || bIsTick || bIsOnPaint)
		{
			auto RegisterScriptTickImplementation = [bIsReceiveTick, bIsTick, bIsOnPaint](UObject* InObject)
			{
				if (InObject != nullptr && !InObject->HasAnyInternalFlags(EInternalObjectFlags::Garbage))
				{
					if (bIsReceiveTick)
					{
						if (const auto Actor = Cast<AActor>(InObject))
						{
							Actor->PrimaryActorTick.bCanEverTick = true;

							if (!Actor->IsTemplate() &&
								Actor->GetLevel() != nullptr &&
								!Actor->PrimaryActorTick.IsTickFunctionRegistered())
							{
								Actor->RegisterAllActorTickFunctions(false, false);

								Actor->RegisterAllActorTickFunctions(true, false);
							}
						}
						else if (const auto ActorComponent = Cast<UActorComponent>(InObject))
						{
							ActorComponent->PrimaryComponentTick.bCanEverTick = true;

							if (!ActorComponent->IsTemplate() &&
								!ActorComponent->PrimaryComponentTick.IsTickFunctionRegistered())
							{
								ActorComponent->RegisterAllComponentTickFunctions(false);

								ActorComponent->RegisterAllComponentTickFunctions(true);
							}
						}
					}
					else if (bIsTick || bIsOnPaint)
					{
						if (const auto Widget = Cast<UUserWidget>(InObject))
						{
							const auto bHasScriptImplementedTick = Widget->bHasScriptImplementedTick != 0;

							if (bIsTick)
							{
								Widget->bHasScriptImplementedTick = true;
							}

							if (bIsOnPaint)
							{
								Widget->bHasScriptImplementedPaint = true;
							}

							if (bIsTick && !bHasScriptImplementedTick)
							{
								Widget->UpdateCanTick();
							}
						}
					}
				}
			};

			ForEachObjectOfClass(InClass, RegisterScriptTickImplementation, false, RF_NoFlags);
		}
	}
}

UFunction* FCSharpBind::DuplicateFunction(UFunction* InOriginalFunction, UClass* InClass, const FName& InFunctionName)
{
	if (InOriginalFunction == nullptr || InClass == nullptr)
	{
		return nullptr;
	}

	const auto OriginalFunctionFlags = InOriginalFunction->FunctionFlags;

	InOriginalFunction->FunctionFlags &= (~EFunctionFlags::FUNC_Native);

	FObjectDuplicationParameters ObjectDuplicationParameters(InOriginalFunction, InClass);

	ObjectDuplicationParameters.DestClass = UCSharpFunction::StaticClass();

	ObjectDuplicationParameters.DestName = InFunctionName;

	ObjectDuplicationParameters.InternalFlagMask &= (~EInternalObjectFlags::Native);

	const auto NewFunction = Cast<UFunction>(StaticDuplicateObjectEx(ObjectDuplicationParameters));

	InOriginalFunction->FunctionFlags = OriginalFunctionFlags;

	if (NewFunction == nullptr)
	{
		return nullptr;
	}

	NewFunction->FunctionFlags = OriginalFunctionFlags;

	NewFunction->SetNativeFunc(InOriginalFunction->GetNativeFunc());

	NewFunction->StaticLink(true);

	InClass->AddFunctionToFunctionMap(NewFunction, InFunctionName);

	NewFunction->ClearInternalFlags(EInternalObjectFlags::Native);

	if (InClass->HasAnyInternalFlags(EInternalObjectFlags::RootSet) || GUObjectArray.IsDisregardForGC(InClass))
	{
		NewFunction->AddToRoot();
	}

	return NewFunction;
}

void FCSharpBind::OnCSharpEnvironmentInitialize()
{
	for (const auto Class : TObjectRange<UClass>())
	{
		if (const auto DefaultObject = Class->GetDefaultObject(false))
		{
			if (BindClassDefaultObject(DefaultObject))
			{
				TArray<UObject*> Results;

				GetObjectsOfClass(Class, Results, false);

				for (const auto Result : Results)
				{
					Bind(Result);
				}
			}
		}
	}
}
