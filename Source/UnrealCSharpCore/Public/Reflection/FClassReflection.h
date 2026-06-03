#pragma once

#include "FReflection.h"
#include "FPropertyReflection.h"
#include "FFieldReflection.h"
#include "FMethodReflection.h"
#include "Domain/Script/IManagedTypes.h"

class UNREALCSHARPCORE_API FClassReflection : public FReflection
{
public:
	explicit FClassReflection(const IManagedClass InManagedClass, const FString& InName = {});

#if WITH_MONO
	explicit FClassReflection(const IManagedReflectionType InManagedReflectionType);
#endif

	~FClassReflection();

public:
	void Initialize();

	void Deinitialize();

public:
	IManagedClass GetManagedClass() const;

#if WITH_MONO
	IManagedReflectionType GetManagedReflectionType() const;
#endif

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

	FMethodReflection* GetMethod(const IManagedReflectionMethod InManagedReflectionMethod);

	FMethodReflection* GetParentMethod(const FString& InName, int32 InParamCount) const;

public:
	IManagedHandle NewObject() const;

	IManagedHandle InitObject(int32 InParamCount = 0, void** InParams = nullptr) const;

	void ConstructorObject(const IManagedHandle InManagedHandle, int32 InParamCount = 0,
	                       void** InParams = nullptr) const;

	void ConstructorClass() const;

	IManagedHandle NewGCHandle(const IManagedHandle InManagedHandle, bool bPinned) const;

	IManagedHandle NewWeakRefGCHandle(const IManagedHandle InManagedHandle, bool bTrackResurrection) const;

	IManagedHandle GetGCHandle(const IManagedObject InManagedObject) const;

	IManagedHandle BoxValue(void* InValue) const;

	IManagedArray NewArray(int32 InNum) const;

	bool IsAssignableFrom(const FClassReflection* InSuperClass, bool bIncludeInterfaces = false) const;

private:
	IManagedClass ManagedClass{INVALID_MANAGED};

#if WITH_MONO
	IManagedReflectionType ManagedReflectionType{INVALID_MANAGED};
#endif

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
