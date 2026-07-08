#pragma once

#include "FReflection.h"
#include "FPropertyReflection.h"
#include "FFieldReflection.h"
#include "FMethodReflection.h"
#include "Domain/Script/IManagedHandle.h"

class UNREALCSHARPCORE_API FClassReflection : public FReflection
{
public:
	explicit FClassReflection(const IManagedHandle InManagedClass, const FString& InName = {});

	~FClassReflection();

public:
	void Initialize();

	void Deinitialize();

public:
	IManagedHandle GetManagedClass() const;

	FClassReflection* GetTypeDefinition() const;

	const FString& GetNameSpace() const;

	const FString& GetPathName() const;

	bool IsClass() const;

	bool IsEnum() const;

	bool IsOverride() const;

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
	IManagedHandle ManagedClass{InvalidManagedHandle};

	FClassReflection* TypeDefinition{};

	FString NameSpace;

	FString PathName;

	FClassReflection* Parent{};

	FClassReflection* UnderlyingType{};

	bool bIsClass{};

	bool bIsEnum{};

	bool bIsOverride{};

	TArray<FClassReflection*> GenericArguments;

	TArray<FClassReflection*> Interfaces;

	TMap<FString, FPropertyReflection*> Properties;

	TMap<FString, FFieldReflection*> Fields;

	TMap<TPair<FString, int32>, FMethodReflection*> Methods;
};
