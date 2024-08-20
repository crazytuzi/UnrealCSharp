#pragma once

#include "FClassBuilder.h"
#include "Binding/Template/TIsProjectClass.inl"
#include "Binding/TypeInfo/TTypeInfo.inl"
#include "CoreMacro/BindingMacro.h"
#include "Macro/FunctionMacro.h"
#include "Template/TIsReflectionClass.inl"

template <typename T, bool bIsProjectClass>
class TClassBuilder : public FClassBuilder
{
public:
	explicit TClassBuilder(const FString& InImplementationNameSpace,
	                       const TOptional<TFunction<FString()>>& InClassFunction):
		FClassBuilder({
			              [InClassFunction]()
			              {
				              return InClassFunction.IsSet() ? InClassFunction.GetValue()() : TName<T, T>::Get();
			              }
		              },
		              InImplementationNameSpace,
		              {[]() { return TIsProjectClass<T, bIsProjectClass>::Get(); }},
		              TIsReflectionClass<T>::Value
#if WITH_TYPE_INFO
		              , {[]() { return TTypeInfo<T>::Get(); }}
#endif
		)
	{
	}

public:
	auto Constructor(const void* InMethod,
#if WITH_FUNCTION_INFO
	                 const TOptional<TFunction<FFunctionInfo*()>>& InFunctionInfoFunction = {},
#endif
	                 const TArray<FString>& InParamNames = {}) -> TClassBuilder&
	{
#if WITH_FUNCTION_INFO
		InFunctionInfoFunction.GetValue()()->SetParamNames(InParamNames);
#endif

		Function(TName<T, T>::Get(), InMethod
#if WITH_FUNCTION_INFO
		         , InFunctionInfoFunction
#endif
		);

		return *this;
	}

	auto Destructor(const void* InMethod
#if WITH_FUNCTION_INFO
	                , const TOptional<TFunction<FFunctionInfo*()>>& InFunctionInfoFunction = {}
#endif
	) -> TClassBuilder&
	{
		Function(FString::Printf(TEXT(
			         "~%s"
		         ),
		                         *TName<T, T>::Get()
		         ),
		         FUNCTION_DESTRUCTOR,
		         InMethod
#if WITH_FUNCTION_INFO
		         , InFunctionInfoFunction
#endif
		);

		return *this;
	}

	auto Subscript(const void* InGetMethod,
	               const void* InSetMethod
#if WITH_FUNCTION_INFO
	               , const TOptional<TFunction<FFunctionInfo*()>>& InFunctionInfoFunction
#endif
	) -> TClassBuilder&
	{
#if WITH_FUNCTION_INFO
		if (InFunctionInfoFunction.IsSet())
		{
			ClassRegister->BindingSubscript(TEXT("this"),
			                                FUNCTION_GET_SUBSCRIPT,
			                                FUNCTION_SET_SUBSCRIPT,
			                                InFunctionInfoFunction);
		}
#endif

		Function(FUNCTION_GET_SUBSCRIPT, TFunctionPointer<decltype(InGetMethod)>(InGetMethod));

		Function(FUNCTION_SET_SUBSCRIPT, TFunctionPointer<decltype(InSetMethod)>(InSetMethod));

		return *this;
	}

public:
	PREFIX_UNARY_CONST_OPERATOR(LogicalNot, TEXT("operator !"), FUNCTION_LOGICAL_NOT, !);

	PREFIX_UNARY_CONST_OPERATOR(UnaryPlus, TEXT("operator +"), FUNCTION_UNARY_PLUS, +);

	PREFIX_UNARY_CONST_OPERATOR(UnaryMinus, TEXT("operator -"), FUNCTION_UNARY_MINUS, -);

	PREFIX_UNARY_CONST_OPERATOR(Complement, TEXT("operator ~"), FUNCTION_COMPLEMENT, ~);

	PREFIX_UNARY_OPERATOR(PreIncrement, TEXT("operator ++"), FUNCTION_PRE_INCREMENT, ++);

	PREFIX_UNARY_OPERATOR(PreDecrement, TEXT("operator --"), FUNCTION_PRE_DECREMENT, --);

	BINARY_OPERATOR(Plus, TEXT("operator +"), FUNCTION_PLUS, +);

	BINARY_OPERATOR(Minus, TEXT("operator -"), FUNCTION_MINUS, -);

	BINARY_OPERATOR(Multiplies, TEXT("operator *"), FUNCTION_MULTIPLIES, *);

	BINARY_OPERATOR(Divides, TEXT("operator /"), FUNCTION_DIVIDES, /);

	BINARY_OPERATOR(Modulus, TEXT("operator %"), FUNCTION_MODULUS, %);

	BINARY_OPERATOR(BitAnd, TEXT("operator &"), FUNCTION_BIT_AND, &);

	BINARY_OPERATOR(BitOr, TEXT("operator |"), FUNCTION_BIT_OR, |);

	BINARY_OPERATOR(BitXor, TEXT("operator ^"), FUNCTION_BIT_XOR, ^);

	BINARY_OPERATOR(LeftShift, TEXT("operator <<"), FUNCTION_LEFT_SHIFT, <<);

	BINARY_OPERATOR(RightShift, TEXT("operator >>"), FUNCTION_RIGHT_SHIFT, >>);

	BINARY_OPERATOR(EqualTo, TEXT("operator =="), FUNCTION_EQUAL_TO, ==);

	BINARY_OPERATOR(NotEqualTo, TEXT("operator !="), FUNCTION_NOT_EQUAL_TO, !=);

	BINARY_OPERATOR(Less, TEXT("operator <"), FUNCTION_LESS, <);

	BINARY_OPERATOR(LessEqual, TEXT("operator <="), FUNCTION_LESS_EQUAL, <=);

	BINARY_OPERATOR(Greater, TEXT("operator >"), FUNCTION_GREATER, >);

	BINARY_OPERATOR(GreaterEqual, TEXT("operator >="), FUNCTION_GREATER_EQUAL, >=);
};
