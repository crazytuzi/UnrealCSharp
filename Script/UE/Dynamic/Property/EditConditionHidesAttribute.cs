using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class EditConditionHidesAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}