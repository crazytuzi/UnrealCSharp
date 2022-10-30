using System;
using System.Collections.Generic;

namespace Script.Reflection.Function
{
    public class IntPtrList
    {
        public IntPtrList()
        {
            IntPtrs = new List<IntPtr>();
        }

        ~IntPtrList()
        {
            IntPtrs.Clear();
        }

        public unsafe void Add(void* InValue)
        {
            IntPtrs.Add(new IntPtr(InValue));
        }

        public readonly List<IntPtr> IntPtrs;
    }
}