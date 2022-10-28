#include "Reflection/Function/FFunctionDescriptor.h"
#include "Environment/FCSharpEnvironment.h"

FFunctionDescriptor::FFunctionDescriptor(UFunction* InFunction):
	Function(InFunction),
	OriginalFunction(nullptr),
	ReturnPropertyDescriptor(nullptr)
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

			const auto Index = PropertyDescriptors.Add(PropertyDescriptor);

			if (Property->HasAnyPropertyFlags(CPF_OutParm | CPF_ReferenceParm) && !Property->HasAnyPropertyFlags(
				CPF_ConstParm))
			{
				OutPropertyIndexes.Add(Index);
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
}

FOutParmRec* FFunctionDescriptor::FindOutParmRec(FOutParmRec* OutParam, const FProperty* OutProperty)
{
	while (OutParam != nullptr)
	{
		if (OutParam->Property == OutProperty)
		{
			return OutParam;
		}

		OutParam = OutParam->NextOutParm;
	}

	return nullptr;
}

bool FFunctionDescriptor::CallCSharp(FFrame& Stack, void* const Z_Param__Result)
{
	const auto InParams = Stack.Locals;

	auto OutParams = Stack.OutParms;

	TArray<void*> CSharpParams;

	CSharpParams.Reserve(PropertyDescriptors.Num());

	for (const auto& PropertyDescriptor : PropertyDescriptors)
	{
		const auto Index = CSharpParams.Add(FMemory::Malloc(PropertyDescriptor->GetProperty()->GetSize()));

		PropertyDescriptor->Get(PropertyDescriptor->GetProperty()->ContainerPtrToValuePtr<void>(InParams),
		                        CSharpParams[Index]);
	}

	if (const auto FoundMonoObject = FCSharpEnvironment::GetEnvironment()->GetObject(Stack.Object))
	{
		if (const auto FoundMonoClass = FCSharpEnvironment::GetEnvironment()->GetClassDescriptor(
			Stack.Object->GetClass())->GetMonoClass())
		{
			if (const auto FoundMonoMethod = FCSharpEnvironment::GetEnvironment()->GetDomain()->
				Class_Get_Method_From_Name(FoundMonoClass, TCHAR_TO_UTF8(*Stack.Node->GetName()),
				                           PropertyDescriptors.Num()))
			{
				const auto ResultValue = FCSharpEnvironment::GetEnvironment()->GetDomain()->Runtime_Invoke(
					FoundMonoMethod, FoundMonoObject, CSharpParams.GetData(), nullptr);

				if (ResultValue != nullptr && ReturnPropertyDescriptor != nullptr)
				{
					if (const auto UnBoxResultValue = FCSharpEnvironment::GetEnvironment()->GetDomain()->Object_Unbox(
						ResultValue))
					{
						ReturnPropertyDescriptor->Set(UnBoxResultValue, Z_Param__Result);
					}
				}

				if (OutPropertyIndexes.Num() > 0)
				{
					for (auto Index = 0; Index < OutPropertyIndexes.Num(); ++Index)
					{
						const auto OutPropertyDescriptor = PropertyDescriptors[OutPropertyIndexes[Index]];

						OutParams = FindOutParmRec(OutParams, OutPropertyDescriptor->GetProperty());

						if (OutParams != nullptr && OutPropertyDescriptor != nullptr)
						{
							OutPropertyDescriptor->Set(CSharpParams[OutPropertyIndexes[Index]], OutParams->PropAddr);
						}
					}
				}
			}
		}
	}

	for (auto Index = 0; Index < PropertyDescriptors.Num(); ++Index)
	{
		FMemory::Free(CSharpParams[Index]);

		CSharpParams[Index] = nullptr;
	}

	CSharpParams.Empty();

	return true;
}
