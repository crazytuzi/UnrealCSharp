#include "Reflection/Container/FMapHelper.h"

FMapHelper::FMapHelper(FProperty* InKeyProperty, FProperty* InValueProperty, void* InData,
                       const bool InbNeedFreeData, const bool InbNeedFreeProperty,
                       const FDataDeleter InDataDeleter) :
	KeyPropertyDescriptor(nullptr),
	ValuePropertyDescriptor(nullptr),
	ScriptMap(nullptr),
	ScriptMapLayout{},
	KeyBuffer(nullptr),
	bNeedFreeData(InbNeedFreeData),
	bNeedFreeProperty(InbNeedFreeProperty),
	DataDeleter(InDataDeleter)
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
	}

	if (KeyPropertyDescriptor != nullptr && ValuePropertyDescriptor != nullptr)
	{
		ScriptMapLayout = FScriptMap::GetScriptLayout(KeyPropertyDescriptor->GetSize(),
		                                              KeyPropertyDescriptor->GetMinAlignment(),
		                                              ValuePropertyDescriptor->GetSize(),
		                                              ValuePropertyDescriptor->GetMinAlignment());

		const auto Size = KeyPropertyDescriptor->GetSize();

		const auto Alignment = KeyPropertyDescriptor->GetMinAlignment();

		if (Size > 0 && Alignment > 0)
		{
			KeyBuffer = FMemory::Malloc(Size, Alignment);

			FMemory::Memzero(KeyBuffer, Size);
		}
	}

	Initialize();
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
		if (DataDeleter != nullptr)
		{
			DataDeleter(ScriptMap);
		}
		else
		{
			if (KeyPropertyDescriptor != nullptr && ValuePropertyDescriptor != nullptr)
			{
				Empty(0);
			}

			delete ScriptMap;
		}

		ScriptMap = nullptr;
	}

	if (KeyBuffer != nullptr)
	{
		FMemory::Free(KeyBuffer);

		KeyBuffer = nullptr;
	}

	if (KeyPropertyDescriptor != nullptr)
	{
		if (bNeedFreeProperty)
		{
			KeyPropertyDescriptor->DestroyProperty();
		}

		delete KeyPropertyDescriptor;

		KeyPropertyDescriptor = nullptr;
	}

	if (ValuePropertyDescriptor != nullptr)
	{
		if (bNeedFreeProperty)
		{
			ValuePropertyDescriptor->DestroyProperty();
		}

		delete ValuePropertyDescriptor;

		ValuePropertyDescriptor = nullptr;
	}
}

void FMapHelper::Empty(const int32 InExpectedNumElements) const
{
	if (InExpectedNumElements >= 0)
	{
		for (auto Index = 0; Index < ScriptMap->GetMaxIndex(); ++Index)
		{
			if (ScriptMap->IsValidIndex(Index))
			{
				const auto Data = static_cast<uint8*>(ScriptMap->GetData(Index, ScriptMapLayout));

				KeyPropertyDescriptor->DestroyValue(Data);

				ValuePropertyDescriptor->DestroyValue(Data + ScriptMapLayout.ValueOffset);
			}
		}

		ScriptMap->Empty(InExpectedNumElements, ScriptMapLayout);
	}
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

	if (KeyPropertyDescriptor != nullptr && ValuePropertyDescriptor != nullptr && KeyBuffer != nullptr)
	{
		InitializeKeyBuffer(InKey);

		do
		{
			if (const auto Index = FindPairIndex(KeyBuffer); Index != INDEX_NONE)
			{
				++Count;

				if (const auto Data = static_cast<uint8*>(ScriptMap->GetData(Index, ScriptMapLayout)))
				{
					KeyPropertyDescriptor->DestroyValue(Data);

					ValuePropertyDescriptor->DestroyValue(Data + ScriptMapLayout.ValueOffset);
				}

				ScriptMap->RemoveAt(Index, ScriptMapLayout);
			}
			else
			{
				break;
			}
		}
		while (true);

		DestroyKeyBuffer();
	}

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
	auto Result = static_cast<void*>(nullptr);

	if (KeyPropertyDescriptor != nullptr && ValuePropertyDescriptor != nullptr && KeyBuffer != nullptr)
	{
		InitializeKeyBuffer(InKey);

		if (const auto Index = FindPairIndex(KeyBuffer); Index != INDEX_NONE)
		{
			if (const auto Data = static_cast<uint8*>(ScriptMap->GetData(Index, ScriptMapLayout)))
			{
				Result = Data + ScriptMapLayout.ValueOffset;
			}
		}

		DestroyKeyBuffer();
	}

	return Result;
}

void FMapHelper::Set(void* InKey, void* InValue) const
{
	if (KeyPropertyDescriptor != nullptr && ValuePropertyDescriptor != nullptr && KeyBuffer != nullptr)
	{
		InitializeKeyBuffer(InKey);

		if (const auto Index = FindPairIndex(KeyBuffer); Index != INDEX_NONE)
		{
			if (const auto Data = static_cast<uint8*>(ScriptMap->GetData(Index, ScriptMapLayout)))
			{
				ValuePropertyDescriptor->DestroyValue(Data + ScriptMapLayout.ValueOffset);

				ValuePropertyDescriptor->Set(InValue, Data + ScriptMapLayout.ValueOffset);
			}
		}
		else
		{
			ScriptMap->FindOrAdd(KeyBuffer, ScriptMapLayout,
			                     [this](const void* Src)
			                     {
				                     return GetKeyHash(Src);
			                     },
			                     [this](const void* A, const void* B)
			                     {
				                     return IsIdenticalKey(A, B);
			                     },
			                     [this, InKey, InValue](void* NewKey, void* NewValue)
			                     {
				                     KeyPropertyDescriptor->Set(InKey, NewKey);

				                     ValuePropertyDescriptor->Set(InValue, NewValue);
			                     });
		}

		DestroyKeyBuffer();
	}
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

void* FMapHelper::GetAddress() const
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

void FMapHelper::InitializeKeyBuffer(const void* InKey) const
{
	const auto Size = KeyPropertyDescriptor->GetSize();

	FMemory::Memzero(KeyBuffer, Size);

	if (const auto Property = KeyPropertyDescriptor->GetProperty())
	{
		Property->InitializeValue(KeyBuffer);
	}

	KeyPropertyDescriptor->Set(const_cast<void*>(InKey), KeyBuffer);
}

void FMapHelper::DestroyKeyBuffer() const
{
	KeyPropertyDescriptor->DestroyValue(KeyBuffer);
}

uint32 FMapHelper::GetKeyHash(const void* InKey) const
{
	auto Result = 0u;

	if (const auto Property = KeyPropertyDescriptor->GetProperty())
	{
		Result = Property->GetValueTypeHash(InKey);
	}

	return Result;
}

bool FMapHelper::IsIdenticalKey(const void* A, const void* B) const
{
	auto Result = false;

	if (const auto Property = KeyPropertyDescriptor->GetProperty())
	{
		Result = Property->Identical(A, B, 0);
	}

	return Result;
}

int32 FMapHelper::FindPairIndex(const void* InKey) const
{
	return ScriptMap->FindPairIndex(InKey, ScriptMapLayout,
	                                [this](const void* Src)
	                                {
		                                return GetKeyHash(Src);
	                                },
	                                [this](const void* A, const void* B)
	                                {
		                                return IsIdenticalKey(A, B);
	                                });
}
