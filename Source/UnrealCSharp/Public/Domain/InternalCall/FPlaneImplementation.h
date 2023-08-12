#pragma once

#include "UEVersion.h"
#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

class FPlaneImplementation
{
#if UE_LWC_TYPE
	using LwcType = double;
#else
	using LwcType = float;
#endif

public:
	static bool Plane_IsValidImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Plane_GetOriginImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                          MonoObject** OutValue);

	static LwcType Plane_PlaneDotImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                            const MonoObject* P);

	static bool Plane_NormalizeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                          LwcType Tolerance);

	static void Plane_FlipImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                     MonoObject** OutValue);

	static void Plane_TransformByImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                            const MonoObject* M, MonoObject** OutValue);

	static void Plane_TransformByUsingAdjointTImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                         const MonoObject* M, LwcType DetM, const MonoObject* TA,
	                                                         MonoObject** OutValue);

	static bool Plane_EqualityImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static bool Plane_InequalityImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static bool Plane_EqualsImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                       LwcType Tolerance);

	static LwcType Plane_DotProductImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static void Plane_AddImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                    MonoObject** OutValue);

	static void Plane_SubtractImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                         MonoObject** OutValue);

	static void Plane_DivideImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, LwcType Scale,
	                                       MonoObject** OutValue);

	static void Plane_MultiplyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, LwcType Scale,
	                                         MonoObject** OutValue);
};
