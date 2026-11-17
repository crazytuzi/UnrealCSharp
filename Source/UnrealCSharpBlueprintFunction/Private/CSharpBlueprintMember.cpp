#include "CSharpBlueprintMember.h"

#include "UnrealCSharpCore.h"
#include "Bridge/FTypeBridge.h"
#include "Bridge/FTypeBridge.inl"
#include "CoreMacro/PropertyMacro.h"
#include "Domain/Script/IScriptDomain.h"
#include "Dynamic/FDynamicGenerator.h"
#include "Dynamic/FDynamicGeneratorCore.h"
#include "Reflection/FClassReflection.h"
#include "Reflection/FReflectionRegistry.h"
#include "UObject/Package.h"

bool FCSharpBlueprintMemberInfo::IsValid() const
{
	return ClassReflection != nullptr &&
		(Kind == ECSharpBlueprintMemberKind::Function ? Method != nullptr : Property != nullptr);
}

const FReflection* FCSharpBlueprintMemberInfo::GetReflection() const
{
	return Kind == ECSharpBlueprintMemberKind::Function
		       ? static_cast<const FReflection*>(Method)
		       : static_cast<const FReflection*>(Property);
}

FString FCSharpBlueprintMemberInfo::GetMemberName() const
{
	const auto Reflection = GetReflection();

	return Reflection != nullptr ? Reflection->GetName() : FString();
}

int32 FCSharpBlueprintMemberInfo::GetParamCount() const
{
	return Kind == ECSharpBlueprintMemberKind::Function && Method != nullptr ? Method->GetParamCount() : 0;
}

bool FCSharpBlueprintMemberLibrary::IsScriptDomainReady()
{
	const auto ScriptDomain = IScriptDomain::Get();

	return ScriptDomain != nullptr && ScriptDomain->IsInitialized();
}

bool FCSharpBlueprintMemberLibrary::IsRuntimeActive()
{
	return IsScriptDomainReady() && FUnrealCSharpCoreModule::Get().IsLoaded();
}

bool FCSharpBlueprintMemberLibrary::IsBlueprintCallable(const FMethodReflection* InMethod)
{
	if (InMethod == nullptr || !InMethod->IsUFunction() || InMethod->IsStatic())
	{
		return false;
	}

	const auto& Registry = FReflectionRegistry::Get();

	return InMethod->HasAttribute(Registry.GetBlueprintCallableAttributeClass()) ||
		InMethod->HasAttribute(Registry.GetBlueprintPureAttributeClass());
}

bool FCSharpBlueprintMemberLibrary::IsBlueprintPure(const FMethodReflection* InMethod)
{
	return InMethod != nullptr && InMethod->HasAttribute(FReflectionRegistry::Get().GetBlueprintPureAttributeClass());
}

bool FCSharpBlueprintMemberLibrary::IsBlueprintReadable(const FPropertyReflection* InProperty)
{
	if (InProperty == nullptr || !InProperty->IsUProperty())
	{
		return false;
	}

	const auto& Registry = FReflectionRegistry::Get();

	return InProperty->HasAttribute(Registry.GetBlueprintReadOnlyAttributeClass()) ||
		InProperty->HasAttribute(Registry.GetBlueprintReadWriteAttributeClass());
}

bool FCSharpBlueprintMemberLibrary::IsBlueprintWritable(const FPropertyReflection* InProperty)
{
	return InProperty != nullptr && InProperty->IsUProperty() &&
		InProperty->HasAttribute(FReflectionRegistry::Get().GetBlueprintReadWriteAttributeClass());
}

FClassReflection* FCSharpBlueprintMemberLibrary::GetOverrideClassReflection(UClass* InClass)
{
	if (InClass == nullptr || InClass->IsChildOf<UInterface>() || FDynamicGenerator::IsDynamicClass(InClass))
	{
		return nullptr;
	}

	const auto ClassReflection = FReflectionRegistry::Get().GetClass(TWeakObjectPtr<UField>(InClass));

	return ClassReflection != nullptr && ClassReflection->IsOverride() ? ClassReflection : nullptr;
}

UClass* FCSharpBlueprintMemberLibrary::FindOwnerClass(const FClassReflection* InClassReflection)
{
	if (InClassReflection == nullptr)
	{
		return nullptr;
	}

	const auto& PathName = InClassReflection->GetPathName();

	if (PathName.IsEmpty())
	{
		return nullptr;
	}

	const auto Class = FindObject<UClass>(nullptr, *PathName);

	return Class != nullptr && !Class->HasAnyClassFlags(CLASS_NewerVersionExists) ? Class : nullptr;
}

void FCSharpBlueprintMemberLibrary::ForEachOverrideClass(const TFunctionRef<void(FClassReflection*)>& InFunction)
{
	if (!IsScriptDomainReady())
	{
		return;
	}

	FDynamicGeneratorCore::Generator(FReflectionRegistry::Get().GetOverrideAttributeClass(),
	                                 [&InFunction](FClassReflection* InClassReflection)
	                                 {
		                                 if (InClassReflection != nullptr && InClassReflection->IsClass())
		                                 {
			                                 InFunction(InClassReflection);
		                                 }
	                                 });
}

void FCSharpBlueprintMemberLibrary::ForEachBlueprintMember(FClassReflection* InClassReflection, UClass* InOwnerClass,
                                                           const TFunctionRef<void(const FCSharpBlueprintMemberInfo&)>&
                                                           InFunction)
{
	if (InClassReflection == nullptr)
	{
		return;
	}

	FCSharpBlueprintMemberInfo Info;

	Info.ClassReflection = InClassReflection;

	Info.OwnerClass = InOwnerClass;

	for (const auto& [Pair, Methods] : InClassReflection->GetMethods())
	{
		for (const auto Method : Methods)
		{
			if (IsBlueprintCallable(Method))
			{
				Info.Kind = ECSharpBlueprintMemberKind::Function;

				Info.Method = Method;

				InFunction(Info);

				break;
			}
		}
	}

	Info.Method = nullptr;

	for (const auto& [Name, Property] : InClassReflection->GetProperties())
	{
		if (IsBlueprintReadable(Property))
		{
			Info.Property = Property;

			Info.Kind = ECSharpBlueprintMemberKind::PropertyGet;

			InFunction(Info);

			if (IsBlueprintWritable(Property))
			{
				Info.Kind = ECSharpBlueprintMemberKind::PropertySet;

				InFunction(Info);
			}
		}
	}
}

bool FCSharpBlueprintMemberLibrary::Resolve(UClass* InClass, const ECSharpBlueprintMemberKind InKind,
                                            const FName& InName, const int32 InParamCount,
                                            FCSharpBlueprintMemberInfo& OutInfo)
{
	for (auto Class = InClass; Class != nullptr; Class = Class->GetSuperClass())
	{
		if (const auto ClassReflection = GetOverrideClassReflection(Class))
		{
			if (ResolveDeclared(ClassReflection, Class, InKind, InName, InParamCount, OutInfo))
			{
				return true;
			}
		}
	}

	return false;
}

bool FCSharpBlueprintMemberLibrary::ResolveDeclared(FClassReflection* InClassReflection, UClass* InOwnerClass,
                                                    const ECSharpBlueprintMemberKind InKind, const FName& InName,
                                                    const int32 InParamCount, FCSharpBlueprintMemberInfo& OutInfo)
{
	if (InClassReflection == nullptr)
	{
		return false;
	}

	OutInfo = FCSharpBlueprintMemberInfo();

	OutInfo.Kind = InKind;

	OutInfo.ClassReflection = InClassReflection;

	OutInfo.OwnerClass = InOwnerClass;

	if (InKind == ECSharpBlueprintMemberKind::Function)
	{
		const auto Name = InName.ToString();

		if (const auto FoundMethods = InClassReflection->GetMethods().Find(TTuple<FString, int32>(Name, InParamCount)))
		{
			for (const auto Method : *FoundMethods)
			{
				if (IsBlueprintCallable(Method))
				{
					OutInfo.Method = Method;

					return true;
				}
			}
		}

		FMethodReflection* UniqueMethod = nullptr;

		for (const auto& [Pair, Methods] : InClassReflection->GetMethods())
		{
			if (Pair.Get<0>() != Name)
			{
				continue;
			}

			for (const auto Method : Methods)
			{
				if (IsBlueprintCallable(Method))
				{
					if (UniqueMethod != nullptr)
					{
						return false;
					}

					UniqueMethod = Method;
				}
			}
		}

		OutInfo.Method = UniqueMethod;

		return UniqueMethod != nullptr;
	}

	const auto Property = InClassReflection->GetProperty(InName.ToString());

	if (InKind == ECSharpBlueprintMemberKind::PropertyGet ? IsBlueprintReadable(Property) : IsBlueprintWritable(Property))
	{
		OutInfo.Property = Property;

		return true;
	}

	return false;
}

static FString GetReflectionAttributeValue(const FCSharpBlueprintMemberInfo& InInfo,
                                           FClassReflection* InAttributeClass)
{
	const auto Reflection = InInfo.GetReflection();

	if (Reflection == nullptr || InAttributeClass == nullptr || !Reflection->HasAttribute(InAttributeClass))
	{
		return FString();
	}

	return Reflection->GetAttributeValue(InAttributeClass);
}

FString FCSharpBlueprintMemberLibrary::GetDisplayName(const FCSharpBlueprintMemberInfo& InInfo)
{
	const auto DisplayName = GetReflectionAttributeValue(InInfo,
	                                                     FReflectionRegistry::Get().GetDisplayNameAttributeClass());

	return !DisplayName.IsEmpty() ? DisplayName : InInfo.GetMemberName();
}

FString FCSharpBlueprintMemberLibrary::GetCategory(const FCSharpBlueprintMemberInfo& InInfo)
{
	return GetReflectionAttributeValue(InInfo, FReflectionRegistry::Get().GetCategoryAttributeClass());
}

FString FCSharpBlueprintMemberLibrary::GetToolTip(const FCSharpBlueprintMemberInfo& InInfo)
{
	return GetReflectionAttributeValue(InInfo, FReflectionRegistry::Get().GetToolTipAttributeClass());
}

UFunction* FCSharpBlueprintMemberLibrary::BuildSignature(const FCSharpBlueprintMemberInfo& InInfo,
                                                         const FName& InBaseName)
{
	if (!InInfo.IsValid())
	{
		return nullptr;
	}

	const auto Outer = GetTransientPackage();

	const auto Function = NewObject<UFunction>(Outer,
	                                           MakeUniqueObjectName(Outer, UFunction::StaticClass(), InBaseName),
	                                           RF_Public | RF_Transient);

	auto bHasOutParms = false;

	auto bFailed = false;

	const auto AddParam = [Function, &bHasOutParms, &bFailed](FClassReflection* InType, const FName& InName,
	                                                          const EPropertyFlags InFlags)
	{
		const auto Property = FTypeBridge::Factory(InType, Function, InName, RF_Public | RF_Transient);

		if (Property == nullptr)
		{
			bFailed = true;

			return;
		}

		Property->SetPropertyFlags(InFlags);

		if (Property->HasAnyPropertyFlags(CPF_OutParm))
		{
			bHasOutParms = true;
		}

		Function->AddCppProperty(Property);
	};

	switch (InInfo.Kind)
	{
	case ECSharpBlueprintMemberKind::Function:
		{
			if (const auto Return = InInfo.Method->GetReturn())
			{
				if (const auto Property = FTypeBridge::Factory(Return, Function, TEXT("ReturnValue"),
				                                               RF_Public | RF_Transient))
				{
					Property->SetPropertyFlags(CPF_Parm | CPF_OutParm | CPF_ReturnParm);

					bHasOutParms = true;

					Function->AddCppProperty(Property);
				}
			}

			const auto& Params = InInfo.Method->GetParams();

			for (auto Index = Params.Num() - 1; Index >= 0; --Index)
			{
				AddParam(Params[Index]->GetReflectionType(),
				         FName(*Params[Index]->GetName()),
				         Params[Index]->IsRef() ? CPF_Parm | CPF_OutParm | CPF_ReferenceParm : CPF_Parm);
			}

			FDynamicGeneratorCore::SetFlags(Function, InInfo.Method);

			break;
		}

	case ECSharpBlueprintMemberKind::PropertyGet:
		{
			AddParam(InInfo.Property->GetReflectionType(), TEXT("ReturnValue"),
			         CPF_Parm | CPF_OutParm | CPF_ReturnParm);

			Function->FunctionFlags |= FUNC_BlueprintPure | FUNC_BlueprintCallable;

			break;
		}

	case ECSharpBlueprintMemberKind::PropertySet:
		{
			AddParam(InInfo.Property->GetReflectionType(), TEXT("Value"), CPF_Parm);

			Function->FunctionFlags |= FUNC_BlueprintCallable;

			break;
		}
	}

	if (bFailed)
	{
		DestroySignature(Function);

		return nullptr;
	}

	Function->FunctionFlags |= FUNC_Public;

	Function->FunctionFlags &= ~FUNC_Native;

	if (bHasOutParms)
	{
		Function->FunctionFlags |= FUNC_HasOutParms;
	}

	Function->StaticLink(true);

#if WITH_EDITOR
	if (InInfo.Kind == ECSharpBlueprintMemberKind::Function)
	{
		FDynamicGeneratorCore::SetMetaData(Function, InInfo.Method);
	}
#endif

	return Function;
}

void FCSharpBlueprintMemberLibrary::DestroySignature(UFunction* InFunction)
{
	if (InFunction != nullptr)
	{
		InFunction->RemoveFromRoot();

		InFunction->MarkAsGarbage();
	}
}

uint32 FCSharpBlueprintMemberLibrary::ComputeSignatureHash(const UFunction* InFunction)
{
	uint32 Hash = 0;

	if (InFunction == nullptr)
	{
		return Hash;
	}

	for (TFieldIterator<FProperty> It(InFunction); It && (It->PropertyFlags & CPF_Parm); ++It)
	{
		Hash = HashCombine(Hash, GetTypeHash(It->GetName()));

		Hash = HashCombine(Hash, GetTypeHash(It->GetCPPType()));

		Hash = HashCombine(Hash, static_cast<uint32>(It->PropertyFlags & (CPF_OutParm | CPF_ReferenceParm | CPF_ReturnParm)));
	}

	return Hash;
}

TUniquePtr<FMethodReflection> FCSharpBlueprintMemberLibrary::MakeAccessorMethod(
	const FCSharpBlueprintMemberInfo& InInfo)
{
	if (InInfo.Kind == ECSharpBlueprintMemberKind::Function || !InInfo.IsValid())
	{
		return nullptr;
	}

	const auto ScriptDomain = IScriptDomain::Get();

	if (ScriptDomain == nullptr)
	{
		return nullptr;
	}

	const auto bIsSet = InInfo.Kind == ECSharpBlueprintMemberKind::PropertySet;

	const auto Name = (bIsSet ? PROPERTY_SET_PREFIX : FString(TEXT("get_"))) + InInfo.Property->GetName();

	const auto ParamCount = bIsSet ? 1 : 0;

	const auto ManagedMethod = ScriptDomain->GetMethod(InInfo.ClassReflection->GetManagedClass(), Name, ParamCount);

	if (!IManagedHandleIsValid(ManagedMethod))
	{
		return nullptr;
	}

	TArray<FParamReflection*> Params;

	if (bIsSet)
	{
		Params.Add(new FParamReflection(TEXT("Value"), false, InInfo.Property->GetReflectionType()));
	}

	return MakeUnique<FMethodReflection>(Name, ParamCount, ManagedMethod, false,
	                                     bIsSet ? nullptr : InInfo.Property->GetReflectionType(),
	                                     Params, TSet<FClassReflection*>(),
	                                     TMap<FClassReflection*, TArray<FString>>());
}
