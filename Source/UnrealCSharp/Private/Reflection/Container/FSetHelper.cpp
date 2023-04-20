#include "Reflection/Container/FSetHelper.h"

#include "AITypes.h"
#include "Reflection/Property/FPropertyDescriptor.h"

FSetHelper::FSetHelper(FProperty* InProperty, void* InData):
	ElementPropertyDescriptor(nullptr),
	ScriptSet(nullptr),
	bNeedFree(false)
{
	if (InData != nullptr)
	{
		bNeedFree = false;

		ScriptSet = static_cast<FScriptSet*>(InData);
	}
	else
	{
		bNeedFree = true;

		ScriptSet = new FScriptSet();
	}

	if (InProperty != nullptr)
	{
		ElementPropertyDescriptor = FPropertyDescriptor::Factory(InProperty);

		ScriptSetLayout = FScriptSet::GetScriptLayout(ElementPropertyDescriptor->GetSize(),
		                                              ElementPropertyDescriptor->GetMinAlignment());
	}
}

FSetHelper::~FSetHelper()
{
	Deinitialize();
}

void FSetHelper::Initialize()
{
}

void FSetHelper::Deinitialize()
{
	if (bNeedFree && ScriptSet != nullptr)
	{
		delete ScriptSet;

		ScriptSet = nullptr;
	}

	if (ElementPropertyDescriptor != nullptr)
	{
		if (bNeedFree)
		{
			ElementPropertyDescriptor->DestroyProperty();
		}

		delete ElementPropertyDescriptor;

		ElementPropertyDescriptor = nullptr;
	}
}

void FSetHelper::Empty(const int32 InExpectedNumElements) const
{
	ScriptSet->Empty(InExpectedNumElements, ScriptSetLayout);
}

int32 FSetHelper::Num() const
{
	return ScriptSet->Num();
}

int32 FSetHelper::GetMaxIndex() const
{
	return ScriptSet->GetMaxIndex();
}

void FSetHelper::Add(void* InValue) const
{
	auto ValueIndex = static_cast<int32>(INDEX_NONE);

	for (auto Index = 0; Index < ScriptSet->GetMaxIndex(); ++Index)
	{
		if (ScriptSet->IsValidIndex(Index))
		{
			const auto Data = static_cast<uint8*>(ScriptSet->GetData(Index, ScriptSetLayout));

			if (ElementPropertyDescriptor->Identical(Data, InValue))
			{
				ValueIndex = Index;

				break;
			}
		}
	}

	if (ValueIndex == INDEX_NONE)
	{
		ValueIndex = ScriptSet->AddUninitialized(ScriptSetLayout);

		const auto Data = static_cast<uint8*>(ScriptSet->GetData(ValueIndex, ScriptSetLayout));

		ElementPropertyDescriptor->Set(InValue, Data);

		ScriptSet->Rehash(ScriptSetLayout, [=](const void* Src)
		{
			return ElementPropertyDescriptor->GetValueTypeHash(Src);
		});
	}
}

int32 FSetHelper::Remove(const void* InValue) const
{
	auto ValueIndex = static_cast<int32>(INDEX_NONE);

	for (auto Index = 0; Index < ScriptSet->GetMaxIndex(); ++Index)
	{
		if (ScriptSet->IsValidIndex(Index))
		{
			const auto Data = static_cast<uint8*>(ScriptSet->GetData(Index, ScriptSetLayout));

			if (ElementPropertyDescriptor->Identical(Data, InValue))
			{
				ValueIndex = Index;

				break;
			}
		}
	}

	if (ValueIndex == INDEX_NONE)
	{
		return 0;
	}

	const auto Data = static_cast<uint8*>(ScriptSet->GetData(ValueIndex, ScriptSetLayout));

	ElementPropertyDescriptor->DestroyValue(Data);

	ScriptSet->RemoveAt(ValueIndex, ScriptSetLayout);

	return 1;
}

bool FSetHelper::Contains(const void* InValue) const
{
	for (auto Index = 0; Index < ScriptSet->GetMaxIndex(); ++Index)
	{
		if (ScriptSet->IsValidIndex(Index))
		{
			const auto Data = static_cast<uint8*>(ScriptSet->GetData(Index, ScriptSetLayout));

			if (ElementPropertyDescriptor->Identical(Data, InValue))
			{
				return true;
			}
		}
	}

	return false;
}

FPropertyDescriptor* FSetHelper::GetElementPropertyDescriptor() const
{
	return ElementPropertyDescriptor;
}

FScriptSet* FSetHelper::GetScriptSet() const
{
	return ScriptSet;
}

bool FSetHelper::IsValidIndex(const int32 InIndex) const
{
	return ScriptSet->IsValidIndex(InIndex);
}

void* FSetHelper::GetEnumerator(const int32 InIndex) const
{
	return ScriptSet->IsValidIndex(InIndex)
		       ? static_cast<uint8*>(ScriptSet->GetData(InIndex, ScriptSetLayout))
		       : nullptr;
}
