#include "Binding/Enum/FBindingEnumRegister.h"

FBindingEnumRegister::FBindingEnumRegister(const TFunction<FString()>& InEnumFunction,
                                           const FString& InUnderlyingType,
                                           const bool InIsProjectEnum,
                                           const TOptional<TFunction<FTypeInfo*()>>& InTypeInfoFunction):
	EnumFunction(InEnumFunction),
	UnderlyingType(InUnderlyingType),
	bIsProjectEnum(InIsProjectEnum),
	TypeInfoRegister(InTypeInfoFunction)
{
}

FBindingEnumRegister::operator FBindingEnum*() const
{
	return new FBindingEnum(EnumFunction(),
	                        UnderlyingType,
	                        bIsProjectEnum,
	                        FBindingTypeInfo(TypeInfoRegister),
	                        Enumerators
	);
}

void FBindingEnumRegister::BindingEnumerator(const FString& InKey, const int64 InEnumerator)
{
	Enumerators.Add(InKey, InEnumerator);
}
