using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class MaterialParameterCollectionFunctionAttribute : Attribute
    {
        public MaterialParameterCollectionFunctionAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}