#pragma once

#include "FClassBuilder.h"
#include "Binding/Template/TClassName.inl"
#include "Binding/Template/TClassFullName.inl"
#include "Binding/TypeInfo/TTypeInfo.inl"
#include "Macro/FunctionMacro.h"

template <typename T>
class TClassBuilder : public FClassBuilder
{
public:
	explicit TClassBuilder(const FString& InImplementationNameSpace):
#if WITH_PROPERTY_INFO
		FClassBuilder(TClassName<T>::Get(), InImplementationNameSpace,
		              TClassFullName<T>::Get(), TTypeInfo<T>::Get())
#else
		FClassBuilder(TClassName<T>::Get(), InImplementationNameSpace)
#endif
	{
	}

public:
#if WITH_FUNCTION_INFO
	TClassBuilder& Constructor(const void* InMethod, FFunctionInfo* InFunctionInfo,
	                           const TArray<FString>& InParamNames = {})
#else
	TClassBuilder& Constructor(const void* InMethod,
	                           const TArray<FString>& InParamNames = {})
#endif
	{
#if WITH_FUNCTION_INFO
		Function(TClassFullName<T>::Get(), InMethod, InFunctionInfo, InParamNames);
#else
		Function(TClassFullName<T>::Get(), InMethod, InParamNames);
#endif

		return *this;
	}

#if WITH_FUNCTION_INFO
	TClassBuilder& Destructor(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TClassBuilder& Destructor(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(FString::Printf(TEXT(
			         "~%s"
		         ),
		                         *TClassFullName<T>::Get()
		         ),
		         FUNCTION_DESTRUCTOR,
		         InMethod,
		         InFunctionInfo);
#else
		Function(FString::Printf(TEXT(
					 "~%s"
				 ),
								 *TClassFullName<T>::Get()
				 ),
				 FUNCTION_DESTRUCTOR,
				 InMethod);
#endif

		return *this;
	}

public:
	PREFIX_UNARY_CONST_OPERATOR(LogicalNot, "operator !", FUNCTION_LOGICAL_NOT, !);

	PREFIX_UNARY_CONST_OPERATOR(UnaryPlus, "operator +", FUNCTION_UNARY_PLUS, +);

	PREFIX_UNARY_CONST_OPERATOR(UnaryMinus, "operator -", FUNCTION_UNARY_MINUS, -);

	PREFIX_UNARY_CONST_OPERATOR(Complement, "operator ~", FUNCTION_COMPLEMENT, ~);

	PREFIX_UNARY_OPERATOR(PreIncrement, "operator ++", FUNCTION_PRE_INCREMENT, ++);

	PREFIX_UNARY_OPERATOR(PreDecrement, "operator --", FUNCTION_PRE_DECREMENT, --);

	BINARY_OPERATOR(Plus, "operator +", FUNCTION_PLUS, +);

	BINARY_OPERATOR(Minus, "operator -", FUNCTION_MINUS, -);

	BINARY_OPERATOR(Multiplies, "operator *", FUNCTION_MULTIPLIES, *);

	BINARY_OPERATOR(Divides, "operator /", FUNCTION_DIVIDES, /);

	BINARY_OPERATOR(Modulus, "operator %", FUNCTION_MODULUS, %);

	BINARY_OPERATOR(BitAnd, "operator &", FUNCTION_BIT_AND, &);

	BINARY_OPERATOR(BitOr, "operator |", FUNCTION_BIT_OR, |);

	BINARY_OPERATOR(BitXor, "operator ^", FUNCTION_BIT_XOR, ^);

	BINARY_OPERATOR(LeftShift, "operator <<", FUNCTION_LEFT_SHIFT, <<);

	BINARY_OPERATOR(RightShift, "operator >>", FUNCTION_RIGHT_SHIFT, >>);

	BINARY_OPERATOR(EqualTo, "operator ==", FUNCTION_EQUAL_TO, ==);

	BINARY_OPERATOR(NotEqualTo, "operator !=", FUNCTION_NOT_EQUAL_TO, !=);

	BINARY_OPERATOR(Less, "operator <", FUNCTION_LESS, <);

	BINARY_OPERATOR(LessEqual, "operator <=", FUNCTION_LESS_EQUAL, <=);

	BINARY_OPERATOR(Greater, "operator >", FUNCTION_GREATER, >);

	BINARY_OPERATOR(GreaterEqual, "operator >=", FUNCTION_GREATER_EQUAL, >=);
};
