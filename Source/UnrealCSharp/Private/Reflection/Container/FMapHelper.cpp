#include "Reflection/Container/FMapHelper.h"

FMapHelper::FMapHelper(FProperty* InKeyProperty, FProperty* InValueProperty, void* InData):
	KeyPropertyDescriptor(nullptr),
	ValuePropertyDescriptor(nullptr),
	ScriptMap(nullptr),
	bNeedFree(false)
{
	if (InData != nullptr)
	{
		bNeedFree = false;

		ScriptMap = static_cast<FScriptMap*>(InData);
	}
	else
	{
		bNeedFree = true;

		ScriptMap = new FScriptMap();
	}

	if (InKeyProperty != nullptr && InValueProperty != nullptr)
	{
		KeyPropertyDescriptor = FPropertyDescriptor::Factory(InKeyProperty);

		ValuePropertyDescriptor = FPropertyDescriptor::Factory(InValueProperty);

		ScriptMapLayout = FScriptMap::GetScriptLayout(InKeyProperty->GetSize(), InKeyProperty->GetMinAlignment(),
		                                              InValueProperty->GetSize(), InValueProperty->GetMinAlignment());
	}
}

FMapHelper::~FMapHelper()
{
	Deinitialize();
}

void FMapHelper::Initialize()
{
}

void FMapHelper::Deinitialize()
{
	if (bNeedFree && ScriptMap != nullptr)
	{
		delete ScriptMap;

		ScriptMap = nullptr;
	}

	if (KeyPropertyDescriptor != nullptr)
	{
		if (auto KeyProperty = KeyPropertyDescriptor->GetProperty())
		{
			if (bNeedFree)
			{
				delete KeyProperty;

				KeyProperty = nullptr;
			}
		}

		delete KeyPropertyDescriptor;

		KeyPropertyDescriptor = nullptr;
	}

	if (ValuePropertyDescriptor != nullptr)
	{
		if (auto ValueProperty = ValuePropertyDescriptor->GetProperty())
		{
			if (bNeedFree)
			{
				delete ValueProperty;

				ValueProperty = nullptr;
			}
		}

		delete ValuePropertyDescriptor;

		ValuePropertyDescriptor = nullptr;
	}
}

void FMapHelper::Empty(const int32 InExpectedNumElements) const
{
	ScriptMap->Empty(InExpectedNumElements, ScriptMapLayout);
}

int32 FMapHelper::Num() const
{
	return ScriptMap->Num();
}

void FMapHelper::Add(void* InKey, void* InValue) const
{
	Set(InKey, InValue);
}

int32 FMapHelper::Remove(const void* InKey) const
{
	auto Count = 0;

	do
	{
		const auto Index = ScriptMap->FindPairIndex(InKey,
		                                            ScriptMapLayout,
		                                            [this](const void* ElementKey)
		                                            {
			                                            return KeyPropertyDescriptor->GetProperty()->GetValueTypeHash(
				                                            ElementKey);
		                                            },
		                                            [this](const void* A, const void* B)
		                                            {
			                                            return KeyPropertyDescriptor->GetProperty()->Identical(A, B);
		                                            }
		);

		if (Index == INDEX_NONE)
		{
			break;
		}

		++Count;

		const auto Data = static_cast<uint8*>(ScriptMap->GetData(Index, ScriptMapLayout));

		if (!KeyPropertyDescriptor->IsPrimitiveProperty())
		{
			// @TODO
			KeyPropertyDescriptor->GetProperty()->DestroyValue(Data);
		}

		if (!ValuePropertyDescriptor->IsPrimitiveProperty())
		{
			// @TODO
			ValuePropertyDescriptor->GetProperty()->DestroyValue(Data + ScriptMapLayout.ValueOffset);
		}

		ScriptMap->RemoveAt(Index, ScriptMapLayout);
	}
	while (true);

	return Count;
}

void* FMapHelper::FindKey(const void* InValue) const
{
	for (auto Index = 0; Index < ScriptMap->GetMaxIndex(); ++Index)
	{
		if (ScriptMap->IsValidIndex(Index))
		{
			const auto Data = static_cast<uint8*>(ScriptMap->GetData(Index, ScriptMapLayout));

			if (ValuePropertyDescriptor->GetProperty()->Identical(Data + ScriptMapLayout.ValueOffset, InValue))
			{
				return Data;
			}
		}
	}

	return nullptr;
}

void* FMapHelper::Find(const void* InKey) const
{
	return Get(InKey);
}

bool FMapHelper::Contains(const void* InKey) const
{
	return Get(InKey) != nullptr;
}

void* FMapHelper::Get(const void* InKey) const
{
	return ScriptMap->FindValue(InKey,
	                            ScriptMapLayout,
	                            [this](const void* ElementKey)
	                            {
		                            // @TODO
		                            return KeyPropertyDescriptor->GetProperty()->GetValueTypeHash(ElementKey);
	                            },
	                            [this](const void* A, const void* B)
	                            {
		                            // @TODO
		                            return KeyPropertyDescriptor->GetProperty()->Identical(A, B);
	                            });
}

void FMapHelper::Set(void* InKey, void* InValue) const
{
	ScriptMap->Add(
		InKey,
		InValue,
		ScriptMapLayout,
		[this](const void* ElementKey)
		{
			// @TODO
			return KeyPropertyDescriptor->GetProperty()->GetValueTypeHash(ElementKey);
		},
		[this](const void* A, const void* B)
		{
			// @TODO
			return KeyPropertyDescriptor->GetProperty()->Identical(A, B);
		},
		[this, InKey](void* NewElementKey)
		{
			// @TODO
			KeyPropertyDescriptor->GetProperty()->InitializeValue_InContainer(NewElementKey);

			KeyPropertyDescriptor->Set(InKey, NewElementKey);
		},
		[this, InValue](void* NewElementValue)
		{
			// @TODO
			ValuePropertyDescriptor->GetProperty()->InitializeValue_InContainer(NewElementValue);

			ValuePropertyDescriptor->Set(InValue, NewElementValue);
		},
		[this, InValue](void* ExistingElementValue)
		{
			ValuePropertyDescriptor->Set(InValue, ExistingElementValue);
		},
		[this](void* ElementKey)
		{
			// @TODO
			if (!KeyPropertyDescriptor->IsPrimitiveProperty())
			{
				// @TODO
				KeyPropertyDescriptor->GetProperty()->DestroyValue(ElementKey);
			}
		},
		[this](void* ElementValue)
		{
			// @TODO
			if (!ValuePropertyDescriptor->IsPrimitiveProperty())
			{
				// @TODO
				ValuePropertyDescriptor->GetProperty()->DestroyValue(ElementValue);
			}
		}
	);
}

bool FMapHelper::IsKeyPrimitiveProperty() const
{
	return KeyPropertyDescriptor->IsPrimitiveProperty();
}

bool FMapHelper::IsValuePrimitiveProperty() const
{
	return ValuePropertyDescriptor->IsPrimitiveProperty();
}

FProperty* FMapHelper::GetKeyProperty() const
{
	return KeyPropertyDescriptor->GetProperty();
}

FProperty* FMapHelper::GetValueProperty() const
{
	return ValuePropertyDescriptor->GetProperty();
}

FScriptMap* FMapHelper::GetScriptMap() const
{
	return ScriptMap;
}
