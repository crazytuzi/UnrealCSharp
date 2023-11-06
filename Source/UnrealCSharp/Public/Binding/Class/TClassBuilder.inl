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
	TClassBuilder& LogicalNot(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TClassBuilder& LogicalNot(const void* InMethod)
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
	TClassBuilder& UnaryPlus(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TClassBuilder& UnaryPlus(const void* InMethod)
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
	TClassBuilder& UnaryMinus(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TClassBuilder& UnaryMinus(const void* InMethod)
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
	TClassBuilder& Complement(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TClassBuilder& Complement(const void* InMethod)
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
	TClassBuilder& PreIncrement(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TClassBuilder& PreIncrement(const void* InMethod)
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
	TClassBuilder& PreDecrement(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
    TClassBuilder& PreDecrement(const void* InMethod)
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
	TClassBuilder& Plus(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TClassBuilder& Plus(const void* InMethod)
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
	TClassBuilder& Minus(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TClassBuilder& Minus(const void* InMethod)
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
	TClassBuilder& Multiplies(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TClassBuilder& Multiplies(const void* InMethod)
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
	TClassBuilder& Divides(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TClassBuilder& Divides(const void* InMethod)
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
	TClassBuilder& Modulus(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TClassBuilder& Modulus(const void* InMethod)
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
	TClassBuilder& BitAnd(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TClassBuilder& BitAnd(const void* InMethod)
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
	TClassBuilder& BitOr(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TClassBuilder& BitOr(const void* InMethod)
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
	TClassBuilder& BitXor(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TClassBuilder& BitXor(const void* InMethod)
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
	TClassBuilder& LeftShift(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TClassBuilder& LeftShift(const void* InMethod)
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
	TClassBuilder& RightShift(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TClassBuilder& RightShift(const void* InMethod)
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
	TClassBuilder& EqualTo(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TClassBuilder& EqualTo(const void* InMethod)
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
	TClassBuilder& NotEqualTo(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TClassBuilder& NotEqualTo(const void* InMethod)
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
	TClassBuilder& Less(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TClassBuilder& Less(const void* InMethod)
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
	TClassBuilder& LessEqual(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TClassBuilder& LessEqual(const void* InMethod)
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
	TClassBuilder& Greater(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TClassBuilder& Greater(const void* InMethod)
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
	TClassBuilder& GreaterEqual(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TClassBuilder& GreaterEqual(const void* InMethod)
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
