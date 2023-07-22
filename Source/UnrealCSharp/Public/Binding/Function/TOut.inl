#pragma once

#include "CoreMacro/NamespaceMacro.h"
#include "Macro/ClassMacro.h"
#include "Macro/FunctionMacro.h"
#include "Environment/FCSharpEnvironment.h"

template <typename Type>
struct TOut
{
	explicit TOut(MonoObject** InOutValue, Type& InArgument):
		OutValue(InOutValue),
		Argument(InArgument)
	{
	}

	template <SIZE_T Index>
	static void Get()
	{
	}

	template <SIZE_T Index, typename T, typename... Args>
	void Get()
	{
		if (Argument.template Get<Index>().IsOut())
		{
			const auto FoundObjectListClass = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_From_Name(
				COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_OBJECT_LIST);

			if (*OutValue == nullptr)
			{
				*OutValue = FCSharpEnvironment::GetEnvironment().GetDomain()->Object_New(FoundObjectListClass);
			}

			const auto FoundAddMethod = FCSharpEnvironment::GetEnvironment().GetDomain()->Class_Get_Method_From_Name(
				FoundObjectListClass, FUNCTION_OBJECT_LIST_ADD, 1);

			auto Value = static_cast<void*>(Argument.template Get<Index>().Set());

			FCSharpEnvironment::GetEnvironment().GetDomain()->Runtime_Invoke(FoundAddMethod, *OutValue, &Value);
		}

		Get<Index + 1, Args...>();
	}

private:
	MonoObject** OutValue;

	Type& Argument;
};
