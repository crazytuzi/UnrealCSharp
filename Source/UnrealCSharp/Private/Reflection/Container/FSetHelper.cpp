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

void* FSetHelper::Get(int32 Index) const 
{
	auto ScriptArrayHelper = CreateHelperFormElementProperty();

	if (ScriptArrayHelper.IsValidIndex(Index))
	{
		return ScriptArrayHelper.GetElementPtr(Index);
	}

	else
	{
		return  nullptr;
	}

}

void FSetHelper::Set(int32  Index,void* InValue) const 
{
	auto ScriptArrayHelper = CreateHelperFormElementProperty();

	if (ScriptArrayHelper.IsValidIndex(Index))
	{
		ElementPropertyDescriptor->Set(InValue, ScriptArrayHelper.GetElementPtr(Index));
	}
}

FPropertyDescriptor* FSetHelper::GetElementPropertyDescriptor() const
{
	return ElementPropertyDescriptor;
}

FProperty* FSetHelper::GetElementProperty() const
{
	return ElementPropertyDescriptor->GetProperty();
}

FScriptSet* FSetHelper::GetScriptSet() const
{
	return ScriptSet;
}
