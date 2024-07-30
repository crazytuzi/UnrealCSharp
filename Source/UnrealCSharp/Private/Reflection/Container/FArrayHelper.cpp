#include "Reflection/Container/FArrayHelper.h"
#include "Reflection/Property/FPropertyDescriptor.h"

FArrayHelper::FArrayHelper(FProperty* InProperty, void* InData,
                           const bool InbNeedFreeData, const bool InbNeedFreeProperty):
	InnerPropertyDescriptor(nullptr),
	ScriptArray(nullptr),
	bNeedFreeData(InbNeedFreeData),
	bNeedFreeProperty(InbNeedFreeProperty)
{
	InnerPropertyDescriptor = FPropertyDescriptor::Factory(InProperty);

	if (InData != nullptr)
	{
		ScriptArray = static_cast<FScriptArray*>(InData);
	}
	else
	{
		ScriptArray = new FScriptArray();
	}
}

FArrayHelper::~FArrayHelper()
{
	Deinitialize();
}

void FArrayHelper::Initialize()
{
}

void FArrayHelper::Deinitialize()
{
	if (bNeedFreeData && ScriptArray != nullptr)
	{
		delete ScriptArray;

		ScriptArray = nullptr;
	}

	if (bNeedFreeProperty && InnerPropertyDescriptor != nullptr)
	{
		InnerPropertyDescriptor->DestroyProperty();

		delete InnerPropertyDescriptor;

		InnerPropertyDescriptor = nullptr;
	}
}

bool FArrayHelper::Identical(const FArrayHelper* InA, const FArrayHelper* InB)
{
	if (InA == nullptr || InB == nullptr)
	{
		return false;
	}

	if (InA->GetTypeSize() != InB->GetTypeSize())
	{
		return false;
	}

	if (InA->Num() != InB->Num())
	{
		return false;
	}

	auto ScriptArrayHelperA = InA->CreateHelperFormInnerProperty();

	auto ScriptArrayHelperB = InB->CreateHelperFormInnerProperty();

	const auto InnerPropertyDescriptor = InA->GetInnerPropertyDescriptor();

	for (auto Index = 0; Index < InA->Num(); ++Index)
	{
		const auto ItemA = ScriptArrayHelperA.GetRawPtr(Index);

		const auto ItemB = ScriptArrayHelperB.GetRawPtr(Index);

		if (!InnerPropertyDescriptor->GetProperty()->Identical(ItemA, ItemB))
		{
			return false;
		}
	}

	return true;
}

int32 FArrayHelper::GetTypeSize() const
{
	return InnerPropertyDescriptor->GetSize();
}

int32 FArrayHelper::GetSlack() const
{
	return ScriptArray->GetSlack();
}

bool FArrayHelper::IsValidIndex(const int32 InIndex) const
{
	const auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	return ScriptArrayHelper.IsValidIndex(InIndex);
}

int32 FArrayHelper::Num() const
{
	const auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	return ScriptArrayHelper.Num();
}

bool FArrayHelper::IsEmpty() const
{
	return Num() == 0;
}

int32 FArrayHelper::Max() const
{
	return GetSlack() + Num();
}

void* FArrayHelper::Get(const int32 Index) const
{
	if (auto ScriptArrayHelper = CreateHelperFormInnerProperty(); ScriptArrayHelper.IsValidIndex(Index))
	{
		return ScriptArrayHelper.GetRawPtr(Index);
	}

	return nullptr;
}

void FArrayHelper::Set(const int32 Index, void* InValue) const
{
	if (auto ScriptArrayHelper = CreateHelperFormInnerProperty(); ScriptArrayHelper.IsValidIndex(Index))
	{
		InnerPropertyDescriptor->Set(InValue, ScriptArrayHelper.GetRawPtr(Index));
	}
}

int32 FArrayHelper::Find(const void* InValue) const
{
	auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	for (auto Index = 0; Index < Num(); ++Index)
	{
		if (const auto Item = ScriptArrayHelper.GetRawPtr(Index);
			InnerPropertyDescriptor->Identical(Item, InValue))
		{
			return Index;
		}
	}

	return INDEX_NONE;
}

int32 FArrayHelper::FindLast(const void* InValue) const
{
	auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	for (auto Index = Num() - 1; Index >= 0; --Index)
	{
		if (const auto Item = ScriptArrayHelper.GetRawPtr(Index);
			InnerPropertyDescriptor->Identical(Item, InValue))
		{
			return Index;
		}
	}

	return INDEX_NONE;
}

bool FArrayHelper::Contains(const void* InValue) const
{
	auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	for (auto Index = 0; Index < Num(); ++Index)
	{
		if (const auto Item = ScriptArrayHelper.GetRawPtr(Index);
			InnerPropertyDescriptor->Identical(Item, InValue))
		{
			return true;
		}
	}

	return false;
}

int32 FArrayHelper::AddUninitialized(const int32 InCount) const
{
	auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	return ScriptArrayHelper.AddUninitializedValues(InCount);
}

void FArrayHelper::InsertZeroed(const int32 InIndex, const int32 InCount) const
{
	ScriptArray->InsertZeroed(InIndex, InCount, InnerPropertyDescriptor->GetSize(), __STDCPP_DEFAULT_NEW_ALIGNMENT__);
}

void FArrayHelper::InsertDefaulted(const int32 InIndex, const int32 InCount) const
{
	auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	ScriptArrayHelper.InsertValues(InIndex, InCount);
}

void FArrayHelper::RemoveAt(const int32 InIndex, const int32 InCount, const bool bAllowShrinking) const
{
	auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	auto Dest = ScriptArrayHelper.GetRawPtr(InIndex);

	if (!(InnerPropertyDescriptor->GetPropertyFlags() & (CPF_IsPlainOldData | CPF_NoDestructor)))
	{
		for (auto Index = 0; Index < InCount; ++Index, Dest += InnerPropertyDescriptor->GetElementSize())
		{
			InnerPropertyDescriptor->DestroyValue(Dest);
		}
	}

	ScriptArray->Remove(InIndex, InCount, InnerPropertyDescriptor->GetElementSize(), __STDCPP_DEFAULT_NEW_ALIGNMENT__);

	if (bAllowShrinking)
	{
		ScriptArray->Shrink(InnerPropertyDescriptor->GetSize(), __STDCPP_DEFAULT_NEW_ALIGNMENT__);
	}
}

void FArrayHelper::Reset(const int32 InNewSize) const
{
	auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	if (InNewSize <= ScriptArray->GetSlack() + ScriptArray->Num())
	{
		ScriptArrayHelper.RemoveValues(0, ScriptArray->Num());
	}
	else
	{
		ScriptArrayHelper.EmptyValues(InNewSize);
	}
}

void FArrayHelper::Empty(const int32 InSlack) const
{
	auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	ScriptArrayHelper.EmptyValues(InSlack);
}

void FArrayHelper::SetNum(const int32 InNewNum, const bool bAllowShrinking) const
{
	auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	ScriptArrayHelper.Resize(InNewNum);

	if (bAllowShrinking)
	{
		ScriptArray->Shrink(InnerPropertyDescriptor->GetSize(), __STDCPP_DEFAULT_NEW_ALIGNMENT__);
	}
}

int32 FArrayHelper::Add(void* InValue) const
{
	auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	const auto Index = ScriptArrayHelper.AddUninitializedValue();

	InnerPropertyDescriptor->Set(InValue, ScriptArrayHelper.GetRawPtr(Index));

	return Index;
}

int32 FArrayHelper::AddZeroed(const int32 InCount) const
{
	return ScriptArray->AddZeroed(InCount, InnerPropertyDescriptor->GetSize(), __STDCPP_DEFAULT_NEW_ALIGNMENT__);
}

int32 FArrayHelper::AddUnique(void* InValue) const
{
	const auto Index = Find(InValue);

	return Index != INDEX_NONE ? Index : Add(InValue);
}

int32 FArrayHelper::RemoveSingle(const void* InValue) const
{
	auto ScriptArrayHelper = CreateHelperFormInnerProperty();

	for (auto Index = 0; Index < Num(); ++Index)
	{
		if (const auto Item = ScriptArrayHelper.GetRawPtr(Index);
			InnerPropertyDescriptor->Identical(Item, InValue))
		{
			RemoveAt(Index, 1, true);

			return 1;
		}
	}

	return 0;
}

int32 FArrayHelper::Remove(const void* InValue) const
{
	auto RemovedNum = 0;

	TArray<int32> x;

	auto Index = Find(InValue);

	while (Index != INDEX_NONE)
	{
		++RemovedNum;

		RemoveAt(Index, 1, true);

		Index = Find(InValue);
	}

	return RemovedNum;
}

void FArrayHelper::SwapMemory(const int32 InFirstIndexToSwap, const int32 InSecondIndexToSwap) const
{
	ScriptArray->SwapMemory(InFirstIndexToSwap, InSecondIndexToSwap, InnerPropertyDescriptor->GetSize());
}

void FArrayHelper::Swap(const int32 InFirstIndexToSwap, const int32 InSecondIndexToSwap) const
{
	ScriptArray->SwapMemory(InFirstIndexToSwap, InSecondIndexToSwap, InnerPropertyDescriptor->GetSize());
}

FPropertyDescriptor* FArrayHelper::GetInnerPropertyDescriptor() const
{
	return InnerPropertyDescriptor;
}

FScriptArray* FArrayHelper::GetScriptArray() const
{
	return ScriptArray;
}
