#include "Reflection/Container/FSetHelper.h"
#include "Reflection/Property/FPropertyDescriptor.h"

FSetHelper::FSetHelper(FProperty* InProperty, void* InData,
                       const bool InbNeedFreeData, const bool InbNeedFreeProperty,
                       const FDataDeleter InDataDeleter) :
	ElementPropertyDescriptor(nullptr),
	ScriptSet(nullptr),
	ElementBuffer(nullptr),
	bNeedFreeData(InbNeedFreeData),
	bNeedFreeProperty(InbNeedFreeProperty),
	DataDeleter(InDataDeleter)
{
	if (InData != nullptr)
	{
		ScriptSet = static_cast<FScriptSet*>(InData);
	}
	else
	{
		ScriptSet = new FScriptSet();
	}

	if (InProperty != nullptr)
	{
		ElementPropertyDescriptor = FPropertyDescriptor::Factory(InProperty);

		const auto Size = ElementPropertyDescriptor->GetSize();

		const auto Alignment = ElementPropertyDescriptor->GetMinAlignment();

		ScriptSetLayout = FScriptSet::GetScriptLayout(Size, Alignment);

		if (Size > 0 && Alignment > 0)
		{
			ElementBuffer = FMemory::Malloc(Size, Alignment);

			FMemory::Memzero(ElementBuffer, Size);
		}
	}

	Initialize();
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
	if (bNeedFreeData && ScriptSet != nullptr)
	{
		if (DataDeleter != nullptr)
		{
			DataDeleter(ScriptSet);
		}
		else
		{
			if (ElementPropertyDescriptor != nullptr)
			{
				Empty(0);
			}

			delete ScriptSet;
		}

		ScriptSet = nullptr;
	}

	if (ElementBuffer != nullptr)
	{
		FMemory::Free(ElementBuffer);

		ElementBuffer = nullptr;
	}

	if (ElementPropertyDescriptor != nullptr)
	{
		if (bNeedFreeProperty)
		{
			ElementPropertyDescriptor->DestroyProperty();
		}

		delete ElementPropertyDescriptor;

		ElementPropertyDescriptor = nullptr;
	}
}

void FSetHelper::Empty(const int32 InExpectedNumElements) const
{
	if (InExpectedNumElements >= 0)
	{
		for (auto Index = 0; Index < ScriptSet->GetMaxIndex(); ++Index)
		{
			if (ScriptSet->IsValidIndex(Index))
			{
				const auto Data = static_cast<uint8*>(ScriptSet->GetData(Index, ScriptSetLayout));

				ElementPropertyDescriptor->DestroyValue(Data);
			}
		}

		ScriptSet->Empty(InExpectedNumElements, ScriptSetLayout);
	}
}

int32 FSetHelper::Num() const
{
	return ScriptSet->Num();
}

bool FSetHelper::IsEmpty() const
{
	return Num() == 0;
}

int32 FSetHelper::GetMaxIndex() const
{
	return ScriptSet->GetMaxIndex();
}

void FSetHelper::Add(void* InValue) const
{
	if (ElementPropertyDescriptor != nullptr && ElementBuffer != nullptr)
	{
		InitializeElementBuffer(InValue);

		ScriptSet->FindOrAdd(ElementBuffer, ScriptSetLayout,
		                     [this](const void* Src)
		                     {
			                     return GetElementHash(Src);
		                     },
		                     [this](const void* A, const void* B)
		                     {
			                     return IsIdenticalElement(A, B);
		                     },
		                     [this, InValue](void* Dest)
		                     {
			                     ElementPropertyDescriptor->Set(InValue, Dest);
		                     });

		DestroyElementBuffer();
	}
}

int32 FSetHelper::Remove(const void* InValue) const
{
	auto Result = 0;

	if (ElementPropertyDescriptor != nullptr && ElementBuffer != nullptr)
	{
		InitializeElementBuffer(InValue);

		if (const auto Index = FindElementIndex(ElementBuffer); Index != INDEX_NONE)
		{
			if (const auto Data = static_cast<uint8*>(ScriptSet->GetData(Index, ScriptSetLayout)))
			{
				ElementPropertyDescriptor->DestroyValue(Data);
			}

			ScriptSet->RemoveAt(Index, ScriptSetLayout);

			Result = 1;
		}

		DestroyElementBuffer();
	}

	return Result;
}

bool FSetHelper::Contains(const void* InValue) const
{
	auto Result = false;

	if (ElementPropertyDescriptor != nullptr && ElementBuffer != nullptr)
	{
		InitializeElementBuffer(InValue);

		Result = FindElementIndex(ElementBuffer) != INDEX_NONE;

		DestroyElementBuffer();
	}

	return Result;
}

FPropertyDescriptor* FSetHelper::GetElementPropertyDescriptor() const
{
	return ElementPropertyDescriptor;
}

FScriptSet* FSetHelper::GetScriptSet() const
{
	return ScriptSet;
}

void* FSetHelper::GetAddress() const
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

void FSetHelper::InitializeElementBuffer(const void* InValue) const
{
	const auto Size = ElementPropertyDescriptor->GetSize();

	FMemory::Memzero(ElementBuffer, Size);

	if (const auto Property = ElementPropertyDescriptor->GetProperty())
	{
		Property->InitializeValue(ElementBuffer);
	}

	ElementPropertyDescriptor->Set(const_cast<void*>(InValue), ElementBuffer);
}

void FSetHelper::DestroyElementBuffer() const
{
	ElementPropertyDescriptor->DestroyValue(ElementBuffer);
}

uint32 FSetHelper::GetElementHash(const void* InValue) const
{
	auto Result = 0u;

	if (const auto Property = ElementPropertyDescriptor->GetProperty())
	{
		Result = Property->GetValueTypeHash(InValue);
	}

	return Result;
}

bool FSetHelper::IsIdenticalElement(const void* A, const void* B) const
{
	auto Result = false;

	if (const auto Property = ElementPropertyDescriptor->GetProperty())
	{
		Result = Property->Identical(A, B, 0);
	}

	return Result;
}

int32 FSetHelper::FindElementIndex(const void* InValue) const
{
	return ScriptSet->FindIndex(InValue, ScriptSetLayout,
	                            [this](const void* Src)
	                            {
		                            return GetElementHash(Src);
	                            },
	                            [this](const void* A, const void* B)
	                            {
		                            return IsIdenticalElement(A, B);
	                            });
}
