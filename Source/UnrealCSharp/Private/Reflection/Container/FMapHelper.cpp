#include "Reflection/Container/FMapHelper.h"
#include "CppVersion.h"

FMapHelper::FMapHelper(FProperty* InKeyProperty, FProperty* InValueProperty, void* InData,
                       const bool InbNeedFreeData, const bool InbNeedFreeProperty):
	KeyPropertyDescriptor(nullptr),
	ValuePropertyDescriptor(nullptr),
	ScriptMap(nullptr),
	bNeedFreeData(InbNeedFreeData),
	bNeedFreeProperty(InbNeedFreeProperty)
{
	if (InData != nullptr)
	{
		ScriptMap = static_cast<FScriptMap*>(InData);
	}
	else
	{
		ScriptMap = new FScriptMap();
	}

	if (InKeyProperty != nullptr && InValueProperty != nullptr)
	{
		KeyPropertyDescriptor = FPropertyDescriptor::Factory(InKeyProperty);

		ValuePropertyDescriptor = FPropertyDescriptor::Factory(InValueProperty);

		ScriptMapLayout = FScriptMap::GetScriptLayout(KeyPropertyDescriptor->GetSize(),
		                                              KeyPropertyDescriptor->GetMinAlignment(),
		                                              ValuePropertyDescriptor->GetSize(),
		                                              ValuePropertyDescriptor->GetMinAlignment());
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
	if (bNeedFreeData && ScriptMap != nullptr)
	{
		delete ScriptMap;

		ScriptMap = nullptr;
	}

	if (bNeedFreeProperty && KeyPropertyDescriptor != nullptr && ValuePropertyDescriptor != nullptr)
	{
		KeyPropertyDescriptor->DestroyProperty();

		delete KeyPropertyDescriptor;

		KeyPropertyDescriptor = nullptr;

		ValuePropertyDescriptor->DestroyProperty();

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

bool FMapHelper::IsEmpty() const
{
	return Num() == 0;
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
		auto KeyIndex = static_cast<int32>(INDEX_NONE);

		for (auto Index = 0; Index < ScriptMap->GetMaxIndex(); ++Index)
		{
			if (ScriptMap->IsValidIndex(Index))
			{
				if (const auto Data = static_cast<uint8*>(ScriptMap->GetData(Index, ScriptMapLayout));
					KeyPropertyDescriptor->Identical(Data, InKey))
				{
					KeyIndex = Index;

					break;
				}
			}
		}

		if (KeyIndex == INDEX_NONE)
		{
			break;
		}

		++Count;

		const auto Data = static_cast<uint8*>(ScriptMap->GetData(KeyIndex, ScriptMapLayout));

		KeyPropertyDescriptor->DestroyValue(Data);

		ValuePropertyDescriptor->DestroyValue(Data + ScriptMapLayout.ValueOffset);

		ScriptMap->RemoveAt(KeyIndex, ScriptMapLayout);
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
			if (const auto Data = static_cast<uint8*>(ScriptMap->GetData(Index, ScriptMapLayout));
				ValuePropertyDescriptor->Identical(Data + ScriptMapLayout.ValueOffset, InValue))
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
	for (auto Index = 0; Index < ScriptMap->GetMaxIndex(); ++Index)
	{
		if (ScriptMap->IsValidIndex(Index))
		{
			if (const auto Data = static_cast<uint8*>(ScriptMap->GetData(Index, ScriptMapLayout));
				KeyPropertyDescriptor->Identical(Data, InKey))
			{
				return Data + ScriptMapLayout.ValueOffset;
			}
		}
	}

	return nullptr;
}

void FMapHelper::Set(void* InKey, void* InValue) const
{
	auto KeyIndex = static_cast<int32>(INDEX_NONE);

	for (auto Index = 0; Index < ScriptMap->GetMaxIndex(); ++Index)
	{
		if (ScriptMap->IsValidIndex(Index))
		{
			if (const auto Data = static_cast<uint8*>(ScriptMap->GetData(Index, ScriptMapLayout));
				KeyPropertyDescriptor->Identical(Data, InKey))
			{
				KeyIndex = Index;

				break;
			}
		}
	}

	uint8* Data;

	if (KeyIndex == INDEX_NONE)
	{
		KeyIndex = ScriptMap->AddUninitialized(ScriptMapLayout);

		Data = static_cast<uint8*>(ScriptMap->GetData(KeyIndex, ScriptMapLayout));

		KeyPropertyDescriptor->Set(InKey, Data);

#if STD_CPP_20
		ScriptMap->Rehash(ScriptMapLayout, [=, this](const void* Src)
#else
		ScriptMap->Rehash(ScriptMapLayout, [=](const void* Src)
#endif
		                  {
			                  return KeyPropertyDescriptor->GetValueTypeHash(Src);
		                  });
	}
	else
	{
		Data = static_cast<uint8*>(ScriptMap->GetData(KeyIndex, ScriptMapLayout));

		ValuePropertyDescriptor->DestroyValue(Data + ScriptMapLayout.ValueOffset);
	}

	ValuePropertyDescriptor->Set(InValue, Data + ScriptMapLayout.ValueOffset);
}

FPropertyDescriptor* FMapHelper::GetKeyPropertyDescriptor() const
{
	return KeyPropertyDescriptor;
}

FPropertyDescriptor* FMapHelper::GetValuePropertyDescriptor() const
{
	return ValuePropertyDescriptor;
}

FScriptMap* FMapHelper::GetScriptMap() const
{
	return ScriptMap;
}

int32 FMapHelper::GetMaxIndex() const
{
	return ScriptMap->GetMaxIndex();
}

bool FMapHelper::IsValidIndex(const int32 InIndex) const
{
	return ScriptMap->IsValidIndex(InIndex);
}

void* FMapHelper::GetEnumeratorKey(const int32 InIndex) const
{
	return ScriptMap->IsValidIndex(InIndex)
		       ? static_cast<uint8*>(ScriptMap->GetData(InIndex, ScriptMapLayout))
		       : nullptr;
}

void* FMapHelper::GetEnumeratorValue(const int32 InIndex) const
{
	return ScriptMap->IsValidIndex(InIndex)
		       ? static_cast<uint8*>(ScriptMap->GetData(InIndex, ScriptMapLayout)) + ScriptMapLayout.ValueOffset
		       : nullptr;
}
