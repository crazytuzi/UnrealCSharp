using System;
using System.Collections;
using System.Collections.Generic;
using Script.Reflection.Container;

namespace Script.Common
{
    public class TSet<T> :IEnumerable 
    {
        public TSet() => SetUtils.Set_Register(this);

        public TSet(Type InValue)
        {
        }

        ~TSet() => SetUtils.Set_UnRegister(this);

        public IEnumerator  GetEnumerator()
        {
            
            for (var Index = 0; Index < Num(); Index++)
            {
                yield return this[Index];
            }
        }

        public void Empty(Int32 InExpectedNumElements = 0) => SetUtils.Set_Empty(this, InExpectedNumElements);

        public Int32 Num() => SetUtils.Set_Num(this);

        public void Add(T InValue) => SetUtils.Set_Add(this, InValue);

        public Int32 Remove(T InValue) => SetUtils.Set_Remove(this, InValue);

        public Boolean Contains(T InValue) => SetUtils.Set_Contains(this, InValue);

        //public  TArray<uint8*> ToArray()=>SetUtils.Set_ToArray(this);
       
        public Int32 Find(T Value)=>SetUtils.Set_Find(this,Value);
            
        public Int32 GetMaxIndex()=>SetUtils.Set_GetMaxIndex(this);

        public T this[Int32 InIndex]
        {
            get => SetUtils.Set_Get(this, InIndex);

            set => SetUtils.Set_Set(this, InIndex, value);
        }
        //public TSet<void*> Union(TSet<T> OtherSet)=>SetUtils.Set_Union(this,OtherSet);
        
    }
}