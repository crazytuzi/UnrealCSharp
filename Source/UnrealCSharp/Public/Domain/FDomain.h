#pragma once

#include "Tickable.h"
#include "Domain/FMonoDomain.h"

class UNREALCSHARP_API FDomain final : public FTickableGameObject
{
private:
	typedef void (*SynchronizationContextTickType)(float, MonoObject**);

public:
	explicit FDomain(const FMonoDomainInitializeParams& InParams);

	virtual ~FDomain() override;

public:
	void Initialize(const FMonoDomainInitializeParams& InParams);

	void Deinitialize();

public:
	virtual void Tick(float DeltaTime) override;

	virtual bool IsTickable() const override;

	virtual TStatId GetStatId() const override;

public:
	static void* Object_Unbox(MonoObject* InMonoObject);

	static MonoString* String_New(const char* InText);

	static char* String_To_UTF8(MonoString* InMonoString);

	static MonoObject* GCHandle_Get_Target_V2(MonoGCHandle InGCHandle);

	static void GCHandle_Free_V2(MonoGCHandle InGCHandle);

	static bool IsLoadSucceed();

	template <typename T>
	static auto Array_Get(MonoArray* InArray, const uint64 InIndex) -> T;

	template <typename T>
	static auto Array_Set(MonoArray* InArray, const uint64 InIndex, T InValue) -> void;

public:
	static FString GetTraceback();

private:
	void InitializeSynchronizationContext();

	void DeinitializeSynchronizationContext();

private:
	SynchronizationContextTickType SynchronizationContextTick;
};

#include "FDomain.inl"
