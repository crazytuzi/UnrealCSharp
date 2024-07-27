#pragma once

#include "Macro/BindingMacro.h"
#include "UEVersion.h"

static UScriptStruct* StaticGetBaseStructureInternal(const FName& Name)
{
	static auto CoreUObjectPkg = FindObjectChecked<UPackage>(nullptr, TEXT("/Script/CoreUObject"));

	const auto Result = static_cast<UScriptStruct*>(StaticFindObjectFast(
#if UE_STATIC_FIND_OBJECT_FAST_ANY_PACKAGE
		UScriptStruct::StaticClass(), CoreUObjectPkg, Name, false, false, RF_NoFlags, EInternalObjectFlags::None));
#else
		UScriptStruct::StaticClass(), CoreUObjectPkg, Name, false, RF_NoFlags, EInternalObjectFlags::None));
#endif

#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
	if (Result == nullptr)
	{
		UE_LOG(LogClass, Fatal, TEXT("Failed to find native struct '%s.%s'"), *CoreUObjectPkg->GetName(),
		       *Name.ToString());
	}
#endif

	return Result;
}

#if UE_T_BASE_STRUCTURE_F_INT_POINT
template <>
struct TBaseStructure<FIntPoint>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FIntPoint));
	}
};
#endif

template <>
struct TBaseStructure<FTimespan>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FTimespan));
	}
};

template <>
struct TBaseStructure<FAssetBundleEntry>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FAssetBundleEntry));
	}
};

template <>
struct TBaseStructure<FBox>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FBox));
	}
};

template <>
struct TBaseStructure<FBoxSphereBounds>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FBoxSphereBounds));
	}
};

#if UE_T_BASE_STRUCTURE_F_INT_VECTOR
template <>
struct TBaseStructure<FIntVector>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FIntVector));
	}
};
#endif

template <>
struct TBaseStructure<FExpressionInput>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FExpressionInput));
	}
};

template <>
struct TBaseStructure<FExpressionOutput>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FExpressionOutput));
	}
};

template <>
struct TBaseStructure<FVector3f>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FVector3f));
	}
};

template <>
struct TBaseStructure<FVector4f>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FVector4f));
	}
};

template <>
struct TBaseStructure<FFrameRate>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FFrameRate));
	}
};

template <>
struct TBaseStructure<FDirectoryPath>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FDirectoryPath));
	}
};

template <>
struct TBaseStructure<FInterpCurveVector>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FInterpCurveVector));
	}
};

template <>
struct TBaseStructure<FInterpCurveQuat>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FInterpCurveQuat));
	}
};

template <>
struct TBaseStructure<FInterpCurveFloat>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FInterpCurveFloat));
	}
};

template <>
struct TBaseStructure<FInterpCurveVector2D>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FInterpCurveVector2D));
	}
};

template <>
struct TBaseStructure<FInterpCurveTwoVectors>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FInterpCurveTwoVectors));
	}
};

template <>
struct TBaseStructure<FInterpCurveLinearColor>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FInterpCurveLinearColor));
	}
};

template <>
struct TBaseStructure<FMaterialAttributesInput>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FMaterialAttributesInput));
	}
};

template <>
struct TBaseStructure<FColorMaterialInput>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FColorMaterialInput));
	}
};

template <>
struct TBaseStructure<FScalarMaterialInput>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FScalarMaterialInput));
	}
};

template <>
struct TBaseStructure<FVectorMaterialInput>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FVectorMaterialInput));
	}
};

template <>
struct TBaseStructure<FShadingModelMaterialInput>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FShadingModelMaterialInput));
	}
};

#if UE_T_BASE_STRUCTURE_F_STRATA_MATERIAL_INPUT
template <>
struct TBaseStructure<FStrataMaterialInput>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FStrataMaterialInput));
	}
};
#endif
