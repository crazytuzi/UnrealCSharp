#pragma once

#include "Environment/FCSharpEnvironment.h"
#include "Domain/Script/IManagedHandle.h"
#include "Domain/FDomain.h"
#include "Binding/Property/TPropertyBuilder.inl"
#include "Binding/TypeInfo/TIsPrimitive.inl"
#include "Binding/Core/TPropertyValue.inl"
#include "Reflection/FReflectionRegistry.h"

template <typename>
struct TMethodHelper
{
};

template <typename Result, typename... Args>
struct TMethodHelper<std::tuple<Result, std::tuple<Args...>>>
{
public:
	template <typename Class>
	static auto Call(Class* InObject, const FString& InName, Args&&... InArgs)
	{
		IManagedHandle Object{};

		FClassReflection* ClassReflection{};

		if (InObject == nullptr)
		{
			ClassReflection = FReflectionRegistry::Get().GetClass<Class>();
		}
		else if constexpr (TIsUObject<Class>::Value)
		{
			Object = FCSharpEnvironment::GetEnvironment().GetObject(InObject);

			if (!IManagedHandleIsValid(Object))
			{
				return DefaultReturn();
			}

			ClassReflection = FReflectionRegistry::Get().GetClass(InObject->GetClass());
		}
		else
		{
			Object = FCSharpEnvironment::GetEnvironment().GetBinding(InObject);

			if (!IManagedHandleIsValid(Object))
			{
				return DefaultReturn();
			}

			ClassReflection = FReflectionRegistry::Get().GetClass<Class>();
		}

		if (ClassReflection == nullptr)
		{
			return DefaultReturn();
		}

		const auto Method = ClassReflection->GetParentMethod(InName, static_cast<int32>(sizeof...(Args)));

		if (Method == nullptr)
		{
			return DefaultReturn();
		}

		constexpr auto Size = static_cast<int32>(sizeof...(Args));

		constexpr auto ArraySize = Size > 0 ? Size : 1;

		IManagedHandle ManagedHandles[ArraySize] = {};

		IManagedHandle ShadowManagedHandles[ArraySize] = {};

		void* Params[ArraySize] = {};

		auto ShadowArgs = std::tuple<std::decay_t<Args>...>(std::forward<Args>(InArgs)...);

		ArgumentToParams(std::index_sequence_for<Args...>{}, ShadowArgs, ManagedHandles, ShadowManagedHandles, Params);

		const auto ReturnValue = Method->Runtime_Invoke(Object, Size > 0 ? Params : nullptr);

		if constexpr (Size > 0)
		{
			GetReferenceValue(std::index_sequence_for<Args...>{}, std::tie(InArgs...), ShadowArgs,
			                  ManagedHandles, ShadowManagedHandles);
		}

		if constexpr (!std::is_void_v<Result>)
		{
			auto Value = TPropertyValue<Result, Result>::Get(ReturnValue);

			FDomain::GCHandle_Free(ReturnValue);

			return Value;
		}
	}

private:
	template <auto... Index>
	static void ArgumentToParams(std::index_sequence<Index...>,
	                             std::tuple<std::decay_t<Args>...>& InShadowArgs,
	                             IManagedHandle* InManagedHandles,
	                             IManagedHandle* InShadowManagedHandles,
	                             void** InParams)
	{
		([&]
		{
			using Type = std::decay_t<std::tuple_element_t<Index, std::tuple<Args...>>>;

			if constexpr (TIsPrimitive<Type>::Value)
			{
				InParams[Index] = &std::get<Index>(InShadowArgs);
			}
			else
			{
				InManagedHandles[Index] = IManagedHandleFromObject(
					TPropertyBuilder<Type*, nullptr>::Get(std::get<Index>(InShadowArgs)));

				InShadowManagedHandles[Index] = InManagedHandles[Index];

				InParams[Index] = &InManagedHandles[Index];
			}
		}(), ...);
	}

	template <auto... Index, typename ArgsTuple>
	static void GetReferenceValue(std::index_sequence<Index...>,
	                              ArgsTuple InArgs,
	                              std::tuple<std::decay_t<Args>...>& InShadowArgs,
	                              IManagedHandle* InManagedHandles,
	                              IManagedHandle* InShadowManagedHandles
	)
	{
		([&]
		{
			using Type = std::tuple_element_t<Index, std::tuple<Args...>>;

			if constexpr (std::is_lvalue_reference_v<Type> &&
				!std::is_const_v<std::remove_reference_t<Type>>)
			{
				if constexpr (TIsPrimitive<Type>::Value)
				{
					std::get<Index>(InArgs) = std::get<Index>(InShadowArgs);
				}
				else if (InManagedHandles[Index] != InShadowManagedHandles[Index])
				{
					std::get<Index>(InArgs) = TPropertyValue<Type, Type>::Get(InManagedHandles[Index]);
				}
			}
		}(), ...);
	}

	static auto DefaultReturn()
	{
		if constexpr (!std::is_void_v<Result>)
		{
			return Result{};
		}
	}
};
