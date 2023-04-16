using System;
using System.Collections.Generic;

namespace Script.Common
{
    public class ObjectList
    {
        private ObjectList() => Value = new List<Object>();

        ~ObjectList() => Value.Clear();

        public void Add(Object InObject) => Value.Add(InObject);

        public readonly List<Object> Value;
    }
}