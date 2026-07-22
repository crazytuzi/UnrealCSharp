#pragma once

#include "FReflection.h"
#include "FPropertyReflection.h"
#include "FFieldReflection.h"
#include "FMethodReflection.h"
#include "Domain/Script/IManagedHandle.h"

class IScriptDomain;

struct FManagedReader;

class UNREALCSHARPCORE_API FClassReflection : public FReflection
{
public:
	explicit FClassReflection(const IManagedHandle InManagedClass, const FString& InName = {});

	~FClassReflection();

public:
	void Deinitialize();

public:
	bool HasAttribute(const FClassReflection* InAttribute) const;

	FString GetAttributeValue(const FClassReflection* InAttribute, int32 InIndex = 0) const;

public:
	IManagedHandle GetManagedClass() const;

	FClassReflection* GetTypeDefinition() const;

	const FString& GetNameSpace() const;

	const FString& GetPathName() const;

	bool IsClass() const;

	bool IsEnum() const;

	bool IsOverride();

	FClassReflection* GetParent() const;

	FClassReflection* GetUnderlyingType() const;

	const TArray<FClassReflection*>& GetGenericArguments() const;

	FClassReflection* GetGenericArgument(int InIndex = 0) const;

	const TArray<FClassReflection*>& GetInterfaces() const;

	const TMap<FString, FPropertyReflection*>& GetProperties() const;

	FPropertyReflection* GetProperty(const FString& InName) const;

	const TMap<FString, FFieldReflection*>& GetFields() const;

	FFieldReflection* GetField(const FString& InName) const;

	const TMap<TPair<FString, int32>, FMethodReflection*>& GetMethods() const;

	FMethodReflection* GetMethod(const FString& InName, int32 InParamCount) const;

	FMethodReflection* GetMethod(const IManagedHandle InManagedMethod);

	FMethodReflection* GetParentMethod(const FString& InName, int32 InParamCount) const;

public:
	IManagedHandle NewObject() const;

	IManagedHandle InitObject(int32 InParamCount = 0, void** InParams = nullptr) const;

	void ConstructorObject(const IManagedHandle InManagedHandle, int32 InParamCount = 0,
	                       void** InParams = nullptr) const;

	void ConstructorClass() const;

	IManagedHandle BoxValue(void* InValue) const;

	IManagedHandle NewArray(int32 InNum) const;

	bool IsAssignableFrom(const FClassReflection* InSuperClass, bool bIncludeInterfaces = false) const;

private:
	FORCEINLINE void EnsureDescriptor() const
	{
		if (!bDescriptorLoaded)
		{
			const_cast<FClassReflection*>(this)->EnsureDescriptorImplementation();
		}
	}

	FORCEINLINE void EnsureProperties() const
	{
		if (!bPropertiesLoaded)
		{
			const_cast<FClassReflection*>(this)->EnsurePropertiesImplementation();
		}
	}

	FORCEINLINE void EnsureFields() const
	{
		if (!bFieldsLoaded)
		{
			const_cast<FClassReflection*>(this)->EnsureFieldsImplementation();
		}
	}

	FORCEINLINE void EnsureMethods() const
	{
		if (!bMethodsLoaded)
		{
			const_cast<FClassReflection*>(this)->EnsureMethodsImplementation();
		}
	}

	void EnsureDescriptorImplementation();

	void EnsurePropertiesImplementation();

	void EnsureFieldsImplementation();

	void EnsureMethodsImplementation();

	void EnsureMemberImplementation(
		bool& bLoaded, int32 InSlotCount,
		void (IScriptDomain::*GetMemberFunction)(const IManagedHandle, PTRINT*),
		void (FClassReflection::*ParseMemberFunction)(const FManagedReader&, IManagedHandle*));

	void ParseDescriptor(const FManagedReader& InManagedReader, IManagedHandle* InParams);

	void ParseProperties(const FManagedReader& InManagedReader, IManagedHandle* InParams);

	void ParseFields(const FManagedReader& InManagedReader, IManagedHandle* InParams);

	void ParseMethods(const FManagedReader& InManagedReader, IManagedHandle* InParams);

private:
	IManagedHandle ManagedClass{InvalidManagedHandle};

	bool bOverrideLoaded{};

	bool bDescriptorLoaded{};

	bool bPropertiesLoaded{};

	bool bFieldsLoaded{};

	bool bMethodsLoaded{};

	bool bInitializing{};

	bool bIsOverride{};

	FClassReflection* TypeDefinition{};

	FString NameSpace;

	FString PathName;

	FClassReflection* Parent{};

	FClassReflection* UnderlyingType{};

	bool bIsClass{};

	bool bIsEnum{};

	TArray<FClassReflection*> GenericArguments;

	TArray<FClassReflection*> Interfaces;

	TMap<FString, FPropertyReflection*> Properties;

	TMap<FString, FFieldReflection*> Fields;

	TMap<TPair<FString, int32>, FMethodReflection*> Methods;
};
