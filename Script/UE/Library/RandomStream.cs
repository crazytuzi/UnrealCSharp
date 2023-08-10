using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FRandomStream
    {
        public void Initialize(Int32 InSeed) =>
            RandomStreamImplementation.RandomStream_InitializeImplementation(GetHandle(), InSeed);

        public void Initialize(FName InName) =>
            RandomStreamImplementation.RandomStream_InitializeNameImplementation(GetHandle(), InName);

        public void Reset() =>
            RandomStreamImplementation.RandomStream_ResetImplementation(GetHandle());

        public Int32 GetInitialSeed() =>
            RandomStreamImplementation.RandomStream_GetInitialSeedImplementation(GetHandle());

        public void GenerateNewSeed() =>
            RandomStreamImplementation.RandomStream_GenerateNewSeedImplementation(GetHandle());

        public Single GetFraction() =>
            RandomStreamImplementation.RandomStream_GetFractionImplementation(GetHandle());

        public UInt32 GetUnsignedInt() =>
            RandomStreamImplementation.RandomStream_GetUnsignedIntImplementation(GetHandle());

        public FVector GetUnitVector()
        {
            RandomStreamImplementation.RandomStream_GetUnitVectorImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public Int32 GetCurrentSeed() =>
            RandomStreamImplementation.RandomStream_GetCurrentSeedImplementation(GetHandle());

        public Single FRand() =>
            RandomStreamImplementation.RandomStream_FRandImplementation(GetHandle());

        public Int32 RandHelper(Int32 A) =>
            RandomStreamImplementation.RandomStream_RandHelperImplementation(GetHandle(), A);

        public Int32 RandRange(Int32 Min, Int32 Max) =>
            RandomStreamImplementation.RandomStream_RandRangeImplementation(GetHandle(), Min, Max);

        public Single FRandRange(Single InMin, Single InMax) =>
            RandomStreamImplementation.RandomStream_FRandRangeImplementation(GetHandle(), InMin, InMax);

        public FVector VRand()
        {
            RandomStreamImplementation.RandomStream_VRandImplementation(GetHandle(), out var OutValue);

            return OutValue;
        }

        public FVector VRandCone(FVector Dir, Single ConeHalfAngleRad)
        {
            RandomStreamImplementation.RandomStream_VRandConeHalfAngleImplementation(GetHandle(), Dir, ConeHalfAngleRad,
                out var OutValue);

            return OutValue;
        }

        public FVector VRandCone(FVector Dir, Single HorizontalConeHalfAngleRad, Single VerticalConeHalfAngleRad)
        {
            RandomStreamImplementation.RandomStream_VRandConeHorizontalAndVerticalHalfAngleImplementation(GetHandle(),
                Dir,
                HorizontalConeHalfAngleRad, VerticalConeHalfAngleRad, out var OutValue);

            return OutValue;
        }

        // @TODO
        // ExportTextItem

        public override string ToString()
        {
            RandomStreamImplementation.RandomStream_ToStringImplementation(GetHandle(), out var OutValue);

            return OutValue.ToString();
        }
    }
}