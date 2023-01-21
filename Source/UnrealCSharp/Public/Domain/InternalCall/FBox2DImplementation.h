#pragma once

#include "mono/metadata/object-forward.h"

class FBox2DImplementation
{
public:
	static bool Box2D_EqualityImplementation(const MonoObject* A, const MonoObject* B);

	static bool Box2D_InequalityImplementation(const MonoObject* A, const MonoObject* B);

	static void Box2D_AddVector2DImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Box2D_AddImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Box2D_GetReferenceImplementation(const MonoObject* InMonoObject, int32 Index, MonoObject** OutValue);

	static void Box2D_SetReferenceImplementation(const MonoObject* InMonoObject, int32 Index,
	                                             const MonoObject* InValue);

	static float Box2D_ComputeSquaredDistanceToPointImplementation(const MonoObject* InMonoObject,
	                                                               const MonoObject* Point);

	static void Box2D_ExpandByImplementation(const MonoObject* InMonoObject, float W, MonoObject** OutValue);

	static float Box2D_GetAreaImplementation(const MonoObject* InMonoObject);

	static void Box2D_GetCenterImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Box2D_GetCenterAndExtentsImplementation(const MonoObject* InMonoObject, MonoObject** center,
	                                                    MonoObject** Extents);

	static void Box2D_GetClosestPointToImplementation(const MonoObject* InMonoObject, const MonoObject* Point,
	                                                  MonoObject** OutValue);

	static void Box2D_GetExtentImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Box2D_GetSizeImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Box2D_InitImplementation(const MonoObject* InMonoObject);

	static bool Box2D_IntersectImplementation(const MonoObject* InMonoObject, const MonoObject* other);

	static bool Box2D_IsInsideVector2DImplementation(const MonoObject* InMonoObject, const MonoObject* TestPoint);

	static bool Box2D_IsInsideBox2DImplementation(const MonoObject* InMonoObject, const MonoObject* Other);

	static void Box2D_ShiftByImplementation(const MonoObject* InMonoObject, const MonoObject* Offset,
	                                        MonoObject** OutValue);

	static void Box2D_ToStringImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);
};
