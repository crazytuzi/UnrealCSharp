#include "Reflection/FClassReflection.h"
#include "CoreMacro/Macro.h"
#include "CoreMacro/ClassMacro.h"
#include "CoreMacro/FunctionMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/PropertyMacro.h"
#include "Domain/Mono/FMonoDomain.h"
#include "Domain/Script/IScriptDomain.h"
#include "Reflection/FReflectionRegistry.h"
#include "Template/TGetArrayLength.inl"

#define FREE_PARAM(InIndex)\
	ScriptDomain->Free(Params[InIndex]); \
	Params[InIndex] = InvalidManagedHandle;

FClassReflection::FClassReflection(const IManagedClass InManagedClass, const FString& InName):
	FReflection(InName),
	ManagedClass(InManagedClass)
{
#if WITH_MONO
	const auto Type = FMonoDomain::Class_Get_Type(ManagedClass);

	ManagedReflectionType = FMonoDomain::Type_Get_Object(Type);
#endif
}

#if WITH_MONO
FClassReflection::FClassReflection(const IManagedReflectionType InManagedReflectionType)
{
	ManagedReflectionType = InManagedReflectionType;

	const auto Type = FMonoDomain::Reflection_Type_Get_Type(ManagedReflectionType);

	ManagedClass = FMonoDomain::Class_From_Type(Type);
}
#endif

FClassReflection::~FClassReflection()
{
	Deinitialize();
}

void FClassReflection::Initialize()
{
#if WITH_MONO
	IManagedReflectionType OutTypeDefinition{};

	IManagedString OutName{};

	IManagedString OutNameSpace{};

	IManagedString OutPathName{};

	IManagedReflectionType OutParent{};

	IManagedReflectionType OutUnderlyingType{};

	int32 OutGenericArgumentLength{};

	IManagedArray OutGenericArguments{};

	int32 OutInterfaceLength{};

	IManagedArray OutInterfaces{};

	int32 OutClassAttributeLength{};

	IManagedArray OutClassAttributes{};

	IManagedArray OutClassAttributeValueLength{};

	IManagedArray OutClassAttributeValues{};

	int32 OutPropertyLength{};

	IManagedArray OutPropertyNames{};

	IManagedArray OutPropertyInfos{};

	IManagedArray OutPropertyTypes{};

	IManagedArray OutPropertyAttributeCounts{};

	IManagedArray OutPropertyAttributes{};

	IManagedArray OutPropertyAttributeValueCounts{};

	IManagedArray OutPropertyAttributeValues{};

	int32 OutFieldLength{};

	IManagedArray OutFieldNames{};

	IManagedArray OutFieldInfos{};

	int32 OutMethodLength{};

	IManagedArray OutMethodNames{};

	IManagedArray OutMethodInfos{};

	IManagedArray OutMethodIsStatics{};

	IManagedArray OutMethodParamCounts{};

	IManagedArray OutMethodReturnTypes{};

	IManagedArray OutMethodParamIndex{};

	IManagedArray OutMethodParamNames{};

	IManagedArray OutMethodParamTypes{};

	IManagedArray OutMethodParamRefs{};

	IManagedArray OutMethodAttributeCounts{};

	IManagedArray OutMethodAttributes{};

	IManagedArray OutMethodAttributeValueCounts{};

	IManagedArray OutMethodAttributeValues{};

	void* InParams[42] = {
		ManagedReflectionType,
		&OutTypeDefinition,
		&OutName,
		&OutNameSpace,
		&OutPathName,
		&OutParent,
		&OutUnderlyingType,
		&bIsClass,
		&bIsEnum,
		&OutGenericArgumentLength,
		&OutGenericArguments,
		&OutInterfaceLength,
		&OutInterfaces,
		&OutClassAttributeLength,
		&OutClassAttributes,
		&OutClassAttributeValueLength,
		&OutClassAttributeValues,
		&OutPropertyLength,
		&OutPropertyNames,
		&OutPropertyInfos,
		&OutPropertyTypes,
		&OutPropertyAttributeCounts,
		&OutPropertyAttributes,
		&OutPropertyAttributeValueCounts,
		&OutPropertyAttributeValues,
		&OutFieldLength,
		&OutFieldNames,
		&OutFieldInfos,
		&OutMethodLength,
		&OutMethodNames,
		&OutMethodInfos,
		&OutMethodIsStatics,
		&OutMethodParamCounts,
		&OutMethodReturnTypes,
		&OutMethodParamIndex,
		&OutMethodParamNames,
		&OutMethodParamTypes,
		&OutMethodParamRefs,
		&OutMethodAttributeCounts,
		&OutMethodAttributes,
		&OutMethodAttributeValueCounts,
		&OutMethodAttributeValues,
	};

	if (Name == CLASS_UTILS)
	{
		if (const auto UtilsClass = FMonoDomain::Class_From_Name(
			COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_UTILS))
		{
			if (const auto GetTypesWithAttributeMethod = FMonoDomain::Class_Get_Method_From_Name(
				UtilsClass, FUNCTION_UTILS_GET_CLASS_REFLECTION, TGetArrayLength(InParams)))
			{
				FMonoDomain::Runtime_Invoke(GetTypesWithAttributeMethod, nullptr, InParams);
			}
		}
	}
	else
	{
		if (auto UtilsClass = FReflectionRegistry::Get().GetUtilsClass())
		{
			if (const auto GetTypesWithAttributeMethod = UtilsClass->GetMethod(
				FUNCTION_UTILS_GET_CLASS_REFLECTION, TGetArrayLength(InParams)))
			{
				GetTypesWithAttributeMethod->Runtime_Invoke(InvalidManagedHandle, InParams);
			}
		}
	}

	if (OutTypeDefinition != ManagedReflectionType)
	{
		TypeDefinition = FReflectionRegistry::Get().GetClass(OutTypeDefinition);
	}
	else
	{
		TypeDefinition = this;
	}

	Name = FMonoDomain::String_To_UTF8(OutName);

	NameSpace = FMonoDomain::String_To_UTF8(OutNameSpace);

	PathName = FMonoDomain::String_To_UTF8(OutPathName);

	if (Name != CLASS_UTILS && OutParent != nullptr)
	{
		Parent = FReflectionRegistry::Get().GetClass(OutParent);
	}

	if (IManagedIsValid(OutUnderlyingType))
	{
		UnderlyingType = FReflectionRegistry::Get().GetClass(OutUnderlyingType);
	}

	if (bIsClass || bIsEnum)
	{
		for (auto GenericArgumentIndex = 0; GenericArgumentIndex < OutGenericArgumentLength; ++GenericArgumentIndex)
		{
			GenericArguments.Add(FReflectionRegistry::Get().GetClass(
				FMonoDomain::Array_Get<IManagedReflectionType>(OutGenericArguments, GenericArgumentIndex)));
		}

		for (auto InterfaceIndex = 0; InterfaceIndex < OutInterfaceLength; ++InterfaceIndex)
		{
			Interfaces.Add(FReflectionRegistry::Get().GetClass(
				FMonoDomain::Array_Get<IManagedReflectionType>(OutInterfaces, InterfaceIndex)));
		}

		auto ClassAttributeIndex = 0;

		for (auto AttributeIndex = 0; AttributeIndex < OutClassAttributeLength; ++AttributeIndex)
		{
			const auto Attribute = FReflectionRegistry::Get().GetClass(
				FMonoDomain::Array_Get<IManagedReflectionType>(OutClassAttributes, AttributeIndex));

			Attributes.Add(Attribute);

			const auto AttributeValueCount = FMonoDomain::Array_Get<int32>(
				OutClassAttributeValueLength, AttributeIndex);

			for (auto AttributeValueIndex = 0; AttributeValueIndex < AttributeValueCount; ++AttributeValueIndex)
			{
				AttributeValues.FindOrAdd(Attribute).Add(
					FMonoDomain::String_To_UTF8(FMonoDomain::Array_Get<IManagedString>(OutClassAttributeValues,
						ClassAttributeIndex + AttributeValueIndex)));
			}

			ClassAttributeIndex += AttributeValueCount;
		}

		if (Name != CLASS_UTILS)
		{
			bIsOverride = HasAttribute(FReflectionRegistry::Get().GetOverrideAttributeClass()) ||
				HasAttribute(FReflectionRegistry::Get().GetUClassAttributeClass());
		}

		auto PropertyAttributeIndex = 0;

		auto PropertyAttributeValueIndex = 0;

		for (auto PropertyIndex = 0; PropertyIndex < OutPropertyLength; ++PropertyIndex)
		{
			auto PropertyName =
				FMonoDomain::String_To_UTF8(FMonoDomain::Array_Get<IManagedString>(OutPropertyNames, PropertyIndex));

			auto AttributeCount = FMonoDomain::Array_Get<int32>(OutPropertyAttributeCounts, PropertyIndex);

			TSet<FClassReflection*> PropertyAttributes;

			TMap<FClassReflection*, TArray<FString>> PropertyAttributeValues;

			for (auto AttributeIndex = 0; AttributeIndex < AttributeCount; ++AttributeIndex)
			{
				const auto Attribute = FReflectionRegistry::Get().GetClass(
					FMonoDomain::Array_Get<IManagedReflectionType>(
						OutPropertyAttributes, PropertyAttributeIndex + AttributeIndex));

				PropertyAttributes.Add(Attribute);

				auto AttributeValueCount = FMonoDomain::Array_Get<int32>(
					OutPropertyAttributeValueCounts, PropertyAttributeIndex + AttributeIndex);

				for (auto AttributeValueIndex = 0; AttributeValueIndex < AttributeValueCount; ++AttributeValueIndex)
				{
					PropertyAttributeValues.FindOrAdd(Attribute).Add(FMonoDomain::String_To_UTF8(
						FMonoDomain::Array_Get<IManagedString>(
							OutPropertyAttributeValues, PropertyAttributeValueIndex + AttributeValueIndex)));
				}

				PropertyAttributeValueIndex += AttributeValueCount;
			}

			PropertyAttributeIndex += AttributeCount;

			Properties.Add(PropertyName,
			               new FPropertyReflection(PropertyName,
			                                       FMonoDomain::Array_Get<IManagedReflectionProperty>(
				                                       OutPropertyInfos, PropertyIndex),
			                                       FReflectionRegistry::Get().GetClass(
				                                       FMonoDomain::Array_Get<IManagedReflectionType>(
					                                       OutPropertyTypes, PropertyIndex)),
			                                       PropertyAttributes, PropertyAttributeValues));
		}

		for (auto FieldIndex = 0; FieldIndex < OutFieldLength; ++FieldIndex)
		{
			auto FieldName =
				FMonoDomain::String_To_UTF8(FMonoDomain::Array_Get<IManagedString>(OutFieldNames, FieldIndex));

			Fields.Add(FieldName,
			           new FFieldReflection(FieldName,
			                                FMonoDomain::Array_Get<IManagedReflectionField>(OutFieldInfos, FieldIndex)
			           ));
		}

		auto MethodAttributeIndex = 0;

		auto MethodAttributeValueIndex = 0;

		for (auto MethodIndex = 0; MethodIndex < OutMethodLength; ++MethodIndex)
		{
			auto MethodName =
				FMonoDomain::String_To_UTF8(FMonoDomain::Array_Get<IManagedString>(OutMethodNames, MethodIndex));

			auto MethodParamCount = FMonoDomain::Array_Get<int32>(OutMethodParamCounts, MethodIndex);

			auto AttributeCount = FMonoDomain::Array_Get<int32>(OutMethodAttributeCounts, MethodIndex);

			TSet<FClassReflection*> MethodAttributes;

			TMap<FClassReflection*, TArray<FString>> MethodAttributeValue;

			for (auto AttributeIndex = 0; AttributeIndex < AttributeCount; ++AttributeIndex)
			{
				const auto Attribute = FReflectionRegistry::Get().GetClass(
					FMonoDomain::Array_Get<IManagedReflectionType>(
						OutMethodAttributes, MethodAttributeIndex + AttributeIndex));

				MethodAttributes.Add(Attribute);

				auto AttributeValueCount = FMonoDomain::Array_Get<int32>(
					OutMethodAttributeValueCounts, MethodAttributeIndex + AttributeIndex);

				for (auto AttributeValueIndex = 0; AttributeValueIndex < AttributeValueCount; ++AttributeValueIndex)
				{
					MethodAttributeValue.FindOrAdd(Attribute).Add(FMonoDomain::String_To_UTF8(
						FMonoDomain::Array_Get<IManagedString>(
							OutMethodAttributeValues, MethodAttributeValueIndex + AttributeValueIndex)));
				}

				MethodAttributeValueIndex += AttributeValueCount;
			}

			MethodAttributeIndex += AttributeCount;

			auto bIsUFunction = MethodAttributes.Contains(
				FReflectionRegistry::Get().GetUFunctionAttributeClass());

			auto bMethodIsStatic = false;

			FClassReflection* ReturnType{};

			TArray<FParamReflection*> ParamReflections;

			if (bIsUFunction)
			{
				bMethodIsStatic = FMonoDomain::Array_Get<bool>(OutMethodIsStatics, MethodIndex);

				ReturnType = FReflectionRegistry::Get().GetClass(
					FMonoDomain::Array_Get<IManagedReflectionType>(OutMethodReturnTypes, MethodIndex));

				const auto MethodParamIndex = FMonoDomain::Array_Get<int32>(OutMethodParamIndex, MethodIndex);

				ParamReflections.Init(nullptr, MethodParamCount);

				for (auto ParamIndex = 0; ParamIndex < MethodParamCount; ++ParamIndex)
				{
					auto ParamName = FMonoDomain::String_To_UTF8(
						FMonoDomain::Array_Get<IManagedString>(OutMethodParamNames, MethodParamIndex + ParamIndex));

					ParamReflections[ParamIndex] = new FParamReflection(
						ParamName,
						FMonoDomain::Array_Get<bool>(OutMethodParamRefs, MethodParamIndex + ParamIndex),
						FReflectionRegistry::Get().GetClass(
							FMonoDomain::Array_Get<IManagedReflectionType>(
								OutMethodParamTypes, MethodParamIndex + ParamIndex)));
				}
			}

			Methods.Add({MethodName, MethodParamCount},
			            new FMethodReflection(MethodName,
			                                  FMonoDomain::Array_Get<int32>(OutMethodParamCounts, MethodIndex),
			                                  FMonoDomain::Array_Get<IManagedReflectionMethod>(
				                                  OutMethodInfos, MethodIndex),
			                                  bMethodIsStatic,
			                                  ReturnType,
			                                  ParamReflections,
			                                  MethodAttributes,
			                                  MethodAttributeValue));
		}
	}
#else
	if (IManagedIsValid(ManagedClass))
	{
		if (const auto ScriptDomain = IScriptDomain::Get())
		{
			constexpr auto ParamCount = 42;

			IManagedHandle Params[ParamCount];

			Params[0] = MANAGED_HANDLE_FROM_OBJECT(ManagedClass);

			for (auto Index = 1; Index < ParamCount; ++Index)
			{
				Params[Index] = InvalidManagedHandle;
			}

			if (const auto UtilsClass = ScriptDomain->GetClass(
					COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_CORE_UOBJECT), CLASS_UTILS);
				IManagedIsValid(UtilsClass))
			{
				if (const auto Method = ScriptDomain->GetMethod(
						UtilsClass, FUNCTION_UTILS_GET_CLASS_REFLECTION, ParamCount);
					IManagedIsValid(Method))
				{
					void* MethodParams[ParamCount];

					for (auto Index = 0; Index < ParamCount; ++Index)
					{
						MethodParams[Index] = &Params[Index];
					}

					ScriptDomain->Invoke(INVALID_MANAGED, Method, ParamCount, MethodParams);
				}
			}

			auto GetBool = [&](const int32 InIndex) -> bool
			{
				return Params[InIndex].Value != 0;
			};

			auto GetInt32 = [&](const int32 InIndex) -> int32
			{
				return static_cast<int32>(Params[InIndex].Value);
			};

			auto GetString = [&](const int32 InIndex) -> FString
			{
				if (IManagedIsValid(Params[InIndex]))
				{
					auto Result = ScriptDomain->StringToFString(Params[InIndex]);

					FREE_PARAM(InIndex)

					return Result;
				}

				return {};
			};

			auto GetClass = [&](const int32 InIndex) -> FClassReflection*
			{
				if (IManagedIsValid(Params[InIndex]))
				{
					const auto Result = FReflectionRegistry::Get().GetClass(
						IManagedHandleToIManagedClass(Params[InIndex]));

					Params[InIndex] = InvalidManagedHandle;

					return Result;
				}

				return {};
			};

			auto ArrayGetBool = [&](const IManagedHandle InManagedHandle, const int32 Index) -> bool
			{
				if (const auto ManagedHandle = ScriptDomain->ArrayGetRef(
						IManagedHandleToIManagedArray(InManagedHandle), Index);
					IManagedIsValid(InManagedHandle))
				{
					const auto Result = *static_cast<bool*>(ScriptDomain->UnboxValue(ManagedHandle));

					ScriptDomain->Free(ManagedHandle);

					return Result;
				}

				return {};
			};

			auto ArrayGetInt32 = [&](const IManagedHandle InManagedHandle, const int32 Index) -> int32
			{
				if (const auto ManagedHandle = ScriptDomain->ArrayGetRef(
						IManagedHandleToIManagedArray(InManagedHandle), Index);
					IManagedIsValid(InManagedHandle))
				{
					const auto Result = *static_cast<int32*>(ScriptDomain->UnboxValue(ManagedHandle));

					ScriptDomain->Free(ManagedHandle);

					return Result;
				}

				return {};
			};

			auto ArrayGetRef = [&](const IManagedHandle InManagedHandle, const int32 InIndex) -> IManagedHandle
			{
				return ScriptDomain->ArrayGetRef(IManagedHandleToIManagedArray(InManagedHandle), InIndex);
			};

			auto ArrayGetString = [&](const IManagedHandle InManagedHandle, const int32 Index) -> FString
			{
				if (const auto ManagedHandle = ArrayGetRef(InManagedHandle, Index);
					IManagedIsValid(InManagedHandle))
				{
					return ScriptDomain->StringToFString(ManagedHandle);
				}

				return {};
			};

			auto ArrayGetClass = [&](const IManagedHandle InManagedHandle, const int32 Index) -> FClassReflection*
			{
				if (const auto ManagedHandle = ArrayGetRef(InManagedHandle, Index);
					IManagedIsValid(InManagedHandle))
				{
					return FReflectionRegistry::Get().GetClass(IManagedHandleToIManagedClass(ManagedHandle));
				}

				return {};
			};

			if (auto Class = GetClass(1))
			{
				TypeDefinition = Class;
			}
			else
			{
				TypeDefinition = this;
			}

			Name = GetString(2);

			NameSpace = GetString(3);

			PathName = GetString(4);

			if (Name != CLASS_UTILS)
			{
				Parent = GetClass(5);
			}
			else
			{
				FREE_PARAM(5)
			}

			UnderlyingType = GetClass(6);

			bIsClass = GetBool(7);

			bIsEnum = GetBool(8);

			if (bIsClass || bIsEnum)
			{
				for (auto GenericArgumentIndex = 0; GenericArgumentIndex < GetInt32(9); ++GenericArgumentIndex)
				{
					GenericArguments.Add(ArrayGetClass(Params[10], GenericArgumentIndex));
				}

				FREE_PARAM(10)

				for (auto InterfaceIndex = 0; InterfaceIndex < GetInt32(11); ++InterfaceIndex)
				{
					Interfaces.Add(ArrayGetClass(Params[12], InterfaceIndex));
				}

				FREE_PARAM(12)

				auto ClassAttributeIndex = 0;

				for (auto AttributeIndex = 0; AttributeIndex < GetInt32(13); ++AttributeIndex)
				{
					const auto Attribute = ArrayGetClass(Params[14], AttributeIndex);

					Attributes.Add(Attribute);

					const auto AttributeValueCount = ArrayGetInt32(Params[15], AttributeIndex);

					for (auto AttributeValueIndex = 0; AttributeValueIndex < AttributeValueCount; ++AttributeValueIndex)
					{
						AttributeValues.FindOrAdd(Attribute).Add(
							ArrayGetString(Params[16], ClassAttributeIndex + AttributeValueIndex));
					}

					ClassAttributeIndex += AttributeValueCount;
				}

				FREE_PARAM(14)

				FREE_PARAM(15)

				FREE_PARAM(16)

				if (Name != CLASS_UTILS)
				{
					bIsOverride = HasAttribute(FReflectionRegistry::Get().GetOverrideAttributeClass()) ||
						HasAttribute(FReflectionRegistry::Get().GetUClassAttributeClass());
				}

				auto PropertyAttributeIndex = 0;

				auto PropertyAttributeValueIndex = 0;

				for (auto PropertyIndex = 0; PropertyIndex < GetInt32(17); ++PropertyIndex)
				{
					auto PropertyName = ArrayGetString(Params[18], PropertyIndex);

					const auto AttributeCount = ArrayGetInt32(Params[21], PropertyIndex);

					TSet<FClassReflection*> PropertyAttributes;

					TMap<FClassReflection*, TArray<FString>> PropertyAttributeValues;

					for (auto AttributeIndex = 0; AttributeIndex < AttributeCount; ++AttributeIndex)
					{
						const auto Attribute = ArrayGetClass(Params[22], PropertyAttributeIndex + AttributeIndex);

						PropertyAttributes.Add(Attribute);

						const auto AttributeValueCount = ArrayGetInt32(
							Params[23], PropertyAttributeIndex + AttributeIndex);

						for (auto AttributeValueIndex = 0; AttributeValueIndex < AttributeValueCount; ++
						     AttributeValueIndex)
						{
							PropertyAttributeValues.FindOrAdd(Attribute).Add(
								ArrayGetString(Params[24], PropertyAttributeValueIndex + AttributeValueIndex));
						}

						PropertyAttributeValueIndex += AttributeValueCount;
					}

					PropertyAttributeIndex += AttributeCount;

					Properties.Add(PropertyName, new FPropertyReflection(PropertyName,
					                                                     IManagedHandleToIManagedReflectionProperty(
						                                                     ArrayGetRef(Params[19], PropertyIndex)),
					                                                     FReflectionRegistry::Get().GetClass(
						                                                     IManagedHandleToIManagedClass(
							                                                     ArrayGetRef(
								                                                     Params[20], PropertyIndex))),
					                                                     PropertyAttributes,
					                                                     PropertyAttributeValues));
				}

				FREE_PARAM(18)

				FREE_PARAM(19)

				FREE_PARAM(20)

				FREE_PARAM(21)

				FREE_PARAM(22)

				FREE_PARAM(23)

				FREE_PARAM(24)

				for (auto FieldIndex = 0; FieldIndex < GetInt32(25); ++FieldIndex)
				{
					auto FieldName = ArrayGetString(Params[26], FieldIndex);

					Fields.Add(FieldName, new FFieldReflection(
						           FieldName,
						           IManagedHandleToIManagedReflectionField(ArrayGetRef(Params[27], FieldIndex))));
				}

				FREE_PARAM(26)

				FREE_PARAM(27)

				auto MethodAttributeIndex = 0;

				auto MethodAttributeValueIndex = 0;

				for (auto MethodIndex = 0; MethodIndex < GetInt32(28); ++MethodIndex)
				{
					auto MethodName = ArrayGetString(Params[29], MethodIndex);

					const auto MethodParamCount = ArrayGetInt32(Params[32], MethodIndex);

					const auto AttributeCount = ArrayGetInt32(Params[38], MethodIndex);

					TSet<FClassReflection*> MethodAttributes;

					TMap<FClassReflection*, TArray<FString>> MethodAttributeValue;

					for (auto AttributeIndex = 0; AttributeIndex < AttributeCount; ++AttributeIndex)
					{
						const auto Attribute = ArrayGetClass(Params[39], MethodAttributeIndex + AttributeIndex);

						MethodAttributes.Add(Attribute);

						const auto AttributeValueCount = ArrayGetInt32(
							Params[40], MethodAttributeIndex + AttributeIndex);

						for (auto AttributeValueIndex = 0; AttributeValueIndex < AttributeValueCount; ++
						     AttributeValueIndex)
						{
							MethodAttributeValue.FindOrAdd(Attribute).Add(
								ArrayGetString(Params[41], MethodAttributeValueIndex + AttributeValueIndex));
						}

						MethodAttributeValueIndex += AttributeValueCount;
					}

					MethodAttributeIndex += AttributeCount;

					auto bIsUFunction = MethodAttributes.Contains(
						FReflectionRegistry::Get().GetUFunctionAttributeClass());

					auto bMethodIsStatic = false;

					FClassReflection* ReturnType{};

					TArray<FParamReflection*> ParamReflections;

					if (bIsUFunction)
					{
						bMethodIsStatic = ArrayGetBool(Params[31], MethodIndex);

						if (const auto ManagedHandle = ArrayGetRef(Params[33], MethodIndex);
							IManagedIsValid(ManagedHandle))
						{
							ReturnType = FReflectionRegistry::Get().GetClass(
								IManagedHandleToIManagedClass(ManagedHandle));
						}

						const auto MethodParamIndex = ArrayGetInt32(Params[34], MethodIndex);

						ParamReflections.Init(nullptr, MethodParamCount);

						for (auto ParamIndex = 0; ParamIndex < MethodParamCount; ++ParamIndex)
						{
							auto ParamName = ArrayGetString(Params[35], MethodParamIndex + ParamIndex);

							ParamReflections[ParamIndex] = new FParamReflection(
								ParamName,
								ArrayGetBool(Params[37], MethodParamIndex + ParamIndex),
								FReflectionRegistry::Get().GetClass(
									IManagedHandleToIManagedClass(
										ArrayGetRef(Params[36], MethodParamIndex + ParamIndex))));
						}
					}

					Methods.Add({MethodName, MethodParamCount},
					            new FMethodReflection(MethodName,
					                                  MethodParamCount,
					                                  IManagedHandleToIManagedReflectionMethod(
						                                  ArrayGetRef(Params[30], MethodIndex)),
					                                  bMethodIsStatic,
					                                  ReturnType,
					                                  ParamReflections,
					                                  MethodAttributes,
					                                  MethodAttributeValue));
				}

				FREE_PARAM(29)

				FREE_PARAM(30)

				FREE_PARAM(31)

				FREE_PARAM(32)

				FREE_PARAM(33)

				FREE_PARAM(34)

				FREE_PARAM(35)

				FREE_PARAM(36)

				FREE_PARAM(37)

				FREE_PARAM(38)

				FREE_PARAM(39)

				FREE_PARAM(40)

				FREE_PARAM(41)
			}
		}
	}
#endif
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

#if WITH_CORECLR
	if (IManagedIsValid(ManagedClass))
	{
		if (const auto ScriptDomain = IScriptDomain::Get())
		{
			if (!bIsEnum)
			{
				uint32 Value{};

				ScriptDomain->SetFieldStaticValue(ManagedClass,
				                                  bIsClass
					                                  ? PROPERTY_STATIC_CLASS_SINGLETON
					                                  : PROPERTY_STATIC_STRUCT_SINGLETON,
				                                  &Value);
			}

			ScriptDomain->Free(MANAGED_HANDLE_FROM_OBJECT(ManagedClass));
		}

		ManagedClass = INVALID_MANAGED;
	}
#endif
}

IManagedClass FClassReflection::GetManagedClass() const
{
	return ManagedClass;
}

#if WITH_MONO
IManagedReflectionType FClassReflection::GetManagedReflectionType() const
{
	return ManagedReflectionType;
}
#endif

FClassReflection* FClassReflection::GetTypeDefinition() const
{
	return TypeDefinition;
}

const FString& FClassReflection::GetNameSpace() const
{
	return NameSpace;
}

const FString& FClassReflection::GetPathName() const
{
	return PathName;
}

FClassReflection* FClassReflection::GetParent() const
{
	return Parent;
}

FClassReflection* FClassReflection::GetUnderlyingType() const
{
	return UnderlyingType;
}

bool FClassReflection::IsClass() const
{
	return bIsClass;
}

bool FClassReflection::IsEnum() const
{
	return bIsEnum;
}

bool FClassReflection::IsOverride() const
{
	return bIsOverride;
}

const TArray<FClassReflection*>& FClassReflection::GetGenericArguments() const
{
	return GenericArguments;
}

FClassReflection* FClassReflection::GetGenericArgument(const int32 InIndex) const
{
	return GenericArguments.IsValidIndex(InIndex) ? GenericArguments[InIndex] : nullptr;
}

const TArray<FClassReflection*>& FClassReflection::GetInterfaces() const
{
	return Interfaces;
}

const TMap<FString, FPropertyReflection*>& FClassReflection::GetProperties() const
{
	return Properties;
}

FPropertyReflection* FClassReflection::GetProperty(const FString& InName) const
{
	const auto FoundProperty = Properties.Find(InName);

	return FoundProperty != nullptr ? *FoundProperty : nullptr;
}

const TMap<FString, FFieldReflection*>& FClassReflection::GetFields() const
{
	return Fields;
}

FFieldReflection* FClassReflection::GetField(const FString& InName) const
{
	const auto FoundField = Fields.Find(InName);

	return FoundField != nullptr ? *FoundField : nullptr;
}

const TMap<TPair<FString, int32>, FMethodReflection*>& FClassReflection::GetMethods() const
{
	return Methods;
}

FMethodReflection* FClassReflection::GetMethod(const FString& InName, const int32 InParamCount) const
{
	const auto FoundMethod = Methods.Find({InName, InParamCount});

	return FoundMethod != nullptr ? *FoundMethod : nullptr;
}

FMethodReflection* FClassReflection::GetMethod(const IManagedReflectionMethod InManagedReflectionMethod)
{
#if WITH_MONO
	const auto ManagedMethod = InManagedReflectionMethod->method;
#else
	const auto ManagedMethod = IManagedHandleToIManagedMethod(MANAGED_HANDLE_FROM_OBJECT(InManagedReflectionMethod));
#endif

	for (const auto& [PLACEHOLDER, Method] : Methods)
	{
		if (Method->GetManagedMethod() == ManagedMethod)
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
		FoundMethod->Runtime_Invoke(MANAGED_HANDLE_FROM_OBJECT(ManagedClass), nullptr);
	}
}

IManagedHandle FClassReflection::NewGCHandle(const IManagedHandle InManagedHandle, const bool bPinned) const
{
	auto ManagedHandle = InvalidManagedHandle;

	if (const auto ScriptDomain = IScriptDomain::Get())
	{
		ManagedHandle = ScriptDomain->NewRef(InManagedHandle, bPinned);
	}

	void* InParams[] = {&ManagedHandle};

	if (const auto FoundProperty = GetProperty(PROPERTY_GARBAGE_COLLECTION_HANDLE))
	{
		FoundProperty->SetValue(InManagedHandle, InParams);
	}

	return ManagedHandle;
}

IManagedHandle FClassReflection::NewWeakRefGCHandle(const IManagedHandle InManagedHandle,
                                                    const bool bTrackResurrection) const
{
	auto ManagedHandle = InvalidManagedHandle;

	if (const auto ScriptDomain = IScriptDomain::Get())
	{
		ManagedHandle = ScriptDomain->NewWeakRef(InManagedHandle, bTrackResurrection);
	}

	void* InParams[] = {&ManagedHandle};

	if (const auto FoundProperty = GetProperty(PROPERTY_GARBAGE_COLLECTION_HANDLE))
	{
		FoundProperty->SetValue(InManagedHandle, InParams);
	}

	return ManagedHandle;
}

IManagedHandle FClassReflection::GetGCHandle(const IManagedObject InManagedObject) const
{
	if (const auto FoundProperty = GetProperty(PROPERTY_GARBAGE_COLLECTION_HANDLE))
	{
		if (const auto ScriptDomain = IScriptDomain::Get())
		{
			return *static_cast<IManagedHandle*>(ScriptDomain->UnboxValue(
				MANAGED_HANDLE_FROM_OBJECT(
					FoundProperty->GetValue(MANAGED_HANDLE_FROM_OBJECT(InManagedObject), nullptr))));
		}
	}

	return InvalidManagedHandle;
}

IManagedHandle FClassReflection::BoxValue(void* InValue) const
{
	if (const auto ScriptDomain = IScriptDomain::Get())
	{
#if WITH_MONO
		return ScriptDomain->BoxValue(ManagedClass, InValue);
#else
		return ScriptDomain->BoxValue(NameSpace, Name, InValue);
#endif
	}

	return InvalidManagedHandle;
}

IManagedArray FClassReflection::NewArray(const int32 InNum) const
{
	if (const auto ScriptDomain = IScriptDomain::Get())
	{
#if WITH_MONO
		return ScriptDomain->NewArray(ManagedClass, InNum);
#else
		return ScriptDomain->NewArray(NameSpace, Name, InNum);
#endif
	}

	return INVALID_MANAGED;
}

bool FClassReflection::IsAssignableFrom(const FClassReflection* InSuperClass, const bool bIncludeInterfaces) const
{
	for (auto Class = this; Class != nullptr; Class = Class->Parent)
	{
		if (Class == InSuperClass)
		{
			return true;
		}
	}

	if (bIncludeInterfaces)
	{
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
