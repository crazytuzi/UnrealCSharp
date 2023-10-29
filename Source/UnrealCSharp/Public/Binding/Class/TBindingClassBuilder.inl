#pragma once

#include "FClassBuilder.h"
#include "Binding/Template/TClassName.inl"
#include "Binding/Template/TClassFullName.inl"
#include "Binding/TypeInfo/TTypeInfo.inl"
#include "Macro/FunctionMacro.h"

template <typename T>
class TBindingClassBuilder final : public FClassBuilder
{
public:
	explicit TBindingClassBuilder(const FString& InImplementationNameSpace):
#if WITH_PROPERTY_INFO
		FClassBuilder(TClassName<T>::Get(), InImplementationNameSpace,
		              TClassFullName<T>::Get(), TTypeInfo<T>::Get())
#else
		FClassBuilder(TClassName<T>::Get(), InImplementationNameSpace)
#endif
	{
		if constexpr (std::is_default_constructible_v<T>)
		{
			Constructor(BINDING_CONSTRUCTOR(T));
		}

		Destructor(BINDING_DESTRUCTOR());
	}

	template <typename Class>
	TBindingClassBuilder& Inheritance(const FString& InImplementationNameSpace)
	{
		GetBindingClass()->Inheritance(TClassName<Class>::Get(), TClassFullName<Class>::Get(),
		                               InImplementationNameSpace, TTypeInfo<Class>::Get());

		return *this;
	}

	TBindingClassBuilder& LogicalNot()
	{
		LogicalNot(BINDING_OPERATOR(bool(*)(const T&), &operator!));

		return *this;
	}

	TBindingClassBuilder& UnaryPlus()
	{
		UnaryPlus(BINDING_OPERATOR(T(*)(const T&), &operator+));

		return *this;
	}

	TBindingClassBuilder& UnaryMinus()
	{
		UnaryMinus(BINDING_OPERATOR(T(*)(const T&), (&operator-)));

		return *this;
	}

	TBindingClassBuilder& Complement()
	{
		Complement(BINDING_OPERATOR(T(*)(const T&), &operator~));

		return *this;
	}

	TBindingClassBuilder& Plus()
	{
		Plus(BINDING_OPERATOR(T(*)(const T&, const T&), &operator+));

		return *this;
	}

	TBindingClassBuilder& Minus()
	{
		Minus(BINDING_OPERATOR(T(*)(const T&, const T&), (&operator-)));

		return *this;
	}

	TBindingClassBuilder& Multiplies()
	{
		Multiplies(BINDING_OPERATOR(T(*)(const T&, const T&), &operator*));

		return *this;
	}

	TBindingClassBuilder& Divides()
	{
		Divides(BINDING_OPERATOR(T(*)(const T&, const T&), &operator/));

		return *this;
	}

	TBindingClassBuilder& Modulus()
	{
		Modulus(BINDING_OPERATOR(T(*)(const T&, const T&), (&operator%)));

		return *this;
	}

	TBindingClassBuilder& BitAnd()
	{
		BitAnd(BINDING_OPERATOR(T(*)(const T&, const T&), &operator&));

		return *this;
	}

	TBindingClassBuilder& BitOr()
	{
		BitOr(BINDING_OPERATOR(T(*)(const T&, const T&), &operator|));

		return *this;
	}

	TBindingClassBuilder& BitXor()
	{
		BitXor(BINDING_OPERATOR(T(*)(const T&, const T&), &operator^));

		return *this;
	}

	TBindingClassBuilder& LeftShift()
	{
		LeftShift(BINDING_OPERATOR(T(*)(const T&, const T&), &operator<<));

		return *this;
	}

	TBindingClassBuilder& RightShift()
	{
		RightShift(BINDING_OPERATOR(T(*)(const T&, const T&), (&operator>>)));

		return *this;
	}

	TBindingClassBuilder& EqualTo()
	{
		EqualTo(BINDING_OPERATOR(bool(*)(const T&, const T&), &operator==));

		return *this;
	}

	TBindingClassBuilder& NotEqualTo()
	{
		NotEqualTo(BINDING_OPERATOR(bool(*)(const T&, const T&), &operator!=));

		return *this;
	}

	TBindingClassBuilder& Less()
	{
		Less(BINDING_OPERATOR(bool(*)(const T&, const T&), &operator<));

		return *this;
	}

	TBindingClassBuilder& LessEqual()
	{
		LessEqual(BINDING_OPERATOR(bool(*)(const T&, const T&), &operator<=));

		return *this;
	}

	TBindingClassBuilder& Greater()
	{
		Greater(BINDING_OPERATOR(bool(*)(const T&, const T&), (&operator>)));

		return *this;
	}

	TBindingClassBuilder& GreaterEqual()
	{
		GreaterEqual(BINDING_OPERATOR(bool(*)(const T&, const T&), &operator>=));

		return *this;
	}

#if WITH_FUNCTION_INFO
	TBindingClassBuilder& Constructor(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TBindingClassBuilder& Constructor(const void* InMethod)
#endif
	{
#if WITH_FUNCTION_INFO
		Function(TClassFullName<T>::Get(), InMethod, InFunctionInfo);
#else
		Function(TClassFullName<T>::Get(), InMethod);
#endif

		return *this;
	}

#if WITH_FUNCTION_INFO
	TBindingClassBuilder& Destructor(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TBindingClassBuilder& Destructor(const void* InMethod)
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

#if WITH_FUNCTION_INFO
	TBindingClassBuilder& LogicalNot(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TBindingClassBuilder& LogicalNot(const void* InMethod)
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
	TBindingClassBuilder& UnaryPlus(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TBindingClassBuilder& UnaryPlus(const void* InMethod)
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
	TBindingClassBuilder& UnaryMinus(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TBindingClassBuilder& UnaryMinus(const void* InMethod)
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
	TBindingClassBuilder& Complement(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TBindingClassBuilder& Complement(const void* InMethod)
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
	TBindingClassBuilder& Plus(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TBindingClassBuilder& Plus(const void* InMethod)
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
	TBindingClassBuilder& Minus(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TBindingClassBuilder& Minus(const void* InMethod)
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
	TBindingClassBuilder& Multiplies(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TBindingClassBuilder& Multiplies(const void* InMethod)
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
	TBindingClassBuilder& Divides(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TBindingClassBuilder& Divides(const void* InMethod)
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
	TBindingClassBuilder& Modulus(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TBindingClassBuilder& Modulus(const void* InMethod)
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
	TBindingClassBuilder& BitAnd(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TBindingClassBuilder& BitAnd(const void* InMethod)
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
	TBindingClassBuilder& BitOr(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TBindingClassBuilder& BitOr(const void* InMethod)
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
	TBindingClassBuilder& BitXor(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TBindingClassBuilder& BitXor(const void* InMethod)
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
	TBindingClassBuilder& LeftShift(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TBindingClassBuilder& LeftShift(const void* InMethod)
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
	TBindingClassBuilder& RightShift(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TBindingClassBuilder& RightShift(const void* InMethod)
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
	TBindingClassBuilder& EqualTo(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TBindingClassBuilder& EqualTo(const void* InMethod)
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
	TBindingClassBuilder& NotEqualTo(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TBindingClassBuilder& NotEqualTo(const void* InMethod)
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
	TBindingClassBuilder& Less(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TBindingClassBuilder& Less(const void* InMethod)
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
	TBindingClassBuilder& LessEqual(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TBindingClassBuilder& LessEqual(const void* InMethod)
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
	TBindingClassBuilder& Greater(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TBindingClassBuilder& Greater(const void* InMethod)
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
	TBindingClassBuilder& GreaterEqual(const void* InMethod, FFunctionInfo* InFunctionInfo)
#else
	TBindingClassBuilder& GreaterEqual(const void* InMethod)
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
