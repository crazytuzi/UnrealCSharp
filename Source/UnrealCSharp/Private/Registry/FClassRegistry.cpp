﻿#include "Registry/FClassRegistry.h"
#include "Domain/FDomain.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Dynamic/FDynamicClassGenerator.h"
#include "Environment/FCSharpEnvironment.h"
#include "Template/TAccessPrivate.inl"
#include "Template/TAccessPrivateStub.inl"

TMap<TWeakObjectPtr<UClass>, UClass::ClassConstructorType> FClassRegistry::ClassConstructorMap;

FClassRegistry::FClassRegistry()
{
	Initialize();
}

FClassRegistry::~FClassRegistry()
{
	Deinitialize();
}

void FClassRegistry::Initialize()
{
	FDynamicClassGenerator::ClassConstructorSet.Add(&FClassRegistry::ClassConstructor);
}

void FClassRegistry::Deinitialize()
{
	FDynamicClassGenerator::ClassConstructorSet.Remove(&FClassRegistry::ClassConstructor);

	for (const auto& ClassConstructorPair : ClassConstructorMap)
	{
		if (ClassConstructorPair.Key.IsValid())
		{
			if (ClassConstructorPair.Key->ClassConstructor == &FClassRegistry::ClassConstructor)
			{
				ClassConstructorPair.Key->ClassConstructor = ClassConstructorPair.Value;
			}
		}
	}

	ClassConstructorMap.Empty();

	for (auto& ClassDescriptorPair : ClassDescriptorMap)
	{
		delete ClassDescriptorPair.Value;

		ClassDescriptorPair.Value = nullptr;
	}

	ClassDescriptorMap.Empty();

	PropertyHashMap.Empty();

	for (auto& PropertyDescriptorPair : PropertyDescriptorMap)
	{
		delete PropertyDescriptorPair.Value;

		PropertyDescriptorPair.Value = nullptr;
	}

	PropertyDescriptorMap.Empty();

	FunctionHashMap.Empty();

	for (auto& FunctionDescriptorPair : FunctionDescriptorMap)
	{
		delete FunctionDescriptorPair.Value;

		FunctionDescriptorPair.Value = nullptr;
	}

	FunctionDescriptorMap.Empty();
}

FClassDescriptor* FClassRegistry::GetClassDescriptor(const UStruct* InStruct) const
{
	const auto FoundClassDescriptor = ClassDescriptorMap.Find(InStruct);

	return FoundClassDescriptor != nullptr ? *FoundClassDescriptor : nullptr;
}

FClassDescriptor* FClassRegistry::GetClassDescriptor(const FName& InClassName) const
{
	const auto InClass = LoadObject<UStruct>(nullptr, *InClassName.ToString());

	return InClass != nullptr ? GetClassDescriptor(InClass) : nullptr;
}

FClassDescriptor* FClassRegistry::AddClassDescriptor(const FDomain* InDomain, UStruct* InStruct)
{
	const auto FoundClassDescriptor = ClassDescriptorMap.Find(InStruct);

	if (FoundClassDescriptor != nullptr)
	{
		return *FoundClassDescriptor;
	}

	const auto FoundMonoClass = InDomain->Class_From_Name(
		FUnrealCSharpFunctionLibrary::GetClassNameSpace(InStruct),
		FUnrealCSharpFunctionLibrary::GetFullClass(InStruct));

	if (FoundMonoClass == nullptr)
	{
		return nullptr;
	}

	const auto ClassDescriptor = new FClassDescriptor(InStruct, FoundMonoClass);

	ClassDescriptorMap.Add(InStruct, ClassDescriptor);

	return ClassDescriptor;
}

void FClassRegistry::AddClassConstructor(UClass* InClass)
{
	if (!ClassConstructorMap.Contains(InClass))
	{
		ClassConstructorMap.Add(InClass, InClass->ClassConstructor);

		InClass->ClassConstructor = &FClassRegistry::ClassConstructor;
	}
}

void FClassRegistry::RemoveClassDescriptor(const UStruct* InStruct)
{
	if (const auto FoundClassDescriptor = ClassDescriptorMap.Find(InStruct))
	{
		if (const auto Class = Cast<UClass>(const_cast<UStruct*>(InStruct)))
		{
			Class->ClassConstructor = ClassConstructorMap[Class];

			ClassConstructorMap.Remove(Class);
		}

		delete *FoundClassDescriptor;

		ClassDescriptorMap.Remove(InStruct);
	}
}

FFunctionDescriptor* FClassRegistry::GetFunctionDescriptor(const uint32 InFunctionHash)
{
	const auto FoundFunctionDescriptor = FunctionDescriptorMap.Find(InFunctionHash);

	return FoundFunctionDescriptor != nullptr ? *FoundFunctionDescriptor : nullptr;
}

FFunctionDescriptor* FClassRegistry::GetOrAddFunctionDescriptor(const uint32 InFunctionHash)
{
	if (const auto FoundFunctionDescriptor = GetFunctionDescriptor(InFunctionHash))
	{
		return FoundFunctionDescriptor;
	}

	if (const auto FoundFunctionHash = FunctionHashMap.Find(InFunctionHash))
	{
		if (const auto FoundFunctionDescriptor = FoundFunctionHash->Key->
		                                                            AddFunctionDescriptor(FoundFunctionHash->Value))
		{
			FunctionHashMap.Remove(InFunctionHash);

			FunctionDescriptorMap.Add(InFunctionHash, FoundFunctionDescriptor);

			return FoundFunctionDescriptor;
		}
	}

	return nullptr;
}

FPropertyDescriptor* FClassRegistry::GetOrAddPropertyDescriptor(const uint32 InPropertyHash)
{
	if (const auto FoundPropertyDescriptor = PropertyDescriptorMap.Find(InPropertyHash))
	{
		return *FoundPropertyDescriptor;
	}

	if (const auto FoundPropertyHash = PropertyHashMap.Find(InPropertyHash))
	{
		if (const auto FoundPropertyDescriptor = FoundPropertyHash->Key->
		                                                            AddPropertyDescriptor(FoundPropertyHash->Value))
		{
			PropertyHashMap.Remove(InPropertyHash);

			PropertyDescriptorMap.Add(InPropertyHash, FoundPropertyDescriptor);

			return FoundPropertyDescriptor;
		}
	}

	return nullptr;
}

void FClassRegistry::AddFunctionDescriptor(const uint32 InFunctionHash, FFunctionDescriptor* InFunctionDescriptor)
{
	FunctionDescriptorMap.Add(InFunctionHash, InFunctionDescriptor);
}

void FClassRegistry::AddFunctionHash(const uint32 InFunctionHash, FClassDescriptor* InClassDescriptor,
                                     const FString& InFunctionName)
{
	FunctionHashMap.Add(InFunctionHash, TPair<FClassDescriptor*, FString>(InClassDescriptor, InFunctionName));
}

void FClassRegistry::RemoveFunctionDescriptor(const uint32 InFunctionHash)
{
	if (const auto FoundFunctionDescriptor = FunctionDescriptorMap.Find(InFunctionHash))
	{
		delete *FoundFunctionDescriptor;

		FunctionDescriptorMap.Remove(InFunctionHash);

		FunctionHashMap.Remove(InFunctionHash);
	}
}

void FClassRegistry::AddPropertyDescriptor(const uint32 InPropertyHash, FPropertyDescriptor* InPropertyDescriptor)
{
	PropertyDescriptorMap.Add(InPropertyHash, InPropertyDescriptor);
}

void FClassRegistry::AddPropertyHash(const uint32 InPropertyHash, FClassDescriptor* InClassDescriptor,
                                     const FString& InPropertyName)
{
	PropertyHashMap.Add(InPropertyHash, TPair<FClassDescriptor*, FString>(InClassDescriptor, InPropertyName));
}

void FClassRegistry::RemovePropertyDescriptor(const uint32 InPropertyHash)
{
	if (const auto FoundPropertyDescriptor = PropertyDescriptorMap.Find(InPropertyHash))
	{
		delete *FoundPropertyDescriptor;

		PropertyDescriptorMap.Remove(InPropertyHash);
	}
}

struct FObjectInitializer_bIsDeferredInitializer
{
	typedef bool (FObjectInitializer::*Type);
};

template struct TAccessPrivateStub<FObjectInitializer_bIsDeferredInitializer,
                                   &FObjectInitializer::bIsDeferredInitializer>;

void FClassRegistry::ClassConstructor(const FObjectInitializer& InObjectInitializer)
{
	auto Class = InObjectInitializer.GetClass();

	while (Class != nullptr)
	{
		if (ClassConstructorMap.Contains(Class) && ClassConstructorMap[Class] != &FClassRegistry::ClassConstructor)
		{
			ClassConstructorMap[Class](InObjectInitializer);

			break;
		}

		Class = Class->GetSuperClass();
	}

	if (IsInGameThread())
	{
		if (FMonoDomain::bLoadSucceed)
		{
			if (const auto FoundMonoObject = FCSharpEnvironment::GetEnvironment().GetObject(
				InObjectInitializer.GetObj()))
			{
				auto& ObjectInitializer = FObjectInitializer::Get();

				ObjectInitializer.~FObjectInitializer();

				ObjectInitializer.*TAccessPrivate<FObjectInitializer_bIsDeferredInitializer>::Value = true;

				FDomain::Object_Constructor(FoundMonoObject);
			}
		}
	}
}
