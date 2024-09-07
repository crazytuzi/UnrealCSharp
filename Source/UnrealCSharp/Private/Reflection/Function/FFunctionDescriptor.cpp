#include "Reflection/Function/FFunctionDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

FFunctionDescriptor::FFunctionDescriptor(UFunction* InFunction,
                                         const TSharedPtr<FFunctionParamBufferAllocator>& InBufferAllocator):
	Function(InFunction),
	ReturnPropertyDescriptor(nullptr),
	BufferAllocator(InBufferAllocator)
{
	FFunctionDescriptor::Initialize();
}

FFunctionDescriptor::~FFunctionDescriptor()
{
	FFunctionDescriptor::Deinitialize();
}

void FFunctionDescriptor::Initialize()
{
	if (!Function.IsValid())
	{
		return;
	}

	const auto IsNativeClass = Function->GetOuter()->IsNative();

	PropertyDescriptors.Reserve(Function->ReturnValueOffset != MAX_uint16
		                            ? (Function->NumParms > 0
			                               ? Function->NumParms - 1
			                               : 0)
		                            : Function->NumParms);

	for (TFieldIterator<FProperty> It(Function.Get()); It && (It->PropertyFlags & CPF_Parm); ++It)
	{
		if (const auto Property = *It)
		{
			auto PropertyDescriptor = FPropertyDescriptor::Factory(Property);

			if (Property->HasAnyPropertyFlags(CPF_ReturnParm))
			{
				ReturnPropertyDescriptor = PropertyDescriptor;

				continue;
			}

			InBufferOffsets.Add(InBufferOffsets.IsEmpty()
				                    ? 0
				                    : InBufferOffsets.Last() +
				                    (PropertyDescriptors.Last()->IsPrimitiveProperty()
					                     ? PropertyDescriptors.Last()->GetElementSize()
					                     : sizeof(void*)));

			const auto Index = PropertyDescriptors.Add(PropertyDescriptor);

			if (Property->HasAnyPropertyFlags(CPF_OutParm) && !Property->HasAnyPropertyFlags(CPF_ConstParm))
			{
				if (IsNativeClass || Property->HasAnyPropertyFlags(CPF_ReferenceParm))
				{
					ReferencePropertyIndexes.Emplace(Index);
				}

				OutBufferOffsets.Add(OutBufferOffsets.IsEmpty()
					                     ? 0
					                     : OutBufferOffsets.Last() +
					                     (PropertyDescriptors[OutPropertyIndexes.Last()]->IsPrimitiveProperty()
						                      ? PropertyDescriptors[OutPropertyIndexes.Last()]->GetElementSize()
						                      : sizeof(void*)));

				OutPropertyIndexes.Emplace(Index);
			}
		}
	}
}

void FFunctionDescriptor::Deinitialize()
{
	for (auto& PropertyDescriptorPair : PropertyDescriptors)
	{
		delete PropertyDescriptorPair;

		PropertyDescriptorPair = nullptr;
	}

	PropertyDescriptors.Empty();

	if (ReturnPropertyDescriptor != nullptr)
	{
		delete ReturnPropertyDescriptor;

		ReturnPropertyDescriptor = nullptr;
	}

	OutPropertyIndexes.Empty();

	Function.Reset();
}

FString FFunctionDescriptor::GetName() const
{
	return Function.IsValid() ? Function->GetName() : FString();
}
