#include "Registry/FClassRegistry.h"
#include "Domain/FDomain.h"
#include "Dynamic/FDynamicClassGenerator.h"
#include "Environment/FCSharpEnvironment.h"

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

	for (const auto& [Key, Value] : ClassConstructorMap)
	{
		if (Key.IsValid())
		{
			if (Key->ClassConstructor == &FClassRegistry::ClassConstructor)
			{
				Key->ClassConstructor = Value;
			}
		}
	}

	ClassConstructorMap.Empty();

	for (auto& [Key, Value] : ClassDescriptorMap)
	{
		delete Value;

		Value = nullptr;
	}

	ClassDescriptorMap.Empty();

	PropertyHashMap.Empty();

	for (auto& [Key, Value] : PropertyDescriptorMap)
	{
		delete Value;

		Value = nullptr;
	}

	PropertyDescriptorMap.Empty();

	CSharpFunctionHashMap.Empty();

	UnrealFunctionHashMap.Empty();

	for (auto& [Key, Value] : CSharpFunctionDescriptorMap)
	{
		delete Value;

		Value = nullptr;
	}

	CSharpFunctionDescriptorMap.Empty();

	for (auto& [Key, Value] : UnrealFunctionDescriptorMap)
	{
		delete Value;

		Value = nullptr;
	}

	UnrealFunctionDescriptorMap.Empty();
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

FClassDescriptor* FClassRegistry::AddClassDescriptor(UStruct* InStruct)
{
	if (const auto FoundClassDescriptor = ClassDescriptorMap.Find(InStruct))
	{
		return *FoundClassDescriptor;
	}

	const auto ClassDescriptor = new FClassDescriptor(InStruct);

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
			if (const auto FoundClassConstructor = ClassConstructorMap.Find(Class))
			{
				Class->ClassConstructor = *FoundClassConstructor;

				ClassConstructorMap.Remove(Class);
			}
		}

		delete *FoundClassDescriptor;

		ClassDescriptorMap.Remove(InStruct);
	}
}

FPropertyDescriptor* FClassRegistry::GetOrAddPropertyDescriptor(const uint32 InPropertyHash)
{
	if (const auto FoundPropertyDescriptor = PropertyDescriptorMap.Find(InPropertyHash))
	{
		return *FoundPropertyDescriptor;
	}

	if (const auto FoundPropertyHash = PropertyHashMap.Find(InPropertyHash))
	{
		if (const auto FoundPropertyDescriptor = std::get<0>(*FoundPropertyHash)->AddPropertyDescriptor(
			std::get<1>(*FoundPropertyHash)))
		{
			PropertyHashMap.Remove(InPropertyHash);

			PropertyDescriptorMap.Add(InPropertyHash, FoundPropertyDescriptor);

			return FoundPropertyDescriptor;
		}
	}

	return nullptr;
}

void FClassRegistry::RemoveFunctionDescriptor(const uint32 InFunctionHash)
{
	if (const auto FoundCSharpFunctionDescriptor = CSharpFunctionDescriptorMap.Find(InFunctionHash))
	{
		delete *FoundCSharpFunctionDescriptor;

		CSharpFunctionDescriptorMap.Remove(InFunctionHash);

		CSharpFunctionHashMap.Remove(InFunctionHash);
	}

	if (const auto FoundUnrealFunctionDescriptor = UnrealFunctionDescriptorMap.Find(InFunctionHash))
	{
		delete *FoundUnrealFunctionDescriptor;

		UnrealFunctionDescriptorMap.Remove(InFunctionHash);

		UnrealFunctionHashMap.Remove(InFunctionHash);
	}
}

void FClassRegistry::AddPropertyHash(const uint32 InPropertyHash, FClassDescriptor* InClassDescriptor,
                                     FProperty* InProperty)
{
	PropertyHashMap.Add(InPropertyHash, std::make_tuple(InClassDescriptor, InProperty));
}

void FClassRegistry::RemovePropertyDescriptor(const uint32 InPropertyHash)
{
	if (const auto FoundPropertyDescriptor = PropertyDescriptorMap.Find(InPropertyHash))
	{
		delete *FoundPropertyDescriptor;

		PropertyDescriptorMap.Remove(InPropertyHash);
	}
}

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
		if (FDomain::IsLoadSucceed())
		{
			const auto Object = InObjectInitializer.GetObj();

			if (const auto FoundManagedHandle = FCSharpEnvironment::GetEnvironment().GetObject(Object);
				IManagedHandleIsValid(FoundManagedHandle))
			{
				FDynamicClassGenerator::ObjectDeferredInitializer(InObjectInitializer);

				if (const auto FoundClass = FReflectionRegistry::Get().GetClass(Object->GetClass()))
				{
					FoundClass->ConstructorObject(FoundManagedHandle);
				}
			}
		}
	}
}
