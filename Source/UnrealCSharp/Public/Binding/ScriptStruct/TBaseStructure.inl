#pragma once

#include "MaterialExpressionIO.h"
#include "Macro/BindingMacro.h"
#include "UEVersion.h"

static UScriptStruct* StaticGetBaseStructureInternal(const FName& Name)
{
	static auto CoreUObjectPkg = FindObjectChecked<UPackage>(nullptr, TEXT("/Script/CoreUObject"));

	const auto Result = static_cast<UScriptStruct*>(StaticFindObjectFast(
#if UE_STATIC_FIND_OBJECT_FAST_ANY_PACKAGE
		UScriptStruct::StaticClass(), CoreUObjectPkg, Name, false, false, RF_NoFlags, EInternalObjectFlags::None));
#else
		UScriptStruct::StaticClass(), CoreUObjectPkg, Name,
#if STATIC_FIND_OBJECT_FAST_E_FIND_OBJECT_FLAGS
		EFindObjectFlags::None,
#else
		false,
#endif
		RF_NoFlags, EInternalObjectFlags::None));
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

#if UE_T_BASE_STRUCTURE_F_FRAME_RATE
template <>
struct TBaseStructure<FFrameRate>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FFrameRate));
	}
};
#endif

template <>
struct TBaseStructure<FDirectoryPath>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FDirectoryPath));
	}
};

#if UE_T_BASE_STRUCTURE_F_INTERP_CURVE_VECTOR
template <>
struct TBaseStructure<FInterpCurveVector>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FInterpCurveVector));
	}
};
#endif

#if UE_T_BASE_STRUCTURE_F_INTERP_CURVE_QUAT
template <>
struct TBaseStructure<FInterpCurveQuat>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FInterpCurveQuat));
	}
};
#endif

#if UE_T_BASE_STRUCTURE_F_INTERP_CURVE_FLOAT
template <>
struct TBaseStructure<FInterpCurveFloat>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FInterpCurveFloat));
	}
};
#endif

#if UE_T_BASE_STRUCTURE_F_INTERP_CURVE_VECTOR_2D
template <>
struct TBaseStructure<FInterpCurveVector2D>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FInterpCurveVector2D));
	}
};
#endif

#if UE_T_BASE_STRUCTURE_F_INTERP_CURVE_TWO_VECTORS
template <>
struct TBaseStructure<FInterpCurveTwoVectors>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FInterpCurveTwoVectors));
	}
};
#endif

#if UE_T_BASE_STRUCTURE_F_INTERP_CURVE_LINEAR_COLOR
template <>
struct TBaseStructure<FInterpCurveLinearColor>
{
	static auto Get()
	{
		return StaticGetBaseStructureInternal(*BINDING_REMOVE_PREFIX_CLASS_STR(FInterpCurveLinearColor));
	}
};
#endif

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
