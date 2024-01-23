using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class BlueprintProtectedAttribute : Attribute
    {
        public BlueprintProtectedAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}