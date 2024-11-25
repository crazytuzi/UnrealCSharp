﻿#pragma once

#include "Misc/EngineVersionComparison.h"

#define UE_VERSION_START(MajorVersion, MinorVersion, PatchVersion) \
	UE_GREATER_SORT(ENGINE_MAJOR_VERSION, MajorVersion, UE_GREATER_SORT(ENGINE_MINOR_VERSION, MinorVersion, UE_GREATER_SORT(ENGINE_PATCH_VERSION, PatchVersion, true)))

#define UE_T_BASE_STRUCTURE_F_INT_POINT !UE_VERSION_START(5, 1, 0)

#define UE_T_BASE_STRUCTURE_F_INT_VECTOR !UE_VERSION_START(5, 1, 0)

#define UE_CLASS_ADD_REFERENCED_OBJECTS !UE_VERSION_START(5, 1, 0)

#define UE_STATIC_FIND_OBJECT_FAST_ANY_PACKAGE !UE_VERSION_START(5, 1, 0)

#define UE_GUID_TO_STRING !UE_VERSION_START(5, 1, 0)

#define UE_DATETIME_PLUS !UE_VERSION_START(5, 1, 0)

#define UE_VECTOR2_LESS !UE_VERSION_START(5, 1, 0)

#define UE_VECTOR2_GREATER !UE_VERSION_START(5, 1, 0)

#define UE_VECTOR2_LESS_EQUAL !UE_VERSION_START(5, 1, 0)

#define UE_VECTOR2_GREATER_EQUAL !UE_VERSION_START(5, 1, 0)

#define UE_SOFT_OBJECT_PATH_CONSTRUCTOR_F_NAME !UE_VERSION_START(5, 1, 0)

#define UE_SOFT_OBJECT_PATH_CONSTRUCTOR_F_NAME_F_STRING !UE_VERSION_START(5, 1, 0)

#define UE_SOFT_OBJECT_PATH_SET_PATH_F_NAME !UE_VERSION_START(5, 1, 0)

#define UE_SOFT_OBJECT_PATH_SET_ASSET_PATH_NAME !UE_VERSION_START(5, 1, 0)

#define UE_ASSET_BUNDLE_DATA_ADD_BUNDLE_ASSET !UE_VERSION_START(5, 1, 0)

#define UE_ASSET_BUNDLE_DATA_ADD_BUNDLE_ASSETS !UE_VERSION_START(5, 1, 0)

#define UE_ASSET_BUNDLE_DATA_SET_BUNDLE_ASSETS !UE_VERSION_START(5, 1, 0)

#define UE_F_NAME_PERMISSION_LIST !UE_VERSION_START(5, 1, 0)

#define UE_TRY_GET_COLLECTION_ID_F_SOFT_OBJECT_PATH !UE_VERSION_START(5, 1, 0)

#define UE_BOX_2D_EXPAND_BY_VECTOR2 UE_VERSION_START(5, 1, 0)

#define UE_APP_STYLE_GET UE_VERSION_START(5, 1, 0)

#define UE_APP_STYLE_GET_BRUSH UE_VERSION_START(5, 1, 0)

#define UE_ASSET_DATA_GET_OBJECT_PATH_STRING UE_VERSION_START(5, 1, 0)

#define UE_ASSET_DATA_GET_SOFT_OBJECT_PATH UE_VERSION_START(5, 1, 0)

#define UE_NOTIFY_REGISTRATION_EVENT UE_VERSION_START(5, 1, 0)

#define UE_VECTOR2_COMPONENT_WISE_ALL_LESS_THAN UE_VERSION_START(5, 1, 0)

#define UE_VECTOR2_COMPONENT_WISE_ALL_GREATER_THAN UE_VERSION_START(5, 1, 0)

#define UE_VECTOR2_COMPONENT_WISE_ALL_LESS_OR_EQUAL UE_VERSION_START(5, 1, 0)

#define UE_VECTOR2_COMPONENT_WISE_ALL_GREATER_OR_EQUAL UE_VERSION_START(5, 1, 0)

#define UE_F_TOP_LEVEL_ASSET_PATH UE_VERSION_START(5, 1, 0)

#define UE_T_IS_T_ENUM_AS_BYTE !UE_VERSION_START(5, 2, 0)

#define UE_REPLACE_INSTANCES_OF_CLASS_F_REPLACE_INSTANCES_OF_CLASS_PARAMETERS UE_VERSION_START(5, 2, 0)

#define UE_FIELD_NOTIFICATION UE_VERSION_START(5, 3, 0)

#define UE_F_OPTIONAL_PROPERTY UE_VERSION_START(5, 3, 0)

#define UE_F_DELEGATE_PROPERTY_SIGNATURE_FUNCTION_T_OBJECT_PTR UE_VERSION_START(5, 3, 0)

#define UE_T_BASE_STRUCTURE_F_STRATA_MATERIAL_INPUT !UE_VERSION_START(5, 4, 0)

#define UE_SOFT_OBJECT_PATH_GET_CURRENT_TAG !UE_VERSION_START(5, 4, 0)

#define UE_SOFT_OBJECT_PATH_INVALIDATE_TAG !UE_VERSION_START(5, 4, 0)

#define UE_E_CONTENT_BROWSER_ITEM_FLAGS_CATEGORY_PLUGIN UE_VERSION_START(5, 4, 0)

#define UE_T_BASE_STRUCTURE_F_FRAME_RATE !UE_VERSION_START(5, 5, 0)

#define UE_U_CONTENT_BROWSER_DATA_SOURCE_NOTIFY_ITEM_DATA_REFRESHED !UE_VERSION_START(5, 5, 0)

#define UE_STRUCT_UTILS_U_USER_DEFINED_STRUCT UE_VERSION_START(5, 5, 0)

#define UE_F_CONTENT_BROWSER_ITEM_DATA_F_NAME UE_VERSION_START(5, 5, 0)

#define UE_F_PROPERTY_GET_ELEMENT_SIZE UE_VERSION_START(5, 5, 0)

#define UE_F_PROPERTY_SET_ELEMENT_SIZE UE_VERSION_START(5, 5, 0)

#define UE_F_STRING_REMOVE_AT_E_ALLOW_SHRINKING UE_VERSION_START(5, 5, 0)

#define UE_E_INTERNAL_OBJECT_FLAGS_ASYNC_LOADING UE_VERSION_START(5, 5, 0)

#define UE_F_STRING_LEFT_CHOP_IN_LINE_E_ALLOW_SHRINKING UE_VERSION_START(5, 5, 0)

#define UE_DO_NATIVE_IMPL_OPTIMIZATION UE_VERSION_START(5, 5, 0)
