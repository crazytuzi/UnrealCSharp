#pragma once

#include "FFunctionDescriptor.h"
#include "CoreMacro/MonoMacro.h"
#include "Domain/FMonoDomain.h"
#include "Environment/FCSharpEnvironment.h"
#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object.h"

class FUnrealFunctionDescriptor final : public FFunctionDescriptor
{
public:
	typedef FFunctionDescriptor Super;

public:
	explicit FUnrealFunctionDescriptor(UFunction* InFunction);

public:
	MonoObject* ProcessEvent(UObject* InObject, MonoObject** OutValue, MonoArray* InValue) const;

	MonoObject* Invoke(UObject* InObject, MonoObject** OutValue, MonoArray* InValue) const;

private:
	FORCEINLINE void SlowProcessIn(MonoArray* InValue, void* Params) const
	{
		auto ParamIndex = 0;

		for (auto Index = 0; Index < PropertyDescriptors.Num(); ++Index)
		{
			const auto& PropertyDescriptor = PropertyDescriptors[Index];

			PropertyDescriptor->InitializeValue_InContainer(Params);

			if (ReferencePropertyIndexes.Contains(Index) || !OutPropertyIndexes.Contains(Index))
			{
				if (PropertyDescriptor->IsPrimitiveProperty())
				{
					if (const auto UnBoxValue = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(
						ARRAY_GET(InValue, MonoObject*, ParamIndex++)))
					{
						PropertyDescriptor->Set(UnBoxValue, PropertyDescriptor->ContainerPtrToValuePtr<void>(Params));
					}
				}
				else
				{
					PropertyDescriptor->Set(
						*static_cast<FGarbageCollectionHandle*>(
							FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(
								ARRAY_GET(InValue, MonoObject*, ParamIndex++))),
						PropertyDescriptor->ContainerPtrToValuePtr<void>(Params));
				}
			}
		}
	}

	FORCEINLINE void FastProcessIn(MonoArray* InValue, FOutParmRec** LastOut, void* Params) const
	{
		auto ParamIndex = 0;

		for (auto Index = 0; Index < PropertyDescriptors.Num(); ++Index)
		{
			const auto& PropertyDescriptor = PropertyDescriptors[Index];

			PropertyDescriptor->InitializeValue_InContainer(Params);

			if (ReferencePropertyIndexes.Contains(Index) || !OutPropertyIndexes.Contains(Index))
			{
				if (PropertyDescriptor->IsPrimitiveProperty())
				{
					if (const auto UnBoxValue = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(
						ARRAY_GET(InValue, MonoObject*, ParamIndex++)))
					{
						PropertyDescriptor->Set(UnBoxValue, PropertyDescriptor->ContainerPtrToValuePtr<void>(Params));
					}
				}
				else
				{
					PropertyDescriptor->Set(
						*static_cast<FGarbageCollectionHandle*>(
							FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(
								ARRAY_GET(InValue, MonoObject*, ParamIndex++))),
						PropertyDescriptor->ContainerPtrToValuePtr<void>(Params));
				}

				CA_SUPPRESS(6263)

				const auto Out = (FOutParmRec*)FMemory_Alloca(sizeof(FOutParmRec));

				Out->Property = PropertyDescriptor->GetProperty();

				Out->PropAddr = (uint8*)PropertyDescriptor->ContainerPtrToValuePtr<void>(Params);

				if (*LastOut)
				{
					(*LastOut)->NextOutParm = Out;

					LastOut = &(*LastOut)->NextOutParm;
				}
				else
				{
					*LastOut = Out;
				}
			}
		}
	}

	FORCEINLINE void ProcessOut(MonoObject** OutValue, void* Params) const
	{
		if (!OutPropertyIndexes.IsEmpty())
		{
			const auto MonoObjectArray = FMonoDomain::Array_New(FMonoDomain::Get_Object_Class(),
			                                                    OutPropertyIndexes.Num());

			for (auto Index = 0; Index < OutPropertyIndexes.Num(); ++Index)
			{
				if (const auto OutPropertyDescriptor = PropertyDescriptors[OutPropertyIndexes[Index]])
				{
					MonoObject* Value = nullptr;

					OutPropertyDescriptor->Get(OutPropertyDescriptor->ContainerPtrToValuePtr<void>(Params),
					                           reinterpret_cast<void**>(&Value));

					ARRAY_SET(MonoObjectArray, MonoObject*, Index, Value);
				}
			}

			*OutValue = (MonoObject*)MonoObjectArray;
		}
	}

	FORCEINLINE MonoObject* ProcessReturn(void* Params) const
	{
		MonoObject* ReturnValue{};

		if (ReturnPropertyDescriptor != nullptr)
		{
			ReturnPropertyDescriptor->Get(ReturnPropertyDescriptor->ContainerPtrToValuePtr<void>(Params),
			                              reinterpret_cast<void**>(&ReturnValue));
		}

		if (Params != nullptr)
		{
			BufferAllocator->Free(Params);
		}

		return ReturnValue;
	}
};
