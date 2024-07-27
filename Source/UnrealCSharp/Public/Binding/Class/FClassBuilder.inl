#pragma once

template <typename T>
auto FClassBuilder::Function(const FString& InName,
                             T InMethod
#if WITH_FUNCTION_INFO
                             , const TOptional<TFunction<FFunctionInfo*()>>& InFunctionInfoFunction
#endif
) -> FClassBuilder&
{
	auto FunctionPointer = TFunctionPointer<decltype(InMethod)>(InMethod);

	return Function(InName,
	                InName,
	                FunctionPointer.Value.Pointer
#if WITH_FUNCTION_INFO
	                , InFunctionInfoFunction
#endif
	);
}

template <typename T, typename U>
auto FClassBuilder::Property(const FString& InName,
                             T InGetMethod,
                             U InSetMethod
#if WITH_PROPERTY_INFO
                             , const TOptional<TFunction<FTypeInfo*()>>& InTypeInfoFunction
#endif
) -> FClassBuilder&
{
	auto GetFunctionPointer = TFunctionPointer<decltype(InGetMethod)>(InGetMethod);

	auto SetFunctionPointer = TFunctionPointer<decltype(InSetMethod)>(InSetMethod);

#if WITH_PROPERTY_INFO
	if (InTypeInfoFunction.IsSet())
	{
		ClassRegister->BindingProperty(InName,
		                               GetFunctionPointer.Value.Pointer,
		                               SetFunctionPointer.Value.Pointer,
		                               InTypeInfoFunction
		);
	}
#endif

	return Function(BINDING_PROPERTY_GET + InName, GetFunctionPointer.Value.Pointer).
		Function(BINDING_PROPERTY_SET + InName, SetFunctionPointer.Value.Pointer);
}

template <typename T>
auto FClassBuilder::Function(const FString& InImplementationName, const TFunctionPointer<T>& InMethod)
{
	ClassRegister->BindingMethod(InImplementationName, InMethod.Value.Pointer);
}
