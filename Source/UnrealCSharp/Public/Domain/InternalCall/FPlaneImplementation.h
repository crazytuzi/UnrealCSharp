#pragma once

#include "UEVersion.h"
#include "mono/metadata/object-forward.h"

class FPlaneImplementation
{
#if UE_LWC_TYPE
	using LwcType = double;
#else
	using LwcType = float;
#endif

public:
	static bool Plane_IsValidImplementation(const MonoObject* InMonoObject);

	static void Plane_GetOriginImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static LwcType Plane_PlaneDotImplementation(const MonoObject* InMonoObject, const MonoObject* P);

	static bool Plane_NormalizeImplementation(const MonoObject* InMonoObject, LwcType Tolerance);

	static void Plane_FlipImplementation(const MonoObject* InMonoObject, MonoObject** OutValue);

	static void Plane_TransformByImplementation(const MonoObject* InMonoObject, const MonoObject* M,
	                                            MonoObject** OutValue);

	static void Plane_TransformByUsingAdjointTImplementation(const MonoObject* InMonoObject, const MonoObject* M,
	                                                         LwcType DetM, const MonoObject* TA, MonoObject** OutValue);

	static bool Plane_EqualityImplementation(const MonoObject* A, const MonoObject* B);

	static bool Plane_InequalityImplementation(const MonoObject* A, const MonoObject* B);

	static bool Plane_EqualsImplementation(const MonoObject* A, const MonoObject* B, LwcType Tolerance);

	static LwcType Plane_DotProductImplementation(const MonoObject* A, const MonoObject* B);

	static void Plane_AddImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Plane_SubtractImplementation(const MonoObject* A, const MonoObject* B, MonoObject** OutValue);

	static void Plane_DivideImplementation(const MonoObject* InMonoObject, LwcType Scale, MonoObject** OutValue);

	static void Plane_MultiplyImplementation(const MonoObject* InMonoObject, LwcType Scale, MonoObject** OutValue);
};
