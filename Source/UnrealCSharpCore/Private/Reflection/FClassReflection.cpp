#include "Reflection/FClassReflection.h"
#include "CoreMacro/Macro.h"
#include "CoreMacro/ClassMacro.h"
#include "CoreMacro/FunctionMacro.h"
#include "Domain/Script/IScriptDomain.h"
#include "Reflection/FReflectionRegistry.h"
#include "Template/TGetArrayLength.inl"

struct FManagedReader
{
	static bool ManagedHandle2Bool(const IManagedHandle& InManagedHandle)
	{
		return InManagedHandle.Value != 0;
	}

	static int32 ManagedHandle2Int32(const IManagedHandle& InManagedHandle)
	{
		return static_cast<int32>(InManagedHandle.Value);
	}

	FString ManagedHandle2String(IManagedHandle& InManagedHandle) const
	{
		if (IManagedHandleIsValid(InManagedHandle))
		{
			const auto Result = ScriptDomain->StringToFString(InManagedHandle);

			ScriptDomain->Free(InManagedHandle);

			InManagedHandle = InvalidManagedHandle;

			return Result;
		}

		return {};
	}

	static FClassReflection* ManagedHandle2Class(IManagedHandle& InManagedHandle)
	{
		if (IManagedHandleIsValid(InManagedHandle))
		{
			const auto Result = FReflectionRegistry::Get().GetClass(InManagedHandle);

			InManagedHandle = InvalidManagedHandle;

			return Result;
		}

		return {};
	}

	IManagedHandle ArrayGet(const IManagedHandle InManagedHandle, const int32 InIndex) const
	{
		return ScriptDomain->ArrayGet(InManagedHandle, InIndex);
	}

	bool ArrayGetBool(const IManagedHandle InManagedHandle, const int32 InIndex) const
	{
		if (const auto ManagedHandle = ArrayGet(InManagedHandle, InIndex); IManagedHandleIsValid(ManagedHandle))
		{
			const auto Result = *static_cast<bool*>(ScriptDomain->UnboxValue(ManagedHandle));

			ScriptDomain->Free(ManagedHandle);

			return Result;
		}

		return {};
	}

	int32 ArrayGetInt32(const IManagedHandle InManagedHandle, const int32 InIndex) const
	{
		if (const auto ManagedHandle = ArrayGet(InManagedHandle, InIndex); IManagedHandleIsValid(ManagedHandle))
		{
			const auto Result = *static_cast<int32*>(ScriptDomain->UnboxValue(ManagedHandle));

			ScriptDomain->Free(ManagedHandle);

			return Result;
		}

		return {};
	}

	FString ArrayGetString(const IManagedHandle InManagedHandle, const int32 InIndex) const
	{
		if (const auto ManagedHandle = ArrayGet(InManagedHandle, InIndex); IManagedHandleIsValid(ManagedHandle))
		{
			const auto Result = ScriptDomain->StringToFString(ManagedHandle);

			ScriptDomain->Free(ManagedHandle);

			return Result;
		}

		return {};
	}

	FClassReflection* ArrayGetClass(const IManagedHandle InManagedHandle, const int32 InIndex) const
	{
		if (const auto ManagedHandle = ArrayGet(InManagedHandle, InIndex); IManagedHandleIsValid(ManagedHandle))
		{
			return FReflectionRegistry::Get().GetClass(ManagedHandle);
		}

		return {};
	}

	void Free(IManagedHandle* InParams, const int32 InIndex) const
	{
		ScriptDomain->Free(InParams[InIndex]);

		InParams[InIndex] = InvalidManagedHandle;
	}

	IScriptDomain* ScriptDomain;
};

FClassReflection::FClassReflection(const IManagedHandle InManagedClass, const FString& InName):
	FReflection(InName),
	ManagedClass(InManagedClass)
{
}

FClassReflection::~FClassReflection()
{
	Deinitialize();
}

void FClassReflection::ParseDescriptor(const FManagedReader& InManagedReader, IManagedHandle* InParams)
{
	if (const auto Class = InManagedReader.ManagedHandle2Class(InParams[1]))
	{
		TypeDefinition = Class;
	}
	else
	{
		TypeDefinition = this;
	}

	NameSpace = InManagedReader.ManagedHandle2String(InParams[2]);

	PathName = InManagedReader.ManagedHandle2String(InParams[3]);

	if (Name != CLASS_UTILS)
	{
		Parent = InManagedReader.ManagedHandle2Class(InParams[4]);
	}
	else
	{
		InManagedReader.Free(InParams, 4);
	}

	UnderlyingType = InManagedReader.ManagedHandle2Class(InParams[5]);

	bIsClass = InManagedReader.ManagedHandle2Bool(InParams[6]);

	bIsEnum = InManagedReader.ManagedHandle2Bool(InParams[7]);

	if (bIsClass || bIsEnum)
	{
		for (auto GenericArgumentIndex = 0; GenericArgumentIndex < InManagedReader.ManagedHandle2Int32(InParams[8]);
		     ++GenericArgumentIndex)
		{
			GenericArguments.Add(InManagedReader.ArrayGetClass(InParams[9], GenericArgumentIndex));
		}

		InManagedReader.Free(InParams, 9);

		for (auto InterfaceIndex = 0; InterfaceIndex < InManagedReader.ManagedHandle2Int32(InParams[10]);
		     ++InterfaceIndex)
		{
			Interfaces.Add(InManagedReader.ArrayGetClass(InParams[11], InterfaceIndex));
		}

		InManagedReader.Free(InParams, 11);

		auto ClassAttributeIndex = 0;

		for (auto AttributeIndex = 0; AttributeIndex < InManagedReader.ManagedHandle2Int32(InParams[12]);
		     ++AttributeIndex)
		{
			const auto Attribute = InManagedReader.ArrayGetClass(InParams[13], AttributeIndex);

			Attributes.Add(Attribute);

			const auto AttributeValueCount = InManagedReader.ArrayGetInt32(InParams[14], AttributeIndex);

			for (auto AttributeValueIndex = 0; AttributeValueIndex < AttributeValueCount; ++AttributeValueIndex)
			{
				AttributeValues.FindOrAdd(Attribute).Add(
					InManagedReader.ArrayGetString(InParams[15], ClassAttributeIndex + AttributeValueIndex));
			}

			ClassAttributeIndex += AttributeValueCount;
		}

		InManagedReader.Free(InParams, 13);

		InManagedReader.Free(InParams, 14);

		InManagedReader.Free(InParams, 15);
	}
}

void FClassReflection::ParseProperties(const FManagedReader& InManagedReader, IManagedHandle* InParams)
{
	if (!bIsClass)
	{
		return;
	}

	auto PropertyAttributeIndex = 0;

	auto PropertyAttributeValueIndex = 0;

	for (auto PropertyIndex = 0; PropertyIndex < InManagedReader.ManagedHandle2Int32(InParams[1]); ++PropertyIndex)
	{
		auto PropertyName = InManagedReader.ArrayGetString(InParams[2], PropertyIndex);

		const auto AttributeCount = InManagedReader.ArrayGetInt32(InParams[5], PropertyIndex);

		TSet<FClassReflection*> PropertyAttributes;

		TMap<FClassReflection*, TArray<FString>> PropertyAttributeValues;

		for (auto AttributeIndex = 0; AttributeIndex < AttributeCount; ++AttributeIndex)
		{
			const auto Attribute = InManagedReader.ArrayGetClass(
				InParams[6], PropertyAttributeIndex + AttributeIndex);

			PropertyAttributes.Add(Attribute);

			const auto AttributeValueCount = InManagedReader.ArrayGetInt32(
				InParams[7], PropertyAttributeIndex + AttributeIndex);

			for (auto AttributeValueIndex = 0; AttributeValueIndex < AttributeValueCount;
			     ++AttributeValueIndex)
			{
				PropertyAttributeValues.FindOrAdd(Attribute).Add(
					InManagedReader.ArrayGetString(InParams[8], PropertyAttributeValueIndex + AttributeValueIndex));
			}

			PropertyAttributeValueIndex += AttributeValueCount;
		}

		PropertyAttributeIndex += AttributeCount;

		Properties.Add(PropertyName, new FPropertyReflection(PropertyName,
		                                                     InManagedReader.ArrayGet(InParams[3], PropertyIndex),
		                                                     FReflectionRegistry::Get().GetClass(
			                                                     InManagedReader.ArrayGet(InParams[4], PropertyIndex)),
		                                                     PropertyAttributes,
		                                                     PropertyAttributeValues));
	}

	InManagedReader.Free(InParams, 2);

	InManagedReader.Free(InParams, 3);

	InManagedReader.Free(InParams, 4);

	InManagedReader.Free(InParams, 5);

	InManagedReader.Free(InParams, 6);

	InManagedReader.Free(InParams, 7);

	InManagedReader.Free(InParams, 8);
}

void FClassReflection::ParseFields(const FManagedReader& InManagedReader, IManagedHandle* InParams)
{
	if (!bIsClass && !bIsEnum)
	{
		return;
	}

	for (auto FieldIndex = 0; FieldIndex < InManagedReader.ManagedHandle2Int32(InParams[1]); ++FieldIndex)
	{
		auto FieldName = InManagedReader.ArrayGetString(InParams[2], FieldIndex);

		Fields.Add(FieldName, new FFieldReflection(FieldName, InManagedReader.ArrayGet(InParams[3], FieldIndex)));
	}

	InManagedReader.Free(InParams, 2);

	InManagedReader.Free(InParams, 3);
}

void FClassReflection::ParseMethods(const FManagedReader& InManagedReader, IManagedHandle* InParams)
{
	if (!bIsClass)
	{
		return;
	}

	auto MethodAttributeIndex = 0;

	auto MethodAttributeValueIndex = 0;

	for (auto MethodIndex = 0; MethodIndex < InManagedReader.ManagedHandle2Int32(InParams[1]); ++MethodIndex)
	{
		auto MethodName = InManagedReader.ArrayGetString(InParams[2], MethodIndex);

		const auto MethodParamCount = InManagedReader.ArrayGetInt32(InParams[5], MethodIndex);

		const auto AttributeCount = InManagedReader.ArrayGetInt32(InParams[11], MethodIndex);

		TSet<FClassReflection*> MethodAttributes;

		TMap<FClassReflection*, TArray<FString>> MethodAttributeValue;

		for (auto AttributeIndex = 0; AttributeIndex < AttributeCount; ++AttributeIndex)
		{
			const auto Attribute = InManagedReader.ArrayGetClass(
				InParams[12], MethodAttributeIndex + AttributeIndex);

			MethodAttributes.Add(Attribute);

			const auto AttributeValueCount = InManagedReader.ArrayGetInt32(
				InParams[13], MethodAttributeIndex + AttributeIndex);

			for (auto AttributeValueIndex = 0; AttributeValueIndex < AttributeValueCount;
			     ++AttributeValueIndex)
			{
				MethodAttributeValue.FindOrAdd(Attribute).Add(
					InManagedReader.ArrayGetString(InParams[14], MethodAttributeValueIndex + AttributeValueIndex));
			}

			MethodAttributeValueIndex += AttributeValueCount;
		}

		MethodAttributeIndex += AttributeCount;

		const auto bIsUFunction = MethodAttributes.Contains(FReflectionRegistry::Get().GetUFunctionAttributeClass());

		auto bMethodIsStatic = false;

		FClassReflection* ReturnType{};

		TArray<FParamReflection*> ParamReflections;

		if (bIsUFunction)
		{
			bMethodIsStatic = InManagedReader.ArrayGetBool(InParams[4], MethodIndex);

			if (const auto ManagedHandle = InManagedReader.ArrayGet(InParams[6], MethodIndex);
				IManagedHandleIsValid(ManagedHandle))
			{
				ReturnType = FReflectionRegistry::Get().GetClass(ManagedHandle);
			}

			const auto MethodParamIndex = InManagedReader.ArrayGetInt32(InParams[7], MethodIndex);

			ParamReflections.Init(nullptr, MethodParamCount);

			for (auto ParamIndex = 0; ParamIndex < MethodParamCount; ++ParamIndex)
			{
				auto ParamName = InManagedReader.ArrayGetString(InParams[8], MethodParamIndex + ParamIndex);

				ParamReflections[ParamIndex] = new FParamReflection(
					ParamName,
					InManagedReader.ArrayGetBool(InParams[10], MethodParamIndex + ParamIndex),
					FReflectionRegistry::Get().
					GetClass(InManagedReader.ArrayGet(InParams[9], MethodParamIndex + ParamIndex)));
			}
		}

		Methods.Add({MethodName, MethodParamCount},
		            new FMethodReflection(MethodName,
		                                  MethodParamCount,
		                                  InManagedReader.ArrayGet(InParams[3], MethodIndex),
		                                  bMethodIsStatic,
		                                  ReturnType,
		                                  ParamReflections,
		                                  MethodAttributes,
		                                  MethodAttributeValue));
	}

	InManagedReader.Free(InParams, 2);

	InManagedReader.Free(InParams, 3);

	InManagedReader.Free(InParams, 4);

	InManagedReader.Free(InParams, 5);

	InManagedReader.Free(InParams, 6);

	InManagedReader.Free(InParams, 7);

	InManagedReader.Free(InParams, 8);

	InManagedReader.Free(InParams, 9);

	InManagedReader.Free(InParams, 10);

	InManagedReader.Free(InParams, 11);

	InManagedReader.Free(InParams, 12);

	InManagedReader.Free(InParams, 13);

	InManagedReader.Free(InParams, 14);
}

void FClassReflection::EnsureDescriptorImplementation()
{
	if (bDescriptorLoaded || bInitializing)
	{
		return;
	}

	TGuardValue<bool> Guard(bInitializing, true);

	if (const auto ScriptDomain = IScriptDomain::Get())
	{
		IManagedHandle Params[16];

		Params[0] = ManagedClass;

		for (auto Index = 1; Index < 16; ++Index)
		{
			Params[Index] = InvalidManagedHandle;
		}

		ScriptDomain->GetClassDescriptor(ManagedClass, reinterpret_cast<PTRINT*>(&Params[1]));

		ParseDescriptor(FManagedReader{ScriptDomain}, &Params[0]);
	}

	bDescriptorLoaded = true;
}

void FClassReflection::EnsureMemberImplementation(
	bool& bLoaded, const int32 InSlotCount,
	void (IScriptDomain::*GetMemberFunction)(const IManagedHandle, PTRINT*),
	void (FClassReflection::*ParseMemberFunction)(const FManagedReader&, IManagedHandle*))
{
	if (bLoaded || bInitializing)
	{
		return;
	}

	EnsureDescriptor();

	TGuardValue<bool> Guard(bInitializing, true);

	if (const auto ScriptDomain = IScriptDomain::Get())
	{
		TArray<IManagedHandle, TInlineAllocator<32>> Params;

		Params.Init(InvalidManagedHandle, InSlotCount + 1);

		Params[0] = ManagedClass;

		(ScriptDomain->*GetMemberFunction)(ManagedClass, reinterpret_cast<PTRINT*>(&Params[1]));

		(this->*ParseMemberFunction)(FManagedReader{ScriptDomain}, &Params[0]);
	}

	bLoaded = true;
}

void FClassReflection::EnsurePropertiesImplementation()
{
	EnsureMemberImplementation(bPropertiesLoaded, 8,
	                           &IScriptDomain::GetClassProperties, &FClassReflection::ParseProperties);
}

void FClassReflection::EnsureFieldsImplementation()
{
	EnsureMemberImplementation(bFieldsLoaded, 3,
	                           &IScriptDomain::GetClassFields, &FClassReflection::ParseFields);
}

void FClassReflection::EnsureMethodsImplementation()
{
	EnsureMemberImplementation(bMethodsLoaded, 14,
	                           &IScriptDomain::GetClassMethods, &FClassReflection::ParseMethods);
}

void FClassReflection::Deinitialize()
{
	for (const auto& [PLACEHOLDER, Property] : Properties)
	{
		delete Property;
	}

	Properties.Empty();

	for (const auto& [PLACEHOLDER, Field] : Fields)
	{
		delete Field;
	}

	Fields.Empty();

	for (const auto& [PLACEHOLDER, Method] : Methods)
	{
		delete Method;
	}

	Methods.Empty();

	if (IManagedHandleIsValid(ManagedClass))
	{
		if (const auto ScriptDomain = IScriptDomain::Get())
		{
			ScriptDomain->Free(ManagedClass);
		}

		ManagedClass = InvalidManagedHandle;
	}
}

IManagedHandle FClassReflection::GetManagedClass() const
{
	return ManagedClass;
}

bool FClassReflection::HasAttribute(const FClassReflection* InAttribute) const
{
	EnsureDescriptor();

	return FReflection::HasAttribute(InAttribute);
}

FString FClassReflection::GetAttributeValue(const FClassReflection* InAttribute, const int32 InIndex) const
{
	EnsureDescriptor();

	return FReflection::GetAttributeValue(InAttribute, InIndex);
}

FClassReflection* FClassReflection::GetTypeDefinition() const
{
	EnsureDescriptor();

	return TypeDefinition;
}

const FString& FClassReflection::GetNameSpace() const
{
	EnsureDescriptor();

	return NameSpace;
}

const FString& FClassReflection::GetPathName() const
{
	EnsureDescriptor();

	return PathName;
}

FClassReflection* FClassReflection::GetParent() const
{
	EnsureDescriptor();

	return Parent;
}

FClassReflection* FClassReflection::GetUnderlyingType() const
{
	EnsureDescriptor();

	return UnderlyingType;
}

bool FClassReflection::IsClass() const
{
	EnsureDescriptor();

	return bIsClass;
}

bool FClassReflection::IsEnum() const
{
	EnsureDescriptor();

	return bIsEnum;
}

bool FClassReflection::IsOverride()
{
	if (!bOverrideLoaded)
	{
		if (IManagedHandleIsValid(ManagedClass))
		{
			if (const auto ScriptDomain = IScriptDomain::Get())
			{
				bIsOverride = ScriptDomain->IsOverride(ManagedClass);
			}
		}

		bOverrideLoaded = true;
	}

	return bIsOverride;
}

const TArray<FClassReflection*>& FClassReflection::GetGenericArguments() const
{
	EnsureDescriptor();

	return GenericArguments;
}

FClassReflection* FClassReflection::GetGenericArgument(const int32 InIndex) const
{
	EnsureDescriptor();

	return GenericArguments.IsValidIndex(InIndex) ? GenericArguments[InIndex] : nullptr;
}

const TArray<FClassReflection*>& FClassReflection::GetInterfaces() const
{
	EnsureDescriptor();

	return Interfaces;
}

const TMap<FString, FPropertyReflection*>& FClassReflection::GetProperties() const
{
	EnsureProperties();

	return Properties;
}

FPropertyReflection* FClassReflection::GetProperty(const FString& InName) const
{
	EnsureProperties();

	const auto FoundProperty = Properties.Find(InName);

	return FoundProperty != nullptr ? *FoundProperty : nullptr;
}

const TMap<FString, FFieldReflection*>& FClassReflection::GetFields() const
{
	EnsureFields();

	return Fields;
}

FFieldReflection* FClassReflection::GetField(const FString& InName) const
{
	EnsureFields();

	const auto FoundField = Fields.Find(InName);

	return FoundField != nullptr ? *FoundField : nullptr;
}

const TMap<TPair<FString, int32>, FMethodReflection*>& FClassReflection::GetMethods() const
{
	EnsureMethods();

	return Methods;
}

FMethodReflection* FClassReflection::GetMethod(const FString& InName, const int32 InParamCount) const
{
	EnsureMethods();

	const auto FoundMethod = Methods.Find({InName, InParamCount});

	return FoundMethod != nullptr ? *FoundMethod : nullptr;
}

FMethodReflection* FClassReflection::GetMethod(const IManagedHandle InManagedMethod)
{
	EnsureMethods();

	for (const auto& [PLACEHOLDER, Method] : Methods)
	{
		if (Method->GetManagedMethod() == InManagedMethod)
		{
			return Method;
		}
	}

	return nullptr;
}

FMethodReflection* FClassReflection::GetParentMethod(const FString& InName, const int32 InParamCount) const
{
	auto Class = this;

	while (Class != nullptr)
	{
		if (const auto FoundMethod = Class->GetMethod(InName, InParamCount))
		{
			return FoundMethod;
		}

		Class = Class->GetParent();
	}

	return nullptr;
}

IManagedHandle FClassReflection::NewObject() const
{
	if (const auto ScriptDomain = IScriptDomain::Get())
	{
		return ScriptDomain->NewObject(ManagedClass);
	}

	return InvalidManagedHandle;
}

IManagedHandle FClassReflection::InitObject(const int32 InParamCount, void** InParams) const
{
	if (const auto Object = NewObject(); IManagedHandleIsValid(Object))
	{
		if (const auto FoundMethod = GetMethod(FUNCTION_OBJECT_CONSTRUCTOR, InParamCount))
		{
			FoundMethod->Runtime_Invoke(Object, InParams);
		}

		return Object;
	}

	return InvalidManagedHandle;
}

void FClassReflection::ConstructorObject(const IManagedHandle InManagedHandle, const int32 InParamCount,
                                         void** InParams) const
{
	if (const auto FoundMethod = GetMethod(FUNCTION_OBJECT_CONSTRUCTOR, InParamCount))
	{
		FoundMethod->Runtime_Invoke(InManagedHandle, InParams);
	}
}

void FClassReflection::ConstructorClass() const
{
	if (const auto FoundMethod = GetMethod(FUNCTION_CLASS_CONSTRUCTOR, 0))
	{
		FoundMethod->Runtime_Invoke(ManagedClass);
	}
}

IManagedHandle FClassReflection::BoxValue(void* InValue) const
{
	EnsureDescriptor();

	if (const auto ScriptDomain = IScriptDomain::Get())
	{
		return ScriptDomain->BoxValue(Name, InValue);
	}

	return InvalidManagedHandle;
}

IManagedHandle FClassReflection::NewArray(const int32 InNum) const
{
	EnsureDescriptor();

	if (const auto ScriptDomain = IScriptDomain::Get())
	{
		return ScriptDomain->NewArray(NameSpace, Name, InNum);
	}

	return InvalidManagedHandle;
}

bool FClassReflection::IsAssignableFrom(const FClassReflection* InSuperClass, const bool bIncludeInterfaces) const
{
	for (auto Class = this; Class != nullptr; Class = Class->Parent)
	{
		Class->EnsureDescriptor();

		if (Class == InSuperClass)
		{
			return true;
		}
	}

	if (bIncludeInterfaces)
	{
		EnsureDescriptor();

		for (const auto Interface : Interfaces)
		{
			if (Interface == InSuperClass)
			{
				return true;
			}
		}
	}

	return false;
}
