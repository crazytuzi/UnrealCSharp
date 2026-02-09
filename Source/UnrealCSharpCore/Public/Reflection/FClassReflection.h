#pragma once

#include "FReflection.h"
#include "FFieldReflection.h"
#include "FPropertyReflection.h"
#include "FMethodReflection.h"

class UNREALCSHARPCORE_API FClassReflection : public FReflection
{
public:
	FClassReflection(const TWeakObjectPtr<UStruct>& InStruct, MonoClass* InClass);
	
	FClassReflection(const TWeakObjectPtr<UField>& InStruct, MonoClass* InClass);

	FClassReflection(MonoClass* InClass);
	
	FClassReflection(const FString& InName, MonoClass* InClass);

public:
	void Initialize();

	void Deinitialize();

public:
	bool IsOverride() const;

	MonoClass* GetClass() const;

	MonoVTable* GetVTable() const;

	MonoReflectionType* GetReflectionType() const;

	const TMap<FString, FPropertyReflection*>& GetProperties() const;

	const TMap<FString, FFieldReflection*>& GetFields() const;

	const TMap<TPair<FString, int32>, FMethodReflection*>& GetMethods() const;

	FPropertyReflection* GetPropertyReflection(const FString& InName) const;

	void Property_Set_Value(const FString& InName, void* InMonoObject, void** InParams, MonoObject** InExc) const;

	FFieldReflection* Class_Get_Field_From_Name(const FString& InName) const;

	void Field_Static_Set_Value(const FString& InName, void* InValue) const;

	FMethodReflection* Get_Method_From_Name(const FString& InFunctionName, const int32 InParamCount);

public:
	static MonoClass* GetMonoClass(const TWeakObjectPtr<UField>& InStruct);

public:
	bool bIsOverride{};

	FClassReflection* Parent{};

	MonoClass* Class{};

	MonoVTable* VTable{};

	MonoType* Type{};

	MonoReflectionType* ReflectionType{};

	TMap<FString, FPropertyReflection*> Properties;

	TMap<FString, FFieldReflection*> Fields;

	TMap<TPair<FString, int32>, FMethodReflection*> Methods;
};
