#pragma once

#include "Tickable.h"
#include "Domain/Script/IManagedTypes.h"
#include "Domain/Script/IScriptDomain.h"

class UNREALCSHARP_API FDomain final : public FTickableGameObject
{
public:
	explicit FDomain();

	virtual ~FDomain() override;

public:
	void Initialize();

	void Deinitialize();

public:
	virtual void Tick(float DeltaTime) override;

	virtual bool IsTickable() const override;

	virtual TStatId GetStatId() const override;

public:
	static void* Object_Unbox(const IManagedHandle InManagedHandle);

	static IManagedHandle String_New(const char* InText);

	static FString StringToFString(const IManagedHandle InManagedHandle);

	static IManagedHandle GCHandle_Get_Target(const IManagedHandle InManagedHandle);

	static void GCHandle_Free(const IManagedHandle InManagedHandle);

	static bool IsLoadSucceed();

	template <typename T>
	static auto Array_Get(const IManagedArray InArray, const uint64 InIndex) -> T;

	template <typename T>
	static auto Array_Set(const IManagedArray InArray, const uint64 InIndex, T InValue) -> void;

public:
	static FString GetTraceback();

private:
	void InitializeSynchronizationContext();

	void DeinitializeSynchronizationContext();
};

#include "FDomain.inl"
