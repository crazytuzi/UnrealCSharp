#pragma once

#include "UEVersion.h"
#include "GarbageCollection/FGarbageCollectionHandle.h"
#include "mono/metadata/object-forward.h"

class FQuatImplementation
{
#if UE_LWC_TYPE
	using LwcType = double;
#else
	using LwcType = float;
#endif

public:
	static void Quat_AddImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                   MonoObject** OutValue);

	static void Quat_SubtractImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                        MonoObject** OutValue);

	static bool Quat_EqualsImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                      LwcType Tolerance);

	static bool Quat_IsIdentityImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                          LwcType Tolerance);

	static void Quat_MultiplyImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                        MonoObject** OutValue);

	static void Quat_MultiplyVectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                              const MonoObject* V, MonoObject** OutValue);

	static void Quat_MultiplyMatrixImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                              const MonoObject* M, MonoObject** OutValue);

	static void Quat_MultiplyScaleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                             LwcType Scale, MonoObject** OutValue);

	static void Quat_DivideImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, LwcType Scale,
	                                      MonoObject** OutValue);

	static bool Quat_IdenticalImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                         const MonoObject* Q, uint32 PortFlags);

	static bool Quat_EqualityImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static bool Quat_InequalityImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static LwcType Quat_DotProductImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B);

	static void Quat_MakeFromEulerImplementation(const MonoObject* Euler, MonoObject** OutValue);

	static void Quat_EulerImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                     MonoObject** OutValue);

	static void Quat_NormalizeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                         LwcType Tolerance);

	static void Quat_GetNormalizedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                             LwcType Tolerance, MonoObject** OutValue);

	static bool Quat_IsNormalizedImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static LwcType Quat_SizeImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static LwcType Quat_SizeSquaredImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static LwcType Quat_GetAngleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Quat_ToAxisAndAngleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                              MonoObject** Axis, LwcType& Angle);

	static void Quat_ToSwingTwistImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                            const MonoObject* InTwistAxis, MonoObject** OutSwing,
	                                            MonoObject** OutTwist);

	static LwcType Quat_GetTwistAngleImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                const MonoObject* TwistAxis);

	static void Quat_RotateVectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                            const MonoObject* V, MonoObject** OutValue);

	static void Quat_UnrotateVectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                              const MonoObject* V, MonoObject** OutValue);

	static void Quat_LogImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue);

	static void Quat_ExpImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue);

	static void Quat_InverseImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                       MonoObject** OutValue);

	static void Quat_EnforceShortestArcWithImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                      const MonoObject* OtherQuat);

	static void Quat_GetAxisXImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                        MonoObject** OutValue);

	static void Quat_GetAxisYImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                        MonoObject** OutValue);

	static void Quat_GetAxisZImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                        MonoObject** OutValue);

	static void Quat_GetForwardVectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                MonoObject** OutValue);

	static void Quat_GetRightVectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                              MonoObject** OutValue);

	static void Quat_GetUpVectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                           MonoObject** OutValue);

	static void Quat_VectorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                      MonoObject** OutValue);

	static void Quat_RotatorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                       MonoObject** OutValue);

	static void Quat_GetRotationAxisImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                               MonoObject** OutValue);

	static LwcType Quat_AngularDistanceImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                                  const MonoObject* Q);

	static bool Quat_ContainsNaNImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle);

	static void Quat_ToStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                        MonoObject** OutValue);

	static bool Quat_InitFromStringImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                              MonoObject* InSourceString);

	static void Quat_FindBetweenImplementation(const MonoObject* Vector1, const MonoObject* Vector2,
	                                           MonoObject** OutValue);

	static void Quat_FindBetweenNormalsImplementation(const MonoObject* Normal1, const MonoObject* Normal2,
	                                                  MonoObject** OutValue);

	static void Quat_FindBetweenVectorsImplementation(const MonoObject* Vector1, const MonoObject* Vector2,
	                                                  MonoObject** OutValue);

	static LwcType Quat_ErrorImplementation(const FGarbageCollectionHandle Q1, const FGarbageCollectionHandle Q2);

	static LwcType Quat_ErrorAutoNormalizeImplementation(const FGarbageCollectionHandle Q1,
	                                                     const FGarbageCollectionHandle Q2);

	static void Quat_FastLerpImplementation(const FGarbageCollectionHandle A, const FGarbageCollectionHandle B,
	                                        LwcType Alpha, MonoObject** OutValue);

	static void Quat_FastBilerpImplementation(const FGarbageCollectionHandle P00, const FGarbageCollectionHandle P10,
	                                          const FGarbageCollectionHandle P01, const FGarbageCollectionHandle P11,
	                                          LwcType FracX, LwcType FracY, MonoObject** OutValue);

	static void Quat_Slerp_NotNormalizedImplementation(const FGarbageCollectionHandle Quat1,
	                                                   const FGarbageCollectionHandle Quat2, LwcType Slerp,
	                                                   MonoObject** OutValue);

	static void Quat_SlerpImplementation(const FGarbageCollectionHandle Quat1, const FGarbageCollectionHandle Quat2,
	                                     LwcType Slerp, MonoObject** OutValue);

	static void Quat_SlerpFullPath_NotNormalizedImplementation(const FGarbageCollectionHandle quat1,
	                                                           const FGarbageCollectionHandle quat2, LwcType Alpha,
	                                                           MonoObject** OutValue);

	static void Quat_SlerpFullPathImplementation(const FGarbageCollectionHandle quat1,
	                                             const FGarbageCollectionHandle quat2, LwcType Alpha,
	                                             MonoObject** OutValue);

	static void Quat_SquadImplementation(const FGarbageCollectionHandle quat1, const FGarbageCollectionHandle tang1,
	                                     const FGarbageCollectionHandle quat2, const FGarbageCollectionHandle tang2,
	                                     LwcType Alpha, MonoObject** OutValue);

	static void Quat_SquadFullPathImplementation(const FGarbageCollectionHandle quat1,
	                                             const FGarbageCollectionHandle tang1,
	                                             const FGarbageCollectionHandle quat2,
	                                             const FGarbageCollectionHandle tang2, LwcType Alpha,
	                                             MonoObject** OutValue);

	static void Quat_CalcTangentsImplementation(const FGarbageCollectionHandle PrevP, const FGarbageCollectionHandle P,
	                                            const FGarbageCollectionHandle NextP, LwcType Tension,
	                                            MonoObject** OutValue);
};
