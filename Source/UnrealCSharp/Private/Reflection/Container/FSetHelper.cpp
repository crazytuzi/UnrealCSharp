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
		if (auto ElementProperty = ElementPropertyDescriptor->GetProperty())
		{
			if (bNeedFree)
			{
				delete ElementProperty;

				ElementProperty = nullptr;
			}
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
		               // @TODO
		               return ElementPropertyDescriptor->GetProperty()->GetValueTypeHash(Element);
	               },
	               [this](const void* A, const void* B)
	               {
		               // @TODO
		               return ElementPropertyDescriptor->GetProperty()->Identical(A, B);
	               },
	               [this, InValue](void* NewElement)
	               {
		               // @TODO
		               ElementPropertyDescriptor->GetProperty()->InitializeValue_InContainer(NewElement);

		               ElementPropertyDescriptor->Set(InValue, NewElement);
	               },
	               [this](void* Element)
	               {
		               if (!ElementPropertyDescriptor->IsPrimitiveProperty())
		               {
			               // @TODO
			               ElementPropertyDescriptor->GetProperty()->DestroyValue(Element);
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
		                                        // @TODO
		                                        return ElementPropertyDescriptor->GetProperty()->GetValueTypeHash(
			                                        Element);
	                                        },
	                                        [this](const void* A, const void* B)
	                                        {
		                                        // @TODO
		                                        return ElementPropertyDescriptor->GetProperty()->Identical(A, B);
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

		// @TODO
		ElementPropertyDescriptor->GetProperty()->DestroyValue(Data);
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
		                            // @TODO
		                            return ElementPropertyDescriptor->GetProperty()->GetValueTypeHash(Element);
	                            },
	                            [this](const void* A, const void* B)
	                            {
		                            // @TODO
		                            return ElementPropertyDescriptor->GetProperty()->Identical(A, B);
	                            }
	) != INDEX_NONE;
}

bool FSetHelper::IsPrimitiveProperty() const
{
	return ElementPropertyDescriptor->IsPrimitiveProperty();
}

FProperty* FSetHelper::GetElementProperty() const
{
	return ElementPropertyDescriptor->GetProperty();
}

FScriptSet* FSetHelper::GetScriptSet() const
{
	return ScriptSet;
}
