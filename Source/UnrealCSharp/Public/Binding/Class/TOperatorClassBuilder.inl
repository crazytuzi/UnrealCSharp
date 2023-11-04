#pragma once

#include "FClassBuilder.h"
#include "Binding/Template/TClassName.inl"
#include "Binding/Template/TClassFullName.inl"
#include "Binding/TypeInfo/TTypeInfo.inl"
#include "Macro/FunctionMacro.h"

template <typename T>
class TOperatorClassBuilder : public FClassBuilder
{
public:
	explicit TOperatorClassBuilder(const FString& InImplementationNameSpace):
#if WITH_PROPERTY_INFO
		FClassBuilder(TClassName<T>::Get(), InImplementationNameSpace,
		              TClassFullName<T>::Get(), TTypeInfo<T>::Get())
#else
		FClassBuilder(TClassName<T>::Get(), InImplementationNameSpace)
#endif
	{
	}

public:
	PREFIX_UNARY_CONST_OPERATOR(LogicalNot, bool(*)(const T&), !);

	PREFIX_UNARY_CONST_OPERATOR(UnaryPlus, T(*)(const T&), +);

	PREFIX_UNARY_CONST_OPERATOR(UnaryMinus, T(*)(const T&), -);

	PREFIX_UNARY_CONST_OPERATOR(Complement, T(*)(const T&), ~);

	PREFIX_UNARY_OPERATOR(PreIncrement, T&(*)(T&), ++);

	PREFIX_UNARY_OPERATOR(PreDecrement, T&(*)(T&), --);

	BINARY_OPERATOR(Plus, T(*)(const T&, const T&), +);

	BINARY_OPERATOR(Minus, T(*)(const T&, const T&), -);

	BINARY_OPERATOR(Multiplies, T(*)(const T&, const T&), *);

	BINARY_OPERATOR(Divides, T(*)(const T&, const T&), /);

	BINARY_OPERATOR(Modulus, T(*)(const T&, const T&), %);

	BINARY_OPERATOR(BitAnd, T(*)(const T&, const T&), &);

	BINARY_OPERATOR(BitOr, T(*)(const T&, const T&), |);

	BINARY_OPERATOR(BitXor, T(*)(const T&, const T&), ^);

	BINARY_OPERATOR(LeftShift, T(*)(const T&, const T&), <<);

	BINARY_OPERATOR(RightShift, T(*)(const T&, const T&), >>);

	BINARY_OPERATOR(EqualTo, bool(*)(const T&, const T&), ==);

	BINARY_OPERATOR(NotEqualTo, bool(*)(const T&, const T&), !=);

	BINARY_OPERATOR(Less, bool(*)(const T&, const T&), <);

	BINARY_OPERATOR(LessEqual, bool(*)(const T&, const T&), <=);

	BINARY_OPERATOR(Greater, bool(*)(const T&, const T&), >);

	BINARY_OPERATOR(GreaterEqual, bool(*)(const T&, const T&), >=);

private:
#if WITH_FUNCTION_INFO
	TOperatorClassBuilder& LogicalNot(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TOperatorClassBuilder& LogicalNot(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(TEXT("operator !"),
		         FUNCTION_LOGICAL_NOT,
		         InMethod,
		         InFunctionInfo);
#else
		Function(TEXT("operator !"),
				 FUNCTION_LOGICAL_NOT,
				 InMethod);
#endif

		return *this;
	}

#if WITH_FUNCTION_INFO
	TOperatorClassBuilder& UnaryPlus(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TOperatorClassBuilder& UnaryPlus(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(TEXT("operator +"),
		         FUNCTION_UNARY_PLUS,
		         InMethod,
		         InFunctionInfo);
#else
		Function(TEXT("operator +"),
				 FUNCTION_UNARY_PLUS,
				 InMethod);
#endif

		return *this;
	}

#if WITH_FUNCTION_INFO
	TOperatorClassBuilder& UnaryMinus(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TOperatorClassBuilder& UnaryMinus(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(TEXT("operator -"),
		         FUNCTION_UNARY_MINUS,
		         InMethod,
		         InFunctionInfo);
#else
		Function(TEXT("operator -"),
				 FUNCTION_UNARY_MINUS,
				 InMethod);
#endif

		return *this;
	}

#if WITH_FUNCTION_INFO
	TOperatorClassBuilder& Complement(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TOperatorClassBuilder& Complement(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(TEXT("operator ~"),
		         FUNCTION_COMPLEMENT,
		         InMethod,
		         InFunctionInfo);
#else
		Function(TEXT("operator ~"),
				 FUNCTION_COMPLEMENT,
				 InMethod);
#endif

		return *this;
	}

#if WITH_FUNCTION_INFO
	TOperatorClassBuilder& PreIncrement(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TOperatorClassBuilder& PreIncrement(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(TEXT("operator ++"),
		         FUNCTION_PRE_INCREMENT,
		         InMethod,
		         InFunctionInfo);
#else
		Function(TEXT("operator ++"),
				 FUNCTION_PRE_INCREMENT,
				 InMethod);
#endif

		return *this;
	}

#if WITH_FUNCTION_INFO
	TOperatorClassBuilder& PreDecrement(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
    TOperatorClassBuilder& PreDecrement(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(TEXT("operator --"),
		         FUNCTION_PRE_DECREMENT,
		         InMethod,
		         InFunctionInfo);
#else
    	Function(TEXT("operator --"),
    			 FUNCTION_PRE_DECREMENT,
    			 InMethod);
#endif

		return *this;
	}

#if WITH_FUNCTION_INFO
	TOperatorClassBuilder& Plus(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TOperatorClassBuilder& Plus(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(TEXT("operator +"),
		         FUNCTION_PLUS,
		         InMethod,
		         InFunctionInfo);
#else
		Function(TEXT("operator +"),
				 FUNCTION_PLUS,
				 InMethod);
#endif

		return *this;
	}

#if WITH_FUNCTION_INFO
	TOperatorClassBuilder& Minus(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TOperatorClassBuilder& Minus(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(TEXT("operator -"),
		         FUNCTION_MINUS,
		         InMethod,
		         InFunctionInfo);
#else
		Function(TEXT("operator -"),
				 FUNCTION_MINUS,
				 InMethod);
#endif

		return *this;
	}

#if WITH_FUNCTION_INFO
	TOperatorClassBuilder& Multiplies(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TOperatorClassBuilder& Multiplies(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(TEXT("operator *"),
		         FUNCTION_MULTIPLIES,
		         InMethod,
		         InFunctionInfo);
#else
		Function(TEXT("operator *"),
				 FUNCTION_MULTIPLIES,
				 InMethod);
#endif

		return *this;
	}

#if WITH_FUNCTION_INFO
	TOperatorClassBuilder& Divides(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TOperatorClassBuilder& Divides(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(TEXT("operator /"),
		         FUNCTION_DIVIDES,
		         InMethod,
		         InFunctionInfo);
#else
		Function(TEXT("operator /"),
				 FUNCTION_DIVIDES,
				 InMethod);
#endif

		return *this;
	}

#if WITH_FUNCTION_INFO
	TOperatorClassBuilder& Modulus(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TOperatorClassBuilder& Modulus(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(TEXT("operator %"),
		         FUNCTION_MODULUS,
		         InMethod,
		         InFunctionInfo);
#else
		Function(TEXT("operator %"),
				 FUNCTION_MODULUS,
				 InMethod);
#endif

		return *this;
	}

#if WITH_FUNCTION_INFO
	TOperatorClassBuilder& BitAnd(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TOperatorClassBuilder& BitAnd(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(TEXT("operator &"),
		         FUNCTION_BIT_AND,
		         InMethod,
		         InFunctionInfo);
#else
		Function(TEXT("operator &"),
				 FUNCTION_BIT_AND,
				 InMethod);
#endif

		return *this;
	}

#if WITH_FUNCTION_INFO
	TOperatorClassBuilder& BitOr(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TOperatorClassBuilder& BitOr(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(TEXT("operator |"),
		         FUNCTION_BIT_OR,
		         InMethod,
		         InFunctionInfo);
#else
		Function(TEXT("operator |"),
				 FUNCTION_BIT_OR,
				 InMethod);
#endif

		return *this;
	}

#if WITH_FUNCTION_INFO
	TOperatorClassBuilder& BitXor(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TOperatorClassBuilder& BitXor(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(TEXT("operator ^"),
		         FUNCTION_BIT_XOR,
		         InMethod,
		         InFunctionInfo);
#else
		Function(TEXT("operator ^"),
				 FUNCTION_BIT_XOR,
				 InMethod);
#endif

		return *this;
	}

#if WITH_FUNCTION_INFO
	TOperatorClassBuilder& LeftShift(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TOperatorClassBuilder& LeftShift(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(TEXT("operator <<"),
		         FUNCTION_LEFT_SHIFT,
		         InMethod,
		         InFunctionInfo);
#else
		Function(TEXT("operator <<"),
				 FUNCTION_LEFT_SHIFT,
				 InMethod);
#endif

		return *this;
	}

#if WITH_FUNCTION_INFO
	TOperatorClassBuilder& RightShift(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TOperatorClassBuilder& RightShift(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(TEXT("operator >>"),
		         FUNCTION_RIGHT_SHIFT,
		         InMethod,
		         InFunctionInfo);
#else
		Function(TEXT("operator >>"),
				 FUNCTION_RIGHT_SHIFT,
				 InMethod);
#endif

		return *this;
	}

#if WITH_FUNCTION_INFO
	TOperatorClassBuilder& EqualTo(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TOperatorClassBuilder& EqualTo(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(TEXT("operator =="),
		         FUNCTION_EQUAL_TO,
		         InMethod,
		         InFunctionInfo);
#else
		Function(TEXT("operator =="),
				 FUNCTION_EQUAL_TO,
				 InMethod);
#endif

		return *this;
	}

#if WITH_FUNCTION_INFO
	TOperatorClassBuilder& NotEqualTo(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TOperatorClassBuilder& NotEqualTo(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(TEXT("operator !="),
		         FUNCTION_NOT_EQUAL_TO,
		         InMethod,
		         InFunctionInfo);
#else
		Function(TEXT("operator !="),
				 FUNCTION_NOT_EQUAL_TO,
				 InMethod);
#endif

		return *this;
	}

#if WITH_FUNCTION_INFO
	TOperatorClassBuilder& Less(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TOperatorClassBuilder& Less(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(TEXT("operator <"),
		         FUNCTION_LESS,
		         InMethod,
		         InFunctionInfo);
#else
		Function(TEXT("operator <"),
				 FUNCTION_LESS,
				 InMethod);
#endif

		return *this;
	}

#if WITH_FUNCTION_INFO
	TOperatorClassBuilder& LessEqual(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TOperatorClassBuilder& LessEqual(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(TEXT("operator <="),
		         FUNCTION_LESS_EQUAL,
		         InMethod,
		         InFunctionInfo);
#else
		Function(TEXT("operator <="),
				 FUNCTION_LESS_EQUAL,
				 InMethod);
#endif

		return *this;
	}

#if WITH_FUNCTION_INFO
	TOperatorClassBuilder& Greater(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TOperatorClassBuilder& Greater(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(TEXT("operator >"),
		         FUNCTION_GREATER,
		         InMethod,
		         InFunctionInfo);
#else
		Function(TEXT("operator >"),
				 FUNCTION_GREATER,
				 InMethod);
#endif

		return *this;
	}

#if WITH_FUNCTION_INFO
	TOperatorClassBuilder& GreaterEqual(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TOperatorClassBuilder& GreaterEqual(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(TEXT("operator >="),
		         FUNCTION_GREATER_EQUAL,
		         InMethod,
		         InFunctionInfo);
#else
		Function(TEXT("operator >="),
				 FUNCTION_GREATER_EQUAL,
				 InMethod);
#endif

		return *this;
	}
};
