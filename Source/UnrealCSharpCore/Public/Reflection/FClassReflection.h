#pragma once

#include "FReflection.h"
#include "FPropertyReflection.h"
#include "FFieldReflection.h"
#include "FMethodReflection.h"
#include "Domain/FMonoDomain.h"

class UNREALCSHARPCORE_API FClassReflection : public FReflection
{
public:
	explicit FClassReflection(MonoClass* InClass, const FString& InName = {});

	explicit FClassReflection(MonoReflectionType* InReflectionType);

	~FClassReflection();

public:
	void Initialize();

	void Deinitialize();

public:
	MonoClass* GetClass() const;

	MonoVTable* GetVTable() const;

	MonoReflectionType* GetReflectionType() const;

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

	FMethodReflection* GetMethod(const FString& InMethodName, int32 InParamCount) const;

	FMethodReflection* GetMethod(const MonoReflectionMethod* InReflectionMethod);

	FMethodReflection* GetParentMethod(const FString& InFunctionName, int32 InParamCount) const;

public:
	MonoObject* NewObject() const;

	MonoObject* InitObject(int32 InParamCount = 0, void** InParams = nullptr) const;

	void ConstructorObject(MonoObject* InMonoObject, int32 InParamCount = 0, void** InParams = nullptr) const;

	void ConstructorClass() const;

	MonoGCHandle NewGCHandle(MonoObject* InMonoObject, mono_bool bPinned) const;

	MonoGCHandle NewWeakRefGCHandle(MonoObject* InMonoObject, mono_bool bTrackResurrection) const;

	MonoObject* BoxValue(void* InValue) const;

	MonoArray* NewArray(uint32 InNum) const;

	bool IsAssignableFrom(const FClassReflection* InSuperClass, mono_bool bCheckInterfaces = false) const;

private:
	MonoClass* Class{};

	MonoVTable* VTable{};

	MonoReflectionType* ReflectionType{};

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
