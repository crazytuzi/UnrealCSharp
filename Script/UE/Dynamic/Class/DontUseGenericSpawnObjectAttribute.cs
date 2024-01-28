using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class DontUseGenericSpawnObjectAttribute : Attribute
    {
        public DontUseGenericSpawnObjectAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}