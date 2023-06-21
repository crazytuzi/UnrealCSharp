#pragma once

#include "FTypeInfo.h"
#include "Binding/TypeInfo/TNameSpace.inl"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "CoreMacro/ClassMacro.h"
#include "Template/TTemplateTypeTraits.inl"
#include "Template/TIsTScriptInterface.inl"
#include "Template/TIsTWeakObjectPtr.inl"
#include "Template/TIsTLazyObjectPtr.inl"

template <typename T, typename Enable = void>
struct TTypeInfo
{
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, uint8>::Value, T>::Type>
{
private:
	struct FInner final : FPrimitiveTypeInfo
	{
		virtual FString GetClass() const override
		{
			return TEXT("Byte");
		}
	};

public:
	static FTypeInfo* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, uint16>::Value, T>::Type>
{
private:
	struct FInner final : FPrimitiveTypeInfo
	{
		virtual FString GetClass() const override
		{
			return TEXT("UInt16");
		}
	};

public:
	static FTypeInfo* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, uint32>::Value, T>::Type>
{
private:
	struct FInner final : FPrimitiveTypeInfo
	{
		virtual FString GetClass() const override
		{
			return TEXT("UInt32");
		}
	};

public:
	static FTypeInfo* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, uint64>::Value, T>::Type>
{
private:
	struct FInner final : FPrimitiveTypeInfo
	{
		virtual FString GetClass() const override
		{
			return TEXT("UInt64");
		}
	};

public:
	static FTypeInfo* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, int8>::Value, T>::Type>
{
private:
	struct FInner final : FPrimitiveTypeInfo
	{
		virtual FString GetClass() const override
		{
			return TEXT("SByte");
		}
	};

public:
	static FTypeInfo* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, int16>::Value, T>::Type>
{
private:
	struct FInner final : FPrimitiveTypeInfo
	{
		virtual FString GetClass() const override
		{
			return TEXT("Int16");
		}
	};

public:
	static FTypeInfo* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, int32>::Value, T>::Type>
{
private:
	struct FInner final : FPrimitiveTypeInfo
	{
		virtual FString GetClass() const override
		{
			return TEXT("Int32");
		}
	};

public:
	static FTypeInfo* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, int64>::Value, T>::Type>
{
private:
	struct FInner final : FPrimitiveTypeInfo
	{
		virtual FString GetClass() const override
		{
			return TEXT("Int64");
		}
	};

public:
	static FTypeInfo* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, bool>::Value, T>::Type>
{
private:
	struct FInner final : FPrimitiveTypeInfo
	{
		virtual FString GetClass() const override
		{
			return TEXT("Boolean");
		}
	};

public:
	static FTypeInfo* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, float>::Value, T>::Type>
{
private:
	class FInner final : public FPrimitiveTypeInfo
	{
	public:
		virtual FString GetClass() const override
		{
			return TEXT("Single");
		}
	};

public:
	static FTypeInfo* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TAnd<
	                                       TIsDerivedFrom<typename TRemovePointer<T>::Type, UObject>,
	                                       TNot<TIsSame<typename TRemovePointer<T>::Type, UClass>>>::Value, T>
                 ::Type>
{
private:
	struct FInner final : FTypeInfo
	{
		virtual FString GetClass() const override
		{
			return FUnrealCSharpFunctionLibrary::GetFullClass(TRemovePointer<T>::Type::StaticClass());
		}

		virtual FNameSpace* GetNameSpace() const override
		{
			return TNameSpace<T, T>::Get();
		}
	};

public:
	static FTypeInfo* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, FName>::Value, T>::Type>
{
private:
	struct FInner final : FCommonTypeInfo
	{
		virtual FString GetClass() const override
		{
			return CLASS_F_NAME;
		}
	};

public:
	static FTypeInfo* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsTScriptInterface<T>::Value, T>::Type>
{
private:
	struct FInner final : FTypeInfo
	{
		virtual FString GetClass() const override
		{
			return FString::Printf(TEXT(
				"TScriptInterface<%s>"
			),
			                       *FUnrealCSharpFunctionLibrary::GetFullInterface(
				                       TTemplateTypeTraits<T>::Type::UClassType::StaticClass())
			);
		}

		virtual FNameSpace* GetNameSpace() const override
		{
			return TNameSpace<T, T>::Get();
		}
	};

public:
	static FTypeInfo* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, FString>::Value, T>::Type>
{
private:
	struct FInner final : FCommonTypeInfo
	{
		virtual FString GetClass() const override
		{
			return CLASS_F_STRING;
		}
	};

public:
	static FTypeInfo* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, FText>::Value, T>::Type>
{
private:
	struct FInner final : FCommonTypeInfo
	{
		virtual FString GetClass() const override
		{
			return CLASS_F_TEXT;
		}
	};

public:
	static FTypeInfo* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsTWeakObjectPtr<T>::Value, T>::Type>
{
private:
	struct FInner final : FTypeInfo
	{
		virtual FString GetClass() const override
		{
			return FString::Printf(TEXT(
				"TWeakObjectPtr<%s>"
			),
			                       *FUnrealCSharpFunctionLibrary::GetFullClass(
				                       TTemplateTypeTraits<T>::Type < 0 > ::StaticClass())
			);
		}

		virtual FNameSpace* GetNameSpace() const override
		{
			return TNameSpace<T, T>::Get();
		}
	};

public:
	static FTypeInfo* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsTLazyObjectPtr<T>::Value, T>::Type>
{
private:
	struct FInner final : FTypeInfo
	{
		virtual FString GetClass() const override
		{
			return FString::Printf(TEXT(
				"TLazyObjectPtr<%s>"
			),
			                       *FUnrealCSharpFunctionLibrary::GetFullClass(
				                       TTemplateTypeTraits<T>::Type::StaticClass())
			);
		}

		virtual FNameSpace* GetNameSpace() const override
		{
			return TNameSpace<T, T>::Get();
		}
	};

public:
	static FTypeInfo* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<T, double>::Value, T>::Type>
{
private:
	class FInner final : public FPrimitiveTypeInfo
	{
	public:
		virtual FString GetClass() const override
		{
			return TEXT("Double");
		}
	};

public:
	static FTypeInfo* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsTSubclassOf<T>::Value, T>::Type>
{
private:
	struct FInner final : FTypeInfo
	{
		virtual FString GetClass() const override
		{
			return FString::Printf(TEXT(
				"TSubclassOf<%s>"
			),
			                       *FUnrealCSharpFunctionLibrary::GetFullClass(
				                       TTemplateTypeTraits<T>::Type::StaticClass())
			);
		}

		virtual FNameSpace* GetNameSpace() const override
		{
			return TNameSpace<T, T>::Get();
		}
	};

public:
	static FTypeInfo* Get()
	{
		static FInner Instance;

		return &Instance;
	}
};

template <typename T>
struct TTypeInfo<T, typename TEnableIf<TIsSame<typename TRemovePointer<T>::Type, UClass>::Value, T>::Type> :
	TTypeInfo<TSubclassOf<UObject>, TSubclassOf<UObject>>
{
};
