using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class CommutativeAssociativeBinaryOperatorAttribute : Attribute
    {
        public CommutativeAssociativeBinaryOperatorAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}