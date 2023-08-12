#pragma once

#include "UEVersion.h"
#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

class FBox2DImplementation
{
#if UE_LWC_TYPE
	using LwcType = double;
#else
	using LwcType = float;
#endif

public:
	static bool Box2D_EqualityImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static bool Box2D_InequalityImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static void Box2D_AddVector2DImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                            MonoObject** OutValue);

	static void Box2D_AddImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                    MonoObject** OutValue);

	static void Box2D_GetReferenceImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, int32 Index,
	                                             MonoObject** OutValue);

	static void Box2D_SetReferenceImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, int32 Index,
	                                             const MonoObject* InValue);

	static LwcType Box2D_ComputeSquaredDistanceToPointImplementation(
		const FGarbageCollectionHandle InGarbageCollectionHandle, const MonoObject* Point);

	static void Box2D_ExpandByImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, LwcType W,
	                                         MonoObject** OutValue);

	static LwcType Box2D_GetAreaImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Box2D_GetCenterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                          MonoObject** OutValue);

	static void Box2D_GetCenterAndExtentsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                    MonoObject** center, MonoObject** Extents);

	static void Box2D_GetClosestPointToImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                  const MonoObject* Point, MonoObject** OutValue);

	static void Box2D_GetExtentImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                          MonoObject** OutValue);

	static void Box2D_GetSizeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                        MonoObject** OutValue);

	static void Box2D_InitImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static bool Box2D_IntersectImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                          const MonoObject* other);

	static bool Box2D_IsInsideVector2DImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                 const MonoObject* TestPoint);

	static bool Box2D_IsInsideBox2DImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                              const MonoObject* Other);

	static void Box2D_ShiftByImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                        const MonoObject* Offset, MonoObject** OutValue);

	static void Box2D_ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                         MonoObject** OutValue);
};
