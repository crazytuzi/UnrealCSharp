#pragma once

#include "FNameSpace.h"
#include "CoreMacro/ClassMacro.h"
#include "Template/TIsTScriptInterface.inl"
#include "Template/TIsTWeakObjectPtr.inl"
#include "Template/TIsTLazyObjectPtr.inl"
#include "Template/TIsTSoftObjectPtr.inl"
#include "Template/TIsTSoftClassPtr.inl"
#include "Template/TIsTSubclassOf.inl"
#include "Template/TIsTSet.inl"
#include "Template/TIsTMap.inl"

template <typename T, typename Enable = void>
struct TGeneric
{
};

struct FGenericNameSpace
{
	static FString GetNameSpace()
	{
		return FCommonNameSpace::Get()[0];
	}
};

template <typename T>
struct TGeneric<T, std::enable_if_t<TIsTScriptInterface<std::decay_t<T>>::Value, T>> :
	FGenericNameSpace
{
	static FString GetTemplateName()
	{
		return TEMPLATE_T_SCRIPT_INTERFACE;
	}

	static FString GetGenericName()
	{
		return GENERIC_T_SCRIPT_INTERFACE;
	}
};

template <typename T>
struct TGeneric<T, std::enable_if_t<TIsTWeakObjectPtr<std::decay_t<T>>::Value, T>> :
	FGenericNameSpace
{
	static FString GetTemplateName()
	{
		return TEMPLATE_T_WEAK_OBJECT_PTR;
	}

	static FString GetGenericName()
	{
		return GENERIC_T_WEAK_OBJECT_PTR;
	}
};

template <typename T>
struct TGeneric<T, std::enable_if_t<TIsTLazyObjectPtr<std::decay_t<T>>::Value, T>> :
	FGenericNameSpace
{
	static FString GetTemplateName()
	{
		return TEMPLATE_T_LAZY_OBJECT_PTR;
	}

	static FString GetGenericName()
	{
		return GENERIC_T_LAZY_OBJECT_PTR;
	}
};

template <typename T>
struct TGeneric<T, std::enable_if_t<TIsTSoftObjectPtr<std::decay_t<T>>::Value, T>> :
	FGenericNameSpace
{
	static FString GetTemplateName()
	{
		return TEMPLATE_T_SOFT_OBJECT_PTR;
	}

	static FString GetGenericName()
	{
		return GENERIC_T_SOFT_OBJECT_PTR;
	}
};

template <typename T>
struct TGeneric<T, std::enable_if_t<TIsTMap<std::decay_t<T>>::Value, T>> :
	FGenericNameSpace
{
	static FString GetTemplateName()
	{
		return TEMPLATE_T_MAP;
	}

	static FString GetGenericName()
	{
		return GENERIC_T_MAP;
	}
};

template <typename T>
struct TGeneric<T, std::enable_if_t<TIsTSet<std::decay_t<T>>::Value, T>> :
	FGenericNameSpace
{
	static FString GetTemplateName()
	{
		return TEMPLATE_T_SET;
	}

	static FString GetGenericName()
	{
		return GENERIC_T_SET;
	}
};

template <typename T>
struct TGeneric<T, std::enable_if_t<TIsTSubclassOf<std::decay_t<T>>::Value, T>> :
	FGenericNameSpace
{
	static FString GetTemplateName()
	{
		return TEMPLATE_T_SUB_CLASS_OF;
	}

	static FString GetGenericName()
	{
		return GENERIC_T_SUB_CLASS_OF;
	}
};

template <typename T>
struct TGeneric<T, std::enable_if_t<TIsTArray<std::decay_t<T>>::Value, T>> :
	FGenericNameSpace
{
	static FString GetTemplateName()
	{
		return TEMPLATE_T_ARRAY;
	}

	static FString GetGenericName()
	{
		return GENERIC_T_ARRAY;
	}
};

template <typename T>
struct TGeneric<T, std::enable_if_t<TIsTSoftClassPtr<std::decay_t<T>>::Value, T>> :
	FGenericNameSpace
{
	static FString GetTemplateName()
	{
		return TEMPLATE_T_SOFT_CLASS_PTR;
	}

	static FString GetGenericName()
	{
		return GENERIC_T_SOFT_CLASS_PTR;
	}
};
