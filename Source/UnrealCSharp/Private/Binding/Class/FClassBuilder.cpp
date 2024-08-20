#include "Binding/Class/FClassBuilder.h"
#include "Binding/FBinding.h"
#include "Kismet/KismetStringLibrary.h"
#include "Algo/Count.h"

FClassBuilder::FClassBuilder(const TFunction<FString()>& InClassFunction,
                             const FString& InImplementationNameSpace,
                             const TFunction<bool()>& InIsProjectClassFunction,
                             const bool InIsReflectionClass,
                             const TOptional<TFunction<FTypeInfo*()>>& InTypeInfoFunction):
	ClassRegister(FBinding::Get().Register(InClassFunction,
	                                       InImplementationNameSpace,
	                                       InIsProjectClassFunction,
	                                       InIsReflectionClass,
	                                       InTypeInfoFunction))
{
}

FClassBuilder::FClassBuilder(const FString& InClass,
                             const FString& InImplementationNameSpace,
                             const bool InIsProjectClass,
                             const bool InIsReflectionClass,
                             const TOptional<TFunction<FTypeInfo*()>>& InTypeInfoFunction):
	FClassBuilder([InClass]() { return InClass; },
	              InImplementationNameSpace,
	              [InIsProjectClass]() { return InIsProjectClass; },
	              InIsReflectionClass,
	              InTypeInfoFunction)
{
}

FClassBuilder& FClassBuilder::Function(const FString& InName,
#if WITH_FUNCTION_INFO
                                       const TArray<TPair<void*, TFunction<FFunctionInfo*()>>>& InMethod
#else
                                       const TArray<void*>& InMethod
#endif
)
{
#if WITH_FUNCTION_INFO
	for (const auto& [Key, Value] : InMethod)
#else
	for (const auto& Elem : InMethod)
#endif
	{
		Function(InName,
#if WITH_FUNCTION_INFO
		         Key,
		         Value
#else
				 Elem
#endif
		);
	}

	return *this;
}

FClassBuilder& FClassBuilder::Function(const FString& InName,
                                       const FString& InImplementationName,
                                       const void* InMethod
#if WITH_FUNCTION_INFO
                                       , const TOptional<TFunction<FFunctionInfo*()>>& InFunctionInfoFunction
#endif
)
{
	const auto FunctionImplementationName = GetFunctionImplementationName(InName, InImplementationName);

	Functions.Add(InName);

#if WITH_FUNCTION_INFO
	if (InFunctionInfoFunction.IsSet())
	{
		ClassRegister->BindingFunction(InName, FunctionImplementationName, InFunctionInfoFunction);
	}
#endif

	Function(FunctionImplementationName, TFunctionPointer<decltype(InMethod)>(InMethod));

	return *this;
}

FString FClassBuilder::GetFunctionImplementationName(const FString& InName, const FString& InImplementationName) const
{
	const auto Count = Algo::Count(Functions, InName);

	return FString::Printf(TEXT(
		"%s%s"),
	                       *InImplementationName,
	                       Count == 0 ? TEXT("") : *UKismetStringLibrary::Conv_IntToString(Count)
	);
}
