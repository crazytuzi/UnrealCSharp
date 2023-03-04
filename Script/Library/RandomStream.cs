using System;
using Script.Library;
using Script.Common;

namespace Script.CoreUObject
{
    public partial class FRandomStream
    {
        public void Initialize(Int32 InSeed) =>
            RandomStreamImplementation.RandomStream_InitializeImplementation(this, InSeed);

        public void Initialize(FName InName) =>
            RandomStreamImplementation.RandomStream_InitializeNameImplementation(this, InName);

        public void Reset() =>
            RandomStreamImplementation.RandomStream_ResetImplementation(this);

        public Int32 GetInitialSeed() =>
            RandomStreamImplementation.RandomStream_GetInitialSeedImplementation(this);

        public void GenerateNewSeed() =>
            RandomStreamImplementation.RandomStream_GenerateNewSeedImplementation(this);

        public Single GetFraction() =>
            RandomStreamImplementation.RandomStream_GetFractionImplementation(this);

        public UInt32 GetUnsignedInt() =>
            RandomStreamImplementation.RandomStream_GetUnsignedIntImplementation(this);

        public FVector GetUnitVector()
        {
            RandomStreamImplementation.RandomStream_GetUnitVectorImplementation(this, out var OutValue);

            return OutValue;
        }

        public Int32 GetCurrentSeed() =>
            RandomStreamImplementation.RandomStream_GetCurrentSeedImplementation(this);

        public Single FRand() =>
            RandomStreamImplementation.RandomStream_FRandImplementation(this);

        public Int32 RandHelper(Int32 A) =>
            RandomStreamImplementation.RandomStream_RandHelperImplementation(this, A);

        public Int32 RandRange(Int32 Min, Int32 Max) =>
            RandomStreamImplementation.RandomStream_RandRangeImplementation(this, Min, Max);

        public Single FRandRange(Single InMin, Single InMax) =>
            RandomStreamImplementation.RandomStream_FRandRangeImplementation(this, InMin, InMax);

        public FVector VRand()
        {
            RandomStreamImplementation.RandomStream_VRandImplementation(this, out var OutValue);

            return OutValue;
        }

        public FVector VRandCone(FVector Dir, Single ConeHalfAngleRad)
        {
            RandomStreamImplementation.RandomStream_VRandConeHalfAngleImplementation(this, Dir, ConeHalfAngleRad,
                out var OutValue);

            return OutValue;
        }

        public FVector VRandCone(FVector Dir, Single HorizontalConeHalfAngleRad, Single VerticalConeHalfAngleRad)
        {
            RandomStreamImplementation.RandomStream_VRandConeHorizontalAndVerticalHalfAngleImplementation(this, Dir,
                HorizontalConeHalfAngleRad, VerticalConeHalfAngleRad, out var OutValue);

            return OutValue;
        }

        // @TODO
        // ExportTextItem

        public override string ToString()
        {
            RandomStreamImplementation.RandomStream_ToStringImplementation(this, out var OutValue);

            return OutValue.ToString();
        }
    }
}