#pragma once

#include "TPropertyGetClass.h"
#include "Environment/FCSharpEnvironment.h"

template <typename Class, typename Result, Result Class::* Member>
class TPrimitivePropertyBuilder
{
public:
	static void Get(const MonoObject* InMonoObject, MonoObject** OutValue)
	{
		if (auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			*OutValue = FCSharpEnvironment::GetEnvironment().GetDomain()->Value_Box(
				(FCSharpEnvironment::GetEnvironment().GetDomain()->*TPropertyGetClass<Result>::GetClass)(),
				&(FoundObject->*Member));
		}
	}

	static void Set(const MonoObject* InMonoObject, MonoObject* InValue)
	{
		if (auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			FoundObject->*Member = *(Result*)FCSharpEnvironment::GetEnvironment().GetDomain()->
				Object_Unbox(InValue);
		}
	}
};

template <typename Class, typename Result, Result Class::* Member>
class TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, int32>::Value>::type> :
	public TPrimitivePropertyBuilder<Class, int32, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
class TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsSame<Result, float>::Value>::type> :
	public TPrimitivePropertyBuilder<Class, float, Member>
{
};

template <typename Class, typename Result, Result Class::* Member>
class TPropertyBuilder<Result Class::*, Member, typename TEnableIf<TIsDerivedFrom<Result, UObject*>::Value>::type>
{
public:
	static void Get(const MonoObject* InMonoObject, MonoObject** OutValue)
	{
		if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			*OutValue = FCSharpEnvironment::GetEnvironment().Bind(FoundObject->*Member);
		}
	}

	static void Set(const MonoObject* InMonoObject, const MonoObject* InValue)
	{
		if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject<Class>(InMonoObject))
		{
			FoundObject->*Member = FCSharpEnvironment::GetEnvironment().GetObject
				<typename TRemovePointer<Result>::Type>(InValue);
		}
	}
};
