#pragma once

class FUObjectListener final : FUObjectArray::FUObjectCreateListener, FUObjectArray::FUObjectDeleteListener
{
public:
	FUObjectListener();

	virtual ~FUObjectListener() override;

private:
	void AddListeners();

	void RemoveListeners();

	void OnUnrealCSharpModuleActive();

	void OnUnrealCSharpModuleInActive();

private:
	virtual void NotifyUObjectCreated(const class UObjectBase* Object, int32 Index) override;

	virtual void NotifyUObjectDeleted(const class UObjectBase* Object, int32 Index) override;

	virtual void OnUObjectArrayShutdown() override;

private:
	FDelegateHandle OnUnrealCSharpModuleActiveDelegateHandle;

	FDelegateHandle OnUnrealCSharpModuleInActiveDelegateHandle;

	bool bIsRegistered{};
};
