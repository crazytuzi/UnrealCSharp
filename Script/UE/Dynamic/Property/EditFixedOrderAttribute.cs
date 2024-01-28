using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class EditFixedOrderAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}