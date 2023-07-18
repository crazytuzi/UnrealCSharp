#pragma once

template <class T>
struct TClassFullName
{
	static FString Get()
	{
		return FString::Printf(TEXT(
			"%s%s"
		),
		                       T::StaticClass()->GetPrefixCPP(),
		                       *T::StaticClass()->GetName());
	}
};
