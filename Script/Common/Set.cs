using System;
using Script.Reflection.Container;
using System.Collections;

namespace Script.Common
{
    public class TSet<T> : IEnumerable
    {
        public TSet() => SetUtils.Set_Register(this);

        public TSet(Type InValue)
        {
        }

        public IEnumerator GetEnumerator()
        {
            for (var Index = 0; Index < Num(); Index++)
            {
                if (IsValidIndex(Index))
                {
                    yield return this[Index];
                }
            }
        }

        ~TSet() => SetUtils.Set_UnRegister(this);

        public void Empty(Int32 InExpectedNumElements = 0) => SetUtils.Set_Empty(this, InExpectedNumElements);

        public Int32 Num() => SetUtils.Set_Num(this);

        public void Add(T InValue) => SetUtils.Set_Add(this, InValue);

        public Int32 Remove(T InValue) => SetUtils.Set_Remove(this, InValue);

        public Boolean Contains(T InValue) => SetUtils.Set_Contains(this, InValue);

        private Boolean IsValidIndex(Int32 InIndex) => SetUtils.Set_IsValidIndex(this, InIndex);

        public T this[Int32 InIndex]
        {
            get => SetUtils.Set_GetEnumerator(this, InIndex);

            set => SetUtils.Set_SetEnumerator(this, InIndex, value);

            //set => SetUtils.Set_SetEnumerator(this, InIndex, value);
        }

        public Int32 GetMaxIndex() => SetUtils.Set_GetMaxIndex(this);
    }
}