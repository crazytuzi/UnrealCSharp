#pragma once

#include "UEVersion.h"

enum class UNREALCSHARPCORE_API EPropertyTypeExtent
{
	None = CPT_None,
	Byte = CPT_Byte,
	UInt16 = CPT_UInt16,
	UInt32 = CPT_UInt32,
	UInt64 = CPT_UInt64,
	Int8 = CPT_Int8,
	Int16 = CPT_Int16,
	Int = CPT_Int,
	Int64 = CPT_Int64,
	Bool = CPT_Bool,
	Bool8 = CPT_Bool8,
	Bool16 = CPT_Bool16,
	Bool32 = CPT_Bool32,
	Bool64 = CPT_Bool64,
	Float = CPT_Float,
	ObjectReference = CPT_ObjectReference,
	Name = CPT_Name,
	Delegate = CPT_Delegate,
	Interface = CPT_Interface,
	Struct = CPT_Struct,
	String = CPT_String,
	Text = CPT_Text,
	MulticastDelegate = CPT_MulticastDelegate,
	WeakObjectReference = CPT_WeakObjectReference,
	LazyObjectReference = CPT_LazyObjectReference,
	SoftObjectReference = CPT_SoftObjectReference,
	Double = CPT_Double,
	Map = CPT_Map,
	Set = CPT_Set,
	FieldPath = CPT_FieldPath,
	ClassReference = CPT_MAX + 1,
	SubclassOfReference,
	Array,
	Enum,
	SoftClassReference,
	MulticastInlineDelegate,
	MulticastSparseDelegate
#if UE_F_OPTIONAL_PROPERTY
	, Optional
#endif
};
