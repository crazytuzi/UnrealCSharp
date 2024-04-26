#include "Binding/Enum/FBindingEnumRegister.h"

FBindingEnumRegister::FBindingEnumRegister(const TFunction<FString()>& InEnumFunction,
                                           const FString& InUnderlyingType,
                                           const bool InIsEngineEnum,
                                           const TOptional<TFunction<FTypeInfo*()>>& InTypeInfoFunction):
	EnumFunction(InEnumFunction),
	UnderlyingType(InUnderlyingType),
	bIsEngineEnum(InIsEngineEnum),
	TypeInfoRegister(InTypeInfoFunction)
{
}

FBindingEnumRegister::operator FBindingEnum*() const
{
	return new FBindingEnum(EnumFunction(),
	                        UnderlyingType,
	                        bIsEngineEnum,
	                        FBindingTypeInfo(TypeInfoRegister),
	                        Enumerators
	);
}

void FBindingEnumRegister::BindingEnumerator(const FString& InKey, const int64 InEnumerator)
{
	Enumerators.Add(InKey, InEnumerator);
}
