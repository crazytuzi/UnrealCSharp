#include "Binding/Class/FBindingClassRegister.h"
#include "Binding/FBinding.h"
#include "CoreMacro/BindingMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CppVersion.h"

FBindingClassRegister::FBindingClassRegister(const TFunction<FString()>& InClassFunction,
                                             const FString& InImplementationNameSpace,
                                             const TFunction<bool()>& InIsProjectClassFunction,
                                             const bool InIsReflectionClass,
                                             const TOptional<TFunction<FTypeInfo*()>>& InTypeInfoFunction):
	ClassFunction(InClassFunction),
	ImplementationNameSpace(COMBINE_NAMESPACE(NAMESPACE_ROOT, InImplementationNameSpace)),
	IsProjectClassFunction(InIsProjectClassFunction),
	bIsReflectionClass(InIsReflectionClass),
	TypeInfoRegister{InTypeInfoFunction}
{
}

FBindingClassRegister::operator FBindingClass*() const
{
	TArray<FBindingProperty> Properties;

	TArray<FBindingFunction> Functions;

	TArray<FBindingMethod> Methods;

#if WITH_PROPERTY_INFO
	for (const auto& Property : PropertyRegisters)
	{
		Properties.Emplace(FBindingProperty(Property));
	}
#endif

#if WITH_FUNCTION_INFO
	for (const auto& Function : FunctionRegisters)
	{
		Functions.Emplace(FBindingFunction(Function));
	}
#endif

	for (const auto& Method : MethodRegisters)
	{
		Methods.Emplace(FBindingMethod(Method));
	}

	return new FBindingClass(BaseClassFunction.IsSet() ? BaseClassFunction.GetValue()() : FString(),
	                         ClassFunction(),
	                         ImplementationNameSpace,
	                         IsProjectClassFunction(),
	                         bIsReflectionClass,
	                         FBindingTypeInfo(TypeInfoRegister),
	                         FBindingSubscript(SubscriptRegister),
	                         Properties,
	                         Functions,
	                         Methods
	);
}

FString FBindingClassRegister::GetClass() const
{
	return ClassFunction();
}

bool FBindingClassRegister::IsReflectionClass() const
{
	return bIsReflectionClass;
}

void FBindingClassRegister::BindingSubscript(const FString& InName,
                                             const FString& InGetImplementationName,
                                             const FString& InSetImplementationName,
                                             const TOptional<TFunction<FFunctionInfo*()>>& InFunctionInfoFunction)
{
	SubscriptRegister = FBindingSubscriptRegister(InName,
	                                              InName,
	                                              InFunctionInfoFunction,
	                                              InGetImplementationName,
	                                              InSetImplementationName);
}

void FBindingClassRegister::BindingProperty(const FString& InName,
                                            const void* InGetMethod,
                                            const void* InSetMethod,
                                            const TOptional<TFunction<FTypeInfo*()>>& InTypeInfoFunction)
{
	PropertyRegisters.Emplace(
		InTypeInfoFunction,
		InName,
		static_cast<EBindingPropertyAccess>(
			static_cast<int32>((InGetMethod != nullptr
				                    ? EBindingPropertyAccess::OnlyRead
				                    : EBindingPropertyAccess::None)) +
			static_cast<int32>(InSetMethod != nullptr
				                   ? EBindingPropertyAccess::OnlyWrite
				                   : EBindingPropertyAccess::None))
	);
}

void FBindingClassRegister::BindingFunction(const FString& InName,
                                            const FString& InImplementationName,
                                            const TOptional<TFunction<FFunctionInfo*()>>& InFunctionInfoFunction)
{
	FunctionRegisters.Emplace(
		InName,
		InImplementationName,
		InFunctionInfoFunction
	);
}

void FBindingClassRegister::BindingMethod(const FString& InImplementationName, const void* InFunction)
{
#if STD_CPP_20
	MethodRegisters.Emplace([=, this]()
#else
	MethodRegisters.Emplace([=]()
#endif
	                        {
		                        return BINDING_COMBINE_CLASS(
				                        ImplementationNameSpace,
				                        BINDING_COMBINE_CLASS_IMPLEMENTATION(GetClass())) +
			                        BINDING_COMBINE_FUNCTION(
				                        BINDING_COMBINE_FUNCTION_IMPLEMENTATION(GetClass(),
					                        InImplementationName));
	                        },
	                        InFunction);
}

void FBindingClassRegister::Inheritance(const TFunction<FString()>& InBaseClassFunction,
                                        const FString& InImplementationNameSpace,
                                        const TFunction<bool()>& InIsProjectClassFunction,
                                        const bool InIsReflectionClass,
                                        const TOptional<TFunction<FTypeInfo*()>>& InTypeInfoFunction)
{
	BaseClassFunction = InBaseClassFunction;

	FBinding::Get().Register(InBaseClassFunction,
	                         InImplementationNameSpace,
	                         InIsProjectClassFunction,
	                         InIsReflectionClass,
	                         InTypeInfoFunction);
}
