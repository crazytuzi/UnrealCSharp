using System.Collections.Generic;

namespace Script.Reflection.Function
{
    public class ObjectList
    {
        private ObjectList() => Value = new List<object>();

        ~ObjectList() => Value.Clear();

        public void Add(object InObject) => Value.Add(InObject);

        public readonly List<object> Value;
    }
}