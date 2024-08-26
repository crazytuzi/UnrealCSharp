#pragma once

#include <iomanip>
#include <sstream>

inline FString SanitizeFloat(const double InFloat, const int32 InMinFractionalDigits = 1)
{
	std::stringstream StringStream;

	StringStream << std::fixed << std::setprecision(std::numeric_limits<float>::max_digits10) << InFloat;

	FString TempString = StringStream.str().c_str();

	int32 TrimIndex = INDEX_NONE;

	int32 DecimalSeparatorIndex = INDEX_NONE;

	for (auto CharIndex = TempString.Len() - 1; CharIndex >= 0; --CharIndex)
	{
		const auto Char = TempString[CharIndex];

		if (Char == TEXT('.'))
		{
			DecimalSeparatorIndex = CharIndex;

			TrimIndex = FMath::Max(TrimIndex, DecimalSeparatorIndex);

			break;
		}

		if (TrimIndex == INDEX_NONE && Char != TEXT('0'))
		{
			TrimIndex = CharIndex + 1;
		}
	}

	TempString.RemoveAt(TrimIndex, TempString.Len() - TrimIndex, false);

	if (InMinFractionalDigits > 0)
	{
		if (TrimIndex == DecimalSeparatorIndex)
		{
			TempString.AppendChar(TEXT('.'));
		}

		const auto NumFractionalDigits = TempString.Len() - DecimalSeparatorIndex - 1;

		if (const auto FractionalDigitsToPad = InMinFractionalDigits - NumFractionalDigits;
			FractionalDigitsToPad > 0)
		{
			TempString.Reserve(TempString.Len() + FractionalDigitsToPad);

			for (auto Cx = 0; Cx < FractionalDigitsToPad; ++Cx)
			{
				TempString.AppendChar(TEXT('0'));
			}
		}
	}

	return TempString;
}

template <typename T, typename Enable = void>
struct TDefaultArgument
{
};

template <typename T>
struct TEmptyDefaultArgument
{
	static auto Get(const T& InValue)
	{
		return FString{};
	}
};

template <typename T>
struct TDefaultArgumentBuilder
{
	template <auto Prefix>
	static auto GetImplementation()
	{
		return FString{};
	}

	template <auto Prefix, typename DefaultArgument, typename... Args>
	static auto GetImplementation(DefaultArgument InDefaultArgument, Args&&... InParams)
	{
		return Prefix +
			TDefaultArgument<DefaultArgument, DefaultArgument>::Get(InDefaultArgument) +
			GetImplementation<Comma>(InParams...);
	}

	template <typename... Args>
	static auto Get(Args&&... InDefaultArguments)
	{
		return FString::Printf(TEXT(
			"new %s(%s)"),
		                       *TName<T, T>::Get(),
		                       *GetImplementation<Space>(InDefaultArguments...)
		);
	}

	static constexpr char Space[] = "";

	static constexpr char Comma[] = " ,";
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint8>, T>>
{
	static auto Get(const uint8 InValue)
	{
		return FString::Printf(TEXT("%d"), InValue);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint16>, T>>
{
	static auto Get(const uint16 InValue)
	{
		return FString::Printf(TEXT("%d"), InValue);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint32>, T>>
{
	static auto Get(const uint32 InValue)
	{
		return FString::Printf(TEXT("%d"), InValue);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, uint64>, T>>
{
	static auto Get(const uint64 InValue)
	{
		return FString::Printf(TEXT("%lld"), InValue);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int8>, T>>
{
	static auto Get(const int8 InValue)
	{
		return FString::Printf(TEXT("%d"), InValue);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int16>, T>>
{
	static auto Get(const int16 InValue)
	{
		return FString::Printf(TEXT("%d"), InValue);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int32>, T>>
{
	static auto Get(const int32 InValue)
	{
		return FString::Printf(TEXT("%d"), InValue);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, int64>, T>>
{
	static auto Get(const int64 InValue)
	{
		return FString::Printf(TEXT("%lld"), InValue);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, bool>, T>>
{
	static auto Get(const bool InValue)
	{
		return InValue ? TEXT("true") : TEXT("false");
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, float>, T>>
{
	static auto Get(const float InValue)
	{
		return FString::Printf(TEXT("%sf"), *SanitizeFloat(InValue));
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_base_of_v<UObject, std::remove_pointer_t<std::decay_t<T>>>, T>> :
	TEmptyDefaultArgument<T>
{
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<TIsTObjectPtr<std::decay_t<T>>::Value, T>> :
	TEmptyDefaultArgument<T>
{
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FName>, T>>
{
	static auto Get(const FName& InValue)
	{
		return FString::Printf(TEXT(
			"new %s(\"%s\")"),
		                       *TName<T, T>::Get(),
		                       *InValue.ToString()
		);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<TIsIInterface<std::decay_t<T>>::Value, T>> :
	TEmptyDefaultArgument<T>
{
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<TIsTScriptInterface<std::decay_t<T>>::Value, T>> :
	TEmptyDefaultArgument<T>
{
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<TIsUStruct<std::decay_t<T>>::Value, T>> :
	TEmptyDefaultArgument<T>
{
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FString>, T>>
{
	static auto Get(const FString& InValue)
	{
		return FString::Printf(TEXT(
			"new %s(\"%s\")"),
		                       *TName<T, T>::Get(),
		                       *InValue
		);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FText>, T>>
{
	static auto Get(const FText& InValue)
	{
		return FString::Printf(TEXT(
			"new %s(\"%s\")"),
		                       *TName<T, T>::Get(),
		                       *InValue.ToString()
		);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<TIsTWeakObjectPtr<std::decay_t<T>>::Value, T>> :
	TEmptyDefaultArgument<T>
{
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<TIsTLazyObjectPtr<std::decay_t<T>>::Value, T>> :
	TEmptyDefaultArgument<T>
{
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<TIsTSoftObjectPtr<std::decay_t<T>>::Value, T>> :
	TEmptyDefaultArgument<T>
{
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, double>, T>>
{
	static auto Get(const double InValue)
	{
		return SanitizeFloat(InValue);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FRotator>, T>>
{
	static auto Get(const FRotator& InValue)
	{
		return TDefaultArgumentBuilder<T>::Get(InValue.Pitch, InValue.Yaw, InValue.Roll);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FQuat>, T>>
{
	static auto Get(const FQuat& InValue)
	{
		return TDefaultArgumentBuilder<T>::Get(InValue.X, InValue.Y, InValue.Z, InValue.W);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FVector>, T>>
{
	static auto Get(const FVector& InValue)
	{
		return TDefaultArgumentBuilder<T>::Get(InValue.X, InValue.Y, InValue.Z);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FTransform>, T>>
{
	static auto Get(const FTransform& InValue)
	{
		return TDefaultArgumentBuilder<T>::Get(InValue.GetRotation(), InValue.GetTranslation(), InValue.GetScale3D());
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FLinearColor>, T>>
{
	static auto Get(const FLinearColor& InValue)
	{
		return TDefaultArgumentBuilder<T>::Get(InValue.R, InValue.G, InValue.B, InValue.A);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FColor>, T>>
{
	static auto Get(const FColor& InValue)
	{
		return TDefaultArgumentBuilder<T>::Get(InValue.R, InValue.G, InValue.B, InValue.A);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FPlane>, T>>
{
	static auto Get(const FPlane& InValue)
	{
		return TDefaultArgumentBuilder<T>::Get(InValue.X, InValue.Y, InValue.Z, InValue.W);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FVector2D>, T>>
{
	static auto Get(const FVector2D& InValue)
	{
		return TDefaultArgumentBuilder<T>::Get(InValue.X, InValue.Y);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FVector4>, T>>
{
	static auto Get(const FVector4& InValue)
	{
		return TDefaultArgumentBuilder<T>::Get(InValue.X, InValue.Y, InValue.Z, InValue.W);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FGuid>, T>>
{
	static auto Get(const FGuid& InValue)
	{
		return TDefaultArgumentBuilder<T>::Get(InValue.A, InValue.B, InValue.C, InValue.D);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<std::is_same_v<std::decay_t<T>, FBox2D>, T>>
{
	static auto Get(const FBox2D& InValue)
	{
		return TDefaultArgumentBuilder<T>::Get(InValue.Min, InValue.Max);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<TIsTSubclassOf<std::decay_t<T>>::Value, T>> :
	TEmptyDefaultArgument<T>
{
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<TIsEnum<std::decay_t<T>>::Value && !TIsNotUEnum<std::decay_t<T>>::Value, T>>
{
	static auto Get(const T& InValue)
	{
		return FString::Printf(TEXT(
			"%s.%s"
		),
		                       *StaticEnum<std::decay_t<T>>()->GetName(),
		                       *StaticEnum<std::decay_t<T>>()->GetNameStringByValue(static_cast<int64>(InValue))
		);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<TIsTEnumAsByte<std::decay_t<T>>::Value, T>>
{
	static auto Get(const T& InValue)
	{
		return FString::Printf(TEXT(
			"%s.%s"
		),
		                       *StaticEnum<typename std::decay_t<T>::EnumType>()->GetName(),
		                       *StaticEnum<typename std::decay_t<T>::EnumType>()->
		                       GetNameStringByValue(static_cast<int64>(InValue))
		);
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<TIsTSoftClassPtr<std::decay_t<T>>::Value, T>> :
	TEmptyDefaultArgument<T>
{
};

#if UE_F_OPTIONAL_PROPERTY
template <typename T>
struct TDefaultArgument<T, std::enable_if_t<TIsTOptional<std::decay_t<T>>::Value, T>> :
	TEmptyDefaultArgument<T>
{
};
#endif

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<TIsTMap<std::decay_t<T>>::Value, T>>
{
	static auto Get(const TMap<typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>,
	                           typename TTemplateTypeTraits<std::decay_t<T>>::template Type<1>>& InValue)
	{
		auto Value0 = FString::Printf(TEXT(
			"new %s{"),
		                              *TName<T, T>::Get()
		);

		auto bIsFirst = true;

		for (const auto& [Key, Value] : InValue)
		{
			Value0 += FString::Printf(TEXT(
				"%s{%s, %s}"),
			                          bIsFirst ? TEXT("") : TEXT(" ,"),
			                          *TDefaultArgument<
				                          typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>,
				                          typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>>
			                          ::Get(Key),
			                          *TDefaultArgument<
				                          typename TTemplateTypeTraits<std::decay_t<T>>::template Type<1>,
				                          typename TTemplateTypeTraits<std::decay_t<T>>::template Type<1>>
			                          ::Get(Value)
			);

			bIsFirst = false;
		}

		Value0 += TEXT("}");

		return Value0;
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<TIsTSet<std::decay_t<T>>::Value, T>>
{
	static auto Get(const TSet<typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>>& InValue)
	{
		auto Value = FString::Printf(TEXT(
			"new %s{"),
		                             *TName<T, T>::Get()
		);

		auto bIsFirst = true;

		for (const auto& Iterator : InValue)
		{
			Value += FString::Printf(TEXT(
				"%s%s"),
			                         bIsFirst ? TEXT("") : TEXT(" ,"),
			                         *TDefaultArgument<
				                         typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>,
				                         typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>>
			                         ::Get(Iterator)
			);

			bIsFirst = false;
		}

		Value += TEXT("}");

		return Value;
	}
};

template <typename T>
struct TDefaultArgument<T, std::enable_if_t<TIsTArray<std::decay_t<T>>::Value, T>>
{
	static auto Get(const TArray<typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>>& InValue)
	{
		auto Value = FString::Printf(TEXT(
			"new %s{"),
		                             *TName<T, T>::Get()
		);

		auto bIsFirst = true;

		for (const auto& Iterator : InValue)
		{
			Value += FString::Printf(TEXT(
				"%s%s"),
			                         bIsFirst ? TEXT("") : TEXT(" ,"),
			                         *TDefaultArgument<
				                         typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>,
				                         typename TTemplateTypeTraits<std::decay_t<T>>::template Type<0>>
			                         ::Get(Iterator)
			);

			bIsFirst = false;
		}

		Value += TEXT("}");

		return Value;
	}
};
