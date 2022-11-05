using System;
using System.Collections.Generic;

namespace Script.Reflection.Function
{
    public class ObjectList
    {
        private ObjectList() => Value = new List<Object>();

        ~ObjectList() => Value.Clear();

        public void Add(Object InObject) => Value.Add(InObject);

        public readonly List<Object> Value;
    }
}