#include "Binding/FBinding.h"

FBinding& FBinding::Get()
{
	static FBinding Binding;

	return Binding;
}

FBinding& FBinding::Register()
{
	if (!bIsRegister)
	{
		bIsRegister = true;

		for (const auto& Class : ClassRegisters)
		{
			Classes.Emplace(Class->operator FBindingClass*());

			delete Class;
		}

		ClassRegisters.Empty();

		for (const auto& Enum : EnumRegisters)
		{
			Enums.Emplace(Enum->operator FBindingEnum*());

			delete Enum;
		}

		EnumRegisters.Empty();
	}

	return *this;
}

FBindingClassRegister*& FBinding::Register(const TFunction<FString()>& InClassFunction,
                                           const FString& InImplementationNameSpace,
                                           const TFunction<bool()>& InIsEngineClassFunction,
                                           const bool InIsReflectionClass,
                                           const TOptional<TFunction<FTypeInfo*()>>& InTypeInfoFunction)
{
	if (!InIsReflectionClass)
	{
		const auto Class = InClassFunction();

		for (auto& ClassRegister : ClassRegisters)
		{
			if (!ClassRegister->IsReflectionClass())
			{
				if (Class == ClassRegister->GetClass())
				{
					return ClassRegister;
				}
			}
		}
	}

	return ClassRegisters.Add_GetRef(new FBindingClassRegister(InClassFunction,
	                                                           InImplementationNameSpace,
	                                                           InIsEngineClassFunction,
	                                                           InIsReflectionClass,
	                                                           InTypeInfoFunction));
}

FBindingEnumRegister*& FBinding::Register(const TFunction<FString()>& InEnumFunction,
                                          const FString& InUnderlyingType,
                                          const bool InIsEngineEnum,
                                          const TOptional<TFunction<FTypeInfo*()>>& InTypeInfoFunction)
{
	return EnumRegisters.Add_GetRef(new FBindingEnumRegister(InEnumFunction,
	                                                         InUnderlyingType,
	                                                         InIsEngineEnum,
	                                                         InTypeInfoFunction));
}

const TArray<FBindingClass*>& FBinding::GetClasses() const
{
	return Classes;
}

const TArray<FBindingEnum*>& FBinding::GetEnums() const
{
	return Enums;
}

bool FBinding::IsEngineClass(const FString& InClass) const
{
	for (auto& Class : Classes)
	{
		if (InClass == Class->GetClass())
		{
			return Class->IsEngineClass();
		}
	}

	return false;
}

bool FBinding::IsEngineEnum(const FString& InEnum) const
{
	for (auto& Enum : Enums)
	{
		if (InEnum == Enum->GetEnum())
		{
			return Enum->IsEngineEnum();
		}
	}

	return false;
}
