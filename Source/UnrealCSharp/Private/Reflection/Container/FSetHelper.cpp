#include "Reflection/Container/FSetHelper.h"
#include "Reflection/Property/FPropertyDescriptor.h"

FSetHelper::FSetHelper(FProperty* InProperty, void* InData):
	ElementPropertyDescriptor(nullptr),
	ScriptSet(nullptr),
	bNeedFree(false)
{
	ElementPropertyDescriptor = FPropertyDescriptor::Factory(InProperty);

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
		ScriptSetLayout = FScriptSet::GetScriptLayout(InProperty->GetSize(), InProperty->GetMinAlignment());
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

void FSetHelper::Find(int32 SetIndex,void* InValue) const
{
	for (auto Index = 0; Index < ScriptSet->GetMaxIndex(); ++Index)
	{
		if (ScriptSet->IsValidIndex(SetIndex))
		{
			if(Index==SetIndex)
			{
				const auto Data = static_cast<uint8*>(ScriptSet->GetData(Index, ScriptSetLayout));
				InValue=Data;
			}
		}
	}
}

TArray<FProperty*> FSetHelper::ToArray() const
{
	TArray<FProperty*> Result;
	
	Result.Reserve(ScriptSet->Num());
	
	for (auto Index = 0; Index < ScriptSet->GetMaxIndex(); ++Index)
	{
		if (ScriptSet->IsValidIndex(Index))
		{
			const auto Data = static_cast<FProperty*>(ScriptSet->GetData(Index, ScriptSetLayout));
			Result.Add(Data);
		}
	}
	return Result;
}

TSet<void*> FSetHelper::Union(TSet<void*> OtherSet) const 
{
	TSet<void*> NewSet;

	NewSet.Reserve(ScriptSet->GetMaxIndex()+OtherSet.GetMaxIndex());
	
	for(int i=0;i<ScriptSet->GetMaxIndex();i++)
	{
		const auto Data = static_cast<uint8*>(ScriptSet->GetData(i, ScriptSetLayout));
		NewSet.Add(Data);
	}
	
	// for(int i=0;i<OtherSet.GetMaxIndex();i++)
	// {
	// 	NewSet.Add(OtherSet[i]);
	// }
	
	return NewSet;
}

void FSetHelper::Add(void* InValue) const
{

	ScriptSet->Add(InValue,
	               ScriptSetLayout,
	               [this](const void* Element)
	               {
		               return ElementPropertyDescriptor->GetValueTypeHash(Element);
	               },
	               [this](const void* A, const void* B)
	               {
		               return ElementPropertyDescriptor->Identical(A, B);
	               },
	               [this, InValue](void* NewElement)
	               {
		               ElementPropertyDescriptor->InitializeValue_InContainer(NewElement);

		               if (ElementPropertyDescriptor->IsPrimitiveProperty())
		               {
			               ElementPropertyDescriptor->Set(InValue, NewElement);
		               }
		               else
		               {
			               ElementPropertyDescriptor->Set(static_cast<void**>(InValue), NewElement);
		               }
	               },
	               [this](void* Element)
	               {
		               if (!ElementPropertyDescriptor->IsPrimitiveProperty())
		               {
			               ElementPropertyDescriptor->DestroyValue(Element);
		               }
	               }
	);
}

int32 FSetHelper::Remove(const void* InValue) const
{
	const auto Index = ScriptSet->FindIndex(InValue,
	                                        ScriptSetLayout,
	                                        [this](const void* Element)
	                                        {
		                                        return ElementPropertyDescriptor->GetValueTypeHash(Element);
	                                        },
	                                        [this](const void* A, const void* B)
	                                        {
		                                        return ElementPropertyDescriptor->Identical(A, B);
	                                        }
	);

	if (Index == INDEX_NONE)
	{
		return 0;
	}

	// @TODO
	if (!ElementPropertyDescriptor->IsPrimitiveProperty())
	{
		const auto Data = static_cast<uint8*>(ScriptSet->GetData(Index, ScriptSetLayout));

		ElementPropertyDescriptor->DestroyValue(Data);
	}

	ScriptSet->RemoveAt(Index, ScriptSetLayout);

	return 1;
}

bool FSetHelper::Contains(const void* InKey) const
{
	return ScriptSet->FindIndex(InKey,
	                            ScriptSetLayout,
	                            [this](const void* Element)
	                            {
		                            return ElementPropertyDescriptor->GetValueTypeHash(Element);
	                            },
	                            [this](const void* A, const void* B)
	                            {
		                            return ElementPropertyDescriptor->Identical(A, B);
	                            }
	) != INDEX_NONE;
}

FProperty* FSetHelper::GetElementProperty() const
{
	return ElementPropertyDescriptor->GetProperty();
}

FScriptSet* FSetHelper::GetScriptSet() const
{
	return ScriptSet;
}
